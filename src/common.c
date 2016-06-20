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
    fprintf(stderr, "%c",( ((c>>i ) & 1) ? '1' : '0'));
    if (space)
      if (i == 4) fprintf(stderr, " ");
  }
}

void printInt(int c) {
  printByte(c >> 24, 1); fprintf(stderr, " ");
  printByte(c >> 16, 1); fprintf(stderr, " ");
  printByte(c >> 8, 1); fprintf(stderr, " ");
  printByte(c >> 0, 1); fprintf(stderr, " ");
}

int blocks(int c) {
  int cnt = 0;
  int pos = 7;
  while( (c>>(pos--)) & 1) cnt++;
  return cnt ? cnt : 1;
}

int calcMask(const int bytes) {
  if (bytes == 1) return 0xFF;
  if (bytes == 2) return 0x1F;
  if (bytes == 3) return 0x0F;
  if (bytes == 4) return 0x07;
  assert(bytes == 1);
  return 0;
}

int nextCodepoint(FILE *f) {
  int c = getc(f);
  if (EOF == c) return EOF;
  int bytes = blocks(c);
  int mask = calcMask(bytes);
  c &= mask;
  for(int i = 1; i < bytes; i++) {
    int tmp = getc(f);
    c = (c << 6) | (tmp & 0x3F);
  }
  return c;
}

void encodeUtf8(int u) {
  if (verbose) {
    fprintf(stderr, "%d: ", u);
    printInt(u);
    fprintf(stderr, "\t");
  }
  int msb = 32 - __builtin_clz(u);
  if (msb < 8) {
    write(u);
  }
  else if (u <0x0800) {
    write(192 | (u>>6));
    write(128 | (u&63) );
  }
  else  {
    write(224 | ( (u>>12)) );
    write(128 | ( 63 & (u>>6)) );
    write(128 | (u&63) );
  }
  if(verbose) fprintf(stderr, "\n");
}

