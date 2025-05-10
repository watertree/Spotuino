#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <RTClib.h> // RTC library

#include <Keyboard.h>


//#include <Arduino.h>
//#include <WiFi.h>
//#include <SpotifyEsp32.h>


RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char ctrlkey = KEY_LEFT_CTRL;
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

//int RedOneK = 2;
//int YellowK = 3;
//int RedTwoK = 4;


int kfc = 9;

bool GS = false;

int counter = 0;


void setup() {
  Serial.begin(9600);
  //while (!Serial); // Wait for serial port to be ready

  if (!rtc.begin()) {
    Serial.println("ERROR: Could not find DS3231 RTC!");
    while (1); // Halt execution if RTC not found
  }

  if(rtc.lostPower()){
    Serial.println("lost power");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  lcd.begin(16, 2);
  lcd.clear();
  lcd.backlight();

  //Serial.begin(9600);

  Keyboard.begin();

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


  
  if(GS == false){//counter
/*
    lcd.setCursor(0, 0);
    lcd.print(hour);
    Serial.print(":");
    lcd                   .print(minutes);
    Serial.print(":");
    lcd.print(seconds);

    lcd.setCursor(0, 1);
    lcd.print("count:");
    lcd.print(counter);
*/

    lcd.setCursor(0, 0);

    if(month<10){
      Serial.print(" ");
    }
    Serial.print(month);
    Serial.print("/");
    if(day<10){
      Serial.print(" ");
    }
    Serial.print(day);
    Serial.print("/");
    Serial.print(year);

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
    //counter
    if(digitalRead(Yellow)== HIGH){
      counter = counter + 1;
      //lcd.clear();
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

    Serial.println(counter);

    Serial.println("");

    //switching
    if(digitalRead(Green)== HIGH){
      GS = true;
      lcd.clear();
      delay(500);
    }
    else{
      //Serial.println("not pressed false");
      delay(100);
    }
  }
  else{//spotify
    //Serial.println("spotify");
    lcd.setCursor(0, 0);
    lcd.print("spotify");

    if(digitalRead(Yellow)==HIGH){
      Keyboard.press(32);
      //0xD8 left arrow
      //0xD7 right arrow
      //0xDA up arrow
      //0xD9 Down arrow
      //0x80 left control
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("spotify");      
      lcd.setCursor(0, 1);
      lcd.print("Pausing/Starting");
      delay(50);
      
    }
    else{
      Keyboard.release(32);
      delay(50);
    }

    if(digitalRead(RedOne)==HIGH){
      Keyboard.press(0x80);//+(0x80);
      Keyboard.press(0xD8);
      //0xD8 left arrow
      //0xD7 right arrow
      //0xDA up arrow
      //0xD9 Down arrow

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("spotify");     
      lcd.setCursor(0, 1);
      lcd.print("Going Back");
      
      delay(50);

      
    }
    else{
      Keyboard.release(0x80);//+(0x80);
      Keyboard.release(0xD8);
      delay(50);
    }

    if(digitalRead(RedTwo)==HIGH){
      Keyboard.press(0x80);//(0x80);
      Keyboard.press(0xD7);
      //0xD8 left arrow
      //0xD7 right arrow
      //0xDA up arrow
      //0xD9 Down arrow
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("spotify");     
      lcd.setCursor(0, 1);
      lcd.print("Going Forward");
      delay(50);
      
    }
    else{
      Keyboard.release(0x80);//+(0x80);
      Keyboard.release(0xD7);
      delay(50);
    }


    
    if(digitalRead(Green)== HIGH){//switch
      GS = false;
      lcd.clear();
      delay(500);
    }
    else{
     // Serial.println("");
      delay(100);
    }
  
  }

/*
  if(digitalRead(RedOne)== HIGH){
    Serial.println("Power is on");
  }

  if(digitalRead(Yellow)== HIGH){
    Serial.println("Power is on");
  }

  if(digitalRead(RedTwo)== HIGH){
    Serial.println("Power is on");
  }

  if(digitalRead(Green)== HIGH){
    Serial.println("Power is on");
  }
*/
}