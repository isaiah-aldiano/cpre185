#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>


int close_to(double tolerance, double point, double value);
double mag(double x, double y, double z); //normalized acceleration
double fall_distance(double seconds);
double air_resistance(double seconds, double acc_mag);


const double GRAVITY = 9.8;

int main() {

    printf("Isaiah Aldiano\n");
    printf("490845364\n");

    bool waiting = true;
    bool hasFallen = false;

    int t, cnt_input, initial_t, final_t, delta_t, previous_t;
    double gx, gy, gz, converted_sec, fd, acc_mag, f_velocity, test_distance;


    while(1) {
        scanf("%d, %lf, %lf, %lf, %lf, %lf, %lf", &t, &gx, &gy, &gz);
        
        //This variable increases to check if it should output a '.' for "I'm waiting..."
        cnt_input++;

        if(close_to(.5, 1, mag(gx, gy, gz)) == 1 && cnt_input == 20 && waiting == true) {
            cnt_input = 0;
            printf(".");
            fflush(stdout);

        } else if (close_to(.5, 1, mag(gx, gy, gz)) == 0 && hasFallen == false) {
            waiting = false;
            hasFallen = true;

            initial_t = t;
            previous_t = t;

            printf("\n\tHelp me! I'm falling");
            fflush(stdout);
        }

        if(close_to(.5, 1, mag(gx, gy, gz)) == 0 && mag(gx, gy, gz) < 1.1){
            printf("!");
            fflush(stdout);

            f_velocity = f_velocity + GRAVITY * (1 - mag(gx, gy, gz))*(t/1000 - previous_t/1000);
            test_distance = test_distance + f_velocity*(t/1000 - previous_t/1000);
            previous_t = t; 

            
        } else if(hasFallen == true && (close_to(.5, 1, mag(gx, gy, gz)) == 1 || mag(gx, gy, gz) > 1.5)) {
            final_t = t;
            delta_t = final_t - initial_t;
            converted_sec = delta_t/1000.0;

            fd = fall_distance(converted_sec);
            printf("\nOuch! I fell %.3lf meters in %.3lf seconds", fd, converted_sec);
            printf("\n%.5lf %.5lf %.5lf", f_velocity, test_distance, fabs(((test_distance - fd)/fd)));
            
            fflush(stdout);   
            break;
        }

        // printf("%.5lf %.5lf\n", mag(ax, ay, az), mag(gx, gy, gz));
        

          
    }
}


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

double fall_distance(double seconds) {
    double fd = 0;
    
    fd = .5 * GRAVITY * pow(seconds, 2);
    
    return fd;

}

double air_resistance(double init_t, double mag_a) {
    double vi = GRAVITY * (1 - mag_a*((init_t/1000) - ((init_t/1000) - 1)));

    return vi;
}