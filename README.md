# 🤖🦿 İleri Robotik 🤖🦾

<p><strong>İleri Robotik Eğitmeni Yusuf Sami Kaygusuz tarafından oluşturuldu. Paydaşlar: </strong></p>

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
| 📆 Week 5 | [**Çift Joyistik 4 Servo Motor**](#week-5-çift-joyistik-4-servo-motor) |


## Week 2: LDR Sensörlerinin Analog Çıkışları ile Servo Motor Kontrolü

Bu projede, Deneyap Kart üzerinde iki LDR (Light Dependent Resistor) sensörü kullanılmıştır. LDR'ler, ışık miktarına göre direnç değerlerini değiştirirler. Bu yüzden, bir LDR'ye düşen ışık miktarı arttığında veya azaldığında, direnç değeri değişir ve bu değişiklik elektronik devre tarafından algılanabilir.
Deneyap Kart'ın (muhtemelen yerel bir kart) bu kodda temel görevi, iki LDR sensöründen alınan analog değerleri okumak ve bu değerlere göre bir servo motorunu kontrol etmektir.

<h4><b>Projedeki ana fikir şu şekildedir:</b></h4>

İki LDR sensörü arasındaki ışık yoğunluğu farkını ölçmek.
Sağdaki LDR'den gelen değer (sensor1) ile soldaki LDR'den gelen değer (sensor2) arasındaki farka bakarak servo motorunu belirli bir açıyla hareket ettirmek.
Özetle, bu projede LDR sensörlerinin okuduğu ışık değerlerini kullanarak servo motorunu sağa veya sola hareket ettirme amacı vardır.

<p> <img src="https://github.com/YusufsKaygusuz/ileriRobotik/assets/86704802/55cac0a9-2985-4172-8e1f-f0c0107d5f73" alt="ReLU" width="600"/> </p>
<p></p>

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

<p> Bu kod, iki servo motorunun hareketini analog sensörler (X ve Y değerleri) 🕹️ aracılığıyla takip eder ve bu sensör değerlerine bağlı olarak servo motorların pozisyonunu 🔄 günceller. Aynı zamanda, bir anahtarın (SW_pin) 🎛️ durumunu izler; eğer anahtar aktifse, servo motorların hareket sürelerini dinamik olarak değiştirerek farklı hızlarda hareket etmelerini sağlar. Bu sayede, sistemin tepkisini ve çalışma süresini kullanıcının kontrolüne bırakır 🎮. </p>

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
Bu kod, LSM6DSM IMU sensöründen okunan verilere 📊 göre iki servo motorunun 🤖 dinamik olarak ayarlar. IMU sensöründen alınan ivme verileri 📏 kullanılarak x ve y eksenlerindeki açısal pozisyonlar 📐 hesaplanır ve bu pozisyonlara göre servo motorların 🎛️ pozisyonları güncellenir. Bu, örneğin bir dengeleme sistemi 🏗️ veya bir robotik uygulama için kullanılabilir. 🤹‍♂️

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

## Week 5: Çift Joyistik 4 Servo Motor

<h3>Motor Sürücü ile Uygulama</h3>

L298N motor sürücü entegresi dijital sinyaller ile çalışan ve röle, motor gibi endüktif yükleri kontrol edebilen 4 ampere kadar akım verebilen bir motor sürücü entegresidir. Bu entegre ile 2 adet motor sürülebilmektedir. L298 sürücü kartı incelendiğinde üzerinde çeşitli giriş ve çıkışlar bulunmaktadır. Bu giriş çıkışlar aşağıdaki tabloda verilmiştir.

<img src="https://github.com/YusufsKaygusuz/ileriRobotik/assets/86704802/2d8560f8-b171-4f88-a720-acf4e5b4cbce" alt="ReLU" width="600"/>

```ino
#include "lsm6dsm.h"
#define MOT_ENA D12
#define MOT_DIR1 D13
#define MOT_DIR2 D14
float angle_x=0.;
int hiz=0;
LSM6DSM IMU;

void setup() {
IMU.begin();
pinMode(MOT_ENA, OUTPUT); // Motor hız kontrol pini cikis olarak ayarlandi
pinMode(MOT_DIR1, OUTPUT); // Motor yon secme pin1 cikis olarak ayarlandi
pinMode(MOT_DIR2, OUTPUT); // Motor yon secme pin2 cikis olarak ayarlandi
}

void loop() {
//açı hesaplama denklemi (sqrt: karekök alma işlemi, pow: üs alma işlemi, PI: pi (π) sayısı)
angle_x = atan(IMU.readFloatAccelX() / sqrt(pow(IMU.readFloatAccelY(), 2) + pow(IMU.readFloatAccelZ(), 2)+0.001)) * 180 / PI;
hiz= abs(angle_x);
if(angle_x > 0) // Ileri yon
{
digitalWrite(MOT_DIR1, HIGH);
digitalWrite(MOT_DIR2, LOW);
}
else if(angle_x < 0) // Geri yon {
digitalWrite(MOT_DIR1, LOW);
digitalWrite(MOT_DIR2, HIGH);
}
digitalWrite(MOT_ENA, LOW);
delay(100/hiz);
digitalWrite(MOT_ENA, HIGH);
delay(100/hiz);
}
```

<h3>3 Işık Sensörü ile Uygulama</h3>

Program Deneyap Geliştirme Kartına yüklendiğinde motorların ışık sensörleri ve potansiyometre aktivitelerine göre davranış gösterdiği görülecektir. Şekilde de görüldüğü gibi sistemharicibirbataryaileçalıştırılıptestedilebilir. Sistemitestederkenbirelfeneriyadabir cep telefonunun flaş ışığı kullanılabilir. Sistemin davranışı (motorların ışığa karşı reaksiyonu) devredeki potansiyometre ile kalibre edilebilir.

<img src="https://github.com/YusufsKaygusuz/ileriRobotik/assets/86704802/1497de6e-30f2-4f40-a129-e73a3e9a1f41" alt="ReLU" width="600"/>
<img src="https://github.com/YusufsKaygusuz/ileriRobotik/assets/86704802/7bfceba2-cfce-461d-912a-81ae014a7b57" alt="ReLU" width="600"/>

```ino
#include <Deneyap_Servo.h>
#define SERVOPIN1 D9
#define SERVOPIN2 D14
#define L1_pin A0
#define L2_pin A1
#define L3_pin A2
#define Pot_pin A3
int teta1min=0;
int teta1max=180;
int teta2min=0;
int teta2max=180;
int accAngleX=0;
int accAngleY=0;
int conavail=0;
int coef, valin1, valin2, valin3; int pos1 = 0;
int pos2 = 0;
int clb1=0;
int clb2=0;
int clb3=0;
int i=0;
int n=10; 
int32_t tot1=0.;
int32_t tot2=0.;
int32_t tot3=0.;
Servo myservo1, myservo2;

void setup() 
{
myservo1.attach(SERVOPIN1);
myservo2.attach(SERVOPIN2,1);
}

void loop()
{
coef = analogRead(Pot_pin);
valin1 = 4095-analogRead(L1_pin);
valin2 = 4095-analogRead(L2_pin);
valin3 = 4095-analogRead(L3_pin);
if (i<n) { 
i++;
}
tot1=int(((i-1)*tot1+valin1)/i);
tot2=int(((i-1)*tot2+valin2)/i);
tot3=int(((i-1)*tot3+valin3)/i);
pos1=90+(tot2-tot1)*((2048-coef)/2048.);
pos2=120+(0.5*(tot1+tot2)-tot3)*((2048-coef)/2048.);
myservo1.write(pos1);
myservo2.write(pos2);
delay(5); 
}
```
<h3>2 Joyistik 4 Servo </h3>

Birinci kumanda kolu (soldaki) sağa sola hareket ettirildiğinde, taban servo motoru dönme hareketini gerçekleştirecektir. Birinci kumanda kolu ileri geri hareket ettirildiğinde ise iki numaralı servo motor hareket edecektir. İkinci kumanda kolu, ileri geri hareket ettirildiğinde, 3 numaralı servo motor dönme hareketini gerçekleştirecektir. İkinci kumanda kolu sağa sola hareket ettirildiğinde ise tutucu el kapanıp açılacaktır.
Birinci kumanda kolunun butonuna tek tıklama yapıldığında, o anki servo motor konumları hafızaya alınır (öğrenme modu). Bu her tekrarlandığında değişmiş her konum sıralı hafızaya alınır. 
<img src="https://github.com/YusufsKaygusuz/ileriRobotik/assets/86704802/cd1d30b1-b205-4106-9203-e916e1c20a8a" alt="ReLU" width="600"/>
Birinci kumanda kolunun butonuna çift klik yapıldığında, robot hafızadaki hareketleri sürekliolaraktekrarlayacaktır(oynatmamodu). Aynıkumandakolununbutonunatekrartekklik yapıldığında da robot yavaşlayıp duracaktır. Herhangi bir yeni konum bilgisi hafızaya girildiği anda önceki konum bilgilerinin hepsi silinmektedir. Eğer yeni konum bilgisi girilmez ve tekrardan birinci kumanda kolu butonuna çift klik yapılırsa robot hafızasındaki konum bilgilerine uygun olarak hareketleri sürekli tekrarlayacaktır.
Robotun hız kontrolü, ikinci kumanda kolu butonuna tek tıklama yapılması suretiyle gerçekleştirilmektedir. Her tıklamada eklem hızları değişecektir. Yavaş, normal ve hızlı olmak üzere üç hız modu bulunmaktadır. Robot öğrenme veya oynatma modlarında iken ikinci kumanda kolunun butonuna tek tıklama yapıldığında, bir hız modundan diğerine geçilebilmektedir.

```ino
#include "deneyap.h"
#include <Deneyap_Servo.h>// Eğer bu kütüphane çalışmaz ise <ESP32Servo.h> kütüphanesi denenebilir.
#define SW1_pin D0
#define SW2_pin D1
#define X1_pin A0
#define Y1_pin A1
#define X2_pin A2
#define Y2_pin A3
#define SERVOPIN1 D9
#define SERVOPIN2 D12
#define SERVOPIN3 D13
#define SERVOPIN4 D14

//Aşağıdaki teta değerleri 0-3000 arasında kalibre edilmiştir. 3000 değeri 180 dereceye
karşılık gelmektedir.
int teta1min=0;
int teta1max=3000;

int teta2min=0;
int teta2max=3000;
int teta3min=0;
int teta3max=3000;
int teta4min=1500;
int teta4max=2000;
int valin1, valin2, valin3, valin4;
int valcalc1=1500; //Başlangıç açı değerleri
int valcalc2=1500;
int valcalc3=1500;
int valcalc4=2000;
int jystp=20;
bool playmode=false;
int ButtonMode=0;
unsigned long CurrentMilliSec = millis();
long PreMilliSec=0;
int NumMemory=0;
int PreNumMemory=0;
int Step=-1;
int joint1[50];
int joint2[50];
int joint3[50];
int joint4[50];
int maxarray=49;
int prehiz=10;
int normalhiz=10;
// hiz=1 çok yavaş, 5 yavaş, 10 normal, 15 hızlı, 20+ çok hızlı int hiz=10;
int prepos1, prepos2, prepos3, prepos4;
int pos11,pos21,pos31,pos41;
Servo myservo1, myservo2, myservo3, myservo4;

void setup()
{
myservo1.attach(SERVOPIN1); //Eğer <ESP32Servo.h> kütüphanesi kullanırsanız, bu ve aşağıdaki 3 satırda parantez içerisindeki 2’inci parametreyi silin, tek parametre yeterlidir.
myservo2.attach(SERVOPIN2,1);
myservo3.attach(SERVOPIN3,2);
myservo4.attach(SERVOPIN4,3);
pinMode(SW1_pin, INPUT_PULLUP);
pinMode(SW2_pin, INPUT_PULLUP);
pinMode(X1_pin, INPUT);
pinMode(Y1_pin, INPUT);

pinMode(X2_pin, INPUT);
pinMode(Y2_pin, INPUT);
digitalWrite(SW1_pin, HIGH);
digitalWrite(SW2_pin, HIGH); Serial.begin(115200); Serial.println("Ready.");
}

void loop()
{
CurrentMilliSec = millis();
Button();
if (playmode==false && Step==-1){
ReadAnalog();
myservo1.writeMicroseconds(valcalc1);
myservo2.writeMicroseconds(valcalc2);
myservo3.writeMicroseconds(valcalc3);
myservo4.writeMicroseconds(valcalc4);
delay(int(300./hiz));
}
else{
playit();
}
}


void ReadAnalog() {
valin1 = analogRead(Y1_pin);
valin2 = analogRead(X1_pin);
valin3 = analogRead(X2_pin);
valin4 = analogRead(Y2_pin);
if (valin1<1000 && valcalc1>teta1min)
valcalc1-=jystp;
if (valin1>3000 && valcalc1<teta1max)
valcalc1+=jystp;
if (valin2<1000 && valcalc2>teta2min)
valcalc2+=jystp;
if (valin2>3000 && valcalc2<teta2max)
valcalc2-=jystp;
if (valin3<1000 && valcalc3>teta3min) valcalc3-=jystp;
if (valin3>3000 && valcalc3<teta3max) valcalc3+=jystp;
if (valin4<1000 && valcalc4>teta4min) valcalc4-=jystp;
if (valin4>3000 && valcalc4<teta4max) valcalc4+=jystp;
}

void Button() {
if (playmode==false){
if (digitalRead(SW1_pin) == 0){
delay(100);
if (digitalRead(SW1_pin) == 1) {
if (ButtonMode == 0) {
ButtonMode = 1;
PreMilliSec = CurrentMilliSec;
}
else if ((ButtonMode == 1) && (CurrentMilliSec - PreMilliSec < 500)) {
ButtonMode = 2; }
} }
if ((ButtonMode == 1) && (CurrentMilliSec - PreMilliSec > 600)) { saveit();
NumMemory += 1;
if (NumMemory>maxarray) NumMemory= maxarray; ButtonMode = 0;
Serial.print("Saved: "); Serial.println(NumMemory);
}
else if (ButtonMode == 2 && (CurrentMilliSec - PreMilliSec > 600)) {
if ((NumMemory>1 || PreNumMemory>1) && playmode==false){ Serial.println("Playmode...");
playmode = true;
ButtonMode = 0;
if (NumMemory<2) NumMemory=PreNumMemory; else PreNumMemory=NumMemory;
joint1[0]=pos11; joint2[0]=pos21; joint3[0]=pos31; joint4[0]=pos41;
Step=NumMemory-1; ReadAnalog(); prepos1=valcalc1; prepos2=valcalc2; prepos3=valcalc3; prepos4=valcalc4;
} }
if (ButtonMode<3 && CurrentMilliSec - PreMilliSec > 1000) {
ButtonMode = 0; }
}
else if (ButtonMode<3 && digitalRead(SW1_pin) == 0) {
ButtonMode = 3; Serial.println("Stopping."); ReadAnalog();
NumMemory+=1; joint1[NumMemory-1] = valcalc1; joint2[NumMemory-1] = valcalc2; joint3[NumMemory-1] = valcalc3; joint4[NumMemory-1] = valcalc4;
}
if (digitalRead(SW2_pin) == 0) { if (prehiz==hiz) {
if (hiz==normalhiz) { hiz=2*normalhiz;
jystp=40; Serial.println("High speed."); if (playmode==false) {
delay(300); }
}else{
if (hiz==(2*normalhiz)) {
hiz=normalhiz/2;
jystp=10; Serial.println("Low speed."); if (playmode==false) {
delay(300); }
}
else if (hiz==(normalhiz/2)) {
hiz=normalhiz;
jystp=20; Serial.println("Normal speed."); if (playmode==false) {
delay(300); }
} }
} }
else{ prehiz=hiz;
} }

void saveit() { joint1[NumMemory] = valcalc1; joint2[NumMemory] = valcalc2; joint3[NumMemory] = valcalc3; joint4[NumMemory] = valcalc4;
prepos1=valcalc1; prepos2=valcalc2; prepos3=valcalc3; prepos4=valcalc4;
if (NumMemory==1){ pos11=joint1[0]; pos21=joint2[0]; pos31=joint3[0]; pos41=joint4[0];
} }

void playit() {
float pos1=prepos1; float pos2=prepos2; float pos3=prepos3; float pos4=prepos4;
float dif1=abs(joint1[Step]-pos1); float dif2=abs(joint2[Step]-pos2); float dif3=abs(joint3[Step]-pos3); float dif4=abs(joint4[Step]-pos4); float maxdif=0.0;
if (dif1>maxdif) maxdif=dif1; if (dif2>maxdif) maxdif=dif2; if (dif3>maxdif) maxdif=dif3; if (dif4>maxdif) maxdif=dif4; maxdif=maxdif/hiz;
if (maxdif<1.0) maxdif=1.0;
float stp1=(joint1[Step]-pos1)/maxdif; float stp2=(joint2[Step]-pos2)/maxdif; float stp3=(joint3[Step]-pos3)/maxdif;

float stp4=(joint4[Step]-pos4)/maxdif; for (int i=1;i<=int(maxdif);i++){
pos1=pos1+stp1; pos2=pos2+stp2; pos3=pos3+stp3; pos4=pos4+stp4; if (i==int(maxdif)){
pos1=joint1[Step]; pos2=joint2[Step]; pos3=joint3[Step]; pos4=joint4[Step];
}
myservo1.writeMicroseconds(int(pos1)); myservo2.writeMicroseconds(int(pos2)); myservo3.writeMicroseconds(int(pos3)); myservo4.writeMicroseconds(int(pos4));
prepos1=pos1; prepos2=pos2; prepos3=pos3; prepos4=pos4; delay(10);
if (ButtonMode<3) Button();
else delay(5); }
if (ButtonMode==3 && Step==NumMemory-1) { NumMemory = 0;
Step=-1;
ButtonMode = 0;
playmode=false;
Serial.println("Stopped."); }
else{
Step+=1;
if (Step>NumMemory-1) Step=0;
} }


```




<h3>Bluwtooth ile Motor Kontrolü </h3>

```ino
#include "deneyap.h"
#include "BluetoothSerial.h"

char gelen;
BluetootSerial SerailBT;

void setup() {
  SerailBT.begin("DeneyapKart");
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);
}

void loop() {
  if(SerailBT.available()){
    gelen = SerailBT.read(){
      if(gelen == 'F'){
        digitalWrite(D0, HIGH);
        digitalWrite(D1, LOW);
        digitalWrite(D8, HIGH);
        digitalWrite(D9, LOW);
      }
      else if (gelen == 'L'){
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D8, HIGH);
        digitalWrite(D9, LOW);
      }
      else if (gelen ='R'){
        digitalWrite(D0, HIGH);
        digitalWrite(D1, LOW);
        digitalWrite(D8, LOW);
        digitalWrite(D9, LOW);
      }
      else {
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D8, LOW);
        digitalWrite(D9, LOW);
      }
    }
  }
}
```

