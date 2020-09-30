#include "lib.h"
#include <time.h>

int max_nodes(list* head) {
	list* curr;
	char* max_string;
	int cnt = 0, cmp_res;

	if (!head)
		return 0;
	max_string = head->string;

	for (curr = head; curr; curr = curr->next) {
		cmp_res = strcmp(curr->string, max_string);
		if (cmp_res > 0)
			max_string = curr->string, cnt = 1;
		else if (cmp_res == 0)
			++cnt;
	}
	return cnt;
}

int main(int argc, char* argv[]) {
	int res, ans;
	double timer;
	char* fname;
	list* head;

	if (argc != 2) {
		printf("Usage: a.out file.txt\n");
		return -1;
	}

	fname = argv[1];
	res = read_list(fname, &head);
	if (res != SUCCESS) {
        switch (res) {
	        case OPEN_ERROR:
	            printf("Cannot open the file\n");
	            break;
	        case MALLOC_ERROR:
	            printf("Cannot allocate memory for the list\n");
	            break;
	        default:
	            printf("Unknown error with code %d\n", res);
        }
        return -2;
    }

    print_list(head, MAX_PRINT);
    timer = clock();
    ans = max_nodes(head);
    timer = (clock() - timer) / CLOCKS_PER_SEC;
    printf("Answer = %d\nTime = %.2lf\n", ans, timer);

    delete_list(head);
	return 0;
}
