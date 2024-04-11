void check_out() {
  myFile = SD.open("registro.txt", FILE_WRITE);
  DateTime time = rtc.now();

  Serial.println("Hora de salida: ");
  imprimirSalida();

  if (myFile) {
    Serial.println("Writing checkout ");
    myFile.print(time.timestamp(DateTime::TIMESTAMP_TIME));
    myFile.print("/");
    myFile.println(id_employee);

    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening registro.txt");
  }
}
