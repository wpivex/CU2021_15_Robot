#ifndef SlewRate_CPP
#define SlewRate_CPP

#include "main.h"
#include "SlewRate.hpp"

SlewRate slewRateInit(float maxAccel) {
	SlewRate slewRate;
	slewRate.maxAccel = maxAccel;
	slewRate.lastSlewTime = pros::millis();
	slewRate.lastSlewRate = 0;

	return slewRate;
}

void slewRateReset(SlewRate rate) {
    rate.lastSlewRate = 0;
    rate.lastSlewTime = pros::millis();
}

float
slewRateCalculate (SlewRate rate, float desiredRate) {
		//pros::lcd::print(7, "called: %f", desiredRate);
		float deltaTime = pros::millis()-rate.lastSlewTime;
		float desiredAccel = (desiredRate -rate.lastSlewRate)/deltaTime;
		float addedRate;
		float newRate;

		if (fabs(desiredAccel) < rate.maxAccel || (desiredAccel<0 && desiredRate>0) || (desiredAccel>0 && desiredRate<0)) {
		    addedRate = desiredAccel*deltaTime;
		    newRate = addedRate+rate.lastSlewRate;
		}
		else {
		    addedRate = ((desiredAccel>0)? 1: -1)*rate.maxAccel*deltaTime;
        newRate = addedRate+rate.lastSlewRate;
		}
	  rate.lastSlewTime = rate.lastSlewTime+deltaTime;
	  rate.lastSlewRate = newRate;

		float returnVal = newRate;
		return returnVal;
}

#endif
