void requestEvent(){
   double data = rpm;
   Wire.write((byte*) &data, sizeof(double));
}
