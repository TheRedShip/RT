#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

uint16_t swap_bits_uint16(uint16_t nb)
{
	return(nb << 8 | nb >> 8);
}

int main(void)
{
	uint16_t a=1880;
	printBits(sizeof(uint16_t), &a);
	uint16_t orig = htons(a);
	uint16_t ft = a << 8 | a >> 8; 
	printf("orig : ");
	printBits(sizeof(uint16_t), &orig);
	printf("ft   : ");
	printBits(sizeof(uint16_t), &ft);
}
