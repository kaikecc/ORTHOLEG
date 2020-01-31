void receiveEvent(int howMany) {

  static String inString = "";
  int numOfBytes = Wire.available();
  byte cmd = Wire.read();

  for (int i = 0; i < numOfBytes - 1; i++) {
    char data = Wire.read();
    inString += (char)data;
    ref = inString.toDouble();
  }

  velPid.setSetPoint(ref * (PI / 30.0));
  inString = "";

}
