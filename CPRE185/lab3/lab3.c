/* 185 Lab 3 Template */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/* Put your function prototypes here */

double mag(double x, double y, double z);
int close_to(double tolerance, double point, double value);

int const MIN = 60000;
int const SEC = 1000;

int minutes(int t);
int seconds(int t);
int millis(int t);



int main(void) {
    /* DO NOT MODIFY THESE VARIABLE DECLARATIONS */
    int t;
    double gx, gy, gz, ax, ay, az, magnitude, a_mag;     
    bool falling = true;

    /* This while loop makes your code repeats. Don't get rid of it. */
    while (1) {
       scanf("%d, %lf, %lf, %lf", &t, &gx, &gy, &gz);

/* CODE SECTION 0 */
        // printf("Echoing OUTPUT: %8.3lf, %7.4lf, %7.4lf, %7.4lf\n", t/1000.00, ax, ay, az);

/* CODE SECTION 1 */
        // printf("At %d ms, the acceleration's magnitude was: %lf\n", 
        //     t, mag(ax, ay, az)); 
            
/* CODE SECTION 2 */

        magnitude = mag(gx, gy, gz);
        
        
            // printf("At %d minutes, %d seconds, and %d milliseconds it was: %lf\n", 
            // minutes(t), seconds(t), millis(t), mag(ax,ay,az)); 
            // printf("%d %.3lf what\n", t, mag(ax,ay,az));
            // printf("%lf %lf %lf %lf\n", mag(ax, ay, az), ax, ay, az);
        if(close_to(.5, 1, magnitude) == 0){ 
            if (magnitude > 1.5) {
                printf("SPLATTT");
                break;
            }
            printf("%.5lf %lf %lf %lf\n", magnitude, gx, gy, gz);
            fflush(stdout);
            
        } else {
            printf("\n");
        } 
        
        

        
        
        
        // printf("%d %.3lf", t, magnitude);
        
        
        fflush(stdout);
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
    return sqrt(pow(x,2) + pow(y,2) + pow(z,2));    
}

int minutes(int t) {

    // Takes milliseconds / CONST MIN 
    t = t / MIN; 
    
    return t;
}

int seconds(int t) {

    // milliseconds % CONST MIN then divides by CONST SEC
    t = t % MIN;
    t = t / SEC;

    return t;
}

int millis(int t) {

    // milliseconds % CONST SEC
    t = t % SEC;

    return t;
}

