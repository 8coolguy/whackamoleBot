// int dirPin = 50;
// int stepPin = 52;
// int stepState,dirState2;
// long alastUpdate,alastUpdate2;
// void stepperSetup() {
//   pinMode(dirPin, OUTPUT);
//   pinMode(stepPin, OUTPUT);
// }
// void stepper() {
//   if((millis()-alastUpdate2) > 500){
//     digitalWrite(dirPin,dirState);
//     Serial.println(digitalRead(dirPin));
//     dirState=!dirState;
//     alastUpdate2=millis();
//   }
//   if((millis()-alastUpdate) > 2){
//     digitalWrite(stepPin,stepState);
//     stepState=!stepState;
//     alastUpdate=millis();
//   }
// }