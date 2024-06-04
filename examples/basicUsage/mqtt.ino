#include <EspLight.h>
#include <EspMQ.h>
#include <EspDHT.h>
#include <EspNoise.h>
#include <CxMQTT.h>
#include "tls_data.h"

#define PIN_DHT 4
#define DHT_TYPE DHT11
#define PIN_MQ 16
#define PIN_SOUND 5
#define PIN_NOISE 14
#define PIN_LIGHT 3

CxMQTT mqttClient("wifi_name", "wifi_password", "broker_url", 8883, ca_cert, thing_cert, thing_key, "tenant_id", "context", "client_id");
EspDHT dht(PIN_DHT, 3, "client_id.dht.temperature", "client_id.dht.humidity", DHT_TYPE);
EspMQ mq(PIN_MQ, 5, "client_id.CO2");
EspLight light(PIN_LIGHT, 4, "client_id.light");
EspNoise noise(PIN_NOISE, PIN_SOUND, 2, "client_id.dns.noise", "client_id.dns.sound");

void setup() {
  mqttClient.setup();
  dht.begin();
  mq.calibrate();
}

void loop() {
  mqttClient.loop();
  StaticJsonDocument<512> telemetryPayload;
  JsonArray telemetryArray = telemetryPayload.to<JsonArray>();
  int now = mqttClient.getTime();

  if (noise.cooldownEnded(now)) {
    noise.addWrappedNoiseValue(telemetryArray, now);
    noise.addWrappedSoundValue(telemetryArray, now);
  }

  if (dht.cooldownEnded(now)) {
    dht.addWrappedTemperatureValue(telemetryArray, now);
    dht.addWrappedHumidityValue(telemetryArray, now);
  }

  if (mq.cooldownEnded(now)) {
    mq.addWrappedCO2Value(telemetryArray, now);
  }

  if (light.cooldownEnded(now)) {
    light.addWrappedLightValue(telemetryArray, now);
  }

  if (telemetryPayload.size() != 0) {
    mqttClient.sendTelemetry(telemetryArray);
  }
}