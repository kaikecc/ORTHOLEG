void setDuty_Motor_L(float value){

  byte duty;

  value = value/100;

  duty = (value * 256) - 1;

  OCR2A = duty;
}