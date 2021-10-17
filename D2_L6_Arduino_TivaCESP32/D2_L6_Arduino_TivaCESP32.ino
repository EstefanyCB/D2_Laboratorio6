//******************************************************************************************
//Universidad del Valle de Guatemala
//BE3015: Electronica Digital 2
//Estefany Eleuteria Batz Cantor
//Laboratorio 6. 
//******************************************************************************************

//******************************************************************************************
//Librerias
//******************************************************************************************
#include <LiquidCrystal.h>

//******************************************************************************************
//Definicion de los pines
//******************************************************************************************
//Potenciometros
#define Poten1 35

//Pantalla LCD
#define RS 32
#define E 33
#define D4 25
#define D5 26
#define D6 27
#define D7 14

//Comunicacion UART
#define RXp2 16
#define TXp2 17

//******************************************************************************************
//Prototipos de funciones
//******************************************************************************************
void Potenciometros(void);
void PantallLCD(void);
void ValoresPotenciometros(void);
void UART(void);

//******************************************************************************************
//Variables globales
//******************************************************************************************
//Para los potenciometros
float ADCPoten1 = 0.0; //Recibe el valor ADC
double VoltajePoten1 = 0;

double alpha = 0.09; // Filtro para estabilizar

int DCLedR = 0;

char inByte = 0;
String mensaje = "";

LiquidCrystal LCD(RS, E, D4, D5, D6, D7);
uint8_t P1Centena, P1Decena, P1Unidad;

//******************************************************************************************
//Configuraciones
//******************************************************************************************
void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  
  Potenciometros();
  UART();
  
  LCD.begin(16, 2);
}

//******************************************************************************************
//Loop principal
//******************************************************************************************
void loop()
{
  UART();
  Potenciometros();
  ValoresPotenciometros();
    
  LCD.setCursor(0, 0);
  LCD.print("Rojo");
  LCD.setCursor(0, 1);
  LCD.print(P1Centena);
  LCD.print(P1Decena);
  LCD.print(P1Unidad);

  LCD.setCursor(6, 0);
  LCD.print("Verde");


  LCD.setCursor(12, 0);
  LCD.print("Azul");
  delay(100);
}

//******************************************************************************************
//Potenciometros
//******************************************************************************************
void Potenciometros(void)
{
  ADCPoten1 = analogRead(Poten1);
  VoltajePoten1 = (alpha * ADCPoten1) + ((1.0 - alpha) * VoltajePoten1); //Filtro pasa bajas
  DCLedR = map(VoltajePoten1, 0, 4095, 0, 255);
  delay(100);
}

//******************************************************************************************
//Valores Potenciometros
//******************************************************************************************
void ValoresPotenciometros(void)
{
  P1Centena = DCLedR / 100;
  P1Decena = (DCLedR - (P1Centena * 100)) / 10;
  P1Unidad = (DCLedR - P1Centena * 100) - (P1Decena * 10);
}


//******************************************************************************************
//UART
//******************************************************************************************
void UART(void)
{
  if (Serial.available()){
    int data_rcv = Serial.read();

    Serial.print("Recibi el siguiente mensaje: ");
    Serial.println(data_rcv);
  }
}
