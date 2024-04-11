void timestamp() {
  DateTime time = rtc.now();

  Serial.print(daysOfTheWeek[time.dayOfTheWeek()]);
  Serial.print("/");
  Serial.print(time.timestamp(DateTime::TIMESTAMP_DATE));
  Serial.print("/");
  Serial.print(time.timestamp(DateTime::TIMESTAMP_TIME));
  Serial.print("/");
  Serial.println(id_employee);
  // Serial.print("/");

  Serial.print("Minuto: ");
  Serial.println(time.minute());
}

void imprimirSalida(){
  DateTime time = rtc.now();
  Serial.println(time.timestamp(DateTime::TIMESTAMP_TIME));
}