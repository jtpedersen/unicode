#include "common.h"
#include  <stdlib.h>
#include  <stdio.h>
#include  <assert.h>

static char *output;
static size_t size;
static size_t idx;
static int verbose;

void makeRoom() {
  if (idx == size) {
    size >>=1;
    char *old = output;
    output = realloc(output, size);
    free(old);
  }
}

void write(char c) {
  assert(c!=0);
  makeRoom();
  output[idx++] = c;
}

void display() {
  makeRoom();
  output[idx] = 0;
  printf("%s", output);
}

void initOutput(int level) {
  size = 1024;
  output = malloc(size);
  idx = 0;
  verbose = level;
}

void printByte(int c, int space) {
  for (int i = 7; i >= 0; i--) {
    putchar( ((c>>i ) & 1) ? '1' : '0');
    if (space)
      if (i == 4) putchar(' ');
  }
}

void printInt(int c) {
  printByte(c >> 24, 1); putchar(' ');
  printByte(c >> 16, 1); putchar(' ');
  printByte(c >> 8, 1); putchar(' ');
  printByte(c >> 0, 1); putchar(' ');
}
