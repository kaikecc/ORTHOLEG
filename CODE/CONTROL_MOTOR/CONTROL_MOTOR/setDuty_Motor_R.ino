void setDuty_Motor_R(float value) {

  byte duty;

  value = value / 100;

  duty = (value * 256) - 1;

  OCR2B = duty;
}
