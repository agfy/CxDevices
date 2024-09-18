/*
  EspMQ.cpp - Library for getting telemetry from arduino esp8266.
  Created by Petrovskiy Maxim 31 May 2024.
  Released into the public domain.
*/

#include "Arduino.h"
#include "EspMQ.h"

EspMQ::EspMQ(int mqPin, int cooldown, String mqTag):
    _mq(mqPin)
{
    _cooldown = cooldown;
    _mqTag = mqTag;
}

int EspMQ::getCO2Value(int now){
    _lastCall = now;

    return _mq.readCO2();
}

void EspMQ::addWrappedCO2Value(JsonArray telemetryArray, int now){
    _lastCall = now;

    JsonObject telemetry = telemetryArray.createNestedObject();
    telemetry["T"] = _mqTag;
    telemetry["V"] = _mq.readCO2();
    telemetry["TS"] = now;
}

bool EspMQ::cooldownEnded(int now){
    return _lastCall + _cooldown < now;
}

void EspMQ::calibrate(){
    _mq.calibrate();
}