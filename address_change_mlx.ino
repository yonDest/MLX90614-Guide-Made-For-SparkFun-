 #include "I2C.h"

 // New slave address (default is 0x5A)
 byte NewMLXAddr = 0x2B;

 void setup(){   
   Serial.begin(9600);
   Serial.println("Setup...");
   // Initialise some stuff
   i2c_init();
   PORTC = (1 << PORTC4) | (1 << PORTC5);
   delay(5000);
   // Read on universal address (0)
   ReadAddr(0);
   // Change to new address NewMLXAddr
   ChangeAddr(NewMLXAddr, 0x00);
   // Read on universal address (0)
   ReadAddr(0);
   Serial.println("**---READY---**");
   Serial.println("> [setup] Cycle power NOW to store new address - you have 10 seconds");
   delay(10000);
   // Read on universal address (0)
   ReadAddr(0);
   Serial.println("  Warning, next ReadTemp() may fail if address has not been set.");
   ReadTemp(NewMLXAddr);
   Serial.println("**---DONE---**");
 }


 //Read temperature from MLX at new address once setup() is done.
 
 void loop(){
     delay(5000);
     ReadTemp(NewMLXAddr);
 }

 /**
 * Changes the address of the MLX to NewAddr1.
 */
 word ChangeAddr(byte NewAddr1, byte NewAddr2) {
   Serial.print("> [ChangeAddr] Will change address to: ");
   Serial.println(NewAddr1, HEX);
   i2c_start_wait(0 + I2C_WRITE); // address sensor + write 
   i2c_write(0x2E); // current address
   i2c_write(0x00); // clear high and low bits
   i2c_write(0x00);

   if (i2c_write(0x6F) == 0) {
     i2c_stop();
     Serial.println("> [ChangeAddr] Data erased.");
   }
   else {
     i2c_stop();
     Serial.println("> [ChangeAddr] Failed to erase data");
     return -1;
   }

   Serial.print("> [ChangeAddr] Writing data: ");
   Serial.print(NewAddr1, HEX);
   Serial.print(", ");
   Serial.println(NewAddr2, HEX);

   for (int a = 0; a != 256; a++) {
     i2c_start_wait(0 + I2C_WRITE);
     i2c_write(0x2E);
     i2c_write(NewAddr1);
     i2c_write(NewAddr2);

     if (i2c_write(a) == 0) {
       i2c_stop();
       delay(100);
       Serial.print("> [ChangeAddr] Found correct CRC: 0x");
       Serial.println(a, HEX);
       return a;
     }
   }
   i2c_stop();
   Serial.println("> [ChangeAddr] Correct CRC not found");
   return -1;
 }

 /**
 * Reads the MLX address.
 *
 */
 byte ReadAddr(byte MLXAddress) {
   byte NewMLXAddress;
   Serial.println("> [ReadAddr] Reading address");
   if (MLXAddress == 0) {
     Serial.print("  Using MLX univeral address");
   } else {
     Serial.print("  Using MLX address: ");
     Serial.print(MLXAddress, HEX);
   }
   Serial.print(", Data: ");
   i2c_start_wait(MLXAddress + I2C_WRITE);
   i2c_write(0x2E);
   i2c_rep_start(MLXAddress + I2C_READ);

   NewMLXAddress = i2c_readAck();
   Serial.print(NewMLXAddress, HEX);
   Serial.print(", ");
   Serial.print(i2c_readAck(), HEX);
   Serial.print(", ");
   Serial.println(i2c_readNak(), HEX);
   i2c_stop();
   return NewMLXAddress;
 }
  float ReadTemp(byte address) {
   int data_low = 0;
   int data_high = 0;
   int pec = 0;
   byte MLXAddress = address<<1;

   Serial.print("> [ReadTemp] Read temperature ");
   if (MLXAddress == 0) {
     Serial.print("using MLX univeral address");
   } else {
     Serial.print("using MLX address ");
     Serial.print(address, HEX);
   };
   Serial.print(": ");

   i2c_start_wait(MLXAddress + I2C_WRITE);
   i2c_write(0x07); // command for temperture in device's RAM
   i2c_rep_start(MLXAddress + I2C_READ);
   data_low = i2c_readAck();
   data_high = i2c_readAck();
   pec = i2c_readNak();
   i2c_stop();

   float temp = 0x0000;
   temp = (float)(((data_high & 0x007F) << 8) + data_low);
   temp = (temp * 0.02) - 273.16;
   Serial.print(temp);
   Serial.println(" C");
   return temp;
 }
