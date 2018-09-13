  float cmMec;
// Antonio Mendes M. Jr
// Projeto Wee v1.0 21/05/2014

#include <Servo.h> // importando biblioteca de servo motor
#include <Ultrasonic.h> // importando biblioteca do ultrassonico

#define pinoRecep 11 // definindo pino de recepcao do ultrassonico
#define pinoEmiss 12 // definindo pino de emissão do ultrassonico

#define IN1 5 // definições pinos ponte h
#define IN2 6
#define IN3 9
#define IN4 10

#define ENA 10
#define ENB 11 // fim definição ponte h.

const int velocidade=255; // velocidade 0-255

const float velang=16.7; // definindo velocidade angular media 16,7ms por grau

Servo servo; // cria um obejeto Servo
Ultrasonic ultra(pinoEmiss,pinoRecep); // criando um objeto ultrassonico

void setup(){
  Serial.begin(9600);
  pinMode(pinoEmiss,OUTPUT);
  pinMode(pinoRecep,INPUT);
  servo.attach(2); // relacionando servo físico com virtual
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  //pinMode(ENA,OUTPUT);
  //pinMode(ENB,OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(3000); // delay p/ posicionar o robô  
  servo.write(100);
  servo.write(0);
}

void loop(){
  delay(200);
  //int distancia = 0; // "limpa" a varíavel
  //delayMicroseconds(10); // espera 5 microsegundos  
  long microsec = ultrasonic.timing();
  distancia = ultrasonic.convert(microsec, Ultrasonic::CM);  if (distancia>=40){// canculando distancia em cm
  delayMicroseconds(10); // espera 5 microsegundos  
  
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
  delay(2000);

  long microsec = ultrasonic.timing();
  distancia = ultrasonic.convert(microsec, Ultrasonic::CM);  if (distancia>=40){
    servo.write(90);
    viraresquerda(90); // vira 90 graus pra esquerda
    delay(100);
  } 
  else if (distancia<40) {
    servo.write(165); // servo vira para 165 graus
    delay(2000);
    long microsec = ultrasonic.timing();
    distancia = ultrasonic.convert(microsec, Ultrasonic::CM);  if (distancia>=40){
    if (distancia>=40){
      servo.write(90);
      virardireita(70); //vira 90 graus pra direita
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
void viraresquerda(int angulo){
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
void virardireita(int angulo){
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
    viraresquerda(170); // vira pela esquerda em 180 graus
  }
  else {
    virardireita(160); // vira pela esquerda em 180 graus
  }
}
