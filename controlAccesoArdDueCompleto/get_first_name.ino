// String get_first_name() {
  // MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
//   MFRC522::MIFARE_Key key;
//   for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

//   //some variables we need
//   byte block;
//   byte len;
//   MFRC522::StatusCode status;

//   Serial.print(F("Name: "));

//   byte buffer1[18];

//   block = 4;
//   len = 18;

//   //------------------------------------------- GET FIRST NAME
//   status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid));  //line 834 of MFRC522.cpp file
//   if (status != MFRC522::STATUS_OK) {
//     Serial.print(F("Authentication failed: "));
//     Serial.println(mfrc522.GetStatusCodeName(status));
//     return;
//   }

//   status = mfrc522.MIFARE_Read(block, buffer1, &len);
//   if (status != MFRC522::STATUS_OK) {
//     Serial.print(F("Reading failed: "));
//     Serial.println(mfrc522.GetStatusCodeName(status));
//     return;
//   }

//   //PRINT FIRST NAME
//   for (uint8_t i = 0; i < 16; i++) {
//     if (buffer1[i] != 32) {
//       Serial.write(buffer1[i]);
//     }
//   }
//   Serial.print(" ");
// }