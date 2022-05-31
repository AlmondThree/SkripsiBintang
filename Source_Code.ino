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

//RTC
bool on=LOW;
bool off=HIGH;
String hari;
String waktu;
String tanggal;

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

void loop() {
  readRTC();
  ultrasonicON();
  delay(500);
}
