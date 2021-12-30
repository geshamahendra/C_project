/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 11/18/2021
Author  : 
Company : 
Comments: 


Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 10.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*******************************************************/

#include <mega128.h>
#include <delay.h>
#include <stdio.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here

bit start_bit=0;
int counter;
char text[16];

#define proses_isi      0B00010011             //INFLOW1 & INFLOW2 ON
#define proses_panas    0B00001000             //STIRON & HTRON aktif
#define proses_kosong   0B00100100             //OUTFLOW aktif
#define shutdown        0B01110000             //ALARM aktif
#define normal          0B00010000             //Aktuator Off

#define TANKMT PINE.0
#define TEMPOK PINE.1 
#define TANKFUL PINE.2
 

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
 PORTA= shutdown;
 lcd_clear();
 lcd_gotoxy(0,1);
 lcd_putsf("Shutdown..!");
 EIMSK= 0x00;            //disable INT
}

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
// Place your code here
  start_bit ^=1; //start_bit=start_bit EXOR 1
 if (start_bit==0 && counter>0)
 {
  lcd_clear();
  lcd_gotoxy(0,0);
  lcd_putsf("PROCESS CONTROL");
  lcd_gotoxy(6,1);
  lcd_putsf("HOLD");
  delay_ms(1000);
 } else if ((start_bit==0) && (counter=0))
 {       
  lcd_clear();
  PORTA= normal;
  lcd_gotoxy(0,0);
  lcd_putsf("PROCESS CONTROL");
  lcd_gotoxy(0,1);
  lcd_putsf("Add counter !!!"); 
  delay_ms(1000);
 } else
 {
  lcd_clear();
  lcd_gotoxy(0,0);
  lcd_putsf("PROCESS CONTROL");
  lcd_gotoxy(6,1);
  lcd_putsf("ON  ");
  delay_ms(1000);
 }
}

// External Interrupt 2 service routine
interrupt [EXT_INT2] void ext_int2_isr(void)
{
// Place your code here
 counter=counter+1;
 lcd_clear();
 lcd_gotoxy(0,0);
 lcd_putsf("PROCESS CONTROL");
 lcd_gotoxy(0,1);
 sprintf(text,"Counter = %d ",counter); 
 lcd_puts(text);
 delay_ms(500);
}

// External Interrupt 3 service routine
interrupt [EXT_INT3] void ext_int3_isr(void)
{
// Place your code here
 counter=0;
 lcd_clear();
 lcd_gotoxy(0,0);
 lcd_putsf("PROCESS CONTROL");
 lcd_gotoxy(0,1);
 sprintf(text,"Counter = %d ",counter); 
 lcd_puts(text);
 delay_ms(1000);
}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRA=(0<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
// State: Bit7=T Bit6=0 Bit5=0 Bit4=1 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (1<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Port E initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=Out Bit1=Out Bit0=Out 
DDRE=(0<<DDE7) | (0<<DDE6) | (0<<DDE5) | (0<<DDE4) | (0<<DDE3) | (1<<DDE2) | (1<<DDE1) | (1<<DDE0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=0 Bit1=0 Bit0=0 
PORTE=(0<<PORTE7) | (0<<PORTE6) | (0<<PORTE5) | (0<<PORTE4) | (0<<PORTE3) | (0<<PORTE2) | (1<<PORTE1) | (1<<PORTE0);

// Port F initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRF=(0<<DDF7) | (0<<DDF6) | (0<<DDF5) | (0<<DDF4) | (0<<DDF3) | (0<<DDF2) | (0<<DDF1) | (0<<DDF0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTF=(0<<PORTF7) | (0<<PORTF6) | (0<<PORTF5) | (0<<PORTF4) | (0<<PORTF3) | (0<<PORTF2) | (0<<PORTF1) | (0<<PORTF0);

// Port G initialization
// Function: Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRG=(0<<DDG4) | (0<<DDG3) | (0<<DDG2) | (0<<DDG1) | (0<<DDG0);
// State: Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTG=(0<<PORTG4) | (0<<PORTG3) | (0<<PORTG2) | (0<<PORTG1) | (0<<PORTG0);

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: On
// INT1 Mode: Falling Edge
// INT2: On
// INT2 Mode: Falling Edge
// INT3: On
// INT3 Mode: Falling Edge
// INT4: Off
// INT5: Off
// INT6: Off
// INT7: Off
EICRA=(1<<ISC31) | (0<<ISC30) | (1<<ISC21) | (0<<ISC20) | (1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
EICRB=(0<<ISC71) | (0<<ISC70) | (0<<ISC61) | (0<<ISC60) | (0<<ISC51) | (0<<ISC50) | (0<<ISC41) | (0<<ISC40);
EIMSK=(0<<INT7) | (0<<INT6) | (0<<INT5) | (0<<INT4) | (1<<INT3) | (1<<INT2) | (1<<INT1) | (1<<INT0);
EIFR=(0<<INTF7) | (0<<INTF6) | (0<<INTF5) | (0<<INTF4) | (1<<INTF3) | (1<<INTF2) | (1<<INTF1) | (1<<INTF0);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 0
// RD - PORTC Bit 2
// EN - PORTC Bit 1
// D4 - PORTC Bit 4
// D5 - PORTC Bit 5
// D6 - PORTC Bit 6
// D7 - PORTC Bit 7
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")

lcd_putsf("PROCESS CONTROL");
lcd_gotoxy(6,1);
lcd_putsf("OFF");

while (1)
      {
      // Place your code here
        if (counter==0)
        { 
            lcd_clear();
            PORTA= normal;
            lcd_gotoxy(0,0);
            lcd_putsf("PROCESS CONTROL");
            lcd_gotoxy(0,1);
            lcd_putsf("Add counter !!!"); 
            delay_ms(1000);
        }else
            {
            lcd_clear();
            lcd_gotoxy(0,0);
            lcd_putsf("PROCESS CONTROL");
            lcd_gotoxy(0,1);
            sprintf(text,"Counter = %d ",counter); 
            lcd_puts(text);
            delay_ms(1000);
        };
        
        while (start_bit==1 && counter>0)
        {
            lcd_clear();
            PORTA= proses_isi;
            lcd_putsf("Fill process...");
            while(~TANKFUL){ };          //tunggu sampai TANKFUL=1
            lcd_gotoxy(0,1);
            lcd_putsf("Succes....!");
            delay_ms(1000);
            
            lcd_clear();
            PORTA= proses_panas;
            lcd_putsf("Heat process...");
            while(TEMPOK){ };          //tunggu sampai TEMPOK=0
            lcd_gotoxy(0,1);
            lcd_putsf("Succes....!");
            delay_ms(1000);
            
            lcd_clear();
            PORTA= proses_kosong;
            lcd_putsf("Empty process...");
            while(TANKMT){ };          //tunggu sampai TANKMT=0
            lcd_gotoxy(0,1);
            lcd_putsf("Succes....!");
            counter= counter-1;
            delay_ms(1000);
            
            lcd_clear();
            lcd_gotoxy(0,0);
            lcd_putsf("PROCESS CONTROL");
            lcd_gotoxy(0,1);
            sprintf(text,"Counter = %d ",counter); 
            lcd_puts(text);
            PORTA= normal;
            delay_ms(1000);
        };
        
        if (counter==0)
        { 
            start_bit=0;
            lcd_gotoxy(0,0);
            lcd_putsf("PROCESS CONTROL");
            lcd_gotoxy(0,1);
            lcd_putsf("Add counter !!!"); 
            delay_ms(1000);
        };
      }
}
