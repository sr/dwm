//#define DEBUG

// Fast Gaussian Blur v1.3
// by Mario Klingemann <http://incubator.quasimondo.com>

// One of my first steps with Processing. I am a fan
// of blurring. Especially as you can use blurred images
// as a base for other effects. So this is something I
// might get back to in later experiments.
//
// What you see is an attempt to implement a Gaussian Blur algorithm
// which is exact but fast. I think that this one should be
// relatively fast because it uses a special trick by first
// making a horizontal blur on the original image and afterwards
// making a vertical blur on the pre-processed image-> This
// is a mathematical correct thing to do and reduces the
// calculation a lot.
//
// In order to avoid the overhead of function calls I unrolled
// the whole convolution routine in one method. This may not
// look nice, but brings a huge performance boost.
//
//
// v1.1: I replaced some multiplications by additions
//       and added aome minor pre-caclulations.
//       Also add correct rounding for float->int conversion
//
// v1.2: I completely got rid of all floating point calculations
//       and speeded up the whole process by using a
//       precalculated multiplication table. Unfortunately
//       a precalculated division table was becoming too
//       huge. But maybe there is some way to even speed
//       up the divisions.
//
// v1.3: Fixed a bug that caused blurs that start at y>0
//	 to go wrong. Thanks to Jeroen Schellekens for 
//       finding it!

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

typedef struct {
	unsigned char *pix;
	int x;
	int y;
	int w;
	int y2;
	int H;
	int wm;
	int wh;
	int *r;
	int *g;
	int *b;
	int *dv;
	int radius;
	int *vminx;
	int *vminy;
} StackBlurRenderingParams;

#include <pthread.h>

void *HStackRenderingThread(void *arg);

void *VStackRenderingThread(void *arg);

void stackblur(XImage *image,int x, int y,int w,int h,int radius, unsigned int num_threads);


