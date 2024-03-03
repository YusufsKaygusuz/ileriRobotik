#include "BluetoothSerial.h"
#include <Deneyap_Servo.h>

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

class MotorController {
public:
  MotorController() {
    pinMode(MOT_DIR1, OUTPUT);
    pinMode(MOT_DIR2, OUTPUT);
    pinMode(MOT_DIR3, OUTPUT);
    pinMode(MOT_DIR4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    stop();
  }

  void moveForward() {
    ...
    setSpeed(true);
  }

  void moveLeft() {
    ...
    digitalWrite(ENA, LOW);
    digitalWrite(ENA, HIGH);
  }

  void moveRight() {
    digitalWrite(MOT_DIR1, HIGH);
    digitalWrite(MOT_DIR2, LOW);
    digitalWrite(MOT_DIR3, LOW);
    digitalWrite(MOT_DIR4, LOW);
    setSpeed(true);
  }

  void stop() {
    ...
    setSpeed(false);
  }

private:
  void setSpeed(bool enable) {
    digitalWrite(ENA, enable ? HIGH : LOW);
    digitalWrite(ENB, enable ? HIGH : LOW);
  }
};

MotorController motorController;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("DeneyapKart");
  SerialBT.println("\nDeneyapKart'a bağlanıldı.");
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  servo3.attach(servo3_pin);
  servo4.attach(servo4_pin);
  servo5.attach(servo5_pin);
  pinMode(servo1_pin, INPUT);
  pinMode(servo2_pin, INPUT);
  pinMode(servo3_pin, INPUT);
  pinMode(servo4_pin, INPUT);
  pinMode(servo5_pin, INPUT);
}

void loop() {
  if (SerialBT.available()) {
    char receivedChar = SerialBT.read();  //BLUETOOTH AÇMA
    handleCommand(receivedChar);
    servo1.write(map(servo1_pin, 0, 4096, 0, 180));
    servo2.write(map(servo2_pin, 0, 4096, 0, 180));
    servo3.write(map(servo3_pin, 0, 4096, 0, 180));
    servo4.write(map(servo4_pin, 0, 4096, 0, 180));
    servo5.write(map(servo5_pin, 0, 4096, 0, 180));
  }
}

void handleCommand(char command) {
  switch (command) {
    case 'F':
      motorController.moveForward(); 
      break;
    case 'L':
      motorController.moveLeft();
      break;
    case 'R':
      motorController.moveRight();
      break;
    default:
      motorController.stop();
      servo1.write(90); // Orta konum
      servo2.write(90); // Orta konum
      servo3.write(90); // Orta konum
      servo4.write(90); // Orta konum
      servo5.write(90); // Orta konum
      break;
  }
}
