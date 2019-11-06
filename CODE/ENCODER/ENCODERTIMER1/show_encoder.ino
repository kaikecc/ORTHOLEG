//=============================================================================
// --- Desenvolvimento das Funções ---
void show_encoder() {

  // toggle_bit(PORTB, led); // digitalWrite(led, !digitalRead(7));
  // set_bit(PORTB, led); //digitalWrite(led, HIGH);

  static unsigned char counter = 0; // variavel pra armazenar valor do encoder
  char tmpdata; // dado temporario


  tmpdata = read_encoder();
  

  
  if ( tmpdata )
  {
  
    counter += tmpdata;
   // results [resultNumber++] = counter;

  }


  // reset_bit(PORTB, led); //digitalWrite(led, LOW);
}
//=============================================================================
