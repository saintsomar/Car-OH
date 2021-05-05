#include <LiquidCrystal.h>
#include <DS1302.h>
LiquidCrystal lcd(53, 51, 49, 47, 45, 43);
DS1302 rtc(25, 27, 29);
int v=36, a=34, r=32;
int d=38, m=30;
int in=26, ou=28;
int ve= 150, am=300, ro=400;                  
float valor_alcohol;    
#define PIN_TRIG 41
#define PIN_ECO  39
#define DS1302_GND_PIN 31
#define DS1302_VCC_PIN 33
                             
void setup() { 
  digitalWrite(d,HIGH);//asegurar el rebote de monoestable al comenzar
  Serial.begin(9600);
  pinMode(in, INPUT);//entrada del motor
  pinMode(ou, OUTPUT);//Salida del motor
  pinMode(v,OUTPUT);//VERDE                  
  pinMode(a, OUTPUT);//AMARILLO
  pinMode(r, OUTPUT);//rojo
  pinMode(d,OUTPUT);//trigger de monoestable
  pinMode(m, INPUT);//monoestable
  
 
  digitalWrite(ou,LOW);//Bloquear el motor
  
  digitalWrite(DS1302_GND_PIN, LOW);
  pinMode(DS1302_GND_PIN, OUTPUT);
  digitalWrite(DS1302_VCC_PIN, HIGH);
  pinMode(DS1302_VCC_PIN, OUTPUT);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECO, INPUT); 

  //configuracion del rtc
  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setTime(18, 16, 30);     // Hora (formato 24)
  rtc.setDate(29, 11, 2016);   // Dia, mes, año
 
  lcd.begin(16, 2);
  valor_alcohol=0;
}
 

void loop() { 
  delay(2);
  digitalWrite(d,HIGH); 
  valor_alcohol=0;
  lcd.setCursor(0,0 );
  lcd.print(rtc.getDateStr());
  lcd.setCursor(11, 0);
  lcd.print(rtc.getTimeStr());
  delay (100);
  
           //ULTRASONICO
  long duracion, distancia;  // Variables
  /* Hacer el disparo */
  digitalWrite(PIN_TRIG, LOW);  
  delayMicroseconds(2); 
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  /* Recepcion del eco de respuesta */
  duracion = pulseIn(PIN_ECO, HIGH);
  /* Calculo de la distancia efectiva */
  distancia = (duracion/2) / 29;
   /* Imprimir resultados a la terminal serial */
   Serial.print(distancia);
   Serial.println("cm");
  if (distancia <=12 ){
    digitalWrite(d,LOW);
    delay(100);
    digitalWrite(d, HIGH);
  }
  else {
    digitalWrite(d,HIGH);
  }  
      while( digitalRead(m)==HIGH){
      valor_alcohol=analogRead(A0); 
      Serial.println(valor_alcohol);
      Serial.println(' ');   
      float porcentaje=(valor_alcohol/10000);  
      Serial.println(porcentaje);            
      lcd.begin(16, 2);
      lcd.setCursor(3,1); 
      lcd.write("Cargando...");
      lcd.setCursor(0,0 );
      lcd.print(rtc.getDateStr());
      lcd.setCursor(11, 0);
      lcd.print(rtc.getTimeStr());
      delay (500);
      }
      if (valor_alcohol >= ro){
       digitalWrite(v, LOW);
       digitalWrite(a, LOW);
       digitalWrite(r, HIGH);
       digitalWrite(ou,LOW);
  lcd.begin(16, 2);
  lcd.setCursor(0,0 );
  lcd.print(rtc.getDateStr());
  lcd.setCursor(11, 0);
  lcd.print(rtc.getTimeStr());
  delay (500);

  
  lcd.setCursor(0,1); 
  lcd.write("ALCOHOL:"); 
  lcd.setCursor(9,1); 
  float porcentaje=(valor_alcohol/1000);  
  lcd.print(porcentaje);
  lcd.setCursor(14,1); 
  lcd.write((char)223);
       
       
  delay (2500);

  lcd.begin(16, 2);
  lcd.setCursor(7, 0);
  lcd.write("NO");
  lcd.setCursor(5, 1);
  lcd.write("MANEJE");
 
  delay (2500);
  
  lcd.begin(16,1);
   digitalWrite(v, LOW);
   digitalWrite(a, LOW);
   digitalWrite(r, LOW);
  
   valor_alcohol=0;
} 
if (valor_alcohol >= am){
       digitalWrite(v, LOW);
       digitalWrite(a, HIGH);
       digitalWrite(r, LOW);
       digitalWrite(ou,HIGH);
       
  lcd.begin(16, 2);

  lcd.setCursor(0,0 );
  lcd.print(rtc.getDateStr());
  lcd.setCursor(11, 0);
  lcd.print(rtc.getTimeStr());
   delay (1000);
  lcd.setCursor(0,1); 
  lcd.write("ALCOHOL:"); 
  lcd.setCursor(9,1); 
  float porcentaje=(valor_alcohol/1000);  
  lcd.print(porcentaje);
  lcd.setCursor(14,1); 
  lcd.write((char)223);

  delay (2500);
  
  lcd.begin(16, 2);
  lcd.setCursor(6, 0);
  lcd.write("TOME");
  lcd.setCursor(2, 1);
  lcd.write("PRECAUCIONES");
  
  delay (2500);
  
  lcd.begin(16,1);
  digitalWrite(v, LOW);
  digitalWrite(a, LOW);
  digitalWrite(r, LOW);
       

  
       valor_alcohol=0;
}
if (valor_alcohol >= ve){
       digitalWrite(v, HIGH);
       digitalWrite(a, LOW);
       digitalWrite(r, LOW);
       digitalWrite(ou,HIGH);
  lcd.begin(16, 2);

  lcd.setCursor(0,0 );
  lcd.print(rtc.getDateStr());
  lcd.setCursor(11, 0);
  lcd.print(rtc.getTimeStr());
   delay (1000);
  lcd.setCursor(0,1); 
  lcd.write("ALCOHOL:"); 
  lcd.setCursor(9,1); 
  float porcentaje=(valor_alcohol/1000);  
  lcd.print(porcentaje);
  lcd.setCursor(14,1); 
  lcd.write((char)223);
      
  delay (2500); 
  
  lcd.begin(16, 2);
  lcd.setCursor(6, 0);
  lcd.write("BUEN");
  lcd.setCursor(6, 1);
  lcd.write("VIAJE");
  delay (2500);
  
  lcd.begin(16,1);
       digitalWrite(v, LOW);
       digitalWrite(a, LOW);
       digitalWrite(r, LOW);
       valor_alcohol=0;
  }
  if (valor_alcohol > 0 && valor_alcohol < ve){
  lcd.begin(16, 2);
  lcd.setCursor(5, 0);
  lcd.write("INTENTE");
  lcd.setCursor(3, 1);
  lcd.write("NUEVAMENTE");
  delay (2500);
  lcd.begin(16,1);
  }
}
