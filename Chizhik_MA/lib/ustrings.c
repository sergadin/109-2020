#include <stdio.h>
#include <stdlib.h>

#include "../lib/ustrings.h"

#define N 1024

int string_length(const char *string) {
	int length = 0;
	while (string[length] != '\0') {
		length++;
	}
	return length;
}

char *substr(const char *haystack, const char *needle) {
	int len, sub_len;
	len = string_length(haystack);
	sub_len = string_length(needle);

	for (int i = 0; i < len - sub_len + 1; i++) {
		unsigned int flag = 1;
		for (int j = 0; j < sub_len; j++) {
			if (haystack[i + j] != needle[j]) {
				flag = 0;
				break;
			}
		}
		if (flag == 1) {
			return (char *)haystack + i;
		}
	}

	return NULL;
}

char *string_copy(char *dest, const char *src) {
	int len = string_length(src);
	for (int i = 0; i < len + 1; i++) {
		dest[i] = src[i];
	}
	return dest;
}

int string_cmp(const char *s1, const char *s2) {
	int i = 0;
	int len = string_length(s1);
	while((s1[i] == s2[i]) && (i < len)) {
		i++;
	}

	return s1[i] - s2[i];
}

char *read_string(FILE *f) {
	char buf[N];
	char *temp, *result = NULL;
	int t_len, curr_len = 1;

	buf[0] = '\0';
	temp = buf;

	do {
		fgets(buf, N, f);
		t_len = string_length(temp);

		result = (char *)realloc(result, curr_len + t_len);
		string_copy(&result[curr_len - 1], temp);
		curr_len += t_len;

		if ((curr_len > 1) && (result[curr_len - 2] == '\n')) {
			result[curr_len - 2] = '\0';
			result = (char *)realloc(result, curr_len - 1);
			break;
		}
	} while (t_len > 0);

	if (curr_len == 1) {
		free(result);
		return NULL;
	}
	return result;
}
