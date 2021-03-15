#include <SPI.h>
#include <MFRC522.h>


#define buzz 8

int kirmizi = 2;
int yesil = 3;
int mavi = 4;

int rstPin = 9;
int ssPin = 10;

MFRC522 rfid(ssPin,rstPin);

int ID[4] = {233,245,199,184};

char sifre0[4]={'4','2','1','3'};
char sifre[4];

void bzzz(){
  tone(buzz,10);
  delay(1000);
  noTone(buzz);
}



//kart id görmeye yaran fonksiyon
void ekranaYaz(){
  Serial.print("id = ");
  for(int sayac=0;sayac<4;sayac++){
     Serial.print(rfid.uid.uidByte[sayac]);
     Serial.print(" ");
  }
   Serial.println(" ");
}
//kırmızı yanıp sönüyo
void yanlis(){
      bzzz();
      analogWrite(kirmizi,255);
      analogWrite(yesil,255);
      analogWrite(mavi,255);
      delay(100);
      analogWrite(kirmizi,0);
      analogWrite(yesil,255);
      analogWrite(mavi,255);
      delay(100);
      analogWrite(kirmizi,255);
      analogWrite(yesil,255);
      analogWrite(mavi,255);
      delay(100);
      analogWrite(kirmizi,0);
      analogWrite(yesil,255);
      analogWrite(mavi,255);
      delay(100);
      analogWrite(kirmizi,255);
      analogWrite(yesil,255);
      analogWrite(mavi,255);
      delay(100);
      analogWrite(kirmizi,0);
      analogWrite(yesil,255);
      analogWrite(mavi,255);
      delay(100);
      analogWrite(kirmizi,255);
      analogWrite(yesil,255);
      analogWrite(mavi,255);
      delay(100);
      analogWrite(kirmizi,0);
      analogWrite(yesil,255);
      analogWrite(mavi,255);
      delay(100);

}

void setup() {
  
  pinMode(kirmizi,OUTPUT);
  pinMode(yesil,OUTPUT);
  pinMode(mavi,OUTPUT);
  Serial.begin(9600);//Arduino
  SPI.begin();//RFID
  rfid.PCD_Init();
}

void loop() {
    
    analogWrite(kirmizi,0);
    analogWrite(yesil,255);
    analogWrite(mavi,255);
    
    if(Serial.available()){
          sifre[0] = Serial.read();
          sifre[1] = Serial.read();
          sifre[2] = Serial.read();
          sifre[3] = Serial.read();
          //Serial.print(sifre);          
    }

  if(sifre0[0]==sifre[0] && sifre0[1]==sifre[1] && sifre0[2]==sifre[2] && sifre0[3]==sifre[3]){
    sifreYaz();
    bzzz();
    analogWrite(yesil,255);
    analogWrite(mavi,0);
    analogWrite(kirmizi,255);
    delay(5000);
  }
    
    
    
  if(!rfid.PICC_IsNewCardPresent()){
    return;  
  }
  if(!rfid.PICC_ReadCardSerial()){
    return;  
  }
  
  if(rfid.uid.uidByte[0]==ID[0] && rfid.uid.uidByte[1]==ID[1] && rfid.uid.uidByte[2]==ID[2] && rfid.uid.uidByte[3]==ID[3]){
    Serial.println("kapi kart ile açıldı");
    ekranaYaz(); 
    
    analogWrite(kirmizi,255);
    analogWrite(mavi,255);
    analogWrite(yesil,0);
    bzzz();
    delay(3000);
  }
  else{
      Serial.println("yetkisiz kart");
      ekranaYaz();
      yanlis();
      
  }

  
  rfid.PICC_HaltA();
}

//şifreyi gösteren fonk
void sifreYaz(){
  Serial.println("kapı şifre ile açıldı");
  Serial.print("sifre = ");
  for(int i=0;i<4;i++){
    Serial.print(sifre[i]);
  }
  Serial.println(" ");
}
