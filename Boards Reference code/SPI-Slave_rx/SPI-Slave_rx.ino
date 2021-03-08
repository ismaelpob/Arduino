/**
  ******************************************************************************
  * @Project    : SPI-Slave_rx
  * @Autor      : Ismael Poblete V.
  * @Company    : -
  * @Date       : 03-07-2021
  * @Target     : ARDUINO UNO ATmega328P
  * @brief      : Example of SPI like Slave receive form master.
  *
  * @Lib      : SPI
  * @Perf
  *   *SPI  16/SPI_CLOCK_DIV8 = 2MHz
  *     13     <-----> SCK
  *     12     <-----> MISO
  *     11     <-----> MOSI
  *     10     <-----> SS
  ******************************************************************************
*/

#include <SPI.h>
char buff [50];
volatile byte indx;
volatile boolean process;

void setup (void) {
  Serial.begin (115200);
  pinMode(MISO, OUTPUT); // have to send on master in so it set as output
  SPCR |= _BV(SPE); // turn on SPI in slave mode
  indx = 0; // buffer empty
  process = false;
  SPI.attachInterrupt(); // turn on interrupt
}
ISR (SPI_STC_vect){ // SPI interrupt routine
  byte c = SPDR; // read byte from SPI Data Register
  if (indx < sizeof buff) {
    buff [indx++] = c; // save data in the next index in the array buff
    if (c == '\n'){ //check for the end of the word
      process = true;
    }
  }
}

void loop (void) {
  if (process) {
    process = false; //reset the process
    Serial.print(buff); //print the array on serial monitor
    indx = 0; //reset button to zero
  }
}
