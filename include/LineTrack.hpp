#ifndef LineTrack_hpp
#define LineTrack_hpp

#include "main.h"

class LineTrack{
private:
  static LineTrack *instance;
  const float SENSOR_IMBALANCE_OFFSET = 0;
  const float MAX_TURN_EFFORT = 20;
  bool isTwoLines = false;

public:
  float kP;
  float kI;
  float kD;
  float debugError = 0;
  static LineTrack *getInstance() {
     if (!instance){
           instance = new LineTrack();
     }
     return instance;
  }
  int sensorVals[8];
  //Construct with PID terms

  void setPIDConsts(float kP, float kI, float kD);

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
