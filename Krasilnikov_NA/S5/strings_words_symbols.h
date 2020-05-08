typedef struct symbols_count
{
	char symbol;
	int count;
};

typedef struct result_of_counting
{
	int ec;    // ec = Error_Code
	int maxls; // maxls = MAXimum_Length_of_String
	int minls; // minls = MINimum_Length_of_String
	int maxlw; // maxlw = MAXimum_Length_of_Word
	int minlw; // minlw = MINimum_Length_of_Word
	int strc;  // strc = STRings_Count
	int wc;    // wc = Words_Count
	int symc;  // symc = SYMbols_Count
	struct symbols_count *symboltable;
};

void sws(FILE *fin, FILE *fout); //sws = strings_words_symbols
struct result_of_counting count_sws(FILE *fin);
int decimal_places(int number);
