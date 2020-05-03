#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  char *kek, *lol;
  kek = (char*)malloc(6);
  lol = (char*)malloc(3);
  kek[0] = 'k';
  kek[1] = 'i';
  kek[2] = 'k';
  kek[3] = 'l';
  kek[4] = '5';
  kek[5] = '\0';
  strcpy(lol, kek);
  printf("%s\n", lol);
  printf("%d", strlen(lol));
  return 0;
}
