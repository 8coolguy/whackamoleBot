#define Bspeed 100
#define Kp 5
#define Kd 15
#define Ki 0
#define Rspeed 70
#define RKp .5
#define RKd 20
#define RKi 0
double error,int_error,prev_error,P,D,I,distance;
int motor_cmd,start,colorRead,gameState,newColor;

int dir = 50;
int step = 52;
int stepState =0;
int dirState2 =0;
long lastUpdate = 0,stepCount = 0,lastUpdate2 = 0;

void setup(){
  motorSetup();
  sensorSetup();
  colorSensorSetup();
  distanceSensorSetup();
  servoSetup();
  // stepperSetup();
  
  calibrate();
  colorRead = 2;
  gameState = 0;
  Serial.println(gameState);
}


//set duty cycle
//error modifies duty cycle
//error added to duty cycle of one motor and subtracted from the other

void loop() {
  //stepper();
  
  determineLine();
  // forwardTilLine();
  //delay(1000);
  // servoTest();
  
  //analogForward(Bspeed,0);
  //rpid();
  // 
  // Serial.println(getPos());
  // distance = readDistanceSensor();
  // printColor(readColorSensor());
  // delay(1000);
  // Serial.println(distance);
  // delay(1000);

  //pivotRight();
  // cmPivotRight(90);
  // brake();
  // delay(10000);
  

  // stepper();
  // // printColor(readColorSensor());
  
  // determineLine();
  // //servoTest();
  // //stepper();
  // newColor = fakeRead();
  
  // // pid();
  // countLines(5,8);
  // brake();
  // delay(1000);
  // color=newColor;

  // /*
  // For this to work, we need to:
  //   1. make sure the count lines function works
  //   2. measure the distance or time that it needs to rpid the first time to and go forward to reach the black start line
  //   3. Make sure servo test is able to hit the mole
  //   4.Make sure the stepper function is able to knock the quarters in.
  // */
  // /*
  // *Game State Logic
  // * 0 : Start till it hits the first wall
  // * 1 : Reverse till it is lined up in middle( measure distance ot time)
  // * 2 : Forward till hits black line
  // * 3 : Forward pid till bumper press and button press
  // * 4 : Read Color
  // * 5 : rpid till center
  // * 6 : pivot based on color reading
  // * 7 : forward pid till button then servo down and go back to state 4
  // */
  if(gameState==0){
    // stepper();
    pid();
    distance = readDistanceSensor();
    if(distance < 5){
      delay(100);
      gameState+=1;
    }
  }
  else if (gameState==1){ 
    distance = readDistanceSensor();
    rpid();//until the line 
    if(distance>14){
      cmPivotLeft(160);
      gameState+=1;
    }
    //pivotLeft or turn left
    // forward
  }
  else if(gameState==2){
    cmForward(20);
    gameState+=1;
  }
  else if (gameState==3){
    pid();//till hits button
    distance = readDistanceSensor();
    if(distance < 10)
      gameState+=1;
  }else if(gameState==4){
    distance = readDistanceSensor();
    forward();
    delay(400);
    //if(distance < 7)
    gameState+=1;

  }else if(gameState==5){
    distance = readDistanceSensor();
    rpid();//until all black
    if(distance > 40){
      cmPivotLeft(60);
      cmForward(20);
      forwardTilLine();
      gameState+=1;
    }
  }else if (gameState==6){
    distance = readDistanceSensor();
    pid();
    if(distance < 5){
      brake();
      gameState+=1;
    }
  }
  else if (gameState==7){
    newColor = printColor(readColorSensor());
    gameState = gameState +1;
  }else if(gameState==8){
    distance = readDistanceSensor();
    rpid();//until all black
    if(allBlack()){
      brake();
      gameState+=1;
    }
  }
  else if(gameState==9){
    countLines(colorRead,newColor);
    colorRead=newColor;
    brake();
    gameState = gameState + 1;
  }else if(gameState==10){
    pid();
    distance = readDistanceSensor();
    if(distance < 7)
      gameState+=1;
  }else if(gameState==11){
    servoTest();
    gameState=7;
  }

  
  /*Transition game states
  *
  *
  *
  */
  // if(distance<7){
  //   gameState+=1;
  //   if(gameState==7){
  //     servoTest();
  //     delay(1000);
  //     gameState=4;
  //   }
  // }
    
  


  

}


void pid(){
  //read cmd
  //read sensor
  prev_error = error;
  //error = cmd – sensor
  error = (getPos() - 3500)/100;
  int_error = int_error + error;
  P = Kp * error;
  D = Kd * (error - prev_error);
  I = Ki * int_error;

  //write motor_cmd
  motor_cmd = P + I + D;
  
  analogForward(Bspeed,motor_cmd);

}
void rpid(){
  //read cmd
  //read sensor
  prev_error = error;
  //error = cmd – sensor
  error = (getPos() - 3500)/100;
  int_error = int_error + error;
  P = RKp * error;
  D = RKd * (error - prev_error);
  I = RKi * int_error;

  //write motor_cmd
  motor_cmd = P + I + (.75*D)-(pow(D,5));
  
  analogReverse(Rspeed,-motor_cmd);

}

