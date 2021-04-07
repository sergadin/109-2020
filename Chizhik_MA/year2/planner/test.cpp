#include "planner.hpp"
#define out "output.txt"

using namespace std;

int main(void) {
	FILE *output;
	unsigned char squares[64];

	const std::string FEN_1 = "1nb1k1r1/r1q1n1b1/1p1p1p1p/p1p1p1p1/1P1P1P1P/P1P1P1P1/1B1N1RB1/R1Q1K1N1 w - - 18 18";
	const std::string FEN_2 = "1r1q1rk1/pb2bppp/2p1pn2/8/3P1Q2/P3PN2/2B2PPP/R1B2RK1 b - - 4 16";
	const std::string FEN_3 = "r2qk2r/1p1nb1p1/p2ppn1p/4p3/4P3/2N1BN2/PPP2PPP/1R1QK2R w Kkq - 2 12";
	const std::string Carlsen_FEN_1 = "rnbqk2r/pp2p1bp/2p2Ppn/3p4/3P4/2PB1N2/PP3PPP/RNBQK2R b KQkq - 0 7";
	const std::string Carlsen_FEN_2 = "r1bq1rk1/p2n1pbp/2pp1npB/1p2p3/3PP3/2NB1P2/PPPQN1PP/R3K2R w KQ - 4 10";

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

	//Position to FEN
	char *fen = (char *)malloc(100);
	sample_position.to_FEN(fen);
	fprintf(output, "This position in FEN: %s\n", fen);

	//FEN to Position and back
	fprintf(output, "FEN_1:\n%s\n", FEN_1.c_str());
	Position from_fen_1(FEN_1);
	from_fen_1.to_FEN(fen);
	fprintf(output, "After chain FEN_1 -> Position -> FEN:\n%s\n", fen);

	fprintf(output, "FEN_2:\n%s\n", FEN_2.c_str());
	Position from_fen_2(FEN_2);
	from_fen_2.to_FEN(fen);
	fprintf(output, "After chain FEN_2 -> Position -> FEN:\n%s\n", fen);
	
	fprintf(output, "FEN_3:\n%s\n", FEN_3.c_str());
	Position from_fen_3(FEN_3);
	from_fen_3.to_FEN(fen);
	fprintf(output, "After chain FEN_3 -> Position -> FEN:\n%s\n", fen);
	
	fprintf(output, "Carlsen_FEN_1:\n%s\n", Carlsen_FEN_1.c_str());
	Position from_carlsen_fen_1(Carlsen_FEN_1);
	from_carlsen_fen_1.to_FEN(fen);
	fprintf(output, "After chain Carlsen_FEN_1 -> Position -> FEN:\n%s\n", fen);
	
	fprintf(output, "Carlsen_FEN_2:\n%s\n", Carlsen_FEN_2.c_str());
	Position from_carlsen_fen_2(Carlsen_FEN_2);
	from_carlsen_fen_2.to_FEN(fen);
	fprintf(output, "After chain Carlsen_FEN_2 -> Position -> FEN:\n%s\n", fen);

	free(fen);
	fclose(output);
	return 0;
}
