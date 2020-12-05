#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>

void testChar();
void testShort();
void testInt();
void testLong();
void testFloat();
void testDouble();

int main()
{
  testChar();
  testShort();
  testInt();
  testLong();
  testFloat();
  testDouble();

  printf("\n");
  return 0;
}

void testChar()
{
  printf("\nType char\n");
  unsigned char uch = 0;
  uch--;
  char ch = uch / 2;
  printf("max: %d (CHAR_MAX is %d)\n", ch, CHAR_MAX);
  printf("min: %d (CHAR_MIN is %d)\n", ++ch, CHAR_MIN);
  printf("unsigned max: %u (UCHAR_MAX is %u)\n", uch, UCHAR_MAX);
}

void testShort()
{
  printf("\nType short\n");
  unsigned short int ush = 0;
  ush--;
  short int sh = ush / 2;
  printf("max: %d (SHRT_MAX: %d)\n", sh, SHRT_MAX);
  printf("min: %d (SHRT_MIN: %d)\n", ++sh, SHRT_MIN);
  printf("unsigned max: %u (USHRT_MAX: %u)\n", ush, USHRT_MAX);
}

void testInt()
{
  printf("\nType int\n");
  unsigned int ui = 0;
  ui--;
  int i = ui / 2;
  printf("max: %d (INT_MAX: %d)\n", i, INT_MAX);
  printf("min: %d (INT_MIN: %d)\n", ++i, INT_MIN);
  printf("unsigned max: %u (UINT_MAX: %u)\n", ui, UINT_MAX);
}

void testLong()
{
  printf("\nType long\n");
  unsigned long int ul = 0;
  ul--;
  long int l = ul / 2;
  printf("max: %ld (LONG_MAX: %ld)\n", l, LONG_MAX);
  printf("min: %ld (LONG_MIN: %ld)\n", ++l, LONG_MIN);
  printf("unsigned max: %lu (ULONG_MAX: %lu)\n", ul, ULONG_MAX);
}

void testFloat()
{
  printf("\nType float\n");

  float v1, v2, v3, v4;

  int i = 0;
  do
  {
    i++;
    v1 = v2;
    v2 = 1.0f * pow(2, i);
  } while (v2 < INFINITY);

  i = 0;
  do
  {
    i++;
    v3 = v4;
    v4 = -1.0f * pow(2, i);
  } while (-INFINITY < v4);

  printf("min: %.0f (FLT_MIN: %.0f)\n", v3, FLT_MIN);
  printf("max: %.0f (FLT_MAX: %.0f)\n", v1, FLT_MAX);
}

void testDouble()
{
  printf("\nType double\n");

  double v1, v2, v3, v4;

  int i = 0;
  do
  {
    i++;
    v1 = v2;
    v2 = 1.0 * pow(2, i);
  } while (v2 < INFINITY);

  i = 0;
  do
  {
    i++;
    v3 = v4;
    v4 = -1.0 * pow(2, i);
  } while (-INFINITY < v4);

  printf("min: %.0f (DBL_MIN: %.0f)\n", v3, DBL_MIN);
  printf("max: %.0f (DBL_MAX: %.0f)\n", v1, DBL_MAX);
  printf("----\013-----");
}
