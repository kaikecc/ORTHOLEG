//=============================================================================
// --- Desenvolvimento das Funções ---
void show_encoder() {

  static unsigned char counter = 0; // variavel pra armazenar valor do encoder
  char tmpdata; // dado temporario


  tmpdata = read_encoder();

  if ( tmpdata )
  {
    Serial.print(F("Counter value: "));
    Serial.println(counter, DEC);

    counter += tmpdata;
  }
}
//=============================================================================
