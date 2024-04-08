/* gaussian.c - Gaussian filter sequential program*/
#include "enerc.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "mypgm.h"
#include <omp.h>
#include <math.h>

void gaussian_filtering()
/* Spatial filtering of image data */
/* Gaussian filter */
/* Input: image1[y][x] ---- Output: image2[y][x] */
{
    /* Definition of Gaussian filter */
    double weight[3][3] = {
        {1.0, 2.0, 1.0},
        {2.0, 4.0, 2.0},
        {1.0, 2.0, 1.0}};

    double pixel_value;
    double sum;
    double min, max;
    int x, y, i, j; /* Loop variable */

    /* Maximum values calculation after filtering*/
    printf("Now, filtering of input image is performed\n\n");
    min = DBL_MAX;
    max = -DBL_MAX;

#pragma omp parallel for collapse(2) private(i, j, pixel_value, sum) \
    shared(min, max)
    for (y = 1; y < y_size1 + 1; y++)
    {
        for (x = 1; x < x_size1 + 1; x++)
        {
            sum = 0.0;
            pixel_value = 0.0;

            for (j = -1; j <= 1; j++)
            {
                for (i = -1; i <= 1; i++)
                {
                    sum += weight[j + 1][i + 1] * image1[y + j][x + i];
                }
            }

            pixel_value = sum;

#pragma omp critical
            {
                if (pixel_value < min)
                    min = pixel_value;
                if (pixel_value > max)
                    max = pixel_value;
            }
        }
    }
    printf("the value of minimum %f\n", min);
    printf("the value of maximum %f\n", max);

    if ((int)(max - min) == 0)
    {
        printf("Nothing exists!!!\n\n");
        exit(1);
    }

    /* Initialization of image2[y][x] */
    x_size2 = x_size1;
    y_size2 = y_size1;

#pragma omp parallel for collapse(2) private(x, y) \
    shared(image2)
    for (y = 0; y < y_size2; y++)
    {
        for (x = 0; x < x_size2; x++)
        {
            image2[y][x] = 0;
        }
    }

    /* Generation of image2 after linear transformtion */
#pragma omp parallel for collapse(2) private(i, j, pixel_value, sum) \
    shared(image2)
    for (y = 1; y < y_size1 + 1; y++)
    {
        for (x = 1; x < x_size1 + 1; x++)
        {
            sum = 0.0;
            pixel_value = 0.0;

            for (j = -1; j <= 1; j++)
            {
                for (i = -1; i <= 1; i++)
                {
                    sum += weight[j + 1][i + 1] * image1[y + j][x + i];
                }
            }

            pixel_value = sum;

            pixel_value = MAX_BRIGHTNESS * (pixel_value - min) / (max - min);
            image2[y][x] = (unsigned char)pixel_value;
        }
    }
}

int main(int argc, const char **argv)
{
    double start_time;

    load_image_data(argv[1]); /* Input of image1 */

    start_time = omp_get_wtime();
    gaussian_filtering();
    /* Gaussian filter is applied to image1 */
    printf("The total time for execution is : %f", omp_get_wtime() - start_time);
    save_image_data();
    /* Output of image2 */

    return 0;
}
