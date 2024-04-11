void register_entry() {
  myFile = SD.open("registro.txt", FILE_WRITE);
  DateTime time = rtc.now();

  Serial.println("Hora de entrada: ");
  timestamp();

  if (myFile) {
    Serial.println("Writing date ");
    myFile.print(daysOfTheWeek[time.dayOfTheWeek()]);
    myFile.print("/");
    myFile.print(time.timestamp(DateTime::TIMESTAMP_DATE));
    myFile.print("/");
    myFile.print(time.timestamp(DateTime::TIMESTAMP_TIME));
    myFile.print("/");


    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening registro.txt");
  }

  delay(100);
  Serial.println("Registro de entrada");
}