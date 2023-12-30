

void HCSR04_1_init(void)
{  
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8); 
}

float HCSR04_1_get_distance(void)
{
   int16 tiempo_eco=0;
   float distancia=0;
   float tick = 0;
   tick = (4000.0 / fosc) * 8.0;
   output_high(P_TRIG1); 
   delay_us(10);
   output_low(P_TRIG1);
   while(!input_state(P_ECHO1)){
   } 
   set_timer1(0); 
   while(input_state(P_ECHO1)){
   } 
   tiempo_eco = get_timer1();
   distancia = (tiempo_eco/2.0)*tick*34.0;
   return distancia;
}
