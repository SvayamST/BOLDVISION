#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//SoftwareSerial gsmSerial(D4, D3);,
const int trigPin = D6;
const int echoPin = D5;
const int threshold = 70;
String phoneNumber = "+919141245024";
 
void setup() 
{
  lcd.init();
  Wire.begin(D2,D1);
  lcd.backlight();
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  //gsmSerial.begin(9600);
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
   delay(1000);
   Serial.println("Preparing to send SMS");
   SendMessage();
  delay(1000);
  lcd.clear();
  lcd.print("Smart Dustbin");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
}
 
void loop() 
{
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0342;
  Serial.print("distnace is");
  Serial.println(distance);
  int fillLevel = distance*100/40 ;
  //Serial.print(fillLevel);
  //int fillLevel = map(distance, 0, 100, 100, 0);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Fill Level: ");
  lcd.print(fillLevel);
  lcd.print("%");
  if (fillLevel >= threshold) {
    SendMessage();
  }
  delay(2000);
}
 
void SendMessage() 
{
  lcd.clear();
  lcd.print("Sending Alert...");
  //gsmSerial.println("AT+CPIN=<SIM_PIN>");
   Serial.println("Setting the GSM in text mode");
   Serial.println("AT+CMGF=1\r");
   delay(2000);
  //gsmSerial.println("AT+CMGF=1");
  Serial.println("Sending SMS to the desired phone number!");
   Serial.println("AT+CMGS=\"+919141245024\"\r");
  delay(1000);
  //gsmSerial.print("AT+CMGS=\"+919535343392\"\r");
  //gsmSerial.print(phoneNumber);
  //gsmSerial.println("\"");
  delay(1000);
  //String message = "Dustbin Full! Please Empty.";
  //gsmSerial.print(message);
  Serial.println("Hello Smart Dustbin");    // SMS Text
   delay(200);
   Serial.println((char)26);
  delay(1000);
  //gsmSerial.write(0x1A);
  delay(2000);
  lcd.clear();
  lcd.print("Alert Sent!");
  delay(2000);  
}

