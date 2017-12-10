
#include <TM1637Display.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define tempoMinimo 5                                                       //Tempo minimo prima di accendere
const byte CLK = 52;
const byte DIO = 53;                         
TM1637Display display(CLK, DIO);                                            //Inizializzo il clock
LiquidCrystal_I2C lcd(0x27,16,2);                                           //Inizializzo lo schermo

void setup() {
  Serial.begin(9600);  
  lcd.begin();
  lcd.backlight();
}

void loop() {
  bool keepUp=true;
  while(keepUp){
  lcd.clear();
  lcd.blink();
  lcd.cursor();
  display.showNumberDec(0);
  display.setBrightness(0,false);                                         //Spengo lo schermo dell'orologio 
  keepUp=mainMenu();
  }
  while(1){}
}
bool mainMenu(){
  bool t=true;
  char temp;                                                               //Variabile temporanea
  Serial.println("Scegli il progetto");
  Serial.println("1)Test su rampa ");
  Serial.println("2)Lancio del razzo");
  lcd.print("Scegli progetto");
  lcd.setCursor(0,1);
  lcd.print("[1]Test");
  lcd.print("[2]Lancio");
  while(!Serial.available()){                                              //Aspetto che venga messo un input
  } 
  temp=Serial.read();
    switch(temp){
      case '1':                                                            //Programma test con rampa
        menuTest();
        t=check();
        break;
      case '2':
        menuLancio();                                                      //Programma test di lancio  
        t=check();      
        break;
      default:
        Serial.println("Nope");
        break;
    }
  return t;
    
  
}
void menuTest(){                                                           //Menu che si apre se scelgo il progetto test
  lcd.clear();
  lcd.print("Progetto rampa");
  Serial.println("Hai selezionato il progetto rampa");
  delay(1000);
  sequenzaLancio();  
}

void menuLancio(){                                                         //Menu che si apre se scelgo il progetto lancio
  lcd.clear();
  lcd.print("Progetto lancio");
  Serial.println("Hai selezionato il progetto lancio");
  delay(1000);
  sequenzaLancio();
}

void sequenzaLancio(){                                                     //Ho impostato il tempo minimo di lancio a 5 secondi, penso sia una precauzione necessaria 
  int time=0;
  lcd.clear();
  lcd.print("Seleziona il");
  lcd.setCursor(0,1);
  lcd.print("delay pre-lancio");
  while(time < tempoMinimo){
    Serial.println("Inserire il delay prima del lancio(Minimo 5 secondi)");
    while(!Serial.available()){
    }
    time=Serial.parseInt();
  }
  lcd.clear();
  lcd.print("Conto alla");
  lcd.setCursor(0,1);
  lcd.print("rovescia");
 display.setBrightness(7,true);                                             //Accendo lo schermo dell'orologio
  for(;time>0;time--){
    display.showNumberDec(time);
    Serial.println(time);
    
    delay(1000);
  }
  display.showNumberDec(0);
  display.setBrightness(0,false);
  lancio();
}

void lancio(){
  int i;
    Serial.println("Lancio!");
    lcd.clear();
    lcd.print("Lancio!");                                                     //Da modificiare in modo che mostri dei dati
}

bool check(){                                                                 //Parte del programma per tornare all'inizio
  bool c=false;
  Serial.println("Vuoi tornare al menu di selezione?(Y/N)");
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

