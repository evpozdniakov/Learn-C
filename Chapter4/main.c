#include <stdio.h>
#include <math.h>

#define swap(t,x,y) { t tmp = y; y = x; x = tmp; }

typedef enum {
  CLEAR = 'a',
  DUPL,
  EXP,
  GET,
  NUM,
  POW,
  SET_A,
  SET_B,
  SET_C,
  SET_Z,
  SIN,
  SWAP,
  TOP,
} command;

typedef enum { false, true } bool;
int stackIndex = 0;
double stack[100];
int bufIndex = 0;
const int BUFMAX = 100;
char buf[BUFMAX];
char bufChar;
bool bufEmpty = true;
bool bufIsEOF = false;



void swapTest(void);
void itoa(int i, char s[]);
int itoaRec(const int i, char s[], int len);
void itoaTest(void);
int getline2(char s[], int lim);
bool matchStr(char s1[], char s2[]);
void matchStrTest(void);
int strindex(char s[], char t[]);
void testStrindex(void);
int strrindex(char s[], char t[]);
void reverse(char s[]);
int reverseRec(char s[], int p);
void reverseTest();
int strlen2(char s[]);
double atof(char s[]);
void testAtof(void);
void calculator(void);
void push(double op);
double pop(void);
char getOp(char s[]);
char getch(void);
char getchUno(void);
void ungetch(char c);
void ungetchUno(char c);
void ungets(char s[]);

int main()
{
  // printf("SWAP is %d\n", SWAP);
  // printf("new line is %d\n", '\n');
  // testAtof();
  // testStrindex();
  // ungets("10 5 /\ntop\n");
  // calculator();
  // matchStrTest();
  // itoaTest();
  // reverseTest();
  swapTest();

  return 0;
}

void swapTest(void)
{
  float i1 = 12.3;
  float i2 = 4.56;

  swap(float, i1, i2);

  printf("%f & %f\n", i1, i2);
}

/**
 * Creates string representing the number i.
 */
void itoa(int i, char s[])
{
  int j = 0;

  if (i < 0)
  {
    i *= -1;
    s[j++] = '-';
  }
  
  int len = itoaRec(i, s, j);

  s[len] = '\0';
}

int itoaRec(const int i, char s[], int len)
{
  char c = i % 10 + '0';

  if (i / 10)
  {
    len = itoaRec(i / 10, s, len);
  }

  s[len] = c;

  return len + 1;
}

void itoaTest(void)
{
  int i;
  char s[100];

  i = -234;
  itoa(i, s);
  printf("%d is \"%s\"\n", i, s);

  i = 5400;
  itoa(i, s);
  printf("%d is \"%s\"\n", i, s);
}

bool matchStr(char s1[], char s2[])
{
  int i = -1;

  do {
    i++;
    if (s1[i] != s2[i])
      return false;
  }
  while (s1[i] != '\0');

  return true;
}

void matchStrTest(void)
{
  printf("abc == abc ? %d\n", matchStr("abc", "abc"));
  printf("abc == ABC ? %d\n", matchStr("abc", "ABC"));
  printf("abcdef == abc ? %d\n", matchStr("abcdef", "abc"));
  printf("ab == abc ? %d\n", matchStr("ab", "abc"));
  printf("`` == `` ? %d\n", matchStr("", ""));
}

/* getline:  read a line into s, return length */
int getline2(char s[], int lim)
{
  int c, i;
  for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

/**
 * Reads user input inf reverse Polish format, e.g.
 * `1 2 + 3 4 - *`
 * and returns result
 */
void calculator()
{
  double tmp;
  char s[100];
  double abc[26];

  do {
    char c = getOp(s);

    if (c == EOF)
      return;

    switch (c)
    {
      case '+':
        push(pop() + pop());
        break;
      case '-':
        tmp = pop();
        push(pop() - tmp);
        break;
      case '*':
        push(pop() * pop());
        break;
      case '/':
        tmp = pop();
        push(pop() / tmp);
        break;
      case '%':
        tmp = pop();
        push((int) pop() % (int) tmp);
        break;
      case '=':
        printf("result is %f", stack[stackIndex - 1]);
        break;
      case GET:
        printf("GET %c\n", s[0]);
        push(abc[s[0] - 'a']);
        break;
      case NUM:
        push(atof(s));
        break;
      case TOP:
        printf("top of the stack is %f", stack[stackIndex - 1]);
        break;
      case SWAP:
        tmp = stack[stackIndex - 1];
        stack[stackIndex - 1] = stack[stackIndex - 2];
        stack[stackIndex - 2] = tmp;
        printf("now top is %f", stack[stackIndex - 1]);
        break;
      case DUPL:
        push(stack[stackIndex - 1]);
        break;
      case CLEAR:
        stackIndex = 0;
        break;
      case SIN:
        push(sin(pop()));
        break;
      case EXP:
        push(exp(pop()));
        break;
      case POW:
        tmp = pop();
        push(pow(pop(), tmp));
        break;
      case SET_A:
        // printf("SET a to %s\n", s);
        abc[0] = atof(s);
        break;
      case SET_B:
        // printf("SET b to %s\n", s);
        abc[1] = atof(s);
        break;
      case SET_C:
        // printf("SET c to %s\n", s);       abc[2] = atof(s);
        break;
      default:
        printf("\n\n");
        break;
    }
  }
  while (1);
}

void push(double op)
{
  // printf("------ pushed %f\n", op);
  stack[stackIndex++] = op;
}

double pop()
{
  return stack[--stackIndex];
}

char getOp(char s[])
{
  // if (bufIndex == 0)
  // {
  //   char s2[BUFMAX];
  //   int l = getline2(s2, BUFMAX);

  //   if (l == 0)
  //   {
  //     return EOF;
  //   }

  //   ungets(s2);
  // }

  char c;
  static char lastC = 0;

  // skip spaces and tabs
  do
  {
    if (lastC > 0)
    {
      c = lastC;
      lastC = 0;
    }
    else
      c = getch();
  } while (c == ' ' || c == '\t');

  // return new line or EOF
  if (c == '\n' || c == EOF)
  {
    return c;
  }
  
  int i = 0;

  // read characters into a string
  while (c != ' ' && c != '\t' && c != '\n')
  {
    s[i++] = c;
    c = getch();
  }

  s[i] = '\0';
  lastC = c; // ungetch(c);

  if (i == 1)
  {
    // return GET if the result string
    // is a single letter
    if (s[0] >= 'a' && s[0] <= 'z')
      return GET;

    // return the result string
    // if it contains single non-numeric character
    if (s[0] < '0' || s[0] > '9')
      return s[0];
  }

  // check for a command
  if (matchStr(s, "top"))
    return TOP;

  if (matchStr(s, "swap"))
    return SWAP;

  if (matchStr(s, "duplicate"))
    return DUPL;

  if (matchStr(s, "clear"))
    return CLEAR;

  if (matchStr(s, "sin"))
    return SIN;

  if (matchStr(s, "exp"))
    return EXP;

  if (matchStr(s, "pow"))
    return POW;

  if (matchStr(s, "set"))
  {
    // read the variabe name
    getOp(s);
    char varName = s[0];

    // read the argument to assign
    getOp(s);

    switch (varName)
    { 
      case 'a':
        return SET_A;
      case 'b':
        return SET_B;
      case 'c':
        return SET_C;
      default:
        return SET_Z;
    }
  }

  // if it is not a command
  // then we assume it is a number
  return NUM;
}

char getch()
{
  if (bufIndex > 0)
  {
    return buf[--bufIndex];
  }

  return getchar();
}

char getchUno()
{
  printf(",");
  if (bufEmpty == false)
  {
    bufEmpty = true;

    if (bufIsEOF == true)
    {
      bufIsEOF = false;
      return EOF;
    }

    return bufChar;
  }

  return getchar();
}

void ungetch(char c)
{
  if (bufIndex < BUFMAX)
    buf[bufIndex++] = c;
  else
    printf("char buffer limit reached");
}

void ungetchUno(char c)
{
  if (bufEmpty == true)
  {
    bufEmpty = false;
    if (c == EOF)
      bufIsEOF = true;
    else
      bufChar = c;
  }
  else
    printf("uno char buffer not empty");
}

void ungets(char s[])
{
  int l = strlen2(s);

  for (int i = l - 1; i >= 0; i--)
    ungetch(s[i]);
}

/**
 * returns position of letf most entry of t in s
 * or -1
 */
int strindex(char s[], char t[])
{
  int j, k;

  for (int i = 0; s[i] != '\0'; i++)
  {
    for (j = i, k = 0; s[j] == t[k] && t[k] != '\0'; j++, k++);

    if (t[k] == '\0')
      return i;
  }

  return -1;
}

void testStrindex()
{
  printf("strindex(`Hello, world`, `Hell`) is %d\n", strindex("Hello, world", "Hell"));
  printf("strindex(`Hello, world`, `abc`) is %d\n", strindex("Hello, world", "abc"));
  printf("strindex(`Hello, world`, ``) is %d\n", strindex("Hello, world", ""));
  printf("strlen2(`Hello`): %d\n", strlen2("Hello"));
  char s1[] = "0123456789";
  reverse(s1);
  printf("reverse(`0123456789`): %s\n", s1);
  char s2[] = "123456789";
  reverse(s2);
  printf("reverse(`123456789`): %s\n", s2);
  char s3[] = "Hello, hello, my dear friend!!!";
  char s4[] = "ll";
  printf("strindex(`%s`, `%s`) is %d\n", s3, s4, strindex(s3, s4));
  printf("strrindex(`%s`, `%s`) is %d\n", s3, s4, strrindex(s3, s4));
  char s5[] = "Hello, hello, my dear friend!!!";
  char s6[] = "??";
  printf("strindex(`%s`, `%s`) is %d\n", s5, s6, strindex(s5, s6));
  printf("strrindex(`%s`, `%s`) is %d\n", s5, s6, strrindex(s5, s6));
}

/**
 * returns position of right most entry of t in s
 * or -1
 */
int strrindex(char s[], char t[])
{
  reverse(s);
  reverse(t);

  int i = strindex(s, t);

  reverse(s);
  reverse(t);

  if (i >= 0)
    return --i + strlen2(t);

  return i;
}

/**
 * Takes string representation of a float value
 * with scientific notation
 * and returns double, e.g.
 * " 1.23456e-3 " -> 0.00123456
 * Returns 0 if the string can't be converted into a number
 */
double atof(char s[])
{
  int i = 0;
  int sign = 1;
  double result = 0;

  // skip any space
  while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
    i++;

  // expect '+' or '-'
  if (s[i] == '-')
  {
    sign = -1;
    i++;
  }
  else if (s[i] == '+')
  {
    i++;
  }

  // expect a number character
  // return 0 otherwise
  if (s[i] >= '0' && s[i] <= '9')
  {
    do
    {
      result *= 10;
      result += s[i] - '0';
      i++;
    } while (s[i] >= '0' && s[i] <= '9');
  }

  // expect an optional decimal point
  if (s[i] == '.')
  {
    i++;

    // expect a number character after the decimal point
    // return 0 otherwise
    if (s[i] < '0' && s[i] > '9')
    {
      // printf("return 0 because no number found after decimal point\n");
      return 0;
    }

    for (double d = 0.1; s[i] >= '0' && s[i] <= '9'; d /= 10, i++)
      result += (s[i] - '0') * d;
  }

  // expect an optional 'e' or 'E'
  if (s[i] == 'e' || s[i] == 'E')
  {
    i++;

    float k = 10.0;

    // expect '+' or '-'
    if (s[i] == '-')
    {
      k = 0.1;
      i++;
    }
    else if (s[i] == '+')
    {
      i++;
    }

    // expect a number character
    // return 0 otherwise
    if (s[i] < '0' && s[i] > '9')
    {
      // printf("return 0 because no number found after E\n");
      return 0;
    }

    int p = 0;

    do
    {
      p *= 10;
      p += s[i] - '0';
      i++;
    }
    while (s[i] < '0' && s[i] > '9');

    // apply power
    for (int j = 0; j < p; j++)
      result *= k;
  }

  // skip any space
  while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
    i++;

  // expect end of string
  // return 0 otherwise
  if (s[i] != '\0')
  {
    // printf("return 0 because end of string not found\n");
    return 0;
  }

  return result * sign;
}

void testAtof()
{
    printf("atof('1234') is %f\n", atof("1234"));
  printf("atof('-123') is %f\n", atof("-123"));
  printf("atof('+12') is %f\n", atof("+12"));
  printf("atof('12.34') is %f\n", atof("12.34"));
  printf("atof('-12.3') is %f\n", atof("-12.3"));
  printf("atof('+1.2') is %f\n", atof("+1.2"));
  printf("atof('.1234') is %f\n", atof(".1234"));
  printf("atof('-.123') is %f\n", atof("-.123"));
  printf("atof('+.12') is %f\n", atof("+.12"));
  printf("atof('1234e1') is %f\n", atof("1234e1"));
  printf("atof('-123e-2') is %f\n", atof("-123e-2"));
  printf("atof('+12E3') is %f\n", atof("+12E3"));
  printf("atof('12.34e3') is %f\n", atof("12.34e3"));
  printf("atof('-12.3E1') is %f\n", atof("-12.3E1"));
  printf("atof('+1.2E-2') is %f\n", atof("+1.2E-2"));
  printf("atof('.1234e3') is %f\n", atof(".1234e3"));
  printf("atof('-.123E1') is %f\n", atof("-.123E1"));
  printf("atof('+.12E-2') is %f\n", atof("+.12E-2"));
  printf("\n");
  printf("atof('  1234  ') is %f\n", atof("  1234  "));
  printf("atof('  -123  ') is %f\n", atof("  -123  "));
  printf("atof('  +12  ') is %f\n", atof("  +12  "));
  printf("atof('  12.34  ') is %f\n", atof("  12.34  "));
  printf("atof('  -12.3  ') is %f\n", atof("  -12.3  "));
  printf("atof('  +1.2  ') is %f\n", atof("  +1.2  "));
  printf("atof('  1234e1  ') is %f\n", atof("  1234e1  "));
  printf("atof('  -123e-2  ') is %f\n", atof("  -123e-2  "));
  printf("atof('  +12E3  ') is %f\n", atof("  +12E3  "));
  printf("atof('  12.34e3  ') is %f\n", atof("  12.34e3  "));
  printf("atof('  -12.3E1  ') is %f\n", atof("  -12.3E1  "));
  printf("atof('  +1.2E-2  ') is %f\n", atof("  +1.2E-2  "));
  printf("atof('  .1234e3  ') is %f\n", atof("  .1234e3  "));
  printf("atof('  -.123E1  ') is %f\n", atof("  -.123E1  "));
  printf("atof('  +.12E-2  ') is %f\n", atof("  +.12E-2  "));
  printf("\n");
  printf("atof(' d +1.2E-2  ') is %f\n", atof(" d +1.2E-2  "));
  printf("atof(' 0x32  ') is %f\n", atof(" 0x32  "));
  printf("atof(' 32  s') is %f\n", atof(" 32  s"));
  printf("atof(' 32,0') is %f\n", atof(" 32,0"));
}

/**
 * changes the incoming string by reversing it
 */
void reverse(char s[])
{
  // int lastIndx = strlen2(s) - 1;

  // for (int i = 0; i <= lastIndx / 2; i++)
  // {
  //   char t = s[i];
  //   s[i] = s[lastIndx - i];
  //   s[lastIndx - i] = t;
  // }

  int i;
  reverseRec(s, 0);
}

int reverseRec(char s[], int p)
{
  char c = s[p];

  if (c != '\0')
  {
    int len = reverseRec(s, p + 1);
    s[len - p - 1] = c;

    return len;
  }

  return p;
}

void reverseTest()
{
  char s[] = "abcdef";
  reverse(s);
  printf("\nreverse of `abcdef` is `%s`\n", s);

}

/**
 * changes the incoming string by reversing it
 */
int strlen2(char s[])
{
  int i;

  for (i = 0; s[i] != '\0'; i++);

  return i;
}

