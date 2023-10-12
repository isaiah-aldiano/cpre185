#include <stdio.h>
#include <math.h>

double mag(double a, double b, double c);
int close_to(double tolerance, double point, double value);


int main(void) {
	int time; //number of milliseconds since ds4rd.exe has started running
	double gx, gy, gz;
	double magnitude;

	printf("Isaac Heng\nitheng@iastate.edu\n");
	
	scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
	printf("Okay, I'm now receiving data.\n");
	printf("I'm waiting");
	
	while (close_to(0.1,1.0,mag(gx,gy,gz))) {  //loop is exited when the acceleration becomes too great
		
		scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);    //scanning values from ds4rd.exe
	
		fflush(stdout);
		
		if (time % 10 == 0) {
			printf(".");        //printing a period every ten milliseconds
	
		}
		
	}
		
		int firstTime = time;
		
		printf("\nHelp me! I'm falling!");
double velocityPrev = 0;
double previousTime = 0;
double airPrev = 0;
double resistanceTotal = 0;
double airResistance = 0;
double actualVelocity = 0;
previousTime = time;



   while (mag(gx,gy,gz) < 1.5) {
		// while (mag(gx,gy,gz) < 1.5) {
		
		scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz); //scanning values from ds4rd.exe

		actualVelocity = velocityPrev + 9.8 * (1 - mag(gx,gy,gz)) * (time/1000.0 - previousTime/1000.0);
		velocityPrev = actualVelocity;

		airResistance = airPrev + actualVelocity * (time/1000.0 - previousTime/1000.0);
		airPrev = airResistance;

		previousTime = time;
		
		
		
		if (time % 10 == 0) {
			
			printf("!");   
		}
		fflush(stdout);
	}
	
	double distanceFalling;
	double timeFalling;
	
	timeFalling = (time - firstTime) / 1000.0;                        // calculates the time the controller fell for
	distanceFalling = 0.5 * 9.8 * (timeFalling * timeFalling);        // calculates the distance the controller fell based on the time
	
	printf("\nOuch! I fell %4.3lf meters in %4.3lf seconds.", distanceFalling, timeFalling);
		
		double percentError = airResistance / distanceFalling;
		double calcError = 1.0 - percentError;

		printf("\nCompensating for air resistance, the fall was %lf meters", airResistance);
		printf("\nThis is %lf%% less than computed before.", calcError * 100);
	
	
	return 0;
}

double mag(double a, double b, double c) { //computes the magnitude of the controller and returns it
	
	double asquared = pow(a, 2);
	double bsquared = pow(b, 2);
	double csquared = pow(c, 2);
	double temp = asquared + bsquared + csquared;
	double magnitude = sqrt(temp);
	
	return magnitude;
}

int close_to(double tolerance, double point, double value) { //tests if a point is within the tolerance of a value
	if (fabs(point - value) < tolerance) { 
	return 1; 
	}
	else {
		return 0;
	}
}