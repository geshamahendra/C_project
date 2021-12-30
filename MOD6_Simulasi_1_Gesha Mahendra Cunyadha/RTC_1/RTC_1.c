/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 11/9/2021
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
#include <stdlib.h>

// I2C Bus functions
#include <i2c.h>

// PCF8583 Real Time Clock functions
#include <pcf8583.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
unsigned char hdetik, detik, menit, jam, hari, bulan;
unsigned int tahun;
char line1[16], line2[16];
char* bulantext[12] = {"Januari","Februari","Maret","April","Mei","Juni","Juli","Agustus","September","Oktober","November","Desember"};

void main(void)
{
// Declare your local variables here

// Bit-Banged I2C Bus initialization
// I2C Port: PORTA
// I2C SDA bit: 1
// I2C SCL bit: 0
// Bit Rate: 100 kHz
// Note: I2C settings are specified in the
// Project|Configure|C Compiler|Libraries|I2C menu.
i2c_init();

// PCF8583 Real Time Clock initialization
rtc_init(0,0);
rtc_set_time(0,21,29,9,0);
rtc_set_date(0,20,10,15);

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

while (1)
      {
      // Place your code here
      rtc_get_date(0, &hari, &bulan, &tahun);
      sprintf(line1,"%2d %s %4d",hari, bulantext[bulan-1], 2000+tahun);
      lcd_gotoxy(0,0);
      lcd_puts(line1);
      delay_ms(250);
      
      rtc_get_time(0, &jam, &menit, &detik, &hdetik);
      sprintf(line2,"%2d:%02d:%02d",jam, menit, detik);
      lcd_gotoxy(0,1);
      lcd_puts(line2);
      delay_ms(250);
      }
}
