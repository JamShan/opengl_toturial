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

	static int list_sun_light = 0, list_sun_mat = 0, list_earth_mat = 0;
	
	if(list_sun_light == 0)
	{
		// GL_LIGHT0表示第0号光源，GL_LIGHT1表示第1号光源，依次类推，OpenGL至少会支持8个光源
		// 定义太阳光源，它是一种白色的光源
		
		// 光源所在的位置。（X, Y, Z, W）。
		// W为零，表示光源位于无限远处，前三个值表示了它所在的方向，这种光源称为方向性光源。太阳可以近似的被认为是方向性光源。
		// W不为零，则X/W, Y/W, Z/W表示了光源的位置。这种光源称为位置性光源。
		// 对于位置性光源，设置其位置与设置多边形顶点的方式相似，各种矩阵变换函数例如：glTranslate*、glRotate*等在这里也同样有效。
		// 方向性光源在计算时比位置性光源快了不少，因此，在视觉效果允许的情况下，应该尽可能的使用方向性光源。
		GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

		list_sun_light = glGenLists(1); // 分配显示列表编号， 返回的是分配的若干连续编号中最小的一个。如果函数返回零，表示分配失败。
		// glIsList函数判断一个编号是否已经被用作显示列表;

		// 创建显示列表 把各种OpenGL函数的调用装入到显示列表中
		glNewList(list_sun_light, GL_COMPILE); // 开始装入。   GL_COMPILE，则表示以下的内容只是装入到显示列表，但现在不执行它们；
		// GL_COMPILE_AND_EXECUTE，表示在装入的同时，把装入的内容执行一遍


		// 注：
		// 显示列表只能装入OpenGL函数，而不能装入其它内容
		// 并非所有的OpenGL函数都可以装入到显示列表中。例如，各种用于查询的函数，它们无法被装入到显示列表，因为它们都具有返回值，而glCallList和glCallLists函数都不知道如何处理这些返回值。在网络方式下，设置客户端状态的函数也无法被装入到显示列表，这是因为显示列表被保存到服务器端，各种设置客户端状态的函数在发送到服务器端以前就被执行了，而服务器端无法执行这些函数。
		// 分配、创建、删除显示列表的动作也无法被装入到另一个显示列表，但调用显示列表的动作则可以被装入到另一个显示列表

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


		glEndList(); // 结束装入
	}

	// 定义太阳的材质
	if(list_sun_mat == 0)
	{
		GLfloat sun_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_shininess   = 0.0f;

		list_sun_mat = glGenLists(1); 
		glNewList(list_sun_mat, GL_COMPILE); 


		// 绘制太阳
		// 设置哪一面的哪个属性
		glMaterialfv(GL_FRONT, GL_AMBIENT,    sun_mat_ambient); // GL_AMBIENT表示各种光线照射到该材质上，经过很多次反射后最终遗留在环境中的光线强度（颜色）。通常，GL_AMBIENT和GL_DIFFUSE都取相同的值，可以达到比较真实的效果。使用GL_AMBIENT_AND_DIFFUSE可以同时设置GL_AMBIENT和GL_DIFFUSE属性。
		glMaterialfv(GL_FRONT, GL_DIFFUSE,    sun_mat_diffuse); // GL_DIFFUSE表示光线照射到该材质上，经过漫反射后形成的光线强度（颜色）。
		glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);// GL_SPECULAR表示光线照射到该材质上，经过镜面反射后形成的光线强度（颜色）。
		glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);// GL_SHININESS属性。该属性只有一个值，称为“镜面指数”，取值范围是0到128。该值越小，表示材质越粗糙，点光源发射的光线照射到上面，也可以产生较大的亮点。该值越大，表示材质越类似于镜面，光源照射到上面后，产生较小的亮点。
		glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);// GL_EMISSION属性。该属性由四个值组成，表示一种颜色。OpenGL认为该材质本身就微微的向外发射光线，以至于眼睛感觉到它有这样的颜色，但这光线又比较微弱，以至于不会影响到其它物体的颜色。

		// GL_COLOR_INDEXES属性。该属性仅在颜色索引模式下使用，颜色索引模式下的光照比RGBA模式要复杂


		glEndList(); // 结束装入
	}
	
	// 定义地球的材质
	if(list_earth_mat == 0)
	{
		GLfloat earth_mat_ambient[]   = {0.0f, 0.0f, 0.5f, 1.0f};
		GLfloat earth_mat_diffuse[]   = {0.0f, 0.0f, 0.5f, 1.0f};
		GLfloat earth_mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
		GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat earth_mat_shininess   = 30.0f;

		list_earth_mat = glGenLists(1); 
		glNewList(list_earth_mat, GL_COMPILE); 


		// 绘制地球
		glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
		glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);


		glEndList(); // 结束装入
	}

	glEnable(GL_LIGHT0);	// 开启光源
	glEnable(GL_LIGHTING);	// 打开光照处理功能
	glEnable(GL_DEPTH_TEST);


	// 调用显示列表
	glCallList(list_sun_light);
	glCallList(list_sun_mat);
	glutSolidSphere(2.0, 40, 32);

	glCallList(list_earth_mat);
	glRotatef(angle, 0.0f, -1.0f, 0.0f);
	glTranslatef(5.0f, 0.0f, 0.0f);
	glutSolidSphere(1.0, 40, 32);

	/*
	glCallLists函数可以调用一系列的显示列表。该函数有三个参数，
	第一个参数表示了要调用多少个显示列表。
	第二个参数表示了这些显示列表的编号的储存格式，可以是GL_BYTE（每个编号用一个GLbyte表示），GL_UNSIGNED_BYTE（每个编号用一个GLubyte表示），GL_SHORT，GL_UNSIGNED_SHORT，GL_INT，GL_UNSIGNED_INT，GL_FLOAT。
	第三个参数表示了这些显示列表的编号所在的位置。在使用该函数前，需要用glListBase函数来设置一个偏移量。假设偏移量为k，且glCallLists中要求调用的显示列表编号依次为l1, l2, l3, ...，则实际调用的显示列表为l1+k, l2+k, l3+k, ...。
	例如：
	GLuint lists[] = {1, 3, 4, 8};
	glListBase(10);
	glCallLists(4, GL_UNSIGNED_INT, lists);
	则实际上调用的是编号为11, 13, 14, 18的四个显示列表。
	注：“调用显示列表”这个动作本身也可以被装在另一个显示列表中。

	glDeleteLists来销毁一串编号连续的显示列表。
	例如，使用glDeleteLists(20, 4);将销毁20，21，22，23这四个显示列表。
	*/




	/*
	光照模型包括四个部分的内容：全局环境光线（即那些充分散射，无法分清究竟来自哪个光源的光线）的强度、观察点位置是在较近位置还是在无限远处、物体正面与背面是否分别计算光照、镜面颜色（即GL_SPECULAR属性所指定的颜色)的计算是否从其它光照计算中分离出来，并在纹理操作以后在进行应用。
	以上四方面的内容都通过同一个函数glLightModel*来进行设置
	GL_LIGHT_MODEL_AMBIENT表示全局环境光线强度，由四个值组成。
	GL_LIGHT_MODEL_LOCAL_VIEWER表示是否在近处观看，若是则设置为GL_TRUE，否则（即在无限远处观看）设置为GL_FALSE。
	GL_LIGHT_MODEL_TWO_SIDE表示是否执行双面光照计算。如果设置为GL_TRUE，则OpenGL不仅将根据法线向量计算正面的光照，也会将法线向量反转并计算背面的光照。
	GL_LIGHT_MODEL_COLOR_CONTROL表示颜色计算方式。如果设置为GL_SINGLE_COLOR，表示按通常顺序操作，先计算光照，再计算纹理。如果设置为GL_SEPARATE_SPECULAR_COLOR，表示将GL_SPECULAR属性分离出来，先计算光照的其它部分，待纹理操作完成后再计算GL_SPECULAR。后者通常可以使画面效果更为逼真（当然，如果本身就没有执行任何纹理操作，这样的分离就没有任何意义）。
	*/

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