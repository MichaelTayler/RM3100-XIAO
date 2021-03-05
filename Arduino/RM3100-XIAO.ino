#include <SPI.h>
#define SS_pin 6 
#define SCK_pin 8 
#define MISO_pin 9
#define MOSI_pin 10
byte rawX[3],rawY[3],rawZ[3];
int32_t mx,my,mz;

void setup() {
  pinMode(SS_pin, OUTPUT);  digitalWrite(SS_pin, HIGH);
  pinMode(MOSI_pin, OUTPUT);
  pinMode(MISO_pin, INPUT); 
  pinMode(SCK_pin, OUTPUT);

  SPI.begin();  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  Serial.begin(115200);  while (!Serial);
}

void loop() {
  digitalWrite(SS_pin, LOW); 
  SPI.transfer(0x00); 
  SPI.transfer(B01110000);  // Mx+My+Mz read request (0xFF800000 = -8388608 to 0x7FFFFFFF = 8388607, approximately -800 uT to +800 uT).  Adjust for 1, 2 or 3 channels
  digitalWrite(SS_pin, HIGH); 
  delay(10);
  
  digitalWrite(SS_pin, LOW); 
  SPI.transfer(0x0A4); 
  rawX[0]=SPI.transfer(0x00); 
  rawX[1]=SPI.transfer(0x00); 
  rawX[2]=SPI.transfer(0x00); 
  rawY[0]=SPI.transfer(0x00); 
  rawY[1]=SPI.transfer(0x00); 
  rawY[2]=SPI.transfer(0x00); 
  rawZ[0]=SPI.transfer(0x00); 
  rawZ[1]=SPI.transfer(0x00); 
  rawZ[2]=SPI.transfer(0x00); 
  digitalWrite(SS_pin, HIGH); 
  
  mx=((65536*rawX[0]+256*rawX[1]+rawX[2])<<8)/800; Serial.print(mx); Serial.print(" ");
  my=((65536*rawY[0]+256*rawY[1]+rawY[2])<<8)/800; Serial.print(my); Serial.print(" ");
  mz=((65536*rawZ[0]+256*rawZ[1]+rawZ[2])<<8)/800; Serial.println(mz);   
  delay(1); 
}

/*  digitalWrite(SS_pin, LOW); // Register write and read
  SPI.transfer(0x04); 
  SPI.transfer(0x00);  SPI.transfer(0x64);
  SPI.transfer(0x00);  SPI.transfer(0x64); 
  SPI.transfer(0x00);  SPI.transfer(0x64);
  digitalWrite(SS_pin, HIGH); 
delay(1);
  digitalWrite(SS_pin, LOW); 
  SPI.transfer(0x84);
  data[0]=SPI.transfer(0x00); 
  data[1]=SPI.transfer(0x00); 
  data[2]=SPI.transfer(0x00); 
  digitalWrite(SS_pin, HIGH); 
  Serial.print(data[0]); Serial.print(", ");    Serial.print(data[1]); Serial.print(", ");  Serial.println(data[2]);
*/  
