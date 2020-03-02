#include "Arduino.h"
class PID {
  public:

#define DIRECT 1
#define REVERSE 0


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

  

    PID(double _kP, double _kI, double _kD, bool direcao) {

      setTunings(_kP, _kI, _kD, direcao);
     
    }
    void setTunings(double Kp, double Ki, double Kd, bool dir)
    {

      if (Kp < 0 || Ki < 0 || Kd < 0) return;

      if (dir == REVERSE) {
        kP = (0 - Kp);
        kI = (0 - Ki);
        kD = (0 - Kd);
      }
      else {
        kP = Kp;
        kI = Ki;
        kD = Kd;
      }
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
