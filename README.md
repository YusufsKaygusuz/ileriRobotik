# 🤖🦿 İleri Robotik 🤖🦾

<p align="center">
<img src="https://github.com/YusufsKaygusuz/Deneyap_Software_Techn/assets/86704802/cd98b111-b66c-4ddb-b0c4-f62ce0ab8b46" alt="ReLU" width="150"/>
<img src="https://github.com/YusufsKaygusuz/Deneyap_Software_Techn/assets/86704802/7bfa61ee-d340-41b9-8855-dec4c561744f" alt="ReLU" width="200"/> 
<img src="https://github.com/YusufsKaygusuz/Deneyap_Software_Techn/assets/86704802/a4e54abd-9ff4-4d8f-b784-bd0653e9b8f3" alt="ReLU" width="150"/>
<img src="https://github.com/YusufsKaygusuz/Deneyap_Software_Techn/assets/86704802/a90a23b8-0c21-40ee-9617-b17d2858b100" alt="ReLU" width="150"/>
<img src="https://github.com/YusufsKaygusuz/Deneyap_Software_Techn/assets/86704802/705deb43-4977-46c8-8d32-b0c34b4b7b66" alt="ReLU" width="150"/>

</p>


## 📚 İçindekiler
| Hafta | Haftalık İçerik                                               |
|-------|--------------------------------------------------------------|
| 📆 Week 2 | [**LDR Sensörlerinin Analog Çıkışları ile Servo Motor Kontrolü**](#week-2-ldr-sensörlerinin-analog-çıkışları-ile-servo-motor-kontrolü) |
| 📆 Week 3 | [**Mesafe ve IMU Sensörleri ile Servo ve DC Motor Kontrolü**](#week-3-mesafe-ve-imu-sensörleri-ile-servo-ve-dc-motor-kontrolü) |

## Week 2: LDR Sensörlerinin Analog Çıkışları ile Servo Motor Kontrolü

Bu projede, Deneyap Kart üzerinde iki LDR (Light Dependent Resistor) sensörü kullanılmıştır. LDR'ler, ışık miktarına göre direnç değerlerini değiştirirler. Bu yüzden, bir LDR'ye düşen ışık miktarı arttığında veya azaldığında, direnç değeri değişir ve bu değişiklik elektronik devre tarafından algılanabilir.
Deneyap Kart'ın (muhtemelen yerel bir kart) bu kodda temel görevi, iki LDR sensöründen alınan analog değerleri okumak ve bu değerlere göre bir servo motorunu kontrol etmektir.

<h4><b>Projedeki ana fikir şu şekildedir:</b></h4>

İki LDR sensörü arasındaki ışık yoğunluğu farkını ölçmek.
Sağdaki LDR'den gelen değer (sensor1) ile soldaki LDR'den gelen değer (sensor2) arasındaki farka bakarak servo motorunu belirli bir açıyla hareket ettirmek.
Özetle, bu projede LDR sensörlerinin okuduğu ışık değerlerini kullanarak servo motorunu sağa veya sola hareket ettirme amacı vardır.

<img src="https://github.com/YusufsKaygusuz/ileriRobotik/assets/86704802/55cac0a9-2985-4172-8e1f-f0c0107d5f73" alt="ReLU" width="600"/>

```ino
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
```


## Week 3: Mesafe ve IMU Sensörleri ile Servo ve DC Motor Kontrolü

Bu kod, bir 📏 ultrasonik sensörle ölçülen mesafeye göre bir 🌀 servo motorunun hareketini ve bir 🔊 buzzerın durumunu kontrol eden bir sistem için yazılmıştır.

Ultrasonik Sensör: 🌐 Sensör, tetikleme ve yansıma pinleri arasında sinyal göndererek nesnenin sensöre olan uzaklığını ölçer.
Buzzer: 🚨 Mesafe 10 cm'den kısa olduğunda, 🔊 buzzer aktif hale getirilir ve ses çıkarır. 10 cm veya daha fazla olduğunda, buzzer pasif hale gelir.
Servo Motor: 🔄 Uzaklık değerine bağlı olarak, servo motorunun pozisyonu ayarlanır. Maksimum uzaklık değerine göre 180 dereceye kadar hareket edebilir.
Bu kod, sensöre olan uzaklığı ölçmek, bu değere göre bir servo motorunun hareketini kontrol etmek ve belirli bir mesafenin altındaysa bir buzzer'ı etkinleştirmek için kullanılır.

<img src="https://github.com/YusufsKaygusuz/ileriRobotik/assets/86704802/4c706f0e-6c4f-45aa-abb9-39304270dff4" alt="ReLU" width="600"/>

```ino
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
```


```ino
#include <Deneyap_Servo.h>

#define SERVOPIN1 D0       // Servo motor bağlantısı
#define trig_pin D14        // Ultrasonik sensör trigger pin bağlantısı
#define echo_pin D15        // Ultrasonik sensör echo pin bağlantısı
#define buzzer_pin D1       // Zil bağlantısı

Servo myservo;
int pos = 0;
long sure;
long uzaklik;

void setup()
{
    myservo.attach(SERVOPIN1);
    Serial.begin(9600);
    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
    pinMode(buzzer_pin, OUTPUT);
}

void loop()
{
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(5);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);

    sure = pulseIn(echo_pin, HIGH);
    uzaklik = sure / 29.1 / 2;

    Serial.print("Uzaklik: ");
    Serial.print(uzaklik);
    Serial.println(" CM");

    pos = map(uzaklik, 0, 40, 0, 180); // Uzaklık değerini servo açısına dönüştür

    if (uzaklik < 10)
    {
        digitalWrite(buzzer_pin, HIGH);
        delay(500);  // Buzzer'ı yarım saniye boyunca açık tut
        digitalWrite(buzzer_pin, LOW);
    }

    myservo.write(pos);

    delay(1000);  // Örnek bir süre, uygulamanıza göre ayarlayın
}

```
