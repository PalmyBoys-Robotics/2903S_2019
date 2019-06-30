#include "main.h"

#define COEFFICIENT_OF_SPEED 1.57
#define COEFFICIENT_OF_MEDIUM 1.0
#define COEFFICIENT_OF_SLOW 0.8

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
	// Use the controller for the
	pros::Controller masterController(pros::E_CONTROLLER_MASTER);

	// Speed setting
	int speedSetting = 0;

	// Motor contructors
	pros::Motor leftMotor(19, true);
	pros::Motor rightMotor(20);
	pros::Motor armMotor(18);

	leftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	// Rumble the controller
	masterController.rumble("... - - ...");

	pros::lcd::register_btn0_cb(autonomous);

	// While loop
	while (true) {
		if( masterController.get_digital(pros::E_CONTROLLER_DIGITAL_UP) ) {
			speedSetting = 0;
		}
		else if( masterController.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) || masterController.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) ) {
			speedSetting = 1;
		}
		else if( masterController.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) ){
			speedSetting = 2;
		}

		int left; int right;

		switch(speedSetting) {
			case 0:
				left = masterController.get_analog(ANALOG_LEFT_Y) * COEFFICIENT_OF_SPEED;
				right = masterController.get_analog(ANALOG_RIGHT_Y) * COEFFICIENT_OF_SPEED;
				break;
			case 1:
				left = masterController.get_analog(ANALOG_LEFT_Y) * COEFFICIENT_OF_MEDIUM;
				right = masterController.get_analog(ANALOG_RIGHT_Y) * COEFFICIENT_OF_MEDIUM;
				break;
			case 2:
				left = masterController.get_analog(ANALOG_LEFT_Y) * COEFFICIENT_OF_SLOW;
				right = masterController.get_analog(ANALOG_RIGHT_Y) * COEFFICIENT_OF_SLOW;
				break;
			default:
				left = masterController.get_analog(ANALOG_LEFT_Y) * COEFFICIENT_OF_MEDIUM;
				right = masterController.get_analog(ANALOG_RIGHT_Y) * COEFFICIENT_OF_MEDIUM;
				break;
		}

		pros::lcd::clear();

		// Right top
		if( masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R1) ) {
			armMotor.move_velocity(200);
		}
		else if( masterController.get_digital(pros::E_CONTROLLER_DIGITAL_R2) ) {
			armMotor.move_velocity(-200);
		}
		//if( leftMotor.is_over_current() || rightMotor.is_over_current() ) {
		//	masterController.rumble(".-.");
		//}

		// set the motor values for each
		leftMotor.move_velocity(left);
		rightMotor.move_velocity(right);

		// Don't hog the cpu
		pros::delay(20);
	}
}
