int IN1  = 13;
int IN2 = 12;
int ENA  = 5 ;
int SPEED = 210;
int echoPin = 2;
int trigPin = 3;
long duration;
int distance;
int manheight;
int temp = 0;
int movement   = 0;
int count = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(IN1 , OUTPUT);
  pinMode(IN2 , OUTPUT);
  pinMode(ENA  , OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  //Serial.begin(9600);
  //Time = (25 * distance)/11.4 ;
  //Serial.print(Time);


  digitalWrite(IN1 , LOW);
  digitalWrite(IN2 , HIGH );


  analogWrite(ENA , SPEED ) ;

  delay(1550);

  digitalWrite(IN1 , LOW) ;
  digitalWrite(IN2 , LOW ) ;


}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(IN1 , HIGH) ;
  //digitalWrite(IN2 , LOW ) ;
  //analogWrite(ENA , SPEED );
  //delay(5000);
  //digitalWrite(IN1 , LOW) ;
  //digitalWrite(IN2 , HIGH ) ;
  //analogWrite(ENA , SPEED );
  //delay(5000);


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);



  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034 / 2);
  manheight =  distance;

  if (manheight  > 40 and temp == 0) {
    if (count != 10) {
      count = count + 1;
      delay(1000);
    } else {
      digitalWrite(IN1 , HIGH);
      digitalWrite(IN2 , LOW );


      analogWrite(ENA , SPEED ) ;

      delay(1550);

      digitalWrite(IN1 , LOW) ;
      digitalWrite(IN2 , LOW ) ;

      count = 0;

    }
  } else {
    count = 0;
    if (temp == 0 and manheight > 20 and manheight < 35 and movement == 0) {

      // for moving up

      if (manheight <26 and manheight>20) {
        digitalWrite(IN1 , LOW) ;
        digitalWrite(IN2 , HIGH ) ;
        analogWrite(ENA , SPEED );
        delay(((26-manheight) / 4.01) * 1000);
        digitalWrite(IN1 , LOW) ;
        digitalWrite(IN2 , LOW );
        temp = ((26-manheight) / 4.01) * 1000;
        movement = 1;



      } else {
        //for moving down
        if (manheight > 26 and manheight < 35 ) {
          digitalWrite(IN1 , HIGH) ;
          digitalWrite(IN2 , LOW) ;
          analogWrite(ENA , SPEED );
          delay(((manheight - 26) / 4.01) * 1000);
          digitalWrite(IN1 , LOW) ;
          digitalWrite(IN2 , LOW );
          temp = ((manheight - 26) / 4.01) * 1000;
          movement = 2;

        }
      }
    } else {
      if (temp != 0 and manheight>50) {
        if (movement == 1) {
          digitalWrite(IN1 , HIGH) ;
          digitalWrite(IN2 , LOW) ;
          analogWrite(ENA , SPEED );
          delay(temp);
          digitalWrite(IN1 , LOW) ;
          digitalWrite(IN2 , LOW );
          temp = 0;
          count = 0;
          movement = 0;


        } else {
          if (movement == 2) {
            digitalWrite(IN1 , LOW) ;
            digitalWrite(IN2 , HIGH) ;
            analogWrite(ENA , SPEED );
            delay(temp);
            digitalWrite(IN1 , LOW) ;
            digitalWrite(IN2 , LOW );
            temp = 0;
            count = 0;
            movement = 0;
          }

        }

      }
    }
  }
}
