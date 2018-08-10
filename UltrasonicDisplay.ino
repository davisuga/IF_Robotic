//Codigo que coloca no display a distância registrada no sensor ultrasônico
#include <LiquidCrystal.h> //inclui biblioteca 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //pinos utilizados na comunicacao entre arduino e display 
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
#define pino_trigger 7
#define pino_echo 8

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
}

void loop()
{
  lcd.setCursor(0, 0);
  //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  //Exibe informacoes no serial monitor
  lcd.print(cmMsec);
  lcd.setCursor(0, 1);
  lcd.print(inMsec);
  Serial.println(inMsec);
  delay(500);
  lcd.clear()
}
