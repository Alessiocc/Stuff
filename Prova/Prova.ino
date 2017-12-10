#include <TM1637Display.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const byte CLK = 52;
const byte DIO = 53;                         
TM1637Display display(CLK,DIO);              //Inizializzo il clock
LiquidCrystal_I2C lcd(0x27, 16, 2);          //Inizializzo lo schermo+

void setup() {
  Serial.begin(9600);  
  lcd.begin();
  display.showNumberDec(0,false,0,0);         //Metodo brutale per resettare il TM1637 (clock), poiche display.clear cancella tutti gli output successivi
}

void loop() {
  bool keepUp=true;
  while(keepUp){
  //lcd.clear();
  //display.showNumberDec(0,false,0,0);  
  keepUp=mainMenu();
  }
  while(1){}
}
bool mainMenu(){
  bool t=true;
  char temp;                                   //Variabile temporanea
  Serial.println("Scegli il progetto");
  Serial.println("1)Test su rampa ");
  Serial.println("2)Lancio del razzo");
  //lcd.print("Benvenuto, scegli il progetto");
  //lcd.setCursor(1,2);
  //lcd.print("[1]Test");
  //lcd.setCursor(13,2);
  //lcd.print("[2]Lancio");
  while(!Serial.available()){                  //Aspetto che venga messo un input
  } 
  temp=Serial.read();
    switch(temp){
      case '1':                                //Programma test con rampa
        menuTest();
        t=check();
        break;
      case '2':
        menuLancio();                          //Programma test di lancio  
        t=check();      
        break;
      default:
        Serial.println("Nope");
        break;
    }
  return t;
    
  
}
void menuTest(){
  //lcd.clear();
  //lcd.print("Hai selezionato il progetto rampa");
  Serial.println("Hai selezionato il progetto rampa");
  delay(1000);
  sequenzaLancio();  
}

void menuLancio(){
  //lcd.clear();
  //lcd.print("Hai selezionato il progetto lancio");
  Serial.println("Hai selezionato il progetto lancio");
  delay(1000);
  sequenzaLancio();
}

void sequenzaLancio(){
  int time;
  //lcd.setCursor(1,2);
  Serial.println("Inserire il delay prima del lancio");
  //lcd.print("Inserire il delay prima del lancio");
  while(!Serial.available()){
  }
  time=Serial.parseInt();
  for(;time>0;time--){
    Serial.println(time);
    display.showNumberDec(time);
    delay(1000);
  }
  Launch();
}

void Launch(){
    Serial.println("Launch!");  
}

bool check(){
  bool c=false;
  Serial.println("Vuoi tornare all'inizio?(Y/N)");
  while(!Serial.available()){
  }
  if(Serial.read()=='Y'){
    c=true;
  }
  else{
    c=false;
  }
  return c;
}

