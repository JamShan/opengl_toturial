#include <math.h>
#include "glut/glut.h"

#pragma comment(lib, "glut32.lib")

const int n = 20;
const GLfloat R = 0.1f;
const GLfloat Pi = 3.1415926536f;
const GLfloat factor = 0.1f;

void drawrect()
{
	// 画一个矩形。四个参数分别表示了位于对角线上的两个点的横、纵坐标。
	// 窗口中心为原点，坐标值都是归一后的

	// 1. RGBA颜色	
	/*
	注意：glColor系列函数，在参数类型不同时，表示“最大”颜色的值也不同。
	采用f和d做后缀的函数，以1.0表示最大的使用。
	采用b做后缀的函数，以127表示最大的使用。
	采用ub做后缀的函数，以255表示最大的使用。
	采用s做后缀的函数，以32767表示最大的使用。
	采用us做后缀的函数，以65535表示最大的使用。
	*/
	glColor3f(0.0f, 1.0f, 1.0f);	// RGBA模式 将浮点数作为参数，其中0.0表示不使用该种颜色，而1.0表示将该种颜色用到最多
	glRectf(-0.9f, 0.81f, -0.8f, 0.9f);

	glColor3f(1.0f, 1.0f, 1.0f);
	// 2. 索引颜色
	glutSetColor(0, 1.0f, 0.0f, 0.0f); // 设置颜色表不起作用，可能是需要glutInitDisplayMode设置索引颜色模式
	glutSetColor(1, 0.0f, 1.0f, 0.0f);
	glutSetColor(2, 0.0f, 0.0f, 1.0f);

	glIndexi(0);
	glRectf(-0.9f, 0.71f, -0.8f, 0.8f);
	glIndexi(2);
	glRectf(-0.9f, 0.61f, -0.8f, 0.7f);

	// 3. 指定清除屏幕用的颜色
	//glRectf(-0.9f, 0.51f, -0.8f, 0.6f);
	// 4. 指定着色模型
	glRectf(-0.9f, 0.41f, -0.8f, 0.5f);

	glColor3f(1.0f, 1.0f, 1.0f);

	
	// glEnable(GL_CULL_FACE);来启动剔除功能（使用glDisable(GL_CULL_FACE)可以关闭之）
	// 使用glCullFace来进行剔除。	glCullFace的参数可以是GL_FRONT，GL_BACK或者GL_FRONT_AND_BACK，分别表示剔除正面、剔除反面、剔除正反两面的多边形。
	// 注意：剔除功能只影响多边形，而对点和直线无影响。例如，使用glCullFace(GL_FRONT_AND_BACK)后，所有的多边形都将被剔除，所以看见的就只有点和直线

	//	使用glEnable(GL_POLYGON_STIPPLE);来启动镂空模式（使用glDisable(GL_POLYGON_STIPPLE)可以关闭之）。
	//  然后，使用glPolygonStipple来设置镂空的样式。
	//	void glPolygonStipple(const GLubyte *mask);
	static GLubyte Mask[128] =
	{

		0x00, 0x00, 0x00, 0x00,    //   这是最下面的一行
		0x00, 0x00, 0x00, 0x00,
		0x03, 0x80, 0x01, 0xC0,    //   麻
		0x06, 0xC0, 0x03, 0x60,    //   烦
		0x04, 0x60, 0x06, 0x20,    //   的
		0x04, 0x30, 0x0C, 0x20,    //   初
		0x04, 0x18, 0x18, 0x20,    //   始
		0x04, 0x0C, 0x30, 0x20,    //   化
		0x04, 0x06, 0x60, 0x20,    //   ，
		0x44, 0x03, 0xC0, 0x22,    //   不
		0x44, 0x01, 0x80, 0x22,    //   建
		0x44, 0x01, 0x80, 0x22,    //   议
		0x44, 0x01, 0x80, 0x22,    //   使
		0x44, 0x01, 0x80, 0x22,    //   用
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
		0x10, 0x00, 0x00, 0x08    // 这是最上面的一行
	};
	/*
	这样一堆数据非常缺乏直观性，我们需要很费劲的去分析，才会发现它表示的竟然是一只苍蝇。
	如果将这样的数据保存成图片，并用专门的工具进行编辑，显然会方便很多。下面介绍如何做到这一点。
	首先，用Windows自带的画笔程序新建一副图片，取名为mask.bmp，注意保存时，应该选择“单色位图”。在“图象”->“属性”对话框中，设置图片的高度和宽度均为32。
	用放大镜观察图片，并编辑之。黑色对应二进制零（镂空），白色对应二进制一（不镂空），编辑完毕后保存。
	然后，就可以使用以下代码来获得这个Mask数组了。

	static GLubyte Mask[128];
	FILE *fp;
	fp = fopen("mask.bmp", "rb");
	if( !fp )
	exit(0);
	// 移动文件指针到这个位置，使得再读sizeof(Mask)个字节就会遇到文件结束
	// 注意-(int)sizeof(Mask)虽然不是什么好的写法，但这里它确实是正确有效的
	// 如果直接写-sizeof(Mask)的话，因为sizeof取得的是一个无符号数，取负号会有问题

	if( fseek(fp, -(int)sizeof(Mask), SEEK_END) )
	exit(0);

	// 读取sizeof(Mask)个字节到Mask
	if( !fread(Mask, sizeof(Mask), 1, fp) )
	exit(0);
	fclose(fp);
	*/
	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(Mask);
	glRectf(-0.5f, -0.5f, 0.0f, 0.0f);   // 在左下方绘制一个有镂空效果的正方形

	glDisable(GL_POLYGON_STIPPLE);
	glRectf(0.0f, 0.0f, 0.5f, 0.5f);     // 在右上方绘制一个无镂空效果的正方形
	
}

void drawpoint()
{
	glPointSize(5.0f);	// size必须大于0.0f，默认值为1.0f，单位为“像素”  点的大小都有个限度的，如果设置的size超过最大值，则设置可能会有问题
	glBegin(GL_POINTS); // GL_POINT 居然画不出点
	glVertex2f(0.1f, 0.1f);
	glEnd();

	glPointSize(1.0f);
}

void drawline()
{
	glLineWidth(2.0f);
	glBegin(GL_LINES);	// GL_LINE 居然画不出线
		glVertex2f(0.3f, 0.3f);
		glVertex2f(0.5f, 0.5f);
	glEnd();

	glLineWidth(1.0f);

	glEnable(GL_LINE_STIPPLE); // 来启动虚线模式（使用glDisable(GL_LINE_STIPPLE)可以关闭之）
	glLineStipple(1, 0x00ff);
	glBegin(GL_LINES);	// GL_LINE 居然画不出线
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


	glFrontFace(GL_CW);	// 设置顺时针方向为正面
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


	glFrontFace(GL_CCW);	// 设置逆时针方向为正面

}

/*
设五角星的五个顶点分布位置关系如下：
      A
  E        B

    D    C
首先，根据余弦定理列方程，计算五角星的中心到顶点的距离a
（假设五角星对应正五边形的边长为.0）
a = 1 / (2-2*cos(72*Pi/180));
然后，根据正弦和余弦的定义，计算B的x坐标bx和y坐标by，以及C的y坐标
（假设五角星的中心在坐标原点）
bx = a * cos(18 * Pi/180);
by = a * sin(18 * Pi/180);
cy = -a * cos(18 * Pi/180);
五个点的坐标就可以通过以上四个量和一些常数简单的表示出来
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
	// 按照A->C->E->B->D->A的顺序，可以一笔将五角星画出
	glBegin(GL_LINE_LOOP);
	glVertex2fv(PointA);
	glVertex2fv(PointC);
	glVertex2fv(PointE);
	glVertex2fv(PointB);
	glVertex2fv(PointD);
	glEnd();

}

	/*
	由于OpenGL默认坐标值只能从-1到1，（可以修改，但方法留到以后讲）
	所以我们设置一个因子factor，把所有的坐标值等比例缩小，
	这样就可以画出更多个正弦周期
	试修改factor的值，观察变化情况
	*/
void drawsin()
{

	GLfloat x;
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);         // 以上两个点可以画x轴
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);         // 以上两个点可以画y轴
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
	在默认情况下，OpenGL会计算两点顶点之间的其它点，并为它们填上“合适”的颜色，使相邻的点的颜色值都比较接近。如果使用的是RGB模式，看起来就具有渐变的效果。如果是使用颜色索引模式，则其相邻点的索引值是接近的，如果将颜色表中接近的项设置成接近的颜色，则看起来也是渐变的效果。但如果颜色表中接近的项颜色却差距很大，则看起来可能是很奇怪的效果。
	使用glShadeModel函数可以关闭这种计算，如果顶点的颜色不同，则将顶点之间的其它点全部设置为与某一个点相同。（直线以后指定的点的颜色为准，而多边形将以任意顶点的颜色为准，由实现决定。）为了避免这个不确定性，尽量在多边形中使用同一种颜色。
	glShadeModel的使用方法：
	glShadeModel(GL_SMOOTH);    // 平滑方式，这也是默认方式
	glShadeModel(GL_FLAT);      // 单色方式
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
	// 清除。GL_COLOR_BUFFER_BIT表示清除颜色
	/*
	在RGB模式下，使用glClearColor来指定“空”的颜色，它需要四个参数，其参数的意义跟glColor4f相似。
	在索引颜色模式下，使用glClearIndex来指定“空”的颜色所在的索引，它需要一个参数，其意义跟glIndexi相似。
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

	//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）。其作用跟fflush(stdout)类似。
	glFlush();

}

int main(int argc, char *argv[])

{
	// 对GLUT进行初始化，这个函数必须在其它的GLUT使用之前调用一次
	glutInit(&argc, argv);
	// 设置显示方式，其中GLUT_RGB表示使用RGB颜色，与之对应的还有GLUT_INDEX（表示使用索引颜色）。GLUT_SINGLE表示使用单缓冲，与之对应的还有GLUT_DOUBLE（使用双缓冲）
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowPosition(100, 100);

	glutInitWindowSize(400, 400);

	glutCreateWindow("第一个OpenGL程序");

	glutDisplayFunc(&myDisplay);

	glutMainLoop();

	return 0;

}