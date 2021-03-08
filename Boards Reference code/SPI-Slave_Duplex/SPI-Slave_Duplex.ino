/**
  ******************************************************************************
  * @Project    : SPI-Slave_Duplex
  * @Autor      : Ismael Poblete V.
  * @Company    : -
  * @Date       : 03-07-2021
  * @Target     : ARDUINO UNO ATmega328P
  * @brief      : Example of SPI like slave transmit to master vice versa.
  *
  * @Lib      : SPI
  * @Perf
  *   *SPI  16/SPI_CLOCK_DIV8 = 2MHz
  *     13     <-----> SCK
  *     12     <-----> MISO
  *     11     <-----> MOSI
  *     10     <-----> SS
  ******************************************************************************
**/

#include <SPI.h>          
volatile bool received = false;
volatile byte Slavereceived;

void setup ()
{
  Serial.begin(115200);
  pinMode(SS, INPUT_PULLUP); 
  pinMode(MISO, OUTPUT);
  //Arduino is Slave
  SPCR |= _BV(SPE);
  SPCR &= ~(_BV(MSTR)); 
  //test value
  SPDR = 0x67;  
  SPCR |= _BV(SPIE);   
  //global interrupt bit is enabled   
  sei();                           
}

void loop()
{
    if(received == true)
    {
       Serial.println(Slavereceived, HEX);
       received = false;
    }
}

ISR (SPI_STC_vect)                        
{
  //Value received from master is stored in variable slavereceived
  Slavereceived = SPDR; 
  //Send data for Master to be reached there at the next port cycle             
  SPDR = 0x02;                           
  received = true;                       
}
