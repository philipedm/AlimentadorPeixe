#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo motor;
const int botao = 9;
int estado_botao = 0;

int aux=0;
int giros = 1; // quantidade de giros
int cont, hora, minuto, segundo;
long qnt_horas=0;


const int buzzer = 8;//no pino 8

void setup(){
  pinMode(buzzer, OUTPUT); //do tipo saída
  pinMode(botao, INPUT); //do tipo entrada
  motor.attach(7); //no pino 7
  lcd.begin(16, 2); //lcd de 16 colunas e 2 linhas
}
void loop(){
  //girar 1 vez se apertar botão
  estado_botao = digitalRead(botao);
  if(estado_botao == LOW){
    motor.write(10);
    delay(450);
    motor.write(140);
  }
  //inicio de giro por tempo
  lcd.clear(); //limpa tela
  if(qnt_horas <= 0){ //se acabar o tempo
    if(aux>2){
      aux=1;
    }
    else{
      aux++;
    }
    lcd.setCursor(0,0); //posiciona o cursor
    lcd.print("Iniciando");
    lcd.setCursor(0,1);
    lcd.print("alimentacao...");
    
    //apita buzzer
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    motor.write(140); //posiciona motor pra cima
    delay(3000); //espera 3 segundos
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Alimentando");
    lcd.setCursor(0,1);
    lcd.print("Oscar  :)");
    
    //começa a girar o motor
    while(cont<giros){
      motor.write(10);
      delay(450);
      motor.write(140);
      delay(450);
      cont++;
    }
    cont=0; //zera o contador dos giros do motor
    qnt_horas=36000000; //incrementa 8 horas
  }
  else{ //se ainda houver tempo
    //calcula hora, minuto e segundo  
    hora = qnt_horas/3600000;
    minuto = (qnt_horas%3600000)/60000;
    segundo = (qnt_horas%60000)/1000;
    
    //escreve no display a contagem do tempo restante para a proxima alimentação
    lcd.setCursor(0,0);
    lcd.print("Tempo Restante:");
    lcd.setCursor(0,1);
    lcd.print(hora);
    lcd.setCursor(2,1);
    lcd.print(":");
    lcd.setCursor(3,1);
    lcd.print(minuto);
    lcd.setCursor(5,1);
    lcd.print(":");
    lcd.setCursor(6,1);
    lcd.print(segundo);
    lcd.setCursor(13,1);
    lcd.print(aux);
    lcd.setCursor(14,1);
    lcd.print("/");
    lcd.setCursor(15,1);
    lcd.print("2");
      
    qnt_horas = qnt_horas - 1000; // decrescenta 1 segundo da variavel
  }
  delay(985); //aguarda 1 segundo pra voltar ao inicio do loop
}
