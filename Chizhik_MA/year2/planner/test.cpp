#include "planner.hpp"
#define out "output.txt"

using namespace std;

int main(void) {
	FILE *output;
	char squares[64];
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
	squares[4*8 + 1] = KING + ((char)BLACK << 3);
	Position sample_position(squares);

	// White pawn
	Pawn wpawn(57, (Colour)(sample_position.get_figure_info(57).colour));
	fprintf(output, "%s pawn's position is ", (wpawn.colour() ? "Black" : "White"));
	wpawn.print_fig_square_name(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	wpawn.possible_moves(output);
	fprintf(output, "\n");

	// Black pawn
	Pawn bpawn(10, (Colour)(sample_position.get_figure_info(10).colour));
	fprintf(output, "%s pawn's position is ", (bpawn.colour() ? "Black" : "White"));
	bpawn.print_fig_square_name(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	bpawn.possible_moves(output);
	fprintf(output, "\n");

	// White knight
	Knight knight(53, (Colour)(sample_position.get_figure_info(53).colour));
	fprintf(output, "%s knight's position is ", (knight.colour() ? "Black" : "White"));
	knight.print_fig_square_name(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	knight.possible_moves(output);
	fprintf(output, "\n");

	// Black bishop
	Bishop bishop(20, (Colour)(sample_position.get_figure_info(20).colour));
	fprintf(output, "%s bishop's position is ", (bishop.colour() ? "Black" : "White"));
	bishop.print_fig_square_name(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	bishop.possible_moves(output);
	fprintf(output, "\n");

	// White rook
	Rook rook(3, (Colour)(sample_position.get_figure_info(3).colour));
	fprintf(output, "%s rook's position is ", (rook.colour() ? "Black" : "White"));
	rook.print_fig_square_name(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	rook.possible_moves(output);
	fprintf(output, "\n");

	// Black queen
	Queen queen(30, (Colour)(sample_position.get_figure_info(30).colour));
	fprintf(output, "%s queen's position is ", (queen.colour() ? "Black" : "White"));
	queen.print_fig_square_name(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	queen.possible_moves(output);
	fprintf(output, "\n");

	// Black king
	King king(33, (Colour)(sample_position.get_figure_info(33).colour));
	fprintf(output, "%s king's position is ", (king.colour() ? "Black" : "White"));
	king.print_fig_square_name(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	king.possible_moves(output);
	fprintf(output, "\n");

	fclose(output);
	return 0;
}
