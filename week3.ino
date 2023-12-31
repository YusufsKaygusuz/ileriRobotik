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
