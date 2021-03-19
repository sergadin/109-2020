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
	squares[7*8 + 1] = PAWN;
	squares[1*8 + 2] = PAWN + (1 << 3);
	squares[6*8 + 5] = KNIGHT;
	squares[2*8 + 4] = BISHOP + (1 << 3);
	squares[3] = ROOK;
	squares[3*8 + 6] = QUEEN + (1 << 3);
	squares[4*8 + 1] = KING + (1 << 3);
	Position sample_position(squares);

	// White pawn
	Pawn wpawn(57, sample_position.get_figure_info(57));
	fprintf(output, "%s pawn's position is ", (wpawn.colour() ? "Black" : "White"));
	wpawn.print_position(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	wpawn.possible_turns(output);
	fprintf(output, "\n");

	// Black pawn
	Pawn bpawn(10, sample_position.get_figure_info(10));
	fprintf(output, "%s pawn's position is ", (bpawn.colour() ? "Black" : "White"));
	bpawn.print_position(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	bpawn.possible_turns(output);
	fprintf(output, "\n");

	// White knight
	Knight knight(53, sample_position.get_figure_info(53));
	fprintf(output, "%s knight's position is ", (knight.colour() ? "Black" : "White"));
	knight.print_position(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	knight.possible_turns(output);
	fprintf(output, "\n");

	// Black bishop
	Bishop bishop(20, sample_position.get_figure_info(20));
	fprintf(output, "%s bishop's position is ", (bishop.colour() ? "Black" : "White"));
	bishop.print_position(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	bishop.possible_turns(output);
	fprintf(output, "\n");

	// White rook
	Rook rook(3, sample_position.get_figure_info(3));
	fprintf(output, "%s rook's position is ", (rook.colour() ? "Black" : "White"));
	rook.print_position(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	rook.possible_turns(output);
	fprintf(output, "\n");

	// Black queen
	Queen queen(30, sample_position.get_figure_info(30));
	fprintf(output, "%s queen's position is ", (queen.colour() ? "Black" : "White"));
	queen.print_position(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	queen.possible_turns(output);
	fprintf(output, "\n");

	// Black king
	King king(33, sample_position.get_figure_info(33));
	fprintf(output, "%s king's position is ", (king.colour() ? "Black" : "White"));
	king.print_position(output);
	fprintf(output, "\n");
	fprintf(output, "And its possible turns are:\n");
	king.possible_turns(output);
	fprintf(output, "\n");

	fclose(output);
	return 0;
}
