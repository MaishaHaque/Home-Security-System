#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int PIRSensor = 2; //Define PIR Sensor pin

int Buzzer = 9; //PWM (~) pin BUzzer

int trigPin = 10; //trigger pin
int echoPin = 11; //echopin
int DISTANCE_THRESHOLD = 50; // centimeters


int smoke_detector = A0;
int safety_lim = 100; //Sets  smoke density safe limit

LiquidCrystal_I2C lcd(0x27,16,2);


int redPin= 7;
int greenPin = 6;
int bluePin = 5;


void setup(){
  Serial.begin(9600); //set baud rate
  
  //Sensors  
  pinMode(PIRSensor, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(smoke_detector, INPUT);
  
  
  //RGB
  pinMode(redPin, OUTPUT);              
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
 	
  //Buzzer
  pinMode(Buzzer, OUTPUT);
  
  

  //LCD Setup
  lcd.init();
  lcd.backlight();
  lcd.clear(); 
  lcd.setCursor(0, 0);
  Serial.println("Alarm is Activated"); 
  lcd.setCursor(0,0);
  
  //RGB Setup
  setColor(0,  255, 0); // Green Color
 
  
}

void loop() {
  
  //Readings
  
  //Ultrasonic
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delay(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int distance = duration * 0.034 / 2;
	
  //PIR & Smoke
  int SensorValue = digitalRead(PIRSensor); 
  int sensor_read = analogRead(smoke_detector); 
  
  //Conditions for Alarm
  
  //If triggers PIR Sensor
  
  if(SensorValue == HIGH){
	setColor(255, 0, 0); // Red Color
    tone(Buzzer, 10000);
    lcd.setCursor(0,0);
    Serial.println("Motion Detected!!!"); 
    delay(3000);
    lcd.clear();
  }
  
  //If triggers Ultrasonic
  else if(distance<DISTANCE_THRESHOLD){
    setColor(255, 0, 0); // Red Color
    tone(Buzzer, 10000);
    //Serial.println("Door Opened!!!");
    Serial.println(sensor_read);
    delay(3000);
    lcd.clear();
  }
  
  else if (sensor_read > safety_lim){
  
	setColor(255, 0, 0); // Red Color
    tone(Buzzer, 10000);
    Serial.println("FIRE!!!");
    //Serial.println(sensor_read);
    delay(3000);
  }
  
  //If nothing is triggered
  else {
    noTone(Buzzer);
    setColor(0,  255, 0); // Green Color
    Serial.println("Alarm Activated");
    delay(1000);
  }
 
}

void setColor(int redValue, int greenValue,  int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin,  greenValue);
  analogWrite(bluePin, blueValue);
}

