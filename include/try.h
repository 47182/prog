#ifndef _TRY_HPP_
#define _TRY_HPP_
void powerDrive(int forwardpower, int turningpower);
void turntime( int time );
void drivetime( int time );
void turn(int target);
void drive(int target);
double inchestoticks(int distance);
void PIDdrive(int inches, double kP, double kI, double kD);
void imuturn(int target, double kP, double kI, double kD);
int SpeedCap(int speed);
void DriveStraight(int inches, double kP, double kI, double kD);
#endif