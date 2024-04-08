/* moy.c - moy filter sequential program*/
#include "enerc.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "mypgm.h"
#include <omp.h>
#include <math.h>

void moy_filtering(int ker_size)
	/* Spatial filtering of image data */
	/* moy filter (horizontal differentiation */
	/* Input: image1[y][x] ---- Outout: image2[y][x] */
{
	/* Definition of moy filter in horizontal direction */
	int weight_x[ker_size][ker_size];
	for(int i = 0; i < ker_size; i++){
		for (int j = 0; j < ker_size; j++){
		weight_x[i][j] = 1;
		}
	}

double pixel_value;
// double min, max;
int x, y, i, j; /* Loop variable */
/* Maximum values calculation after filtering*/

/* Initialization of image2[y][x] */
x_size2 = x_size1;
y_size2 = y_size1;
int deb = ker_size/2;

#pragma omp parallel for collapse(2) private(x,y)\
				shared(image2)
for (y = 0; y < y_size2; y++) {
	for (x = 0; x < x_size2; x++) {
		image2[y][x] = 0;
	}
}
/* Generation of image2 after linear transformtion */
#pragma omp parallel for collapse(2) private(i,j,pixel_value)\
									shared(image2)
for (y = deb; y < y_size1 + 1; y++) {
	for (x = deb; x < x_size1 + 1; x++) {
		pixel_value = 0.0;
		for (j = -deb; j <= deb; j++) {
			for (i = -deb; i <= deb; i++) {
				pixel_value += weight_x[j + deb][i + deb] * image1[y + j][x + i];
			}
		}
		pixel_value = pixel_value/(double)(ker_size*ker_size);

	//	pixel_value = MAX_BRIGHTNESS * (pixel_value - min) / (max - min);
		image2[y][x] = (unsigned char)pixel_value;
	}
}
}
int main(int argc, const char** argv)
{
double start_time, time;
    
        load_image_data(argv[1]);   /* Input of image1 */
	/* Input of image1 */
	start_time = omp_get_wtime();
	int ker_size = strtol(argv[2], NULL, 10);
	moy_filtering(ker_size);
	/* moy filter is applied to image1 */
	printf("The total time for execution is : %f", omp_get_wtime() - start_time );
	save_image_data( );
	/* Output of image2 */
	return 0;
}

