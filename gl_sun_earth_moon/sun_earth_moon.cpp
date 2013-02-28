#include <Windows.h>
#include "glut/glut.h"

#pragma comment(lib, "glut.lib")

static int day = 10;
static int frame = 0;

void mydisplay();
void dayafterday()
{
	do 
	{
		mydisplay();

		Sleep(500);

	} while (true);
}

void mydisplay()
{
	while(frame++ == 1)
	{
		frame = 0;
		day++;


		if(day == 361)
			day = 1;
	}

	// �����ӿ�
	glViewport(0, 200, 200, 200);

	// ������ȼ��
	glEnable(GL_DEPTH_TEST); // ������ȼ����Ȼ���������ƽ����ԭ����Ҫ�ȵ��ó�ʼ��glDepthFunc(GL_LEQUAL) 
	// ��ջ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	// ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 400000000); // ͸�����

	// ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);

	// ���ƺ�ɫ�ġ�̫����
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(69600000, 20, 20);

	// ����һ��
	// ������ɫ�ġ�����
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(150000000, 0.0f, 0.0f);
	glutSolidSphere(15945000, 40, 40);
	// ���ƻ�ɫ�ġ�������
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(38000000, 0.0f, 0.0f);
	glutSolidSphere(4345000, 20, 20);

	//// ��������
	//glPushMatrix();

	//// ������ɫ�ġ�����
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glRotatef(day/360.0*360.0, 0.0f, 0.0f, -1.0f);
	//glTranslatef(150000000, 0.0f, 0.0f);
	//glutSolidSphere(15945000, 40, 40);

	//glPopMatrix();

	//// ���ƻ�ɫ�ġ�������
	//glColor3f(1.0f, 1.0f, 0.0f);
	////glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 0.0f, -1.0f);

	//glTranslatef(38000000, 0.0f, 0.0f);
	//glutSolidSphere(4345000, 20, 20);


	glFlush();
}

int main(int argc, char *args[])
{
	glutInit(&argc, args);


	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowPosition(100, 100);

	glutInitWindowSize(400, 400);

	glutCreateWindow("̫��-����-����");

	/*
	glClearDepth only specifies what value is written to the depth buffer when the buffer is cleared. 
	The actual clearing is only performed when glClear is called.
	Anyways, the default depth test function is GL_LESS, not GL_LEQUAL. This could be an important difference, 
	as GL_LESS does not work well with multipass rendering for example. And 1.0 is the default depth clear value, 
	so no need to call glClearDepth unless you want another value. 
	*/
	// �����Ƚ������ã���������Ȳ��Ժ󣬿�����ģ��
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	glutDisplayFunc(&dayafterday);

	glutMainLoop();

	return 0;
}