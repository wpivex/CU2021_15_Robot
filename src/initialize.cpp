#include "main.h"

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



pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Motor frontRight(2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor middleRight(6, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backRight(10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor backLeft(20, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor middleLeft(14, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor frontLeft(12, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor leftConveyor(1, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightConveyor(9, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor leftIntake(18, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightIntake(16, pros::E_MOTOR_GEARSET_06, true,pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor leftIndexer(4, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightIndexer(8, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::ADIEncoder rightEncoder('E', 'F', true);
pros::ADIEncoder leftEncoder('C', 'D', false);
// pros::ADIEncoder backEncoder('A', 'B', true);
pros::ADIUltrasonic ultrasonicL ('A', 'B');
// pros::ADIUltrasonic ultrasonicR ('G', 'H');

int NUMBER_OF_SENSORS(8);
int ADI_EXPANDER_SMART_PORT(19);

pros::ADIUltrasonic ultrasonicR ({{ADI_EXPANDER_SMART_PORT,'a','b'}});
																		//Tuple -> {3wire expander port, ADI port on exapnder}
pros::ADIAnalogIn ls1({{ADI_EXPANDER_SMART_PORT,'a'}});
pros::ADIAnalogIn ls2({{ADI_EXPANDER_SMART_PORT,'b'}});
pros::ADIAnalogIn ls3({{ADI_EXPANDER_SMART_PORT,'c'}});
pros::ADIAnalogIn ls4({{ADI_EXPANDER_SMART_PORT,'d'}});
pros::ADIAnalogIn ls5({{ADI_EXPANDER_SMART_PORT,'e'}});
pros::ADIAnalogIn ls6({{ADI_EXPANDER_SMART_PORT,'f'}});
// pros::ADIAnalogIn ls7({{ADI_EXPANDER_SMART_PORT,'g'}});

// pros::ADIDigitalIn frontBumper('G');
pros::ADIDigitalIn leftBumper({{ADI_EXPANDER_SMART_PORT,'f'}});
pros::ADIDigitalIn rightBumper({{ADI_EXPANDER_SMART_PORT,'g'}});
pros::ADIDigitalOut deploy('H');

// pros::ADIGyro gyro('G' , 0.96);

//Initialize pointer to zero so that it can be initialized in first call to getInstance
LineTrack *LineTrack::instance = 0;

void setDrivePower(int forwardPower, int turnPower){
	float leftVal = -(forwardPower+turnPower);
	float rightVal = -(forwardPower-turnPower);
	frontLeft.move(leftVal);
	middleLeft.move(leftVal);
	backLeft.move(leftVal);
	frontRight.move(rightVal);
	middleRight.move(rightVal);
	backRight.move(rightVal);
}

void setRightPower(int forwardPower) {
	frontRight.move(forwardPower);
	middleRight.move(forwardPower);
	backRight.move(forwardPower);
}

void setLeftPower(int forwardPower) {
	frontLeft.move(forwardPower);
	middleLeft.move(forwardPower);
	backLeft.move(forwardPower);
}

void initialize() {
	deploy.set_value(false);
	pros::lcd::initialize();
	pros::lcd::set_text(4, "In Initialize");

	pros::lcd::register_btn1_cb(on_center_button);

	leftIndexer.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rightIndexer.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

	controller.clear();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	pros::lcd::set_text(4, "In Disabled");
	deploy.set_value(false);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

void competition_initialize() {
	pros::lcd::set_text(4, "In competition_initialize()");
	deploy.set_value(false);
}
