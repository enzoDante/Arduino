#define btn 8
const int pinoBuzzer = 5; //PINO DIGITAL EM QUE O BUZZER ESTÁ CONECTADO
int inches = 0;

int cm = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}



void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  pinMode(btn, INPUT);
  digitalWrite(btn, LOW);
  digitalWrite(7, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(btn) == HIGH){
    digitalWrite(7, HIGH);
  }
  //digitalWrite(7, HIGH);
  //delay(1000);

  cm = 0.01723 * readUltrasonicDistance(11, 10);
  // convert to inches by dividing by 2.54
  inches = (cm / 2.54);
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.println("cm");
  delay(100); // Wait for 100 millisecond(s)
  
  if(cm <= 30){// SE A DISTÂNCIA ENTRE O OBJETO E O SENSOR ULTRASONICO FOR MENOR QUE 50CM, FAZ
  	digitalWrite(7, HIGH);
    //tone(pinoBuzzer,400);//ACIONA O BUZZER 1500
    tone(pinoBuzzer,262,200); //DO
    delay(200);
    tone(pinoBuzzer,294,300); //RE
    delay(200);
    tone(pinoBuzzer,330,300); //MI
    delay(200);
    tone(pinoBuzzer,349,300); //FA
    delay(300);
    tone(pinoBuzzer,349,300); //FA
    delay(300);
    tone(pinoBuzzer,349,300); //FA
    delay(300);
    tone(pinoBuzzer,262,100); //DO
    delay(200);
    tone(pinoBuzzer,294,300); //RE
    delay(200);   
    tone(pinoBuzzer,262,100); //DO
    delay(200);
    tone(pinoBuzzer,294,300); //RE
    delay(300);
    tone(pinoBuzzer,294,300); //RE
    delay(300);
    tone(pinoBuzzer,294,300); //RE
    delay(300);
    tone(pinoBuzzer,262,200); //DO
    delay(200);
    tone(pinoBuzzer,392,200); //SOL
    delay(200);
    tone(pinoBuzzer,349,200); //FA
    delay(200);
    tone(pinoBuzzer,330,300); //MI
    delay(300);
    tone(pinoBuzzer,330,300); //MI
    delay(300);
    tone(pinoBuzzer,330,300); //MI
    delay(300);
    tone(pinoBuzzer,262,200); //DO
    delay(200);
    tone(pinoBuzzer,294,300); //RE
    delay(200);
    tone(pinoBuzzer,330,300); //MI
    delay(200);
    tone(pinoBuzzer,349,300); //FA
    delay(300);
    tone(pinoBuzzer,349,300); //FA
    delay(300);
    tone(pinoBuzzer,349,300); //FA
    delay(300);
  }else{//SENÃO, FAZ
    digitalWrite(7, LOW);
    noTone(pinoBuzzer);//BUZZER PERMANECE DESLIGADO
  }

  //digitalWrite(7, LOW);


  //delay(1000);
  
}
