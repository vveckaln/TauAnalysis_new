#include "LIP/TauAnalysis/interface/test_utilities.hh"

const unsigned short size = 64;
void bitwise_and(unsigned short * array1, unsigned short *array2, unsigned short* result_array)
{
  for (unsigned short ind = 0; ind < size; ind ++)
    {
      result_array[ind] = array1[ind] &  array2[ind];
    }
}

void print(const unsigned short *array)
{
  for (short ind = size-1; ind > -1; ind --) 
    {
      if ((ind +1)%8 == 0) printf(" ");
      printf("%u", array[ind]);
    }
  printf("\n");
}
void convert1(unsigned short *array, const unsigned short positions)
{
  for (unsigned short ind = 0; ind < size; ind ++)
    {
      array[ind] = 0;
    }
  array[positions] = 1;
}

void convert_to_digital(unsigned short *array, unsigned long value)
{
  for (unsigned short ind = 0; ind < size; ind ++)
    {
      array[ind] = (value >> ind) & 1;
    }
}
