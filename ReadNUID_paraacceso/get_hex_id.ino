String get_hex_id() {

  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);

  Serial.println(F("A new card has been detected."));

  // Store NUID into nuidPICC array
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = mfrc522.uid.uidByte[i];
  }
  Serial.println("ID hexadecimal en string: ");

  to_string(mfrc522.uid.uidByte, mfrc522.uid.size, id_employee);
  Serial.println(" --------- ID --------- ");

  return id_employee;
}