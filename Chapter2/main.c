#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define REG 0
#define ESCAPE 1

int htoi(const char s[]);
char toLower(const char c);
void strToLower(char s[]);
int strlen2(const char s[]);
void squeeze(char s1[], char s2[]);
int any(char s1[], char s2[]);
unsigned setbits(unsigned x, int n, int p, unsigned y);
unsigned bitMask(int n, int p);
unsigned zeroMask(int n, int p);
unsigned invert(unsigned x, int n, int p);
int bits(unsigned x);
int oneBits(unsigned x);
unsigned rightrot(unsigned x, int n);
int binsearch(int x, int v[], int n);
void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main()
{
  printf("\n");
  // printf("10001000 ^ 1000 = %u\n", 0b10001000 ^ 0b1000);
  // printf("invert(0b10011000, 3, 1) => %u\n", invert(0b10011000, 3, 1));
  // printf("zeroMask(3, 2) => %u\n", zeroMask(3, 2));
  // printf("rightrot(0b11001010, 2) is %u\n", rightrot(0b11001010, 2));
  // printf("oneBits(0b100000011) is %d\n", oneBits(0b100000011));
  // int v[6] = {0, 1, 2, 3, 4};
  // printf("index of 10 in [0,1,2,3,4]: %d\n", binsearch(10, v, 5));
  char s[100] = "Hello\\tmy\\tfriend\\n!!!!";
  printf("s is %s\n", s);
  char t[100];
  unescape(s, t);
  printf("t is %s\n", t);
  
  return 0;
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

void squeeze(char s1[], char s2[])
{
  int i = 0;
  char c1, c2;

  while ((c1 = s2[i++]) != '\0')
  {
    int j = 0;
    int k = 0;

    do
    {
      c2 = s1[j++];

      if (c2 != c1)
        s1[k++] = c2;
    } while (c2 != '\0');
  }
}

int any(char s1[], char s2[])
{
  int i, j;

  for (i = 0; s1[i] != '\0'; i++)
    for (j = 0; s2[j] != '\0'; j++)
      if (s1[i] == s2[j])
        return i;

  return -1;
}

unsigned setbits(unsigned x, int n, int p, unsigned y)
{
  /**
   *   
   * x is 10101010
   * y is 11001100
   * n = 3, p = 2
   * 
   * shift x right then left to n + p positions
   * x‘ = x >> p + n << p + n = 10100000
   *
   * make a mask from 0 to p
   * mask = 11
   *
   * use mask on x‘ with
   * x‘ = (x & mask) | x‘ = (10101010 & 11) | 10100000 = 10100010
   *
   * make a mask from p to n
   * mask = 11100
   *
   * make y‘
   * y‘ = y & mask = 11001100 & 11100 = 1100
   *
   * finally join x‘ and y‘
   * x‘ | y‘ = 10100010 | 1100 = 10101110
   */
  unsigned mask;
  unsigned x2, y2;

  x2 = x >> (p + n) << (p + n); // 0b10100000 -> 160
  // printf("x2 (160): %u\n", x2);

  mask = ~(~0 << p); // 11 -> 3
  // printf("mask u (3): %u\n", mask);

  x2 = x & mask | x2; // 0b10100010 -> 162
  // printf("x2 (162): %u\n", x2);

  mask = bitMask(n, p); // 0b11100 -> 28
  // printf("mask (28): %u\n", mask);

  y2 = y & mask; // 0b1100 -> 12
  // printf("y2 (12): %u\n", y2);

  x2 = x2 | y2; // 0b10101110 -> 174
  // printf("0b10101110 -> 174: %u", x2);

  return x2;
}

/**
 * n = 3, p = 0: 111
 * n = 3, p = 1: 1110
 * n = 3, p = 2: 11100
 */
unsigned bitMask(int n, int p)
{
  return ~(~0 << n) << p;
}

/**
 * n = 1, p = 0: 10
 * n = 1, p = 1: 101
 * n = 1, p = 2: 1011
 * n = 2, p = 0: 100
 * n = 2, p = 1: 1001
 * n = 2, p = 2: 10011
 * n = 3, p = 0: 1000
 * n = 3, p = 1: 10001
 * n = 3, p = 2: 100011
 */
unsigned zeroMask(int n, int p)
{
  unsigned r = 1;

  r = r << (n + p);

  unsigned mask = ~(~0 << p);

  return r | mask;
}

/**
 * 1. make mask of n, p => 1110
 * 2. x‘ = (mask & x) ^ x  => 1000
 * 2. x“ = ~x & mask => 110
 * 3. x‘ = x ^ x‘ =>
 */
unsigned invert(unsigned x, int n, int p)
{
  // x = 10011000
  // n = 3, p = 1

  // make mask of n, p => 1110
  unsigned mask = bitMask(n, p);

  // x‘ = (mask & x) ^ x  => (1110 & 10011000) ^ 10011000 => 10010000
  unsigned x2 = (x & mask) ^ x;

  // x“ = x‘ | (mask & ~x) => 10010000 | 1110 & 01100111 =>
  unsigned x3 = x2 | (mask & ~x);

  return x3;
}

int bits(unsigned x)
{
  int bits = 0;

  do {
    x = x >> 1;
    bits++;
  }
  while (x > 0);

  return bits;
}

/**
 * receives 11001010
 * n = 2
 * returns 10110010
 */
unsigned rightrot(unsigned x, int n)
{
  int N = bits(x) - n;

  // 11 & 11001010 -> 10
  unsigned nBits = bitMask(n, 0) & x;

  // 10000000 | 110010 -> 10110010
  return nBits << N | x >> n;
}

int oneBits(unsigned x)
{
  if (x == 0)
    return 0;

  int j;

  for (j = 1; (x &= x - 1) != 0; j++);

  return j;
}

void strToLower(char s[])
{
  char c;

  for (int i = 0; (c = s[i]) != '\0'; i++)
  {
    s[i] = (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
  }
}
