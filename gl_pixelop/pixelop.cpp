#include <stdio.h>
#include <stdlib.h>
#include "glut/glut.h"
#pragma comment(lib, "glut32.lib")

#define USE_SIMPLE_GL_LIB 1
#include "../sgl_lib/sgl.h"
#pragma comment(lib, "sgl_lib.lib")

#define FILENAME "grab.bmp"

static GLint ImageWidth;
static GLint ImageHeight;
static GLint PixelLength;
static GLubyte* PixelData;

void
drawpixel() {
	
	// 图象宽度、图象高度、像素数据内容、像素数据在内存中的格式
	glDrawPixels(ImageWidth, ImageHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);
	// glDrawPixels函数比glReadPixels函数少了两个参数，这两个参数在glReadPixels中分别是表示图象的起始位置。在glDrawPixels中，不必显式的指定绘制的位置，这是因为绘制的位置是由另一个函数glRasterPos*来指定的。glRasterPos*函数的参数与glVertex*类似，通过指定一个二维/三维/四维坐标，OpenGL将自动计算出该坐标对应的屏幕位置，并把该位置作为绘制像素的起始位置。
}

void
copypixel() {
	// 绘制
	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f);     glVertex2f(0.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);     glVertex2f(1.0f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);     glVertex2f(0.5f, 1.0f);
	//glEnd();

	glPixelZoom(-0.5f, -0.5f);
	glRasterPos2i(1, 1); // 通过glRasterPos*系列函数来设置绘制的位置
	// 直接从像素数据复制出新的像素数据，避免了多余的数据的格式转换，并且也可能减少一些数据复制操作（因为数据可能直接由显卡负责复制，不需要经过主内存），因此效率比较高。
	// 第一、二个参数表示复制像素来源的矩形的左下角坐标，第三、四个参数表示复制像素来源的举行的宽度和高度，第五个参数通常使用GL_COLOR，表示复制像素的颜色，但也可以是GL_DEPTH或GL_STENCIL，分别表示复制深度缓冲数据或模板缓冲数据。
	glCopyPixels(0, 0, ImageWidth, ImageHeight, GL_COLOR);
}

void 
display() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawpixel();
	//glutSwapBuffers();

	copypixel();

	glutSwapBuffers();

	grab(0, 0, 400, 400);
}

int
main(int argc, char* argv[]) {
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, FILENAME, "rb");
	if(err != 0)
		return 0;

	fseek(pFile, 0x0012, SEEK_SET);
	fread(&ImageWidth, sizeof(ImageWidth), 1, pFile);
	fread(&ImageHeight, sizeof(ImageHeight), 1, pFile);

	PixelLength = ImageWidth * 3;
	PixelLength += (PixelLength%BMP_LINE_ALIGNMENT==0) ? 0 : (BMP_LINE_ALIGNMENT-ImageWidth%BMP_LINE_ALIGNMENT);

	PixelLength *= ImageHeight;

	PixelData = (GLubyte*)malloc(PixelLength);
	if(PixelData == 0)
		return 0;

	fseek(pFile, BMP_HEADER_LENGTH, SEEK_SET);
	fread(PixelData, PixelLength, 1, pFile);

	fclose(pFile);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("像素绘制及拷贝");
	glutDisplayFunc(&display);

	glutMainLoop();


	free(PixelData);
}