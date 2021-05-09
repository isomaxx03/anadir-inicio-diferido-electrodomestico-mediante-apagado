#include "OneButton.h"


// Inicializa boton en el pin 2 
OneButton boton(2, false);



// Inicializa variables de control de la libreria
int botonclickado = 0;
int botonpresionado = 0;
int botondoble = 0;

// inicializa variables de control del programa
int contando = 0;
int tiempo = 0;
int horas = 0;
int contar2 = 0;
int contar4 = 0;
int contar6 = 0;
int terminado = 0;
int espera = 0;
int esperando = 0;
int x = 0;
unsigned long contar = 0;
unsigned long tiempoinicio = 0;
unsigned long tiempoactual = 0;
unsigned long tiempotranscurrido = 0;

// codigo setup, a correr una sola vez
void setup() {
 
  pinMode(4, OUTPUT); // inicializa pin 4 como salida  // led 2 horas
  pinMode(5, OUTPUT); // inicializa pin 5 como salida  // led 4 horas
  pinMode(6, OUTPUT); // inicializa pin 6 como salida  // rele
  pinMode(7, OUTPUT); // inicializa pin 7 como salida  // led de contando/cuenta finalizada/6 horas
 
  // Enlaza la funcion click de la libreria con un evento click
  boton.attachClick(clicado);

  //Enlaza la funcion press de la libreria con un evento press
  boton.attachPress(presionado);

  //Enlaza la funcion dobleclick de la libreria con un evento dobleclick
  boton.attachDoubleClick(dobleclick);

  // inicializa salida serie para monitorear
  Serial.begin(9600);

} // termina setup
 
// Codigo principal, a ser ejecutado infinitamente
void loop() {
  // vigila estado del botón
  boton.tick();

if (botonclickado == 1 && terminado == 1) { // evalua si al pulsar boton se ha terminado el programa anterior, para poner led verde a 0)
  Serial.println("empezamos de nuevo");
  digitalWrite(7, LOW);
  terminado = 0;
}

if (botonclickado == 1 && contando == 0 && horas == 0) { // evalua estado de variables y pone horas a 2 (desde 0 por no haber habido ninguna pulsacion)
  horas = 2;
  Serial.println("2 horas desde 0");
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  botonclickado = 0;
}

if (botonclickado == 1 && contando == 0 && horas == 6) { // evalua estado de variables y pone horas a 2
  horas = 2;
  Serial.println("2 horas desde 6");
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  botonclickado = 0;
}

if (botonclickado == 1 && contando == 0 && horas == 2) { // evalua estado de variables y pone horas a 4
  horas = 4;
  Serial.println("4 horas");
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);  
  botonclickado = 0;
}

if (botonclickado == 1 && contando == 0 && horas == 4) { // evalua estado de variables y pone horas a 6
  horas = 6;
  Serial.println("6 horas");
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);  
  digitalWrite(7, HIGH);
  botonclickado = 0;
}

if (botonpresionado == 1 && horas == 2) { // Estos tres siguientes if sirven para poner a 1 la variable correspondiente a la duraccion seleccionada
  contar2 = 1;
  botonpresionado = 0;
  esperando = 1;
}

if (botonpresionado == 1 && horas == 4) {
  contar4 = 1;
  botonpresionado = 0;
  esperando = 1;
}

if (botonpresionado == 1 && horas == 6) {
  contar6 = 1;
  botonpresionado = 0;
  esperando = 1;
}

if (esperando == 1) {
  x = 0;
  //for (x=0;x<10;x=x+1){   //ejecuta 10 veces una secuencia de colores
  while (x < 20) {
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);
  delay(333);
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(7, LOW);
  delay(333);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(7, HIGH);
  delay(333);
  boton.tick();
  if (digitalRead(2) == HIGH && x > 2) {
    x = 11;
    espera = 0;
    esperando = 0;
    delay(3000);
    botondoble = 1;
  }
   x = x+1;
  }
  if (digitalRead(2) == LOW) {
    espera = 1;
    esperando = 0;
  }
  
}

if (contar2 == 1 && espera == 1) { // inicializa variables para cuenta (2 horas = 7200000 milisegundos)
  tiempoinicio = millis();
  contando = 1;  
  Serial.println("contando2");
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  contar = 7200000;
  contar2 = 0;
  espera = 0;
}

if (contar4 == 1 && espera == 1) { // inicializa variables para cuenta (4 horas = 14400000 milisegundos)
  tiempoinicio = millis();
  contando = 1;  
  Serial.println("contando4");
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  contar = 14400000;
  contar4 = 0;
  espera = 0;
}

if (contar6 == 1 && espera == 1) { // inicializa variables para cuenta (6 horas = 21600000 milisegundos)
  tiempoinicio = millis();
  contando = 1;  
  Serial.println("contando6");
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  contar = 21600000;
  contar6 = 0;
  espera = 0;
}

if (contando == 1) { // calcula el tiempo transcurrido
  tiempoactual = millis();
  tiempotranscurrido = tiempoactual - tiempoinicio;
}

if (contando == 1 && tiempotranscurrido > contar) { //pone a 1 tiempo por haber llegado ya el tiempo que se tenia que esperar
  tiempo = 1;
  contando = 0;
}

if (tiempo == 1) { // hace la secuencia de acciones que debe hacer cuando ha llegado el tiempo
digitalWrite(4, LOW);
  Serial.println("ha llegado el tiempo");
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  tiempo = 0;
  tiempoactual = 0;
  tiempotranscurrido = 0;
  contando = 0;
  contar2 = 0;
  contar4 = 0;
  contar6 = 0;
  horas = 0;
  terminado = 1;
}

if (botondoble == 1) { // acciones a realizar cuando se produce doble click (reset) y pone todo a 0
  horas = 0;
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  Serial.println("reiniciado");
  contando = 0;
  botondoble = 0;
  }
  
} // termina el codigo principal


// define que hace cada evento del boton, poniendo a "1" la variable de control
void clicado(){
  botonpresionado = 0;
  botondoble = 0;
  botonclickado = 1;
}//click

void presionado(){
  botonpresionado = 1;
  botondoble = 0;
  botonclickado = 0;
}//press

void dobleclick(){
  botondoble = 1;
  botonclickado = 0;
  botonpresionado = 0;
}//press
