#ifndef COMMON_H_
#define COMMON_H_

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

#endif /* !COMMON_H_ */
