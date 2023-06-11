#include "main.h"
#include "math.h"
using namespace pros;
Controller master(E_CONTROLLER_MASTER);
Motor left1(11,1);
Motor left2(12,1);
Motor left3(13,1);
Motor left4(14,1);
Motor right1(17);
Motor right2(18);
Motor right3(19);
Motor right4(20);
Imu imu(21);

void BrakeOn() {
	left1.set_brake_mode(MOTOR_BRAKE_BRAKE);
	left2.set_brake_mode(MOTOR_BRAKE_BRAKE);
	left3.set_brake_mode(MOTOR_BRAKE_BRAKE);
	left4.set_brake_mode(MOTOR_BRAKE_BRAKE);
	right1.set_brake_mode(MOTOR_BRAKE_BRAKE);
	right2.set_brake_mode(MOTOR_BRAKE_BRAKE);
	right3.set_brake_mode(MOTOR_BRAKE_BRAKE);
	right4.set_brake_mode(MOTOR_BRAKE_BRAKE);
}
void BrakeOff() {
	left1.set_brake_mode(MOTOR_BRAKE_COAST);
	left2.set_brake_mode(MOTOR_BRAKE_COAST);
	left3.set_brake_mode(MOTOR_BRAKE_COAST);
	left4.set_brake_mode(MOTOR_BRAKE_COAST);
	right1.set_brake_mode(MOTOR_BRAKE_COAST);
	right2.set_brake_mode(MOTOR_BRAKE_COAST);
	right3.set_brake_mode(MOTOR_BRAKE_COAST);
	right4.set_brake_mode(MOTOR_BRAKE_COAST);


}


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
delay(500);
imu.reset();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	DriveStraight(10,1,0,0);
/*BrakeOff();
PIDdrive(10,0.2,0.01,5);
	BrakeOn();
PIDdrive(10,0.2,0.01,5);
imu.reset();
//imuturn(90, 1, 0.01, 5);
// imuturn(-90, 1, 0.01, 5);*/
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	//DriveStraight(10,0.2,0.01,5);
	//PIDdrive(10,0.2,0.01,5);
	// drive(200);
	// turn(90);
	// drive(200);

	//drivetime(350);
	//delay(2000);
	//drivetime(-350)
	// drivetime(350);
	// delay(2000);
	// turntime(170);
	// delay(2000);
	// drivetime(1200);
	// turntime(311);
	while (true) {
//will print seconds started since program started on line 3
		screen::set_pen(COLOR_BLUE);
		screen ::print(TEXT_MEDIUM, 1, "temperature left1: %3f", left1.get_temperature());
		screen ::print(TEXT_MEDIUM, 2, "temperature: left2 %3f", left2.get_temperature());
		screen ::print(TEXT_MEDIUM, 3, "temperature: left3 %3f", left3.get_temperature());
		screen ::print(TEXT_MEDIUM, 4, "temperature: left4 %3f", left4.get_temperature());
		screen ::print(TEXT_MEDIUM, 5, "temperature: right1 %3f", right1.get_temperature());
		screen ::print(TEXT_MEDIUM, 6, "temperature:right2 %3f", right2.get_temperature());
		screen ::print(TEXT_MEDIUM, 7, "temperature: right3 %3f", right3.get_temperature());
		screen ::print(TEXT_MEDIUM, 8, "temperature:right4  %3f", right4.get_temperature());
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_LEFT_X);

		powerDrive(left,right);
		pros::delay(20);
	}
}
