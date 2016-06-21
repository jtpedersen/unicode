#include  <stdio.h>
#include  <string.h>
#include  <stdlib.h>
#include  <assert.h>
#include  <ctype.h>

#include "common.h"

int verbose = 0; 
int base         = 36;
int tmin         = 1;
int tmax         = 26;
int skew         = 38;
int damp         = 700;
int initial_bias = 72;
int initial_n    = 128; // = 0x80;

//      numpoints is the total number of code points encoded/decoded so
//      far (including the one corresponding to this delta itself, and
//      including the basic code points).

int adapt(int delta, int numpoints, int firsttime) {
  if (firsttime)
    delta = delta / damp;
  else 
    delta = delta / 2;
  delta = delta + (delta / numpoints);
  int k = 0;
  int t = ((base - tmin) * tmax)/2;
  while (delta > t) {
    delta = delta / (base - tmin);
    k = k + base;
  }
  int bias = k + (((base - tmin + 1) * delta) / (delta + skew));
  if (verbose)
    printf("Bias becomes: %d\n", bias);
  return bias;
}

int digitValue(char c) {
  if (isalpha(c)) {
    return tolower(c) - 'a';
  } else if (isdigit(c)) {
    return 26 + c - '0';
  }
  assert(0);
  return 0;
}

int thresshold(int k, int bias) {
  return (k <= (bias + tmin)) ?  tmin : ( k >= (bias + tmax)) ? tmax : k - bias;
}

//https://en.wikipedia.org/wiki/Numeral_system#Generalized_variable-length_integers
//a (0), ba (1), ca (2), .., 9a (35), bb (36), cb (37), .., 9b (70), bca (71), .., 99a (1260), bcb (1261), etc.
int getNumber(char** p, int bias) {
  assert(p);
  int w = 1;
  int i = 0;
  for(int k = base; ; k+=base) {
    int digit = digitValue(**p); // double star programmer
    i = i + digit * w; // fail on overflow?
    int t = thresshold(k, bias);
    if (verbose) 
      printf("%c digit=%d t=%d k=%d bias=%d i=%d\n", **p, digit, t, k, bias, i);
    (*p)++;

    if (digit < t) 
      return i;
    w = w * (base - t); // fail on overflow
  }
  return i;
}

int main(int argc, char **argv) {
  int idx = 1;
  if (argc  < 2 ) return EXIT_FAILURE;
  if (!strcmp(argv[1], "-v")) {
    verbose=1;
    idx++;
  }

  char *cptr = argv[idx];
  int size = strlen(cptr)+2;
  char *res = calloc(1, size);

  initOutput(verbose);
  int n = initial_n;
  int bias = initial_bias;
  int i = 0;
  int cnt = 1;

  while (*cptr) {
    int oldi = i;
    i = getNumber(&cptr, bias);
    printf("%d\n", i);
    int delta = i - oldi;
    if (verbose)
      printf("%s (delta=%d)\n", res, delta);
    bias = adapt(i - oldi, cnt, !oldi);
    n = n + i / (cnt); // fail on overflow
    i = i % (cnt);
    printf("<%d,%d>\n", n, i);
    assert(n > 0xFE);
    encodeUtf8(n);
    i++;
  }
  display();
  idx++;
  if (argc > idx) {
    return strcmp(res, argv[idx]);
  }  else {
    return EXIT_SUCCESS;
  }
}
