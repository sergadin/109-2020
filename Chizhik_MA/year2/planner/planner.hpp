#include <iostream>
#include <cstring>
#include <cmath>

typedef enum {EMPTY = 0, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING} FigureType;
typedef enum {WHITE = 0, BLACK} Colour;
typedef char Square;

const std::string files = "abcdefgh";
const std::string ranks = "12345678";

class Position;

class Figure {
	friend class Position;
	protected:
		Colour colour_; // белая фигура - 0, черная - 1
		FigureType type_;
		Square square_;
		const char static_cost_;
	public:
		Figure(Square sq, Colour colour, FigureType type = EMPTY, char st_cost = 0);
		~Figure() {}
		Square square() const { return square_; }
		void print_square(FILE *f) const;
		FigureType type() const { return (FigureType)type_; }
		Colour colour() const { return colour_; }
		char getCost() const { return static_cost_; }
		virtual void possible_moves(FILE* file) const {}
};

class Pawn : public Figure {
	public:
		Pawn(Square sq, Colour col = WHITE) : Figure(sq, col, PAWN, 1) {}
		void possible_moves(FILE* file) const;
};

class Knight : public Figure {
	public:
		Knight(Square sq, Colour col = WHITE) : Figure(sq, col, KNIGHT, 3) {}
		void possible_moves(FILE* file) const;
};

class Bishop : public Figure {
	public:
		Bishop(Square sq, Colour col = WHITE) : Figure(sq, col, BISHOP, 3) {}
		void possible_moves(FILE* file) const;
};

class Rook : public Figure {
	public:
		Rook(Square sq, Colour col = WHITE) : Figure(sq, col, ROOK, 5) {}
		void possible_moves(FILE* file) const;
};

class Queen : public Figure {
	public:
		Queen(Square sq, Colour col = WHITE) : Figure(sq, col, QUEEN, 9) {}
		void possible_moves(FILE* file) const;
};

class King : public Figure {
	public:
		King(Square sq, Colour col = WHITE) : Figure(sq, col, KING, 100) {}
		void possible_moves(FILE* file) const;
};

class Position {
	private:
		Colour turn_;
		Square squares_[64];
		char are_kings_touched_; // младший разряд для белого, второй - для черного
		char are_rooks_touched_; // от младшего к 4-му в порядке a1-h1-a8-h8
	public:
		Position(char *sqs, char akt = 0, char art = 0, Colour turn = WHITE);
		char get_figure_info(Square sq) const;
};

class Aim {
	private:
		const Position position_;
		const char selected_figure_; // координата клетки с основной фигурой
		char target_square_; // координата целевой клетки
		const bool is_capture_; // является ли целью взятие фигуры, расположенной на этой клетке
	public:
		Aim(Position pos, char sf, char tc, bool ic) 
			: position_(pos), selected_figure_(sf), target_square_(tc), is_capture_(ic) {}
		~Aim();
};
