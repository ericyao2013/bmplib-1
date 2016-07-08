#ifndef BMP_H
#define BMP_H

typedef struct BITMAP_HEADER {
	char bfType[2];
	uint32_t bfSize;
	uint16_t bfReserved;
	uint32_t bfOffBits;
	uint32_t biSize;
	uint32_t biWidth;
	uint32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	uint32_t biXPelsPerMeter;
	uint32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
} HEADER;

int write_bmp (const char* filename, int width, int height, uint8_t* matrix);

#endif 