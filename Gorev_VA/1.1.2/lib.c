#include "lib.h"

int read_list(const char* fname, list** head) {
	list *curr, *tail;
	char buf[LEN];
	FILE* fp = fopen(fname, "r");

	if (!fp)
		return OPEN_ERROR;

	if (!fgets(buf, LEN, fp)) {
		*head = NULL;
		fclose(fp);
		return SUCCESS;
	}

	curr = (list*)malloc(sizeof(list));
	if (!curr) {
		fclose(fp);
		return MALLOC_ERROR;
	}

	if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';

	curr->string = (char*)malloc(strlen(buf) + 1);
	if (!curr->string) {
		free(curr);
		fclose(fp);
		return MALLOC_ERROR;
	}

	curr->next = NULL;
	strcpy(curr->string, buf);
	*head = curr, tail = curr;

	while (fgets(buf, LEN, fp)) {
		curr = (list*)malloc(sizeof(list));
		if (!curr) {
			fclose(fp);
			delete_list(*head);
			return MALLOC_ERROR;
		}

		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = '\0';

		curr->string = (char*)malloc(strlen(buf) + 1);
		if (!curr->string) {
			fclose(fp);
			free(curr);
			delete_list(*head);
			return MALLOC_ERROR;
		}

		curr->next = NULL;
		strcpy(curr->string, buf);
		tail->next = curr;
		tail = curr;
	}

	fclose(fp);
	return SUCCESS;
}

void delete_list(list* head) {
	list *curr, *next_;
	for (curr = head; curr; curr = next_) {
		next_ = curr->next;
		free(curr->string);
		free(curr);
	}
}

void print_list(list* head, int n) {
	list* curr;
	int i = 0;
	for (curr = head; curr && i < n; curr = curr->next, ++i)
		printf("%s\n", curr->string);
}
