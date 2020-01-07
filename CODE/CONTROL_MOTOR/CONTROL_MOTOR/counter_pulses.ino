void counter_pulses() {

  static bool old_state;
  static bool enc_B;
  static byte ENC_last;
  static boolean direction_m;

  old_state = (PINB & (1 << ENC_A)); //Lê estado de ENC_A e armazena em old_state

  if (!ENC_last && old_state) { //ENC_lastigual a zero e old_state diferente de zero?
    //Sim...
    enc_B =  (PINB & (1 << ENC_B)); //Lê estado de  ENC_B e armazena em  ENC_B

    if (!enc_B && direction_m) direction_m = false;     //Sentido reverso
    else if (enc_B && !direction_m) direction_m = true; //Sentido direto
  } //end if
  ENC_last = old_state;

  if (!direction_m)  pulse_number++;           //incrementa número do pulso se direction limpa
  else              pulse_number--;           //senão decrementa
 
}
