int Green_LED = 8;
int Red_LED = 12;
int echoPin = 5;
int trigPin = 6;
long duration;
int distance;
int mouth_distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(Green_LED , OUTPUT);
  pinMode(Red_LED , OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034 / 2);
  mouth_distance =  distance;

  if (mouth_distance > 8){

    digitalWrite(Red_LED , HIGH);
    digitalWrite(Green_LED , LOW);


  } 
  else if (mouth_distance <= 8){
    digitalWrite(Red_LED , LOW);
    digitalWrite(Green_LED , HIGH);
  }


}
