#include<Servo.h>

Servo servoR;//actually the servo motor
Servo servo2;//actually the servo-R motor
int ang = 30;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  servoR.attach(2);//GPIO PIN 4
servo2.attach(4);//GPIO PIN 2
pinMode(5,INPUT);//GPIO PIN 1

}

void hit(int n){
// hit the object at angle n.
//servo2.writeMicroseconds(stand);
  int p=servoR.read();
  //make the moving to desired angular position smoothly.
  //by increment 1 degree a time. 
  while(p<=n){
    //servo2.writeMicroseconds(stand);//make servo-R motor not moving. 
    servoR.write(p);
    //servo2.writeMicroseconds(stand);
    delay(1);
    p++;
  }
  while(p>n){
    //servo2.writeMicroseconds(stand);
    servoR.write(p);
    //servo2.writeMicroseconds(stand);
    delay(1);
    p--;
  }
  delay(50);
  int a = 0;
  while (a<45){
    servo2.write(a);
    a++;
    delay(1);
  }
  delay(50);
  while(a>0){
    servo2.write(a);
    a--;
    delay(1);
  }
  delay(35);
  //servo2.writeMicroseconds(stand);
}

void loop() {
  // put your main code here, to run repeatedly:
 if (digitalRead(5)==HIGH){
    delay(100);
    hit(ang);
    if(ang<60){
      ang = ang +30;
    }
    else 
    {
      ang = ang -30;
   }
   delay(50);
} 
}
