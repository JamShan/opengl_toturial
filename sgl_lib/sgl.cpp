#include <time.h>
#include "sgl.h"

double cal_fps()
{
	static int frame = 0;
	static double fps = 0;
	static clock_t last = 0, current = clock();
	double timegap = 0;

	if(frame++ <= 50)
		return fps;

	frame = 0;

	last = current;
	current = clock();
	timegap = (current - last)/(double)CLK_TCK;
	fps = 50.0/timegap;

	return fps;
}