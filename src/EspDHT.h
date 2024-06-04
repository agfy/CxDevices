/*
  EspDHT.h - Library for getting telemetry from arduino esp8266.
  Created by Petrovskiy Maxim 31 May 2024.
  Released into the public domain.
*/

#ifndef CX_DEVICES_ESPDHT_H
#define CX_DEVICES_ESPDHT_H

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <DHT.h>

class EspDHT
{
public:
    EspDHT(int dhtPin, int cooldown, String temperatureTag, String humidityTag, uint8_t dhtType);
    float getTemperatureValue(int now);
    float getHumidityValue(int now);
    void addWrappedTemperatureValue(JsonArray telemetryArray, int now);
    void addWrappedHumidityValue(JsonArray telemetryArray, int now);
    bool cooldownEnded(int now);
    void begin();

private:
    DHT _dht;
    int _cooldown, _lastCall;
    String _temperatureTag, _humidityTag;
};

#endif //CX_DEVICES_ESPDHT_H
