#ifndef LineTrack_hpp
#define LineTrack_hpp

#include "main.h"

class LineTrack{
private:
  const float SENSOR_IMBALANCE_OFFSET = 0;
  const float MAX_TURN_EFFORT = 1;
  float kP;
  float kI;
  float kD;
  bool isTwoLines = false;
  int sensorVals[8];

public:
  //Construct with PID terms
  LineTrack(float kP, float kI, float kD);

  //Call calirabte when the robot is not moving for 0.5 sec
  void calibrateSensors();

  //get newest sensor readings
  void updateSensorVals();

  //Error value using all senors using linear
  float solveForError();

  //Set to false if we are tracking one line, true is two
  void setTwoLineTracking(bool isTwoLines);

  //Returns turn power, has to be called at a set frequency for I and D to work
  float calcTurnSpeed();



};

#endif
