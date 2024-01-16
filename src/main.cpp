#include <M5Stack.h>
u_int8_t data = 0b01010101;

void setup() {
  M5.begin();
  SPI.begin(SCK, MISO, MOSI, SS);   //Default: 18, 19, 23, 5
  SPI.setHwCs(true);                //It makes working ChipSelect (SS pin above) automatically
}

void loop() {
  SPI.beginTransaction(SPISettings());  //Default: 1000000, SPI_MSBFIRST, SPI_MODE0
  SPI.transfer(data);  //Return value is received data. (transfer16 and transfer32 also available)
  SPI.endTransaction();
}
