#include <LiquidCrystal.h>
#include <DS1302.h>

LiquidCrystal lcd(41, 39, 37, 35, 33, 31 );
DS1302 rtc(13, 12, 11);

int v = 51, a = 49, r = 47;
int pininterrupcion = 23;
int in = 51, ou = 53;
int PIN_TRIG = 7;
int PIN_ECO = 6;
int interrupcion = 3; //pin20

int ve = 50, am = 200, ro = 350;
float valor_alcohol = 0;
float promedio = 0;
long duracion, distancia;
int valorapp;
int tespera = 5000;
int col = 16, inicio = 0, alto = 0, scroll = col;
int tdato = 300;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  lcd.begin(16, 2);
  pinMode(pininterrupcion, OUTPUT);

  pinMode(in, INPUT);//entrada del motor
  pinMode(ou, OUTPUT);//Salida del motor
  digitalWrite(ou, LOW); //Bloquear el motor

  pinMode(v, OUTPUT); //VERDE
  pinMode(a, OUTPUT);//AMARILLO
  pinMode(r, OUTPUT);//rojo

  pinMode(PIN_TRIG, OUTPUT);//ultrasonico
  pinMode(PIN_ECO, INPUT);

 /*//configuracion del rtc
  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setTime(23, 21, 30);     // Hora (formato 24)
  rtc.setDate(14, 06, 2017);   // Dia, mes, año
  //configuracion del rtc*/

  attachInterrupt(interrupcion, prom, RISING);
}

void loop() {
  do{
  hora();
  ultrasonico();
  if (distancia <= 12) {
    digitalWrite(pininterrupcion, HIGH);
    delay(10);
    digitalWrite(pininterrupcion, LOW);
  }
  
if (promedio >= ro) {
  rojo();
}
if (promedio >= am && promedio < ro) {
  amarillo();
}
if (promedio >= ve && promedio < am) {
  verde();
}
if (promedio > 50 && promedio < ve) {
error();
}
else {
  hora();
}
//texto con datos superfluos 19.453456, -99.175735
  String g = String(char(223));
  String enunciado = "LAT:19.453456, LON:-99.175735";
    lcd.setCursor(scroll, 2);
    lcd.print(enunciado.substring(inicio, alto));
    delay(tdato);
    lcd.clear();
    if (inicio == 0 && scroll > 0) {
      scroll--;
      alto++;
    }
    else if (alto != enunciado.length() && scroll == 0) {
      inicio++;
      alto++;
    }
    else {
      inicio++;
    }
//texto con datos superfluos
 }while (inicio != alto);
  inicio = alto = 0;
  scroll = col;
}
void hora () {
  lcd.setCursor(0, 0 );
  lcd.print(rtc.getDateStr());
  lcd.setCursor(11, 0);
  lcd.print(rtc.getTimeStr());
    Serial.print(rtc.getDateStr());
    Serial.print(rtc.getTimeStr());
  delay (10);
}
void ultrasonico () {
  //ULTRASONICO
  /* Hacer el disparo */
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  /* Recepcion del eco de respuesta */
  duracion = pulseIn(PIN_ECO, HIGH);
  /* Calculo de la distancia efectiva */
  distancia = (duracion / 2) / 29;
  /* Imprimir resultados a la terminal serial */
  Serial.print(distancia);
  Serial.println("cm");
  delay(10);
}
void rojo() {
  digitalWrite(v, LOW);
  digitalWrite(a, LOW);
  digitalWrite(r, HIGH);
  digitalWrite(ou, LOW);
  valorapp = 3;
  Serial1.print('#');
  Serial1.print(valorapp);
   Serial1.print('~');
   Serial1.println();
  lcd.clear();
  lcd.setCursor(0, 0 );
  lcd.print(rtc.getDateStr());
  lcd.setCursor(11, 0);
  lcd.print(rtc.getTimeStr());
  delay (500);
  lcd.setCursor(1, 1);
  lcd.write("ALCOHOL: ");
  lcd.setCursor(9, 1);
  float porcentaje = (promedio / 1000);
  lcd.print(porcentaje);
  lcd.write((char)223);
  delay (tespera);
  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.write("NO");
  lcd.setCursor(5, 1);
  lcd.write("MANEJE");
  delay (tespera);
  digitalWrite(v, LOW);
  digitalWrite(a, LOW);
  digitalWrite(r, LOW);
  valor_alcohol = 0;
  promedio = 0;
  lcd.clear();
}
void amarillo () {
  digitalWrite(v, LOW);
  digitalWrite(a, HIGH);
  digitalWrite(r, LOW);
  digitalWrite(ou, HIGH);
  valorapp = 2;
  Serial1.print('#');
  Serial1.print(valorapp);
   Serial1.print('~');
   Serial1.println();
  lcd.clear();
  lcd.setCursor(0, 0 );
  lcd.print(rtc.getDateStr());
  lcd.setCursor(11, 0);
  lcd.print(rtc.getTimeStr());
  delay (500);
  lcd.setCursor(1, 1);
  lcd.write("ALCOHOL: ");
  lcd.setCursor(9, 1);
  float porcentaje = (promedio / 1000);
  lcd.print(porcentaje);
  lcd.write((char)223);
  delay (tespera);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.write("TOME");
  lcd.setCursor(2, 1);
  lcd.write("PRECAUCIONES");
  delay (tespera);
  lcd.clear();
  digitalWrite(v, LOW);
  digitalWrite(a, LOW);
  digitalWrite(r, LOW);
  valor_alcohol = 0;
  promedio = 0;
}
void verde() {
  digitalWrite(v, HIGH);
  digitalWrite(a, LOW);
  digitalWrite(r, LOW);
  digitalWrite(ou, HIGH);
  valorapp = 1;
  Serial1.print('#');
  Serial1.print(valorapp);
   Serial1.print('~');
   Serial1.println();
  lcd.clear();
  lcd.setCursor(0, 0 );
  lcd.print(rtc.getDateStr());
  lcd.setCursor(11, 0);
  lcd.print(rtc.getTimeStr());
  delay (500);
  lcd.setCursor(1, 1);
  lcd.write("ALCOHOL: ");
  lcd.setCursor(9, 1);
  float porcentaje = (promedio / 1000);
  lcd.print(porcentaje);
  lcd.write((char)223);
  delay (tespera);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.write("BUEN");
  lcd.setCursor(6, 1);
  lcd.write("VIAJE");
  delay (tespera);
  lcd.clear();
  digitalWrite(v, LOW);
  digitalWrite(a, LOW);
  digitalWrite(r, LOW);
  valor_alcohol = 0;
  promedio = 0;
}
void error(){
  valorapp = 0;
  Serial1.print('#');
  Serial1.print(valorapp);
   Serial1.print('~');
   Serial1.println();
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.write("INTENTE");
  lcd.setCursor(3, 1);
  lcd.write("NUEVAMENTE");
  valor_alcohol = 0;
  promedio = 0;
  delay (tespera);
  lcd.clear();
}
void prom () {
  for (int i = 0; i < 100; i++) {
    valor_alcohol = analogRead(A0);
    promedio = promedio + analogRead(A0);
    Serial.println(valor_alcohol);
    Serial.println(' ');
    delay(1000);
    lcd.setCursor(2, 1);
    lcd.write("Cargando...");
    lcd.setCursor(0, 0 );
    lcd.print(rtc.getDateStr());
    lcd.setCursor(11, 0);
    lcd.print(rtc.getTimeStr());
    delay (1000);
  }
  promedio = promedio / 100;
  Serial.print("Promedio= ");
  Serial.println(promedio);
  float porcentaje = (promedio / 1000);
  Serial.print("Porcentaje= ");
  Serial.println(porcentaje);
  delay(2);
}

