/*
*
*Activa y/o desactiva e mecanismo para abrir la puerta
*La cerradura indicara el tipo de logica
*
*/

void open_door(){  
  digitalWrite(solenoide, LOW);
  Serial.println("Puerta abierta");
  recording();
  delay(5000);
  digitalWrite(solenoide, HIGH);
}