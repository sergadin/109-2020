typedef enum {EMPTY = 0, SPAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING} FigureType;
typedef enum {WHITE = 0, BLACK} Turn;

class Figure {
	private:
		FigureType type_;
		char position_;
	public:
		Figure(FigureType type, char position) type_(type), position_(position) {}
		~Figure();
		char position() { return position_; }
		FigureType type() { return type_; }
		virtual char getCost() {}
		virtual char first_possible_cell_for_empty() {}
}

~Figure() {}

class Spawn : public Figure {
	public:
		char getCost() { return 1; }
}

class Knight : public Figure {
	public:
		char getCost() { return 3; }
}

class Bishop : public Figure {
	public:
		char getCost() { return 3; }
}

class Rook : public Figure {
	public:
		char getCost() { return 5; }
}

class Queen : public Figure {
	public:
		char getCost() { return 9; }
}

class King : public Figure {
	public:
		char getCost() { return 100; }
}

class Position {
	private:
		Turn turn_;
		char cells_[64];
		char are_kings_touched_; // младший разряд для белого, второй - для черного
		char are_rooks_touched; // от младшего к 4-му в порядке a1-h1-a8-h8
	public:
		Position(char *cells, Turn turn = WHITE);
		bool Move(char from, char to);
}

class Aim {
	private:
		const Position position_;
		const char selected_figure; // координата клетки с основной фигурой
		char target_cell; // координата целевой клетки
		const bool is_capture; // является ли целью взятие фигуры, расположенной на этой клетке
}
