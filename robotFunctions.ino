#define DISPC .2116
#include <TimerOne.h>

volatile int counter1;
volatile int counter2;

int incomingByte; // for incoming serial data

//pins labeled pin_<object>
//1 is right 1 is A 2 is B
//2 is left
int pin_enA=51;
int pin_enB=53;
//pins for right wheel 1
int pin_in1=9;//in1
int pin_in2=8;//in2

//pins for wheel 2
int pin_in3=7;//in3
int pin_in4=6;//in4

int pin_hallL1=2;
int pin_hallL2=3;
int pin_hallR1=4;
int pin_hallR2=5;

int hL1;
int hL2;
int hR1;
int hR2;

void motorSetup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin_enA,OUTPUT);
  pinMode(pin_in1,OUTPUT);
  pinMode(pin_in2,OUTPUT);
  pinMode(pin_in3,OUTPUT);
  pinMode(pin_in4,OUTPUT);

  pinMode(pin_hallL1,INPUT);
  pinMode(pin_hallL2,INPUT);
  pinMode(pin_hallR1,INPUT);
  pinMode(pin_hallR2,INPUT);

  attachInterrupt(digitalPinToInterrupt(pin_hallL1), motorInterrupt1, RISING);
  attachInterrupt(digitalPinToInterrupt(pin_hallR1), motorInterrupt2, RISING);
}
void readHall() {
  //hall sensor reading
  hL1=digitalRead(pin_hallL1);
  hL2=digitalRead(pin_hallL2);
  hR1=digitalRead(pin_hallR1);
  hR2=digitalRead(pin_hallR2);
}
void printHall() {
  Serial.print(" hL1: ");
  Serial.print(hL1);
  Serial.print(" hL2: ");
  Serial.print(hL2);
  Serial.print(" hR1: ");
  Serial.print(hR1);
  Serial.print(" hR2: ");
  Serial.print(hR2);
  Serial.println();
}
void intermediary(){
  
  digitalWrite(pin_enA,LOW);
  digitalWrite(pin_enB,LOW);
  digitalWrite(pin_in1,LOW);
  digitalWrite(pin_in2,LOW);
  digitalWrite(pin_in3,LOW);
  digitalWrite(pin_in4,LOW);
}
void forward(){
  //set to intermidary
  //intermediary();
  
  digitalWrite(pin_in1,LOW);
  digitalWrite(pin_in2,HIGH);

  digitalWrite(pin_in3,LOW);
  digitalWrite(pin_in4,HIGH);

  digitalWrite(pin_enA,HIGH);
  digitalWrite(pin_enB,HIGH);
  
}
void reverse(){
  //set to intermidary
  
  
  digitalWrite(pin_in1,HIGH);
  digitalWrite(pin_in2,LOW);

  digitalWrite(pin_in3,HIGH);
  digitalWrite(pin_in4,LOW);

  digitalWrite(pin_enA,HIGH);
  digitalWrite(pin_enB,HIGH);

}
void brake(){
  //set to intermidary
  digitalWrite(pin_in1,HIGH);
  digitalWrite(pin_in2,HIGH);

  digitalWrite(pin_in3,HIGH);
  digitalWrite(pin_in4,HIGH);

  digitalWrite(pin_enA,LOW);
  digitalWrite(pin_enB,LOW);

}
void coast(){
  
  intermediary();

}
void turnLeft(){

  //set to intermidary
  intermediary();
  
  digitalWrite(pin_in2,HIGH);
  digitalWrite(pin_in1,LOW);

  digitalWrite(pin_enA,HIGH);
  


}
void turnRight(){

  //set to intermidary
  digitalWrite(pin_in3,LOW);
  digitalWrite(pin_in4,HIGH);

  digitalWrite(pin_enB,HIGH);

}
void pivotLeft(){
  //set to intermidary
  intermediary();

  digitalWrite(pin_in2,HIGH);
  digitalWrite(pin_in1,LOW);

  digitalWrite(pin_in3,HIGH);
  digitalWrite(pin_in4,LOW);

  digitalWrite(pin_enA,HIGH);
  digitalWrite(pin_enB,HIGH);


}
void pivotRight(){
  //set to intermidary
  intermediary();

  digitalWrite(pin_in2,LOW);
  digitalWrite(pin_in1,HIGH);

  digitalWrite(pin_in3,LOW);
  digitalWrite(pin_in4,HIGH);

  digitalWrite(pin_enA,HIGH);
  digitalWrite(pin_enB,HIGH);

}

/*Duty Cycle Motor Functions
*/
void analogIntermediary(){
  
  digitalWrite(pin_enA,LOW);
  digitalWrite(pin_enB,LOW);
  analogWrite(pin_in1,LOW);
  analogWrite(pin_in2,LOW);
  analogWrite(pin_in3,LOW);
  analogWrite(pin_in4,LOW);
}
void analogForward(int dCyc,int p){
  //set to intermidary
  int left = max(min(dCyc+p,255),0);
  int right = max(min(dCyc-p,255),0);
  //intermediary();
  // Serial.print("Left: ");
  // Serial.print(left);
  // Serial.print("Right: ");
  // Serial.print(right);

  analogWrite(pin_in1,LOW);
  analogWrite(pin_in2,right);

  analogWrite(pin_in3,LOW);
  analogWrite(pin_in4,left);

  digitalWrite(pin_enA,HIGH);
  digitalWrite(pin_enB,HIGH);
  
}
void analogReverse(int dCyc,int p){
  //set to intermidary
  int left = max(min(dCyc-p,255),0);
  int right = max(min(dCyc+p,255),0);
  
  
  analogWrite(pin_in1,right);
  analogWrite(pin_in2,LOW);

  analogWrite(pin_in3,left);
  analogWrite(pin_in4,LOW);

  digitalWrite(pin_enA,HIGH);
  digitalWrite(pin_enB,HIGH);

}

void analogTurnLeft(int dCyc){

  //set to intermidary
  intermediary();
  
  analogWrite(pin_in2,dCyc);
  analogWrite(pin_in1,LOW);

  digitalWrite(pin_enA,HIGH);
  


}
void analogTurnRight(int dCyc){

  //set to intermidary
  analogWrite(pin_in3,LOW);
  analogWrite(pin_in4,dCyc);

  digitalWrite(pin_enB,HIGH);

}
void analogPivotLeft(int dCyc){
  //set to intermidary
  intermediary();

  analogWrite(pin_in2,dCyc);
  analogWrite(pin_in1,LOW);

  analogWrite(pin_in3,dCyc);
  analogWrite(pin_in4,LOW);

  digitalWrite(pin_enA,HIGH);
  digitalWrite(pin_enB,HIGH);


}
void analogPivotRight(int dCyc){
  //set to intermidary
  intermediary();

  analogWrite(pin_in2,LOW);
  analogWrite(pin_in1,dCyc);

  analogWrite(pin_in3,LOW);
  analogWrite(pin_in4,dCyc);

  digitalWrite(pin_enA,HIGH);
  digitalWrite(pin_enB,HIGH);

}

void motorInterrupt1(){
  if(hL2){//>0 && hL1>0){
    counter1--;
  }
  else{//if(hL1>0 && hL2==0){
    counter1++;
  }
  
}
void motorInterrupt2(){
  if(hR2){//>0 && hL2>0){
    counter2++;
  }
  else{//if(hR1)>0 && hR2==0){
    counter2--;
  }
}
void cmForward(int x){
  x=x*10;
  int start = counter1;
  while(abs((counter1-start)*DISPC)<x){
    Serial.println(abs((counter1-start)*DISPC));
    forward();
  }
  coast();
  brake();
}
void cmReverse (int x){
  x=x*10;
  int start = counter1;
  while(abs((counter1-start)*DISPC)<x){
    reverse();
  } 
  coast();
  brake();
}

void cmPivotLeft (int x){
  int start = counter1;
  while(abs((counter1-start)*DISPC)<x){
    Serial.println((counter1-start)*DISPC);
    pivotLeft();
  }
  brake();
}
void cmPivotRight (int x){
  int start = counter1;
  while(abs((counter1-start)*DISPC)<x){
    pivotRight();
  } 
  brake();
}
void forwardTilLine(){
  while(abs(getPos()-3500)>1000){
    // Serial.println(abs(getPos()-3500));
    determineLine();
    forward();
  }
  coast();
  //brake();
}
