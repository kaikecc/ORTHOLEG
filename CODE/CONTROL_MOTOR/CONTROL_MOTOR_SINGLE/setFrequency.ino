void setFrequency(char option){

  /*
   * TABLE
   * 
   * optio frequency
   * 
   * 1   62.5 kHz  (16e6/256)
   * 2    7.81 kHz (16e6/8)/256
   * 3    1.95 kHz (16e6/32)/256
   * 4  976.56 kHz (16e6/64)/256
   * 5  488.28 Hz  (16e6/128)/256 (freq. do analogWrite) 
   * 6  244.14 Hz  (16e6/256)/256
   * 7   61.03 Hz  (16e6/1024)/256
   * 
   */

   TCCR2B = option;
}
