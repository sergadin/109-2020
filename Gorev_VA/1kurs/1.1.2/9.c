#include "lib.h"
#include <time.h>

list* solve(list* head);

list* solve(list* head) {
	list *curr, *left, *right;
	int cmp_left, cmp_right;
	if (!head)
		return NULL;
	if (!(head->next))
		return head;

	cmp_left = strcmp(head->next->string, head->string);

	for (left = head, curr = head->next, right = head->next->next; right; ) {
		cmp_right = strcmp(curr->string, right->string);
		if (cmp_left >= 0 && cmp_right >= 0) {
			free(curr->string);
			free(curr);
			left->next = right;

			if (!(right->next))
				break;
			else
				curr = right, right = right->next;
		}
		else
			left = curr, curr = right, right = right->next;
		cmp_left = -cmp_right;
	}

	return head;
}

int main(int argc, char* argv[]) {
	int res;
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

    printf("Old list:\n");
    print_list(head, MAX_PRINT);
    timer = clock();
    head = solve(head);
    timer = (clock() - timer) / CLOCKS_PER_SEC;
    printf("New list:\n");
    print_list(head, MAX_PRINT);
    printf("Time = %.2lf\n", timer);

    delete_list(head);
	return 0;
}
