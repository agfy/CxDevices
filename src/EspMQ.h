/*
  EspMQ.h - Library for getting telemetry from arduino esp8266.
  Created by Petrovskiy Maxim 31 May 2024.
  Released into the public domain.
*/

#ifndef CX_DEVICES_ESPMQ_H
#define CX_DEVICES_ESPMQ_H

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <TroykaMQ.h>

class EspMQ
{
public:
    EspMQ(int mqPin, int cooldown, String mqTag);
    int getCO2Value(int now);
    void addWrappedCO2Value(JsonArray telemetryArray, int now);
    bool cooldownEnded(int now);
    void calibrate();

private:
    int _cooldown, _lastCall;
    String _mqTag;
    MQ135 _mq;
};

#endif //CX_DEVICES_ESPMQ_H
