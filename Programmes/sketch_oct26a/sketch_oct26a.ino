#include <SoftwareSerial.h>
#include <RH_RF95.h>

SoftwareSerial ss(5, 6);
RH_RF95 rf95(ss);


void setup() 
{
    Serial.begin(115200);
    Serial.println("RF95 client test.");

    if (!rf95.init())
    {
        Serial.println("init failed");
        while(1);
    }

    // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

    // The default transmitter power is 13dBm, using PA_BOOST.
    // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
    // you can set transmitter powers from 5 to 23 dBm:
    //rf95.setTxPower(13, false);
    
    rf95.setFrequency(434.0);
}

void loop()
{
    // Envoyer un message à rf95_server
    uint8_t data[] = "Hello World!";
    rf95.send(data, sizeof(data));
   
    rf95.waitPacketSent();
    
    // Maintenant, attendez une réponse
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if(rf95.waitAvailableTimeout(3000))
    {   
        if(rf95.recv(buf, &len))
        {
            Serial.print("J'ai répondu: ");
            Serial.println((char*)buf);
        }
        else
        {
            Serial.println("recv failed");
        }
    }
    else
    {
        Serial.println("Pas de réponse, est-ce que rf95_server est en cours d'exécution?");
    }
    
    delay(1000);
}
