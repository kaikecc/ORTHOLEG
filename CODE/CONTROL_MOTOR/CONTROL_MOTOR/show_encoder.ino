//=============================================================================
// --- Desenvolvimento das Funções ---
void show_encoder() {

  static unsigned char counter = 0; // variavel pra armazenar valor do encoder
  char tmpdata; // dado temporario



  tmpdata = read_encoder();

  if ( tmpdata )
  {
    set_bit(PORTB, target1); //digitalWrite(7, HIGH);
    counter += tmpdata;
    cpp += 1;
    //  pulses[resultNumber++] = counter;
    //   Serial.println(cpp += 1);
    reset_bit(PORTB, target1);

  }

if(cpp > 86000) { setDuty_Motor_L(0.0);}



}
//=============================================================================
