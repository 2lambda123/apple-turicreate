//
// gettsc.inl
//
// gives access to the Pentium's (secret) cycle counter
//
// This software was written by Leonard Janke (janke@unixg.ubc.ca)
// in 1996-7 and is entered, by him, into the public domain.

#if defined(__WATCOMC__)
void GetTSC(unsigned long&);
#pragma aux GetTSC = 0x0f 0x31 "mov [edi], eax" parm [edi] modify [edx eax];
#elif defined(__GNUC__)
inline
void GetTSC(unsigned long& tsc)
{
  asm volatile(".byte 15, 49\n\t"
	       : "=eax" (tsc)
	       :
	       : "%edx", "%eax");
}
#elif defined(_MSC_VER)
inline
void GetTSC(unsigned long& tsc)
{
  unsigned long a;
  __asm _emit 0fh
  __asm _emit 31h
  __asm mov a, eax;
  tsc=a;
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include <openssl/des.h>

void main(int argc,char *argv[])
	{
	des_key_schedule key;
	unsigned long s1,s2,e1,e2;
	unsigned long data[2];
	int i,j;

	for (j=0; j<6; j++)
		{
		for (i=0; i<1000; i++) /**/
			{
			des_encrypt1(&data[0],key,1);
			GetTSC(s1);
			des_encrypt1(&data[0],key,1);
			des_encrypt1(&data[0],key,1);
			des_encrypt1(&data[0],key,1);
			GetTSC(e1);
			GetTSC(s2);
			des_encrypt1(&data[0],key,1);
			des_encrypt1(&data[0],key,1);
			des_encrypt1(&data[0],key,1);
			des_encrypt1(&data[0],key,1);
			GetTSC(e2);
			des_encrypt1(&data[0],key,1);
			}

		printf("des %d %d (%d)\n",
			e1-s1,e2-s2,((e2-s2)-(e1-s1)));
		}
	}
