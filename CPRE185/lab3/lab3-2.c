/* 185 Lab 3 Template */

#include <stdio.h>
#include <math.h>

/* Put your function prototypes here */

int currentlyPressed(int b1, int b2, int b3, int b4);

int main(void) {
    int tri, cir, x, sqr;    

    /* This while loop makes your code repeat. Don't get rid of it. */
    while (1) {
        scanf("%d,%d,%d,%d", &tri, &cir, &x, &sqr);

        printf("%d buttons currently pressed\n", currentlyPressed(tri, cir, x, sqr));
        fflush(stdout);
    }

return 0;
}

/* Put your functions here */

int currentlyPressed(int b1, int b2, int b3, int b4) {
    int pressed = b1 + b2 + b3 + b4;
    return pressed;
}


