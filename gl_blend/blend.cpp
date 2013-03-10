#include <stdio.h>
#include "glut/glut.h"

#pragma comment(lib, "glut32.lib")

void my2dblend() {

	glBlendFunc(GL_ONE, GL_ZERO);
	glColor4f(1, 0, 0, 0.5);
	glRectf(-1, 0.6, -0.6, 1);
	glColor4f(0, 1, 0, 0.5);
	glRectf(-0.8, 0.6, -0.4, 1);

	// ����Դ���Ӻ�Ŀ������
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*
	GL_ZERO��      ��ʾʹ��0.0��Ϊ���ӣ�ʵ�����൱�ڲ�ʹ��������ɫ���������㡣
	GL_ONE��       ��ʾʹ��1.0��Ϊ���ӣ�ʵ�����൱����ȫ��ʹ����������ɫ���������㡣
	GL_SRC_ALPHA����ʾʹ��Դ��ɫ��alphaֵ����Ϊ���ӡ�
	GL_DST_ALPHA����ʾʹ��Ŀ����ɫ��alphaֵ����Ϊ���ӡ�
	GL_ONE_MINUS_SRC_ALPHA����ʾ��1.0��ȥԴ��ɫ��alphaֵ����Ϊ���ӡ�
	GL_ONE_MINUS_DST_ALPHA����ʾ��1.0��ȥĿ����ɫ��alphaֵ����Ϊ���ӡ�
	�������⣬����GL_SRC_COLOR����Դ��ɫ���ĸ������ֱ���Ϊ���ӵ��ĸ���������GL_ONE_MINUS_SRC_COLOR��GL_DST_COLOR��GL_ONE_MINUS_DST_COLOR��
	GL_CONST_COLOR���趨һ�ֳ�����ɫ�������ĸ������ֱ���Ϊ���ӵ��ĸ���������GL_ONE_MINUS_CONST_COLOR��GL_CONST_ALPHA��GL_ONE_MINUS_CONST_ALPHA�����⻹��GL_SRC_ALPHA_SATURATE���°汾��OpenGL��������ɫ��alphaֵ��RGBֵ���ò�ͬ�Ļ�����ӡ�
	*/
	glColor4f(1, 0, 0, 0.5); // �Ȼ��ģ�Ŀ����ɫ
	glRectf(-0.4, 0.6, 0, 1);
	glColor4f(0, 1, 0, 0.5); // �󻭵ģ�Դ��ɫ
	glRectf(-0.2, 0.6, 0.2, 1);


	glBlendFunc(GL_ONE, GL_ONE);
	glColor4f(1, 0, 0, 0.5);
	glRectf(0.2, 0.6, 0.6, 1);
	glColor4f(0, 1, 0, 0.5);
	glRectf(0.4, 0.6, 0.8, 1);
}

void
setLight() {
	static const GLfloat light_position[] = {1.0f, 1.0f, -1.0f, 1.0f};
	static const GLfloat light_ambient[]   = {0.2f, 0.2f, 0.2f, 1.0f};
	static const GLfloat light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
	static const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT,   light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,   light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void
setMatirial(const GLfloat mat_diffuse[4], GLfloat mat_shininess) {
	static const GLfloat mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
	static const GLfloat mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,   mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION,   mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, mat_shininess);
}

void
my3dblend() {
	// ����һЩ������ɫ
	const static GLfloat red_color[] = {1.0f, 0.0f, 0.0f, 1.0f};
	const static GLfloat green_color[] = {0.0f, 1.0f, 0.0f, 0.3333f};
	const static GLfloat blue_color[] = {0.0f, 0.0f, 1.0f, 0.5f};

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ���ù�Դ
	setLight();

	// ��(0, 0, 0.5)Ϊ���ģ�����һ���뾶Ϊ.3�Ĳ�͸����ɫ���壨��۲�����Զ��
	setMatirial(red_color, 30.0);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.5f);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();

	// ���潫���ư�͸�������ˣ���˽���Ȼ�������Ϊֻ��
	glDepthMask(GL_FALSE);
	/*
	��Ȼ���������һ�����ݣ�����¼��ÿһ�����ؾ���۲����ж������������Ȼ�����Ե�����£������Ҫ���Ƶ����ر�ԭ�������ظ����������ؽ������ơ��������ؾͻᱻ���Ե��������л��ơ����ڻ��Ʋ�͸��������ʱ�ǳ����á����������Ȼ��ƽ��������ٻ���Զ�����壬�����Ȼ���Զ�������ٻ��ƽ������壬���߸ɴ��Ի��ҵ�˳����л��ƣ�������ʾ������ǽ���������סԶ�����塣
	Ȼ��������Ҫʵ�ְ�͸��Ч��ʱ������һ�ж�������ô�����ˡ�����������һ��������İ�͸�����壬��������Ȼ������ڱ�����һЩ��Ϣ��ʹ��Զ�������彫�޷��ٱ����Ƴ�������Ȼ��͸����������Ȼ��͸������͸����������ȴ������ȷ�������ˡ�
	Ҫ����������⣬��Ҫ�ڻ��ư�͸������ʱ����Ȼ���������Ϊֻ��������һ������Ȼ��͸�����屻������ȥ�ˣ���Ȼ�������������ԭ����״̬���������һ����������ڰ�͸������֮���ڲ�͸������֮ǰ������Ҳ���Ա����ƣ���Ϊ��ʱ��Ȼ������м�¼�����Ǹ���͸���������ȣ����Ժ���Ҫ���Ʋ�͸������ʱ��ֻ��Ҫ�ٽ���Ȼ���������Ϊ�ɶ���д����ʽ���ɡ�
	*/
	// ����Ȼ���һ����͸�������壬�����䱳����ư�͸�����壬��������İ�͸�����彫���ᱻ��ʾ������͸����������ס�ˣ��������������Ȼ��壬������Ȼ������ʾ�������л�ϡ�

	// ��(0.2, 0, -0.5)Ϊ���ģ�����һ���뾶Ϊ.2�İ�͸����ɫ���壨��۲��������
	setMatirial(blue_color, 30.0);
	glPushMatrix();
	glTranslatef(0.2f, 0.0f, -0.5f);
	glutSolidSphere(0.2, 30, 30);
	glPopMatrix();

	// ��(0.1, 0, 0)Ϊ���ģ�����һ���뾶Ϊ.15�İ�͸����ɫ���壨��ǰ��������֮�䣩
	setMatirial(green_color, 30.0);
	glPushMatrix();
	glTranslatef(0.1, 0, 0);
	glutSolidSphere(0.15, 30, 30);
	glPopMatrix();

	// ��ɰ�͸������Ļ��ƣ�����Ȼ������ָ�Ϊ�ɶ���д����ʽ
	glDepthMask(GL_TRUE);
}

void
myblend() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND); // ������Ϲ��ܡ�
	// ע�⣺ֻ����RGBAģʽ�£��ſ���ʹ�û�Ϲ��ܣ���ɫ����ģʽ�����޷�ʹ�û�Ϲ��ܵġ�

	my2dblend();

	my3dblend();

	glutSwapBuffers();
}


int
main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("�����Ⱦ");
	glutDisplayFunc(&myblend);
	glutMainLoop();
	return 0;
}