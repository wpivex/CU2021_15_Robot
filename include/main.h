/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2018, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

/**
 * If defined, some commonly used enums will have preprocessor macros which give
 * a shorter, more convenient naming pattern. If this isn't desired, simply
 * comment the following line out.
 *
 * For instance, E_CONTROLLER_MASTER has a shorter name: CONTROLLER_MASTER.
 * E_CONTROLLER_MASTER is pedantically correct within the PROS styleguide, but
 * not convienent for most student programmers.
 */
#define PROS_USE_SIMPLE_NAMES

/**
 * If defined, C++ literals will be available for use. All literals are in the
 * pros::literals namespace.
 *
 * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
 */
#define PROS_USE_LITERALS

#include "api.h"

/**
 * You should add more #includes here
 */
//#include "okapi/api.hpp"
//#include "pros/api_legacy.h"

/**
 * If you find doing pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented out line.
 *
 * IMPORTANT: Only the okapi or pros namespace may be used, not both
 * concurrently! The okapi namespace will export all symbols inside the pros
 * namespace.
 */
// using namespace pros;
// using namespace pros::literals;
// using namespace okapi;

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C" {
#endif

extern pros::Controller controller;
extern pros::Motor frontRight;
extern pros::Motor middleRight;
extern pros::Motor backRight;
extern pros::Motor frontLeft;
extern pros::Motor middleLeft;
extern pros::Motor backLeft;

extern pros::Motor leftIntake;
extern pros::Motor rightIntake;

extern pros::Motor leftConveyor;
extern pros::Motor rightConveyor;


extern pros::Motor leftIndexer;
extern pros::Motor rightIndexer;

extern pros::ADIGyro gyro;

extern pros::ADIEncoder leftEncoder;
extern pros::ADIEncoder rightEncoder;
extern pros::ADIEncoder backEncoder;


extern pros::ADIDigitalOut deploy;

extern int NUMBER_OF_SENSORS; //Number of light sensors
extern int ADI_EXPANDER_SMART_PORT; //The smart port that the 3wire expander plugs into
// extern pros::ADIAnalogIn sensorArray[8]; //Array of AnalogIn objects (sensors)
extern pros::ADIAnalogIn ls1;
extern pros::ADIAnalogIn ls2;
extern pros::ADIAnalogIn ls3;
extern pros::ADIAnalogIn ls4;
extern pros::ADIAnalogIn ls5;
extern pros::ADIAnalogIn ls6;
extern pros::ADIAnalogIn ls7;
extern pros::ADIAnalogIn ls8;

extern pros::ADIUltrasonic ultrasonicL;
extern pros::ADIUltrasonic ultrasonicR;
extern pros::ADIButton leftBumper;
extern pros::ADIButton rightBumper;


double flywheelCalculate(double target);
void setDrivePower(int forwardPower, int turnPower);
void setLeftPower(int forwardPower);
void setRightPower(int forwardPower);
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#include "LineTrack.hpp"
#endif

#endif  // _PROS_MAIN_H_
