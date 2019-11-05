//=============================================================================
// --- Desenvolvimento das Funções ---
void show_encoder() {

   // toggle_bit(PORTB, led);
    // set_bit(PORTB, led); //digitalWrite(7, HIGH);

  static unsigned char counter = 0; // variavel pra armazenar valor do encoder
  char tmpdata; // dado temporario
  
  
  tmpdata = read_encoder();

  if ( tmpdata )
  {
   
  //  Serial.print("Counter value: ");
   //  Serial.println(counter);
   results [resultNumber++] = counter;
    counter += tmpdata;
  
  }

  
 // reset_bit(PORTB, led);
}
//=============================================================================
