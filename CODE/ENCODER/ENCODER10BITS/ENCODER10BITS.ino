//*************************************************************************************************************
//
//  Firmware to control the SSI Interface for the AEAT-6010 magnetic encoder
//
//
//  2013-04-12  HB
//
// https://www.circuitsonline.net/forum/view/112693
//
//*************************************************************************************************************

// Definitions for the AEAT-6010
int SSI_CLK = 7;
int  DataIN = 8;
int  NCS = 4;
int Test = 13;

// Definitions for variables
unsigned int reading;

// program starts here
// **************************

void setup() {                
  
  Serial.begin(9600);
  
  // initialize the digital pin as an output.
  pinMode(NCS, OUTPUT);   // Chip select
  pinMode(SSI_CLK, OUTPUT);   // Serial clock
  pinMode(DataIN, INPUT);   // Serial data IN/OUT
  pinMode(Test, OUTPUT);   

  digitalWrite(SSI_CLK, HIGH);  
  digitalWrite(Test, LOW);   
}

//***********************************************************************
// Main program loop
//***********************************************************************
void loop() {

unsigned int reading;
  
  ReadSSI();
  Serial.println(reading,DEC);
  delay(10);
  
}

 
//***********************************************************************
// Main Loop ends here
// Start of subroutines
//***********************************************************************

void ReadSSI(void)
{
int i;
char Res = 10;
unsigned int mask;

  reading = 0;
        mask = 0x0200;
  digitalWrite(NCS, LOW);
  delayMicroseconds(1);
  digitalWrite(SSI_CLK, LOW);

  for(i=(Res-1);i>0;i--)
  {
    digitalWrite(SSI_CLK, HIGH);
    delayMicroseconds(1);
  if (digitalRead(DataIN)) reading |= mask; 
  digitalWrite(SSI_CLK, LOW);
  mask = mask >> 1;

  if (i == 1) 
          {
          digitalWrite(SSI_CLK, HIGH);
    if (digitalRead(DataIN)) reading |= mask; 
          }
  }

  digitalWrite(NCS, HIGH);
}
