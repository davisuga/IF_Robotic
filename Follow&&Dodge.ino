//Início do Programa
#include <Servo.h>
Servo s;
int pinoEmiss = 11;
int pinoRecep=12;
#include <Ultrasonic.h> // importando biblioteca do ultrassonico
#define pinoRecep 3 // definindo pino de recepcao do ultrassonico
#define pinoEmiss 2 // definindo pino de emissão do ultrassonico
Ultrasonic ultra(pinoEmiss,pinoRecep); // criando um objeto ultrassonico

//Pinos sensores
int servo = 4;
int us = A5;
int SD1 = A0;
int SE1 = A1;
//Saída Analógica - Pinos PWM dos motores
int MD1 = A4; //Motor Direito - Pino 5
int MD2 = A3; //Motor Direito - Pino 6
int ME1 = A2; //Motor Esquerdo - Pino 10
int ME2 = A1; //Motor Esquerdo - Pino 11
int preto;
int branco;
int d;
int pos;

void setup() {
  pinMode(MD1, OUTPUT); // MD1 com saída
  pinMode(MD2, OUTPUT); // MD2 com saída
  pinMode(ME1, OUTPUT); // ME1 com saída
  pinMode(ME2, OUTPUT); // ME2 com saídau
  Serial.begin(9600);
  s.attach(servo);
  pinMode(pinoEmiss,OUTPUT);
  pinMode(pinoRecep,INPUT);
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
// void freio(){
//   analogWrite(MD1, 0); //Motor Direita parado
//   analogWrite(MD2, 0);
//   analogWrite(ME1, 0); //Motor Esquerda parado
//   analogWrite(ME2, 0);
//   }
// void frente(){
//   //robo anda pra frente
//   analogWrite(MD1, 128); //Motor Direita no Sentido Horário
//   analogWrite(MD2, 0);
//   analogWrite(ME1, 128); //Motor Esquerda no Sentido Horário
//   analogWrite(ME2, 0);

//   }
  
// void esquerda(){
//      //Vira o robo para a esquerda
//     analogWrite(MD1, 128); //Motor Direita no Sentido Horário
//     analogWrite(MD2, 0);
//     analogWrite(ME1, 50); //Motor Esquerda girando devagar
//     analogWrite(ME2, 0);
//   }
  
// void direita(){
//     // Vira o robo para a Direita
//     analogWrite(MD1, 50); //Motor Direita girando devagar
//     analogWrite(MD2, 0);
//     analogWrite(ME1, 128); //Motor Esquerda no Sentido Horário
//     analogWrite(ME2, 0);
//   }
  
void loop() {
  //Frente
  int sensorE = analogRead(SE1);
  int sensorD = analogRead(SD1);
  int dist = analogRead(us);
  Serial.println(sensorD);
  Serial.println(sensorE);
  //delay(2000);

  if (dist < d){
    virar180();
    
    }
  //Direita
  if ((sensorE <= preto ) && (sensorD >= branco)) {
    direita();
  }
  //Esquerda
  if ((sensorE >= preto) && (sensorD <= branco)) {
    esquerda();
  }

  frente();
delay(200);
  //int distancia = 0; // "limpa" a varíavel
  //delayMicroseconds(10); // espera 5 microsegundos  
  float cmMsec, inMsec;
  long microsec = ultra.timing();
  int distancia = ultra.convert(microsec, Ultrasonic::CM);
  delay(5); // espera 5 microsegundos  
  
  Serial.println(distancia);

  if(distancia>=30 || distancia==0){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    //analogWrite(ENA,velocidade);
    //analogWrite(ENB,velocidade);
  }
  else if(distancia<30 && distancia>0){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    //analogWrite(ENA, velocidade);
    //analogWrite(ENB, velocidade);
    Busca(); //chama funcao Busca
  }
}

// função busca (vai procurar por um caminho sem obstáculos)
void Busca(){
  servo.write(15); // servo vira para 15 graus
  delay(2000);;
  long microsec = ultra.timing();
  int distancia = ultra.convert(microsec, Ultrasonic::CM);
  if (distancia>=40){
    servo.write(90);
    esquerda(90); // vira 90 graus pra esquerda
    delay(100);
  } 
  else if (distancia<40) {
    servo.write(165); // servo vira para 165 graus
    delay(2000);
    long microsec = ultra.timing();
    int distancia = ultra.convert(microsec, Ultrasonic::CM);
    if (distancia>=40){
      servo.write(90);
      direita(70); //vira 90 graus pra direita
      delay(100);
    }
    if (distancia<40){
      servo.write(90);
      meiavolta(); //chama função meiavolta
      delay(100);
    }
  }   
}

// função para virar a esquerda
void esquerda(int angulo){
  delay(100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //analogWrite(ENA, 50);
  //analogWrite(ENB, 0);
  delay(angulo*velang);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// função para virar a direita
void direita(int angulo){
  delay(100);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  //analogWrite(ENA, 0);
  //analogWrite(ENB, 50);
  delay(angulo*velang);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// função para dar meia volta
void meiavolta(){
  delay(100);
  int aux=round(random(0,10)); // definir pra que lado virar na meia volta
  if (aux<=5){
    esquerda(170); // vira pela esquerda em 180 graus
  }
  else {
    direita(160); // vira pela esquerda em 180 graus
  }
}

