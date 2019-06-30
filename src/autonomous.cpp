#include "main.h"

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
  // Define our motors
  pros::Motor leftMotor(19, true);
	pros::Motor rightMotor(20);

  // Hold Mode
  leftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	rightMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  // We will now move a set position.
  // Make suer we are tared at the current position.
  leftMotor.tare_position();
  rightMotor.tare_position();

  // Now move a preset distance.
  // We are using degrees,
  // We are using 4" wheels.
  // 24 inches / 4 inches = 5 rotations = 360*5 degrees = 1800degrees
  leftMotor.move_velocity(50);
  rightMotor.move_velocity(50);
  pros::delay(5000);

  // Move backwards and have some fun.
  leftMotor.move_velocity(-200);
  rightMotor.move_velocity(-200);

  pros::delay(2500);

  leftMotor.move_velocity(0);
  rightMotor.move_velocity(0);
}
