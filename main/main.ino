//Librerias SD
#include <SD.h>
#include <SPI.h>

//Libreria reloj
#include <RTClib.h>

//Libreria tira de leds
#include <Adafruit_NeoPixel.h>

//Libreria lector de huella
#include <Adafruit_Fingerprint.h>


//MicroSD
#define SdPin 10
File myFile;


//////////Reloj//////////
RTC_DS3231 rtc;

///////////Tira de leds/////////
Adafruit_NeoPixel PANEL = Adafruit_NeoPixel(4, 12, NEO_GRB + NEO_KHZ800);

/////////Sensor de huella///////////
#define mySerial Serial1
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);


char daysOfTheWeek[7][12] = { "Sunday", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
int LED_1 = 0, LED_2 = 1, LED_3 = 2, LED_4 = 3;  //orden de leds
int solenoide = 41;
int user;
int user_checkout;
int btn = 52;
bool bathroom_available;



void setup() {

  pinMode(btn, INPUT);
  pinMode(solenoide, OUTPUT);
  digitalWrite(solenoide, HIGH);

  PANEL.begin();
  PANEL.show();
  PANEL.setBrightness(20);

  Serial.begin(57600);   //Comunicacion con computadora
  Serial1.begin(57600);  //comunicacion con sensor de huella
  Serial.println("Comunicacion Serial iniciada");
  delay(100);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  // if (rtc.lostPower()) {
  //   Serial.println("RTC lost power, let's set the time!");
  //   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // }

  if (rtc.begin()) {
    Serial.println("Let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }

}

void loop() {
  int user_out;
  bool btn_check_out;

  user = get_finger_id(finger);

  if (user == 0) {
    PANEL.setPixelColor(LED_1, 0, 255, 0);
    PANEL.show();
    Serial.println("Id no encontrado");
    delay(2000);
    digitalWrite(solenoide, HIGH);
  }

  if (user != 0) {
    open_door();
    delay(5000);
    register_entry();

    bathroom_available = false;
    while (!bathroom_available) {
      PANEL.setPixelColor(LED_1, 255, 0, 0);
      PANEL.show();

      if (digitalRead(btn) == HIGH) {
        Serial.println("Boton activado");
        Serial.println("Ingresa tu huella para salir");

        open_door();
        btn_check_out = true;

        while (btn_check_out) {
          user_out = get_finger_id(finger);
          if (user_out == 0) {
            Serial.println("Ingresa de nuevo tu huella...");
            delay(2000);
          }
          if (user_out == user) {
            Serial.println(user_out);
            check_out();
            btn_check_out = false;
          }
        }

        Serial.println("Bano desocupado");
        bathroom_available = true;
      }
    }
    user = 0;
  }
}
