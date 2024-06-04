/*
  EspNoise.cpp - Library for getting telemetry from arduino esp8266.
  Created by Petrovskiy Maxim 31 May 2024.
  Released into the public domain.
*/

#include "Arduino.h"
#include "EspNoise.h"

EspNoise::EspNoise(int noisePin, int soundPin, int cooldown, String noiseTag, String soundTag){
    _noisePin = noisePin;
    _soundPin = soundPin;
    _cooldown = cooldown;
    _noiseTag = noiseTag;
    _soundTag = soundTag;
}

int EspNoise::getNoiseValue(int now){
    _lastCall = now;

    return analogRead(_noisePin);
}

int EspNoise::getSoundValue(int now){
    _lastCall = now;

    return analogRead(_soundPin);
}

void EspNoise::addWrappedNoiseValue(JsonArray telemetryArray, int now){
    _lastCall = now;

    JsonObject telemetry = telemetryArray.createNestedObject();
    telemetry["T"] = _noiseTag;
    telemetry["V"] = String(analogRead(_noisePin));
    telemetry["TS"] = now;
}

void EspNoise::addWrappedSoundValue(JsonArray telemetryArray, int now){
    _lastCall = now;

    JsonObject telemetry = telemetryArray.createNestedObject();
    telemetry["T"] = _soundTag;
    telemetry["V"] = String(analogRead(_soundPin));
    telemetry["TS"] = now;
}

bool EspNoise::cooldownEnded(int now){
    return _lastCall + _cooldown < now;
}