//LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//RTC
#include <DS3231.h>
DS3231  rtc(SDA, SCL);
Time t;

//BUZZER
#define buzzer 4

//ULTRASONIK
#define trig 7
#define echo 8
long duration, cm;

//BUTTTON MAKAN
//#define button1 12
//int statusButton1 = 0;

//BUTTTON SELESAI MAKAN 
//#define button2 13
//int statusButton2 = 0;

//SET TIME MAKAN 1 (24 HOUR FORMAT)
const int OnHour1 = 15;
const int OnMin1 = 35;
const int OnSec1 = 05;

// SET TIME OFF MAKAN 1
const int EndOnHour1 = 15;
const int EndOnMin1 = 35;
const int EndOnSec1 = 35;

////SET TIME SELESAI MAKAN 1 (24 HOUR FORMAT)
const int OffHour1 = 15;
const int OffMin1 = 36;
const int OffSec1 = 05;

// SET TIME OFF SELESAI MAKAN 1
const int EndOffHour1 = 15;
const int EndOffMin1 = 36;
const int EndOffSec1 = 35; 

//SET TIME MAKAN 2 (24 HOUR FORMAT)
const int OnHour2 = 15;
const int OnMin2 = 38;
const int OnSec2 = 05;

// SET TIME OFF Makan 2
const int EndOnHour2 = 15;
const int EndOnMin2 = 38;
const int EndOnSec2 = 35;

////SET TIME SELESAI MAKAN 2 (24 HOUR FORMAT)
const int OffHour2 = 15;
const int OffMin2 = 39;
const int OffSec2 = 05;

// SET TIME OFF SELESAI Makan 2
const int EndOffHour2 = 15;
const int EndOffMin2 = 39;
const int EndOffSec2 = 35;

//SET TIME MAKAN 3 (24 HOUR FORMAT)
const int OnHour3 = 15;
const int OnMin3 = 41;
const int OnSec3 = 05;

// SET TIME OFF MAKAN 3
const int EndOnHour3 = 15;
const int EndOnMin3 = 41;
const int EndOnSec3 = 35;

////SET TIME SELESAI MAKAN 3 (24 HOUR FORMAT)
const int OffHour3 = 15;
const int OffMin3 = 42;
const int OffSec3 = 05;

// SET TIME OFF SELESAI MAKAN 3
const int EndOffHour3 = 15;
const int EndOffMin3 = 42;
const int EndOffSec3 = 35;


//MOTOR TANDON
#define M1A  3 
#define M1B  5

//MOTOR KIRI UNTUK SELESAI MAKAN
#define M2A 6
#define M2B 9

//MOTOR KANAN UNTUK MAKAN
#define M3A 10
#define M3B 11


void setup() {
   // put your setup code here, to run once:
  Serial.begin(9600);

  rtc.begin();  
  rtc.setTime(15, 34, 55);  

  lcd.begin();
  lcd.backlight();

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  pinMode(M3A, OUTPUT);
  pinMode(M3B, OUTPUT);

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  //pinMode(button1, INPUT);
  //pinMode(button2, INPUT);

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  t = rtc.getTime();
 
  Serial.println(rtc.getTimeStr());
  lcd.setCursor(0,1);
  lcd.print("Jam: ");
  
  lcd.setCursor(5,1);
  lcd.print(rtc.getTimeStr());

  Serial.println(cm);

  //PEMBACAAN ULTRASONIK  
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo, HIGH);
  cm = microsecondsToCentimeters(duration);

  //PEMBACAAN BUTTON
  /*statusButton1 = digitalRead(button1);  
  statusButton2 = digitalRead(button2); */

  // KONDISI TANDON
  if (cm > 11){    
    digitalWrite(buzzer, HIGH);
    delay(500);
  } else {
    digitalWrite(buzzer, LOW);    
  }
   

  // BUTTON MAKAN
  /*if (statusButton1 == HIGH){
    //MOTOR TANDON
    analogWrite(M1A, 100);
    analogWrite(M1B, 0);
    //MOTOR KANAN MAKAN
    analogWrite(M2A, 0);
    analogWrite(M2B, 0);
    analogWrite(M3A, 100);
    analogWrite(M3B, 0);    
    Serial.println("MAKAN MANUAL");    
   } */

  // BUTTON SELESAI MAKAN 
  /*if (statusButton2 == HIGH){
    //MOTOR TANDON    
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
    //MOTOR KIRI SELESAI MAKAN 
    analogWrite(M2A, 0);
    analogWrite(M2B, 100);
    analogWrite(M3A, 0);
    analogWrite(M3B, 0); 
    Serial.println("SELESAI MAKAN MANUAL");    
  } */ 
  
  // KONDISI MAKAN 1  
  if (t.hour == OnHour1 && t.min == OnMin1 && t.sec == OnSec1 && cm < 10 ){
    //MOTOR TANDON
    analogWrite(M1A, 100);
    analogWrite(M1B, 0);
    //MOTOR KANAN MAKAN
    analogWrite(M2A, 0);
    analogWrite(M2B, 0);
    analogWrite(M3A, 100);
    analogWrite(M3B, 0);    
    Serial.println("MAKAN 1");
    lcd.setCursor(0,0);
    lcd.print("MAKAN 1 ");
    }
  
  // KONDISI OFF MAKAN 1
  else if (t.hour == EndOnHour1 && t.min == EndOnMin1 && t.sec == EndOnSec1 && cm < 10 ){
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
    analogWrite(M2A, 0);
    analogWrite(M2B, 0);
    analogWrite(M3A, 0);
    analogWrite(M3B, 0);    
    Serial.println("OFF MAKAN 1");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OFF MAKAN 1 ");
    }
    
  // KONDISI SELESAI MAKAN 1    
  if (t.hour == OffHour1 && t.min == OffMin1 && t.sec == OffSec1){
    //MOTOR TANDON    
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
    //MOTOR KIRI SELESAI MAKAN 
    analogWrite(M2A, 0);
    analogWrite(M2B, 100);
    analogWrite(M3A, 0);
    analogWrite(M3B, 0); 
    Serial.println("SELESAI MAKAN 1");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SELESAI MAKAN 1 ");
    }

  //  KONDISI OFF SELESAI MAKAN 1
  else if (t.hour == EndOffHour1 && t.min == EndOffMin1 && t.sec == EndOffSec1){
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
    analogWrite(M2A, 0);
    analogWrite(M2B, 0);
    analogWrite(M3A, 0);
    analogWrite(M3B, 0); 
    Serial.println("OFF SELESAI MAKAN 1");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OFF SELESAI MAKAN 1 ");
    }  

  // KONDISI MAKAN 2  
  if (t.hour == OnHour2 && t.min == OnMin2 && t.sec == OnSec2 && cm < 10){
    //MOTOR TANDON
    analogWrite(M1A, 100);
    analogWrite(M1B, 0);
    //MOTOR KANAN MAKAN
    analogWrite(M2A, 0);
    analogWrite(M2B, 0); 
    analogWrite(M3A, 100);
    analogWrite(M3B, 0);    
    Serial.println("MAKAN 2");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("MAKAN 2 ");
    }

  //  KONDISI OFF MAKAN 2
  else if (t.hour == EndOnHour2 && t.min == EndOnMin2 && t.sec == EndOnSec2){
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
    analogWrite(M2A, 0);
    analogWrite(M2B, 0);
    analogWrite(M3A, 0);
    analogWrite(M3B, 0); 
    Serial.println("OFF MAKAN 2");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OFF MAKAN 2 ");
    }        
          
      
  // KONDISI SELESAI MAKAN 2
  if (t.hour == OffHour2 && t.min == OffMin2 && t.sec == OffSec2){
    //MOTOR TANDON    
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
    //MOTOR KIRI SELESAI MAKAN 
    analogWrite(M2A, 0);
    analogWrite(M2B, 100);
    analogWrite(M3A, 0);
    analogWrite(M3B, 0); 
    Serial.println("SELESAI MAKAN 2");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SELESAI MAKAN 2 ");
    }

  //  KONDISI OFF SELESAI MAKAN 2
  else if (t.hour == EndOffHour2 && t.min == EndOffMin2 && t.sec == EndOffSec2){
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
    analogWrite(M2A, 0);
    analogWrite(M2B, 0);
    analogWrite(M3A, 0);
    analogWrite(M3B, 0); 
    Serial.println("OFF SELESAI MAKAN 2");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OFF SELESAI MAKAN 2 ");
    } 

  // KONDISI MAKAN 3  
  if (t.hour == OnHour3 && t.min == OnMin3 && t.sec == OnSec3 && cm < 10){
    //MOTOR TANDON
    analogWrite(M1A, 100);
    analogWrite(M1B, 0);
    //MOTOR KANAN MAKAN
    analogWrite(M2A, 0);
    analogWrite(M2B, 0);     
    analogWrite(M3A, 100);
    analogWrite(M3B, 0);    
    Serial.println("MAKAN 3");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("MAKAN 3 ");
    }

  //  KONDISI OFF MAKAN 3
  else if (t.hour == EndOnHour3 && t.min == EndOnMin3 && t.sec == EndOnSec3){
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
    analogWrite(M2A, 0);
    analogWrite(M2B, 0);
    analogWrite(M3A, 0);
    analogWrite(M3B, 0); 
    Serial.println("OFF MAKAN 3");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OFF MAKAN 3 ");
    } 

  // KONDISI SELESAI MAKAN 3
  if (t.hour == OffHour3 && t.min == OffMin3 && t.sec == OffSec3){
    //MOTOR TANDON    
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
    //MOTOR KIRI SELESAI MAKAN 
    analogWrite(M2A, 0);
    analogWrite(M2B, 100);
    analogWrite(M3A, 0);
    analogWrite(M3B, 0);     
    Serial.println("SELESAI MAKAN 3");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SELESAI MAKAN 3 ");
    } 

  //  KONDISI OFF SELESAI MAKAN 3
  else if (t.hour == EndOffHour3 && t.min == EndOffMin3 && t.sec == EndOffSec3){
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
    analogWrite(M2A, 0);
    analogWrite(M2B, 0);
    analogWrite(M3A, 0);
    analogWrite(M3B, 0); 
    Serial.println("OFF SELESAI MAKAN 3");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OFF SELESAI MAKAN 3 ");
    }     
     
  delay(1000);
}
  long microsecondsToCentimeters(long microseconds){
    return microseconds / 29 / 2;
  }
