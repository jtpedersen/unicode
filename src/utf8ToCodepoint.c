#include  <stdio.h>
#include  <string.h>
#include  <assert.h>

#include "common.h"

int main(int argc, char **argv) {
  int verbose = 0;
  if (argc == 2) verbose = !strcmp(argv[1], "-v");
  int c;
  int chars = 0;
  while (EOF != (c = getchar())) {
    char res[] = {c,0,0,0};
    int bytes = blocks(c);
    if (verbose) {
      printByte(c, 0); printf(" requires %d\n", bytes);
    }
    int mask = calcMask(bytes);
    c &= mask;
    for(int i = 1; i < bytes; i++) {
      int tmp = getchar();
      res[i+1] = tmp;
      if(verbose) printByte(tmp,0);
      c = (c << 6) | (tmp & 0x3F);
    }

    if (verbose) {
      printInt(c); putchar(' ');
      printf("\t%04x\t%s\n", c, res);
    } else {
      printf("%04x ", c);
      if ((++chars)% 16 == 0) 
	putchar('\n');
    }
    assert(c);
  }

  return 0;
}
