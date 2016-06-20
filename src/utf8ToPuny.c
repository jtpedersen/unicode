#include  <stdio.h>
#include  <string.h>
#include  <assert.h>

#include "common.h"

struct unicode {
  int codepoint;
  int index;
};

#define SIZE 2048
struct unicode extra[SIZE];
int cnt = 0;

int main(int argc, char **argv) {
  int verbose = 0;
  if (argc >1 ) verbose = !strcmp(argv[1], "-v");
  initOutput(verbose);
  int u;
  int idx = 0;
  while(EOF!=(u = nextCodepoint(stdin))) {
    if (u < 0xFE) {
      encodeUtf8(u);
    } else {
      struct unicode tmp = {u, idx};
      extra[cnt++] = tmp;
    }
    idx++;
  }
  if (cnt) {
    write('-');
  }
  
  display();
  return 0;
}
