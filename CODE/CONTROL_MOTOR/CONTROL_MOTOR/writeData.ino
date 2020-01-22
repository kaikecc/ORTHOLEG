
void writeData(double newData) {

  static char Data[sizeof(double)];

  for(byte i = 0; i < sizeof(double); i++) Data[i] = newData;

  Wire.write(Data,sizeof(double));
  

}
