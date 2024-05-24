#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);


double rgbV[6][3] = {
 {40.9,135.3,56.4},//green
 {30.0,60.0,150.0}, //blue
 {57.0,83.0,106.0},//white
 {150.0,59.0,60.0}, // red
 {40.0,53.0,134.0}, // purple
 {120.0,84.0,44.0}, ///yellow
};
double v[3];


void colorSensorSetup(void) {
  Serial.begin(9600);
  Serial.println("Finding Sensor");
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
  }

  // Now we're ready to get readings!
}
/*
* This funciton reads the color and returns an integer determinging what color 
*
*/
int readColorSensor(void) {
  float r, g, b;

  tcs.getRGB(&r, &g, &b);
  v[0]=r;
  v[1]=g;
  v[2]=b;

  // Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  // Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  // Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  // Serial.println(" ");

  float minDis =100000.0;
  int color=0;
  for(int i = 0; i < 6; i++){
     float dis = eucDis(rgbV[i],v);
     if(dis<minDis){
       color=i;
       minDis=dis;
     }
  }
  return color;
}
/*
*Calculates magnitude of vector
*
*/
double magnitude(double vector[]){
 double res=0.0;
 for(int j=0;j<3;j++){
   res= res + pow((double)vector[j],2);
 }
 return sqrt(res);
}
/*
*Calculates dot product of vectors
*
*/
double dotProduct(double a[],double b[]){
 double res=0;
 for(int j=0;j<3;j++){
   res= res + a[j] * b[j];
 }
 return res;
}
/*
*Calcualtes cosSim of 2 vecotrs
*
*/
double cosSim(double a[],double b[]){
 double top =dotProduct(a,b);
 double bottom=magnitude(a)*magnitude(b);
 return top/bottom;
}
/*
* Calculates tbe euclidian Distance between two vectores
*
*/
double eucDis(double a[],double b[]){
 double res=0.0;
 for(int j=0;j<3;j++){
   res= res + pow(a[j]-b[j],2);
 }
 return sqrt(res);
}
int printColor(int color){
  switch(color){
     case 0: //black
     {
       Serial.println("Green");
       return 0;
       break;
     }

     case 1: //blue
     {
       Serial.println("Blue");
       return 1;
       break;
     }
     case 2: //green
     {
       Serial.println("White");
       return 2;
       break;
     }

     case 3: //red
     {
       Serial.println("Red");
       return 4;
       break;
     }

     case 4: //white
     {
       Serial.println("Purple");
       return 5;
       break;
     }
     case 5: //purple
     {
       Serial.println("Yellow");
       return 6;
       break;
     }
   }
}
int fakeRead(){
  return random(0,7);
}