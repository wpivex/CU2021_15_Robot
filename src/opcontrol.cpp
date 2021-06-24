#include "opcontrol.hpp"
#include "PID.hpp"


void opcontrol() {
	// deploy.set_value(true);
	// deployed = true;

	while (true) {
		// pros::lcd::print(0, "Right Encoder: %d", rightEncoder.get_value());
		// pros::lcd::print(1, "Left Encoder: %d", leftEncoder.get_value());
		// pros::lcd::print(2, "Back Encoder: %d", backEncoder.get_value());


		double left = controller.get_analog(ANALOG_RIGHT_X)*1+controller.get_analog(ANALOG_RIGHT_Y);
		double right = -controller.get_analog(ANALOG_RIGHT_X)*1+controller.get_analog(ANALOG_RIGHT_Y);
		frontLeft.move(left);
	  	middleLeft.move(left);
		backLeft.move(left);
		frontRight.move(right);
		middleRight.move(right);
		backRight.move(right);

		handleIntakes();

		if (controller.get_digital_new_press(DIGITAL_RIGHT)) {
			deployed = !deployed;
			deploy.set_value(deployed);
		}

		pros::delay(10);
	}
}

void handleIntakes() {
	if (!indexTaskRunning) {
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
		if (controller.get_digital_new_press(DIGITAL_DOWN)) {
			opStartIndexingTask(0, false);
		}
		if (controller.get_digital_new_press(DIGITAL_LEFT)) {
			opShoot2descore2();
		}
		if (controller.get_digital_new_press(DIGITAL_UP)) {
			opShoot3descore2();
		}
	}
}

void opStartIndexingTask(int time, bool intakesOn) {
	indexTaskRunning = true;
	pros::delay(time);
	pros::Task ballIndexingTask{[=] {
				opIndexBalls();
				opsetIntakeSpeed((intakesOn)? 127: 0);
					indexTaskRunning = false;
	}};


}

void opIndexBalls() {
	opsetIntakeSpeed(127);//In
	opsetConveyorSpeed(-127); //Up
	opsetIndexerSpeed(-127); //Out

	pros::delay(400);

	opsetConveyorSpeed(100); //Up
	opsetIndexerSpeed(-100); //Out

	pros::delay(160);

	opsetConveyorSpeed(60); //Up
	opsetIndexerSpeed(-100); //Out

	pros::delay(520);

	opsetIntakeSpeed(0);//In

	opsetConveyorSpeed(0); //Up
	opsetIndexerSpeed(10); //Out

	pros::delay(120);

	opsetConveyorSpeed(-30); //Up

	opsetIntakeSpeed(-127);//In

	pros::delay(140);

	opsetConveyorSpeed(0); //Up

	opsetIndexerSpeed(0); //Out

}

void opShoot2descore2() {
	//first ball

	opsetConveyorSpeed(100); //Up
	opsetIndexerSpeed(127); //Out
	pros::delay(210);
	opsetConveyorSpeed(0); //Up
	opsetIndexerSpeed(-40); //Out

	pros::delay(200);
	opsetIndexerSpeed(0); //stop
	opsetConveyorSpeed(-40);
	pros::delay(150);


  //second ball
	opsetConveyorSpeed(127); //Up
	opsetIndexerSpeed(127); //Out
	pros::delay(350);
	opsetConveyorSpeed(0); //Up
	opsetIndexerSpeed(0); //Out

}
void opShoot3descore2() {
	opsetIntakeSpeed(127);//Out

	//first ball
	opsetConveyorSpeed(127); //Up
	opsetIndexerSpeed(127); //Out
	pros::delay(200);
	opsetConveyorSpeed(0); //Up
	opsetIndexerSpeed(0); //Out
	pros::delay(200);
	opsetIndexerSpeed(-127); //In
	pros::delay(200);


	//second ball
	opsetConveyorSpeed(100); //Up
	opsetIndexerSpeed(127); //Out
	pros::delay(300);
	opsetConveyorSpeed(0); //Up
	opsetIndexerSpeed(0); //Out
	pros::delay(200);

		opsetIntakeSpeed(0);
	pros::delay(150);
	//third ball
	opsetConveyorSpeed(100); //Up
	opsetIndexerSpeed(127); //Out
	pros::delay(300);
	opsetConveyorSpeed(0); //Up
	opsetIndexerSpeed(0); //Out
//	pros::delay(300);
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
