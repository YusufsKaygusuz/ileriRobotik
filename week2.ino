#include <Deneyap_Servo.h> // Servo motor kütüphanesinin programa eklenmesi

#define SERVOPIN D0 // servo motorun bağlandığı D0 pininin tanımlaması
#define L1_pin A0 // sağ ışık sensörünün bağlandığı D14 pininin tanımlaması
#define L2_pin A1 // sol ışık sensörünün bağlandığı D15 pininin tanımlaması


Servo myservo; //servo motora ilişkin değişken tanımlaması
int sensor1, sensor2; //LDR’lerin değişkenlerinin tanımlanması
int pos=0; //servo motor pozisyonuna ilişkin değişken tanımlaması

void setup() 
{
    myservo.attach(SERVOPIN);
    pinMode(L1_pin, INPUT);
    pinMode(L2_pin, INPUT);
}

void loop() {

sensor1 = (4095-analogRead(L1_pin))*90/4095; // sağ ışık sensöründen gelen dijital verinin okunması
sensor2 = (4095-analogRead(L2_pin))*90/4095; // sol ışık sensöründen gelen dijital verinin okunması

// LDRlere düşen ışık miktarı farkına göre konum belirlenir.
if (sensor1 > sensor2)
{
pos=(sensor1-sensor2)+90; 
myservo.write(pos);
}
else if(sensor2>sensor1)
{
pos=-1*(sensor2-sensor1)+90;
myservo.write(pos);
}
delay(5);
}