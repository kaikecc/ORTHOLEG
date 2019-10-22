//=============================================================================
// --- Desenvolvimento das Funções ---
void show_encoder() {

  static unsigned char counter = 0; // variavel pra armazenar valor do encoder
  char tmpdata; // dado temporario
  static unsigned i = 0;
  
  tmpdata = read_encoder();

  if ( tmpdata )
  {
   
  //  Serial.print("Counter value: ");
      Serial.println(counter,DEC);
    counter += tmpdata;
  
  }
}
//=============================================================================
