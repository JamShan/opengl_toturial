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
	
	// ͼ���ȡ�ͼ��߶ȡ������������ݡ������������ڴ��еĸ�ʽ
	glDrawPixels(ImageWidth, ImageHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, PixelData);
	// glDrawPixels������glReadPixels������������������������������glReadPixels�зֱ��Ǳ�ʾͼ�����ʼλ�á���glDrawPixels�У�������ʽ��ָ�����Ƶ�λ�ã�������Ϊ���Ƶ�λ��������һ������glRasterPos*��ָ���ġ�glRasterPos*�����Ĳ�����glVertex*���ƣ�ͨ��ָ��һ����ά/��ά/��ά���꣬OpenGL���Զ�������������Ӧ����Ļλ�ã����Ѹ�λ����Ϊ�������ص���ʼλ�á�
}

void
copypixel() {
	// ����
	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f);     glVertex2f(0.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);     glVertex2f(1.0f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);     glVertex2f(0.5f, 1.0f);
	//glEnd();

	glPixelZoom(-0.5f, -0.5f);
	glRasterPos2i(1, 1); // ͨ��glRasterPos*ϵ�к��������û��Ƶ�λ��
	// ֱ�Ӵ��������ݸ��Ƴ��µ��������ݣ������˶�������ݵĸ�ʽת��������Ҳ���ܼ���һЩ���ݸ��Ʋ�������Ϊ���ݿ���ֱ�����Կ������ƣ�����Ҫ�������ڴ棩�����Ч�ʱȽϸߡ�
	// ��һ������������ʾ����������Դ�ľ��ε����½����꣬�������ĸ�������ʾ����������Դ�ľ��еĿ�Ⱥ͸߶ȣ����������ͨ��ʹ��GL_COLOR����ʾ�������ص���ɫ����Ҳ������GL_DEPTH��GL_STENCIL���ֱ��ʾ������Ȼ������ݻ�ģ�建�����ݡ�
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
	glutCreateWindow("���ػ��Ƽ�����");
	glutDisplayFunc(&display);

	glutMainLoop();


	free(PixelData);
}