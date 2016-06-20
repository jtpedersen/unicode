#ifndef COMMON_H_
#define COMMON_H_
#include <stdio.h>

void printByte(int c, int space);
void printInt(int c);

/// Output buffer
void initOutput(int verbosity);
void write(char c);
void display();


//reading utf8
int blocks(int c);
int calcMask(const int bytes);
int nextCodepoint(FILE *f);

/// writing
void encodeUtf8(int u);

#endif /* !COMMON_H_ */
