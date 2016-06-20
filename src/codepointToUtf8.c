#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <assert.h>
#include "common.h"

int verbose = 0;

int main(int argc, char **argv) {
  if (argc >1 ) verbose = !strcmp(argv[1], "-v");
  initOutput(verbose);

  int u;
  if (argc == 3) {
    if(1 == sscanf(argv[2], "%04x", &u)) {
      encodeUtf8(u);
    } else {
      printf("wrong format\n");
    }
  } else {
    while (1 == scanf("%04x", &u)) 
      encodeUtf8(u);
  }
  display();
  return 0;
}
