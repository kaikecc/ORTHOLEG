
//=============================================================================
// --- Desenvolvimento das Funções ---
char read_encoder()                              //Função para leitura de Rotary Encoder
{
  static char enc_states[] = {
                              0, -1, 1, 0, 
                              1, 0, 0, -1,
                              -1, 0, 0, 1, 
                              0, 1, -1, 0};
                              
  static unsigned char old_AB = 0;
  /**/
  old_AB >>= 2;                   //remember previous state

  // ou 0x30
  old_AB |= ( ENC_PORT & 0x30 );  //add current state
  
  return ( enc_states[( old_AB & 0x0f )]);

} //end read_encoder
