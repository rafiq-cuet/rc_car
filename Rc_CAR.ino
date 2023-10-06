#include "BluetoothSerial.h"
#include <Arduino.h>

BluetoothSerial serialBT;

//Bluetooth signal Store in this variable
char btSignal;

//initial Speed of the Bot
int Speed = 100;

/*FOR RIGHT MOTOR*/
int RPWM = 5;

/*FOR LEFT MOTOR*/
int LPWM = 23;


//declare channel for pwm Output
#define R 0
#define L 1

//Define in1/in2/in3/in4 pin
int IN1 = 18;
int IN2 = 19;
int IN3 = 21;
int IN4 = 22;

void setup() {
  Serial.begin(115200);

  //Bluetooth Name
  serialBT.begin("CUBIT");

  //output pin declare
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);

  // Setup PWM channels
  ledcSetup(R, 5000, 8);  // Channel 0 for Motor A, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(RPWM, R);
  ledcSetup(L, 5000, 8);  // Channel 0 for Motor A, 5 kHz frequency, 8-bit resolution
  ledcAttachPin(LPWM, L);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {

  while (serialBT.available()) {
    btSignal = serialBT.read();
    //Serial.println(btSignal);

    if (btSignal == '0') Speed = 100;
    if (btSignal == '1') Speed = 110;
    if (btSignal == '2') Speed = 120;
    if (btSignal == '3') Speed = 130;
    if (btSignal == '4') Speed = 140;
    if (btSignal == '5') Speed = 150;
    if (btSignal == '6') Speed = 180;
    if (btSignal == '7') Speed = 200;
    if (btSignal == '8') Speed = 220;
    if (btSignal == '9') Speed = 240;
    if (btSignal == 'q') Speed = 255;

    if (btSignal == 'F')  //forward
    {
      ledcWrite(R, Speed);
      ledcWrite(L, Speed);

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);

      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

    }

    else if (btSignal == 'B')  //backward
    {
      ledcWrite(R, Speed);
      ledcWrite(L, Speed);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

    }

    else if (btSignal == 'L')  //LEFT
    {

      ledcWrite(R, Speed);
      ledcWrite(L, Speed);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }

    else if (btSignal == 'R')  //RIGHT
    {
      ledcWrite(R, Speed);
      ledcWrite(L, Speed);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }

    else if (btSignal == 'S')  //STOP
    {
      ledcWrite(R, Speed);
      ledcWrite(L, Speed);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);

      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
  }
}