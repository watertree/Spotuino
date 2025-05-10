#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

int year;
int month;
int day;


int hour;
int minutes;
int seconds;


LiquidCrystal_I2C lcd(0x27, 16, 2);   

int RedOne = 4;
int Yellow = 5;
int RedTwo = 8;
int Green = 10;

int kfc = 9;

bool GS = false;

int counter = 0;


void setup() {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("ERROR: Could not find DS3231 RTC!");
    while (1);
  }

  if(rtc.lostPower()){
    Serial.println("lost power");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  lcd.begin(16, 2);
  lcd.clear();
  lcd.backlight();

  pinMode(RedOne, INPUT);
  pinMode(Yellow, INPUT);
  pinMode(RedTwo, INPUT);
  pinMode(Green, INPUT);

  pinMode(kfc, OUTPUT);

}

void loop() {

  analogWrite(kfc, 250);
  DateTime now = rtc.now();
  
  year = now.year();
  month = now.month();
  day = now.day();

  hour = now.hour();
  minutes= now.minute();
  seconds= now.second();


  
  if(GS == false){
    lcd.setCursor(0, 0);

    if(hour<10){
      lcd.print(" ");
    }
    lcd.print(hour);
    lcd.print(":");
    if(minutes<10){
      lcd.print("0");
    }
    lcd.print(minutes);
    lcd.print(":");
    if(seconds<10){
      lcd.print("0");
    }
    lcd.print(seconds);



    lcd.setCursor(0, 1);
    lcd.print("counter: ");
    lcd.print(counter);
    if(digitalRead(Yellow)== HIGH){
      counter = counter + 1;
      delay(280);
    }
    else{
      Serial.print("");
    }

    if(digitalRead(RedTwo)== HIGH){
      counter = counter - 1;
      lcd.clear();
      delay(280);
    }
    else{
      Serial.print("");
    }

    if(digitalRead(RedOne)== HIGH){
      counter = 0;
      lcd.clear();
      delay(280);
      
    }
    else{
      Serial.print("");
    }

    if(digitalRead(Green)== HIGH){
      GS = true;
      lcd.clear();
      delay(500);
    }
    else{
      delay(100);
    }
  }
  else{
    lcd.setCursor(0, 0);
    lcd.print("spotify");

    if(digitalRead(Yellow)==HIGH){
      Serial.println("Pausing/Starting if");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("spotify");      
      lcd.setCursor(0, 1);
      lcd.print("Pausing/Starting");
      delay(50);
      
    }

    if(digitalRead(RedOne)==HIGH){
      Serial.println("Going Back if");

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("spotify");     
      lcd.setCursor(0, 1);
      lcd.print("Going Back");
      
      delay(50);

      
    }

    if(digitalRead(RedTwo)==HIGH){
      Serial.println("Going Forward if");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("spotify");     
      lcd.setCursor(0, 1);
      lcd.print("Going Forward");
      delay(50);
      
    }

    
    if(digitalRead(Green)== HIGH){
      GS = false;
      lcd.clear();
      delay(500);
    }
    else{
      delay(100);
    }
  
  }
}