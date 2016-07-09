#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "bmp.h"

int write_bmp (const char* filename, int width, int height, uint8_t* matrix) {

	int bytesPerRow = (3 * (width + 1) / 4) * 4;
	
	HEADER fh = {
		.bfType = 19778,
		.bfOffBits = 54,
		.bfSize = 54 + bytesPerRow * height,
		.bfReserved = 0,
		.biSize = 40,
		.biWidth = width,
		.biHeight = height,
		.biPlanes = 1,
		.biBitCount = 24,
		.biCompression = 0,
		.biSizeImage = bytesPerRow * height,
		.biXPelsPerMeter = 0,
		.biYPelsPerMeter = 0,
		.biClrUsed = 0,       
		.biClrImportant = 0, 
	};

	FILE* file = fopen (filename, "wb");
	if (file == NULL) return 0;
	
	fwrite(&fh, sizeof(HEADER), 1, file);
	
	uint8_t* row = (uint8_t*)malloc(bytesPerRow);
	if (row == NULL) return 0;

	for (int i = height - 1; i >= 0; i--) {
		
		for (int j = 0; j < width; j++) {

			int index = 3 * (width * i + j);
			row[3 * j] = matrix[index + 2];
			row[3 * j + 1] = matrix[index + 1];
			row[3 * j + 2] = matrix[index];
		}

		fwrite(row, bytesPerRow, 1, file);
	}

	free(row);
	fclose(file);
	return 1;
}