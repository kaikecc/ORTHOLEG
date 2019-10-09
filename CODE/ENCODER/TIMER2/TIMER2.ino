
// "Estrutura do Timer2 Arduino Uno"
// Modified By: Kaike Castro
// By: Wagner Rambo, Wr Kits
// https://www.youtube.com/watch?v=H-xzS8DZWZY


// --- Rotina de Interrupção ---
ISR(TIMER2_OVF_vect)
{
    TCNT2=209;          // Reinicializa o registrador do Timer2
    
    digitalWrite(10, !digitalRead(10)); //Inverte o estado da saída
}


// --- Configurações Iniciais ---
void setup()
{
     pinMode(10,OUTPUT);
     
     TCCR2A = 0x00;   //Timer operando em modo normal
     TCCR2B = 0x07;   //Prescaler 1:1024
     TCNT2  = 209;    //3 ms overflow again
     TIMSK2 = 0x01;   //Habilita interrupção do Timer2
 
} //end setup
 

// --- Loop Infinito ---
void loop()
{
   //Aguarda Interrupção...
   
   // Estouro = Timer2_cont x prescaler x ciclo de máquina
   
   // Ciclo de máquina = 1/Fosc = 1/16E6 = 62,5ns = 62,5E-9s
   
   // Estouro = (256 - 100) x 1024 x 62,5E-9 = 9,98ms ~ 10ms
   // Estouro = (256 - 178) x 1024 x 62,5E-9 = 4,99ms ~ 5ms
   // Estouro = (256 - 209) x 1024 x 62,5E-9 = 4,99ms ~ 5ms
 
} //end loop
