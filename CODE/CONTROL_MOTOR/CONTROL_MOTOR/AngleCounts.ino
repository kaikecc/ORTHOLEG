// ENC_RES = 500
// GEAR_RATIO = 43
// 
double AngleCounts(double graus){
 return (double)round(graus * ((500.0 * 43.0 * 2.0) / 360.0));// graus * CPR * N2 * X1 / 
} 
