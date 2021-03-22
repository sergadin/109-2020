#include "planner.hpp"

Figure::Figure(Square sq, Colour colour, FigureType type, char st_cost) 
	: square_(sq), colour_(colour), type_(type), static_cost_(st_cost) {}

void Pawn::possible_moves(FILE *f) const { // пока передвижение на соседнюю вертикаль считаем потенциально возможным, не обращая внимание на наличие или отсутствие там фигур
	char rk = square_ % 8;
	char file = square_ >> 3;

	char min_file = (file > 0) ? (file - 1) : 0;

	char coef = 1 - colour_ * 2; // если пешка белая, то 1, иначе - -1
	bool can_jump = (colour_ == 0 && rk == 1) || (colour_ == 1 && rk == 6);

	char square_name[3];
	square_name[2] = 0;

	for (char k = min_file; (k <= (file + 1)) && (k < 8); k++) {
		char max_prom = (1 + (char)can_jump * (1 - fabs(k - file))); // Если k == file, max_prom[otion] зависит от того, находится ли пешка в начальной позиции;
									     // если fabs(k - file) == 1, то продвинуться в любом случае можно только на одну горизонталь
		for (char l = 1; l <= max_prom; l++) {
			square_name[0] = files[k];
			square_name[1] = ranks[rk + l * coef];

			fprintf(f, "%s\n", square_name);
		}
	}
} // считается, что пешка не может находиться на поле превращения - иначе позиция некорректна

void Knight::possible_moves(FILE *f) const {
	char rk = square_ % 8;
	char file = square_ >> 3;

	char min_file = (file > 2) ? (file - 2) : 0;

	char square_name[3];
	square_name[2] = 0;

	for (char k = min_file; k < file + 3 && k < 8; k++) {
		if (k == file) continue;
		char rk_diff = 3 - fabs(file - k);
		
		for (char l = -1; l <= 1; l += 2) {
			square_name[0] = files[k];
			square_name[1] = ranks[rk + l * rk_diff];

			fprintf(f, "%s\n", square_name);
		}
	}
}

void Bishop::possible_moves(FILE *f) const {
	char rk = square_ % 8;
	char file = square_ >> 3;
	//std::cout << "rk = " << (int)rk << ", file = " << (int)file << std::endl;

	char alt_min = ((7 - rk) < file) ? (7 - rk) : file; // число клеток, которое можно пройти по диагонали наверх налево
	char min = (rk < file) ? rk : file;

	//std::cout << "min = " << (int)min << ", alt_min = " << (int)alt_min << std::endl;
	//std::cout << "rk - min = " << (int)(rk - min) << ", file - min = " << (int)(file - min) << std::endl;	
	//std::cout << "rk + alt_min = " << (int)(rk + alt_min) << ", file - alt_min = " << (int)(file - alt_min) << std::endl;

	char square_name[3];
	square_name[2] = 0;

	for (char k = file - min, l = rk - min; k < 8 && l < 8; k++, l++) {
		if (k == file && l == rk) continue;
		square_name[0] = files[k];
		square_name[1] = ranks[l];

		fprintf(f, "%s\n", square_name);
	}

	for (char k = file - alt_min, l = rk + alt_min; k < 8 && l >= 0; k++, l--) {
		if (k == file && l == rk) continue;
		square_name[0] = files[k];
		square_name[1] = ranks[l];

		fprintf(f, "%s\n", square_name);
	}
}

void Rook::possible_moves(FILE *f) const {
	char rk = square_ % 8;
	char file = square_ >> 3;

	char square_name[3];
	square_name[2] = 0;

	for (char k = 0; k < 8; k++) {
		if (k == file) continue;
		square_name[0] = files[k];
		square_name[1] = ranks[rk];

		fprintf(f, "%s\n", square_name);
	}

	for (char k = 0; k < 8; k++) {
		if (k == rk) continue;
		square_name[0] = files[file];
		square_name[1] = ranks[k];

		fprintf(f, "%s\n", square_name);
	}
}

void Queen::possible_moves(FILE *f) const {
	char rk = square_ % 8;
	char file = square_ >> 3;

	char alt_min = ((7 - rk) < file) ? (7 - rk) : file;
	char min = (rk < file) ? rk : file;

	char square_name[3];
	square_name[2] = 0;

	for (char k = 0; k < 8; k++) {
		if (k == file) continue;
		square_name[0] = files[k];
		square_name[1] = ranks[rk];

		fprintf(f, "%s\n", square_name);
	}

	for (char k = 0; k < 8; k++) {
		if (k == rk) continue;
		square_name[0] = files[file];
		square_name[1] = ranks[k];

		fprintf(f, "%s\n", square_name);
	}

	for (char k = file - min, l = rk - min; k < 8 && l < 8; k++, l++) {
		if (k == file && l == rk) continue;
		square_name[0] = files[k];
		square_name[1] = ranks[l];

		fprintf(f, "%s\n", square_name);
	}

	for (char k = file - alt_min, l = rk + alt_min; k < 8 && l >= 0; k++, l--) {
		if (k == file && l == rk) continue;
		square_name[0] = files[k];
		square_name[1] = ranks[l];

		fprintf(f, "%s\n", square_name);
	}
}

void King::possible_moves(FILE *f) const {
	char rk = square_ % 8;
	char file = square_ >> 3;

	char square_name[3];
	square_name[2] = 0;

	char min_rk = (rk > 0) ? (rk - 1) : 0;
	char min_file = (file > 0) ? (file - 1) : 0;

	for (char k = min_file; k < file + 2 && k < 8; k++) {
		for (char l = min_rk; l < rk + 2 && l < 8; l++) {
			if (k == file && l == rk) continue;
			square_name[0] = files[k];
			square_name[1] = ranks[l];

			fprintf(f, "%s\n", square_name);
		}
	}
}

Position::Position(char *sqs, char akt, char art, Colour t) 
	: are_kings_touched_(akt), are_rooks_touched_(art), turn_(t) {
	for (int i = 0; i < 64; i++) {
		squares_[i] = sqs[i];
	}
}

char Position::get_figure_info(Square square) const {
	return squares_[square];
}

void Figure::print_square(FILE *f) const {
	fprintf(f, "%c%c", files[square_ >> 3], ranks[square_ % 8]);
}
