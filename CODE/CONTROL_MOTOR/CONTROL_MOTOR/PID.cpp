// (Really Simple) PID Class by Ivan Seidel
// GitHub.com/ivanseidel
// Use as you want. Leave credits
#include "Arduino.h"
class PID {
  public:

    double error;
    double sample;
    double lastSample;
    double kP, kI, kD;
    double P, I, D;
    double pid;
    double deltaTime;
    double outMin, outMax;
    double setPoint = 0.0;
    double ITerm;


    PID(double _kP, double _kI, double _kD, double _deltaTime) {
      
      if (_kD<0 || _kI<0 || _kD<0 || _deltaTime) return;
      
      deltaTime = _deltaTime;
      kP = _kP;
      kI = _kI * deltaTime;
      kD = _kD / deltaTime;
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

    double process() {


      // Implementação P I D
      
      error = setPoint - sample;

      ITerm += (kI * error);

      if (ITerm > outMax) ITerm = outMax;
      else if (ITerm < outMin) ITerm = outMin;
      double dInput = (sample - lastSample);

      //P
      P = error * kP;

      //I
      I = ITerm;

      //D
      D = kD * dInput;

      // Soma tudo
      pid = P + I - D;
      
      if (pid > outMax) pid = outMax;
      else if (pid < outMin) pid = outMin;

      lastSample = sample;
    
      return pid;
    }
};
