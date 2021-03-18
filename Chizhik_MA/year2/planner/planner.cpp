#include "planner.hpp"

Figure::Figure(char pos, char type) : position_(pos) {
	type_ = (FigureType)(type % 8);
	colour_ = type >> 3;
}

//std::cout << "Hello, type of square " << i << " is " << squares_[i].type_ << std::endl;
//std::cout << "Colour of " << i << " is " << squares_[i].colour_ << std::endl;

void Bishop::possible_turns(FILE* file) {
	char hor = position_ % 8;
	char ver = (position_ % 16) >> 3;

	std::cout << "Hi there! hor = " << hor << ", ver = " << ver << std::endl;

	char alt_min = ((7 - hor) < ver) ? (7 - hor) : ver; // число клеток, которое можно пройти по диагонали наверх налево
	char min = (hor < ver) ? hor : ver;

	char square_name[3];
	square_name[2] = 0;

	for (char k = hor - min, l = ver - min; k < 8 && l < 8; k++, l++) {
		if (k == hor) continue;
		square_name[0] = files[k];
		square_name[1] = ranks[k];

		fprintf(file, "%s\n", square_name);
	}

	for (char k = hor + alt_min, l = ver - alt_min; k >= 0 && l < 8; k--, l++) {
		if (k == hor) continue;
		square_name[0] = files[k];
		square_name[1] = ranks[k];

		fprintf(file, "%s\n", square_name);
	}
}

void Rook::possible_turns(FILE* file) {
	char hor = position_ % 8;
	char ver = position_ >> 3;

	char square_name[3];
	square_name[2] = 0;

	for (char k = 0; k < 8; k++) {
		if (k == ver) continue;
		square_name[1] = ranks[hor];
		square_name[0] = files[k];

		fprintf(file, "%s\n", square_name);
	}

	for (char k = 0; k < 8; k++) {
		if (k == hor) continue;
		square_name[1] = ranks[k];
		square_name[0] = files[hor];

		fprintf(file, "%s\n", square_name);
	}
}

Position::Position(char *sqs, char akt, char art, Turn t) : are_kings_touched_(akt), are_rooks_touched_(art), turn_(t) {
	for (int i = 0; i < 64; i++) {
		squares_[i] = sqs[i];
	}
}

char Position::get_figure_info(char index) {
	return squares_[index];
}

void Figure::print_position(std::ostream& os) {
	os << files[position_ >> 3] << ranks[position_ % 8];
}
