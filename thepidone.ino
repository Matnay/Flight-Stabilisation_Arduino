#include <Wire.h>
#include <Servo.h>


Servo elevator_servo;
Servo rudder_servo;
int16_t Acc_rawX, Acc_rawY, Acc_rawZ,Gyr_rawX, Gyr_rawY, Gyr_rawZ;
 
float Acceleration_angle[2];
float Gyro_angle[2];
float Total_angle[2];




float elapsedTime, time, timePrev;
int i;
float rad_to_deg = 180/3.141592654;

float PID, pwmLeft, pwmRight, error, previous_error;
float pid_p=0;
float pid_i=0;
float pid_d=0;

double kp=3.55;
double ki=0.005;
double kd=2.05;


double throttle=1300;
float desired_angle = 0;


void setup() {
  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(250000);
  elevator_servo.attach(7);
  rudder_servo.attach(8); 

  time = millis();
  rudder_servo.writeMicroseconds(1000); 
  elevator_servo.writeMicroseconds(1000);
  delay(7000);
}

void loop() {
    timePrev = time; 
    time = millis();  
    elapsedTime = (time - timePrev) / 1000; 
     Wire.beginTransmission(0x68);
     Wire.write(0x3B); 
     Wire.endTransmission(false);
     Wire.requestFrom(0x68,6,true);
    
     Acc_rawX=Wire.read()<<8|Wire.read(); 
     Acc_rawY=Wire.read()<<8|Wire.read();
     Acc_rawZ=Wire.read()<<8|Wire.read();

 

  
     Acceleration_angle[0] = atan((Acc_rawY/16384.0)/sqrt(pow((Acc_rawX/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
    
     Acceleration_angle[1] = atan(-1*(Acc_rawX/16384.0)/sqrt(pow((Acc_rawY/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;

    
   Wire.beginTransmission(0x68);
   Wire.write(0x43); 
   Wire.endTransmission(false);
   Wire.requestFrom(0x68,4,true); 
   
   Gyr_rawX=Wire.read()<<8|Wire.read(); 
   Gyr_rawY=Wire.read()<<8|Wire.read();
 
   Gyro_angle[0] = Gyr_rawX/131.0;
   Gyro_angle[1] = Gyr_rawY/131.0;


   Total_angle[0] = 0.98 *(Total_angle[0] + Gyro_angle[0]*elapsedTime) + 0.02*Acceleration_angle[0];
   Total_angle[1] = 0.98 *(Total_angle[1] + Gyro_angle[1]*elapsedTime) + 0.02*Acceleration_angle[1];
  

   

error = Total_angle[1] - desired_angle;
pid_p = kp*error;
if(-3 <error <3)
{
  pid_i = pid_i+(ki*error);  
}
pid_d = kd*((error - previous_error)/elapsedTime);
PID = pid_p + pid_i + pid_d;

if(PID < -1000)
{
  PID=-1000;
}
if(PID > 1000)
{
  PID=1000;
}


pwmLeft = throttle + PID;
pwmRight = throttle - PID;

if(pwmRight < 1000)
{
  pwmRight= 1000;
}
if(pwmRight > 2000)
{
  pwmRight=2000;
}
if(pwmLeft < 1000)
{
  pwmLeft= 1000;
}
if(pwmLeft > 2000)
{
  pwmLeft=2000;
}
rudder_servo.writeMicroseconds(pwmLeft);
elevator_servo.writeMicroseconds(pwmRight);
previous_error = error;
}
