#include <Servo.h>

Servo s1;

void setup() {
 
  Serial.begin(9600);  
  s1.attach(9);        
  s1.write(90);      
  
}

void loop() {
 
  if (Serial.available() > 0) {
   
    String msg = Serial.readString();  
    int number = msg.toInt();

    if (number  > 10){

      int number1 = number - 10;

      float angle = atan((number1 * 4.5)/60);
      angle = (angle/PI)*180;
      s1.write(90 + angle);

    }
    else if (number  < 10){

      int number1 = 10 - number;
      float angle = atan((number1 * 4.5)/60);
      angle = (angle/PI)*180;
      s1.write(90 - angle);

    }
    else if (number == 10) {
      s1.write(90);
    }

    }
  
}


