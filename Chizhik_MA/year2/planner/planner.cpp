#include "planner.hpp"

Figure::Figure(char sq, Colour colour, FigureType type, Cost st_cost) 
	: square_(sq), static_cost_(st_cost) {
	figinfo_.figtype = (char)type;
	figinfo_.colour = (char)colour;
}

void Pawn::possible_moves(FILE *f) const { // пока передвижение на соседнюю вертикаль считаем потенциально возможным, не обращая внимание на наличие или отсутствие там фигур
	char rk = square_.rank;
	char file = square_.file;

	char min_file = (file > 0) ? (file - 1) : 0;

	char coef = 1 - (char)colour() * 2; // если пешка белая, то 1, иначе - -1
	bool can_jump = ((char)colour() == 0 && rk == 1) || ((char)colour() == 1 && rk == 6);

	for (char k = min_file; (k <= (file + 1)) && (k < 8); k++) {
		char max_prom = (1 + (char)can_jump * (1 - fabs(k - file))); // Если k == file, max_prom[otion] зависит от того, находится ли пешка в начальной позиции;
									     // если fabs(k - file) == 1, то продвинуться в любом случае можно только на одну горизонталь
		for (char l = 1; l <= max_prom; l++) {
			//std::cout << "Annie, are you OK?" << std::endl;
			print_square_name(f, k, rk + l * coef);
			//std::cout << "Are you OK, Annie?" << std::endl;
		}
	}
} // считается, что пешка не может находиться на поле превращения - иначе позиция некорректна

void Knight::possible_moves(FILE *f) const {
	char rk = square_.rank;
	char file = square_.file;

	char min_file = (file > 2) ? (file - 2) : 0;

	for (char k = min_file; k < file + 3 && k < 8; k++) {
		if (k == file) continue;
		char rk_diff = 3 - fabs(file - k);
		
		for (char l = -1; l <= 1; l += 2) {
			print_square_name(f, k, rk + l * rk_diff);
		}
	}
}

void Bishop::possible_moves(FILE *f) const {
	char rk = square_.rank;
	char file = square_.file;
	//std::cout << "rk = " << (int)rk << ", file = " << (int)file << std::endl;

	char alt_min = ((7 - rk) < file) ? (7 - rk) : file; // число клеток, которое можно пройти по диагонали наверх налево
	char min = (rk < file) ? rk : file;

	// Отладочная печать
	//std::cout << "min = " << (int)min << ", alt_min = " << (int)alt_min << std::endl;
	//std::cout << "rk - min = " << (int)(rk - min) << ", file - min = " << (int)(file - min) << std::endl;	
	//std::cout << "rk + alt_min = " << (int)(rk + alt_min) << ", file - alt_min = " << (int)(file - alt_min) << std::endl;

	for (char k = file - min, l = rk - min; k < 8 && l < 8; k++, l++) {
		if (k == file && l == rk) continue;
		print_square_name(f, k, l);
	}

	for (char k = file - alt_min, l = rk + alt_min; k < 8 && l >= 0; k++, l--) {
		if (k == file && l == rk) continue;
		print_square_name(f, k, l);
	}
}

void Rook::possible_moves(FILE *f) const {
	char rk = square_.rank;
	char file = square_.file;

	for (char k = 0; k < 8; k++) {
		if (k == file) continue;
		print_square_name(f, k, rk);
	}

	for (char k = 0; k < 8; k++) {
		if (k == rk) continue;
		print_square_name(f, file, k);
	}
}

void Queen::possible_moves(FILE *f) const {
	char rk = square_.rank;
	char file = square_.file;

	char alt_min = ((7 - rk) < file) ? (7 - rk) : file;
	char min = (rk < file) ? rk : file;

	for (char k = 0; k < 8; k++) {
		if (k == file) continue;
		print_square_name(f, k, rk);
	}

	for (char k = 0; k < 8; k++) {
		if (k == rk) continue;
		print_square_name(f, file, k);
	}

	for (char k = file - min, l = rk - min; k < 8 && l < 8; k++, l++) {
		if (k == file && l == rk) continue;
		print_square_name(f, k, l);
	}

	for (char k = file - alt_min, l = rk + alt_min; k < 8 && l >= 0; k++, l--) {
		if (k == file && l == rk) continue;
		print_square_name(f, k, l);
	}
}

void King::possible_moves(FILE *f) const {
	char rk = square_.rank;
	char file = square_.file;

	char min_rk = (rk > 0) ? (rk - 1) : 0;
	char min_file = (file > 0) ? (file - 1) : 0;

	for (char k = min_file; k < file + 2 && k < 8; k++) {
		for (char l = min_rk; l < rk + 2 && l < 8; l++) {
			if (k == file && l == rk) continue;
			print_square_name(f, k, l);
		}
	}
}

Position::Position(char *sqs, char akt, char art, Colour t) 
	: are_kings_touched_(akt), are_rooks_touched_(art), turn_(t) {
	for (int i = 0; i < 64; i++) {
		squares_[i].colour = sqs[i] >> 3;
		squares_[i].figtype = sqs[i] % 8;
	}
}

FigureInfo Position::get_figure_info(Square square) const {
	return squares_[square.to_char()];
}

void Figure::print_fig_square_name(FILE *f) const {
	fprintf(f, "%c%c", files[square_.file], ranks[square_.rank]);
}

void print_square_name(FILE *f, char file, char rank) {
	fprintf(f, "%c%c\n", files[file], ranks[rank]);
}
