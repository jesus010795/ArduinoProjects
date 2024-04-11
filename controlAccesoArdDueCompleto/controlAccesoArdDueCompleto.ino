
#include <SPI.h>

//RFID
#include <MFRC522.h>

//Librerias SD
#include <SD.h>

//Libreria reloj
#include <RTClib.h>

#define RST_PIN 5  // Configurable, see typical pin layout above

#define SS_1_PIN 53  // Configurable, take a unused pin, only HIGH/LOW required, must be different to SS 2
#define SS_2_PIN 8   // Configurable, take a unused pin, only HIGH/LOW required, must be different to SS 1


#define NR_OF_READERS 2

byte ssPins[] = { SS_1_PIN, SS_2_PIN };
MFRC522 mfrc522[NR_OF_READERS];  // Create MFRC522 instance.
MFRC522::StatusCode status;


//MicroSD
#define SdPin 13
File myFile;

#define LOCK 2
#define RED_LED 30
#define GREEN_LED 31
#define BLUE_LED 32
#define BUZZER 9  //
#define BTN 38

//////////Reloj//////////
RTC_DS3231 rtc;




char daysOfTheWeek[7][12] = { "Sunday", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
// int LED_1 = 0, LED_2 = 1, LED_3 = 2, LED_4 = 3;  //orden de leds

String id_employee;
String first_name;
String last_name;

void setup() {
  pinMode(LOCK, OUTPUT);
  digitalWrite(LOCK, HIGH);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  Serial.begin(9600);  // Initialize serial communications with the PC
  while (!Serial)
    ;

  bool loopExecuted = false;
  myFile = SD.open("registro.txt", FILE_WRITE);
  pinMode(BTN, INPUT);

  SPI.begin();  // Init SPI bus


  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN);  // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  // if (rtc.begin()) {
  //   Serial.println("Let's set the time!");
  //   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // }
  // if (SD.begin(SdPin)) {
  //   Serial.println("initialization MSD!");
  //   // while (1);
  // }
  // if (!SD.begin(SdPin)) {
  //   Serial.println("initialization sd failed!");
  //   while (1)
  //     ;
  // }

  // if (!loopExecuted) {
  //   for (int i = 0; i < 1; i++) {
  //     myFile.print("-Dia-");
  //     myFile.print("/");
  //     myFile.print("Fecha");
  //     myFile.print("/");
  //     myFile.print("Hora de entrada");
  //     myFile.print("/");
  //     myFile.print("Id empleado");
  //     myFile.print("/");
  //     myFile.println("Hora de salida");
  //   }
  //   // Mark the loop as executed
  //   loopExecuted = true;
  // }
}

/**
 * Main loop.
 */
void loop() {
  bool occupied_bathroom;
  digitalWrite(GREEN_LED, HIGH);

  String comparacionTarjeta;
  // leddisponible();
  Serial.println("Ingresa tu tarjeta: " + id_employee);
  Serial.println(("."));
  delay(1000);

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {

      Serial.print("Hexadecimal convertido en string: ");
      to_string(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size, id_employee);

      // first_name = get_first_name();
      Serial.println(id_employee);
      Serial.println(first_name);
      delay(1000);
      // Halt PICCbu
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    }
  }


  if (id_employee != "") {
    occupied_bathroom = true;

    buzzer_ok();
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    open_door();

    register_entry();

    while (occupied_bathroom) {
      // Serial.println("Ocupado");
      // delay(1000);

      if (digitalRead(BTN) == HIGH) {
        buzzer_ok();

        bool compare = true;
        bool card_comparation = true;

        String compare_employee;
        Serial.println("Boton activado");
        open_door();


        while (compare) {
          Serial.println("Ingresa tu tarjeta para salir");
          delay(1000);

          while (card_comparation) {
            checkout_leds();
            for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
              if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {

                Serial.print("Hexadecimal convertido en string: ");
                to_string(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size, compare_employee);
                Serial.println(compare_employee);
                delay(1000);
                // Halt PICCbu
                mfrc522[reader].PICC_HaltA();
                // Stop encryption on PCD
                mfrc522[reader].PCD_StopCrypto1();
              }
            }

            if (compare_employee == id_employee) {
              Serial.println(compare_employee);
              Serial.println(id_employee);
              check_out();
              digitalWrite(RED_LED, LOW);
              compare = false;
              card_comparation = false;
            } else {
              buzzer_error();
            }
            compare_employee = "";
          }
        }

        id_employee = "";
        occupied_bathroom = false;
      }
    }
  }

  // Serial.println(id_employee);
}


void to_string(byte *buffer, byte bufferSize, String &hexValues) {
  for (byte i = 0; i < bufferSize; i++) {
    hexValues += (buffer[i] < 0x10 ? "0" : "");  // Añade un cero inicial si es necesario
    hexValues += String(buffer[i], HEX);         // Concatena el valor hexadecimal
  }
}
