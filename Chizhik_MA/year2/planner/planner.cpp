#include "planner.hpp"

void print_square_name(FILE *f, char file, char rank) {
	fprintf(f, "%c%c\n", files[file], ranks[rank]);
}

void Square::print_name(FILE *f) const {	
	print_square_name(f, file, rank);
}

Figure::Figure(Colour colour, FigureType type, Cost st_cost) 
	: static_cost_(st_cost), figinfo_(type, colour) {}

void Pawn::possible_moves(FILE *f, Square start_sq) const { // пока передвижение на соседнюю вертикаль считаем потенциально возможным, не обращая внимание на наличие или отсутствие там фигур
	char rk = start_sq.rank;
	char file = start_sq.file;

	char min_file = (file > 0) ? (file - 1) : 0;

	char coef = 1 - (char)colour() * 2; // если пешка белая, то 1, иначе - -1
	bool can_jump = (colour() == WHITE && rk == 1) || (colour() == BLACK && rk == 6);

	for (char k = min_file; (k <= (file + 1)) && (k < 8); k++) {
		char max_prom = (1 + (char)can_jump * (1 - fabs(k - file))); // Если k == file, max_prom[otion] зависит от того, находится ли пешка в начальной позиции;
									     // если fabs(k - file) == 1, то продвинуться в любом случае можно только на одну горизонталь
		for (char l = 1; l <= max_prom; l++) {
			print_square_name(f, k, rk + l * coef);
		}
	}
} // считается, что пешка не может находиться на поле превращения - иначе позиция некорректна

void Knight::possible_moves(FILE *f, Square start_sq) const {
	char rk = start_sq.rank;
	char file = start_sq.file;

	char min_file = (file > 2) ? (file - 2) : 0;

	for (char k = min_file; k < file + 3 && k < 8; k++) {
		if (k == file) continue;
		char rk_diff = 3 - fabs(file - k);
		
		for (char l = -1; l <= 1; l += 2) {
			print_square_name(f, k, rk + l * rk_diff);
		}
	}
}

void Bishop::possible_moves(FILE *f, Square start_sq) const {
	char rk = start_sq.rank;
	char file = start_sq.file;

	char alt_min = ((7 - rk) < file) ? (7 - rk) : file; // число клеток, которое можно пройти по диагонали наверх налево
	char min = (rk < file) ? rk : file;

	for (char k = file - min, l = rk - min; k < 8 && l < 8; k++, l++) {
		if (k == file && l == rk) continue;
		print_square_name(f, k, l);
	}

	for (char k = file - alt_min, l = rk + alt_min; k < 8 && l >= 0; k++, l--) {
		if (k == file && l == rk) continue;
		print_square_name(f, k, l);
	}
}

void Rook::possible_moves(FILE *f, Square start_sq) const {
	char rk = start_sq.rank;
	char file = start_sq.file;

	for (char k = 0; k < 8; k++) {
		if (k == file) continue;
		print_square_name(f, k, rk);
	}

	for (char k = 0; k < 8; k++) {
		if (k == rk) continue;
		print_square_name(f, file, k);
	}
}

void Queen::possible_moves(FILE *f, Square start_sq) const {
	char rk = start_sq.rank;
	char file = start_sq.file;

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

void King::possible_moves(FILE *f, Square start_sq) const {
	char rk = start_sq.rank;
	char file = start_sq.file;

	char min_rk = (rk > 0) ? (rk - 1) : 0;
	char min_file = (file > 0) ? (file - 1) : 0;

	for (char k = min_file; k < file + 2 && k < 8; k++) {
		for (char l = min_rk; l < rk + 2 && l < 8; l++) {
			if (k == file && l == rk) continue;
			print_square_name(f, k, l);
		}
	}
}

Position::Position(unsigned char *sqs, unsigned char are_kings_touched, unsigned char are_rooks_touched, Colour turn, unsigned char en_passant, unsigned short halfmove, unsigned short fullmove) 
	: turn_(turn), touched_(are_kings_touched, are_rooks_touched), en_passant_(en_passant), halfmove_clock_(halfmove), fullmove_number_(fullmove) {
	if (halfmove > 200) {
		throw PlannerException(1, "Halfmove clock is incorrect");
	}

	if (fullmove > 300) {
		throw PlannerException(2, "It seems, fullmove number is incorrect");
	}

	for (int i = 0; i < 64; i++) {
		squares_[i].figtype_ = sqs[i] % 8;
		squares_[i].colour_ = (sqs[i] & (1 << 3)) >> 3;

		if (squares_[i].figtype_ == 7) {
			throw PlannerException(3, "Incorrect figure type");
		}
	}	
}

FigureInfo Position::get_figure_info(Square square) const {
	return squares_[square.to_char()];
}

std::string Position::to_FEN() const {
	// Длина буфера должна быть не менее 90 байт, чтобы иметь возможность записать позицию, т.к. возможны позиции а-ля
	// 1nb1k1r1/r1q1n1b1/1p1p1p1p/p1p1p1p1/1P1P1P1P/P1P1P1P1/1B1N1RB1/R1Q1K1N1 w - - 18 18,
	// где описание самой доски занимает 71 байт;
	// то есть максимальная длина раздела с положением фигур - 71, с очередью хода - 1, с информацией о возможности рокировки - 4,
	// с полем, где возможно взятие на проходе - 2, с числом полуходов с последнего взятия или хода пешкой и числом ходов - по 3,
	// на пробелы-разделители - 5. Итого - 89 символов + символ конца строки
	char *buffer = (char *)malloc(90);
	int empty_sqs_counter = 0;
	int carriage_index = 0; // перед каким по счету символом установлена "каретка"

	for(int i = 7; i >= 0; i--) {
		for (int k = 0; k < 8; k++) {
			if (squares_[i + k * 8].type() == EMPTY) {
				empty_sqs_counter++;
				if (k == 7) {
					buffer[carriage_index++] = digits[empty_sqs_counter];
					empty_sqs_counter = 0;
				}
				continue;
			} else if (empty_sqs_counter > 0) {
				buffer[carriage_index++] = digits[empty_sqs_counter];
				empty_sqs_counter = 0;
			}
			const std::string *figlist = (squares_[i + k * 8].colour() == WHITE) ? &w_figures : &b_figures;
			buffer[carriage_index++] = (*figlist)[squares_[i + k * 8].figtype_];
		}
		if (i > 0) {
			buffer[carriage_index++] = '/';
		}
	}
	buffer[carriage_index++] = ' ';

	buffer[carriage_index++] = ((turn_ == WHITE) ? 'w' : 'b');	
	buffer[carriage_index++] = ' ';

	int ci_before_castlings = carriage_index;
	if ((touched_.rw_rook || touched_.w_king) == 0) {
		buffer[carriage_index++] = 'K';
	}
	if ((touched_.lw_rook || touched_.w_king) == 0) {
		buffer[carriage_index++] = 'Q';
	}
	if ((touched_.rb_rook || touched_.b_king) == 0) {
		buffer[carriage_index++] = 'k';
	}
	if ((touched_.lb_rook || touched_.b_king) == 0) {
		buffer[carriage_index++] = 'q';
	}
	if (carriage_index - ci_before_castlings == 0) {
		buffer[carriage_index++] = '-';
	}
	buffer[carriage_index++] = ' ';

	if (en_passant_.to_char() == 0) {
		buffer[carriage_index++] = '-';
	} else {
		buffer[carriage_index++] = en_passant_.file; 
		buffer[carriage_index++] = en_passant_.rank;
	}
	buffer[carriage_index++] = ' ';

	unsigned short halfmoves = halfmove_clock_;
	unsigned char digits_amount_in_halfmoves = 1;
	while ((halfmoves /= 10) > 0) {
		digits_amount_in_halfmoves++;
	}

	halfmoves = halfmove_clock_;
	for (int i = 1; i <= digits_amount_in_halfmoves; i++) {
		int power = pow(10, digits_amount_in_halfmoves - i);
		int next_digit = (halfmoves / power);
		halfmoves %= power;
		buffer[carriage_index++] = digits[next_digit];
	}
	buffer[carriage_index++] = ' ';

	unsigned short fullmoves = fullmove_number_;
	unsigned char digits_amount_in_fullmoves = 1;
	while ((fullmoves /= 10) > 0) {
		digits_amount_in_fullmoves++;
	}

	fullmoves = fullmove_number_;
	for (int i = 1; i <= digits_amount_in_fullmoves; i++) {
		int power = pow(10, digits_amount_in_fullmoves - i);
		int next_digit = (fullmoves / power);
		fullmoves %= power;
		buffer[carriage_index++] = digits[next_digit];
	}

	buffer[carriage_index] = 0;

	std::string FEN(buffer);
	free(buffer);
	return FEN;
}

Position::Position(const std::string& FEN): touched_(3, 15) {
	int carriage_index = 0;
	int empty_squares_left = 0;

	for (int rank = 7; rank >= 0; rank--) {
		int file = 0;
		while (file < 8) {
			FigureInfo *current_square = squares_ + (file * 8 + rank);
			int curr_symbol_index = b_figures.find(tolower(FEN[carriage_index]), 1);
			if (curr_symbol_index != std::string::npos) {
				current_square->figtype_ = curr_symbol_index;
				current_square->colour_ = (char)((FEN[carriage_index] == tolower(FEN[carriage_index])) ? BLACK : WHITE);
				file++;
			} else if (digits.find(FEN[carriage_index], 1) != std::string::npos) {
				int curr_value = digits.find(FEN[carriage_index], 1);
				if (curr_value <= 8 - file) {
					empty_squares_left = curr_value;
					do {
						current_square->figtype_ = 0;
						current_square->colour_ = 0;

						file++;
						current_square = squares_ + (file * 8 + rank);
					} while (--empty_squares_left > 0);
				} else {
					throw FENException(1, "Incorrect number of squares");
				}
			} else {
				throw FENException(2, "Unexpected symbol");
			}
			carriage_index++;
		}

		if (rank > 0 && FEN[carriage_index] != '/') {
			throw FENException(3, "\'/\' as a separator of ranks' descriptions was expected");
		} else if (rank == 0 && FEN[carriage_index] != ' ') {
			throw FENException(4, "\'Spacebar\' was expected");
		}
		carriage_index++;
	}

	switch (FEN[carriage_index++]) {
		case 'w':
			turn_ = WHITE;
			break;
		case 'b':
			turn_ = BLACK;
			break;
		default:
			throw FENException(2, "Unexpected symbol");
	}

	if (FEN[carriage_index++] != ' ') {
		throw FENException(4, "\'Spacebar\' was expected");
	}

	if (FEN[carriage_index] == '-') {
		touched_.w_king = touched_.b_king = 1;
		carriage_index++;
	} else {
		if (FEN[carriage_index] == 'K') {
			touched_.w_king = touched_.rw_rook = 0;
			carriage_index++;
		}

		if (FEN[carriage_index] == 'Q') {
			touched_.w_king = touched_.lw_rook = 0;
			carriage_index++;
		}

		if (FEN[carriage_index] == 'k') {
			touched_.b_king = touched_.rb_rook = 0;
			carriage_index++;
		}

		if (FEN[carriage_index] == 'q') {
			touched_.b_king = touched_.lb_rook = 0;
			carriage_index++;
		}
	}

	if (FEN[carriage_index++] != ' ') {
		throw FENException(4, "\'Spacebar\' was expected");
	}

	if (ranks.find(FEN[carriage_index]) != std::string::npos && files.find(FEN[carriage_index + 1]) != std::string::npos && FEN[carriage_index + 2] == ' ') {
		en_passant_.rank = ranks.find(FEN[carriage_index]);
		en_passant_.file = files.find(FEN[carriage_index + 1]);
		carriage_index += 3;
	} else if (FEN[carriage_index] == '-' && FEN[carriage_index + 1] == ' ') {
		en_passant_.rank = en_passant_.file = 0;
		carriage_index += 2;
	} else {
		throw FENException(2, "Unexpected symbol");
	}

	if (sscanf(FEN.c_str() + carriage_index, "%hhu", &halfmove_clock_) != 1 || halfmove_clock_ > 200) {
		throw FENException(5, "Invalid FEN");
	}

	int length = 1;
	while (halfmove_clock_ >= pow(10, length)) {
		length++;
	}
	carriage_index += length;

	if (FEN[carriage_index++] != ' ') {
		throw FENException(4, "\'Spacebar\' was expected");
	}

	if (sscanf(FEN.c_str() + carriage_index, "%hu", &fullmove_number_) != 1 || fullmove_number_ > 999) {
		std::cout << "halfmove_clock_: " << halfmove_clock_ << std::endl;
		throw FENException(5, "Invalid FEN");
	}
}

std::ostream& operator<<(std::ostream& os, const PlannerException& e) {
	os << "Error " << e.code() << ": " << e.message() << std::endl;
	return os;
}
