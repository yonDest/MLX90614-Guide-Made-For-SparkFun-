# MLX90614-Guide-Made-For-SparkFun-
Setup guide
A Short MLX90614 Sensor Guide

University of Colorado 

Introduction 
With using the Melexis MLX90614 Infrared Thermometer, I2C protocol communication is needed to communicate with the sensor and send its data. The MLX90614 has two interfaces: I2C and PWM (pulse width modulation) and will operate either with 3.3V or 5V. The sensor contains a 17-bit ADC and a custom DSP chip to achieve high accuracy and resolution of objects being measured. Every object emits a wavelength in the infrared spectrum. Where according to the Stefan–Boltzmann law, this wavelength is proportional to its temperature. When the sensor reads the infrared energy being emitted from the object, it produces an electrical signal of it to then be sent as data and processed.
Steps:
The first step in communication to the MLX90614 sensor is to write an I2C initialization, start condition, stop condition, etc. functions where the TWCR and TWSR registers have certain bits set and the TWBR register is set to the bit rate. Fortunately, there is a dedicated library that can be downloaded from GitHub for this purpose. (https://github.com/DSSCircuits/I2C-Master-Library)

After downloading the I2C master library and adding it to the Arduino library, the MLX90614 sensors can be put onto a breadboard and connected to power where the Arduino board SDA / SCL pins are shown below. Pull-up resistors of 3.7k Ohms will be needed for this set up.

![image](https://user-images.githubusercontent.com/50503074/109747823-11912300-7b95-11eb-90e9-e010f6335865.png)

(Patarroyo, Jaime. (2012, July 16). [digital image]. Retrieved from http://wiki.wiring.co/wiki/Connecting_Infrared_Thermometer_MLX90614_to_Wiring#Download_and_Install_I.C2.B2Cmaster_library)

--->

![image](https://user-images.githubusercontent.com/50503074/109747960-4604df00-7b95-11eb-944d-aaedaedec1a3.png)

![image](https://user-images.githubusercontent.com/50503074/109747971-4bfac000-7b95-11eb-88d3-668b2723917e.png)

            
Pay attention to MLX90614 sensor pinout		Arduino UNO board pinout (other boards vary)


Once sensors are setup, the address must be changed to access data of each individual sensor. To do this disconnect one sensor from power and the data / clock line. Compile and upload this code onto the board. Change the address of the other sensor (code for address changing listed in project repo as "address_change_mlx.ino") as well to your choice of listed slave addresses found in the MLX90614 data sheet (0x00…0x7F). Also remember to power cycle the sensor, by just removing and then re-connecting ground wire of sensor.


After each sensor address has changed to a different slave address, upload this .ino file to your arduino board with the slave addresses used from before to receive each sensors field of view temperature to the serial monitor.
