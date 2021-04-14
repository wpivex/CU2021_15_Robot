#include <thread>
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
	odom.Init();

	//start the task for updating pose;
	pros::Task odomTask(odomTaskFn);
	drivePID = pidInit (0.34, 0, 0.4, 0, 100.0,5,15);
	gyroDrivePID = pidInit(0.7, 0, 0.4, 0, 40,999999,9999999);
	// gyroPID = pidInit(1.62,  0, 0.08, 0, 10,99999,999999); //1.6, 0, 0.62, 1.3,0,0.51
	 gyroPID = pidInit(2.12,  0, 0.08, 0, 10,99999,999999); //1.6, 0, 0.62, 1.3,0,0.51
//                        	P    I  D  idk idk idk idk
//	odomDistancePID = pidInit (0, 0, 0, 0, 100.0,0.1,0.5);

	odomDistancePID = pidInit (6, 0, 0.9, 0, 100.0,0.1,0.5);
//	odomTurningPID = pidInit (0,  0, 0, 0, 10,99999,999999);
	odomTurningPID = pidInit(2,  0, 0, 0, 10,99999,999999);

	distanceControl = slewRateInit(0.22);
	turnControl = slewRateInit(0.5);
	//pros::lcd::clear();
//	indexer.move(127);
	stop();

	gyro.reset();
	pros::delay(2000);


	odom.tarePosition();

	//programmingSkills();
	odomProgrammingSkills();
	//gyroTurn(-90, 0, 100000);
	// MoveToPosition(60, 30, 3000);
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

void odomProgrammingSkills() {
	intakeButDontShoot();
	MoveToPosition(30, 0, 600); //Cut off short  - intake first ball
	MoveToPosition(28, 28, 900); //Intake 2nd ball
	MoveToPosition(17, 12, 800); //align with goal 1

  indexBalls();

	gyroTurn(135, 0,600); //Face Goal
	setIntakeSpeed(127);//In
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	MoveToPosition(1, 27, 800);

	shoot3descore2(); //goal 1
	setIntakeSpeed(-127); //o ut
	MoveToPosition(17, 12, 500);
	intakeAllForward(); //meaning spit out the top

	gyroTurn(-65, 0, 500); //cut short
	pros::Task task{[=] {
				pros::delay(300);
				intakeButDontShoot();
	}};
	MoveToPosition(40, -31, 1300); //undershhot so we get a 90 degree approch
	gyroTurn(-179, 0, 500);
	MoveToPosition(-3, -34, 1100);
	shoot1descore1(); //at goal 2
	pros::Task task2{[=] {
				pros::delay(300);
				intakeAllBackward();
	}};
	MoveToPosition(12, -36, 450);
	gyroTurn(-90, 0, 700);
	intakeButDontShoot();
	MoveToPosition(12, -72, 1000);
	MoveToPosition(20, -98, 1000);//ball at the wall
	MoveToPosition(10, -78, 1000);//back up in front of goal 3
	indexBalls();
	gyroTurn(-145, 0, 700);
	setIntakeSpeed(127);
	MoveToPosition(-5.5, -98, 900);
	shoot2descore2(); //goal 3
	setIntakeSpeed(-127);
	pros::Task task4{[=] {
				pros::delay(400);
				intakeAllBackward();
	}};
	MoveToPosition(20, -75, 1200);
	gyroTurn(10, 0, 1300); //cut off
	intakeButDontShoot();
	MoveToPosition(57, -56, 1200);
	indexBalls();
	gyroTurn(-170, 0, 500);
	intakeButDontShoot();
	MoveToPosition(58, -95, 1200);

	shoot2descore1(); //goal 4
	setIntakeSpeed(-127);
	pros::Task task3{[=] {
				pros::delay(400);
				intakeAllBackward();
	}};
	MoveToPosition(70, -72, 1000);
	intakeButDontShoot();

	gyroTurn(90,0,500);
	MoveToPosition(102, -70.5, 1000);
	gyroTurn(-90,0,500);
	MoveToPosition(90, -98, 1000);
	MoveToPosition(105, -88, 1000);
	gyroTurn(-45,0,500); //line up with 5
	MoveToPosition(115, -97, 1000);

	shoot2descore2(); //goal 5
	setIntakeSpeed(-127);
	pros::Task task5{[=] {
				pros::delay(400);
				intakeAllBackward();
	}};
	MoveToPosition(96, -74, 1000);

	gyroTurn(120,0,1200);
	intakeButDontShoot();
	MoveToPosition(76, -38, 1250);
	gyroTurn(90,0,400);
	MoveToPosition(114, -35, 2000);

	shoot1descore1();
	//goal 6
	pros::Task task6{[=] {
				pros::delay(300);
				intakeAllBackward();
	}};
	MoveToPosition(98, -35, 450);
	gyroTurn(-270, 0, 700);
	intakeButDontShoot();
	MoveToPosition(98, 0, 1000);

	MoveToPosition(87, 28, 1000);

	//line up with goal 7
	MoveToPosition(100, 10, 1000);

	gyroTurn(45,0,600);


	MoveToPosition(113, 24, 1000);

	shoot2descore2();
	setIntakeSpeed(-127); //goal 7
	MoveToPosition(101, 13, 1000);















	intakeAllStop();

}

void indexBalls() {
	setIntakeSpeed(0);//In
	setConveyorSpeed(-30); //Up
	setIndexerSpeed(-80); //Out
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
	intakeButDontShoot();
	driveTarget(1050,0,0,2500);

	driveTarget(-310,0,0,1200);
	setIntakeSpeed(0);//In
	setConveyorSpeed(-30); //Up
	setIndexerSpeed(-80); //Out
	gyroTurn(-70,0,1200);
	setIntakeSpeed(127);//In
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	driveTarget(430,-70,0,1200);

	shoot3descore2();

	intakeAllForward();
	setIntakeSpeed(-80);

	driveTarget(-350,-69,0,1200);
	gyroTurnRelative(-167, 0, 1200);
	intakeButDontShoot();
	driveTargetRelative(1140,0,2000);
	gyroTurnRelative(111,0,1200);
	driveTargetRelative(700,0,1300);

	//Second goal

	shoot1descore1();

	driveTargetRelative(-210,0,800);

	gyroTurnRelative(66,0,500);
	intakeAllBackward();
	gyroTurnRelative(-150.5,0,2000);

	intakeButDontShoot();
	driveTargetRelative(690,0,2000);
	gyroTurnRelative(-30,0,1200);

	driveTargetRelative(600,0,1200);
	driveTargetRelative(-350,0,2000);

	gyroTurnRelative(71,0,1200);


	//To 3rd Goal
  driveTargetRelative(550,0,1300);
	shoot2descore1();

	//setIntakeSpeed(-70);
	// setConveyorSpeed(0);
	// setIndexerSpeed(0);

	driveTargetRelative(-950,0,2000);

	intakeAllBackward();
	gyroTurnRelative(-142,0,1400);

	intakeButDontShoot();
	driveTargetRelative(700,0,1800);


	//goal 4
	gyroTurnRelative(96, 0, 1200);

	driveTargetRelative(720,0,2000);


	shoot2descore1();

	driveTargetRelative(-300,0,1200);

	gyroTurnRelative(66,0,500);
	intakeAllBackward();
	gyroTurnRelative(-150.5,0,2000);

	intakeButDontShoot();

	driveTargetRelative(600,0,1200);

	gyroTurnRelative(100,0,1200);

	driveTargetRelative(600,0,1200);
	driveTargetRelative(-400,0,1200);






	//goal 5
	driveTargetRelative(960,0,1600);

	shoot2descore1();

	driveTargetRelative(-300,0,1000);



	stop();
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
	pros::delay(300);

	setConveyorSpeed(40); //Up
	setIndexerSpeed(0); //Out
//	pros::delay(300);
}

void shoot2descore1() {
	//first ball
	setConveyorSpeed(100); //Up
	setIndexerSpeed(127); //Out
	pros::delay(180);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	pros::delay(500);


  //second ball
	setConveyorSpeed(100); //Up
	setIndexerSpeed(127); //Out
	pros::delay(200);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
}

void shoot2descore2() {
	//first ball
	setConveyorSpeed(100); //Up
	setIndexerSpeed(127); //Out
	pros::delay(215);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	pros::delay(500);


  //second ball
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
	pros::delay(400);


  //second ball
	setConveyorSpeed(100); //Up
	setIndexerSpeed(127); //Out
	pros::delay(200);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	pros::delay(350);
	setIntakeSpeed(0);

	//third ball
	setConveyorSpeed(100); //Up
	setIndexerSpeed(127); //Out
	pros::delay(400);
	setConveyorSpeed(0); //Up
	setIndexerSpeed(0); //Out
	pros::delay(300);
}

void MoveToPosition(float targetX, float targetY, int maxTime)
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

				float leftVal = -(power+turnPower);
				float rightVal = -(power-turnPower);
				frontLeft.move(leftVal);
			  middleLeft.move(leftVal);
				backLeft.move(leftVal);
				frontRight.move(rightVal);
				middleRight.move(rightVal);
				backRight.move(rightVal);

        if (sqrt(pow(targetY-odom.getY(),2) + pow(targetX-odom.getX(),2)) < 0.6 || pros::millis() - startTime > maxTime) {
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
	idealHeading = target;
	target = target*side;
	int startTime = pros::millis();
	bool gyroAtTarget = false;
	int repsAtTarget = 0;
	//go into the loop that will repeat to update motor values and break when at target
	while (!gyroAtTarget  && (pros::millis()-startTime) < time) {
	//	pros::lcd::print(7, "Angle: %f", odom.getAngle());
		// auxiliary();
		// calculate the desired motor value based on the sensor value relative to the target
		float drive = pidCalculate(gyroPID, target,odom.getAngle())*((precise)? 0.75: 1);
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
