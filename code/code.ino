const int trigPin = 9;   
const int echoPin = 10;  
const int linePin = 2;   

const int AIN1 = 4;
const int AIN2 = 5;
const int BIN1 = 6;
const int BIN2 = 7;

long duration;
int distance;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(linePin, INPUT);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
  stopRobot();
  delay(5000); 
}

void loop() {
  distance = getDistance();
  int lineStatus = digitalRead(linePin);

  if (lineStatus == LOW) { 
    moveForward();
  } 
  else {
    if (distance > 0 && distance <= 40) {
      moveForward();
    }
    else {
      spinRight(); 
    }
  }
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  int d = duration * 0.034 / 2;
  
  if (d <= 0 || d > 400) return 400; 
  return d;
}

void moveForward() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void spinRight() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void stopRobot() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}
