/*
*Registrara la hora de entrada
*
*timestamp: Devuelve la hora y fecha en la que se ingreso
*Con la libreria SD almacenaremos la hora de entrada en un archivo txt
*/

void register_entry(){
  // get_time();
  Serial.println("Hora de entrada: ");
  timestamp();
  delay(1000);
  Serial.println("Registro de entrada");
}