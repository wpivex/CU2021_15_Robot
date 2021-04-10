#ifndef Odometry_hpp
#define Odometry_hpp

#include "main.h"

class Odometry{
    private:
        float x, y, theta;
        unsigned long time_prev = pros::millis(), time_now;
        const float l = 12; //distance from wheel-to-wheel in m
        const float rB = 4;
        float leftEncoderPrev = 0;
        float rightEncoderPrev = 0;
        float backEncoderPrev = 0;


    public:
        float getX();
        float getY();
        float getAngle();
        void tarePosition();
        void setAngle(float angle);
        void Init(void);
        void UpdatePose();
        void Restart();
        void PrintData(void);
        void Stop(void);
        void setOrigin(double setX, double setY);
};

#endif
