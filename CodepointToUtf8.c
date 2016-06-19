#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <assert.h>
#include "common.h"

int verbose = 0;


char *output;
size_t size;
size_t idx;

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
  if(verbose) {
    printByte(c, 0); putchar(' ');
  }
}

void display() {
  makeRoom();
  output[idx] = 0;
  printf("%s\n", output);
}


void encode(int u) {
  if (verbose) {
    printf("%d: ", u);
    printInt(u); putchar('\t');
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

  if(verbose) putchar('\n');

}

int main(int argc, char **argv) {
  size = 1024;
  output = malloc(size);
  idx = 0;
  if (argc >1 ) verbose = !strcmp(argv[1], "-v");
  int u;
  if (argc == 3) {
    if(1 == sscanf(argv[2], "%04x", &u)) {
      encode(u);
    } else {
      printf("wrong format\n");
    }
  } else {
    while (1 == scanf("%04x", &u)) 
      encode(u);
  }
  display();
  return 0;
}
