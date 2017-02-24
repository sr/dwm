/* See LICENSE file for copyright and license details. */
#define DRW_FONT_CACHE_SIZE 32

typedef struct {
	unsigned long pix;
	XftColor rgb;
} Clr;

typedef struct {
	Cursor cursor;
} Cur;

typedef struct {
	Display *dpy;
	int ascent;
	int descent;
	unsigned int h;
	XftFont *xfont;
	FcPattern *pattern;
} Fnt;

typedef struct {
	Clr *fg;
	Clr *bg;
	Clr *border;
} ClrScheme;

typedef struct {
	unsigned int w, h;
	Display *dpy;
	int screen;
	Window root;
	Drawable drawable;
	GC gc;
	ClrScheme *scheme;
	XImage *screenshot;
	unsigned char* last_wallpaper_data;
	size_t fontcount;
	Fnt *fonts[DRW_FONT_CACHE_SIZE];
} Drw;

typedef struct {
	unsigned int w;
	unsigned int h;
} Extnts;

void drw_bluriamge (XImage *image, int radius, unsigned int cpu_threads);
void drw_blurrect(Drw *drw, int x, int y, unsigned int w, unsigned int h, unsigned long tint, unsigned int num_threads);

/* Drawable abstraction */
Drw *drw_create(Display *, int, Window, unsigned int, unsigned int);
void drw_resize(Drw *, unsigned int, unsigned int);
void drw_free(Drw *);
void drw_takeblurscreenshot(Drw *drw, int x, int y, unsigned int w, unsigned int h, int blurlevel, unsigned int num_threads);

/* Fnt abstraction */
Fnt *drw_font_create(Drw *, const char *);
void drw_load_fonts(Drw *, const char *[], size_t);
void drw_font_free(Fnt *);
void drw_font_getexts(Fnt *, const char *, unsigned int, Extnts *);
unsigned int drw_font_getexts_width(Fnt *, const char *, unsigned int);

/* Colour abstraction */
Clr *drw_clr_create(Drw *, const char *);
void drw_clr_free(Clr *);

/* Cursor abstraction */
Cur *drw_cur_create(Drw *, int);
void drw_cur_free(Drw *, Cur *);

/* Drawing context manipulation */
void drw_setfont(Drw *, Fnt *);
void drw_setscheme(Drw *, ClrScheme *);

/* Drawing functions */
void drw_colored_text(Drw *drw, ClrScheme *scheme, int numcolors, int x, int y, unsigned int w, unsigned int h, char *text, unsigned int num_threads);
void drw_rect(Drw *drw, int x, int y, unsigned int w, unsigned int h, int filled, int empty, int invert, unsigned int num_threads);
int drw_text(Drw *, int, int, unsigned int, unsigned int, const char *, int, unsigned int);


/* Map functions */
void drw_map(Drw *, Window, int, int, unsigned int, unsigned int);
