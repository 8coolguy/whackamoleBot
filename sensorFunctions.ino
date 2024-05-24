#include <QTRSensors.h>



QTRSensors qtr;
int whiteButton = 11;
int startButton = 12;

const int SensorCount = 8;
int sensorValues[SensorCount];
int tempStore[100];
int blackValues[SensorCount];
int whiteValues[SensorCount];
int lightState[SensorCount];
int pos;
int lights[] ={36,38,40,42,44,46,48,50};



void sensorSetup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){29, 31, 33, 37, 39, 41, 43, 45}, SensorCount);
  qtr.setEmitterPin(27);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // turn on Arduino's LED to indicate we are in calibration mode


  pinMode(whiteButton,INPUT_PULLUP);
  pinMode(startButton,INPUT_PULLUP);

  for(int i=0;i<8;i++)
    pinMode(lights[i],OUTPUT);
  

}

void calibration(){
  while(1)
  {
    if(digitalRead(whiteButton)==LOW){
      calibrateBlack();
      Serial.println("Black Calibrated");
      break;
    }
  }
  delay(1500);
  while(1){
    if(digitalRead(startButton)==LOW){
      calibrateWhite();
      Serial.println("White Calibrated");
      break;
    }
  }
  while(digitalRead(25)==HIGH)
    Serial.println("Press Again to Start");

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum
  // reflectance and 1000 means minimum reflectance, followed by the line
  // position
}
void calibrate(){
  while(1){
    if(digitalRead(whiteButton)==LOW){
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Calibration Started");
      for (int i = 0; i < 200; i++){
        qtr.calibrate();
      }
      break;
    }
  }
  Serial.print("White Calibrated: ");
  for (int i = 0; i < SensorCount; i++){
    whiteValues[i]=qtr.calibrationOn.minimum[i];
    Serial.print(whiteValues[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  Serial.print("Black Calibrated: ");
  for (int i = 0; i < SensorCount; i++)
  {
    blackValues[i]=qtr.calibrationOn.maximum[i];
    Serial.print(blackValues[i]);
    Serial.print(' ');
  }
  Serial.println();
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Press Again to Start");
  
  while(digitalRead(startButton)==HIGH)
    delay(1);
  Serial.println("Started");
}

int average(int array[]){
  int sum = 0;  // sum will be larger than an item, long for safety.
  for (int i = 0; i < 10; i++)
    sum += array [i];
  return  sum / 10 ;  // average will be fractional, so float may be appropriate.
}
void calibrateBlack(){
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    for(int j=0; j<10;j++){
      // for (uint8_t i = 0; i < SensorCount; i++)
      // {
      //   Serial.print(sensorValues[i]);
      //   Serial.print("\t");
      // }
      // Serial.println();
      qtr.read(sensorValues);
      tempStore[j]=sensorValues[i];
    }
    blackValues[i] = average(tempStore);
  }
  Serial.println();
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(blackValues[i]);
    Serial.print("\t");
  }
  Serial.println();

  delay(250);
}
void calibrateWhite(){
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    for(int j=0; j<10;j++){
      // for (uint8_t i = 0; i < SensorCount; i++)
      // {
      //   Serial.print(sensorValues[i]);
      //   Serial.print("\t");
      // }
      // Serial.println();
      qtr.read(sensorValues);
      tempStore[j]=sensorValues[i];
    }
    whiteValues[i] = average(tempStore);
  }
  Serial.println();
  

  delay(250);
}
void determineLine(){
  pos = qtr.readLineBlack(sensorValues);
  for(int i=0;i<SensorCount;i++){
    int mid = (blackValues[i]-whiteValues[i])/2;
    // Serial.print(sensorValues[i]*2.5);
    // Serial.print(" ");
    if(sensorValues[i]*2.5 > mid)
      lightState[i]=LOW;
    else
      lightState[i]=HIGH;
    digitalWrite(lights[i],lightState[i]);
  }
}

int getLight(int i){
  return lightState[i-1];
}
int getPos(){
  return pos;
}
int countLines(int state, int nextState){
  int modifier=0;
  int count = abs(nextState -state);
  Serial.println(count);
  if(state==6 && nextState==4)
    modifier=-12;
  else if(state==0 && nextState==4)
    modifier=-20;
  if(nextState > state)
    cmPivotRight(count*55);
  else if (nextState < state)
    cmPivotLeft(count*55);
  
  
}
bool allBlack(){
  for(int i=0;i<SensorCount;i++){
    // Serial.println(sensorValues[i]);
    if(sensorValues[i]/100!=blackValues[i]/250)
      return false;
  }
  return true;
}
