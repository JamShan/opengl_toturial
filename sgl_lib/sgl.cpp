#include "sgl.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


double cal_fps()
{
	static int frame = 0;
	static double fps = 0;
	static clock_t last = 0, current = clock();
	double timegap = 0;

	if(frame++ <= 50)
		return fps;

	frame = 0;

	last = current;
	current = clock();
	timegap = (current - last)/(double)CLK_TCK;
	fps = 50.0/timegap;

	return fps;
}

void grab(GLint x, GLint y, GLsizei width, GLsizei height) {
	FILE *pDummyFile;
	FILE *pWritingFile;

	GLubyte *pPixelData;
	GLubyte BMP_Header[BMP_HEADER_LENGTH];
	GLint i, j;
	GLint PixelDataLength;

	// 每行字节个数，默认会按4的倍数补齐
	i = width * 3;
	//while( i%4 != 0)
	//	++i;
	i += (4 - i%4);

	// 图像像素字节数
	PixelDataLength = i * height;

	// 分配内存和打开文件
	pPixelData = (GLubyte *)malloc(PixelDataLength);
	if(pPixelData == 0)
		return;

	errno_t err1 = fopen_s(&pDummyFile, "dummy.bmp", "rb");
	if(err1 != 0)
		return;

	errno_t err2 = fopen_s(&pWritingFile, "grab.bmp", "wb");
	if(err2 != 0)
		return;

	// 设置读取文件对齐字节
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	// 读取像素
	glReadPixels(x, y, width, height,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// 把dummy.bmp的文件头复制为新文件的文件头
	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = width;
	j = height;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
}