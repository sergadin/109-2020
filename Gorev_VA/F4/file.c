#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>

int func(const char *fpath, const struct stat *sb, int flag);
int func(const char *fpath, const struct stat *sb, int flag)
{
	printf("%s\n", fpath);
	return 0;
}

int main(void)
{
	ftw("dir1", func, 20);
	return 0;
}
