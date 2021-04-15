#include  "odometry.hpp"



void Odometry::Init(void)
{
    x = 0;
    y = 0;
    theta = 0;
    time_prev = pros::millis();
}

void Odometry::Restart() {
    time_prev = pros::millis();
}

void Odometry::setCoordinates(double newX, double newY) {
    x = newX;
    y = newY;
}

void Odometry::tarePosition() {
  x = 0;
  y = 0;
}

void Odometry::setX(float newX) {
  x = newX;
}

void Odometry::setY(float newY) {
  y = newY;
}
void Odometry::setAngleDegrees(float angle) {
  theta = angle*M_PI/180.0;
}

void Odometry::Stop(void)
{
    x = 0;
    y = 0;
    theta = 0;
    time_prev = pros::millis();
}

void Odometry::PrintData(void)
{
    pros::lcd::print(0, "X: %.2f \t Y: %.2f \t T: %.2f", x, y, getAngle());
    controller.print(0,0, "(%3.0f,%3.0f) T:%3.1f", x, y, getAngle());


    // controller.set
    pros::lcd::print(1, "Right: %d \t Left: %d", rightEncoder.get_value(),leftEncoder.get_value());
    // LineTrack *lineController = lineController->getInstance();
    // pros::lcd::print(2, "1:%.4d\t 2:%.4d\t 3:%.4d\t 4:%.4d", lineController->sensorVals[0],lineController->sensorVals[1],lineController->sensorVals[2],lineController->sensorVals[3]);
    // pros::lcd::print(3, "5:%.4d\t 6:%.4d\t 7:%.4d\t 8:%.4d", lineController->sensorVals[4],lineController->sensorVals[5],lineController->sensorVals[6],lineController->sensorVals[7]);
    // pros::lcd::print(4, "TurnPower: %.3f", lineController->calcTurnSpeed());
    // pros::lcd::print(5, "Raw Error: %.3f", lineController->debugError);
    pros::lcd::print(6, "Millis(): %d", pros::millis());
    pros::lcd::print(7, "SL: %d  SR: %d", ultrasonicL.get_value(),ultrasonicR.get_value());

}

float Odometry::getX() {
  return x;
}

float Odometry::getY() {
  return y;
}
float Odometry::getAngle() {
  return theta*180/M_PI;
}

float Odometry::getAngleRad() {
  return theta;
}
void Odometry::UpdatePose()
{
    //Serial.println(velocity_left);
    time_now = pros::millis();
    if(time_now - time_prev >= 3) //update every 50ms for practical reasons
    {
        float deltaTime = (time_now - time_prev) / 1000.0;

        float velocity_left = ((leftEncoder.get_value() - leftEncoderPrev)/deltaTime) * (3.25 * M_PI) / 1024.0;
        float velocity_right = (rightEncoder.get_value() - rightEncoderPrev)/deltaTime * (3.25 * M_PI) / 1024.0;
        // float velocity_back = (backEncoder.get_value() - backEncoderPrev)/deltaTime * (3.25 * M_PI) / 1024.0;
        float velocity_back = 0;
        leftEncoderPrev = leftEncoder.get_value();
        rightEncoderPrev = rightEncoder.get_value();
        // backEncoderPrev = backEncoder.get_value();

        if (velocity_left == velocity_right) {
            x += velocity_right * cos(theta) * deltaTime;// + velocity_back * sin(theta) * deltaTime;
            y += velocity_right * sin(theta) * deltaTime;// + velocity_back * cos(theta) * deltaTime;

        }
        else {
            float vL = velocity_left;
            float vR = velocity_right;
            float r = (l*(vR+vL))/(2*(vR-vL));
            float omega = (vR-vL)/l;
            float v = omega*r;

            // velocity_back -= omega*rB;
            //1055 is ticks on the back wheel when turning 90 degrees
            float ticksPerDegree = 1055 / M_PI / 2;
            velocity_back -= (omega*deltaTime) * ticksPerDegree;

            x = x - r*sin(theta) + r*sin(theta + omega*deltaTime);// + velocity_back * sin(theta + omega*deltaTime) * deltaTime;
            y = y + r*cos(theta) - r*cos(theta + omega*deltaTime);// + velocity_back * cos(theta + omega*deltaTime) * deltaTime;
            theta += omega*deltaTime;
        }
        if (theta > M_PI) {
            theta -= 2*M_PI;
        }
        else if (theta<-M_PI) {
            theta += 2*M_PI;
        }
        time_prev = time_now;
    }
}
