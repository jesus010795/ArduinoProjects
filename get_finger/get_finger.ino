#include <Adafruit_Fingerprint.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial1
#endif

int finger_id;

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(57600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  // Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  // finger.getTemplateCount();

  // if (finger.templateCount == 0) {
  //   Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  // }
  // else {
  //   Serial.println("Waiting for valid finger...");
  //     Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  // }

}

void loop() {
  // put your main code here, to run repeatedly:

  finger_id = get_finger_id(finger);
  if(finger_id == 0){
    return Serial.println('.');
  }
  Serial.println(finger_id);
  delay(5000);
}
