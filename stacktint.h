//#define DEBUG

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

typedef struct {
	unsigned char *pix;
	unsigned char *tint;
	int y;
	int y2;
	int w;
} StackTintRenderingParams;

#include <pthread.h>

void *StackRenderingThread(void *arg);

void stacktint(XImage *image, unsigned char *tint, unsigned int num_threads);


