#include "C:\Users\sherif\Documents\cnc\main.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Variable Initialization
int xcycle = 0;
int ycycle = 0;
long int right = 0;
long int left = 0;
long int up = 0;
long int down = 0;
long int xdirection = 0;
long int ydirection = 0;
long int z = 0;

float xcurrent = 0;
float ycurrent = 0;
float xdestination = 0;
float ydestination = 0;
float slope=0;
long int timervalue = 0;
float xdir = 0.0;
float ydir = 0.0;

//Interupt Routine For X Axis Stepper Motor
#INT_RTCC
void dod()
{

set_timer0(0);
if(xdirection == 1 && right != 0)
{

switch(xcycle)
{
      case 0:
      output_high(PIN_B4);
      output_low(PIN_B5);
      output_high(PIN_B6);
      output_high(PIN_B7);
      xcycle++;
      break;
      case 1:
      output_high(PIN_B4);
      output_low(PIN_B5);
      output_low(PIN_B6);
      output_low(PIN_B7);
      xcycle++;
      break;
      case 2:
      output_low(PIN_B4);
      output_high(PIN_B5);
      output_low(PIN_B6);
      output_low(PIN_B7);
      xcycle++;
      break;
      case 3:
      output_low(PIN_B4);
      output_high(PIN_B5);
      output_high(PIN_B6);
      output_high(PIN_B7);
      xcycle=0;
      right--;
      break;
      default:
      break;
}
}else
{
   if(xdirection == 0 && left != 0)
{

switch(xcycle)
{
      case 0:
      output_high(PIN_B4);
      output_low(PIN_B6);
      output_high(PIN_B5);
      output_high(PIN_B7);
      xcycle++;
      break;
      case 1:
      output_high(PIN_B4);
      output_low(PIN_B5);
      output_low(PIN_B6);
      output_low(PIN_B7);
      xcycle++;
      break;
      case 2:
      output_low(PIN_B4);
      output_high(PIN_B6);
      output_low(PIN_B5);
      output_low(PIN_B7);
      xcycle++;
      break;
      case 3:
      output_low(PIN_B4);
      output_high(PIN_B5);
      output_high(PIN_B6);
      output_high(PIN_B7);
      xcycle=0;
      left--;
      break;
      default:
      break;
}
}else
{

      disable_interrupts(INT_RTCC);
      
      output_low(PIN_D3);
      
}

}


}
//Interupt Routine For Y Axis Stepper Motor
#INT_TIMER1
void t2()
{
set_timer1(timervalue);

if(ydirection == 1 && up != 0)
{

switch(ycycle)
{
      case 0:
      output_high(PIN_B0);
      output_low(PIN_B2);
      output_high(PIN_B1);
      output_high(PIN_B3);
      ycycle++;
      break;
      case 1:
      output_high(PIN_B0);
      output_low(PIN_B1);
      output_low(PIN_B2);
      output_low(PIN_B3);
      ycycle++;
      break;
      case 2:
      output_low(PIN_B0);
      output_high(PIN_B2);
      output_low(PIN_B1);
      output_low(PIN_B3);
      ycycle++;
      break;
      case 3:
      output_low(PIN_B0);
      output_high(PIN_B1);
      output_high(PIN_B2);
      output_high(PIN_B3);
      ycycle=0;
      up--;
      break;
      default:
      break;
}
}else
{
   if(ydirection == 0 && down != 0)
{

switch(ycycle)
{
      case 0:
      output_high(PIN_B0);
      output_low(PIN_B1);
      output_high(PIN_B2);
      output_high(PIN_B3);
      ycycle++;
      break;
      case 1:
      output_high(PIN_B0);
      output_low(PIN_B2);
      output_low(PIN_B1);
      output_low(PIN_B3);
      ycycle++;
      break;
      case 2:
      output_low(PIN_B0);
      output_high(PIN_B1);
      output_low(PIN_B2);
      output_low(PIN_B3);
      ycycle++;
      break;
      case 3:
      output_low(PIN_B0);
      output_high(PIN_B1);
      output_high(PIN_B2);
      output_high(PIN_B3);
      ycycle=0;
      down--;
      break;
      default:
      break;
}
}else
{

      disable_interrupts(INT_TIMER1);
      output_low(PIN_D3);
      
}

}


}
//Calculate X Axis Stepper Motor Steps (1.8 degree / step motor)
long int CalculateXSteps(float DistanceInCm)
{
   long int steps = 0;
   
   steps = (( DistanceInCm * 360.0 ) / (1.8*15.6));
   
   return steps;
}
//Calculate Y Axis Stepper Motor Steps (1.8 degree / step motor)
long int CalculateYSteps(float DistanceInCm)
{
   long int steps = 0;
   
   steps = (( DistanceInCm * 360.0 ) / (1.8*15.6));
   
   return steps;
}
//Drawing Function
void DrawLine(float x0,float y0, float x1, float y1)
{
//Slope Calculation To Determine The Speed Of Each Motors (Steps / Seconds)
   if((x1 - x0) != 0)
   slope = fabs((y1 - y0) / (x1 - x0));
   else
   slope = 1.0;
   
   timervalue = (2097152 - (262144 / slope)) / 32;
   xdir = x1 - x0;
   if(xdir >= 0)
   {
   right = CalculateXSteps(fabs(xdir));
   xdirection = 1;
   xcurrent = x1;
   }else
   {
   left = CalculateXSteps(fabs (xdir));
   xdirection = 0;
   xcurrent = x1;
   }
   
   ydir = y1 - y0;
   if(ydir >= 0)
   {
   up = CalculateXSteps(fabs(ydir));
   ydirection = 1;
   ycurrent = y1;
   }else
   {
   down = CalculateXSteps(fabs(ydir));
   ydirection = 0;
   ycurrent = y1;
   }
   if(z == 1)
   {
      output_high(PIN_D2);
   }else
   {
      output_low(PIN_D2);   
   }
//Set Timers For X And Y Axis Steppers
   set_timer1(timervalue);
   set_timer0(0);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_RTCC);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256);
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
}
    
void main()
{
   
//Variable Initialization
   long int i = 0;

   char input[10];
   char data[10];
   char x[10] = "x";
   char y[10] = "y";
   char zz[10] = "z";
   char go[10] = "go";
   char init[10] = "init";

//Initialization Of PIC Microcontroller Peripherals
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   enable_interrupts(GLOBAL);

   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   
//Waits For gcode interface To Send Command
   gets(input);

   delay_ms(500);
   while(1)
   {
   
   while(strcmp(input,go) != 0)
   {
   printf("next\n");

   gets(input);
   if(strcmp(input,x) == 0)
   {

   gets(data);
   xdestination = atof(data);
   
   }
   if(strcmp(input,y) == 0)
   {

   gets(data);
   ydestination = atof(data);

   }
   if(strcmp(input,zz) == 0)
   {

   gets(data);
   z=atoi(data);

   }
   strcpy(data,"");
   }
   printf("wait\n");
   strcpy(data,"");
   strcpy(input,"");

      //Led
   output_high(PIN_D3);
   
   
   //Draw The Line From X1,Y1 To X2,Y2
   DrawLine(xcurrent,ycurrent,xdestination,ydestination);
//Waits Until The Process Is Finished And For Next Gcode Command
   while(right != 0 || left != 0 || up != 0 || down != 0)
   {
   
   }
   //Blinking Led
   output_low(PIN_D3);

   }

}
