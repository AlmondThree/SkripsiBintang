//RTC
#include <DS3231.h> 
DS3231 rtc(SDA,SCL);

//Servo
#include <Servo.h> //library servo
Servo myservo; // membuat variabel servo untuk dikendalikan
int pos = 0; // deklarasi variabel untuk posisi sudut

//Ultrasonik
#define echoPin 12 //Echo Pin
#define trigPin 11 //Trigger Pin
#define Buzzer 13 //Led default dari Arduino uno
 
int maximumRange = 200; //kebutuhan akan maksimal range
int minimumRange = 00; //kebutuhan akan minimal range
long duration, distance; //waktu untuk kalkulasi jarak

//Ultrasonik_Removal
#define echoPin_1 #inputPIN //Echo Pin
#define trigPin_1 #inputPIN //Trigger Pin
#define Buzzer_1 #inputPIN //Led default dari Arduino uno
 
int maximumRange_1 = 200; //kebutuhan akan maksimal range
int minimumRange_1 = 00; //kebutuhan akan minimal range
long duration_1, distance_1; //waktu untuk kalkulasi jarak

//RTC
bool on=LOW;
bool off=HIGH;
String hari;
String waktu;
String tanggal;

//Turbidity
static float kekeruhan;
static float tegangan;

//Solenoid Valve
byte solRemoval #input pin;
bye solFilling #input pin;

void setup() {
  //Setup RTC
rtc.begin();
Serial.begin(9600);
rtc.setDOW(WEDNESDAY);
rtc.setTime(15,21,0);
rtc.setDate(2,2,2022);

//Setup Servo
myservo.attach(9); //deklarasi servo pada pin 9

//Setup Ultrasonic
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(Buzzer, OUTPUT);

//Setup Solenoid Valve
pinMode(solRemoval, OUTPUT);
pinMode(solFilling, OUTPUT);
}

void ultrasonicON(){
  digitalWrite(trigPin, LOW);delayMicroseconds(2);
digitalWrite(trigPin, HIGH);delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
 
//perhitungan untuk dijadikan jarak
distance = duration/58.2;
 
if (distance >= maximumRange || distance <= minimumRange)
{
Serial.println("Diluar Jangkauan");digitalWrite(Buzzer, HIGH);
}
else {
 
Serial.println(distance);
digitalWrite(Buzzer, LOW);
 
//waktu tunda 50mS
delay(50);
}
}

void ultrasonicRemoval_ON(){
  float turbidityBawah;
  
//digitalWrite(trigPin_1, LOW);delayMicroseconds(2);
//digitalWrite(trigPin_1, HIGH);delayMicroseconds(10);
//digitalWrite(trigPin_1, LOW);
//duration_1 = pulseIn(echoPin_1, HIGH);
 
long readUltrasonicRemoval(){
  digitalWrite(trigPin_1, LOW);delayMicroseconds(2);
digitalWrite(trigPin_1, HIGH);delayMicroseconds(10);
digitalWrite(trigPin_1, LOW);
duration_1 = pulseIn(echoPin_1, HIGH);
//perhitungan untuk dijadikan jarak
distance_1 = duration_1/58.2;
return distance_1;
}

distance_1 = readUltrasonicRemoval();

//perhitungan untuk dijadikan jarak
//distance_1 = duration_1/58.2;

bool flag = true; 

while(flag == true){
  digitalWrite(solFilling, HIGH);
  if (distance_1 >= maximumRange_1){

turbidityBawah = turbiditySensor();

if (turbidityBawah =< 50){
  digitalWrite(solRemoval, LOW);
  if (distance_1 <= minimumRange_1){
    digitalWrite(solFilling, LOW);
    flag = False;
};
};
};
};

};

void servoON(){
Delay (2000);
for(pos=0; pos<41 ; pos+=1){
  mekanik.write(150);
delay (250);
mekanik.write(0);
delay (250);
ultrasonicON();
}
}

void readRTC() {
 hari=rtc.getDOWStr();
 waktu=rtc.getTimeStr();
 tanggal=rtc.getDateStr();
 Serial.println(waktu);
 if(waktu=="07:00:00" || waktu=="11:30:00" || waktu=="16:30:00"){
    servoON()
  }
}

float turbiditySensor(){
  int val = analogRead(#input pin);
  tegangan = val * (5.00/1024);
  kekeruhan = 100.00 - (tegangan/4.6) * 100.00;
  return kekeruhan;
}

void turbidityControl(){
  float nilaiKekeruhan;
nilaiKekeruhan = turbiditySensor();

if (nilaiKekeruhan => 50){
  digital.write(solRemoval, HIGH);
  ultrasonicRemoval_ON();
} else {
  digital.write(solRemoval, LOW);
}
}

void loop() {
  readRTC();
  ultrasonicON();
  turbidityControl();
  delay(500);
}
