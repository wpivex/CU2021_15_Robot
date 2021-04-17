#ifndef Odometry_hpp
#define Odometry_hpp

#include "main.h"

class Odometry{
    private:
        float x, y, theta;
        unsigned long time_prev = pros::millis(), time_now;
        const float l = 7.32; //distance from wheel-to-wheel in m
        // const float rB = -5.5;
        float leftEncoderPrev = 0;
        float rightEncoderPrev = 0;
        float backEncoderPrev = 0;


    public:
        float getX();
        float getY();
        float getAngle();
        float getAngleRad();

        void tarePosition();
        void setAngleDegrees(float angle);
        void setX(float newX);
        void setY(float newY);
        void Init(void);
        void UpdatePose();
        void Restart();
        void PrintData(void);
        void Stop(void);
        void setCoordinates(double setX, double setY);
};

#endif
