#include "Arduino.h"
class PID {
  public:

    double error,
           sample,
           lastSample,
           kP, kI, kD,
           P , I , D,
           pid,
           deltaTime,
           outMin, outMax,
           setPoint,
           ITerm, dInput;


    PID(double _kP, double _kI, double _kD) {

      if (_kD < 0 || _kI < 0 || _kD < 0) return;

      kP = _kP;
      kI = _kI;
      kD = _kD;

    }

    void addNewSample(double _sample) {

      sample = _sample;

    }

    void setSetPoint(double _setPoint) {
      setPoint = _setPoint;
    }

    void SetOutputLimit(double Min, double Max)
    {

      if (Min > Max) return;
      outMin = Min;
      outMax = Max;

      if (pid > outMax) pid = outMax;
      else if (pid < outMin) pid = outMin;

      if (ITerm > outMax) ITerm = outMax;
      else if (ITerm < outMin) ITerm = outMin;
    }

    void setSampleTime(double _deltaTime)
    {
      deltaTime = _deltaTime;
    }

    double process() {

      // Implementação P I D

      error = setPoint - sample;

      ITerm += (kI * error) * deltaTime;

      if (ITerm > outMax) ITerm = outMax;
      else if (ITerm < outMin) ITerm = outMin;

      dInput = (sample - lastSample);

      //P
      P = error * kP;

      //I
      I = ITerm;

      //D
      D = (kD * dInput) / deltaTime;

      // Soma tudo
      pid = P + I + D;

      if (pid > outMax) pid = outMax;
      else if (pid < outMin) pid = outMin;

      lastSample = sample;

      return pid;
    }
};
