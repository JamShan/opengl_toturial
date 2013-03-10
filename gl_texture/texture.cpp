#include "glut/glut.h"
#pragma comment(lib, "glut.lib")

#define USE_SIMPLE_GL_LIB 1
#include "../sgl_lib/sgl.h"
#pragma comment(lib, "sgl_lib.lib")

/* �����������ı��
*/
GLuint texGround;
GLuint texWall;

void display(void)
{
	// �����Ļ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �����ӽ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 5, 5, 0, 0, 0, 0, 0, 1);

	// ʹ�á��ء������������
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -8.0f, 0.0f);
	glTexCoord2f(0.0f, 5.0f); glVertex3f(-8.0f, 8.0f, 0.0f);
	glTexCoord2f(5.0f, 5.0f); glVertex3f(8.0f, 8.0f, 0.0f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f);
	glEnd();
	// ʹ�á�ǽ���������դ��
	glBindTexture(GL_TEXTURE_2D, texWall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	// ��ת���ٻ���һ��
	glRotatef(-90, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	// �������������������������ݵ��ļ�
	glutSwapBuffers();
	grab(0, 0, 400, 400);
}

int main(int argc, char* argv[])
{
	// GLUT��ʼ��
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("����");
	glutDisplayFunc(&display);

	// ��������һЩ��ʼ��
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	texGround = load_texture("ground.bmp");
	texWall = load_texture("wall.bmp");

	// ��ʼ��ʾ
	glutMainLoop();

	return 0;
}