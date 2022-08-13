#include <SPI.h>
#include <MFRC522.h>
#include<Servo.h>
#include<SoftwareSerial.h>
#define SS_PIN 10
#define RST_PIN 9
#include<LiquidCrystal.h>

LiquidCrystal lcd(19, 18, 17, 16, 15, 14); //creation of object with all pins used for the class (RS,En,D4,D5,D6,D7)
//Rw,VSS,K is GND
//VDD,A is +5
//Vo to POT Middle terminal

#define GLED 2                     //Global Defination
#define RLED 3                 //Global Defination

String aNAME="Sudhanva_G_R";
String bNAME="Tejesh_U";

String aNO="9743182919";
String bNO="9875664812";

int aBAL=100;
int bBAL=200;

int atemp, btemp;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myservo;
void setup() 
{
  lcd.begin(16, 2);            //initiate data transmission uaing object LCD
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  pinMode(RLED,OUTPUT);
  pinMode(GLED,OUTPUT);
  mfrc522.PCD_Init();   // Initiate MFRC522 (Performs a soft reset on the MFRC522 chip and waits for it to be ready again)iniate comm. b/w Tx & Rx in RFID
  myservo.attach(5);     //Attach the Servo variable to a pin
}

void loop() 
{
  digitalWrite(RLED,HIGH);
  digitalWrite(GLED,LOW);// Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("RFID tag No.      :");
  String content= ""; //Here content is variable
  byte letter; //Here letter is variable
  for (byte i = 0; i < mfrc522.uid.size; i++) // unique identification.size is the length of that RFID
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
 
  content.toUpperCase();
  
  if (content.substring(1) == "F2 C5 D4 1B") //change here the UID of the card/cards that you want to give access
  {
           lcd.clear();
           lcd.setCursor(4,0);          
           lcd.print("WELCOME"); 
          Serial.print("Owner Name        : ");
          Serial.print(aNAME);
          Serial.print("\n");
          Serial.print("Mobile No.        : ");
          Serial.print(aNO);
          Serial.print("\n");
          Serial.println("Vehicle No.       : KA-06-V-6542");
          Serial.println("Vehicle Type      : L M V");
          Serial.print("Available balance : ");
          Serial.print(aBAL);
          Serial.print(" Rs.\n");
          Serial.print("Toll Charges      : 30 Rs.\n");
          if(aBAL>=30)
          {
              aBAL=aBAL-30;
              atemp=aBAL;
              lcd.setCursor(0,1);
              lcd.print("Remain Bal:");
              lcd.setCursor(11,1);
              lcd.print(aBAL);
              Serial.println("Gate opened");
              myservo.write(0);
              digitalWrite(RLED,LOW);
              digitalWrite(GLED,HIGH);
              delay(4000);
              myservo.write(90);
              Serial.println("Gate closed");    
              digitalWrite(RLED,HIGH);
              digitalWrite(GLED,LOW);
              lcd.clear();
              lcd.setCursor(3,1);
              lcd.print("THANK YOU");           
              Serial.print("Remaining balance : ");
              Serial.print(aBAL);
              Serial.print(" Rs.\n\n");
              delay(2000);
              lcd.clear();
              lcd.setCursor(4,0);
              lcd.print("WELCOME");
         }
          else
          {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Please Recharge");
              lcd.setCursor(0,1);
              lcd.print("Balance is low");
              delay(3000);
              lcd.clear();   
              Serial.println("*************** Please Recharge *************** ");
              Serial.println("*************** The Balance is low *************** ");
          }
           
  }
  
  else if(content.substring(1)=="D9 5E 4F D3")
 {
           lcd.clear();
           lcd.setCursor(4,0);
           lcd.print("WELCOME");           
          Serial.print("Owner Name        : ");
          Serial.print(bNAME);
          Serial.print("\n");
          Serial.print("Mobile No.        : ");
          Serial.print(bNO);
          Serial.print("\n");
          Serial.println("Vehicle No.       : KA-06-V-6542");
          Serial.println("Vehicle Type      : L M V");
          Serial.print("Available balance : ");
          Serial.print(bBAL);
          Serial.print(" Rs.\n");
          Serial.print("Toll Charges      : 30 Rs.\n");
          if(bBAL>=30)
          {
              bBAL=bBAL-30;
              btemp=bBAL;
              lcd.setCursor(0,1);
              lcd.print("Remain Bal:");
              lcd.setCursor(11,1);
              lcd.print(bBAL);
              Serial.println("Gate opened");
              myservo.write(0);
              digitalWrite(RLED,LOW);
              digitalWrite(GLED,HIGH);
              delay(4000);
              myservo.write(90);
              Serial.println("Gate closed");    
              digitalWrite(RLED,HIGH);
              digitalWrite(GLED,LOW);
              lcd.clear();
              lcd.setCursor(3,1);
              lcd.print("THANK YOU");           
              Serial.print("Remaining balance : ");
              Serial.print(bBAL);
              Serial.print(" Rs.\n\n");
              delay(2000);
              lcd.clear();
              lcd.setCursor(4,0);
              lcd.print("WELCOME");
         }
         else 
          {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Please Recharge");
              lcd.setCursor(0,1);
              lcd.print("Balance is low");
              delay(3000);
              lcd.clear();   
              Serial.println("*************** Please Recharge *************** ");
              Serial.println("*************** The Balance is low *************** ");
          }
          
     }
}
