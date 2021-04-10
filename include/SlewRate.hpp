#ifndef SlewRate_HPP
#define SlewRate_HPP
typedef struct{
	float lastSlewTime;
	float maxAccel;
	float lastSlewRate;
} SlewRate;

extern SlewRate slewRateInit(float maxAccel);
extern float slewRateCalculate (SlewRate rate, float desiredRate);
extern void slewRateReset(SlewRate rate);

#endif
