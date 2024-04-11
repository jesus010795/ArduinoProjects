#include <SPI.h>

#include <SD.h>

#include <RTClib.h>

#include <Adafruit_Fingerprint.h>

#define SdPin 10
File myFile;


RTC_DS3231 rtc;
#define mySerial Serial1
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int LED_1 = 0,LED_2 = 1,LED_3 = 2,LED_4 = 3; //orden de leds
int solenoide = 41;
int user;
int user_checkout;
int btn = 52;
int btn_state;          // Al accionar el boton nos devolvera 1 o 0
bool available = true;
bool loopExecuted = false;


void setup() {
  
  pinMode(btn, INPUT);
  pinMode(solenoide,OUTPUT);
  digitalWrite(solenoide, HIGH);
  
  Serial.begin(9600);//Comunicacion con computadora
  Serial1.begin(57600);//comunicacion con sensor de huella
  Serial.println("Comunicacion Serial iniciada");
  delay(100);



  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  // if (rtc.lostPower()) {
  //   Serial.println("RTC lost power, let's set the time!");
  //   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // }

  if (rtc.begin()) {
    Serial.println("RTC let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  if (!SD.begin(SdPin)) {
    Serial.println("SD initialization failed!");
    while (1);
  }

}

void loop() {

  user = get_finger_id(finger);
  btn_state = digitalRead(btn);
  // Serial.println(btn_state); 

  if (user != 0 || btn_state !=0 ){
    if (btn_state){
      Serial.println("Boton accionado");
    }
    timestamp();
    open_door();
    Serial.println(user);
  }

  delay(2000);

}
