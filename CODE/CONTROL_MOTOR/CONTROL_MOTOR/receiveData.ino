void receiveData(int byteCount) {

  while (Wire.available()) {
     setPoint = Wire.read();
  }
}
