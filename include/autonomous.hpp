#include "main.h"
#include "PID.hpp"
//#include "opcontrol.hpp"

//pros::ADIGyro gyro(1);

PID drivePID;
PID gyroPID;
PID gyroDrivePID;


void stop();
void driveTarget(int target, float angle, int accuracy, int time, float max, bool slew);
void driveTurn(int target, float angle, int accuracy, int time, float max, bool slew);

void driveTarget(int target, float angle, int accuracy, int time);

void gyroTurn(float target, int accuracy, int time);
void gyroTurn(float target, int accuracy, int time, bool precise);
void moveTime(int left, int right, int time);


void auton();

float slewRateCalculate (float desiredRate);


void auxiliary();

int aFlywheelTarget = 0;

float lastSlewTime;
float maxAccel = 0.17;
float lastSlewRate;

void move(void* param);
