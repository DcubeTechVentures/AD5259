// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AD5259
// This code is designed to work with the AD5259_I2CPOT_10K I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Potentiometers?sku=AD5259_I2CPOT_50K#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// AD5259 I2C address is 0x18(24)
#define Addr 0x18

float resistance = 0.0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "AD5259");
  Particle.variable("resistance", resistance);

  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Send command byte
  Wire.write(0x00);
  // Input resistance value, 0x80(128)
  Wire.write(0x80);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data;

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Send command byte
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);

  // Read 1 byte of data
  if (Wire.available() == 1)
  {
    data = Wire.read();
  }

  // Convert the data
  resistance = (data / 256.0 ) * 10.0;

  // Output data to dashboard
  Particle.publish("Resistance : ", String(resistance) + " K");
  delay(500);
}

