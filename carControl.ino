const int x_eks = A0;
const int y_eks = A1;

int x_durum;
int y_durum;


void setup() {
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);


  Serial.begin(9600);// SERİ MONİTÖR KULLANMAK İÇİN 

  
  // put your setup code here, to run once:

}

void loop() {

  x_durum = analogRead(x_eks);
  y_durum = analogRead(y_eks);
  Serial.println("x_durum"); // SERİ PORT EKRANDA JEOSTİK DEGERLERİ GORMEK İÇİN
  Serial.println(x_durum);
  Serial.println("y_durum");
  Serial.println(y_durum);

  if(x_durum>1020){ // İLERİ GİTMEK İÇİN 

    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
  }

    else if(x_durum<50) { // GERİTMEK İÇİN
      digitalWrite(3,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(6,HIGH);
      
    
  }
    else if(y_durum>1020){ //SAGA GITMEK İÇİN 

  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  
 }


 else if(y_durum<50) { // SOLA GITMEK ICIN 

  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  
 }

 else { // EĞRER JEOSTİK KULANILMAZ ISE 
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  
 }
}
