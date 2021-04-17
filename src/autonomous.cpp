#include <thread>
#include "autonomous.hpp"
#include <ctime>
#include "Timer.hpp"
#include "LineTrack.hpp"

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
	odom.Init();
	//start the task for updating pose on the display;
	pros::Task odomTask(odomTaskFn);
	drivePID = pidInit (0.34, 0, 0.4, 0, 100.0,5,15);
	gyroDrivePID = pidInit(1.1,  0.0, 0.3, 0, 10,99999,999999);
	// gyroPID = pidInit(1.62,  0, 0.08, 0, 10,99999,999999); //1.6, 0, 0.62, 1.3,0,0.51
	 // gyroPID = pidInit(5,  0, 2.15, 0, 10,99999,999999); //1.6, 0, 0.62, 1.3,0,0.51

	 //ACTAULLY ODOM TURN PID!!
	 gyroPID = pidInit(1.1,  0.0, 0.3, 0, 10,99999,999999); //1.6, 0, 0.62, 1.3,0,0.51
//                        	P    I  D  idk idk idk idk
//	odomDistancePID = pidInit (0, 0, 0, 0, 100.0,0.1,0.5);

	odomDistancePID = pidInit (6, 0, 0.9, 0, 100.0,0.1,0.5);
	odomTurningPID = pidInit (1.5,  0, 0.08, 0, 10,99999,999999);
//	odomTurningPID = pidInit(1.2,  3.5, 0.1, 0, 10,99999,999999);

	distanceControl = slewRateInit(0.22);
	turnControl = slewRateInit(100); //Probably unsued
	//pros::lcd::clear();
//	indexer.move(127);

	stop();

	// gyro.reset();
	// pros::delay(2000); //TODO: Take this out soon!


	odom.tarePosition();

	//programmingSkills();
	// intialize();
	odomProgrammingSkills();
	 // gyroTurn(135, 0, 3000);
	 // gyroTurn(-135, 0, 3000);
	 // gyroTurn(0, 0, 3000);


//	MoveToPosition(20,-60, 5000);
	// MoveToPosition(30, 60, 3000);
	// MoveToPosition(0, 0, 3000);
	// gyroTurn(0,0,2000);


	// while(1) {
	// 	pros::delay(10);
	// }
	stop();
}

void odomTaskFn() {
	while (1) {
		odom.UpdatePose();
		odom.PrintData();
		pros::delay(3);
	}
}

// setIntakeSpeed(+);//In
// setConveyorSpeed(+); //Up
// setIndexerSpeed(+); //Out

//MAKE SURE THE ROBOT IS STATIONARY
void localizePosOnCorner(){
	stop();
	pros::delay(200);
	odom.setAngleDegrees(odom.getAngle()-90);

	const int NUMBER_OF_SAMPLES = 5;

	std::vector<int> leftVals(NUMBER_OF_SAMPLES);
	std::vector<int> rightVals(NUMBER_OF_SAMPLES);
	for(int i = 0; i < NUMBER_OF_SAMPLES; i++){
		//25.4 is mm -> inches
		leftVals[i] = ultrasonicL.get_value()/25.4;
		rightVals[i] = ultrasonicR.get_value()/25.4;
		pros::delay(51);
	}

	odom.setY(findMedian(leftVals, NUMBER_OF_SAMPLES));
	odom.setX(findMedian(rightVals, NUMBER_OF_SAMPLES));
}

void localizeAngleOnCorner(){
	stop();
	pros::delay(200);

	const int NUMBER_OF_SAMPLES = 5;

	std::vector<int> leftVals(NUMBER_OF_SAMPLES);
	std::vector<int> rightVals(NUMBER_OF_SAMPLES);
	for(int i = 0; i < NUMBER_OF_SAMPLES; i++){
		//25.4 is mm -> inches
		leftVals[i] = ultrasonicL.get_value()/25.4;
		rightVals[i] = ultrasonicR.get_value()/25.4;
		pros::delay(51);
	}

	float y = (findMedian(leftVals, NUMBER_OF_SAMPLES));
	float x = (findMedian(rightVals, NUMBER_OF_SAMPLES));

	float angleRad = atanf(y/x);
	float angleDeg = angleRad*180/M_PI;

	angleDeg = -180 + angleDeg;

	odom.setAngleDegrees(angleDeg);
}

void odomProgrammingSkills() {
	// gyroTurn(0, 0,2600);
	// pros::delay(100);
	// gyroTurn(0, 0,2600);
	// pros::delay(1000);
	// LineTrack *lineController = lineController->getInstance();
	// lineController->calibrateSensors();
	// lineController->setPIDConsts(0.01, 0, 0);
	// Timer lineTrackTimer = Timer();


	// while(true){
	// 	MoveToPosition(24, 0, 2900); //Cut off short  - intake first
	// 	gyroTurn(-90, 0,1600); //Face Goal
	// 	MoveToPosition(24, -24, 2900); //Cut off short  - intake first
	// 	gyroTurn(-180, 0,1600); //Face Goal
	// 	MoveToPosition(0, -24, 2900); //Cut off short  - intake first
	// 	gyroTurn(90, 0,1600); //Face Goal
	// 	MoveToPosition(0, 0, 2900); //Cut off short  - intake first
	// 	gyroTurn(0, 0,1600); //Face Goal
	// }

	// while(true){
	// 	gyroTurn(-90, 0, 3600);
	// 	MoveToPosition(0, -24, 2900); //Cut off short  - intake first
	// 	gyroTurn(0, 0, 3600);
	// 	MoveToPosition(24, -24, 2900); //Cut off short  - intake first
	// 	gyroTurn(90, 0,3600); //Face Goal
	// 	MoveToPosition(24, 0, 2900); //Cut off short  - intake first
	// 	gyroTurn(180, 0,3600); //Face Goal
	// 	MoveToPosition(0, 0, 2900); //Cut off short  - intake first
	// }
//	odom.setAngleDegrees(180);
	// pros::lcd::print(3, "Im here");
	intakeButDontShoot();
	MoveToPosition(12, 0, 600, true); //Cut off short  - intake first
	MoveToPosition(23, 25, 1000, true); //Intake 2nd ball
	startIndexingTask(600, true); //(delay, turn intake on at the end)
	MoveToPosition(18, 10, 800, true); //align with goal 1

	gyroTurn(135, 0,600); //Face Goal
	setIntakeSpeed(127);//In
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out

	localizePosOnCorner();
	odom.setAngleDegrees(odom.getAngle()+180);
	MoveToPosition(30, 30, 3000, true);
	MoveToPosition(5, 5, 1000, true);
	// waitForButton();
	// localizeAngleOnCorner();
	shoot3descore2(); // goal 1
	setIntakeSpeed(-127);
	pros::Task task0{[=] {
				pros::delay(400);
				intakeAllBackward();
	}};

	MoveToPosition(16, 16, 1000, true);
	gyroTurn(40,0,500);
	intakeButDontShoot();
	MoveToPosition(65, 42.5, 6000, false); // ball before goal 2
	gyroTurn(-90,0,900);
	MoveToPosition(65, 5, 1500, true);
	// waitForButton();
	shoot1descore1();		//goal 2
	pros::Task task1{[=] {
				pros::delay(600);
				intakeAllBackward();
	}};
	MoveToPosition(69, 13, 1200, true);

	gyroTurn(135,0,600);
	gyroTurn(0,0,1200);
	intakeButDontShoot();
	MoveToPosition(110, 13, 1000, true);
	MoveToPosition(120, 23, 3000, false);//the really broken one
	startIndexingTask(300,true);
	MoveToPosition(112, 15, 1200, true);
	gyroTurn(-45,0,1100);

//COORDINATE FRAME #2 STARTS HERE
	localizePosOnCorner();
	MoveToPosition(30, 30, 3000, true);
	MoveToPosition(5, 5, 1000, true);
	// waitForButton();
	// localizeAngleOnCorner();
	// waitForButton();
	shoot2descore2(); 			// goal 3
	setIntakeSpeed(-127);
	pros::Task task2{[=] {
				pros::delay(400);
				intakeAllBackward();
	}};

	MoveToPosition(16, 16, 1000, true);
	gyroTurn(40,0,1200);
	intakeButDontShoot();
	MoveToPosition(66, 39, 2000, true); // ball before goal 4
	gyroTurn(-85,0,900);
	startIndexingTask(500, true);
	MoveToPosition(65, 15, 1500, true);
	MoveToPosition(65, 5, 800, true);
	// waitForButton();
	shoot2descore1();		//goal 4
	pros::Task task3{[=] {
				pros::delay(150);
				intakeAllBackward();
	}};
	MoveToPosition(76, 38, 1200, true);
	gyroTurn(0,0,500);
	intakeButDontShoot();

	MoveToPosition(120, 41.5, 1500, true);
	gyroTurn(-120,0,700);
	MoveToPosition(100, -5, 1200, true);
	MoveToPosition(115, 5, 1200, true);
	gyroTurn(-35,0,1200);

//COORDINATE FRAME 3 STARTS HERE
// odom.setAngleDegrees(odom.getAngle()-2);
localizePosOnCorner();
// waitForButton();
// localizeAngleOnCorner();
// waitForButton();
MoveToPosition(40, 40, 3000, true);
MoveToPosition(5, 5, 2000, true);
shoot2descore2(); // goal 5
pros::Task task4{[=] {
			pros::delay(400);
			intakeAllBackward();
}};

MoveToPosition(16, 16, 1000, true);
gyroTurn(40,0,1200);
intakeButDontShoot();
MoveToPosition(61, 37, 8000, false); // ball before goal 6
gyroTurn(-85,0,900);

MoveToPosition(61, 7, 2000, true); // ball before goal 6
MoveToPosition(61, 3, 800, true); // ball before goal 6

shoot1descore1();		//goal 6
pros::Task task6{[=] {
			pros::delay(600);
			intakeAllBackward();
}};

MoveToPosition(69, 13, 800, true);

gyroTurn(135,0,600);
gyroTurn(0,0,1200);
intakeButDontShoot();
MoveToPosition(110, 13, 1000, true);
MoveToPosition(121, 20, 4000, false);
startIndexingTask(300,true);
MoveToPosition(112, 15, 1200, true);
gyroTurn(-45,0,1100);

//COORDINATE FRAME #4 STARTS HERE
localizePosOnCorner();
MoveToPosition(40, 40, 3000, true);
MoveToPosition(5, 5, 2000, true);
// waitForButton();
// localizeAngleOnCorner();
// waitForButton();

shoot2descore2(); //goal 7
setIntakeSpeed(-127);
pros::Task task7{[=] {
			pros::delay(400);
			intakeAllBackward();
}};

MoveToPosition(16, 16, 1000, true);
gyroTurn(0,0,1200);
intakeButDontShoot();
MoveToPosition(66, 42.5, 6000, false); // ball before goal 2
gyroTurn(-90,0,900);
MoveToPosition(65, 5, 2500, true);
// waitForButton();
shoot2descore1();		//goal 8
pros::Task task9{[=] {
			pros::delay(600);
			intakeAllBackward();
}};
MoveToPosition(65, 22, 800, true);

intakeAllStop();
}


void startIndexingTask(int time, bool intakesOn) {
	pros::delay(time);
	pros::Task ballIndexingTask{[=] {
				indexBalls();
				setIntakeSpeed((intakesOn)? 127: 0);
	}};
}

void waitForButton() {
	Timer buttonTimer = Timer();
	buttonTimer.setTimerMS(10000);
	while(!buttonTimer.isExpired()) {
		if(leftBumper.get_value() && rightBumper.get_value()) {
			// pros::lcd::print(4, "Both Pressed");
			break;
		}
		else if (leftBumper.get_value()) {
			// pros::lcd::print(4, "Left Pressed");
			setRightPower(60);
			setLeftPower(-30);
		}
		else if (rightBumper.get_value()) {
			// pros::lcd::print(4, "Right Pressed");
			setLeftPower(60);
			setRightPower(-30);
		}
		else {
			// pros::lcd::print(4, "Neither Pressed");
			setLeftPower(50);
			setRightPower(50);
		 }
		 pros::delay(350);
	}
}

void indexBalls() { //takes 1240ms
	setIntakeSpeed(127);//In
	setConveyorSpeed(-127); //Up
	setIndexerSpeed(-127); //Out

	pros::delay(400);

	setConveyorSpeed(100); //Up
	setIndexerSpeed(-100); //Out

	pros::delay(160);

	setConveyorSpeed(60); //Up
	setIndexerSpeed(-100); //Out

	pros::delay(520);

	setIntakeSpeed(0);//In

	setConveyorSpeed(0); //Up
	setIndexerSpeed(10); //Out

	pros::delay(120);

	setConveyorSpeed(-30); //Up

	setIndexerSpeed(-127);//In

	pros::delay(140);

	setConveyorSpeed(0); //Up

	setIndexerSpeed(0); //Out
}
void pauseForMSthenRunIntake(int ms){
	intakeAllBackward();
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
}

void intakeAllForward() {
	setIndexerSpeed(60);
	setIntakeSpeed(127);
	setConveyorSpeed(127);
}

void intakeAllBackward() {
	setIndexerSpeed(-127); //out
	setIntakeSpeed(-127); //out
	setConveyorSpeed(-127); //down
}

void intakeAllStop() {
	setIndexerSpeed(0);
	setIntakeSpeed(0);
	setConveyorSpeed(0);
}

void intakeButDontShoot(){
	setIntakeSpeed(127);//In
	setConveyorSpeed(60); //Up
	setIndexerSpeed(-70); //In
}

void shoot1descore1() {
	setConveyorSpeed(127); //Up
	setIndexerSpeed(127); //Out
	pros::delay(280);

	setConveyorSpeed(40); //Up
	setIndexerSpeed(0); //Out
//	pros::delay(300);
}

void shoot2descore1() {
	setConveyorSpeed(100); //Up
	setIndexerSpeed(127); //Out
	pros::delay(235);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(-40); //Out

	pros::delay(200);
	setIndexerSpeed(0); //stop
	setConveyorSpeed(-40);
	pros::delay(150);
	setIntakeSpeed(0);


  //second ball
	setConveyorSpeed(127); //Up
	setIndexerSpeed(127); //Out
	pros::delay(350);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	setIntakeSpeed(-127);
}

void shoot2descore2() {
	//first ball

	setConveyorSpeed(100); //Up
	setIndexerSpeed(127); //Out
	pros::delay(235);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(-40); //Out

	pros::delay(200);
	setIndexerSpeed(0); //stop
	setConveyorSpeed(-40);
	pros::delay(150);


  //second ball
	setConveyorSpeed(127); //Up
	setIndexerSpeed(127); //Out
	pros::delay(350);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
}

void shoot3descore2() {
	setIntakeSpeed(127);//Out

	//first ball
	setConveyorSpeed(127); //Up
	setIndexerSpeed(127); //Out
	pros::delay(200);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	pros::delay(200);
	setIndexerSpeed(-127); //In
	pros::delay(200);


  //second ball
	setConveyorSpeed(100); //Up
	setIndexerSpeed(127); //Out
	pros::delay(300);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	pros::delay(200);

		setIntakeSpeed(0);
	pros::delay(150);
	//third ball
	setConveyorSpeed(100); //Up
	setIndexerSpeed(127); //Out
	pros::delay(300);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
//	pros::delay(300);
}

void MoveToPosition(float targetX, float targetY, int maxTime, bool notSeperateTurn)
{
    bool atPoint = false;
	float targetAngle =0;
	float power =0;
	float turnPower =0;
    int repsAtTarget = 0;
    float lastDistance = 0;
    float lastHeading = 0;
    if (pros::millis()-distanceControl.lastSlewTime>10){
    	distanceControl.lastSlewTime = pros::millis()-5;
    }
    if (pros::millis()-turnControl.lastSlewTime>10){
	  turnControl.lastSlewTime = pros::millis()-5;
    }
		long startTime = pros::millis();
    while (!atPoint) {
        float distance = sqrt(pow(targetY-odom.getY(),2) + pow(targetX-odom.getX(),2));


        power = pidCalculate(odomDistancePID, 0, distance);
        power = slewRateCalculate(distanceControl, power);


				float projection = ((targetX-odom.getX())*cos(odom.getAngleRad())+(targetY-odom.getY())*sin(odom.getAngleRad()));
				targetAngle = (atan2f((targetY-odom.getY()),(targetX-odom.getX())));

				 if (projection < 0) {
						power *= -1;
						 targetAngle = modulus((targetAngle+M_PI)+M_PI, 2*M_PI)-M_PI;
				 }

				  pros::lcd::print(7, "TargetAngle: %f", targetAngle);

        float referenceAngle = 0;
        if (targetAngle-odom.getAngleRad()>M_PI) {
            referenceAngle = odom.getAngleRad()+(2*M_PI);
        }
        else if (targetAngle-odom.getAngleRad()<-M_PI) {
            referenceAngle = odom.getAngleRad()-(2*M_PI);
        }
        else {

            referenceAngle = odom.getAngleRad();
        }
				targetAngle *= (180/M_PI);
				referenceAngle *= (180/M_PI);
        turnPower = pidCalculate(odomTurningPID, targetAngle, referenceAngle);
        turnPower = slewRateCalculate(turnControl, turnPower);


				if (distance<7) {
					turnPower = 0;
				}
				if(notSeperateTurn){
					setDrivePower(power, turnPower);
				}else{
					if(pros::millis() > startTime + 2000){
							setDrivePower(power, turnPower);
					}else{
							setDrivePower(0, turnPower);
					}
				}

        if (sqrt(pow(targetY-odom.getY(),2) + pow(targetX-odom.getX(),2)) < 1 || pros::millis() - startTime > maxTime) {
            repsAtTarget++;
        }
        else {
            repsAtTarget = 0;
        }
        if (repsAtTarget > 2) {
            atPoint = true;
            repsAtTarget = -1;
        }
        pros::delay(10);
    }
    slewRateReset(distanceControl);
		slewRateReset(turnControl);
		resetPID(odomTurningPID);
		resetPID(odomDistancePID);

    stop();
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
	// lastSlewTime = pros::millis()-10;
	// lastSlewRate = 0;
	//go into the loop that will repeat to update motor values and break when at target
	while (!atTarget && (pros::millis()-startTime) < time) {
		auxiliary();
    driveEnc = (backLeft.get_position() + backRight.get_position())/2;
		//calculate the value the motors should be set at based on its position relative to the target
		float val = pidCalculate(drivePID, target, driveEnc)*max;
		//val = slewRateCalculate(val);
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
	resetPID(gyroPID);
	idealHeading = target;
	target = target*side;
	int startTime = pros::millis();
	// gyroPID.lastTime = startTime;
	bool gyroAtTarget = false;
	int repsAtTarget = 0;
	//go into the loop that will repeat to update motor values and break when at target
	while (!gyroAtTarget  && (pros::millis()-startTime) < time) {
	//	pros::lcd::print(7, "Angle: %f", odom.getAngle());
		// auxiliary();
		// calculate the desired motor value based on the sensor value relative to the target

		float referenceAngle = 0;
		if (target-odom.getAngle()>180) {
				referenceAngle = odom.getAngle()+360;
		}
		else if (target-odom.getAngle()<-180) {
				referenceAngle = odom.getAngle()-360;
		}
		else {

				referenceAngle = odom.getAngle();
		}
		float drive = pidCalculate(gyroPID, target,referenceAngle);
	//	drive = slewRateCalculate(drive);
	//	drive = ((fabs(gyro.get_value()/10.0-target)>180)? -1 : 1)*drive;
	frontLeft.move(-drive);
	middleLeft.move(-drive);
	backLeft.move(-drive);
	frontRight.move(drive);
	middleRight.move(drive);
	backRight.move(drive);
		//if the sensor value is within the desired range of the target
		if (fabs(odom.getAngle()-target) < accuracy) {
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
	resetPID(gyroPID);
	stop();
}


void auxiliary() {

}

float modulus(float a, float b) {
  while(a<0) {
    a+=b;
  }
  while(a>b) {
    a-=b;
  }
  return a;
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




// C++ program for the above approach

#include <bits/stdc++.h>

// Function for calculating
// the median
double findMedian(std::vector<int> a,
                  int n)
{

    // If size of the arr[] is even
    if (n % 2 == 0) {

        // Applying nth_element
        // on n/2th index
        nth_element(a.begin(),
                    a.begin() + n / 2,
                    a.end());

        // Applying nth_element
        // on (n-1)/2 th index
        nth_element(a.begin(),
                    a.begin() + (n - 1) / 2,
                    a.end());

        // Find the average of value at
        // index N/2 and (N-1)/2
        return (double)(a[(n - 1) / 2]
                        + a[n / 2])
               / 2.0;
    }

    // If size of the arr[] is odd
    else {

        // Applying nth_element
        // on n/2
        nth_element(a.begin(),
                    a.begin() + n / 2,
                    a.end());

        // Value at index (N/2)th
        // is the median
        return (double)a[n / 2];
    }
}
