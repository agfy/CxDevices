/*
  EspNoise.h - Library for getting telemetry from arduino esp8266.
  Created by Petrovskiy Maxim 31 May 2024.
  Released into the public domain.
*/

#ifndef CX_DEVICES_ESPNOISE_H
#define CX_DEVICES_ESPNOISE_H

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

class EspNoise
{
public:
    EspNoise(int noisePin, int soundPin, int cooldown, String noiseTag, String soundTag);
    int getNoiseValue(int now);
    int getSoundValue(int now);
    void addWrappedNoiseValue(JsonArray telemetryArray, int now);
    void addWrappedSoundValue(JsonArray telemetryArray, int now);
    bool cooldownEnded(int now);

private:
    int _noisePin, _soundPin, _cooldown, _lastCall;
    String _noiseTag, _soundTag;
};

#endif //CX_DEVICES_ESPNOISE_H
