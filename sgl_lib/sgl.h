// simple gl lib/dll
#include "glut/glut.h"

//#if (USE_SIMPLE_GL_LIB)


double cal_fps();

// BMP文件头长度
#define BMP_HEADER_LENGTH 54
#define BMP_LINE_ALIGNMENT 4
#define ALIGNLINESIZE(l) if(((l)%BMP_LINE_ALIGNMENT)!=0) { (l)+=(BMP_LINE_ALIGNMENT-(l)%BMP_LINE_ALIGNMENT); }
void grab(GLint x, GLint y, GLsizei width, GLsizei height);
GLuint load_texture(const char* file_name);

//#endif