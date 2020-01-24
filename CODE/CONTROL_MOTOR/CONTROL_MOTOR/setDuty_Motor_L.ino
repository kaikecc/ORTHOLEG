void setDuty_Motor_L(double value) {

  byte duty;

  value = value / 100.0;
 
  duty = (value * 256) - 1;

  OCR2A = duty;
}
