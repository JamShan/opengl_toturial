#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include "glut/glut.h"

#pragma comment(lib, "glut.lib")

static int day = 10;
static int frame = 0;

// #define SINGLE_MODE

void mydisplay();
void dayafterday()
{
	do 
	{
		while(frame++ == 1)
		{
			frame = 0;
			day++;


			if(day == 361)
				day = 1;
		}

		mydisplay();

		Sleep(500);

	} while (true);
}

void displaywhenidle()
{
	day++;
	if(day==360)
		day = 1;

	mydisplay();
}

double calfrequence()
{
	static int count = 0;
	static double fps = 0;
	static clock_t last = 0, current = clock();
	double timegap = 0;

	if(count++ <= 50)
		return fps;

	count = 0;

	last = current;
	current = clock();
	timegap = (current - last)/(double)CLK_TCK;
	fps = 50.0/timegap;

	return fps;
}

void mydisplay()
{
#ifndef SINGLE_MODE
	double fps = calfrequence();
	printf("FPS: %f\n", fps);
#endif

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

#ifndef SINGLE_MODE
	glutSwapBuffers();
#endif
}

int main(int argc, char *args[])
{
	glutInit(&argc, args);

#ifdef SINGLE_MODE
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
#else
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
#endif


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

#ifdef SINGLE_MODE
	glutDisplayFunc(&dayafterday);
#else
	glutDisplayFunc(&mydisplay);
	glutIdleFunc(&displaywhenidle);
#endif


	glutMainLoop();

	return 0;
}