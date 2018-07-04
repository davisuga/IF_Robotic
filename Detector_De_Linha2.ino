//InÃ­cio do Programa
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
#include <Servo.h>
Servo s;
//Pinos sensores
int servo = 4;
int SD1 = A5;
int SE1 = A0;
//SaÃ­da AnalÃ³gica - Pinos PWM dos motores
int MD1 = 3; //Motor Direito - Pino 5
int MD2 = 5; //Motor Direito - Pino 6
int ME1 = 6; //Motor Esquerdo - Pino 10
int ME2 = 9; //Motor Esquerdo - Pino 11
int preto;
int branco;
int d = 5;
int pos;
int cmMsec;
#define ust 7
#define use 12
Ultrasonic ultrasonic(ust, use);
int vele;
int veld;
int dif;
int speedme1;
int speedmd1;
int speedpadrao = 128;
float k = 0.5;

void setup() {
  pinMode(MD1, OUTPUT); // MD1 com saÃ­da
  pinMode(MD2, OUTPUT); // MD2 com saÃ­da
  pinMode(ME1, OUTPUT); // ME1 com saÃ­da
  pinMode(ME2, OUTPUT); // ME2 com saÃ­da
  Serial.begin(9600);
  s.attach(servo);

}

void virar180() {
  freio();
  while (analogRead(SE1 = ! preto)) {
    esquerda();
  }

  while (analogRead(SD1 = ! branco)) {
    esquerda();
  }
}
void freio() {
  analogWrite(MD1, 0); //Motor Direita parado
  analogWrite(MD2, 0);
  analogWrite(ME1, 0); //Motor Esquerda parado
  analogWrite(ME2, 0);
}
void frente() {
  //robo anda pra frente
  analogWrite(MD1, 125); //Motor Direita no Sentido HorÃ¡rio
  analogWrite(MD2, 0);
  analogWrite(ME1, 125); //Motor Esquerda no Sentido HorÃ¡rio
  analogWrite(ME2, 0);

}

void esquerda() {
  //Vira o robo para a esquerda
  analogWrite(MD1, 125); //Motor Direita no Sentido HorÃ¡rio
  analogWrite(MD2, 0);
  analogWrite(ME1, 1); //Motor Esquerda no Sentido Anti-HorÃ¡rio
  analogWrite(ME2, 0);
}

void direita() {
  // Vira o robo para a Direita
  analogWrite(MD1, 1); //Motor Direita no Sentido Anti-HorÃ¡rio
  analogWrite(MD2, 0);
  analogWrite(ME1, 125); //Motor Esquerda no Sentido HorÃ¡rio
  analogWrite(ME2, 0);
}

void loop() {
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  //Frente
  int sensorE = analogRead(SE1);
  int sensorD = analogRead(SD1);
  float dist = cmMsec;
  Serial.print(sensorD);
  Serial.print(" veld ");
  Serial.print(" || ");
  Serial.print(sensorE);
  Serial.println(" vele ");
  Serial.println(dist);

  dif = sensorE - sensorD;
  //delay(2000);
//  if (dist < d) {
//    Serial.println("distÃ¢ncia curta");
//    virar180();
//
//  } 
  Serial.println("agora vamos girar o motor");
  speedme1 = speedpadrao + dif * k;
  speedmd1 = speedpadrao - dif * k;
  analogWrite(MD1, speedmd1);
  analogWrite(MD2, 0);
  analogWrite(ME1, speedme1);
  analogWrite(ME2, 0);
  Serial.println(speedmd1);
  Serial.println(speedme1);
} //Fim do Programa



