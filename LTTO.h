
////---------------------------------------------------------------------------------------------------------
//    Include Libraries
#ifndef LTTO_h
#define LTTO_h

#include <Arduino.h>
#include "HashDefines.h"

#define LIBCALL_ENABLEINTERRUPT
#define EI_ARDUINO_INTERRUPTED_PIN
#include <EnableInterrupt.h>



////---------------------------------------------------------------------------------------------------------
//    Declare Global Variables
        
const byte  ARRAY_LENGTH = 28;
const byte  IR_TIME_OUT  = 9;

#define DEBUG
#define DE_BUG_TIMING_PIN   12

////---------------------------------------------------------------------------------------------------------
//    Declare The class

class LTTO
{
    public:
        LTTO (byte txPin, byte rxPin);
        void PinChange(void);
        void SendIR(char type, uint16_t message);
        void SendTag(byte teamID, byte playerID, byte tagPower);
        void SendHostedTag(byte teamID, byte playerID, byte tagPower);
        void SendBeacon(bool TagReceived, byte teamID, byte tagPower);
        void SendZoneBeacon(char beaconType, byte teamID, byte playerID);
        void PrintBinary(int v, int num_places);

        void PrintPointer(unsigned long index);         //TODO: Get rid of this debug routine.


        
        volatile uint16_t   receiveMilliTimer = 32767;
        volatile byte       irPacketLength = 0;
        volatile byte       countISR = 0;
        int8_t              messageIR [ARRAY_LENGTH];
        
        //struct lttoISR
        //{
        //    byte isrRxPin;
        //    LTTO *lttoInstance;
        //};

        
    private:
        void PulseIR(byte mSec);
        void ISRchange(void);

        byte _txPin;                        // The Pin that the IR LED is attached to (via a current limiting resistor!)
        byte _rxPin;                        // The Pin that the IR Receiver output is connected to.
        byte _checkSumCalc;                 // The Checkcum data for sending Packet/Data messages.
        byte _deBugPin;                     // The Pin used for debugging (via a Logic Analyser or Oscilloscope)
};

void SetUpPinChangeInterupt(byte interruptPin, LTTO* lttoInstance );           // Need to pre-declare it here, otherwise the Compiler barks !

#endif

