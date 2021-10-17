//******************************************************************************************
//Universidad del Valle de Guatemala
//BE3015: Electronica Digital 2
//Estefany Eleuteria Batz Cantor
//Laboratorio 6. Tiva C y ESP32
//******************************************************************************************

//******************************************************************************************
//Definicion de variables
//******************************************************************************************
#define Potenciometro2 PE_0

#define BtnI PF_0
#define BtnD PF_4

#define ledB PF_2
#define ledG PF_3

//******************************************************************************************
//Prototipos de funciones
//******************************************************************************************
void Contador(void);
void Potenciometro(void);

//******************************************************************************************
//Variables globales
//******************************************************************************************
int DCLedB = 0;
int DCLedG = 0;
double alpha = 0.09;
double VoltagePoten2 = 0;

//******************************************************************************************
//Configuracion
//******************************************************************************************
void setup() {
  Serial.begin(9600);
  //Serial1.begin(9600);

  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  pinMode(BtnI, INPUT_PULLUP);
  pinMode(BtnD, INPUT_PULLUP);
}

//******************************************************************************************
//Loop principal
//******************************************************************************************
void loop() {
  Potenciometro();
  Contador();

  analogWrite(ledG, DCLedG);
  analogWrite(ledB, DCLedB);
  
  delay(100);
}

//******************************************************************************************
//Configuracion Contador
//******************************************************************************************
void Contador(void) {
  int EstadoBI = digitalRead(BtnI);
  int EstadoBD = digitalRead(BtnD);

  if(EstadoBI == LOW)
  {
    DCLedG++;
    delay(50);
    if (DCLedG > 254)
    {
      DCLedG == 0;
    }
  }
  
  if(EstadoBD == LOW)
  {
    DCLedG--;
    delay(50);
    if (DCLedG < 1)
    {
      DCLedG == 253;
    }
  }
}

//******************************************************************************************
//Configuracion Potenciometro
//******************************************************************************************
void Potenciometro(void) {
  
  float ADCPoten2 = analogRead(Potenciometro2);
  VoltagePoten2 = (alpha * ADCPoten2) + ((1.0 - alpha) * VoltagePoten2); //Filtro pasa bajas ;
  DCLedB = map(ADCPoten2, 0, 4095, 0, 255);
  Serial.write(DCLedB);
  }
