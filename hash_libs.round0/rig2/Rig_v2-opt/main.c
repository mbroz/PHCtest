/*
	Implementation of the 'Rig' Password Hashing Scheme
	September 25, 2014
	Author: Arpan Jati (arpanj@iiitd.ac.in)
	Rig : v2.0
*/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "blake_impl.h"
#include "rig.h"


void ShowUsage()
{
	printf("\n Usage \n ");
	printf("\n rig [password] [salt] [m_cost] [t_cost] \n ");

	exit(1);
}

void PrintHash(const char* String, unsigned char* Hash)
{
	int k;
	printf("\n %s \n ", String);
	for (k = 0; k < 64; k++)
	{
		printf("%02X", Hash[k]);
		if (((k + 1) % 8) == 0) printf(" ");
	}
	printf("\n");
}


int main(int argc, char *argv[])
{
	int i=0, j=0, k=0, l=0;

	if(argc != 5)
	{
		ShowUsage();
	}

	char* pass = argv[1];
	char* salt =  argv[2];

	int m_cost = atoi(argv[3]);
	int t_cost = atoi(argv[4]);

	double MS_EL = 0;

	unsigned char Hash[64];

	printf("\n Password : %s", pass );
	printf("\n salt : %s", salt );
	printf("\n m_cost : %d", m_cost );
	printf("\n t_cost : %d", t_cost );

	PHS(Hash, 64, (unsigned char *)pass, strlen(pass), (unsigned char*)salt, 
			strlen(salt), t_cost, m_cost);

	PrintHash("\n\n Hash : ", Hash);

	//getchar();

	return 0;
}

/*
----------------------------
| PERFORMANCE TEST RESULTS |
----------------------------

GCC v4.9.1 (CFLAGS=-std=c99 -mavx2 -O3 -funroll-loops)

CPU: Intel Core i7 4770 (Turbo Boost: ON)
RAM: Double Channel DDR3 16 GB (2400 MHz)

OS: UBUNTU 14.04.1, on HYPER-V, on WIN-8

----------------------------------------------------------------------------------
|   2) RIG [BlakeExpand, BlakePerm, Blake2b] - Memory Hashing Speed (MiB/s)      |
----------------------------------------------------------------------------------
| M =>   |  8 M  |  16 M |  32 M |  64 M | 128 M | 256 M | 512 M | 1 GiB | 2 GiB |
----------------------------------------------------------------------------------
| mc =>  |     9 |    10 |    11 |    12 |    13 |    14 |    15 |    16 |    17 |
----------------------------------------------------------------------------------
| n =  1 |  1712 |  1724 |  1812 |  1868 |  1804 |  1840 |  1821 |  1820 |  1822 |
| n =  2 |  1450 |  1362 |  1377 |  1345 |  1307 |  1326 |  1315 |  1312 |  1318 |
| n =  4 |   932 |   873 |   858 |   846 |   829 |   845 |   835 |   838 |   833 |
| n =  6 |   657 |   621 |   621 |   621 |   617 |   618 |   606 |   610 |   619 |
| n =  8 |   500 |   477 |   500 |   485 |   481 |   490 |   485 |   489 |   489 |
| n = 10 |   428 |   397 |   403 |   398 |   399 |   402 |   404 |   404 |   402 |
----------------------------------------------------------------------------------
|   Memory Bandwidth (GiB/s)                                                     |
----------------------------------------------------------------------------------
| n =  1 | 5.021 | 5.055 | 5.312 | 5.477 | 5.290 | 5.394 | 5.340 | 5.337 | 5.342 |
| n =  2 | 7.088 | 6.658 | 6.728 | 6.575 | 6.389 | 6.478 | 6.429 | 6.412 | 6.439 |
| n =  4 | 8.202 | 7.683 | 7.547 | 7.441 | 7.295 | 7.431 | 7.347 | 7.374 | 7.329 |
| n =  6 | 8.354 | 7.889 | 7.888 | 7.898 | 7.847 | 7.858 | 7.709 | 7.750 | 7.873 |
| n =  8 | 8.315 | 7.935 | 8.309 | 8.070 | 8.003 | 8.152 | 8.072 | 8.123 | 8.126 |
| n = 10 | 8.788 | 8.146 | 8.282 | 8.179 | 8.205 | 8.251 | 8.291 | 8.293 | 8.265 |
----------------------------------------------------------------------------------

Memory allocation overhead is a significant reason towards the increasing trends
on the bandwidth data with 'n'.

*/




