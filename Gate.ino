#include <Servo.h>
#include <SoftwareSerial.h>

// 모터
Servo myservo;
#define SERVO_PIN 13

// 블루투스
#define RXD 2
#define TXD 3

SoftwareSerial btSerial = SoftwareSerial(2, 3);

// 초음파 센서
int trig = 7;
int echo = 6;

// LED
#define LED_RED 10
#define LED_BLUE 9

// 잠금 상태 여부
int lock = 0;

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  myservo.attach(SERVO_PIN);
  myservo.write(0);

  lock = 1;
}

void loop() {
  String str = btSerial.readStringUntil('\n');
  Serial.println(str);
  /*
  lock = btSerial.read();
  if (lock != -1){
    Serial.println(lock);
  }
  */
  if(lock!=0){
    
    float distance = ultraSonic();
    // Serial.println(distance);

    if ( distance >= 0 && distance <= 10 ) {
      myservo.write(90);
      LED_ON();
    }else{
      myservo.write(0);
      LED_OFF();
    }
    
  }else{
    int sign = btSerial.read();
  }
}

void LED_ON(){
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, LOW);
  delay(500);
  
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, HIGH);
  delay(500);
}

void LED_OFF(){
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
}

float ultraSonic(){
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);

  float distanceCM = ( (34000 * duration) / 1000000 ) / 2;

  return distanceCM;
}
