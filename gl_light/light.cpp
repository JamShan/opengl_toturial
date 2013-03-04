#include <glut/glut.h>

#define WIDTH 400
#define HEIGHT 400

static GLfloat angle = 0.0f;

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 创建透视效果视图
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// GL_LIGHT0表示第0号光源，GL_LIGHT1表示第1号光源，依次类推，OpenGL至少会支持8个光源
	// 定义太阳光源，它是一种白色的光源
	{
		// 光源所在的位置。（X, Y, Z, W）。
		// W为零，表示光源位于无限远处，前三个值表示了它所在的方向，这种光源称为方向性光源。太阳可以近似的被认为是方向性光源。
		// W不为零，则X/W, Y/W, Z/W表示了光源的位置。这种光源称为位置性光源。
		// 对于位置性光源，设置其位置与设置多边形顶点的方式相似，各种矩阵变换函数例如：glTranslate*、glRotate*等在这里也同样有效。
		// 方向性光源在计算时比位置性光源快了不少，因此，在视觉效果允许的情况下，应该尽可能的使用方向性光源。
		GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

		// 设置哪个光源的哪个属性
		// 每个属性由四个值表示，分别代表了颜色的R, G, B, A值
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT,   sun_light_ambient);	// 光源所发出的光，经过非常多次的反射后，最终遗留在整个光照环境中的强度（颜色）
		glLightfv(GL_LIGHT0, GL_DIFFUSE,   sun_light_diffuse);	// 光源所发出的光，照射到粗糙表面时经过漫反射，所得到的光的强度（颜色）
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);	// 光源所发出的光，照射到光滑表面时经过镜面反射，所得到的光的强度（颜色）

		// GL_SPOT_DIRECTION、GL_SPOT_EXPONENT、GL_SPOT_CUTOFF属性。表示将光源作为聚光灯使用（这些属性只对位置性光源有效）
		// GL_SPOT_DIRECTION属性有三个值，表示一个向量，即光源发射的方向。
		// GL_SPOT_EXPONENT属性只有一个值，表示聚光的程度，为零时表示光照范围内向各方向发射的光线强度相同，为正数时表示光照向中央集中，正对发射方向的位置受到更多光照，其它位置受到较少光照。数值越大，聚光效果就越明显。
		// GL_SPOT_CUTOFF属性也只有一个值，表示一个角度，它是光源发射光线所覆盖角度的一半（见图2），其取值范围在0到90之间，也可以取180这个特殊值。取值为180时表示光源发射光线覆盖360度，即不使用聚光灯，向全周围发射。

		// GL_CONSTANT_ATTENUATION、GL_LINEAR_ATTENUATION、GL_QUADRATIC_ATTENUATION属性。这三个属性表示了光源所发出的光线的直线传播特性（这些属性只对位置性光源有效）。
		// 现实生活中，光线的强度随着距离的增加而减弱，OpenGL把这个减弱的趋势抽象成函数：
		// 衰减因子 = 1 / (k1 + k2 * d + k3 * k3 * d)
		//	其中d表示距离，光线的初始强度乘以衰减因子，就得到对应距离的光线强度。k1, k2, k3分别就是GL_CONSTANT_ATTENUATION, GL_LINEAR_ATTENUATION, GL_QUADRATIC_ATTENUATION。通过设置这三个常数，就可以控制光线在传播过程中的减弱趋势。

		glEnable(GL_LIGHT0);	// 开启光源
		glEnable(GL_LIGHTING);	// 打开光照处理功能
		glEnable(GL_DEPTH_TEST);
	}

	// 定义太阳的材质并绘制太阳
	{
		GLfloat sun_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_shininess   = 0.0f;

		// 设置哪一面的哪个属性
		glMaterialfv(GL_FRONT, GL_AMBIENT,    sun_mat_ambient); // GL_AMBIENT表示各种光线照射到该材质上，经过很多次反射后最终遗留在环境中的光线强度（颜色）。通常，GL_AMBIENT和GL_DIFFUSE都取相同的值，可以达到比较真实的效果。使用GL_AMBIENT_AND_DIFFUSE可以同时设置GL_AMBIENT和GL_DIFFUSE属性。
		glMaterialfv(GL_FRONT, GL_DIFFUSE,    sun_mat_diffuse); // GL_DIFFUSE表示光线照射到该材质上，经过漫反射后形成的光线强度（颜色）。
		glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);// GL_SPECULAR表示光线照射到该材质上，经过镜面反射后形成的光线强度（颜色）。
		glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);// GL_SHININESS属性。该属性只有一个值，称为“镜面指数”，取值范围是0到128。该值越小，表示材质越粗糙，点光源发射的光线照射到上面，也可以产生较大的亮点。该值越大，表示材质越类似于镜面，光源照射到上面后，产生较小的亮点。
		glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);// GL_EMISSION属性。该属性由四个值组成，表示一种颜色。OpenGL认为该材质本身就微微的向外发射光线，以至于眼睛感觉到它有这样的颜色，但这光线又比较微弱，以至于不会影响到其它物体的颜色。

		// GL_COLOR_INDEXES属性。该属性仅在颜色索引模式下使用，颜色索引模式下的光照比RGBA模式要复杂

		glutSolidSphere(2.0, 40, 32);
	}

	// 定义地球的材质并绘制地球
	{
		GLfloat earth_mat_ambient[]   = {0.0f, 0.0f, 0.5f, 1.0f};
		GLfloat earth_mat_diffuse[]   = {0.0f, 0.0f, 0.5f, 1.0f};
		GLfloat earth_mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
		GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat earth_mat_shininess   = 30.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
		glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);

		glRotatef(angle, 0.0f, -1.0f, 0.0f);
		glTranslatef(5.0f, 0.0f, 0.0f);
		glutSolidSphere(1.0, 40, 32);
	}

	glutSwapBuffers();
}
void myIdle(void)
{
	angle += 1.0f;
	if( angle >= 360.0f )
		angle = 0.0f;
	myDisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("OpenGL光照演示");
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);
	glutMainLoop();
	return 0;
}