void requestEvent(){
   double Data = rpm;
   Wire.write((byte*) &Data, sizeof(double));
}
