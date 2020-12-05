#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define REG 0
#define ESCAPE 1

enum boolean { NO, YES };

void itoa(const int i, char s[]);
void itoaPad(const int i, char s[], const int l);
void itob(const int n, char s[], const int b);
void expand(const char s1[], char s2[]);
void escape(char s[], char t[]);
void unescape(char s[], char t[]);
int binsearch(int x, int v[], int n);
int htoi(const char s[]);
char toLower(const char c);
int strlen2(const char s[]);
void strToLower(char s[]);
void reverseStr(char s[]);

int main()
{
  char s2[999];
  // expand("a-zA-Z0-9", s2);
  const int n = -511;
  const int b = 8;
  const int l = 6;
  // itoa(n, s2);
  // itob(n, s2, b);
  itoaPad(n, s2, l);

  printf("\n");
  // printf("itob(%d, s2, %d): %s\n", n, b, s2);
  // printf("itoa(%d, s2): %s\n", n, s2);
  printf("itoaPad(%d, s2, %d): [%s]\n", n, l, s2);
  // printf("10001000 ^ 1000 = %u\n", 0b10001000 ^ 0b1000);
  // printf("invert(0b10011000, 3, 1) => %u\n", invert(0b10011000, 3, 1));
  // printf("zeroMask(3, 2) => %u\n", zeroMask(3, 2));
  // printf("rightrot(0b11001010, 2) is %u\n", rightrot(0b11001010, 2));
  // printf("oneBits(0b100000011) is %d\n", oneBits(0b100000011));
  // int v[6] = {0, 1, 2, 3, 4};
  // printf("index of 10 in [0,1,2,3,4]: %d\n", binsearch(10, v, 5));
  // char s[100] = "Hello\\tmy\\tfriend\\n!!!!";
  // printf("s is %s\n", s);
  // char t[100];
  // unescape(s, t);
  // printf("t is %s\n", t);
  
  return 0;
}

/**
 * Creates string representing the number i.
 */
void itoa(const int i, char s[])
{
  int j = 0;
  int n = i;

  if (n > 0)
    n *= -1;

  do
  {
    s[j++] = '0' - n % 10;
    n /= 10;
  } while (n != 0);

  if (i < 0)
  {
    s[j++] = '-';
  }

  s[j] = '\0';

  reverseStr(s);
}

void itoaPad(const int i, char s[], const int l)
{
    int j = 0;
  int n = i;

  if (n > 0)
    n *= -1;

  do
  {
    s[j++] = '0' - n % 10;
    n /= 10;
  } while (n != 0);

  if (i < 0)
  {
    s[j++] = '-';
  }

  while (j < l)
    s[j++] = ' ';

  s[j] = '\0';

  reverseStr(s);
}

/**
 * Creates string representing the number i
 * with base b, e.g.
 * itob(8, s, 2) will set s = "1000"
 */
void itob(const int n, char s[], const int b)
{
  int j = 0;
  int m = n;

  if (m > 0)
    m *= -1;

  do
  {
    int r = m % b;
    s[j++] = (r > -10 ? '0' : 'a' - 10) - r;
    m /= b;
  } while (m != 0);

  if (n < 0)
    s[j++] = '-';
  
  s[j] = '\0';

  reverseStr(s);
}

void expand(const char s1[], char s2[])
{
  int s1len = strlen2(s1);
  int i;
  int j = 0;

  for (i = 0; i < s1len; i++)
  {
    char c = s1[i];

    if (i == 0 || i + 1 == s1len || c != '-')
      s2[j++] = c;
    else
      for (char k = s1[i - 1] + 1; k < s1[i + 1]; k++)
        s2[j++] = k;
  }
}


void escape(char s[], char t[])
{
  char c;
  int i = 0;
  int j = 0;

  do
  {
    c = s[i++];

    switch (c)
    {
      case '\n':
        t[j++] = '\\';
        t[j++] = 'n';
        break;
      case '\t':
        t[j++] = '\\';
        t[j++] = 't';
        break;
      default:
        t[j++] = c;
        break;
    }
  } while (c != '\0');  
}

void unescape(char s[], char t[])
{
  int i = 0;
  int j = 0;
  char c;
  int mode = REG;

  do {
    c = s[i++];

    if (mode == ESCAPE)
    {
      switch (c)
      {
        case 'n':
          t[j++] = '\n';
          break;
        case 't':
          t[j++] = '\t';
          break;
        default:
          t[j++] = '\\';
          t[j++] = c;
          break;
      }
      mode = REG;
    }
    else if (c == '\\')
      mode = ESCAPE;
    else
      t[j++] = c;
  }
  while (c != '\0');
}

int binsearch(int x, int v[], int n)
{
  int low = 0;
  int high = n - 1;
  int mid;
  int counter = 0;

  while (low != high && ++counter < 10)
  {
    mid = (high + low) / 2;

    if (x > v[mid])
      low = mid + 1;
    else
      high = mid;
    
    printf("round %d: l/h %d/%d mid: %d\n", counter, low, high, mid);
  }

  return x == v[low] ? low : -1;
}

int htoi(const char s[])
{
  int slenght = strlen2(s);
  int result = 0;

  for (int i = 0; i < slenght; i++)
  {
    char c = toLower(s[slenght - i - 1]);

    if (i == slenght - 2)
      if (c == 'X' || c == 'x')
        return result;

    int base = pow(16.0, i);

    if (isdigit(c))
    {
      result += base * (c - '0');
    }
    else
    {
      result += base * (c - 'a' + 10);
    }
  }

  return result;
}

char toLower(const char c)
{
  if (c >= 'A' && c <= 'Z')
  {
    return c - 'A' + 'a';
  }

  return c;  
}

int strlen2(const char s[])
{
  int i = 0;

  while (s[i] != '\0')
    i++;
  
  return i;
}

void strToLower(char s[])
{
  char c;

  for (int i = 0; (c = s[i]) != '\0'; i++)
  {
    s[i] = (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
  }
}

void reverseStr(char s[])
{
    char c;
    int i;
    int slen = strlen2(s);

    for (i = 0; i < (slen / 2); i++)
    {
        c = s[i];
        s[i] = s[slen - i - 1];
        s[slen - i - 1] = c;
    }

    s[slen] = '\0';
}
