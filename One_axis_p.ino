#include <Servo.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
Servo aileronservo ;
Servo elevatorservo ;
Servo rudderservo ;
int aileron;
int rudder;
int elevator;
int val;
int prevVal;
int pin=3;
void setup()
{
    Wire.begin();
    Serial.begin(115200);
    Serial.println("Initialize MPU");
    mpu.initialize();
    Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");
    aileronservo .attach(9);
    elevatorservo .attach(10);
    rudderservo .attach(8);
}
void loop()
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    val = map(az,-17000,17000,-17000,17000);
    if (val != prevVal )
    {
        rudderservo.write(val);
        prevVal = val;
        Serial.println(val);
    }
     
    
    delay(10);
}

