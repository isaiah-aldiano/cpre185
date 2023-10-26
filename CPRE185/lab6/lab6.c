// 185 lab6.c
//
// This is the outline for your program
// Please implement the functions given by the prototypes below and
// complete the main function to make the program complete.
// You must implement the functions which are prototyped below exactly
//  as they are requested.

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#define PI 3.141592653589

//NO GLOBAL VARIABLES ALLOWED


//PRE: Arguments must point to double variables or int variables as appropriate
//This function scans a line of DS4 data, and returns
//  True when the square button is pressed
//  False Otherwise
//This function is the ONLY place scanf is allowed to be used
//POST: it modifies its arguments to return values read from the input line.
int read_line(double* g_x, double* g_y, double* g_z, int* time, int* Button_T, int* Button_X, int* Button_S, int* Button_C);

// PRE: -1.0 <= x_mag <= 1.0
// This function computes the roll of the DS4 in radians
// if x_mag outside of -1 to 1, treat it as if it were -1 or 1
// POST: -PI/2 <= return value <= PI/2
double roll(double x_mag);

// PRE: -1.0 <= y_mag <= 1.0
// This function computes the pitch of the DS4 in radians
// if y_mag outside of -1 to 1, treat it as if it were -1 or 1
// POST: -PI/2 <= return value <= PI/2
double pitch(double y_mag);

// PRE: -PI/2 <= rad <= PI/2
// This function scales the roll value to fit on the screen
// POST: -39 <= return value <= 39
int scaleRadsForScreen(double rad);

// PRE: num >= 0
// This function prints the character use to the screen num times
// This function is the ONLY place printf is allowed to be used
// POST: nothing is returned, but use has been printed num times
void print_chars(int num, char use);

//PRE: -39 <= number <=39
// Uses print_chars to graph a number from -39 to 39 on the screen.
// You may assume that the screen is 80 characters wide.
void graph_line(int number);

double mag(double some_val);

int main()
{
	double x, y, z;                             // magnitude values of x, y, and z
	int b_Triangle, b_X, b_Square, b_Circle;    // variables to hold the button statuses
	double roll_rad, pitch_rad;                 // value of the roll measured in radians
	int scaled_value;                           // value of the roll adjusted to fit screen display
	double selected;
	int t, pt = 100;									// time
	int pressed;
	int mode = 1;
	bool let_off = true;

	//insert any beginning needed code here

	do
	{
		// Get line of input
			pressed = read_line(&x, &y, &z, &t, &b_Triangle, &b_X, &b_Square, &b_Circle);

			if(pressed == 1) {
				return 0;
			}

		// calculate roll (left(+1) to right(-1)) and pitch(forward(-.3) or backward(+.3)).  Use the buttons to set the condition for roll and pitch
			roll_rad = roll(mag(x));
			pitch_rad = pitch(mag(z));
		// switch between roll and pitch(up vs. down button)
			if (pressed == 2 && let_off == true) {
				pt = t;
				if(mode == 1) {
					mode = 0;
				} else {
					mode = 1;
				}
				let_off = false;
			}

			if(pressed == 0 && t - pt > 1000) {
				let_off = true;
			}

			if(mode == 1) {
				selected = roll_rad;
			} else {
				selected = pitch_rad;
			}

		// Scale your output value	
			scaled_value = scaleRadsForScreen(selected);

		// Output your graph line
			graph_line(scaled_value);

		fflush(stdout);
	} while (1); // Modify to stop when the square button is pressed
	return 0;
}


double mag(double some_val) {
	if (some_val > 1) {
		return 1;
	} else if (some_val < -1) {
		return -1;
	} 

	return some_val;
}

void graph_line(int number) {		
	for(int i = 39; i > 0; i--) {
		if(number >= i){
			print_chars(i, 'L');
		} else {
			print_chars(i, ' ');
		}
	}

	print_chars(number, '0');

	for(int i = 0; i > -39; i--) {
		if(i >= number) {
			print_chars(i, 'R');
		} else{
			print_chars(i, ' ');
		}
	}

	print_chars(number, 's');
}

void print_chars(int num, char use) {
	if(use == 's'){
		use = '\n';
	}
	printf("%c", use);
}

int scaleRadsForScreen(double rad) {
	return round(39 * rad);
}

double pitch(double y_mag) {
	return y_mag;
}

double roll(double x_mag) {
	return x_mag;
}

int read_line(double* g_x, double* g_y, double* g_z, int* time, int* Button_T, int* Button_X, int* Button_S, int* Button_C) {
	
	scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d", time, g_x, g_y, g_z, Button_T, Button_C, Button_X, Button_S);

	if((int)*Button_S == 1) {
		return 1;
	} else if((int) *Button_T == 1){
		return 2;
	}
	
	return 0;
}