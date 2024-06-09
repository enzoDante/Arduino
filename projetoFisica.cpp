#include <Servo.h> // Essa biblioteca é nativa da plataforma

// Configuração do sensor de distância com timeout de 40 ms
int trigger = 8;
int echo = 9;
float v = 331.5 + 0.6 * 20; //  m/s

// Configuração do Servo
Servo meuServo;

void setup() {
// Inicializar o Servo
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  meuServo.attach(7);
  meuServo.write(0);
  delay(100);
}
float distanceCm(){
    digitalWrite(trigger, LOW);
    delayMicroseconds(3);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigger,LOW);
    
    float tUs = pulseIn(echo, HIGH);
    float t = tUs / 1000.0 / 1000.0 / 2.0;
    float d = t*v;
    return d*100;
}

void loop() {

  int menorDistancia;
  int distancia;
  int angulo;
  int meuAngulo;

  meuAngulo = 0;
  meuServo.write(0);
  delay(50);
  menorDistancia = 100; // Precisão do sensor vai até 100 cm

  // Inicia varredura em 180 graus de 5 em 5
  for (angulo = 0; angulo <= 180; angulo += 5) {

    // Posiciona o servo em cada ângulo
    meuServo.write(angulo);

    // Ler a distância
    distancia = distanceCm();
    Serial.print(distancia);
    Serial.println();
    // Verificar a menor distância, desprezando leituras inválidas
    if ((distancia > 0) && (distancia < 100) && (distancia < menorDistancia)) {
      menorDistancia = distancia;
      meuAngulo = angulo;
    }

    delay(100); //Pausa para a próxima leitura
  }
  delay(1000);

  for (angulo = 180; angulo >= meuAngulo; angulo -= 5) {
    meuServo.write(angulo);
    delay(100);
  }
  delay(5000);
}