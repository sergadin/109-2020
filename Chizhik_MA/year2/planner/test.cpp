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
	squares[2*8 + 4] = BISHOP + (1 << 3);
	Position bb_pos(squares);
	Figure bishop = Figure(20, bb_pos.get_figure_info(20));
	fprintf(stdout, "Bishop's position is %d\n", bishop.position()); 
	bishop.possible_turns(output);

	fclose(output);
	return 0;
}
