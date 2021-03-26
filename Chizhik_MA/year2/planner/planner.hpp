#include <iostream>
#include <cstring>
#include <cmath>

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
	Square() {
		file = 0;
		rank = 0;
	}

	// Конструктор, получающий в качестве входных данных число типа char
	// 3 младших бита sq  - номер горизонтали, 4-6 биты - номер вертикали
	Square(char sq) {
		file = sq >> 3;
		rank = sq % 8;
	}

	// Преобразование Square в номер клетки (от 0 до 63)
	// Нумерация клеток доски - снизу вверх, слева направо (a1 -> a8, b1 -> b8, ...)
	char to_char() {
		return file * 8 + rank;
	}
} Square;

/* Тип и цвет фигуры
 * Поля:
 * figtype - тип фигуры, соответствующий нумерации FigureType
 * colour - цвет фигуры
 */
typedef struct FigureInfo {
	unsigned figtype: 3; // от 0 до 6
	unsigned colour: 1; // белая фигура - 0, черная - 1

	// Конструктор без параметров
	FigureInfo() {
		figtype = 0;
		colour = 0;
	}

	// Конструктор, получающий в качестве входных данных тип и цвет
	FigureInfo(FigureType type, Colour col) {
		figtype = (char)type;
		colour = (char)col;
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
	Touched (char are_kings_touched, char are_rooks_touched) {
		w_king = are_kings_touched & 1;
		b_king = are_kings_touched & 2;

		lw_rook =  are_rooks_touched & 1;
		rw_rook =  are_rooks_touched & 2;
		lb_rook =  are_rooks_touched & 4;
		rb_rook =  are_rooks_touched & 8;
	}
} Touched;

class Position;
class Figure {
	// Объявление дружественным класса позиции
	friend class Position;
	protected:
		// Тип и цвет фигуры
		FigureInfo figinfo_;

		// Координата фигуры
		Square square_;

		// Номинальная стоимость фигуры
		Cost static_cost_;
	public:
		// Конструктор
		Figure(char sq, Colour colour, FigureType type = EMPTY, Cost st_cost = 0);

		// Деструктор
		~Figure() {}

		// Получение координаты фигуры
		Square square() const { return square_; }

		// Печать координаты фигуры в файл f в человекочитаемом виде
		void print_fig_square_name(FILE *f) const;

		// Получение типа фигуры
		FigureType type() const { return (FigureType)figinfo_.figtype; }

		// Получение цвета фигуры
		Colour colour() const { return (Colour)figinfo_.colour; }

		// Получение номинальной стоимости фигуры
		Cost getCost() const { return static_cost_; }

		// Вывод в файл f полей, на которые ближайшим ходом потенциально может пойти фигура
		// (все фигуры совершают ходы будто на пустой доске; при этом для пешек считаются возможными не только ходы по прямой,
		// но и взятия в любую сторону)
		virtual void possible_moves(FILE* file) const {}
};

/* Далее - классы для всех возможных типов фигур, наследующие Figure */

class Pawn : public Figure {
	public:
		Pawn(char sq, Colour col = WHITE) : Figure(sq, col, PAWN, 1) {}
		void possible_moves(FILE* file) const;
};

class Knight : public Figure {
	public:
		Knight(char sq, Colour col = WHITE) : Figure(sq, col, KNIGHT, 3) {}
		void possible_moves(FILE* file) const;
};

class Bishop : public Figure {
	public:
		Bishop(char sq, Colour col = WHITE) : Figure(sq, col, BISHOP, 3) {}
		void possible_moves(FILE* file) const;
};

class Rook : public Figure {
	public:
		Rook(char sq, Colour col = WHITE) : Figure(sq, col, ROOK, 5) {}
		void possible_moves(FILE* file) const;
};

class Queen : public Figure {
	public:
		Queen(char sq, Colour col = WHITE) : Figure(sq, col, QUEEN, 9) {}
		void possible_moves(FILE* file) const;
};

class King : public Figure {
	public:
		King(char sq, Colour col = WHITE) : Figure(sq, col, KING, 100) {}
		void possible_moves(FILE* file) const;
};

class Position {
	private:
		// Очередность хода
		Colour turn_;

		// Массив данных о типе и цвете каждой фигуры на доске
		FigureInfo squares_[64];

		// Информация о том, предшествовали ли полученной позиции ходы королей и ладей
		Touched touched_; 
	public:
		// Конструктор
		// sqs - массив, содержащий информацию о типе и цвете фигур:
		// последние три бита в sqs[i] выделяются под тип фигуры, четвертый справа бит - под цвет;
		// are_kings_touched и are_rooks_touched являются в сущности теми же переменными, что используются для создания структуры Touched
		// turn - очередность хода
		Position(char *sqs, char are_kings_touched = 0, char are_rooks_touched = 0, Colour turn = WHITE);

		// Получение структуры с типом и цветом фигуры по координате sq соответствующей клетки
		FigureInfo get_figure_info(Square sq) const;
};

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
 * file - номер горизонтали
 * rank - номер вертикали
 */
void print_square_name(FILE *f, char file, char rank);
