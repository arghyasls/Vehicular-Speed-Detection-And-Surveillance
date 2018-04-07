#include<LiquidCrystal.h>


LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

int sensor1 = 2;
int sensor2 = 3;
int buzzerPin = 10; //Define buzzerPin

int Time1;
int Time2;
int Time;
int flag = 0;

float distance = 5;
int led=12;
float Speed;

void setup() {
  Serial.begin(9600);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
     delay(2000);               // wait for a second
  digitalWrite(led, LOW);   
  digitalWrite(buzzerPin ,0); 
    Serial.println("HELLO");
  attachInterrupt(0,fun1,RISING);
  attachInterrupt(1,fun2,FALLING);
pinMode(led, OUTPUT);   
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("SPEED MEASURMENT");

}

void fun1()
{
  Time1 = millis(); 
  if (flag == 0) {flag = 1;}
  else {flag = 0;}
}

void fun2()
{
  Time2 = millis();
  if (flag == 0) {flag = 1;}
  else {flag = 0;}
}

void beep(unsigned char delayms) { //creating function
  analogWrite(buzzerPin, 20); //Setting pin to high
  delay(delayms); //Delaying
  analogWrite(buzzerPin ,0); //Setting pin to LOW
  delay(delayms); //Delaying
  
}
void loop() {
  if (flag == 0){
  if      (Time1 > Time2) {Time = Time1 - Time2;  Speed = (distance*1000)/Time;}
  else if (Time2 > Time1) {Time = Time2 - Time1;  Speed = (distance*1000)/Time;}
  else    {Speed = 0;}
  } 
  
  if (Speed == 0) { 
    lcd.setCursor(0, 1); 
    lcd.print(".......OK......."); 
    }
  else { 
    lcd.setCursor(2, 1); 
    lcd.print(Speed);
    lcd.print(" cm/sec");
    Serial.print(abs(Speed));
    Serial.println(" cm/sec");
 //   Serial.println(Time1);
  //   Serial.println(Time2);
    if (Speed>5)
    {beep(100);delay(500);analogWrite(buzzerPin,255) ;  }
    else
    {digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
     delay(2000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);               // wait for a second
    }   // delay(100);
    Time1 = 0;
    Time2 = 0;
    }
}

