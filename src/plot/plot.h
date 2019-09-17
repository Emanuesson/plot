#ifndef _PLOT_H_
#define _PLOT_H_
#define PLOT_VERSION "0.2.0"
#include <stdlib.h>

struct plot {
	struct plot_data *data;
	unsigned int height;
	unsigned int width;
	size_t datasets;
	int color;
	int follow;
	int merge_plot_peices;
	struct x_label *x_label;
	struct y_label *y_label;
};

struct y_label {
	unsigned int width;
	unsigned int prec;
	int side;
	char *r_fmt;
	char *l_fmt;
};

struct x_label {
	unsigned int mod;
	unsigned int every;
	long start;
	unsigned int color;
	int side;
	char *label;
};

struct plot *plot_init();
void plot_add(struct plot *plot, size_t len, double *data, int color);
void plot_plot(struct plot *plot);
void plot_destroy(struct plot *plot, int free_data);
#endif