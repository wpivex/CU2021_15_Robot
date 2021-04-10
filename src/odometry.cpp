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

void Odometry::setOrigin(double newX, double newY) {
    x = newX;
    y = newY;
}

void Odometry::tarePosition() {
  x = 0;
  y = 0;
}

void Odometry::setAngle(float angle) {
  theta = angle;
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
    pros::lcd::print(0, "X: %f", x);
    pros::lcd::print(1, "Y: %f", y);
    pros::lcd::print(2, "Theta: %f", getAngle());
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
void Odometry::UpdatePose()
{
    //Serial.println(velocity_left);
    time_now = pros::millis();
    if(time_now - time_prev >= 15) //update every 50ms for practical reasons
    {
        float deltaTime = (time_now - time_prev) / 1000.0;

        float velocity_left = ((leftEncoder.get_value() - leftEncoderPrev)/deltaTime) * (3.25 * M_PI) / 1024.0;
        float velocity_right = (rightEncoder.get_value() - rightEncoderPrev)/deltaTime * (3.25 * M_PI) / 1024.0;
        float velocity_back = (backEncoder.get_value() - backEncoderPrev)/deltaTime * (3.25 * M_PI) / 1024.0;

        if (velocity_left == velocity_right) {
            x += velocity_right * cos(theta) * deltaTime + velocity_back * sin(theta) * deltaTime;
            y += velocity_right * sin(theta) * deltaTime + velocity_back * cos(theta) * deltaTime;

        }
        else {
            float vL = velocity_left;
            float vR = velocity_right;
            float r = (l*(vR+vL))/(2*(vR-vL));
            float omega = (vR-vL)/l;
            float v = omega*r;

            velocity_back -= omega*rB;

            x = x - r*sin(theta) + r*sin(theta + omega*deltaTime) + velocity_back * sin(theta + omega*deltaTime) * deltaTime;
            y = y + r*cos(theta) - r*cos(theta + omega*deltaTime) + velocity_back * cos(theta + omega*deltaTime) * deltaTime;
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
