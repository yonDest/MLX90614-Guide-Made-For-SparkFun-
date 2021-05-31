# SparkFun's Melexis MLX90614 Sensor Guide

A Short Melexis MLX90614 Sensor Program and Setup Guide

University of Colorado 

## Introduction 
Every object emits a wavelength in the infrared spectrum. According to the Stefan–Boltzmann law, the wavelength emitted from an object is proportional to its temperature. Infrared sensors read the infrared energy being emitted from the object, it produces an electrical signal of it to then be sent as data and processed. The Melexis MLX90614 Infrared Thermometer requires I2C protocol to communicate by way of sending its data. The MLX90614 has two interfaces: I2C and PWM (pulse width modulation) and will operate either with a 3.3V or 5V connection. The sensor contains a 17-bit ADC and a custom DSP chip to achieve high accuracy and resolution of objects being measured.
### Steps:
1. The first step in communication to the MLX90614 sensor is to write an I2C initialization, start condition, stop condition, etc. 
   
   ... Functions where the TWCR and TWSR registers have certain bits set and the TWBR register is set to the bit rate. Fortunately, there is a dedicated library that can be downloaded from GitHub for this [purpose](https://github.com/DSSCircuits/I2C-Master-Library)

2. After downloading the I2C master library and adding it to the Arduino library, the sensors can be put onto a breadboard and connected to power where the Arduino board's SDA / SCL pins are shown below. Also note, Pull-up resistors of 3.7k Ohms will be needed for this set up.

3. Pay attention to MLX90614 sensor pinout, Arduino board pinout below (other boards vary). Connect to either 3.3V or 5V.

      ![image](https://user-images.githubusercontent.com/50503074/109747823-11912300-7b95-11eb-90e9-e010f6335865.png)<br>
      <sup>Patarroyo, Jaime. (2012, July 16). [digital image]. [retrieved from site](http://wiki.wiring.co/wiki/Connecting_Infrared_Thermometer_MLX90614_to_Wiring#Download_and_Install_I.C2.B2Cmaster_library)  
4. Look for the data line (SDA) and the clock line (SCL) pins on the board, which should be clearly labelled. Using the image below, the sensor's SDA/SCL and power pin sides are shown with the tab oriented at the top of sensor.
            
      ![image](https://user-images.githubusercontent.com/50503074/109747960-4604df00-7b95-11eb-944d-aaedaedec1a3.png)<br>
Arduino UNO board pinout [other boards may vary]<br>
      ![image](https://user-images.githubusercontent.com/50503074/109747971-4bfac000-7b95-11eb-88d3-668b2723917e.png)

5. Once sensors are setup accordingly, each address must be changed to access the data of each individual sensor connected. Change the address of the other sensors to your choice of listed slave addresses found in the Melexis MLX90614 data sheet (0x00…0x7F). To do this, disconnect the sensor from power, as well as the SDA/SCL pins. Compile and upload the driver code onto the board. It is important to power cycle the sensor by just removing and then reconnecting the ground wire of the sensor. (code for address changing listed in project repo as "address_change_mlx.ino")


After each sensor address has changed to a different slave address, upload this .ino file to your arduino board with the slave addresses used from before to receive each sensors field of view temperature to the serial monitor.
