#include "autonomous.hpp"

/*
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
//pros::ADIGyro gyro(3);

int side = 1;
void autonomous() {
	drivePID = pidInit (0.34, 0, 0.4, 0, 100.0,5,15);
	gyroDrivePID = pidInit(0.7, 0, 0.4, 0, 40,999999,9999999);
	gyroPID = pidInit(1.62,  0, 0.08, 0, 10,99999,999999); //1.6, 0, 0.62, 1.3,0,0.51
	//pros::lcd::clear();
//	indexer.move(127);
	stop();

	gyro.reset();
	lastSlewTime = pros::millis();
	pros::delay(2000);

	programmingSkills();
	//gyroTurn(-90, 0, 100000);


	stop();
}

void setIntakeSpeed(int power){
		leftIntake.move(power);
		rightIntake.move(power);
}

void setConveyorSpeed(int power){
		leftConveyor.move(power);
		rightConveyor.move(power);
}

void setIndexerSpeed(int power){
		leftIndexer.move(power);
		rightIndexer.move(power);
}

void programmingSkills(){
	setIntakeSpeed(127);//In
	setConveyorSpeed(60); //Up
	setIndexerSpeed(-70); //Out
	driveTarget(1050,0,0,2500);

	driveTarget(-320,0,0,1200);
	setIntakeSpeed(0);//In
	setConveyorSpeed(-30); //Up
	setIndexerSpeed(-80); //Out
	gyroTurn(-70,0,1200);
	setIntakeSpeed(127);//In
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	driveTarget(430,-70,0,1200);

	shoot3descore2();

	setIntakeSpeed(-80);
	setConveyorSpeed(-127);
	setIndexerSpeed(-127);
	driveTarget(-350,-69,0,1200);
	gyroTurnRelative(-167, 0, 1200);
	setIntakeSpeed(127);//In
	setConveyorSpeed(60); //Up
	setIndexerSpeed(-70); //Out
	driveTargetRelative(1110,0,2000);
	gyroTurnRelative(106,0,1200);
	driveTargetRelative(700,0,1300);

	shoot1descore1();

	setIntakeSpeed(127);
	setConveyorSpeed(0);
	setIndexerSpeed(0);

	driveTargetRelative(-150,0,800);
	setIntakeSpeed(-70);
	setConveyorSpeed(-127);

	gyroTurnRelative(15,0,400);

	gyroTurnRelative(-97,0,1200);
	setIntakeSpeed(127);//In
	setConveyorSpeed(60); //Up
	setIndexerSpeed(-70); //Out
	driveTargetRelative(1060,0,2000);
	gyroTurnRelative(45,0,1200);

	//To 3rd Goal
  driveTargetRelative(300,0,800);
	pros::delay(200);
	shoot1descore1();

	setIntakeSpeed(0);
	setConveyorSpeed(0);
	setIndexerSpeed(0);

	driveTargetRelative(-200,0,1300);
	setIntakeSpeed(-127);
	setConveyorSpeed(-127);
	setIndexerSpeed(-127);






	gyroTurnRelative(-90,0,1200);
	setIntakeSpeed(127);//In
	setConveyorSpeed(60); //Up
	setIndexerSpeed(-70); //In
	driveTargetRelative(280,0,1000);

	driveTargetRelative(-340,0,800);
	gyroTurnRelative(-53, 0, 1000);

	setupIntake();
	driveTargetRelative(1150,0,2500);

	gyroTurnRelative(100, 0, 1200);

	stop();

	// gyroTurn(90, 0.5, 2500);s
	// driveTarget(500,90,0,2500);
	// gyroTurn(180, 0.5, 2500);
	// driveTarget(500, 180,0,2500);
	// gyroTurn(270, 0.5, 2500);
	// driveTarget(500,270,0,2500);
	// gyroTurn(360, 0, 2500);
}

void setupIntake(){
	setIntakeSpeed(127);//In
	setConveyorSpeed(60); //Up
	setIndexerSpeed(-70); //In
}

void shoot1descore1() {
	setConveyorSpeed(100); //Up
	setIndexerSpeed(127); //Out
	pros::delay(200);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	pros::delay(300);
}
void shoot3descore2() {
	setIntakeSpeed(127);//In

	//first ball
	setConveyorSpeed(100); //Up
	setIndexerSpeed(127); //Out
	pros::delay(200);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	pros::delay(300);


  //second ball
	setConveyorSpeed(100); //Up
	setIndexerSpeed(127); //Out
	pros::delay(200);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	pros::delay(250);
	setIntakeSpeed(0);

	//third ball
	setConveyorSpeed(100); //Up
	setIndexerSpeed(127); //Out
	pros::delay(400);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	pros::delay(300);
}

void driveTarget(int target, float angle, int accuracy, int time) {
	driveTarget(target, angle, accuracy, time, 1, true);
}

void driveTargetRelative(int target, int accuracy, int time) {
	driveTarget(target, idealHeading, accuracy, time, 1, true);
}

void driveTarget(int target, float angle, int accuracy, int time, float max, bool slew) {
	idealHeading = angle;
	angle = angle*side;
	//pros::lcd::print(0, "Driving to target");
	//pros::lcd::print(2, "target: %d\n", target);
	int startTime = pros::millis();
	bool atTarget = false;
	//int targetAngle = gyro.get_value()/10.0;
	int targetAngle = angle;
	int repsAtTarget = 0;
  float driveEnc = 0;
	lastSlewTime = pros::millis()-10;
	lastSlewRate = 0;
	//go into the loop that will repeat to update motor values and break when at target
	while (!atTarget && (pros::millis()-startTime) < time) {
		auxiliary();
    driveEnc = (backLeft.get_position() + backRight.get_position())/2;
		//calculate the value the motors should be set at based on its position relative to the target
		float val = pidCalculate(drivePID, target, driveEnc)*max;
		val = slewRateCalculate(val);
		//the left and right drive values should be different in order to correct getting turned as specified by the gyro value
		int rightVal = val - (pidCalculate(gyroDrivePID, angle, gyro.get_value()/10.0)) * (val/127);
		int leftVal = val + pidCalculate(gyroDrivePID, angle, gyro.get_value()/10.0) * (val/127);

		frontLeft.move(leftVal);
	  middleLeft.move(leftVal);
		backLeft.move(leftVal);
		frontRight.move(rightVal);
		middleRight.move(rightVal);
		backRight.move(rightVal);


		//if the sensor value is within the desired range of the target
		if (fabs(driveEnc-target) < accuracy) {
			//if the sensor value is within the range for multiple iterations of the loop where each loop is approximately 20ms
			if (repsAtTarget > 15) {
				//break out of the while loop
				atTarget = true;
			}
			else {
				repsAtTarget++;
			}
		}
		else {
			repsAtTarget = 0;
		}
		pros::delay(15);
	}
	//pros::lcd::print(5, "Out of loop");
	//zero the value of the encoder so that the next time this procedure is called, the encoder will be starting at zero again

  //LD.set_zero_position(driveEnc-target);
  //RD.set_zero_position(driveEnc-target);
	stop();
}

void gyroTurnRelative(float target, int accuracy, int time){
	gyroTurn(idealHeading + target, accuracy, time, false);
}
void gyroTurn(float target, int accuracy, int time) {
 gyroTurn(target, accuracy, time, false);
}

void gyroTurn(float target, int accuracy, int time, bool precise) {
	idealHeading = target;
	target = target*side;
	int startTime = pros::millis();
	bool gyroAtTarget = false;
	int repsAtTarget = 0;
	//go into the loop that will repeat to update motor values and break when at target
	while (!gyroAtTarget  && (pros::millis()-startTime) < time) {
		pros::lcd::print(7, "Angle: %f", gyro.get_value()/10.0);
		auxiliary();
		// calculate the desired motor value based on the sensor value relative to the target
		float drive = pidCalculate(gyroPID, target, gyro.get_value()/10.0)*((precise)? 0.75: 1);
		drive = slewRateCalculate(drive);
	//	drive = ((fabs(gyro.get_value()/10.0-target)>180)? -1 : 1)*drive;
	frontLeft.move(drive);
	middleLeft.move(drive);
	backLeft.move(drive);
	frontRight.move(-drive);
	middleRight.move(-drive);
	backRight.move(-drive);
		//if the sensor value is within the desired range of the target
		if (fabs(gyro.get_value()/10.0-target) < accuracy) {
			//if the sensor value is within the range for multiple iterations of the loop where each loop is approximately 20ms
			if (repsAtTarget > 25) {
				//break out of the loop
				gyroAtTarget = true;
			}
			else {
				repsAtTarget++;
			}
		}
		else {
			repsAtTarget = 0;
		}
		pros::delay(15);
	}
//	LD.set_zero_position(LD.get_position()-RD.get_position()); //zero the value of the drive encoder
  //RD.set_zero_position(LD.get_position()-RD.get_position());
	stop();
}


void auxiliary() {

}


float
slewRateCalculate (float desiredRate) {
		//pros::lcd::print(7, "called: %f", desiredRate);
		float deltaTime = pros::millis()-lastSlewTime;
		float desiredAccel = (desiredRate -lastSlewRate)/deltaTime;
		float addedRate;
		float newRate;

		if (fabs(desiredAccel) < maxAccel || (desiredAccel<0 && desiredRate>0) || (desiredAccel>0 && desiredRate<0)) {
		    addedRate = desiredAccel*deltaTime;
		    newRate = addedRate+lastSlewRate;
		}
		else {
		    addedRate = ((desiredAccel>0)? 1: -1)*maxAccel*deltaTime;
        newRate = addedRate+lastSlewRate;
		}
	  lastSlewTime = lastSlewTime+deltaTime;
	  lastSlewRate = newRate;

		float returnVal = newRate;
		return returnVal;
}

void stop() {
	backLeft.tare_position();
  backRight.tare_position();
	frontLeft.move(0);
	middleLeft.move(0);
	backLeft.move(0);
	frontRight.move(0);
	middleRight.move(0);
	backRight.move(0);

	frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	middleLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	middleRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	backRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}
