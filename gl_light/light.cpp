#include <glut/glut.h>

#define WIDTH 400
#define HEIGHT 400

static GLfloat angle = 0.0f;

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ����͸��Ч����ͼ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// GL_LIGHT0��ʾ��0�Ź�Դ��GL_LIGHT1��ʾ��1�Ź�Դ���������ƣ�OpenGL���ٻ�֧��8����Դ
	// ����̫����Դ������һ�ְ�ɫ�Ĺ�Դ
	{
		// ��Դ���ڵ�λ�á���X, Y, Z, W����
		// WΪ�㣬��ʾ��Դλ������Զ����ǰ����ֵ��ʾ�������ڵķ������ֹ�Դ��Ϊ�����Թ�Դ��̫�����Խ��Ƶı���Ϊ�Ƿ����Թ�Դ��
		// W��Ϊ�㣬��X/W, Y/W, Z/W��ʾ�˹�Դ��λ�á����ֹ�Դ��Ϊλ���Թ�Դ��
		// ����λ���Թ�Դ��������λ�������ö���ζ���ķ�ʽ���ƣ����־���任�������磺glTranslate*��glRotate*��������Ҳͬ����Ч��
		// �����Թ�Դ�ڼ���ʱ��λ���Թ�Դ���˲��٣���ˣ����Ӿ�Ч�����������£�Ӧ�þ����ܵ�ʹ�÷����Թ�Դ��
		GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

		// �����ĸ���Դ���ĸ�����
		// ÿ���������ĸ�ֵ��ʾ���ֱ��������ɫ��R, G, B, Aֵ
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT,   sun_light_ambient);	// ��Դ�������Ĺ⣬�����ǳ���εķ���������������������ջ����е�ǿ�ȣ���ɫ��
		glLightfv(GL_LIGHT0, GL_DIFFUSE,   sun_light_diffuse);	// ��Դ�������Ĺ⣬���䵽�ֲڱ���ʱ���������䣬���õ��Ĺ��ǿ�ȣ���ɫ��
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);	// ��Դ�������Ĺ⣬���䵽�⻬����ʱ�������淴�䣬���õ��Ĺ��ǿ�ȣ���ɫ��

		// GL_SPOT_DIRECTION��GL_SPOT_EXPONENT��GL_SPOT_CUTOFF���ԡ���ʾ����Դ��Ϊ�۹��ʹ�ã���Щ����ֻ��λ���Թ�Դ��Ч��
		// GL_SPOT_DIRECTION����������ֵ����ʾһ������������Դ����ķ���
		// GL_SPOT_EXPONENT����ֻ��һ��ֵ����ʾ�۹�ĳ̶ȣ�Ϊ��ʱ��ʾ���շ�Χ�����������Ĺ���ǿ����ͬ��Ϊ����ʱ��ʾ���������뼯�У����Է��䷽���λ���ܵ�������գ�����λ���ܵ����ٹ��ա���ֵԽ�󣬾۹�Ч����Խ���ԡ�
		// GL_SPOT_CUTOFF����Ҳֻ��һ��ֵ����ʾһ���Ƕȣ����ǹ�Դ������������ǽǶȵ�һ�루��ͼ2������ȡֵ��Χ��0��90֮�䣬Ҳ����ȡ180�������ֵ��ȡֵΪ180ʱ��ʾ��Դ������߸���360�ȣ�����ʹ�þ۹�ƣ���ȫ��Χ���䡣

		// GL_CONSTANT_ATTENUATION��GL_LINEAR_ATTENUATION��GL_QUADRATIC_ATTENUATION���ԡ����������Ա�ʾ�˹�Դ�������Ĺ��ߵ�ֱ�ߴ������ԣ���Щ����ֻ��λ���Թ�Դ��Ч����
		// ��ʵ�����У����ߵ�ǿ�����ž�������Ӷ�������OpenGL��������������Ƴ���ɺ�����
		// ˥������ = 1 / (k1 + k2 * d + k3 * k3 * d)
		//	����d��ʾ���룬���ߵĳ�ʼǿ�ȳ���˥�����ӣ��͵õ���Ӧ����Ĺ���ǿ�ȡ�k1, k2, k3�ֱ����GL_CONSTANT_ATTENUATION, GL_LINEAR_ATTENUATION, GL_QUADRATIC_ATTENUATION��ͨ�������������������Ϳ��Կ��ƹ����ڴ��������еļ������ơ�

		glEnable(GL_LIGHT0);	// ������Դ
		glEnable(GL_LIGHTING);	// �򿪹��մ�����
		glEnable(GL_DEPTH_TEST);
	}

	// ����̫���Ĳ��ʲ�����̫��
	{
		GLfloat sun_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_shininess   = 0.0f;

		// ������һ����ĸ�����
		glMaterialfv(GL_FRONT, GL_AMBIENT,    sun_mat_ambient); // GL_AMBIENT��ʾ���ֹ������䵽�ò����ϣ������ܶ�η�������������ڻ����еĹ���ǿ�ȣ���ɫ����ͨ����GL_AMBIENT��GL_DIFFUSE��ȡ��ͬ��ֵ�����Դﵽ�Ƚ���ʵ��Ч����ʹ��GL_AMBIENT_AND_DIFFUSE����ͬʱ����GL_AMBIENT��GL_DIFFUSE���ԡ�
		glMaterialfv(GL_FRONT, GL_DIFFUSE,    sun_mat_diffuse); // GL_DIFFUSE��ʾ�������䵽�ò����ϣ�������������γɵĹ���ǿ�ȣ���ɫ����
		glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);// GL_SPECULAR��ʾ�������䵽�ò����ϣ��������淴����γɵĹ���ǿ�ȣ���ɫ����
		glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);// GL_SHININESS���ԡ�������ֻ��һ��ֵ����Ϊ������ָ������ȡֵ��Χ��0��128����ֵԽС����ʾ����Խ�ֲڣ����Դ����Ĺ������䵽���棬Ҳ���Բ����ϴ�����㡣��ֵԽ�󣬱�ʾ����Խ�����ھ��棬��Դ���䵽����󣬲�����С�����㡣
		glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);// GL_EMISSION���ԡ����������ĸ�ֵ��ɣ���ʾһ����ɫ��OpenGL��Ϊ�ò��ʱ����΢΢�����ⷢ����ߣ��������۾��о���������������ɫ����������ֱȽ�΢���������ڲ���Ӱ�쵽�����������ɫ��

		// GL_COLOR_INDEXES���ԡ������Խ�����ɫ����ģʽ��ʹ�ã���ɫ����ģʽ�µĹ��ձ�RGBAģʽҪ����

		glutSolidSphere(2.0, 40, 32);
	}

	// �������Ĳ��ʲ����Ƶ���
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
	glutCreateWindow("OpenGL������ʾ");
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);
	glutMainLoop();
	return 0;
}