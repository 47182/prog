#include "main.h"

void powerDrive(int forwardpower, int turningpower){
left1 = forwardpower + turningpower;
left2 = forwardpower + turningpower;
left3 = forwardpower + turningpower;
left4 = forwardpower + turningpower;
right1 = forwardpower - turningpower;
right2 = forwardpower - turningpower;
right3 = forwardpower - turningpower;
right4 = forwardpower - turningpower;
}

void drivetime( int time ){
    int starttime = millis();


    while (time> millis()-starttime){ 

        powerDrive(127, 0);
    }

        powerDrive(0, 0);
}
void turntime( int time ){
    int starttime = millis();


    while (time> millis()-starttime){ 

        powerDrive(0, 55);
    }

        powerDrive(0, 0);
}

void turn(int target){ //target would be encoder ticks
    // imu.reset();
    while(fabs(target - imu.get_rotation()) > 0.5){
        if(target > imu.get_rotation() ){
        powerDrive(0,25);
        }
        else if(target < imu.get_rotation() ){
        powerDrive(0,-25);
        }
        
    }
    powerDrive(0, 0);
}

void drive(int target){
    left1.tare_position();
     while(fabs(target - left1.get_position()) > 2){
        if(target > left1.get_position() ){
        powerDrive(50,0);
        }
        else if(target < left1.get_position() ){
        powerDrive(-50,0);
        }
    }
    powerDrive(0, 0);
}
double inchestoticks(int distance) {
	double external,internal,diameter,pi;
	external = (double)3/5;
	internal = 300;
	diameter = 4.125;
	pi =3.14;
return (distance*internal*external/diameter*pi);
}

void PIDdrive(int inches, double kP, double kI, double kD) {
//declares variables
        left1.tare_position();
	double target = inchestoticks(inches);

	double error = target-left1.get_position();
	int Power;
	int integral;
	int derivative;
	int past_error;

//ensure function runs until robot position in within 2 encoder ticks
	while(fabs(target-left1.get_position()) > 2){
//calculating derivative
		past_error = error;
		error = target-left1.get_position();
		derivative = error - past_error;


//only using integral if within 10 encoder ticks of target
	
		if(fabs(target-left1.get_position())<10){

			integral+=error;
		}
//calculate motor power and assigning power to all motors

		Power = error*kP + integral*kI + derivative*kD;
		powerDrive(SpeedCap(Power),0);
	}
//setting all motors to 0 after function is done
	powerDrive(0,0);
}

void imuturn(int target, double kP, double kI, double kD) {
//declares variables

	double error = target-imu.get_rotation();
	int Power;
	int integral;
	int derivative;
	int past_error;

//ensure function runs until robot position in within 2 encoder ticks
	while(fabs(target-imu.get_rotation()) > 0.5){
//calculating derivative
		past_error = error;
		error = target-imu.get_rotation();
		derivative = error - past_error;


//only using integral if within 10 encoder ticks of target
	
		if(fabs(target-imu.get_rotation())<3){

			integral+=error;
		}
//calculate motor power and assigning power to all motors

		Power = error*kP + integral*kI + derivative*kD;
		powerDrive(0,Power);
	}
//setting all motors to 0 after function is done
	powerDrive(0,0);
}



int SpeedCap(int speed){
		int limit=100;
	if(abs(speed)<= limit){
	    return speed;
	}
	else {
        if (speed > limit){
            return limit;
            
        }
        else{
            return -limit;
        }
    }
    
}

void DriveStraight(int inches, double kP, double kI, double kD) {
//declares variables FOR DRIVING FORWARD
	int power, integral, past_error;
	double derivative, error, target;

//declares variable for turning

	int r_target,r_power,r_integral;
	double r_derivative, r_error;
	double r_kP, r_kI, r_kD, r_past_error;

r_kP=0.005;
r_kI=0.00;
r_kD=0;
//calculating error distance
	left1.tare_position();
	target = inchestoticks(inches);
	error = target-left1.get_position();

//set target for rotation
r_target=imu.get_rotation();
//ensure function runs until robot position in within 2 encoder ticks
	while((fabs(target-left1.get_position()) > 2)||(target-imu.get_rotation()) > 10 ){
//calculating derivative
		past_error = error;
		error = target-left1.get_position();
		//CALCULATES ERROR
		derivative = error - past_error;


//only using integral if within 10 encoder ticks of target
	
		if(fabs(target-left1.get_position())<10){

			integral+=error;
		}
//calculate motor power and assigning power to all motors

		power = error*kP + integral*kI + derivative*kD;
		
	
//calculating derivative
		r_past_error = r_error;
		r_error = target-imu.get_rotation();
		//CALCULATES ERROR
		r_derivative = r_error - r_past_error;


//only using integral if within 10 encoder ticks of target
	
		if(fabs(target-imu.get_rotation())<1){

			r_integral+=r_error;
		}
//calculate motor power and assigning power to all motors

		r_power = r_error*r_kP + r_integral*r_kI + r_derivative*r_kD;
		powerDrive(SpeedCap(power),r_power);
	}
//setting all motors to 0 after function is done
	powerDrive(0,0);
}