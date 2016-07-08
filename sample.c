#include <stdio.h>
#include <stdint.h>
#include "bmp.h"

int main(int argc, char const *argv[])
{
	uint8_t matrix[768 * 3072];
	
	for (int j = 0; j < 768; j++) {
		for (int i = 0; i < 3072; i++) {
			if (i % 3 == 0) {
				matrix[i + (j * 3072)] = 0x00;
			} else {
				matrix[i + (j * 3072)] = 0xFF;
			}
		}
	}
	
	int status = write_bmp("test.bmp", 1024, 768, matrix);

	return 0;
}