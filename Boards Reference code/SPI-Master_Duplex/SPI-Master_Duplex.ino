/**
  ******************************************************************************
  * @Project    : SPI-Master_Duplex
  * @Autor      : Ismael Poblete V.
  * @Company    : -
  * @Date       : 03-07-2021
  * @Target     : ARDUINO UNO ATmega328P
  * @brief      : Example of SPI like Master transmit to slave and vice versa.
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

#include<SPI.h>                            
int x;
void setup (void)

{
  Serial.begin(115200);                 
  SPI.begin();        
  //Sets clock for SPI communication at 8 (16/8=2Mhz)                    
  SPI.setClockDivider(SPI_CLOCK_DIV8);    
  // Setting SlaveSelect as HIGH (So master doesnt connnect with slave)
  digitalWrite(SS, HIGH);                 
}

void loop(void)
{
  byte Mastersend, Mastereceive;
  
  //Logic for Setting x value (To be sent to slave)
  x = 1;  
         
  //Starts communication with Slave connected to master
  digitalWrite(SS, LOW);                 
  Mastersend = x;
  
  //Master gets 0x67
  Mastereceive = SPI.transfer(Mastersend); 
  //shows: 67   
  Serial.println(Mastereceive, HEX);   
  //Master gets 0x02         
  Mastereceive = SPI.transfer(Mastersend); 
  //shows: 2 (leading zero does not appear)
  Serial.println(Mastereceive, HEX);             
  
  if (Mastereceive == 2)                  
  {
    Serial.println("we got this");
  }
  else
  {
    Serial.println("dont got this");
  }
  delay(1000);
}
