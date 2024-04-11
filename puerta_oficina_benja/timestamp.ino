void timestamp(){
  DateTime time = rtc.now();
  Serial.println(daysOfTheWeek[time.dayOfTheWeek()]);
  Serial.println(time.timestamp(DateTime::TIMESTAMP_DATE));
  Serial.println(time.timestamp(DateTime::TIMESTAMP_TIME));
}