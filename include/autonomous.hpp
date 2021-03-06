#include <thread>
#include "main.h"
#include "PID.hpp"
#include "SlewRate.hpp"
#include "odometry.hpp"
//#include "opcontrol.hpp"

//pros::ADIGyro gyro(1);

PID drivePID;
PID gyroPID;
PID gyroDrivePID;
PID odomDistancePID;
PID odomTurningPID;

SlewRate distanceControl;
SlewRate turnControl;


Odometry odom;

void programmingSkills();
void odomProgrammingSkills();

void shoot3descore2();
void shoot1descore1();
void shoot2descore1();
void shoot2descore2();

void odomTaskFn();

void stop();
void localizePosOnCorner();
void localizeAngleOnCorner();
void driveTarget(int target, float angle, int accuracy, int time, float max, bool slew);
void driveTargetRelative(int target, int accuracy, int time);
void driveTurn(int target, float angle, int accuracy, int time, float max, bool slew);

void driveTarget(int target, float angle, int accuracy, int time);

void gyroTurn(float target, int accuracy, int time);
void gyroTurnRelative(float target, int accuracy, int time);
void gyroTurn(float target, int accuracy, int time, bool precise);
void moveTime(int left, int right, int time);

void startIndexingTask(int time, bool intakesOn);
void setIndexerSpeed(int power);
void setConveyorSpeed(int power);
void setIntakeSpeed(int power);
void intakeButDontShoot();
void intakeAllForward();
void intakeAllBackward();
void intakeAllStop();
void indexBalls();
void waitForButton();

float modulus(float a, float b);
void auton();
void MoveToPosition(float x, float y, int maxTime, bool notSeperateTurn, bool stopOnTouch);
double findMedian(std::vector<int> a,int n);

void auxiliary();

float idealHeading = 0;
int aFlywheelTarget = 0;

void move(void* param);
