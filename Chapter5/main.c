#include <stdio.h>

char getch(void);
void getchTest(void);
char getfloat(float *pf);
void getfloatTest(void);
char getint(int *pn);
void getintTest(void);
int isDigit(char c);
void isDigitTest(void);
int isDigitOrDot(char c);
void isDigitOrDotTest(void);
int isWhiteSpace(char c);
void isWhiteSpaceTest(void);
void ungetch(char c);
void ungetchTest(void);

const int BUF_SIZE = 100;
char BUF[BUF_SIZE];
int BUF_INDEX = -1;

int main(int argc, char** argv)
{
  printf("\n");
  // getchTest();
  // getfloatTest();
  getintTest();
  // getint();
  // isDigitTest();
  // isDigitOrDotTest();
  // isWhiteSpaceTest();
  // ungetchTest();

  return 0;
}

char getch(void)
{
  if (BUF_INDEX >= 0)
    return BUF[BUF_INDEX--];

  return getchar();
}

void getchTest(void)
{
  BUF[0] = 'u';
  BUF[1] = 'y';
  BUF[2] = 'x';
  BUF[3] = '?';
  BUF_INDEX = 2;

  printf("%c%c%c! %c", getch(), getch(), getch(), getch());
}

char getfloat(float *pf)
{
  int n;

  int *pn = &n;

  char c = getint(pn);

  float sign = c == '-' ? -1.0 : 1.0;

  *pf = 1.0 * *pn;

  c = getch();

  if (c != '.')
  {
    ungetch(c);
    return c;
  }

  c = getch();

  if (!isDigit(c))
  {
    ungetch(c);
    ungetch('.');
    return '.';
  }

  int d = 1;
  *pf *= sign; // make it positive

  do
  {
    d *= 10;
    *pf += 1.0 * (c - '0') / d;
    c = getch();
  } while (isDigit(c));

  *pf *= sign; // apply sign

  if (c == EOF)
    return EOF;

  ungetch(c);
  return c;
}

void getfloatTest(void)
{
  char c;

  // char input[] = " 05 04+\t03-\t02\t 01- ";
  // char s[45] = "=-4ufaosdihf lasdhf lasdhfk ajsdhf alsdjhfas\n";
  // for some reason the length of 200 works fine, but 100 or 300 don't
  char input[] = " 30.- 09.8\n\t some NaN 0.76\t 05 103.+\n52.-\t102.\t 51.0+ 101.0- 5.0";

  int i = 0;

  while ((c = input[i++]) != '\0')
    ungetch(c);

  float f;
  float *pf = &f;

  while ((c = getfloat(pf)) != EOF)
    if (c)
      printf("%f\t(%c)\n", *pf, c);
}

char getint(int *pn)
{
  char c, res;
  int sign;

  while (isWhiteSpace(c = getch()))
    ;
  
  if (c != '+' && c != '-' && !isDigitOrDot(c) && c != EOF)
    return 0;

  sign = c == '-' ? -1 : 1;
  
  if (c == '+' || c == '-')
    c = getch();

  if (isDigitOrDot(c))
    res = sign == 1 ? '+' : '-';
  else
    res = 0;

  for (*pn = 0; isDigit(c); c = getch())
    *pn = *pn * 10 + c - '0';

  *pn *= sign;

  if (c == EOF)
    return EOF;

  ungetch(c);
  return res;
}

void getintTest(void)
{
  char c;

  // char input[] = " 05 04+\t03-\t02\t 01- ";
  // char s[45] = "=-4ufaosdihf lasdhf lasdhfk ajsdhf alsdjhfas\n";
  // for some reason the length of 200 works fine, but 100 or 300 don't
  char input[] = " 098\n\t some NaN 076\t 05 04+\n03-\t02\t 01- 0 5 - 4 + 3 0- 2 0+ 1";

  int i = 0;

  while ((c = input[i++]) != '\0')
    ungetch(c);

  int n;
  int *pn = &n;

  while ((c = getint(pn)) != EOF)
    if (c)
      printf("`%c`, %d\n", c, *pn);
}

int isDigit(char c)
{
  return (c >= '0' && c <= '9') ? 1 : 0;
}

void isDigitTest(void)
{
  char c = ' ';
  printf("isDigit('%c') is %s\n", c, isDigit(c) ? "YES" : "NO");

  c = '\t';
  printf("isDigit('%c') is %s\n", c, isDigit(c) ? "YES" : "NO");

  c = '\n';
  printf("isDigit('%c') is %s\n", c, isDigit(c) ? "YES" : "NO");

  c = '+';
  printf("isDigit('%c') is %s\n", c, isDigit(c) ? "YES" : "NO");

  c = '-';
  printf("isDigit('%c') is %s\n", c, isDigit(c) ? "YES" : "NO");

  c = '0';
  printf("isDigit('%c') is %s\n", c, isDigit(c) ? "YES" : "NO");

  c = '1';
  printf("isDigit('%c') is %s\n", c, isDigit(c) ? "YES" : "NO");
}

int isDigitOrDot(char c)
{
  if (c == '.')
    return 1;

  return isDigit(c);
}

void isDigitOrDotTest(void)
{
  char c = ' ';
  printf("isDigitOrDot('%c') is %s\n", c, isDigitOrDot(c) ? "YES" : "NO");

  c = '\t';
  printf("isDigitOrDot('%c') is %s\n", c, isDigitOrDot(c) ? "YES" : "NO");

  c = '\n';
  printf("isDigitOrDot('%c') is %s\n", c, isDigitOrDot(c) ? "YES" : "NO");

  c = '+';
  printf("isDigitOrDot('%c') is %s\n", c, isDigitOrDot(c) ? "YES" : "NO");

  c = '-';
  printf("isDigitOrDot('%c') is %s\n", c, isDigitOrDot(c) ? "YES" : "NO");

  c = '0';
  printf("isDigitOrDot('%c') is %s\n", c, isDigitOrDot(c) ? "YES" : "NO");

  c = '1';
  printf("isDigitOrDot('%c') is %s\n", c, isDigitOrDot(c) ? "YES" : "NO");

  c = '.';
  printf("isDigitOrDot('%c') is %s\n", c, isDigitOrDot(c) ? "YES" : "NO");

  c = '8';
  printf("isDigitOrDot('%c') is %s\n", c, isDigitOrDot(c) ? "YES" : "NO");

  c = '9';
  printf("isDigitOrDot('%c') is %s\n", c, isDigitOrDot(c) ? "YES" : "NO");
}

int isWhiteSpace(char c)
{
  return (c == ' ' || c == '\t' || c == '\n') ? 1 : 0;
}

void isWhiteSpaceTest(void)
{
  char c = ' ';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) ? "YES" : "NO");

  c = '\t';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) ? "YES" : "NO");

  c = '\n';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) ? "YES" : "NO");

  c = '+';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) ? "YES" : "NO");

  c = '-';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) ? "YES" : "NO");

  c = '0';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) ? "YES" : "NO");

  c = '1';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) ? "YES" : "NO");
}

void ungetch(char c)
{
  BUF[++BUF_INDEX] = c;
}

void ungetchTest(void)
{
  BUF_INDEX = -1;
  ungetch('a');
  ungetch('b');
  ungetch('c');

  printf("BUF_INDEX should be 2, it is %d\n", BUF_INDEX);
  printf("BUF first 3 chars should be `a`, `b`, `c`. They are: `%c`, `%c`, `%c`\n", BUF[0], BUF[1], BUF[2]);
}
