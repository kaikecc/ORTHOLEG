//=============================================================================
// --- Desenvolvimento das Funções ---
void show_encoder() {

  static unsigned char counter = 0; // variavel pra armazenar valor do encoder
  char tmpdata; // dado temporario
  static unsigned i = 0;
  
  tmpdata = read_encoder();

  if ( tmpdata )
  {
    CPR[i] = &counter;
    i += 1;
  //  Serial.print("Counter value: ");
    counter += tmpdata;
    if(i == 1023) i = 0;
  }
}
//=============================================================================
