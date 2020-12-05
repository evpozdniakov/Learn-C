#include <stdio.h>
#include <string.h>

typedef enum { false, true } bool;

char getch(void);
void getchTest(void);
char getint(int *p);
void getintTest(void);
bool isDigit(char c);
void isDigitTest(void);
bool isWhiteSpace(char c);
void isWhiteSpaceTest(void);
void ungetch(char c);
void ungetchTest(void);

const int BUF_SIZE = 100;
char BUF[BUF_SIZE];
int BUF_INDEX = -1;

int main()
{
  printf("\n");
  // getchTest();
  getintTest();
  // getint();
  // isDigitTest();
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

char getint(int *p)
{
  char c;

  while (isWhiteSpace(c = getch()) == true)
    ;
  
  if (c != '+' && c != '-' && isDigit(c) == false)
    return c == EOF ? EOF : 0;

  int sign = 1;

  if (c == '-')
    sign = -1;
  
  if (c == '+' || c == '-')
    c = getch();

  if (isDigit(c) == false)
    return c == EOF ? EOF : 0;

  int n = 0;

  do
  {
    n *= 10;
    n += c - '0';
    c = getch();
  }
  while (isDigit(c) == true);

  ungetch(c);

  *p = n * sign;

  return c == EOF ? EOF : 1;
}

void getintTest(void)
{
  char c;

  char input[] = " 05 04+\t03-\t02\t 01- ";
  // char s[45] = "=-4ufaosdihf lasdhf lasdhfk ajsdhf alsdjhfas\n";
  // char input[] = "098\n\t 076\t 05 04+\n03-\t02\t 01- ";

  int i = 0;
  
  while ((c = input[i++]) != '\0')
    ungetch(c);

  int *p;

  while ((c = getint(p)) != EOF)
    if (c)
      printf("`%c`, %d\n", c, *p);
}

bool isDigit(char c)
{
  return (c >= '0' && c <= '9') ? true : false;
}

void isDigitTest(void)
{
  char c = ' ';
  printf("isDigit('%c') is %s\n", c, isDigit(c) == true ? "true" : "false");

  c = '\t';
  printf("isDigit('%c') is %s\n", c, isDigit(c) == true ? "true" : "false");

  c = '\n';
  printf("isDigit('%c') is %s\n", c, isDigit(c) == true ? "true" : "false");

  c = '+';
  printf("isDigit('%c') is %s\n", c, isDigit(c) == true ? "true" : "false");

  c = '-';
  printf("isDigit('%c') is %s\n", c, isDigit(c) == true ? "true" : "false");

  c = '0';
  printf("isDigit('%c') is %s\n", c, isDigit(c) == true ? "true" : "false");

  c = '1';
  printf("isDigit('%c') is %s\n", c, isDigit(c) == true ? "true" : "false");
}

bool isWhiteSpace(char c)
{
  return (c == ' ' || c == '\t' || c == '\n') ? true : false;
}

void isWhiteSpaceTest(void)
{
  char c = ' ';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) == true ? "true" : "false");

  c = '\t';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) == true ? "true" : "false");

  c = '\n';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) == true ? "true" : "false");

  c = '+';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) == true ? "true" : "false");

  c = '-';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) == true ? "true" : "false");

  c = '0';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) == true ? "true" : "false");

  c = '1';
  printf("isWhiteSpace('%c') is %s\n", c, isWhiteSpace(c) == true ? "true" : "false");
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
