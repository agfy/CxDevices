/*
  EspLight.cpp - Library for getting telemetry from arduino esp8266.
  Created by Petrovskiy Maxim 31 May 2024.
  Released into the public domain.
*/

#include "Arduino.h"
#include "EspLight.h"

EspLight::EspLight(int lightPin, int cooldown, String lightTag):
    _light(lightPin)
{
    _cooldown = cooldown;
    _lightTag = lightTag;
}

float EspLight::getLightValue(int now){
    _lastCall = now;
    _light.read();
    
    return _light.getLightLux();
}

void EspLight::addWrappedLightValue(JsonArray telemetryArray, int now){
    _lastCall = now;
    _light.read();

    JsonObject telemetry = telemetryArray.createNestedObject();
    telemetry["T"] = _lightTag;
    telemetry["V"] = String(_light.getLightLux());
    telemetry["TS"] = now;
}

bool EspLight::cooldownEnded(int now){
    return _lastCall + _cooldown < now;
}
