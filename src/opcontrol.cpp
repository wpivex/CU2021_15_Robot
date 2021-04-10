#include "opcontrol.hpp"
#include "PID.hpp"


void opcontrol() {

	deploy.set_value(true);
	deployed = true;

	while (true) {
		pros::lcd::print(0, "Encoder: %d", rightEncoder.get_value());

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
}
