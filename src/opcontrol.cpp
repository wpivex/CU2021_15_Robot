#include "opcontrol.hpp"
#include "PID.hpp"


void opcontrol() {

	deploy.set_value(true);
	deployed = true;

	while (true) {
		// pros::lcd::print(0, "Right Encoder: %d", rightEncoder.get_value());
		// pros::lcd::print(1, "Left Encoder: %d", leftEncoder.get_value());
		// pros::lcd::print(2, "Back Encoder: %d", backEncoder.get_value());


		double left = controller.get_analog(ANALOG_RIGHT_X)*0.7+controller.get_analog(ANALOG_RIGHT_Y);
		double right = -controller.get_analog(ANALOG_RIGHT_X)*0.7+controller.get_analog(ANALOG_RIGHT_Y);
		frontLeft.move(left);
	  middleLeft.move(left);
		backLeft.move(left);
		frontRight.move(right);
		middleRight.move(right);
		backRight.move(right);

		handleIntakes();

		if (controller.get_digital_new_press(DIGITAL_LEFT)) {
			deployed = !deployed;
			deploy.set_value(deployed);
		}

		pros::delay(10);
	}
}

void handleIntakes() {
	int intakePower = 0;
	int conveyorPower = 0;
	int indexerPower = 0;

	if (controller.get_digital(DIGITAL_L1)) {
		intakePower+=127;
		conveyorPower+=127;
		indexerPower = -40;
	}
	else if (controller.get_digital(DIGITAL_L2)) {
		intakePower-=127;
		conveyorPower-=127;
		indexerPower-=127;
	}

	if (controller.get_digital(DIGITAL_R1)) {
		indexerPower = 127;
		conveyorPower = 70;
	}


	leftConveyor.move(conveyorPower);
	rightConveyor.move(conveyorPower);

	leftIntake.move(intakePower);
	rightIntake.move(intakePower);

	leftIndexer.move(indexerPower);
	rightIndexer.move(indexerPower);
	if (controller.get_digital_new_press(DIGITAL_B)) {
		opIndexBalls();
	}
	if (controller.get_digital_new_press(DIGITAL_A)) {
		opShoot2descore2();
	}
}

void opIndexBalls() {
	opsetIntakeSpeed(127);//In
	opsetConveyorSpeed(-127); //Up
	opsetIndexerSpeed(-127); //Out

	pros::delay(400);

	opsetConveyorSpeed(127); //Up
	opsetIndexerSpeed(-80); //Out

	pros::delay(400);


	opsetIntakeSpeed(0);//In
	opsetConveyorSpeed(0); //Up
	opsetIndexerSpeed(0); //Out
}

void opShoot2descore2() {
	//first ball

	opsetConveyorSpeed(100); //Up
	opsetIndexerSpeed(127); //Out
	pros::delay(215);
	opsetConveyorSpeed(30); //Up
	opsetIndexerSpeed(-100); //Out
	pros::delay(500);


  //second ball
	opsetConveyorSpeed(100); //Up
	opsetIndexerSpeed(127); //Out
	pros::delay(200);
	opsetConveyorSpeed(0); //Up
	opsetIndexerSpeed(0); //Out
	pros::delay(300);
}

void opsetIntakeSpeed(int power){
		leftIntake.move(power);
		rightIntake.move(power);
}

void opsetConveyorSpeed(int power){
		leftConveyor.move(power);
		rightConveyor.move(power);
}

void opsetIndexerSpeed(int power){
		leftIndexer.move(power);
		rightIndexer.move(power);
}
