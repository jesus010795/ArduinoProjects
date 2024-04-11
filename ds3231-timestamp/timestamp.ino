void timestamp(){
  DateTime time = rtc.now();

  Serial.println(daysOfTheWeek[time.dayOfTheWeek()]);
  Serial.println(String("DateTime::TIMESTAMP_DATE:\t")+time.timestamp(DateTime::TIMESTAMP_DATE));

 //Full Timestamp
  Serial.println(String("DateTime::TIMESTAMP_TIME:\t")+time.timestamp(DateTime::TIMESTAMP_TIME));

  Serial.println("\n");
}