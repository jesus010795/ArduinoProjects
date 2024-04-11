int get_finger_id(Adafruit_Fingerprint finger) {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return 0;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return 0;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return 0;


  int id;
  id = (int)finger.fingerID;
  return id;
}