void receiveEvent(int howMany) {

  int numOfBytes = Wire.available();
  byte b = Wire.read();

  for (int i = 0; i < numOfBytes - 1; i++) {
    int data = Wire.read();
    if (data != '\n') {
      inString += (char)data;
      speeD = inString.toFloat();

    }
  }
  //
  meuPid.setSetPoint((double)speeD * (PI / 30.0)); // 200 rpm

  inString = "";

}
