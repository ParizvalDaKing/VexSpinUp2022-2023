#include "autons.hpp"
#include "main.h"




/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 100; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;




///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

// . . .
// Make your own autonomous functions here!
// . . .
//Help Functions and Variables
pros::Motor intakeAuton(21,pros::E_MOTOR_GEARSET_06);
pros::Motor cataAuton(18,pros::E_MOTOR_GEARSET_36);
pros::ADIDigitalIn cataSwitchAuton ('H');
bool L1pushed = false;
int loopAttempts = 0;
int cataSpeed = 0;

void rollSpiner() {
  chassis.set_drive_pid(14, DRIVE_SPEED, true);
  chassis.wait_drive();
  ///intakeAuton = -110;
  pros::delay(150);
  //intakeAuton = 0;
  chassis.set_drive_pid( -14, DRIVE_SPEED, true);
  chassis.wait_drive();
}
void rollSpinerMove() {
  chassis.set_drive_pid(30, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.reset_gyro(0);
}
void nothing() {
  chassis.set_drive_pid(8, DRIVE_SPEED, true);
}
void skills() {
  pros::c::adi_pin_mode('G', OUTPUT);
  chassis.set_drive_pid(10, DRIVE_SPEED, true);
  chassis.wait_drive();
  intakeAuton = -100;
  pros::delay(200);
  intakeAuton = 0;
  chassis.set_drive_pid( -10, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(145, TURN_SPEED);
  chassis.reset_gyro(0);
  chassis.wait_drive();
  intakeAuton = 105;
  chassis.set_drive_pid(52, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(500);
  intakeAuton = 0;
  chassis.set_drive_pid(20, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-60, TURN_SPEED);
  chassis.reset_gyro(0);
  chassis.wait_drive();
  chassis.set_drive_pid(22, DRIVE_SPEED);
  chassis.wait_drive();
  intakeAuton = -100;
  pros::delay(200);
  intakeAuton = 0;
  chassis.set_drive_pid(-22, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.reset_gyro(0);
  chassis.wait_drive();
  chassis.set_drive_pid(-170, DRIVE_SPEED);
  chassis.wait_drive();
   chassis.set_turn_pid(20, TURN_SPEED);
  chassis.reset_gyro(0);
  chassis.wait_drive();
  cataAuton = 127;
  pros::delay(700);
  cataAuton = 0;
  while (!cataSwitchAuton.get_value()) {
      // move cata motor until switch is pressed
     cataAuton = 127;
  }
  cataAuton = 0;
  pros::delay(1000);
  chassis.set_turn_pid(-12, TURN_SPEED);
  chassis.reset_gyro();
  chassis.wait_drive();
  chassis.set_drive_pid(-111, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.reset_gyro(0);
  chassis.wait_drive();
  chassis.set_drive_pid(-280, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.reset_gyro(0);
  chassis.wait_drive();
  chassis.set_drive_pid(17, DRIVE_SPEED);
  chassis.wait_drive();
  intakeAuton = -100;
  pros::delay(200);
  intakeAuton = 0;
  chassis.set_drive_pid( -20, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(145, TURN_SPEED);
  chassis.reset_gyro(0);
  chassis.wait_drive();
  intakeAuton = 105;
  chassis.set_drive_pid(42, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(500);
  intakeAuton = 0;
  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-60, TURN_SPEED);
  chassis.reset_gyro(0);
  chassis.wait_drive();
  chassis.set_drive_pid(35, DRIVE_SPEED);
  chassis.wait_drive();
  intakeAuton = -100;
  pros::delay(200);
  intakeAuton = 0;
  chassis.set_drive_pid(-35, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.reset_gyro(0);
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.reset_gyro(0);
  chassis.wait_drive();
  // //expand
  // //pros::c::adi_digital_write('G', HIGH);
}