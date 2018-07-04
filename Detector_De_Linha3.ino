//Início do Programa
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
#include <Servo.h>
Servo s;
//Pinos sensores
int servo = 4;
#define ust 7
#define use 12
Ultrasonic ultrasonic(ust, use);
int SD1 = A5;
int SE1 = A0;
//Saída Analógica - Pinos PWM dos motores
int MD1 = 3; //Motor Direito - Pino 5
int MD2 = 5; //Motor Direito - Pino 6
int ME1 = 6; //Motor Esquerdo - Pino 10
int ME2 = 9; //Motor Esquerdo - Pino 11
int preto;
int branco;
int d = 0;
int pos;
int vele;
int veld;


void setup() {
  pinMode(MD1, OUTPUT); // MD1 com saída
  pinMode(MD2, OUTPUT); // MD2 com saída
  pinMode(ME1, OUTPUT); // ME1 com saída
  pinMode(ME2, OUTPUT); // ME2 com saídau
  Serial.begin(9600);
  s.attach(servo);
}

void virar180(){
  freio();
  while(analogRead(SE1 =! preto)){
    esquerda();
    }
  
  while(analogRead(SD1 =! branco)){
    esquerda();
    }
}
void freio(){
  analogWrite(MD1, 0); //Motor Direita parado
  analogWrite(MD2, 0);
  analogWrite(ME1, 0); //Motor Esquerda parado
  analogWrite(ME2, 0);
  }
void frente(){
  //robo anda pra frente
  analogWrite(MD1, 128); //Motor Direita no Sentido Horário
  analogWrite(MD2, 0);
  analogWrite(ME1, 128); //Motor Esquerda no Sentido Horário
  analogWrite(ME2, 0);

  }
  
void esquerda(){
     //Vira o robo para a esquerda
    analogWrite(MD1, 128); //Motor Direita no Sentido Horário
    analogWrite(MD2, 0);
    analogWrite(ME1, 50); //Motor Esquerda girando devagar
    analogWrite(ME2, 0);
  }
  
void direita(){
    // Vira o robo para a Direita
    analogWrite(MD1, 50); //Motor Direita girando devagar
    analogWrite(MD2, 0);
    analogWrite(ME1, 128); //Motor Esquerda no Sentido Horário
    analogWrite(ME2, 0);
  }
  
void loop() {
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  //Frente
  int sensorE = analogRead(SE1);
  int sensorD = analogRead(SD1);
  int dist = cmMsec;
  Serial.print(sensorD);
  Serial.print(" veld ");
  Serial.print(" || ");
  Serial.print(sensorE);
  Serial.println(" vele ");
  Serial.println(dist);
  //delay(2000);
 /* for(pos = 0; pos < 90; pos++){
    s.write(pos);
    delay(15);
    } */
//  if (dist < d){
//    virar180();
//    
//    }else{
    Serial.println("agora vamos girar o motor");

    analogWrite(MD1, 120); //Motor Direita girando devagar
    analogWrite(MD2, 0);
    analogWrite(ME1, 120); //Motor Esquerda no Sentido Horário
    analogWrite(ME2, 0);
//    }
 } //Fim do Programa

