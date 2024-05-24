double x;
int inval;
double m[6]={6.41026,13.16,20.83,26.31,41.6,55.55};
double b[6]={26.41026,38.42,49.16,55.5,70.4,82.22};
double r[6]={1.78,1.40,1.16,.97,.85,.76};
double previous_time=0.0;

void distanceSensorSetup() {
 // put your setup code here, to run once:
 Serial.begin(9600);
//  analogReference(INTERNAL1V1);
 pinMode(A0,INPUT);
}
//function to determine distance from wall using piecewise linear function
double vToC(double v){
 if(v >= r[0]){ //10 cm
   return -1*m[0]*v+b[0];
 }else if(r[0] > v && v >= r[1]){ //15cm
  //  Serial.println(1);
   return -1*m[1]*v+b[1];
 }else if(r[1] > v && v >= r[2]){ //20cm
  //  Serial.println(2);
   return -1*m[2]*v+b[2];
 }else if(r[2] > v && v >= r[3]){ //25cm
  //  Serial.println(3);
   return -1*m[3]*v+b[3];
 }else if(r[3] > v && v >= r[4]){ //30cm
  //  Serial.println(4);
   return -1*m[4]*v+b[4];
 }else if(r[4] > v && v >= r[5]){ //35cm
  //  Serial.println(5);
   return -1*m[5]*v+b[5];
 }else if(r[5] > v){ //40cm
  //  Serial.println(5);
   return -1*m[5]*v+b[5];
 }
 return -1;
}

double readDistanceSensor() {
  inval = analogRead(A0);
  //Serial.println(inval);
  //code to output distance from wall with serial monitor on button press
  
  x = ((double)inval) * (5.0 / 1023.0);
  // Serial.print((double)inval);
  // Serial.print(" ");
  // Serial.print(x);
  // Serial.print(" ");
  // Serial.println(vToC(x));
  double firstReading =vToC(x);
  return firstReading;
}
