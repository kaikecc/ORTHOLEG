void receiveEvent(int howMany) {
  
  static String inString = "";
  static double speeD = 0.0;
  
  int numOfBytes = Wire.available();
  byte cmd = Wire.read();

  for (int i = 0; i < numOfBytes - 1; i++) {
    char data = Wire.read();
    inString += (char)data;
    speeD = inString.toDouble();
  }
 
  velPid.setSetPoint(speeD * (PI / 30.0));
  inString = "";

}
