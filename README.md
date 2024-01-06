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
| 📆 Week 4 | [**Çift Servo ve Joyistik ile Motor Kontrol**](#week-4-çift-servo-ve-joyistik-ile-motor-kontrol) |

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
#include <Deneyap_Servo.h> // Servo motor kütüphanesinin programa eklenmesi

#define trig_pin D14       // Ultrasonik sensör trigger pin bağlantısı
#define echo_pin D15       // Ultrasonik sensör echo pin bağlantısı
#define buzzer_pin D1      // Zil bağlantısı
#define servo_pin D0       // Servo motor bağlantısı

Servo myservo;
int buzzer_threshold = 10;  // Uzaklık değeri bu değerin altındaysa buzzer'ı aktif et

void setup()
{
    Serial.begin(9600);
    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
    pinMode(buzzer_pin, OUTPUT);
    myservo.attach(servo_pin);
}

void loop()
{
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(5);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);

    // Gelen sinyalin echo pinine geliş süresinin tespiti
    long sure = pulseIn(echo_pin, HIGH);

    // Ses hızına göre uzaklığın hesaplanması (gidiş-geliş olduğu için 2’ye bölünmektedir.)
    long uzaklik = sure / 29.1 / 2;

    Serial.print("Uzaklik: ");
    Serial.print(uzaklik);
    Serial.println(" CM");
    delay(50);

    // Belirli bir uzaklık altında ise buzzer'ı aktif et
    if (uzaklik < buzzer_threshold) {
        digitalWrite(buzzer_pin, HIGH);
    } else {
        digitalWrite(buzzer_pin, LOW);
    }

    // Uzaklık değerine göre servo motoru kontrol et
    int servo_position = map(uzaklik, 0, 40, 0, 180);
    myservo.write(servo_position);

    delay(50);  // İhtiyaca göre ayarlayın
}

```

## Week 4: Çift Servo ve Joyistik ile Motor Kontrol
Uygulama için gerekli Deneyap Geliştirme Kartı, servo motor ve kumanda kolu bağlantıları öncesi joyistik kontrolü denenmelidir.

<h3>Joyistik Kontrolü için Kod</h3>

<img src="https://github.com/YusufsKaygusuz/ileriRobotik/assets/86704802/2853372c-685f-49af-a4a8-ebb34b402d1a" alt="ReLU" width="600"/>

```ino
#include "deneyap.h"
#define SW_pin D0
#define X_pin A0
#define Y_pin A1

int X_Val, Y_Val, Dig_Val;

void setup () {
Serial.begin(115200);
pinMode(SW_pin, INPUT_PULLUP);
digitalWrite(SW_pin, HIGH);
pinMode(X_pin, INPUT);
pinMode(Y_pin, INPUT);
}

void loop () {
X_Val = analogRead(X_pin);
Y_Val = analogRead(Y_pin);
Dig_Val =digitalRead(SW_pin);
Serial.print("X_Val: ");
Serial.println(X_Val);
Serial.print("Y_Val: ");
Serial.println(Y_Val);
Serial.print("Dig_Val: ");
Serial.println(Dig_Val);
delay(100);
}
```

<h3>Çift Servo Kullanım Pratiği </h3>
<img src="https://github.com/YusufsKaygusuz/ileriRobotik/assets/86704802/deb530e1-40ff-41bc-8ba4-59f34800db08" alt="ReLU" width="600"/>

```ino
#include <Deneyap_Servo.h>
#define SERVOPIN1 D14
#define SERVOPIN2 D9

Servo myservo1, myservo2;
int pos=0;

void setup() {
myservo1.attach(SERVOPIN1);
myservo2.attach(SERVOPIN2,1);
}

void loop() {

for(pos=0;pos<=180;pos+=1)
{ myservo1.write(pos);
myservo2.write(pos);
delay (10);
 }
for(pos=180;pos>=0;pos-=1){
myservo1.write(pos);
myservo2.write(pos);
delay (10);
}
}
```


<h3> Uygulama Projesi </h3>
<img src="https://github.com/YusufsKaygusuz/ileriRobotik/assets/86704802/9923107e-d3d9-4c8a-9ec4-d7540b423df4" alt="ReLU" width="600"/>

<p> Bu kod, iki servo motorunun hareketini analog sensörler (X ve Y değerleri) aracılığıyla takip eder ve bu sensör değerlerine bağlı olarak servo motorların pozisyonunu günceller. Aynı zamanda, bir anahtarın (SW_pin) durumunu izler; eğer anahtar aktifse, servo motorların hareket sürelerini dinamik olarak değiştirerek farklı hızlarda hareket etmelerini sağlar. Bu sayede, sistemin tepkisini ve çalışma süresini kullanıcının kontrolüne bırakır. </p>

<h3>Kodlar</h3>

```ino
#include "deneyap.h"
#include <Deneyap_Servo.h>
#define SERVOPIN1 D14
#define SERVOPIN2 D9
#define SW_pin D0
#define X_pin A0
#define Y_pin A1


Servo myservo1, myservo2;
int X_Val, Y_Val;
int pos1=0, pos2=0;
int dly = 10; intstp=1;
int Dig_Val = 0;
int teta1min=0;
int teta1max=180;
int teta2min=0;
int teta2max=180;

void setup() {
myservo1.attach(SERVOPIN1);
myservo2.attach(SERVOPIN2,1);
pinMode(SW_pin, INPUT_PULLUP);
digitalWrite(SW_pin, HIGH);
pinMode(X_pin, INPUT);
pinMode(Y_pin, INPUT);
}

void loop() {
X_Val = analogRead(X_pin);
Y_Val = analogRead(Y_pin);
Dig_Val = digitalRead(SW_pin);
if (Dig_Val<1) {
if (dly==5)
dly=10;
else {
if(dly==10)
dly=20;
else if(dly==20)
dly=5;
}
delay (500);
}
if (X_Val<1000 && pos1>teta1min)
pos1-=stp;

if (X_Val>3000 && pos1<teta1max)
pos1+=stp;
if (Y_Val<1000 && pos2>teta2min)
pos2-=stp;
if (Y_Val>3000 && pos2<teta2max)
pos2+=stp;
myservo1.write(pos1);
myservo2.write(pos2);
delay (dly);
}
```

<h3>IMU Sensörü ile Çift Servo Motor Konum Kontrolü</h3>
<img src="https://github.com/YusufsKaygusuz/ileriRobotik/assets/86704802/fdd21e1c-9c13-4792-95ea-8068a023df7a" alt="ReLU" width="600"/>

```ino 
#include <Deneyap_Servo.h>
#include "lsm6dsm.h"
#define SERVOPIN1 D14
#define SERVOPIN2 D9
LSM6DSM IMU;
Servo myservo1;
Servo myservo2;
float accAngleX=0.;
float accAngleY=0.;
int pos1 = 90;
int pos2 = 90;

void setup() {
IMU.begin();
myservo1.attach(SERVOPIN1);
myservo2.attach(SERVOPIN2,1);
}
void loop()
{
accAngleX = atan(IMU.readFloatAccelX() / sqrt(pow(IMU.readFloatAccelY(), 2) +
pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI;

accAngleY = atan(-1 * IMU.readFloatAccelY() / sqrt(pow(IMU.readFloatAccelX(), 2) +
pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI; pos1=90+int(accAngleX);

pos2=90+int(accAngleY);
myservo1.write(pos1);
myservo2.write(pos2); delay(10);
}

```



