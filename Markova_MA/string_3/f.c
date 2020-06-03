static int fn(const char *fpath, const struct stat *sb, int flag) {
    if(flag == FTW_F) {
        n++;
        s = (char **) realloc (s_value, n * sizeof(char *));
        size = (intmax_t *) realloc (size_value, n * sizeof(intmax_t));
        s[n - 1] = malloc((strlen(fpath) + 1) * sizeof(char));
        strcpy(s[n - 1], fpath);
        size[n - 1] = (intmax_t) sb->st_size;
        s_value = s;
        size_value = size;
        if(strlen(s[n - 1]) > max_len)
            max_len = strlen(s[n - 1]);
    }
    return 0;
}

void print(int k, int max) {
    for(int i = 0; i < max - k + 4; i++)
        printf(" ");
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        if(ftw(".", fn, 20) == -1)  {
            printf("Не удалось обойти каталог\n");
            return -1;
        }
    }
    else {
        if(ftw(argv[1], fn, 20) == -1)  {
            printf("Не удалось обойти каталог\n");
            return -1;
        }
    }
    if(max_len > Max_len) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < strlen(s[i]); j++) {
                printf("%c", s[i][j]);
                if (j == Max_len - 1)
                    printf("     %jd", size[i]);
                if((j % Max_len == Max_len - 1) || (j == strlen(s[i]) - 1))
                    printf("\n");
            }
        }
    }
    else {
        for(int i = 0; i < n; i++) {
            printf("%s", s[i]);
            print(strlen(s[i]), max_len);
            printf("%jd\n", size[i]);
        }
    }
    for(int i = 0; i < n; i++) {
        free(s[i]);
    }
    free(s);
    free(size);
    return 0;
}