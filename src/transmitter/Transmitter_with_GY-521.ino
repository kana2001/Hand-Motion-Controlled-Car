#include <RH_ASK.h>

#include <SPI.h>
#include <Wire.h>


// Create Amplitude shift keying object
RH_ASK rf_driver;

//Variables to store data from MPU 6050
long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;

String str_gForceX, str_gForceY, str_out;

void setup()
{
  rf_driver.init();

  //IMU/MPU Setup
  Serial.begin(9600);
  Wire.begin(); //Access I2C
  setupMPU();
}

void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - deals with power section (register map sec 4.28)
  Wire.write(0x00); //Setting SLEEP register to 0.(Required register map, sec 4.8)
  Wire.endTransmission();

  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the Gyroscope configuration (register map, sec 4.4)
  Wire.write(0x00); //Setting the gyro to full scale +/- 250deg (lowest setting)
  Wire.endTransmission();

  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the Accelerometer configuration (register 1C)
  Wire.write(0x00); //Setting the accelerometer to +/- 2g (lowest setting)
  Wire.endTransmission();
}

void recordAccelRegisters(){
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();

  Wire.requestFrom(0b1101000, 6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);  //Store bytes on a buffer on each iteration?
  accelX = Wire.read() <<8 | Wire.read(); // Store the first 2 bytes into accelX
  accelY = Wire.read() <<8 | Wire.read(); // Store the middle 2 bytes into accelY
  accelZ = Wire.read() <<8 | Wire.read(); // Store last first 2 bytes into accelZ 
  processAccelData();
}

void processAccelData() {
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0;
  gForceZ = accelZ / 16384.0;
}



void loop()
{
  //Record acceleration from IMU
  recordAccelRegisters();
//  recordGyroRegisters();
  printData();
  
  delay(10);

  str_gForceX = String(gForceX);
  str_gForceY = String(gForceY);

  // Combine gForceX and gForceY
  str_out = str_gForceX + "," + str_gForceY;
  
  // Compose output character
  static const char *msg = str_out.c_str();
  
  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();
}

void printData() {
  Serial.print("Gyro (deg)");
  Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(" Y=");
  Serial.print(rotY);
  Serial.print(" Z=");
  Serial.print(rotZ);
  Serial.print(" Accel (g)");
  Serial.print(" X=");
  Serial.print(gForceX);
  Serial.print(" Y=");
  Serial.print(gForceY);
  Serial.print(" Z=");
  Serial.print(gForceZ);
  Serial.print(" motor speed=");
  Serial.println("");
}
