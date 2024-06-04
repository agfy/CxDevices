/*
  EspLight.h - Library for getting telemetry from arduino esp8266.
  Created by Petrovskiy Maxim 31 May 2024.
  Released into the public domain.
*/

#ifndef CX_DEVICES_ESPLIGHT_H
#define CX_DEVICES_ESPLIGHT_H

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <TroykaLight.h>

class EspLight
{
public:
    EspLight(int lightPin, int cooldown, String lightTag);
    float getLightValue(int now);
    void addWrappedLightValue(JsonArray telemetryArray, int now);
    bool cooldownEnded(int now);

private:
    int _cooldown, _lastCall;
    String _lightTag;
    TroykaLight _light;
};

#endif //CX_DEVICES_ESPLIGHT_H
