#include "stacktint.h"
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

void *StackRenderingThread(void *arg) {
	StackTintRenderingParams *rp=(StackTintRenderingParams*)arg;
	unsigned int x,y,yi,p;
	for (x=0;x<rp->w;x++) {
		yi=rp->y*rp->w+x;
		for (y=rp->y;y<rp->y2;y++) {
			p=yi*4;
#ifdef DEBUG
// 		fprintf(stdout,"y: %i %i %i 1\n",rp->y, x, y);
#endif
 			rp->pix[p]=(unsigned char)((unsigned int)(rp->pix[p] + rp->tint[0]) / 2);
 			rp->pix[p+1]=(unsigned char)((unsigned int)(rp->pix[p+1] + rp->tint[1]) / 2);
 			rp->pix[p+2]=(unsigned char)((unsigned int)(rp->pix[p+2] + rp->tint[2]) / 2);
 			rp->pix[p+3]=0xff;
#ifdef DEBUG
// 		fprintf(stdout,"y: %i 2\n",rp->y);
#endif

			yi+=rp->w;
		}
	}
    pthread_exit(NULL);
}

void stacktint(XImage *image, unsigned char *tint, unsigned int num_threads) {
	char *pix=image->data;
	int i;

	pthread_t *pth=malloc(num_threads*sizeof(pthread_t));
	StackTintRenderingParams *rp=malloc(num_threads*sizeof(StackTintRenderingParams));
	int threadY=0;
	int threadH=(image->height/num_threads);
 	for (i=0;i<num_threads;i++) {
		rp[i].pix=(unsigned char*)pix;
		rp[i].w=image->width;
		rp[i].y=threadY;
		//Below "if" is to avoid vertical threads running on the same line when h/num_threads is not a round number i.e. 1080 lines / 16 threads = 67.5 lines!
		if (i==num_threads-1)//last turn
			rp[i].y2=image->height;
		else
			rp[i].y2=threadY+threadH;
		rp[i].tint = malloc(3 * sizeof(char));
		memcpy(rp[i].tint, tint, 3 * sizeof(char));
#ifdef DEBUG
		fprintf(stdout,"Thread: %i y: %i w: %i h: %i\n", i, rp[i].y, rp[i].w, threadH);
#endif
		pthread_create(&pth[i],NULL,StackRenderingThread,(void*)&rp[i]);
		threadY+=threadH;
	}
	for (i=0;i<num_threads;i++)
		pthread_join(pth[i],NULL);
	free(rp);
	free(pth);
	rp=NULL;
	pth=NULL;
#ifdef DEBUG
 	fprintf(stdout,"Done.\n");
#endif
}
#undef MIN
#undef MAX
