#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <cmath>

#define DEBUG

class PlannerException {
	private:
		// Код ошибки
		const int error_code_;
		// Сообщение для пользователя
		const std::string reason_;
		// Тип исключения (по умолчанию - пустая строка)
		const std::string type_;
	public:
		// Конструктор исключения
		PlannerException(int code, const std::string& message, const std::string& type = "") : error_code_(code), reason_(message), type_(type) {}
		// Получение кода ошибки
		int code() const { return error_code_; }
		// Получение сообщения
		const std::string& message() const { return reason_; }
		
		// Операторы форматированного вывода ошибки
		friend std::ostream& operator<<(std::ostream& os, const PlannerException& e);
		friend FILE* operator<<(FILE *f, const PlannerException& e);
};

class FENException : public PlannerException {
	public:
		FENException(int code, const std::string& message): PlannerException(code, message, "FEN") {}
};

class PositionException : public PlannerException {
	public:
		PositionException(int code, const std::string& message): PlannerException(code, message, "Position") {}
};

/* Тип фигуры, расположенной в данной клетке:
 * 0 - фигура отсутствует
 * 1 - пешка
 * 2 - конь
 * 3 - слон
 * 4 - ладья
 * 5 - ферзь
 * 6 - король
 */
typedef enum {EMPTY = 0, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING} FigureType;

/* Цвет фигуры или очередность хода
 * 0 - белый
 * 1 - черный
 */ 
typedef enum {WHITE = 0, BLACK} Colour;

const std::string digits = "0123456789";
const std::string b_figures = "epnbrqk";
const std::string w_figures = "EPNBRQK";
const std::string files = "abcdefgh";
const std::string ranks = "12345678";

/* Координата клетки шахматной доски
 * Поля:
 * file - вертикаль
 * rank - горизонталь
 */
typedef struct Square {
	unsigned file: 3;
	unsigned rank: 3;

	// Конструктор без параметров
	// Cоздает координату a1
	Square() {
		file = 0;
		rank = 0;
	}

	// Конструктор копирования
	Square(const Square& sq) {
		file = sq.file;
		rank = sq.rank;
	}

	// Конструктор, получающий в качестве входных данных число типа char
	// 3 младших бита sq  - номер горизонтали, 4-6 биты - номер вертикали
	Square(char sq) {
		file = sq >> 3;
		rank = sq % 8;
	}

	// Преобразование Square в номер клетки (от 0 до 63)
	// Нумерация клеток доски - снизу вверх, слева направо (a1 -> a8, b1 -> b8, ...)
	char to_char() const {
		return file * 8 + rank;
	}

	// Печать координаты в файл f в человекочитаемом формате 
	void print_name(FILE *f) const;
} Square;

/* Тип и цвет фигуры
 * Поля:
 * figtype - тип фигуры, соответствующий нумерации FigureType
 * colour - цвет фигуры
 */
typedef struct FigureInfo {
	unsigned figtype_: 3; // от 0 до 6
	unsigned colour_: 1; // белая фигура - 0, черная - 1

	// Конструктор без параметров
	FigureInfo() {
		figtype_ = 0;
		colour_ = 0;
	}

	Colour colour() const {
		return (Colour)colour_;
	}

	FigureType type() const {
		return (FigureType)figtype_;
	}

	// Конструктор, получающий в качестве входных данных тип и цвет
	FigureInfo(FigureType type, Colour col) {
		figtype_ = (char)type;
		colour_ = (char)col;
	}	
} FigureInfo;

/* Номинальная стоимость фигуры описывается константой типа char */
typedef const char Cost;

/* Структура, содержащая информацию о том, ходили ли ладьи и короли в партии
 *
 * rook - ладья, king - король
 *
 * Префиксы для королей символизируют их цвет:
 * w - белый, b - черный
 *
 * Префиксы для ладей состоят из двух букв:
 * первая показывает, слева (l, вертикаль 'a') или справа (r, вертикаль 'h') находится ладья;
 * вторая аналогично префиксам для королей отвечает за цвет
 */
typedef struct Touched {
	unsigned lw_rook: 1;
	unsigned rw_rook: 1;
	unsigned lb_rook: 1;
	unsigned rb_rook: 1;
	unsigned w_king: 1;
	unsigned b_king: 1;

	// Конструктор
	// Младший разряд are_kings_touched для белого, второй - для черного короля
	// От младшего к 4-му разряду are_rooks_touched - булевые значения, отвечающие за то, ходили ли ладьи со стартовыми позициями a1-h1-a8-h8 соответственно
	Touched (unsigned char are_kings_touched, unsigned char are_rooks_touched) {
		w_king = are_kings_touched & 1;
		b_king = (are_kings_touched & 2) >> 1;

		lw_rook = are_rooks_touched & 1;
		rw_rook = (are_rooks_touched & 2) >> 1;
		lb_rook = (are_rooks_touched & 4) >> 2;
		rb_rook = (are_rooks_touched & 8) >> 3;
	}
} Touched;

class Position;
class Figure {
	// Объявление дружественным класса позиции
	friend class Position;
	protected:
		// Тип и цвет фигуры
		FigureInfo figinfo_;

		// Номинальная стоимость фигуры
		Cost static_cost_;
	public:
		// Конструктор
		Figure(Colour colour, FigureType type = EMPTY, Cost st_cost = 0);

		// Деструктор
		~Figure() {}

		// Получение типа фигуры
		FigureType type() const { return (FigureType)figinfo_.figtype_; }

		// Получение цвета фигуры
		Colour colour() const { return (Colour)figinfo_.colour_; }

		// Получение номинальной стоимости фигуры
		Cost getCost() const { return static_cost_; }

		// Вывод в файл f полей, на которые ближайшим ходом потенциально может пойти фигура с поля start_sq
		// (все фигуры совершают ходы будто на пустой доске; при этом для пешек считаются возможными не только ходы по прямой,
		// но и взятия в любую сторону)
		virtual void possible_moves(FILE* file, Square start_sq) const = 0;
};

/* Далее - классы для всех возможных типов фигур, наследующие Figure */

class Pawn : public Figure {
	public:
		Pawn(Colour col = WHITE) : Figure(col, PAWN, 1) {}
		void possible_moves(FILE* file, Square start_sq) const;
};

class Knight : public Figure {
	public:
		Knight(Colour col = WHITE) : Figure(col, KNIGHT, 3) {}
		void possible_moves(FILE* file, Square start_sq) const;
};

class Bishop : public Figure {
	public:
		Bishop(Colour col = WHITE) : Figure(col, BISHOP, 3) {}
		void possible_moves(FILE* file, Square start_sq) const;
};

class Rook : public Figure {
	public:
		Rook(Colour col = WHITE) : Figure(col, ROOK, 5) {}
		void possible_moves(FILE* file, Square start_sq) const;
};

class Queen : public Figure {
	public:
		Queen(Colour col = WHITE) : Figure(col, QUEEN, 9) {}
		void possible_moves(FILE* file, Square start_sq) const;
};

class King : public Figure {
	public:
		King(Colour col = WHITE) : Figure(col, KING, 100) {}
		void possible_moves(FILE* file, Square start_sq) const;
};

class Position {
	private:
		// Очередность хода
		Colour turn_;

		// Массив данных о типе и цвете каждой фигуры на доске
		FigureInfo squares_[64];

		// Информация о том, предшествовали ли полученной позиции ходы королей и ладей
		Touched touched_;

		// Поле, на котором ближайшим ходом можно совершить взятие на проходе
		Square en_passant_;

		// Число полуходов без взятий и ходов пешками
		unsigned char halfmove_clock_;

		// Номер хода
		unsigned short fullmove_number_;
	public:
		// Конструктор
		// sqs - массив, содержащий информацию о типе и цвете фигур:
		// последние три бита в sqs[i] выделяются под тип фигуры, четвертый справа бит - под цвет;
		// are_kings_touched и are_rooks_touched являются в сущности теми же переменными, что используются для создания структуры Touched;
		// turn - очередность хода;
		// en_passant - координата клетки, на которую возможно совершить ход со взятием на проходе (только если оно действительно возможно; иначе указывается клетка a1);
		// halfmove_clock - число полуходов без взятий и ходов пешками
		// fullmove_number - номер хода
		Position(unsigned char *sqs, unsigned char are_kings_touched = 3, unsigned char are_rooks_touched = 15, Colour turn = WHITE, unsigned char en_passant = 0, unsigned short halfmove_clock = 0, unsigned short fullmove_number = 1);

		// Конструктор, восстанавливающий позицию из ее FEN-представления
		// FEN - строка в формате FEN
		Position(const std::string& FEN);

		// Получение структуры с типом и цветом фигуры по координате sq соответствующей клетки
		FigureInfo get_figure_info(Square sq) const;

		// Запись позиции в формате FEN	
		// Возвращаемое значение - строка с записью позиции в формате FEN
		std::string to_FEN() const;
};

//class Path {
//	private:
//		SquareNode *start_position;
//		SquareNode *destination;
//	public:
//		Path(Square start, Square finish);
//}

//struct SquareNode {
//	Square value_;
//	SquareNode *next_;
//	SquareNode *previous_;
//	SquareNode(Square value) : value_(value) {}
//}

class Aim {
	private:
		// Начальная позиция
		const Position position_;

		// Координата клетки с основной фигурой
		const Square selected_figure_;

		// Координата целевой клетки
		Square target_square_;

		// Является ли целью взятие фигуры, расположенной на целевой клетке
		const bool is_capture_;
	public:
		// Конструктор
		Aim(Position pos, Square selected, Square target, bool capture) 
			: position_(pos), selected_figure_(selected), target_square_(target), is_capture_(capture) {}

		// Деструктор
		~Aim();
};

/* Вывод в файл f координаты клетки
 * Параметры:
 * f - файл, куда выводится координата
 * file - номер горизонтали
 * rank - номер вертикали
 */
void print_square_name(FILE *f, char file, char rank);

std::ostream& operator<<(std::ostream& os, const PlannerException& e);
FILE* operator<<(FILE *f, const PlannerException& e);
