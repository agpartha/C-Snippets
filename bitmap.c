/*
 *
 ******************************************************************************* 

   The MIT License (MIT)

   Copyright (c) <2015> <Anand Girish>

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
 
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.
 
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.

 *******************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


unsigned long  n_bits = 75;
unsigned long  n_bytes = 0;

void set_bit(char *bit_map, unsigned long value)
{
  /*
   * Get the byte number & the bit position in the byte
   * for this value. 
   */
   /* Ensure maximum bit popsition is withing our limits for bits to not voer shoot bitmap */
   bit_map  += (value % n_bits)/ 8;
   *bit_map |= (0x1 << (value % 8));
}


void clear_bit(char *bit_map, unsigned long value)
{
  /*
   * Get the byte number & the bit position in the byte
   * for this value. 
   */
   bit_map  += (value % n_bits)/ 8;
   *bit_map &= ~(0x1 << (value % 8));
}

void set_n_bits(char *bit_map, unsigned long n_bits)
{
	if (n_bits > 8) {
		memset (bit_map, 0xFF, n_bits / 8);
		*(bit_map + n_bits/8) = (0xFF >> (8 - (n_bits % 8)));
	}
}



int test_bit(char *bit_map, unsigned long value)
{
  /*
   * Get the byte number & the bit position in the byte
   * for this value. 
   */
   bit_map  += (value % n_bits)/ 8;
   return(*bit_map & (0x1 << (value % 8))) ? 1 : 0;
}

void show_bits(char *bit_map, unsigned long n_bits)
{
   unsigned long bit_cnt = 0;
   unsigned char mask = 0x01;
   unsigned long ban_min, ban_max;

   if (n_bits == 1)  {
      printf("\nBits  0\n%d \n", *bit_map & 0x01);
      return;
   }
   
   /* Per Row max bits to display */
   ban_max = (n_bits > 32) ? 31: n_bits - 1;
   printf ("\nBits  0 --> %lu\n", ban_max);

   while (bit_cnt < n_bits) {
      printf("%d ", (*bit_map & mask)  ? 1:0);
      bit_cnt++;
      mask <<= 1;

      /* Every 8 bits put a spacer */
      if (!(bit_cnt % 8)) { 
         bit_map++; 
         mask = 0x01;
         printf (" ");
      }

      /* For 32 bits, addd a new line */
      if (!(bit_cnt % 32))  { 
        if (n_bits > bit_cnt) {
           ban_min = bit_cnt;
           ban_max = (bit_cnt + 32) > n_bits ? n_bits - 1: (bit_cnt + 31);
           printf ("\nBits %lu --> %lu\n", ban_min, ban_max);
        } else 
           printf ("\n");
      }
   }
   if (bit_cnt % 32) 
      printf ("\n");
}

int any_bit_set (unsigned char *dbg_flag, size_t n_bytes)
{
    while (n_bytes--)
       if (*dbg_flag++)
          return 1;
    return 0;
}


int main (void)
{
  unsigned char *bit_map    = NULL;
  unsigned long  n_bits       = 75;

  /*
   * Get enough bytes to hold all the bits of the num_dsl.
   */
  n_bytes = (n_bits + 7)/8;
  bit_map = (char *)malloc(n_bytes); 
  if (bit_map) 
     memset(bit_map, 0, n_bytes);
  else 
     return -1;
 
  /*
   * Set a few bit positions randomly to test the bits.
   */
  printf("Bit->Val:  0->%d 9->%d 13->%d 73->%d\n",
          test_bit(bit_map, 0), 
          test_bit(bit_map, 9), 
          test_bit(bit_map, 13), 
          test_bit(bit_map, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_map, n_bytes));

  set_bit(bit_map, 0);
  printf("Bit->Val:  0->%d 9->%d 13->%d 73->%d\n",
          test_bit(bit_map, 0), 
          test_bit(bit_map, 9), 
          test_bit(bit_map, 13), 
          test_bit(bit_map, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_map, n_bytes));

  set_bit(bit_map, 9);
  printf("Bit->Val:  0->%d 9->%d 13->%d 73->%d\n",
          test_bit(bit_map, 0), 
          test_bit(bit_map, 9), 
          test_bit(bit_map, 13), 
          test_bit(bit_map, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_map, n_bytes));

  set_bit(bit_map, 13);
  printf("Bit->Val:  0->%d 9->%d 13->%d 73->%d\n",
          test_bit(bit_map, 0), 
          test_bit(bit_map, 9), 
          test_bit(bit_map, 13), 
          test_bit(bit_map, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_map, n_bytes));

  set_bit(bit_map, 73);
  printf("Bit->Val:  0->%d 9->%d 13->%d 73->%d\n",
          test_bit(bit_map, 0), 
          test_bit(bit_map, 9), 
          test_bit(bit_map, 13), 
          test_bit(bit_map, 73)); 

  show_bits(bit_map, 1);
  show_bits(bit_map, n_bits);
  show_bits(bit_map, 72);

  clear_bit(bit_map, 0);

  printf("Bit->Val:  0->%d 9->%d 13->%d 73->%d\n",
          test_bit(bit_map, 0), 
          test_bit(bit_map, 9), 
          test_bit(bit_map, 13), 
          test_bit(bit_map, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_map, n_bytes));

  clear_bit(bit_map, 9);
  printf("Bit->Val:  0->%d 9->%d 13->%d 73->%d\n",
          test_bit(bit_map, 0), 
          test_bit(bit_map, 9), 
          test_bit(bit_map, 13), 
          test_bit(bit_map, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_map, n_bytes));

  clear_bit(bit_map, 13);
  printf("Bit->Val:  0->%d 9->%d 13->%d 73->%d\n",
          test_bit(bit_map, 0), 
          test_bit(bit_map, 9), 
          test_bit(bit_map, 13), 
          test_bit(bit_map, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_map, n_bytes));

  clear_bit(bit_map, 73);
  printf("Bit->Val:  0->%d 9->%d 13->%d 73->%d\n",
          test_bit(bit_map, 0), 
          test_bit(bit_map, 9), 
          test_bit(bit_map, 13), 
          test_bit(bit_map, 73)); 
  printf("Atleast one bit set ? %d\n", any_bit_set(bit_map, n_bytes));
	
  memset (bit_map, 0, n_bytes);
  set_n_bits (bit_map, n_bits);	
  printf("dsl 73 bit set ? %d\n", test_bit(bit_map, 73));
  printf("dsl 74 bit set ? %d\n", test_bit(bit_map, 74));
  printf("dsl 75 bit set ? %d\n", test_bit(bit_map, 75));
  printf("dsl 76 bit set ? %d\n", test_bit(bit_map, 76));
  printf("dsl 77 bit set ? %d\n", test_bit(bit_map, 77));
  printf("dsl 78 bit set ? %d\n", test_bit(bit_map, 78));
  printf("dsl 79 bit set ? %d\n", test_bit(bit_map, 79));
  printf("dsl 80 bit set ? %d\n", test_bit(bit_map, 80));
}

