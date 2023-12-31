#include <Deneyap_Servo.h>
#define SERVOPIN1 D0 // servo motor bağlantısı
#define trig_pin D14 // ultrasonik sensör trigger pin bağlantısı
#define echo_pin D15 // ultrasonik sensör echo pin bağlantısı
#define buzzer_pin D1 // zil bağlantısı

Servo myservo;
int pos=0;
long sure;
long uzaklik;

void setup()
{
    myservo.attach(SERVOPIN1);
    Serial.begin(115200); // serial monitör üzerinde uzaklık değerini görmek için
    pinMode(trig_pin, OUTPUT); // ultrasonik sensör trigger pinini çıkış olarak ayarlıyoruz
    pinMode(echo_pin,INPUT);   // ultrasonik sensör echo pinini giriş olarak ayarlıyoruz
    pinMode(buzzer_pin,OUTPUT); //zil pinini çıkış olarak ayarlıyoruz
}
void loop()
{
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(5);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);
//gönderilen sinyalin echo pinine geliş süresinin tespiti
sure = pulseIn(echo_pin, HIGH);
//ses hızına göre uzaklığın hesaplanması (gidiş geliş olduğu için 2’ye bölünmektedir.) 
uzaklik = sure /29.1/2;

if(uzaklik < 10) //uzaklık değeri 10 cm’den küçükse zil aktif
digitalWrite(buzzer_pin, HIGH);
if(uzaklik >= 10) //uzaklık değeri 10 cm’den büyükse zil pasif
digitalWrite(buzzer_pin, LOW);

Serial.print("Uzaklık: ", uzaklik); //uzaklık değeri serial monitör ekranına yazdırılıyor.
Serial.print(" CM");


pos=uzaklik*(180/40);
myservo.write(pos); //uzaklık değerine göre (max. 40 cm) ibrenin hareketinin sağlanması

delay(5);
}


