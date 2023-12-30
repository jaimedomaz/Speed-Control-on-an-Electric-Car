
void HCSR04_2_init(void)
{  
   setup_timer_3(T3_INTERNAL | T3_DIV_BY_8); 
}

float HCSR04_2_get_distance(void)
{
   int16 tiempo_eco=0;
   float distancia=0;
   float tick = 0;
   tick = (4000.0 / fosc) * 8.0;
   output_high(P_TRIG2); 
   delay_us(10);
   output_low(P_TRIG2);
   while(!input_state(P_ECHO2)){
   } 
   set_timer3(0); 
   while(input_state(P_ECHO2)){
   } 
   tiempo_eco = get_timer3();
   distancia = (tiempo_eco/2.0)*tick*34.0;
   return distancia;
}
