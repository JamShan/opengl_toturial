#include <math.h>
#include "glut/glut.h"

#pragma comment(lib, "glut32.lib")

const int n = 20;
const GLfloat R = 0.1f;
const GLfloat Pi = 3.1415926536f;
const GLfloat factor = 0.1f;

void drawrect()
{
	// ��һ�����Ρ��ĸ������ֱ��ʾ��λ�ڶԽ����ϵ�������ĺᡢ�����ꡣ
	// ��������Ϊԭ�㣬����ֵ���ǹ�һ���

	// 1. RGBA��ɫ	
	/*
	ע�⣺glColorϵ�к������ڲ������Ͳ�ͬʱ����ʾ�������ɫ��ֵҲ��ͬ��
	����f��d����׺�ĺ�������1.0��ʾ����ʹ�á�
	����b����׺�ĺ�������127��ʾ����ʹ�á�
	����ub����׺�ĺ�������255��ʾ����ʹ�á�
	����s����׺�ĺ�������32767��ʾ����ʹ�á�
	����us����׺�ĺ�������65535��ʾ����ʹ�á�
	*/
	glColor3f(0.0f, 1.0f, 1.0f);	// RGBAģʽ ����������Ϊ����������0.0��ʾ��ʹ�ø�����ɫ����1.0��ʾ��������ɫ�õ����
	glRectf(-0.9f, 0.81f, -0.8f, 0.9f);

	glColor3f(1.0f, 1.0f, 1.0f);
	// 2. ������ɫ
	glutSetColor(0, 1.0f, 0.0f, 0.0f); // ������ɫ�������ã���������ҪglutInitDisplayMode����������ɫģʽ
	glutSetColor(1, 0.0f, 1.0f, 0.0f);
	glutSetColor(2, 0.0f, 0.0f, 1.0f);

	glIndexi(0);
	glRectf(-0.9f, 0.71f, -0.8f, 0.8f);
	glIndexi(2);
	glRectf(-0.9f, 0.61f, -0.8f, 0.7f);

	// 3. ָ�������Ļ�õ���ɫ
	//glRectf(-0.9f, 0.51f, -0.8f, 0.6f);
	// 4. ָ����ɫģ��
	glRectf(-0.9f, 0.41f, -0.8f, 0.5f);

	glColor3f(1.0f, 1.0f, 1.0f);

	
	// glEnable(GL_CULL_FACE);�������޳����ܣ�ʹ��glDisable(GL_CULL_FACE)���Թر�֮��
	// ʹ��glCullFace�������޳���	glCullFace�Ĳ���������GL_FRONT��GL_BACK����GL_FRONT_AND_BACK���ֱ��ʾ�޳����桢�޳����桢�޳���������Ķ���Ρ�
	// ע�⣺�޳�����ֻӰ�����Σ����Ե��ֱ����Ӱ�졣���磬ʹ��glCullFace(GL_FRONT_AND_BACK)�����еĶ���ζ������޳������Կ����ľ�ֻ�е��ֱ��

	//	ʹ��glEnable(GL_POLYGON_STIPPLE);�������ο�ģʽ��ʹ��glDisable(GL_POLYGON_STIPPLE)���Թر�֮����
	//  Ȼ��ʹ��glPolygonStipple�������οյ���ʽ��
	//	void glPolygonStipple(const GLubyte *mask);
	static GLubyte Mask[128] =
	{

		0x00, 0x00, 0x00, 0x00,    //   �����������һ��
		0x00, 0x00, 0x00, 0x00,
		0x03, 0x80, 0x01, 0xC0,    //   ��
		0x06, 0xC0, 0x03, 0x60,    //   ��
		0x04, 0x60, 0x06, 0x20,    //   ��
		0x04, 0x30, 0x0C, 0x20,    //   ��
		0x04, 0x18, 0x18, 0x20,    //   ʼ
		0x04, 0x0C, 0x30, 0x20,    //   ��
		0x04, 0x06, 0x60, 0x20,    //   ��
		0x44, 0x03, 0xC0, 0x22,    //   ��
		0x44, 0x01, 0x80, 0x22,    //   ��
		0x44, 0x01, 0x80, 0x22,    //   ��
		0x44, 0x01, 0x80, 0x22,    //   ʹ
		0x44, 0x01, 0x80, 0x22,    //   ��
		0x44, 0x01, 0x80, 0x22,
		0x44, 0x01, 0x80, 0x22,
		0x66, 0x01, 0x80, 0x66,
		0x33, 0x01, 0x80, 0xCC,
		0x19, 0x81, 0x81, 0x98,
		0x0C, 0xC1, 0x83, 0x30,
		0x07, 0xE1, 0x87, 0xE0,
		0x03, 0x3F, 0xFC, 0xC0,
		0x03, 0x31, 0x8C, 0xC0,
		0x03, 0x3F, 0xFC, 0xC0,
		0x06, 0x64, 0x26, 0x60,
		0x0C, 0xCC, 0x33, 0x30,
		0x18, 0xCC, 0x33, 0x18,
		0x10, 0xC4, 0x23, 0x08,
		0x10, 0x63, 0xC6, 0x08,
		0x10, 0x30, 0x0C, 0x08,
		0x10, 0x18, 0x18, 0x08,
		0x10, 0x00, 0x00, 0x08    // �����������һ��
	};
	/*
	����һ�����ݷǳ�ȱ��ֱ���ԣ�������Ҫ�ܷѾ���ȥ�������Żᷢ������ʾ�ľ�Ȼ��һֻ��Ӭ��
	��������������ݱ����ͼƬ������ר�ŵĹ��߽��б༭����Ȼ�᷽��ܶࡣ����������������һ�㡣
	���ȣ���Windows�Դ��Ļ��ʳ����½�һ��ͼƬ��ȡ��Ϊmask.bmp��ע�Ᵽ��ʱ��Ӧ��ѡ�񡰵�ɫλͼ�����ڡ�ͼ��->�����ԡ��Ի����У�����ͼƬ�ĸ߶ȺͿ�Ⱦ�Ϊ32��
	�÷Ŵ󾵹۲�ͼƬ�����༭֮����ɫ��Ӧ�������㣨�οգ�����ɫ��Ӧ������һ�����οգ����༭��Ϻ󱣴档
	Ȼ�󣬾Ϳ���ʹ�����´�����������Mask�����ˡ�

	static GLubyte Mask[128];
	FILE *fp;
	fp = fopen("mask.bmp", "rb");
	if( !fp )
	exit(0);
	// �ƶ��ļ�ָ�뵽���λ�ã�ʹ���ٶ�sizeof(Mask)���ֽھͻ������ļ�����
	// ע��-(int)sizeof(Mask)��Ȼ����ʲô�õ�д������������ȷʵ����ȷ��Ч��
	// ���ֱ��д-sizeof(Mask)�Ļ�����Ϊsizeofȡ�õ���һ���޷�������ȡ���Ż�������

	if( fseek(fp, -(int)sizeof(Mask), SEEK_END) )
	exit(0);

	// ��ȡsizeof(Mask)���ֽڵ�Mask
	if( !fread(Mask, sizeof(Mask), 1, fp) )
	exit(0);
	fclose(fp);
	*/
	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(Mask);
	glRectf(-0.5f, -0.5f, 0.0f, 0.0f);   // �����·�����һ�����ο�Ч����������

	glDisable(GL_POLYGON_STIPPLE);
	glRectf(0.0f, 0.0f, 0.5f, 0.5f);     // �����Ϸ�����һ�����ο�Ч����������
	
}

void drawpoint()
{
	glPointSize(5.0f);	// size�������0.0f��Ĭ��ֵΪ1.0f����λΪ�����ء�  ��Ĵ�С���и��޶ȵģ�������õ�size�������ֵ�������ÿ��ܻ�������
	glBegin(GL_POINTS); // GL_POINT ��Ȼ��������
	glVertex2f(0.1f, 0.1f);
	glEnd();

	glPointSize(1.0f);
}

void drawline()
{
	glLineWidth(2.0f);
	glBegin(GL_LINES);	// GL_LINE ��Ȼ��������
		glVertex2f(0.3f, 0.3f);
		glVertex2f(0.5f, 0.5f);
	glEnd();

	glLineWidth(1.0f);

	glEnable(GL_LINE_STIPPLE); // ����������ģʽ��ʹ��glDisable(GL_LINE_STIPPLE)���Թر�֮��
	glLineStipple(1, 0x00ff);
	glBegin(GL_LINES);	// GL_LINE ��Ȼ��������
	glVertex2f(0.2f, 0.2f);
	glVertex2f(0.3f, 0.3f);
	glEnd();

	glDisable(GL_LINE_STIPPLE);
}

void drawpolygon()
{
	int i;
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glBegin(GL_POLYGON);
	for (i=0; i<n; ++i)
	{
		glVertex2f(R * cos(2*Pi/n*i) - 0.7, R * sin(2*Pi/n*i) + 0.9);
	}
	glEnd();


	glBegin(GL_POLYGON);
	for (i=n-1; i>=0; i--)
	{
		glVertex2f(R * cos(2*Pi/n*i) - 0.5, R * sin(2*Pi/n*i) + 0.9);
	}
	glEnd();


	glFrontFace(GL_CW);	// ����˳ʱ�뷽��Ϊ����
	glBegin(GL_POLYGON);
	for (i=0; i<n; ++i)
	{
		glVertex2f(R * cos(2*Pi/n*i) - 0.3, R * sin(2*Pi/n*i) + 0.9);
	}
	glEnd();


	glBegin(GL_POLYGON);
	for (i=n-1; i>=0; i--)
	{
		glVertex2f(R * cos(2*Pi/n*i) - 0.1, R * sin(2*Pi/n*i) + 0.9);
	}
	glEnd();


	glFrontFace(GL_CCW);	// ������ʱ�뷽��Ϊ����

}

/*
������ǵ��������ֲ�λ�ù�ϵ���£�
      A
  E        B

    D    C
���ȣ��������Ҷ����з��̣���������ǵ����ĵ�����ľ���a
����������Ƕ�Ӧ������εı߳�Ϊ.0��
a = 1 / (2-2*cos(72*Pi/180));
Ȼ�󣬸������Һ����ҵĶ��壬����B��x����bx��y����by���Լ�C��y����
����������ǵ�����������ԭ�㣩
bx = a * cos(18 * Pi/180);
by = a * sin(18 * Pi/180);
cy = -a * cos(18 * Pi/180);
����������Ϳ���ͨ�������ĸ�����һЩ�����򵥵ı�ʾ����
*/
void draw5star()
{

	GLfloat a = 1 / (2-2*cos(72*Pi/180));
	GLfloat bx = a * cos(18 * Pi/180);
	GLfloat by = a * sin(18 * Pi/180);
	GLfloat cy = -a * cos(18 * Pi/180);
	GLfloat
		PointA[2] = { 0, a },
		PointB[2] = { bx, by },
		PointC[2] = { 0.5, cy },
		PointD[2] = { -0.5, cy },
		PointE[2] = { -bx, by };
	// ����A->C->E->B->D->A��˳�򣬿���һ�ʽ�����ǻ���
	glBegin(GL_LINE_LOOP);
	glVertex2fv(PointA);
	glVertex2fv(PointC);
	glVertex2fv(PointE);
	glVertex2fv(PointB);
	glVertex2fv(PointD);
	glEnd();

}

	/*
	����OpenGLĬ������ֵֻ�ܴ�-1��1���������޸ģ������������Ժ󽲣�
	������������һ������factor�������е�����ֵ�ȱ�����С��
	�����Ϳ��Ի����������������
	���޸�factor��ֵ���۲�仯���
	*/
void drawsin()
{

	GLfloat x;
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);         // ������������Ի�x��
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);         // ������������Ի�y��
	glEnd();
	glBegin(GL_LINE_STRIP);
	for(x=-1.0f/factor; x<1.0f/factor; x+=0.01f)
	{
		glVertex2f(x*factor, sin(x)*factor);
	}
	glEnd();
}

void drawtriangle()
{
	int i;

	/*
	��Ĭ������£�OpenGL��������㶥��֮��������㣬��Ϊ�������ϡ����ʡ�����ɫ��ʹ���ڵĵ����ɫֵ���ȽϽӽ������ʹ�õ���RGBģʽ���������;��н����Ч���������ʹ����ɫ����ģʽ���������ڵ������ֵ�ǽӽ��ģ��������ɫ���нӽ��������óɽӽ�����ɫ��������Ҳ�ǽ����Ч�����������ɫ���нӽ�������ɫȴ���ܴ������������Ǻ���ֵ�Ч����
	ʹ��glShadeModel�������Թر����ּ��㣬����������ɫ��ͬ���򽫶���֮���������ȫ������Ϊ��ĳһ������ͬ����ֱ���Ժ�ָ���ĵ����ɫΪ׼��������ν������ⶥ�����ɫΪ׼����ʵ�־�������Ϊ�˱��������ȷ���ԣ������ڶ������ʹ��ͬһ����ɫ��
	glShadeModel��ʹ�÷�����
	glShadeModel(GL_SMOOTH);    // ƽ����ʽ����Ҳ��Ĭ�Ϸ�ʽ
	glShadeModel(GL_FLAT);      // ��ɫ��ʽ
	*/
	// glShadeModel(GL_FLAT);
	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.8f, 0.3f);
	for(i=0; i<=8; ++i)
	{
		glColor3f(i&0x04, i&0x02, i&0x01);
		glVertex2f(0.1 * cos(i*Pi/4) - 0.8, 0.1 * sin(i*Pi/4) + 0.3);
	}
	glEnd();


	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.8f, 0.1f);
	for(i=0; i<=8; ++i)
	{
		glColor3f(i&0x04, i&0x02, i&0x01);
		glVertex2f(0.1 * cos(i*Pi/4) - 0.8, 0.1 * sin(i*Pi/4) + 0.1);
	}
	glEnd();
}

void myDisplay(void)
{
	// �����GL_COLOR_BUFFER_BIT��ʾ�����ɫ
	/*
	��RGBģʽ�£�ʹ��glClearColor��ָ�����ա�����ɫ������Ҫ�ĸ�������������������glColor4f���ơ�
	��������ɫģʽ�£�ʹ��glClearIndex��ָ�����ա�����ɫ���ڵ�����������Ҫһ���������������glIndexi���ơ�
	*/
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT);

	drawrect();

	drawpoint();

	drawline();

	drawpolygon();
	
	draw5star();

	drawsin();

	drawtriangle();

	//��֤ǰ���OpenGL��������ִ�У��������������ڻ������еȴ����������ø�fflush(stdout)���ơ�
	glFlush();

}

int main(int argc, char *argv[])

{
	// ��GLUT���г�ʼ�����������������������GLUTʹ��֮ǰ����һ��
	glutInit(&argc, argv);
	// ������ʾ��ʽ������GLUT_RGB��ʾʹ��RGB��ɫ����֮��Ӧ�Ļ���GLUT_INDEX����ʾʹ��������ɫ����GLUT_SINGLE��ʾʹ�õ����壬��֮��Ӧ�Ļ���GLUT_DOUBLE��ʹ��˫���壩
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowPosition(100, 100);

	glutInitWindowSize(400, 400);

	glutCreateWindow("��һ��OpenGL����");

	glutDisplayFunc(&myDisplay);

	glutMainLoop();

	return 0;

}