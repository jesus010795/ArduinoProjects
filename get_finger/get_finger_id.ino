int get_finger_id(Adafruit_Fingerprint finger) {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return 0;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return 0;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return 0;

  // found a match!
  // Serial.print("Found ID #"); Serial.print(finger.fingerID);
  // Serial.print(" with confidence of "); Serial.println(finger.confidence);
  // return finger.fingerID;

  int id;
  id = (int)finger.fingerID;
  // Serial.println(id);
  return id;
}
