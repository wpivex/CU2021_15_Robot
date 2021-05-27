#include "main.h"

// lv_obj_t * myButton;
// lv_obj_t * myButtonLabel;
// lv_obj_t * myLabel;
// lv_obj_t * btn;
// lv_obj_t * obj1;
//
// lv_style_t myButtonStyleREL; //relesed style
// lv_style_t myButtonStylePR; //pressed style
// lv_style_t fieldBGStyle; //pressed style


void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		// pros::lcd::set_text(2, "I was pressed!");
	} else {
		// pros::lcd::clear_line(2);
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
pros::ADIUltrasonic ultrasonicR ('G', 'H');

int NUMBER_OF_SENSORS(8);
int ADI_EXPANDER_SMART_PORT(16);

// pros::ADIUltrasonic ultrasonicR ({{ADI_EXPANDER_SMART_PORT,'a','b'}});
																		//Tuple -> {3wire expander port, ADI port on exapnder}
pros::ADIAnalogIn ls1({{ADI_EXPANDER_SMART_PORT,'a'}});
pros::ADIAnalogIn ls2({{ADI_EXPANDER_SMART_PORT,'b'}});
pros::ADIAnalogIn ls3({{ADI_EXPANDER_SMART_PORT,'c'}});
pros::ADIAnalogIn ls4({{ADI_EXPANDER_SMART_PORT,'d'}});
pros::ADIAnalogIn ls5({{ADI_EXPANDER_SMART_PORT,'e'}});
pros::ADIAnalogIn ls6({{ADI_EXPANDER_SMART_PORT,'f'}});
pros::ADIAnalogIn ls7({{ADI_EXPANDER_SMART_PORT,'g'}});

// pros::ADIDigitalIn frontBumper('G');
pros::ADIDigitalIn leftBumper({{ADI_EXPANDER_SMART_PORT,'g'}});
pros::ADIDigitalIn rightBumper({{ADI_EXPANDER_SMART_PORT,'f'}});
pros::ADIDigitalOut deploy('H');

// pros::ADIGyro gyro('G' , 0.96);
const int IMU_PORT = 19;
pros::Imu imu_sensor(IMU_PORT);

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
	// imu_sensor.reset();

	deploy.set_value(false);
	pros::lcd::initialize();
	pros::lcd::set_text(4, "In Initialize");

	pros::lcd::register_btn1_cb(on_center_button);

	leftIndexer.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	rightIndexer.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

	controller.clear();

  // lv_obj_set_x(btn1, 30);
  // lv_obj_set_y(btn1, 10);
  // lv_obj_set_size(btn1, 200, 50);

	// lv_style_copy(&myButtonStyleREL, &lv_style_plain);
	// myButtonStyleREL.body.main_color = LV_COLOR_MAKE(150, 0, 0);
	// myButtonStyleREL.body.grad_color = LV_COLOR_MAKE(0, 0, 150);
	// myButtonStyleREL.body.radius = 0;
	// myButtonStyleREL.text.color = LV_COLOR_MAKE(255, 255, 255);
  //
  //
  // lv_style_copy(&fieldBGStyle, &lv_style_plain);
  // fieldBGStyle.body.main_color = LV_COLOR_MAKE(0, 150, 0);
  // fieldBGStyle.body.grad_color = LV_COLOR_MAKE(0, 0, 150);
  // fieldBGStyle.body.radius = 0;
  // fieldBGStyle.text.color = LV_COLOR_MAKE(255, 255, 255);
	// lv_style_copy(&fieldBGStyle, &lv_style_plain);
	// fieldBGStyle.body.radius = 0;
	// myButtonStylePR.text.color = LV_COLOR_MAKE(255, 255, 255);
  //
	// myButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
	// lv_obj_set_free_num(myButton, 0); //set button is to 0
	// lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
	// lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &fieldBGStyle); //set the relesed style
	// lv_btn_set_style(myButton, LV_BTN_STYLE_PR, &fieldBGStyle); //set the pressed style
	// lv_obj_set_size(myButton, 200, 50); //set the button size
	// lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10); //set the position to top mid
  // //
	// myButtonLabel = lv_label_create(myButton, NULL); //create label and puts it inside of the button
	// lv_label_set_text(myButtonLabel, "Click the Button"); //sets label text
  //
	// myLabel = lv_label_create(lv_scr_act(), NULL); //create label and puts it on the screen
	// lv_label_set_text(myLabel, "Button has not been clicked yet"); //sets label text
	// lv_obj_align(myLabel, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0); //set the position to center

  // btn = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
  // lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
  // lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
  // // lv_obj_set_event_cb(btn, btn_event_cb);                 /*Assign a callback to the button*/
  //
  // lv_obj_t * label = lv_label_create(btn, NULL);          /*Add a label to the button*/
  // lv_label_set_text(label, "Button");                     /*Set the labels text*/

  /* Create a slider in the center of the display */
  // lv_obj_t * slider = lv_slider_create(lv_scr_act(), NULL);
  // lv_obj_set_width(slider, 200);                        /*Set the width*/
  // lv_obj_align(slider, NULL, LV_ALIGN_CENTER, 0, 0);    /*Align to the center of the parent (screen)*/
  // lv_obj_set_event_cb(slider, slider_event_cb);         /*Assign an event function*/

  // obj1 = lv_btn_create(lv_scr_act(), NULL);
  // lv_btn_set_size(obj1, 236, 236);
  // lv_btn_align(obj1, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
  // lv_btn_set_style(obj1, &myButtonStyleREL);
  // lv_obj_set_drag(obj1, true);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	// pros::lcd::set_text(4, "In Disabled");
	deploy.set_value(false);
	imu_sensor.reset();
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
	// pros::lcd::set_text(4, "In competition_initialize()");
	deploy.set_value(false);
	imu_sensor.reset();
}
