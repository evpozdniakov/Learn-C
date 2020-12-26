#include <stdio.h>
#include <string.h>

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
void pointerTest(void);
void ungetch(char c);
void ungetchTest(void);
int strlen3(const char *s);
int strcmp2(char *dst, char *src);
void strcmp2Test(void);
char * strcat2(char *s, const char *t);
void strcat2Test(void);
int strend(char *s, const char *t);
void strendTest(void);
void strncpy2(char *s, const char *t, int n);
void strncpy2Test(void);
void strncat2(char *s, const char *t, int n);
void strncat2Test(void);
int strncmp2(const char *s, const char *t, int n);
void ctrncmp2Test(void);

const int BUF_SIZE = 100;
char BUF[BUF_SIZE];
int BUF_INDEX = -1;

int main(int argc, char** argv)
{
  printf("\n");
  // getchTest();
  // getfloatTest();
  // getintTest();
  // getint();
  // isDigitTest();
  // isDigitOrDotTest();
  // isWhiteSpaceTest();
  // pointerTest();
  // strcmp2Test();
  // strcat2Test();
  // strendTest();
  // strncpy2Test();
  // strncat2Test();
  ctrncmp2Test();
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

void pointerTest(void)
{
  int a[] = {0, 1, 2, 3, 4, 5, 6, 7};

  int *p1 = &a[0];

  int *p2;

  p2 = a;

  printf("a is %p\n", a);
  printf("p1 is %p\n", p1);
  printf("p2 is %p\n", p2);
  printf("p2[3] is %d\n", p2[3]);

  char s[] = "hello";

  char *ps = &s[0];

  int l = strlen3(s);

  printf("length of `%s` is %d\n", s, l);

  for (int i = 0; i < 2000; i++)
    printf("%d %c", i, *(ps + i));
  
  printf("\n");
}

int strlen3(const char *s)
{
  int i;

  for (i = 0; *s != '\0'; s++, i++)
    ;

  return i;
}

int strcmp2(char *s1, char *s2)
{
  do
  {
    if (*s1 < *s2)
      return 1;
    else if (*s1 > *s2)
      return -1;
    s1++;
    s2++;
  } while (*s1 != '\0' || *s2 != '\0');
  
  return 0;
}

void strcmp2Test(void)
{
  printf("strcmp2(`ab`, `ab`) is %d\n", strcmp2("ab", "ab"));
  printf("strcmp2(`ab`, `ac`) is %d\n", strcmp2("ab", "ac"));
  printf("strcmp2(`ab`, `aa`) is %d\n", strcmp2("ab", "aa"));
  printf("strcmp2(`ab`, `abc`) is %d\n", strcmp2("ab", "abc"));
  printf("strcmp2(`abcd`, `abc`) is %d\n", strcmp2("abcd", "abc"));
}

/* copies the string t to the end of s */
char * strcat2(char *s, const char *t)
{
  char *res;
  res = s;

  while (*s)
    s++;
  
  while ((*s++ = *t++) != '\0')
    ;

  return res;
}

void strcat2Test(void)
{
  char s1[] = "ab";
  printf("strcat2(`ab`, `cd`): %s\n", strcat2(s1, "cd"));

  char s2[] = "";
  printf("strcat2(``, `cd`): %s\n", strcat2(s2, "cd"));

  char s3[] = "ab";
  printf("strcat2(`ab`, ``): %s\n", strcat2(s3, ""));
}

/* returns 1 if the string t occurs at the end of the string s, and zero otherwise */
int strend(char *s, const char *t)
{
  int tl = strlen3(t);
  int sl = strlen3(s);

  if (tl > sl)
    return 0;

  s += sl - tl;

  do {
    // printf("%c vs %c\n", *s, *t);
    if (*s++ != *t++)
      return 0;
  }
  while (*s != '\0' && *t != '\0');

  return 1;
}

void strendTest(void)
{
  printf("strend(`abcde`, `cde`) is %d\n", strend("abcde", "cde"));
  printf("strend(`abcde`, `abcde`) is %d\n", strend("abcde", "abcde"));
  printf("strend(`abcde`, `abcdef`) is %d\n", strend("abcde", "abcdef"));
  printf("strend(`abcde`, `cd`) is %d\n", strend("abcde", "cd"));
  printf("strend(`bcde`, `abcde`) is %d\n", strend("bcde", "abcde"));
}

void strncpy2(char *s, const char *t, int n)
{
  for (int i = 0; *s != '\0' && *t != '\0' && i < n; i++)
    *s++ = *t++;
}

void strncpy2Test(void)
{
  char t[30] = "abcdefghijklmn";
  char s[30] = "0123456";
  int n = 90;
  printf("strncpy2(`%s`, `%s`, %d)", s, t, n);
  strncpy2(s, t, n);
  printf(" makes s = `%s`\n", s);

  n = 4;
  for (int i = 0; i < 7; i++)
    *(s + i) = '0' + i;
  *(s + 7) = '\0';
  printf("strncpy2(`%s`, `%s`, %d)", s, t, n);
  strncpy2(s, t, n);
  printf(" makes s = `%s`\n", s);

  n = 0;
  for (int i = 0; i < 7; i++)
    *(s + i) = '0' + i;
  *(s + 7) = '\0';
  printf("strncpy2(`%s`, `%s`, %d)", s, t, n);
  strncpy2(s, t, n);
  printf(" makes s = `%s`\n", s);

  n = -2;
  for (int i = 0; i < 7; i++)
    *(s + i) = '0' + i;
  *(s + 7) = '\0';
  printf("strncpy2(`%s`, `%s`, %d)", s, t, n);
  strncpy2(s, t, n);
  printf(" makes s = `%s`\n", s);
}

/* concatenate at most n characters of t to end of s */
void strncat2(char *s, const char *t, int n)
{
  s += strlen3(s);

  for (int i = 0; i < n && *t != '\0'; i++)
    *s++ = *t++;

  *s = '\0';
}

void strncat2Test(void)
{
  char t[] = "abcdef";
  char s[20] = "0123456";
  int n = 10;

  printf("strncat2(`%s`, `%s`, %d)", s, t, n);
  strncat2(s, t, n);
  printf(" makes s = `%s`\n", s);

  *(s + 7) = '\0';
  n = 2;
  printf("strncat2(`%s`, `%s`, %d)", s, t, n);
  strncat2(s, t, n);
  printf(" makes s = `%s`\n", s);

  *(s + 7) = '\0';
  n = 0;
  printf("strncat2(`%s`, `%s`, %d)", s, t, n);
  strncat2(s, t, n);
  printf(" makes s = `%s`\n", s);

  *(s + 7) = '\0';
  n = -4;
  printf("strncat2(`%s`, `%s`, %d)", s, t, n);
  strncat2(s, t, n);
  printf(" makes s = `%s`\n", s);
}

/* compares first n characters of strings s and t;
   returns difference */
int strncmp2(const char *s, const char *t, int n)
{
  for (int i = 1; i < n && *s == *t && *s != '\0'; s++, t++, i++)
    ;

  return *s - *t;
}

void ctrncmp2Test(void)
{
  int n1 = 0;
  char s1[] = "abcdef";
  char t1[] = "abccc";
  printf("strncmp2(`%s`, `%s`, %d) is %d\n", s1, t1, n1, strncmp2(s1, t1, n1));

  int n2 = 3;
  char s2[] = "abcdef";
  char t2[] = "abccc";
  printf("strncmp2(`%s`, `%s`, %d) is %d\n", s2, t2, n2, strncmp2(s2, t2, n2));

  int n3 = 5;
  char s3[] = "abcdef";
  char t3[] = "abccc";
  printf("strncmp2(`%s`, `%s`, %d) is %d\n", s3, t3, n3, strncmp2(s3, t3, n3));

  int n4 = 5;
  char s4[] = "abcdef";
  char t4[] = "ab";
  printf("strncmp2(`%s`, `%s`, %d) is %d\n", s4, t4, n4, strncmp2(s4, t4, n4));
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
