// --- Mapeamento de Hardware ---
#define ENC_A PB5 // D13 - encoder A
#define ENC_B PB4 // D12 - encoder B
#define ENC_PORT PINB

#define rmpwmpin PD3  // D3 - right motor pulse width  modulation pin    0 - 255          Speed and Brake 
#define rmbrkpin PD4  //  D4 - right motor brake        control    pin    HIGH = Brake 
#define rmdirpin PD2  // D10 - right motor direction    control    pin    HIGH = Forward   Low = Reverse
#define rmcurpin 7   //  A7 - right motor current      monitor    pin    0 - 1023         -20A to +20A   

#define lmpwmpin PB3  // D11 - left  motor pulse width  modulation pin     0 - 255          Speed and Brake
#define lmbrkpin PB1  //  D9 - left  motor brake        control    pin    HIGH = Brake 
#define lmdirpin PB2  //  D2 - left  motor direction    control    pin    HIGH = Forward   Low = Reverse
#define lmcurpin  6   //  A6 - left  motor current      monitor    pin    0 - 1023         -20A to +20A   
