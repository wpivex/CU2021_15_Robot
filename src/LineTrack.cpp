#include "LineTrack.hpp"

void LineTrack::setPIDConsts(float kP, float kI, float kD){
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
}

void LineTrack::setTwoLineTracking(bool isTwoLines){
  isTwoLines = isTwoLines;
}

float LineTrack::calcTurnSpeed(){
  static unsigned long lastTime;
  unsigned long now = pros::millis();

  updateSensorVals();

  float error = solveForError();

  static float sumError = 0;
  sumError += error;
  static float lastError;
  int deltaT = now - lastTime;
  int deriError = error - lastError;

  // float turnPower = kP*error + kI*sumError + kD*deriError;
  float turnPower = kP*error;

  if(turnPower > MAX_TURN_EFFORT) turnPower = MAX_TURN_EFFORT;
  if(turnPower < -MAX_TURN_EFFORT) turnPower = -MAX_TURN_EFFORT;

  lastTime = now;
  lastError = error;

  debugError = error;

  return turnPower;
}

float LineTrack::solveForError(){
  float retVal = 0;
  if(isTwoLines){
    // retVal = -3.5*(sensorVals[0])-2.5*(sensorVals[1])-1.5*(sensorVals[2])-0.5*(sensorVals[3])+
    // 0.5*(sensorVals[4])+1.5*(sensorVals[5])+2.5*(sensorVals[6])+3.5*(sensorVals[7]);
  }else{
    retVal = -3*(sensorVals[0])-2*(sensorVals[1])-1*(sensorVals[2])+
    1*(sensorVals[4])+2*(sensorVals[5])+3*(sensorVals[6]);
  }
  return retVal;
}

void LineTrack::calibrateSensors(){
  // for(int i = 0; i < NUMBER_OF_SENSORS; i++){
  //   sensorArray[i].calibrate();
  // }
  ls1.calibrate();
  ls2.calibrate();
  ls3.calibrate();
  ls4.calibrate();
  ls5.calibrate();
  ls6.calibrate();
  ls7.calibrate();
  ls8.calibrate();
}

void LineTrack::updateSensorVals(){
  std::cout << "Updated sensorVals:";
  // for(int i = 0; i < NUMBER_OF_SENSORS; i++){
  //   sensorVals[i] = sensorArray[i].get_value_calibrated();
  //   std::cout<<" "<<sensorArray[i].get_value_calibrated();
  // }
  sensorVals[0] = ls1.get_value_calibrated();
  std::cout<<" "<<sensorVals[0];
  sensorVals[1] = ls2.get_value_calibrated();
  std::cout<<" "<<sensorVals[1];
  sensorVals[2] = ls3.get_value_calibrated();
  std::cout<<" "<<sensorVals[2];
  sensorVals[3] = ls4.get_value_calibrated();
  std::cout<<" "<<sensorVals[3];
  sensorVals[4] = ls5.get_value_calibrated();
  std::cout<<" "<<sensorVals[4];
  sensorVals[5] = ls6.get_value_calibrated();
  std::cout<<" "<<sensorVals[5];
  sensorVals[6] = ls7.get_value_calibrated();
  std::cout<<" "<<sensorVals[6];
  sensorVals[7] = ls8.get_value_calibrated();
  std::cout<<" "<<sensorVals[7];

  std::cout<<std::endl;
}
