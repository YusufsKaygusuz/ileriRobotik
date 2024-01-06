// Joyistik Verilerini Okuma Algoritması
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
Serial.println(Dig_Val); delay(100);
}

// Tekrar eden yapıyı fonksiyona taşıma
void bilgilendirme(const char *label, int value) {
  Serial.print(label);
  Serial.print(": ");
  Serial.println(value);
}

void loop () {
  X_Val = analogRead(X_pin);
  Y_Val = analogRead(Y_pin);
  Dig_Val = digitalRead(SW_pin);

  bilgilendirme("X_Val", X_Val);
  bilgilendirme("Y_Val", Y_Val);
  bilgilendirme("Dig_Val", Dig_Val);




