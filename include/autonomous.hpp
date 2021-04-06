#include "main.h"
#include "PID.hpp"
//#include "opcontrol.hpp"

//pros::ADIGyro gyro(1);

PID drivePID;
PID gyroPID;
PID gyroDrivePID;


void programmingSkills();

void shoot3descore2();
void shoot1descore1();

void stop();
void driveTarget(int target, float angle, int accuracy, int time, float max, bool slew);
void driveTargetRelative(int target, int accuracy, int time);
void driveTurn(int target, float angle, int accuracy, int time, float max, bool slew);

void driveTarget(int target, float angle, int accuracy, int time);

void gyroTurn(float target, int accuracy, int time);
void gyroTurnRelative(float target, int accuracy, int time);
void gyroTurn(float target, int accuracy, int time, bool precise);
void moveTime(int left, int right, int time);

void setIndexerSpeed(int power);
void setConveyorSpeed(int power);
void setIntakeSpeed(int power);
void setupIntake();
void auton();

float slewRateCalculate (float desiredRate);


void auxiliary();

float idealHeading = 0;
int aFlywheelTarget = 0;

float lastSlewTime;
float maxAccel = 0.17;
float lastSlewRate;

void move(void* param);
