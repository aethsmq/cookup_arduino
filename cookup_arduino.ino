#include <Arduino.h>

#include <M5_Encoder.h>
M5_Encoder monEncodeur; // instance du encoder

#include <MicroOscSlip.h>
MicroOscSlip<128> monOsc(&Serial);

#include <Chrono.h>
Chrono chronoPot;


// RÉCEPTION DES MESSAGES OSC
void traiterMessageOsc(MicroOscMessage & message) {
  if (message.checkOscAddressAndTypeTags("/lumiere", "i")) {
    int valeur = message.nextAsInt();

    digitalWrite(3, valeur);
  }
}


void setup()
{
  Serial.begin(115200);
  // Configurer la DEL
  pinMode(3, OUTPUT);
}


void loop()
{
  
  monOsc.onOscMessageReceived(traiterMessageOsc);
  if (chronoPot.hasPassed(20)) {
    chronoPot.restart();
    
    // Lire la valeur du potentiomètre
    int valeur = analogRead(2);

    // Envoyer la valeur à Pure Data
    monOsc.sendInt("/tourner", valeur);
  }
}
