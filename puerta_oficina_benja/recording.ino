void recording() {
  bool loopExecuted;
  myFile = SD.open("registro.txt", FILE_WRITE);
  DateTime time = rtc.now();

  // Serial.println(daysOfTheWeek[time.dayOfTheWeek()]);
  // Serial.println(time.timestamp(DateTime::TIMESTAMP_DATE));
  // Serial.println(time.timestamp(DateTime::TIMESTAMP_TIME));
  if (!loopExecuted) {
    for (int i = 0; i < 1; i++) {
      myFile.print("-Dia-");
      myFile.print("/");
      myFile.print("Fecha");
      myFile.print("/");
      myFile.print("Hora de entrada");
      myFile.print("/");
      myFile.println("Id empleado");
      myFile.print("/");
      myFile.print("Hora de salida");
    }
    // Mark the loop as executed
    loopExecuted = true;
  }


  if (myFile) {
    Serial.println("Writing date ");
    myFile.print(daysOfTheWeek[time.dayOfTheWeek()]);
    myFile.print("/");
    myFile.print(time.timestamp(DateTime::TIMESTAMP_DATE));
    myFile.print("/");
    myFile.print(time.timestamp(DateTime::TIMESTAMP_TIME));
    myFile.print("/");
    myFile.println();

    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening registro.txt");
  }
}