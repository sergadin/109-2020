#include <iostream>
#include <cstring>

typedef enum {EMPTY = 0, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING} FigureType;
typedef enum {WHITE = 0, BLACK} Turn;

const std::string files = "abcdefgh";
const std::string ranks = "12345678";

class Position;

class Figure {
	friend class Position;
	protected:
		bool colour_; // белая фигура - 0, черная - 1
		FigureType type_;
		char position_;
	public:
		Figure(char pos = -1, char t = 0);
		~Figure() {}
		char position() { return position_; }
		void print_position(std::ostream& os);
		FigureType type() { return (FigureType)type_; }
		bool colour() { return colour_; }
		virtual char getCost() { return -1; }
		virtual void possible_turns(FILE* file);
};

class Pawn : public Figure {
	public:
		void possible_turns(FILE* file) {}
		char getCost() { return 1; }
};

class Knight : public Figure {
	public:
		void possible_turns(FILE* file) {}
		char getCost() { return 3; }
};

class Bishop : public Figure {
	public:
		void possible_turns(FILE* file);
		char getCost() { return 3; }
};

class Rook : public Figure {
	public:
		void possible_turns(FILE* file);
		char getCost() { return 5; }
};

class Queen : public Figure {
	public:
		void possible_turns(FILE* file) {} // Объединение методов от rook и bishop
		char getCost() { return 9; }
};

class King : public Figure {
	public:
		void possible_turns(FILE* file) {}
		char getCost() { return 100; }
};

class Position {
	private:
		Turn turn_;
		char squares_[64];
		char are_kings_touched_; // младший разряд для белого, второй - для черного
		char are_rooks_touched_; // от младшего к 4-му в порядке a1-h1-a8-h8
	public:
		Position(char *sqs, char akt = 0, char art = 0, Turn t = WHITE);
		char get_figure_info(char index);
		//bool Move(char from, char to);
};

class Aim {
	private:
		const Position position_;
		const char selected_figure_; // координата клетки с основной фигурой
		char target_square_; // координата целевой клетки
		const bool is_capture_; // является ли целью взятие фигуры, расположенной на этой клетке
	public:
		Aim(Position pos, char sf, char tc, bool ic) : position_(pos), selected_figure_(sf), target_square_(tc), is_capture_(ic) {}
		~Aim();
};
