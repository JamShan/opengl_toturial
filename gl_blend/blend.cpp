#include <stdio.h>
#include "glut/glut.h"

#pragma comment(lib, "glut32.lib")

void my2dblend() {

	glBlendFunc(GL_ONE, GL_ZERO);
	glColor4f(1, 0, 0, 0.5);
	glRectf(-1, 0.6, -0.6, 1);
	glColor4f(0, 1, 0, 0.5);
	glRectf(-0.8, 0.6, -0.4, 1);

	// 设置源因子和目标因子
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*
	GL_ZERO：      表示使用0.0作为因子，实际上相当于不使用这种颜色参与混合运算。
	GL_ONE：       表示使用1.0作为因子，实际上相当于完全的使用了这种颜色参与混合运算。
	GL_SRC_ALPHA：表示使用源颜色的alpha值来作为因子。
	GL_DST_ALPHA：表示使用目标颜色的alpha值来作为因子。
	GL_ONE_MINUS_SRC_ALPHA：表示用1.0减去源颜色的alpha值来作为因子。
	GL_ONE_MINUS_DST_ALPHA：表示用1.0减去目标颜色的alpha值来作为因子。
	除此以外，还有GL_SRC_COLOR（把源颜色的四个分量分别作为因子的四个分量）、GL_ONE_MINUS_SRC_COLOR、GL_DST_COLOR、GL_ONE_MINUS_DST_COLOR等
	GL_CONST_COLOR（设定一种常数颜色，将其四个分量分别作为因子的四个分量）、GL_ONE_MINUS_CONST_COLOR、GL_CONST_ALPHA、GL_ONE_MINUS_CONST_ALPHA。另外还有GL_SRC_ALPHA_SATURATE。新版本的OpenGL还允许颜色的alpha值和RGB值采用不同的混合因子。
	*/
	glColor4f(1, 0, 0, 0.5); // 先画的，目标颜色
	glRectf(-0.4, 0.6, 0, 1);
	glColor4f(0, 1, 0, 0.5); // 后画的，源颜色
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
	// 定义一些材质颜色
	const static GLfloat red_color[] = {1.0f, 0.0f, 0.0f, 1.0f};
	const static GLfloat green_color[] = {0.0f, 1.0f, 0.0f, 0.3333f};
	const static GLfloat blue_color[] = {0.0f, 0.0f, 1.0f, 0.5f};

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 设置光源
	setLight();

	// 以(0, 0, 0.5)为中心，绘制一个半径为.3的不透明红色球体（离观察者最远）
	setMatirial(red_color, 30.0);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.5f);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();

	// 下面将绘制半透明物体了，因此将深度缓冲设置为只读
	glDepthMask(GL_FALSE);
	/*
	深度缓冲是这样一段数据，它记录了每一个像素距离观察者有多近。在启用深度缓冲测试的情况下，如果将要绘制的像素比原来的像素更近，则像素将被绘制。否则，像素就会被忽略掉，不进行绘制。这在绘制不透明的物体时非常有用——不管是先绘制近的物体再绘制远的物体，还是先绘制远的物体再绘制近的物体，或者干脆以混乱的顺序进行绘制，最后的显示结果总是近的物体遮住远的物体。
	然而在你需要实现半透明效果时，发现一切都不是那么美好了。如果你绘制了一个近距离的半透明物体，则它在深度缓冲区内保留了一些信息，使得远处的物体将无法再被绘制出来。虽然半透明的物体仍然半透明，但透过它看到的却不是正确的内容了。
	要解决以上问题，需要在绘制半透明物体时将深度缓冲区设置为只读，这样一来，虽然半透明物体被绘制上去了，深度缓冲区还保持在原来的状态。如果再有一个物体出现在半透明物体之后，在不透明物体之前，则它也可以被绘制（因为此时深度缓冲区中记录的是那个不透明物体的深度）。以后再要绘制不透明物体时，只需要再将深度缓冲区设置为可读可写的形式即可。
	*/
	// 如果先绘制一个不透明的物体，再在其背后绘制半透明物体，本来后面的半透明物体将不会被显示（被不透明的物体遮住了），但如果禁用深度缓冲，则它仍然将会显示，并进行混合。

	// 以(0.2, 0, -0.5)为中心，绘制一个半径为.2的半透明蓝色球体（离观察者最近）
	setMatirial(blue_color, 30.0);
	glPushMatrix();
	glTranslatef(0.2f, 0.0f, -0.5f);
	glutSolidSphere(0.2, 30, 30);
	glPopMatrix();

	// 以(0.1, 0, 0)为中心，绘制一个半径为.15的半透明绿色球体（在前两个球体之间）
	setMatirial(green_color, 30.0);
	glPushMatrix();
	glTranslatef(0.1, 0, 0);
	glutSolidSphere(0.15, 30, 30);
	glPopMatrix();

	// 完成半透明物体的绘制，将深度缓冲区恢复为可读可写的形式
	glDepthMask(GL_TRUE);
}

void
myblend() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND); // 开启混合功能。
	// 注意：只有在RGBA模式下，才可以使用混合功能，颜色索引模式下是无法使用混合功能的。

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
	glutCreateWindow("深度渲染");
	glutDisplayFunc(&myblend);
	glutMainLoop();
	return 0;
}