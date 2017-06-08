#define pinU 2
#define pinD 3
#define pinT 4
#define pinQ 5
#define pinC 6
#define pinS 7
//Acima estão as definições dos pinos do braille


#include "Arduino.h"
#if !defined(SERIAL_PORT_MONITOR)
  #error "Arduino version not supported. Please update your IDE to the latest version."
#endif

#if defined(__SAMD21G18A__)
  // Shield Jumper on HW (for Zero, use Programming Port)
  #define port SERIAL_PORT_HARDWARE
  #define pcSerial SERIAL_PORT_MONITOR
#elif defined(SERIAL_PORT_USBVIRTUAL)
  // Shield Jumper on HW (for Leonardo and Due, use Native Port)
  #define port SERIAL_PORT_HARDWARE
  #define pcSerial SERIAL_PORT_USBVIRTUAL
#else
  // Shield Jumper on SW (using pins 12/13 or 8/9 as RX/TX)
  #include "SoftwareSerial.h"
  SoftwareSerial port(12, 13);
  #define pcSerial SERIAL_PORT_MONITOR
#endif

#include "EasyVR.h"

EasyVR easyvr(port);

//Groups and Commands
enum Groups
{
  GROUP_0  = 0,
};

enum Group0 
{
  G0_PONTO_LIVRE = 0,
};

// use negative group for wordsets
int8_t group, idx;



//Pin para acionar sequencia do alfabeto
int botaoB = 8;

//Fase da letra
int faseLetraB;

//Estado do botão A
int estadoB;

//Estado anterior do botão A, para evitar altere a letra ao pressionar e segurar
int estadoBant;



void setup()
{

//Parte inicial Botão B
  pinMode (pinU, OUTPUT);
  pinMode (pinD, OUTPUT);
  pinMode (pinT, OUTPUT);
  pinMode (pinQ, OUTPUT);
  pinMode (pinC, OUTPUT);
  pinMode (pinS, OUTPUT);
  
  pinMode (botaoB, INPUT);

  faseLetraB = 0;
  estadoBant = digitalRead(botaoB);


  // ************************************************************


  
// Setup PC serial port
  pcSerial.begin(9600);


  bridge:
  // bridge mode?
  int mode = easyvr.bridgeRequested(pcSerial);
  switch (mode)
  {
  case EasyVR::BRIDGE_NONE:      //This is the case statement used.
    // setup EasyVR serial port
    port.begin(9600);
    // run normally
    pcSerial.println(F("---"));
    pcSerial.println(F("Bridge not started!"));
    Serial.println("*** case EasyVR::BRIDGE_NONE: ***");
    break;
    
  case EasyVR::BRIDGE_NORMAL:
    // setup EasyVR serial port (low speed)
    port.begin(9600);
    // soft-connect the two serial ports (PC and EasyVR)
    easyvr.bridgeLoop(pcSerial);
    // resume normally if aborted
    pcSerial.println(F("---"));
    pcSerial.println(F("Bridge connection aborted!"));
     Serial.println("*** case EasyVR::BRIDGE_NORMAL: ***");
    break;
    
  case EasyVR::BRIDGE_BOOT:
    // setup EasyVR serial port (high speed)
    port.begin(115200);
    // soft-connect the two serial ports (PC and EasyVR)
    easyvr.bridgeLoop(pcSerial);
    // resume normally if aborted
    pcSerial.println(F("---"));
    pcSerial.println(F("Bridge connection aborted!"));
    Serial.println("*** case EasyVR::BRIDGE_BOOT: ***");
    break;
  
  } //end case.

    while (!easyvr.detect())
  {
    Serial.println("EasyVR not detected!");
    delay(100);
  } //end while

  easyvr.setPinOutput(EasyVR::IO1, LOW);
  Serial.println("EasyVR detected!");
  easyvr.setTimeout(1); //Set the number of seconds to listen for each command.
  easyvr.setLanguage(0); //Set language to English

  group = EasyVR::TRIGGER; //<-- start group (customize)


// **************************************************************

}

void loop()
{
  //BOTÃO "B". Ler o botão B e executar letra por letra.
  
  estadoB = digitalRead(botaoB);
  
  if ((estadoB == LOW) && (estadoBant == HIGH)) {
     if (faseLetraB < 28) {
    faseLetraB++;
  } else {
    faseLetraB = 0;
  }
}

 estadoBant = estadoB;

if (faseLetraB == 0) //desligado
  {
  digitalWrite(pinU, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
}

if (faseLetraB == 1) //A
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
  easyvr.playSound(16, EasyVR::VOL_FULL);
}

if (faseLetraB == 2) //B
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
  easyvr.playSound(1, EasyVR::VOL_FULL);
}

if (faseLetraB == 3) //C
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
  easyvr.playSound(2, EasyVR::VOL_FULL);
}

if (faseLetraB == 4) //D
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, LOW);
  easyvr.playSound(3, EasyVR::VOL_FULL);
}

if (faseLetraB == 5) //E
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, LOW);
  easyvr.playSound(4, EasyVR::VOL_FULL);
}

if (faseLetraB == 6) //F
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
  easyvr.playSound(5, EasyVR::VOL_FULL);
}

if (faseLetraB == 7) //G
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, LOW);
  easyvr.playSound(6, EasyVR::VOL_FULL);
}

if (faseLetraB == 8) //H
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, LOW);
  easyvr.playSound(7, EasyVR::VOL_FULL);
}

if (faseLetraB == 9) //I
  {
  digitalWrite(pinU, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
  easyvr.playSound(8, EasyVR::VOL_FULL);
}

if (faseLetraB == 10) //J
  {
  digitalWrite(pinU, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, LOW);
  easyvr.playSound(9, EasyVR::VOL_FULL);
}

if (faseLetraB == 11) //K
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
  easyvr.playSound(10, EasyVR::VOL_FULL);
}

if (faseLetraB == 12) //L
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
  easyvr.playSound(11, EasyVR::VOL_FULL);
}

if (faseLetraB == 13) //M
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
  easyvr.playSound(12, EasyVR::VOL_FULL);
}

if (faseLetraB == 14) //N
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, LOW);
  easyvr.playSound(17, EasyVR::VOL_FULL);
}

if (faseLetraB == 15) //O
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, LOW);
  easyvr.playSound(13, EasyVR::VOL_FULL);
}

if (faseLetraB == 16) //P
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
  easyvr.playSound(14, EasyVR::VOL_FULL);
}

if (faseLetraB == 17) //Q
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, LOW);
  easyvr.playSound(15, EasyVR::VOL_FULL);
}

if (faseLetraB == 18) //R
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, LOW);
  easyvr.playSound(18, EasyVR::VOL_FULL);
}

if (faseLetraB == 19) //S
  {
  digitalWrite(pinU, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
  easyvr.playSound(19, EasyVR::VOL_FULL);
}

if (faseLetraB == 20) //T
  {
  digitalWrite(pinU, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, LOW);
  easyvr.playSound(20, EasyVR::VOL_FULL);
}

if (faseLetraB == 21) //U
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, HIGH);
  easyvr.playSound(21, EasyVR::VOL_FULL);
}

if (faseLetraB == 22) //V
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, HIGH);
  easyvr.playSound(22, EasyVR::VOL_FULL);
}

if (faseLetraB == 23) //W
  {
  digitalWrite(pinU, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, HIGH);
  easyvr.playSound(23, EasyVR::VOL_FULL);
}

if (faseLetraB == 24) //X
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, HIGH);
  easyvr.playSound(24, EasyVR::VOL_FULL);
}

if (faseLetraB == 25) //Y
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, HIGH);
  easyvr.playSound(25, EasyVR::VOL_FULL);
}

if (faseLetraB == 26) //Z
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, HIGH);
  easyvr.playSound(26, EasyVR::VOL_FULL);
}




}
