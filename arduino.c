#include <TLE94112.h>
#include <TLE94112_Motor.h>
//#include <Servo.h>

#define servo1 7
#define servo2 8
#define LED_1 26
#define down 0
#define up 30 

//Servo myservo;

// The TLE94112 has only got 3 PWM channels
// There is no one left for motor4
// This means, we cannot control its speed
Tle94112Motor motor1(tle94112, tle94112.TLE_PWM1);
Tle94112Motor motor2(tle94112, tle94112.TLE_PWM3);
//Tle94112Motor motor3(tle94112, tle94112.TLE_PWM3);
//Tle94112Motor motor4(tle94112, tle94112.TLE_NOPWM);


void setup()
{
  //シリアル通信
  //Serial.begin(9600);//シリアル通信のレートを9600に設定
  
  //サーボ初期化
//  myservo.attach(servo1);
//  myservo.attach(servo2);
  
  //モーター初期化
  // call begin for the TLE94112 firs
  tle94112.begin();
  // motor1 is connected to 2 halfbridges on each side
  motor1.connect(tle94112.TLE_HB1, motor1.HIGHSIDE);
  motor1.connect(tle94112.TLE_HB2, motor1.HIGHSIDE);
  motor1.connect(tle94112.TLE_HB3, motor1.LOWSIDE);
  motor1.connect(tle94112.TLE_HB4, motor1.LOWSIDE);

  // motor2 is connected to 1 halfbridge on each side
  motor2.connect(tle94112.TLE_HB7, motor2.HIGHSIDE);
  motor2.connect(tle94112.TLE_HB8, motor2.LOWSIDE);

  //change the motors PWM frequency (just in case you will ever need it...)
  motor1.setPwmFreq(tle94112.TLE_FREQ200HZ);
  motor2.setPwmFreq(tle94112.TLE_FREQ200HZ);

  //when configuration is done, call begin to start operating the motors
  motor1.begin();
  motor2.begin();
  //after calling begin(), the motors are coasting. 
  
}

void go(int delay_time,int machine_speed){
  motor1.start(machine_speed);
  motor2.start(machine_speed);
  delay(delay_time);
  motor1.stop(255);
  motor2.stop(255);
  }

void senkai(int delay_time,int machine_speed){
  motor1.start(machine_speed/2);
  motor2.start(-machine_speed/2);
  delay(delay_time);
  motor1.stop(255);
  motor2.stop(255);
  }

void magaru(int delay_time,int speed_left,int speed_right){
  motor1.start(speed_left);
  motor2.start(speed_right);
  delay(delay_time);
  motor1.stop(255);
  motor2.stop(255);
  }

void write_J(){
//J 1画目
  //myservo.write(down);
  go(2000,196);
  delay(1000);

//J 2画目の開始位置へ
  //myservo.write(up);
  go(1000,-196);
  delay(1000);
  senkai(250,128);
  delay(1000);

//J 2画目
  //myservo.write(down);
  go(1000,196);
  delay(1000);
  magaru(2000,196,128);
  delay(1000);

//次の文字位置へ移動
  //myservo.write(up);
  go(1000,196);
  delay(1000);
  senkai(250,128);
  delay(1000);
  go (1500,196);
  delay(1000);
  }

void write_P(){
//P開始方向に回転
  senkai(250,128);
  delay(1000);
//P 1画目
  //myservo.write(down);
  go(2000,196);
  delay(1000);
//P 2画目開始位置へ移動
  //myservo.write(up)
  go(2000,-196);
  delay(1000);
//P 2画目
  //myservo(down);
  go(500,196);
  delay(1000);
  magaru(2000,196,128);
  delay(1000);
  go(500,196);
  delay(1000);
//次の位置へ移動
  //myservo.write(up);
  senkai(250,128);
  delay(1000);
  go(1000,196);
  delay(1000);
  senkai(250,128);
  delay(1000);
  go(1250,196);
  delay(1000);
  }

void loop()
{
  //
  //inputchar = Serial.read();  //シリアル通信で送信された値を読み取る
    write_J();
    write_P();
    //if(inputchar!=-1){
    //switch(inputchar){
    //  case 'j':
    //    digitalWrite(LED_1,HIGH);  
    //    write_J();
    //    break;

    //  case 'p':
    //    digitalWrite(LED_1,LOW);
    //    write_P();
    //    break;
   // }
  //}
  //else{
  //}
  
}