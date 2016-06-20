#include  <stdio.h>
#include  <string.h>
#include  <assert.h>

#include "common.h"

int main(int argc, char **argv) {
  int verbose = 0;
  if (argc >1 ) verbose = !strcmp(argv[1], "-v");
  initOutput(verbose);
  int u;
  while(EOF!=(u=getchar())) {
    write(u);
  }
  display();
  return 0;
}
