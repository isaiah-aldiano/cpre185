/*
	outputs the given x, y, and z gyroscope values followed by the
	moving averages of x, y, and z. It should also output the maximum and minimum
	values from the array used to compute the averages, which are calculated in a
	maxmin function. The output should be all on one line and separated by
	commas

	Note that the moving average has to accumulate n inputs before it can output
	something.

*/

// 185 Lab 7
#include <stdio.h>
#include <stdlib.h>

#define MAXPOINTS 10000

// compute the average of the first num_items of buffer
double avg(double buffer[], int num_items);

double avg(double buffer[], int num_items)
{
	double temp_sum = 0;
	for (int k = 0; k < num_items; k++)
	{
		temp_sum += buffer[k];
	}

	temp_sum /= num_items;

	return temp_sum;
}

// update the max and min of the first num_items of array
void maxmin(double array[], int num_items, double *max, double *min);

void maxmin(double array[], int num_items, double *max, double *min)
{
	double temp_max = 0.0;
	double temp_min = 5.0;

	for (int j = 0; j < num_items; j++)
	{
		if (array[j] > temp_max)
		{
			*max = array[j];
		}

		if (array[j] < temp_min)
		{
			*min = array[j];
		}
	}
}

// shift length-1 elements of the buffer to the left and put the
// new_item on the right.
void updatebuffer(double buffer[], int length, double new_item);

void updatebuffer(double buffer[], int length, double new_item)
{
	buffer[length] = new_item;
}

int main(int argc, char *argv[])
{

	/* DO NOT CHANGE THIS PART OF THE CODE */

	double x[MAXPOINTS], y[MAXPOINTS], z[MAXPOINTS];
	int t = 0, b1, b2, b3, b4;
	double gx, gy, gz;
	int lengthofavg = 0;
	int i = 0;
	double xmax, xmin, ymax, ymin, zmax, zmin, xavg, yavg, zavg;
	if (argc > 1)
	{
		sscanf(argv[1], "%d", &lengthofavg);
		printf("You entered a buffer length of %d\n", lengthofavg);
	}
	else
	{
		printf("Enter a length on the command line\n");
		return -1;
	}
	if (lengthofavg < 1 || lengthofavg > MAXPOINTS)
	{
		printf("Invalid length\n");
		return -1;
	}

	/* PUT YOUR CODE HERE */
	printf("gx, gy, gz, xavg, yavg, zavg, xmax, ymax, zmax, zmin, ymin, zmin\n");

	do
	{
		scanf("%lf, %lf, %lf, %d, %d, %d, %d", &gx, &gy, &gz, &b1, &b2, &b3, &b4);

		if (b4 == 1)
		{
			for (int j = 0; j < i - lengthofavg; j++)
			{
				double *x0 = NULL;
				double *y0 = NULL;
				double *z0 = NULL;

				x0 = (double *)malloc(lengthofavg * sizeof(double));
				y0 = (double *)malloc(lengthofavg * sizeof(double));
				z0 = (double *)malloc(lengthofavg * sizeof(double));

				for (int k = 0; k < lengthofavg; k++)
				{
					x0[k] = x[j + k];
					y0[k] = y[j + k];
					z0[k] = z[j + k];
				}

				maxmin(x0, lengthofavg, &xmax, &xmin);
				maxmin(y0, lengthofavg, &ymax, &ymin);
				maxmin(z0, lengthofavg, &zmax, &zmin);

				xavg = avg(x0, lengthofavg);
				yavg = avg(y0, lengthofavg);
				zavg = avg(z0, lengthofavg);

				printf("%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n", x[j], y[j], z[j], xavg, yavg, zavg, xmax, ymax, zmax, xmin, ymin, zmin);

				free(x0);
				free(y0);
				free(z0);
			}
			break;
		}

		updatebuffer(x, i, gx);
		updatebuffer(y, i, gy);
		updatebuffer(z, i, gz);

		i++;

		// if (i >= lengthofavg)
		// {
			// for (int j = 0; j < i - lengthofavg; j++)
			// {
			// 	double *x0 = NULL;
			// 	double *y0 = NULL;
			// 	double *z0 = NULL;

			// 	x0 = (double *)malloc(lengthofavg * sizeof(double));
			// 	y0 = (double *)malloc(lengthofavg * sizeof(double));
			// 	z0 = (double *)malloc(lengthofavg * sizeof(double));

			// 	for (int k = 0; k < lengthofavg; k++)
			// 	{
			// 		x0[k] = x[j + k];
			// 		y0[k] = y[j + k];
			// 		z0[k] = z[j + k];
			// 	}

			// 	maxmin(x0, lengthofavg, &xmax, &xmin);
			// 	maxmin(y0, lengthofavg, &ymax, &ymin);
			// 	maxmin(z0, lengthofavg, &zmax, &zmin);

			// 	xavg = avg(x0, lengthofavg);
			// 	yavg = avg(y0, lengthofavg);
			// 	zavg = avg(z0, lengthofavg);

			// 	printf("%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n", x[j], y[j], z[j], xavg, yavg, zavg, xmax, ymax, zmax, xmin, ymin, zmin);

			// 	free(x0);
			// 	free(y0);
			// 	free(z0);
			// }
		// }

	} while (1);

	return 0;
}
