#include <stdio.h>
#include <math.h>
#include <stdbool.h>


int close_to(double tolerance, double point, double value);
double mag(double x, double y, double z); //normalized acceleration
double fall_distance(double seconds);

const double GRAVITY = 9.8;

int main() {

    printf("Isaiah Aldiano\n");
    printf("490845364\n");

    bool waiting = true;
    bool falling = false;
    bool hasFallen = false;

    int t, cnt_input, initial_t, final_t, delta_t;
    double gx, gy, gz, converted_sec, fd;

    printf("Ok, I'm now receiving data.\n\tI'm waiting");


    while(1) {
        scanf("%d, %lf, %lf, %lf", &t, &gx, &gy, &gz );
        
        //This variable increases to check if it should output a '.' for "I'm waiting..."
        cnt_input++;

        //Continously outputs periods until magnitude is greater than 1 (ie controller is falling)
        if(close_to(.5, 1, mag(gx, gy, gz)) == 1 && cnt_input == 20 && waiting == true) {
            printf(".");
            cnt_input = 0;
            fflush(stdout);

        }

        /*
            Checks if magnitude is greater than 1.
            If greater than 1 then an '!' is printed to screen
        */
        if(close_to(.5, 1, mag(gx, gy, gz)) != 1){
            waiting = false;
            
            if (falling == false) {
                printf("\n\t\tHelp me! I'm falling");
                initial_t = t;
                falling = true;
                hasFallen = true;
            }
            printf("! ");

            fflush(stdout);
        }

        if(hasFallen == true &&  (close_to(.1, 1, mag(gx, gy, gz)) == 1 || mag(gx, gy, gz) > 1.2)) {
            final_t = t;
            delta_t = final_t - initial_t;
            converted_sec = delta_t/1000.0;

            fd = fall_distance(converted_sec);
            // printf("%.3lf %.3lf %d %d %d", converted_sec, fd, initial_t, final_t, delta_t);
            printf("\nOuch! I fell %.3lf meters in %.3lf seconds", fd, converted_sec);
            break;
        }

        fflush(stdout);     
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