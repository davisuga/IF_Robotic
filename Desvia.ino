
// Antonio Mendes M. Jr
// Projeto Wee v1.0 21/05/2014

#include <Servo.h> // importando biblioteca de servo motor
#include <Ultrasonic.h> // importando biblioteca do ultrassonico

#define pinoEcho 11 // definindo pino de recepcao do ultrassonico
#define pinoTrigger 12 // definindo pino de emissão do ultrassonico

#define MDF 5 // definições pinos ponte h
#define MDT 6
#define MEF 9
#define MET 10
int distancia;  

const int velocidade=130; // velocidade 0-255

const float velAng=40; //ESSA PORRA  40 VIU

Servo servo; // cria um obejeto Servo

float cmMsec;
long microsec;

Ultrasonic ultra(pinoTrigger,pinoEcho); // criando um objeto ultrassonico

void virar(String direcao, int graus) {
  int tempo = 1000* graus/velAng;
  if (direcao == "esquerda") {
    analogWrite(MEF, velocidade);
    analogWrite(MDT, velocidade);
    delay(tempo);
    analogWrite(MEF, 0);
    analogWrite(MDT, 0);
  } else if (direcao == "direita") {
    analogWrite(MDF, velocidade*0.9);
    analogWrite(MET, velocidade*0.9);
    delay(tempo);
    analogWrite(MDF, 0);
    analogWrite(MET, 0);
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
  int servo_direcao;
  if (direcao == "esquerda") {
    direcao_oposta = "direita";
    servo_direcao = 0;
  }
  if (direcao == "direita") {
    direcao_oposta = "esquerda";
    servo_direcao = 180;
  }
  
  virar(direcao, 90);
  delay(500);
  servo.write(servo_direcao);
  
  microsec = ultra.timing();
  cmMsec = ultra.convert(microsec, Ultrasonic::CM);
  while(cmMsec <= 20 && cmMsec >= 0) {
    frente(500);
    microsec = ultra.timing();
    cmMsec = ultra.convert(microsec, Ultrasonic::CM);
  }
  frente(1000);

  delay(500);
  virar(direcao_oposta, 90);
  delay(500);
  
  microsec = ultra.timing();
  cmMsec = ultra.convert(microsec, Ultrasonic::CM);
  while(cmMsec > 20) {
    frente(500);
    microsec = ultra.timing();
    cmMsec = ultra.convert(microsec, Ultrasonic::CM);
  }
  
  microsec = ultra.timing();
  cmMsec = ultra.convert(microsec, Ultrasonic::CM);
  while(cmMsec <= 20 && cmMsec >= 0) {
    frente(500);
    microsec = ultra.timing();
    cmMsec = ultra.convert(microsec, Ultrasonic::CM);
  }
  frente(1000);
  
  delay(500);
  virar(direcao_oposta, 90);
  delay(500);
  virar(direcao, 90);
}

void setup(){

  Serial.println('passeo');
  pinMode(MDF,OUTPUT);
  pinMode(MDT,OUTPUT);
  pinMode(MEF,OUTPUT);
  pinMode(MET,OUTPUT);
  servo.attach(3);
  servo.write(90);
  Serial.begin(9600);

}
void loop(){
  microsec = ultra.timing();
  cmMsec = ultra.convert(microsec, Ultrasonic::CM);
  
  Serial.println('vrau');
  Serial.print("Distancia em cm: ");
  Serial.print(cmMsec);
  
  delay(500);
  
  testarCurva();
  
  /*
  if (cmMsec <= 20 && cmMsec >= 0) {
    desviar("esquerda");
  } else if (cmMsec > 20) {
    frente(500);
  }
  */
 }
