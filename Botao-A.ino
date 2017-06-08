#define pinU 2
#define pinD 3
#define pinT 4
#define pinC 6
#define pinS 7
//Acima estão as definições dos pinos do braille
#define pinQ 5


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
int botaoA = 8;

//Fase da letra
int faseLetraA;

//Estado do botão A
int estadoA;

//Estado anterior do botão A, para evitar altere a letra ao pressionar e segurar
int estadoAant;



void setup()
{

//Parte inicial Botão A
  pinMode (pinU, OUTPUT);
  pinMode (pinD, OUTPUT);
  pinMode (pinT, OUTPUT);
  pinMode (pinQ, OUTPUT);
  pinMode (pinC, OUTPUT);
  pinMode (pinS, OUTPUT);
  
  pinMode (botaoA, INPUT);

  faseLetraA = 0;
  estadoAant = digitalRead(botaoA);


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
  //BOTÃO "A". Ler o botão A e executar letra por letra.
  
  estadoA = digitalRead(botaoA);
  
  if ((estadoA == LOW) && (estadoAant == HIGH)) {
     if (faseLetraA < 7) {
    faseLetraA++;
  } else {
    faseLetraA = 0;
  }
}

 estadoAant = estadoA;

if (faseLetraA == 0) //desligado
  {
  digitalWrite(pinU, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
}

if (faseLetraA == 1) //A
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
  easyvr.playSound(16, EasyVR::VOL_FULL);
}

if (faseLetraA == 2) //E
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, LOW);
  easyvr.playSound(4, EasyVR::VOL_FULL);
}

if (faseLetraA == 3) //I
  {
  digitalWrite(pinU, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinT, LOW);
  digitalWrite(pinQ, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, LOW);
  easyvr.playSound(8, EasyVR::VOL_FULL);
}

if (faseLetraA == 4) //O
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinS, LOW);
  easyvr.playSound(13, EasyVR::VOL_FULL);
}

if (faseLetraA == 5) //U
  {
  digitalWrite(pinU, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinT, HIGH);
  digitalWrite(pinQ, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinS, HIGH);
  easyvr.playSound(21, EasyVR::VOL_FULL);
}
}
