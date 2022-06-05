#include <Arduino.h>
#include "wificonfig.h"

void setup()
{
    Serial.begin(115200);

    network_init();   
}

void loop()
{
    network_work();
    delay(100);
}
