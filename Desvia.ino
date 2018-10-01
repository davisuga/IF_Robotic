#define sensorD 7
#define sensorE 3
int branco;
int preto;
#include <Servo.h> // importando biblioteca de servo motor
#include <Ultrasonic.h> // importando biblioteca do ultrassonico

#define pinoEcho 11 // definindo pino de recepcao do ultrassonico
#define pinoTrigger 12 // definindo pino de emissão do ultrassonico

#define MDF 5 // definições pinos ponte h
#define MDT 6
#define MEF 9
#define MET 10

int distancia;  
int velocidade=90; // velocidade 0-130
float velAng=25.0; 

Servo servo; // cria um obejeto Servo

float cmMsec;
long microsec;

Ultrasonic ultra(pinoTrigger,pinoEcho); // criando um objeto ultrassonico

void virar(String direcao, int graus) {
  int tempo = 900* graus/velAng;
  if (direcao == "esquerda") {
    analogWrite(MDF, velocidade);
    analogWrite(MET, velocidade);
    delay(tempo);
    analogWrite(MDF, 0);
    analogWrite(MET, 0);
  } else if (direcao == "direita") {
    analogWrite(MDT, velocidade);
    analogWrite(MEF, velocidade);
    delay(tempo+120);
    analogWrite(MDT, 0);
    analogWrite(MEF, 0);
  }
}

void frente(int tempo) {
  analogWrite(MDF, velocidade);
  analogWrite(MEF, velocidade);
  delay(tempo);
  analogWrite(MDF, 0);
  analogWrite(MEF, 0);
}

void tras(int tempo) {
  analogWrite(MDT, velocidade);
  analogWrite(MET, velocidade);
  delay(tempo);
  analogWrite(MDT, 0);
  analogWrite(MET, 0);
}



void testarCurva() {
  virar("esquerda", 90);
  delay(500);
  virar("direita", 90);
  delay(500);
  
  
}

void desviar(String direcao) {
  String direcao_oposta;
  if (direcao == "esquerda") {
    direcao_oposta = "direita";
  }
  if (direcao == "direita") {
    direcao_oposta = "esquerda";
  }
  
  virar(direcao, 90);
  delay(500);
  frente(1500);
  delay(500);
  virar(direcao_oposta, 90);
  delay(500);
  frente(1500);
  delay(500);
  virar(direcao_oposta, 90);
  delay(500);
  frente(1500);
  delay(500);
  virar(direcao, 90);
}

void setup(){

  pinMode(MDF,OUTPUT);
  pinMode(MDT,OUTPUT);
  pinMode(MEF,OUTPUT);
  pinMode(MET,OUTPUT);
//  servo.attach(13);
  servo.write(90);
  Serial.begin(9600);

}
void loop(){
  microsec = ultra.timing();
  cmMsec = ultra.convert(microsec, Ultrasonic::CM);
  
  Serial.print("Distancia em cm: ");
  Serial.println(cmMsec);
  
  delay(90);
  if (cmMsec < 21){
    desviar("esquerda");
  } 
    
  if(digitalRead(sensorE) && digitalRead(sensorD)) //Se nenhuma luz for refletida para os sensores
  {
    //Move para Trás com velocidade reduzida e aguarda 100 milissegundos
    tras(500);
  }

 

  else if(digitalRead(sensorE)) //Senão se o sensor da Esquerda detectar a linha preta
  {
    //Move para Esquerda
    virar(esquerda, 30);
  }

 

  else if(digitalRead(sensorD)) //Senão se o sensor da Direita detectar a linha preta
  {
    //Move para a Direita
    virar(direita, 30);
  } 

 

  else //Senão
  {
    //Move para Frente
    frente(300)
  }
  }

 
