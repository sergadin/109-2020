#include <iostream>
#include <cstring>
#include <cmath>

typedef enum {EMPTY = 0, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING} FigureType;
typedef enum {WHITE = 0, BLACK} Colour;

typedef struct Square {
	unsigned file: 3;
	unsigned rank: 3;

	Square() {
		file = 0;
		rank = 0;
	}

	Square(char sq) {
		file = sq >> 3;
		rank = sq % 8;
	}

	char to_char() {
		return file * 8 + rank;
	}
} Square;
typedef struct FigureInfo {
	unsigned figtype: 3; // от 0 до 6
	unsigned colour: 1; // белая фигура - 0, черная - 1
	FigureInfo() {
		figtype = 0;
		colour = 0;
	}
} FigureInfo;
typedef const char Cost;

const std::string files = "abcdefgh";
const std::string ranks = "12345678";

class Position;

void print_square_name(FILE *f, char file, char rank);
class Figure {
	friend class Position;
	protected:
		//Colour colour_; 
		//FigureType type_;

		FigureInfo figinfo_;
		Square square_;
		Cost static_cost_;
	public:
		Figure(char sq, Colour colour, FigureType type = EMPTY, Cost st_cost = 0);
		~Figure() {}
		Square square() const { return square_; }
		void print_fig_square_name(FILE *f) const;
		FigureType type() const { return (FigureType)figinfo_.figtype; }
		Colour colour() const { return (Colour)figinfo_.colour; }
		Cost getCost() const { return static_cost_; }
		virtual void possible_moves(FILE* file) const {}
	friend void print_square_name(FILE *f, char file, char rank);
};


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
		Colour turn_;
		FigureInfo squares_[64];
		char are_kings_touched_; // младший разряд для белого, второй - для черного
		char are_rooks_touched_; // от младшего к 4-му в порядке a1-h1-a8-h8
	public:
		// Последние три бита в sqs[i] выделяются под тип фигуры, четвертый справа бит - под цвет
		Position(char *sqs, char akt = 0, char art = 0, Colour turn = WHITE);
		FigureInfo get_figure_info(Square sq) const; // Позднее - FigureInfo
};

class Aim {
	private:
		const Position position_;
		const Square selected_figure_; // координата клетки с основной фигурой
		Square target_square_; // координата целевой клетки
		const bool is_capture_; // является ли целью взятие фигуры, расположенной на этой клетке
	public:
		Aim(Position pos, Square selected, Square target, bool capture) 
			: position_(pos), selected_figure_(selected), target_square_(target), is_capture_(capture) {}
		~Aim();
};
