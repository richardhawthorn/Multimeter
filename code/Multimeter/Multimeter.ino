//   Multimeter1.1
//   Richard Hawthorn
//   Cambridge Hackspace
//   Based on code from Kevin Rye
//   2015-08-08
//
//   7 segment led pixels
//
//    _____         __A__
//   |     |       F     B
//   |_____|  -->  |--G--|
//   |     |       E     C
//   |_____|       |__D__|
//
//   Characters
//    _____     _____     _____     _____ 
//   |     |   |     | . |     | o |     |
//   |_____|   |_____|   |_____|   |_____|
//   |     |   |     | . |     |   |     |
//   |_____| o |_____| o |_____| o |_____| o
//      1         2         3         4
//


//define Pins
int segmentD = 5;
int segmentE = 6;
int segmentF = 7;
int segmentA = 2;
int segmentB = 3;
int segmentC = 4;
int segmentG = 8;
int digitOne = 10;
int digitTwo = 11;
int digitThree = 12;
int digitFour = 13;
int selectButton = A0;
int decimal = A2;

int voltagePin = A4;
int currentPin = A1;

float voltage;
float current;
float value;

char mode = 'v';

int displayPause = 2;

const int meterDelay = 500;

unsigned long startMillis = millis();

//setup
void setup() {

  //pin modes
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
  pinMode(decimal, OUTPUT);
  pinMode(digitOne, OUTPUT);
  pinMode(digitTwo, OUTPUT);
  pinMode(digitThree, OUTPUT);
  pinMode(digitFour, OUTPUT);
  
  //buttons (with pullups)
  pinMode(selectButton, INPUT_PULLUP);
  
  //setup serial line for debugging
  Serial.begin(9600);
  
}





void checkVoltage(){
  
  voltage = analogRead(voltagePin);
  voltage = (voltage / 1024) * 29.00 * 100.00;
  value = voltage;
  
}

void checkCurrent(){
  
  current = analogRead(currentPin);
  current = (((current/1024.00) * 5.00) / 9.866) * 1000;
  value = current;
  
}



void checkButtons(){
  
   //select button pressed
  if (digitalRead(selectButton) == LOW) {
    //basic debounce
    delay(200);
    
    resetNumbers();
    digitalWrite(digitFour,HIGH);
    
    if (mode == 'v'){
      mode = 'c';
      digitalWrite(segmentG,LOW);  
    } else {
      mode = 'v';
      digitalWrite(segmentA,LOW);
    }
    
    delay(1000);
    resetNumbers();
    
  } 
}

//display the time
void showNum(int n) {

  //display digit X
  //digit 1 - only display if time is greater thatn 9:59
  int n1 = (n%10000)/1000;
  if (n > 999) {
    printNumber(n1,1);
  }
  delay(displayPause);
  resetNumbers();

  //digit 2
  int n2 = (n%1000)/100;
  printNumber(n2,2); 
  delay(displayPause);
  resetNumbers();

  //digit 3
  int n3 = (n%100)/10;
  printNumber(n3,3);
  delay(displayPause);
  resetNumbers();

  //digit 4
  int n4 = n%10;
  printNumber(n4,4); 
  delay(displayPause);
  resetNumbers();

}

//reset the screen, so everything is off
void resetNumbers(){
  
    digitalWrite(digitOne,LOW);
    digitalWrite(digitTwo,LOW);
    digitalWrite(digitThree,LOW);
    digitalWrite(digitFour,LOW);
    digitalWrite(decimal,HIGH);
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,HIGH);  
  
}

//output a specific number in a specific position
//n = number, d = position
void printNumber(int n, int d) {
 
  if ((n > 9) || (n < 0)){
    return;  
  }
  
  if ((d > 4) || (d < 1)){
    return;  
  }
  
  //d is the display to illuminate
  if(d==1)  {
    digitalWrite(digitOne,HIGH);
    digitalWrite(digitTwo,LOW);
    digitalWrite(digitThree,LOW);
    digitalWrite(digitFour,LOW);
    if (mode == 'c'){
      digitalWrite(decimal,LOW); //decimal on
    }
  } 

  if(d==2) {
    digitalWrite(digitOne,LOW);
    digitalWrite(digitTwo,HIGH);
    digitalWrite(digitThree, LOW);
    digitalWrite(digitFour,LOW);
    if (mode == 'v'){
      digitalWrite(decimal,LOW); //decimal on
    }
  }

  if(d==3) {
    digitalWrite(digitOne,LOW);
    digitalWrite(digitTwo,LOW);
    digitalWrite(digitThree,HIGH);
    digitalWrite(digitFour,LOW);
    //digitalWrite(decimal,HIGH); //decimal off
  }

  if(d==4) {
    digitalWrite(digitOne,LOW);
    digitalWrite(digitTwo,LOW);
    digitalWrite(digitThree,LOW);
    digitalWrite(digitFour,HIGH);
    //digitalWrite(decimal,HIGH); //decimal off
  }
 
  //n is for the number to be displayed
  switch(n) {
  case 0:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,HIGH);
    break;
    

  case 1:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,HIGH);
    break;

  case 2:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,HIGH);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,LOW);
    break;

  case 3:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,LOW);
    break;

  case 4:
    digitalWrite(segmentA,HIGH);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;

  case 5:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;

  case 6:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,HIGH);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;

  case 7:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,HIGH);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,HIGH);
    digitalWrite(segmentG,HIGH);
    break;

  case 8:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,LOW);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;

  case 9:
    digitalWrite(segmentA,LOW);
    digitalWrite(segmentB,LOW);
    digitalWrite(segmentC,LOW);
    digitalWrite(segmentD,LOW);
    digitalWrite(segmentE,HIGH);
    digitalWrite(segmentF,LOW);
    digitalWrite(segmentG,LOW);
    break;
  }
}





//main loop
void loop() {
 
  
  if (millis() - startMillis > meterDelay){
    if (mode == 'v'){
      checkVoltage();
    } else {
      checkCurrent();
    }
    
    startMillis = millis();
  }
  
  showNum(value);
  checkButtons();
  
}


