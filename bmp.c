#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "bmp.h"

int write_bmp (const char* filename, int width, int height, uint8_t* matrix) {

	int bytesPerRow = (3 * (width + 1) / 4) * 4;
	
	HEADER fh;
    strcpy(fh.bfType, "BM");
    fh.bfOffBits = 54;
    fh.bfSize = fh.bfOffBits + bytesPerRow * height;
    fh.bfReserved = 0;
    fh.biSize = 40;
    fh.biWidth = width;
    fh.biHeight = height;
    fh.biPlanes = 1;
    fh.biBitCount = 24;
    fh.biCompression = 0;
    fh.biSizeImage = bytesPerRow * height;
    fh.biXPelsPerMeter = 0;
    fh.biYPelsPerMeter = 0;
    fh.biClrUsed = 0;       
    fh.biClrImportant = 0; 

    FILE* file = fopen (filename, "wb");
    if (file == NULL) return 0;
  
    fwrite(&fh.bfType, 2, 1, file);
    fwrite(&fh.bfSize, 4, 1, file);
    fwrite(&fh.bfReserved, 4, 1, file);
    fwrite(&fh.bfOffBits, 4, 1, file);
    fwrite(&fh.biSize, 4, 1, file);
    fwrite(&fh.biWidth, 4, 1, file);
    fwrite(&fh.biHeight, 4, 1, file);
    fwrite(&fh.biPlanes, 2, 1, file);
    fwrite(&fh.biBitCount, 2, 1, file);
    fwrite(&fh.biCompression, 4, 1, file);
    fwrite(&fh.biSizeImage, 4, 1, file);
    fwrite(&fh.biXPelsPerMeter, 4, 1, file);
    fwrite(&fh.biYPelsPerMeter, 4, 1, file);
    fwrite(&fh.biClrUsed, 4, 1, file);
    fwrite(&fh.biClrImportant, 4, 1, file);

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