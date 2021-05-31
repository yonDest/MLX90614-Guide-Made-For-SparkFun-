#include <i2cmaster.h>
/*
   Two Infrared Thermometers MLX90614 
   I2C bus infrared sensors for tire temperature to monitor
 */

 int device1 = 0x2A<<1;   // 0x2A is the assigned address for I2C
                          // communication for the first infrared sensor
                          // shifted right for write, use of 7 most 
                          // significant bits 
 int device2 = 0x2B<<1;   // 0x2B is the assigned address for I2C
                          // communication for the second infrared sensor  

 float degrees1 = 0.0;
 float degrees2 = 0.0;

 void setup(){
    Serial.begin(9600); // set baud rate
    i2c_init(); // initialize i2c communication
    PORTC = (1 << PORTC4) | (1 << PORTC5); // enable internal pullups
 }

 void loop(){
  
  degrees1 = temperature(device1); // get temperature of sensor one
  
  degrees2 = temperature(device2);
 
  // print temperatures
  Serial.print("Sensor 1 : tire temperature is "); 
  Serial.println(degrees1); 
  Serial.print("Sensor 2 : tire temperature is "); 
  Serial.println(degrees2);
  Serial.println("idle...");
  delay(1000);
 }

 float temperature(int dev)
 {
  int data_low, data_high;
  int pec = 0;
  // write to line
  i2c_start_wait(dev+I2C_WRITE);
  i2c_write(0x07);

  // read 
  i2c_rep_start(dev+I2C_READ);
  data_low = i2c_readAck(); // store first byte
  data_high = i2c_readAck(); // store next byte
  pec = i2c_readNak();
  i2c_stop();

  // convert high byte + low byte to temperature value
  // mask error bit and put into one
  float temp = 0x0000;
  temp = (float)(((data_high & 0x007F) << 8) + data_low);
  temp = (temp * 0.02) - 273.16;
  temp = (temp * 9/5) + 32;
  
  return temp;
 }
