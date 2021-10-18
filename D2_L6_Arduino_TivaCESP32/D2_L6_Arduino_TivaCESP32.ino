//******************************************************************************************
//Universidad del Valle de Guatemala
//BE3015: Electronica Digital 2
//Estefany Eleuteria Batz Cantor
//ESP32
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
int DCLedB = 0;
int DCLedG = 0;
int Bandera = 0;

LiquidCrystal LCD(RS, E, D4, D5, D6, D7);
uint8_t P1Centena, P1Decena, P1Unidad;
uint8_t P2Centena, P2Decena, P2Unidad;
uint8_t GCentena, GDecena, GUnidad;
//******************************************************************************************
//Configuraciones
//******************************************************************************************
void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  
  Potenciometros();
    
  LCD.begin(16, 2);
}

//******************************************************************************************
//Loop principal
//******************************************************************************************
void loop()
{
  Potenciometros();
  ValoresPotenciometros();
  Serial2.write(DCLedR);

  
  LCD.setCursor(0, 0);
  LCD.print("Rojo");
  LCD.setCursor(0, 1);
  LCD.print(P1Centena);
  LCD.print(P1Decena);
  LCD.print(P1Unidad);

  LCD.setCursor(6, 0);
  LCD.print("Verde");
  LCD.setCursor(6, 1);
  LCD.print(P2Centena);
  LCD.print(P2Decena);
  LCD.print(P2Unidad);

  LCD.setCursor(12, 0);
  LCD.print("Azul");
  LCD.setCursor(12, 1);
  LCD.print(GCentena);
  LCD.print(GDecena);
  LCD.print(GUnidad);

  
  if (Serial2.available() > 0)
  {   
    if (Serial2.read() == 1)
    {
      Bandera = 1;      
      }
      
      if (Bandera == 1)
      {
        DCLedG = Serial2.read();
        Serial.print("Led azul:");
        Serial.println(DCLedB);        
        Bandera = 0;
        }
        
        if (Serial2.read() == 2)
    {
      Bandera = 2;      
      }
      
      if (Bandera == 2)
      {
        DCLedB = Serial2.read();
        Serial.print("Led verde: ");
        Serial.println(DCLedG);
        Bandera = 0;
        }
        }
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

  P2Centena = DCLedB / 100;
  P2Decena = (DCLedB - (P2Centena * 100)) / 10;
  P2Unidad = (DCLedB - P2Centena * 100) - (P2Decena * 10);

  GCentena = DCLedG / 100;
  GDecena = (DCLedG - (GCentena * 100)) / 10;
  GUnidad = (DCLedG - GCentena * 100) - (GDecena * 10);  
}
