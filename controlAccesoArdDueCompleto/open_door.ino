void open_door(){
  digitalWrite(LOCK, LOW);
  delay(5000);
  digitalWrite(LOCK, HIGH);
}