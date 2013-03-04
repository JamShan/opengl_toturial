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

	static int list_sun_light = 0, list_sun_mat = 0, list_earth_mat = 0;
	
	if(list_sun_light == 0)
	{
		// GL_LIGHT0��ʾ��0�Ź�Դ��GL_LIGHT1��ʾ��1�Ź�Դ���������ƣ�OpenGL���ٻ�֧��8����Դ
		// ����̫����Դ������һ�ְ�ɫ�Ĺ�Դ
		
		// ��Դ���ڵ�λ�á���X, Y, Z, W����
		// WΪ�㣬��ʾ��Դλ������Զ����ǰ����ֵ��ʾ�������ڵķ������ֹ�Դ��Ϊ�����Թ�Դ��̫�����Խ��Ƶı���Ϊ�Ƿ����Թ�Դ��
		// W��Ϊ�㣬��X/W, Y/W, Z/W��ʾ�˹�Դ��λ�á����ֹ�Դ��Ϊλ���Թ�Դ��
		// ����λ���Թ�Դ��������λ�������ö���ζ���ķ�ʽ���ƣ����־���任�������磺glTranslate*��glRotate*��������Ҳͬ����Ч��
		// �����Թ�Դ�ڼ���ʱ��λ���Թ�Դ���˲��٣���ˣ����Ӿ�Ч�����������£�Ӧ�þ����ܵ�ʹ�÷����Թ�Դ��
		GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

		list_sun_light = glGenLists(1); // ������ʾ�б��ţ� ���ص��Ƿ�������������������С��һ����������������㣬��ʾ����ʧ�ܡ�
		// glIsList�����ж�һ������Ƿ��Ѿ���������ʾ�б�;

		// ������ʾ�б� �Ѹ���OpenGL�����ĵ���װ�뵽��ʾ�б���
		glNewList(list_sun_light, GL_COMPILE); // ��ʼװ�롣   GL_COMPILE�����ʾ���µ�����ֻ��װ�뵽��ʾ�б������ڲ�ִ�����ǣ�
		// GL_COMPILE_AND_EXECUTE����ʾ��װ���ͬʱ����װ�������ִ��һ��


		// ע��
		// ��ʾ�б�ֻ��װ��OpenGL������������װ����������
		// �������е�OpenGL����������װ�뵽��ʾ�б��С����磬�������ڲ�ѯ�ĺ����������޷���װ�뵽��ʾ�б���Ϊ���Ƕ����з���ֵ����glCallList��glCallLists��������֪����δ�����Щ����ֵ�������緽ʽ�£����ÿͻ���״̬�ĺ���Ҳ�޷���װ�뵽��ʾ�б�������Ϊ��ʾ�б����浽�������ˣ��������ÿͻ���״̬�ĺ����ڷ��͵�����������ǰ�ͱ�ִ���ˣ������������޷�ִ����Щ������
		// ���䡢������ɾ����ʾ�б�Ķ���Ҳ�޷���װ�뵽��һ����ʾ�б���������ʾ�б�Ķ�������Ա�װ�뵽��һ����ʾ�б�

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


		glEndList(); // ����װ��
	}

	// ����̫���Ĳ���
	if(list_sun_mat == 0)
	{
		GLfloat sun_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_shininess   = 0.0f;

		list_sun_mat = glGenLists(1); 
		glNewList(list_sun_mat, GL_COMPILE); 


		// ����̫��
		// ������һ����ĸ�����
		glMaterialfv(GL_FRONT, GL_AMBIENT,    sun_mat_ambient); // GL_AMBIENT��ʾ���ֹ������䵽�ò����ϣ������ܶ�η�������������ڻ����еĹ���ǿ�ȣ���ɫ����ͨ����GL_AMBIENT��GL_DIFFUSE��ȡ��ͬ��ֵ�����Դﵽ�Ƚ���ʵ��Ч����ʹ��GL_AMBIENT_AND_DIFFUSE����ͬʱ����GL_AMBIENT��GL_DIFFUSE���ԡ�
		glMaterialfv(GL_FRONT, GL_DIFFUSE,    sun_mat_diffuse); // GL_DIFFUSE��ʾ�������䵽�ò����ϣ�������������γɵĹ���ǿ�ȣ���ɫ����
		glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);// GL_SPECULAR��ʾ�������䵽�ò����ϣ��������淴����γɵĹ���ǿ�ȣ���ɫ����
		glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);// GL_SHININESS���ԡ�������ֻ��һ��ֵ����Ϊ������ָ������ȡֵ��Χ��0��128����ֵԽС����ʾ����Խ�ֲڣ����Դ����Ĺ������䵽���棬Ҳ���Բ����ϴ�����㡣��ֵԽ�󣬱�ʾ����Խ�����ھ��棬��Դ���䵽����󣬲�����С�����㡣
		glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);// GL_EMISSION���ԡ����������ĸ�ֵ��ɣ���ʾһ����ɫ��OpenGL��Ϊ�ò��ʱ����΢΢�����ⷢ����ߣ��������۾��о���������������ɫ����������ֱȽ�΢���������ڲ���Ӱ�쵽�����������ɫ��

		// GL_COLOR_INDEXES���ԡ������Խ�����ɫ����ģʽ��ʹ�ã���ɫ����ģʽ�µĹ��ձ�RGBAģʽҪ����


		glEndList(); // ����װ��
	}
	
	// �������Ĳ���
	if(list_earth_mat == 0)
	{
		GLfloat earth_mat_ambient[]   = {0.0f, 0.0f, 0.5f, 1.0f};
		GLfloat earth_mat_diffuse[]   = {0.0f, 0.0f, 0.5f, 1.0f};
		GLfloat earth_mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
		GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat earth_mat_shininess   = 30.0f;

		list_earth_mat = glGenLists(1); 
		glNewList(list_earth_mat, GL_COMPILE); 


		// ���Ƶ���
		glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
		glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);


		glEndList(); // ����װ��
	}

	glEnable(GL_LIGHT0);	// ������Դ
	glEnable(GL_LIGHTING);	// �򿪹��մ�����
	glEnable(GL_DEPTH_TEST);


	// ������ʾ�б�
	glCallList(list_sun_light);
	glCallList(list_sun_mat);
	glutSolidSphere(2.0, 40, 32);

	glCallList(list_earth_mat);
	glRotatef(angle, 0.0f, -1.0f, 0.0f);
	glTranslatef(5.0f, 0.0f, 0.0f);
	glutSolidSphere(1.0, 40, 32);

	/*
	glCallLists�������Ե���һϵ�е���ʾ�б��ú���������������
	��һ��������ʾ��Ҫ���ö��ٸ���ʾ�б�
	�ڶ���������ʾ����Щ��ʾ�б�ı�ŵĴ����ʽ��������GL_BYTE��ÿ�������һ��GLbyte��ʾ����GL_UNSIGNED_BYTE��ÿ�������һ��GLubyte��ʾ����GL_SHORT��GL_UNSIGNED_SHORT��GL_INT��GL_UNSIGNED_INT��GL_FLOAT��
	������������ʾ����Щ��ʾ�б�ı�����ڵ�λ�á���ʹ�øú���ǰ����Ҫ��glListBase����������һ��ƫ����������ƫ����Ϊk����glCallLists��Ҫ����õ���ʾ�б�������Ϊl1, l2, l3, ...����ʵ�ʵ��õ���ʾ�б�Ϊl1+k, l2+k, l3+k, ...��
	���磺
	GLuint lists[] = {1, 3, 4, 8};
	glListBase(10);
	glCallLists(4, GL_UNSIGNED_INT, lists);
	��ʵ���ϵ��õ��Ǳ��Ϊ11, 13, 14, 18���ĸ���ʾ�б�
	ע����������ʾ�б������������Ҳ���Ա�װ����һ����ʾ�б��С�

	glDeleteLists������һ�������������ʾ�б�
	���磬ʹ��glDeleteLists(20, 4);������20��21��22��23���ĸ���ʾ�б�
	*/




	/*
	����ģ�Ͱ����ĸ����ֵ����ݣ�ȫ�ֻ������ߣ�����Щ���ɢ�䣬�޷����徿�������ĸ���Դ�Ĺ��ߣ���ǿ�ȡ��۲��λ�����ڽϽ�λ�û���������Զ�������������뱳���Ƿ�ֱ������ա�������ɫ����GL_SPECULAR������ָ������ɫ)�ļ����Ƿ���������ռ����з��������������������Ժ��ڽ���Ӧ�á�
	�����ķ�������ݶ�ͨ��ͬһ������glLightModel*����������
	GL_LIGHT_MODEL_AMBIENT��ʾȫ�ֻ�������ǿ�ȣ����ĸ�ֵ��ɡ�
	GL_LIGHT_MODEL_LOCAL_VIEWER��ʾ�Ƿ��ڽ����ۿ�������������ΪGL_TRUE�����򣨼�������Զ���ۿ�������ΪGL_FALSE��
	GL_LIGHT_MODEL_TWO_SIDE��ʾ�Ƿ�ִ��˫����ռ��㡣�������ΪGL_TRUE����OpenGL���������ݷ���������������Ĺ��գ�Ҳ�Ὣ����������ת�����㱳��Ĺ��ա�
	GL_LIGHT_MODEL_COLOR_CONTROL��ʾ��ɫ���㷽ʽ���������ΪGL_SINGLE_COLOR����ʾ��ͨ��˳��������ȼ�����գ��ټ��������������ΪGL_SEPARATE_SPECULAR_COLOR����ʾ��GL_SPECULAR���Է���������ȼ�����յ��������֣������������ɺ��ټ���GL_SPECULAR������ͨ������ʹ����Ч����Ϊ���棨��Ȼ����������û��ִ���κ���������������ķ����û���κ����壩��
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
	glutCreateWindow("OpenGL������ʾ");
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);
	glutMainLoop();
	return 0;
}