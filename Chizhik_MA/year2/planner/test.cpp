#include "planner.hpp"
#define out "output.txt"

using namespace std;

int main(void) {
	FILE *output;
	unsigned char squares[64];
	for (int i = 0; i < 64; i++) {
		squares[i] = 0;
	}

	if ((output = fopen(out, "w")) == NULL) {
		cerr << "Can't open " << out << endl;
		return -1;
	}

	//Setting black bishop to c5
	squares[7*8 + 1] = PAWN + ((char)WHITE << 3);
	squares[1*8 + 2] = PAWN + ((char)BLACK << 3);
	squares[6*8 + 5] = KNIGHT + ((char)WHITE << 3);
	squares[2*8 + 4] = BISHOP + ((char)BLACK << 3);
	squares[3] = ROOK + ((char)WHITE << 3);
	squares[3*8 + 6] = QUEEN + ((char)BLACK << 3);
	squares[7] = KING + ((char)WHITE << 3);
	squares[4*8 + 1] = KING + ((char)BLACK << 3);
	Position sample_position(squares, 3, 15);

	// White pawn
	Square wpawn_sq = Square(57);
	Pawn wpawn(sample_position.get_figure_info(wpawn_sq).colour());
	fprintf(output, "%s pawn's position is ", (wpawn.colour() ? "Black" : "White"));
	wpawn_sq.print_name(output);
	fprintf(output, "And its possible turns are:\n");
	wpawn.possible_moves(output, wpawn_sq);
	fprintf(output, "\n");

	// Black pawn
	Square bpawn_sq = Square(10);
	Pawn bpawn(sample_position.get_figure_info(bpawn_sq).colour());
	fprintf(output, "%s pawn's position is ", (bpawn.colour() ? "Black" : "White"));
	bpawn_sq.print_name(output);
	fprintf(output, "And its possible turns are:\n");
	bpawn.possible_moves(output, bpawn_sq);
	fprintf(output, "\n");

	// White knight
	Square knight_sq = Square(53);
	Knight knight(sample_position.get_figure_info(knight_sq).colour());
	fprintf(output, "%s knight's position is ", (knight.colour() ? "Black" : "White"));
	knight_sq.print_name(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	knight.possible_moves(output, knight_sq);
	fprintf(output, "\n");

	// Black bishop
	Square bishop_sq = Square(20);
	Bishop bishop(sample_position.get_figure_info(bishop_sq).colour());
	fprintf(output, "%s bishop's position is ", (bishop.colour() ? "Black" : "White"));
	bishop_sq.print_name(output);
	fprintf(output, "And its possible turns are:\n");
	bishop.possible_moves(output, bishop_sq);
	fprintf(output, "\n");

	// White rook
	Square rook_sq = Square(3);
	Rook rook(sample_position.get_figure_info(rook_sq).colour());
	fprintf(output, "%s rook's position is ", (rook.colour() ? "Black" : "White"));
	rook_sq.print_name(output);
	fprintf(output, "And its possible turns are:\n");
	rook.possible_moves(output, rook_sq);
	fprintf(output, "\n");

	// Black queen
	Square queen_sq = Square(30);
	Queen queen(sample_position.get_figure_info(queen_sq).colour());
	fprintf(output, "%s queen's position is ", (queen.colour() ? "Black" : "White"));
	queen_sq.print_name(output);
	fprintf(output, "And its possible turns are:\n");
	queen.possible_moves(output, queen_sq);
	fprintf(output, "\n");

	// White king
	Square wking_sq = Square(7);
	King wking(sample_position.get_figure_info(wking_sq).colour());
	fprintf(output, "%s king's position is ", (wking.colour() ? "Black" : "White"));
	wking_sq.print_name(output);
	fprintf(output, "And its possible turns are:\n");
	wking.possible_moves(output, wking_sq);
	fprintf(output, "\n");
	
	// Black king
	Square bking_sq = Square(33);
	King bking(sample_position.get_figure_info(bking_sq).colour());
	fprintf(output, "%s king's position is ", (bking.colour() ? "Black" : "White"));
	bking_sq.print_name(output);
	fprintf(output, "And its possible turns are:\n");
	bking.possible_moves(output, bking_sq);
	fprintf(output, "\n");

	//FEN
	char *fen = (char *)malloc(100);
	sample_position.to_FEN(fen);
	fprintf(output, "%s\n", fen);
	free(fen);

	fclose(output);
	return 0;
}
