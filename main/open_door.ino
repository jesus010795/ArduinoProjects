/*
*
*Activa y/o desactiva e mecanismo para abrir la puerta
*La cerradura indicara el tipo de logica
*
*/

void open_door(){
  // Serial.println(user);

  digitalWrite(solenoide, LOW);
  Serial.println("Se abre puerta");
  delay(3000);
  digitalWrite(solenoide, HIGH);
}