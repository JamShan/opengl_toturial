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

	// ÿ���ֽڸ�����Ĭ�ϻᰴ4�ı�������
	i = width * 3;
	//while( i%4 != 0)
	//	++i;
	i += (4 - i%4);

	// ͼ�������ֽ���
	PixelDataLength = i * height;

	// �����ڴ�ʹ��ļ�
	pPixelData = (GLubyte *)malloc(PixelDataLength);
	if(pPixelData == 0)
		return;

	errno_t err1 = fopen_s(&pDummyFile, "dummy.bmp", "rb");
	if(err1 != 0)
		return;

	errno_t err2 = fopen_s(&pWritingFile, "grab.bmp", "wb");
	if(err2 != 0)
		return;

	// ���ö�ȡ�ļ������ֽ�
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	// ��ȡ����
	glReadPixels(x, y, width, height,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// ��dummy.bmp���ļ�ͷ����Ϊ���ļ����ļ�ͷ
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