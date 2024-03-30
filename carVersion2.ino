#include "BluetoothSerial.h"
#include <Deneyap_Servo.h>

// Tanımlamalar
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
BluetoothSerial SerialBT;

#define MOT_DIR1  D9
#define MOT_DIR2  D1
#define MOT_DIR3  D14
#define MOT_DIR4  D13
#define ENA  D12
#define ENB  D8

int servo1_pin = D0;
int servo2_pin = D4;
int servo3_pin = D15;
int servo4_pin = A4;
int servo5_pin = A5;

// Motor kontrol sınıfı tanımı
class MotorController {
public:
  MotorController() {
    // Motor pinleri için pin modları ayarlanıyor
    pinMode(MOT_DIR1, OUTPUT);
    pinMode(MOT_DIR2, OUTPUT);
    pinMode(MOT_DIR3, OUTPUT);
    pinMode(MOT_DIR4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    stop(); // Başlangıçta motorlar durduruluyor
  }

  // İleri git metodu
  void moveForward() {
    digitalWrite(MOT_DIR1, HIGH);
    digitalWrite(MOT_DIR2, LOW);
    digitalWrite(MOT_DIR3, HIGH);
    digitalWrite(MOT_DIR4, LOW);
    setSpeed(true); // Hız ayarı yapılıyor
  }

  // Sola dön metodu
  void moveLeft() {
    digitalWrite(MOT_DIR1, HIGH);
    digitalWrite(MOT_DIR2, HIGH);
    digitalWrite(MOT_DIR3, HIGH);
    digitalWrite(MOT_DIR4, LOW);
    digitalWrite(ENA, LOW);
    digitalWrite(ENA, HIGH);
  }

  // Sağa dön metodu
  void moveRight() {
    digitalWrite(MOT_DIR1, HIGH);
    digitalWrite(MOT_DIR2, LOW);
    digitalWrite(MOT_DIR3, LOW);
    digitalWrite(MOT_DIR4, LOW);
    setSpeed(true); // Hız ayarı yapılıyor
  }

  // Dur metodu
  void stop() {
    digitalWrite(MOT_DIR1, LOW);
    digitalWrite(MOT_DIR2, LOW);
    digitalWrite(MOT_DIR3, LOW);
    digitalWrite(MOT_DIR4, LOW);
    setSpeed(false); // Hız sıfırlanıyor
  }

private:
  // Hız ayarı metodu
  void setSpeed(bool enable) {
    digitalWrite(ENA, enable ? HIGH : LOW);
    digitalWrite(ENB, enable ? HIGH : LOW);
  }
};

MotorController motorController; // Motor kontrolcüsü objesi oluşturuluyor

void setup() {
  // Serial port başlatılıyor
  Serial.begin(115200);
  SerialBT.begin("DeneyapKart");
  SerialBT.println("\nDeneyapKart'a bağlanıldı.");
  
  // Servo pinleri ayarlanıyor
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  servo3.attach(servo3_pin);
  servo4.attach(servo4_pin);
  servo5.attach(servo5_pin);
  
  // Servo pinleri giriş olarak ayarlanıyor
  pinMode(servo1_pin, INPUT);
  pinMode(servo2_pin, INPUT);
  pinMode(servo3_pin, INPUT);
  pinMode(servo4_pin, INPUT);
  pinMode(servo5_pin, INPUT);
}

void loop() {
  if (SerialBT.available()) {
    char receivedChar = SerialBT.read();  // Bluetooth komutu okunuyor
    handleCommand(receivedChar); // Komuta göre işlem yapılıyor

    // Servo pozisyonları ayarlanıyor
    servo1.write(map(servo1_pin, 0, 4096, 0, 180));
    servo2.write(map(servo2_pin, 0, 4096, 0, 180));
    servo3.write(map(servo3_pin, 0, 4096, 0, 180));
    servo4.write(map(servo4_pin, 0, 4096, 0, 180));
    servo5.write(map(servo5_pin, 0, 4096, 0, 180));
  }
}

// Komutları işleme metodu
void handleCommand(char command) {
  switch (command) {
    case 'F':
      motorController.moveForward(); // İleri git
      break;
    case 'L':
      motorController.moveLeft(); // Sola dön
      break;
    case 'R':
      motorController.moveRight(); // Sağa dön
      break;
    default:
      motorController.stop(); // Dur
      break;
  }
}
