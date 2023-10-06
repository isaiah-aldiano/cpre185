/*-----------------------------------------------------------------------------
-					         SE/CprE 185 Lab 04
-             Developed for 185-Rursch by T.Tran and K.Wang
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-	                            Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>


/*-----------------------------------------------------------------------------
-	                            Defines
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
-	                            Prototypes
-----------------------------------------------------------------------------*/
int close_to(double tolerance, double point, double value);
double mag(double x, double y, double z); //normalized acceleration
int checking_x(double x);
int checking_y(double y);
int checking_z(double z);


/*-----------------------------------------------------------------------------
-							  Implementation
-----------------------------------------------------------------------------*/
int main(void) {
    int t, b1, b2, b3, b4;
    double ax, ay, az, gx, gy, gz;
    enum orientation {TOP, BOTTOM, RIGHT, LEFT, BACK, FRONT};
    enum orientation currOri;
    enum orientation pastOri = -1;
    char positions [6][7] = {"TOP", "BOTTOM", "RIGHT", "LEFT", "BACK", "FRONT"};


    while (1) {
        if(b1 == 1) {
            break;
        }

        scanf("%d, %lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d", &t, &ax, &ay, &az, &gx, &gy, &gz, &b1, &b2, &b3, &b4 );

        /* printf for observing values scanned in from ds4rd.exe, be sure to comment or remove in final program */
        // printf("Echoing output: %d, %lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d \n", t, ax, ay, az, gx, gy, gz, b1, b2, b3, b4);
 
        /* It would be wise (mainly save time) if you copy your code to calculate the magnitude from last week
         (lab 3).  You will also need to copy your prototypes and functions to the appropriate sections
         in this program. */


        // printf("At %d ms, the acceleration's magnitude was: %f\n", t, mag(ax, ay, az));        

        if(checking_y(gy) == 1) {
            currOri = TOP;
        } else if (checking_y(gy) == 0) {
            currOri = BOTTOM;
        } else if (checking_x(gx) == 1) {
            currOri = RIGHT;
        } else if (checking_x(gx) == 0) {
            currOri = LEFT;
        } else if (checking_z(gz) == 1) {
            currOri = BACK;
        } else if (checking_z(gz) == 0) {
            currOri = FRONT;
        }

        if(pastOri != currOri) {
            printf("%s\n", positions[currOri]);
        }

        pastOri = currOri;

        // printf("%s: %8.3lf, %7.4lf, %7.4lf, %7.4lf\n",positions[currOri], t/1000.00, gx, gy, gz);
    }

    return 0;
}



/* Put your functions here */


int close_to(double tolerance, double point, double value) {
    if(value < (point + tolerance) && value > (point - tolerance)) {
        return 1;
    }

    return 0;

}

double mag (double x, double y, double z) {
    double magnitude;

    magnitude = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
    return magnitude;
}

int checking_x(double x) {
    
    if(close_to(.2, .9, x)){
        return 1;
    }

    if(close_to(.2, -.9, x)){
        return 0;
    } 

    return 2;
}

int checking_y(double y) {
        if(close_to(.2, .9, y)) {
            return 1;
        }

        if(close_to(.2, -.9,y)){
            return 0;
        } 

    return 2; 
}

int checking_z(double z) {
    if(close_to(.2, .9, z)){
        return 1;
    }

    if(close_to(.2, -.9,z)){
        return 0;
    } 

    return 2;
}


