/*
  EspDHT.cpp - Library for getting telemetry from arduino esp8266.
  Created by Petrovskiy Maxim 31 May 2024.
  Released into the public domain.
*/

#include "Arduino.h"
#include "EspDHT.h"

EspDHT::EspDHT(int dhtPin, int cooldown, String temperatureTag, String humidityTag, uint8_t dhtType):
    _dht(dhtPin, dhtType)
{
    _cooldown = cooldown;
    _temperatureTag = temperatureTag;
    _humidityTag = humidityTag;
}

float EspDHT::getTemperatureValue(int now){
    _lastCall = now;

    return _dht.readTemperature();
}

float EspDHT::getHumidityValue(int now){
    _lastCall = now;

    return _dht.readHumidity();
}

void EspDHT::addWrappedTemperatureValue(JsonArray telemetryArray, int now){
    _lastCall = now;

    JsonObject telemetry = telemetryArray.createNestedObject();
    telemetry["T"] = _temperatureTag;
    telemetry["V"] = _dht.readTemperature();
    telemetry["TS"] = now;
}

void EspDHT::addWrappedHumidityValue(JsonArray telemetryArray, int now){
    _lastCall = now;

    JsonObject telemetry = telemetryArray.createNestedObject();
    telemetry["T"] = _humidityTag;
    telemetry["V"] = _dht.readHumidity();
    telemetry["TS"] = now;
}

bool EspDHT::cooldownEnded(int now){
    return _lastCall + _cooldown < now;
}

void EspDHT::begin() {
    _dht.begin();
}