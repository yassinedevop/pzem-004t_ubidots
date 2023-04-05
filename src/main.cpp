#include <Arduino.h>

#include "UbidotsESPMQTT.h"

#define TOKEN "BBFF-rWsuD8P3rALFaaTHHYTMKwIz7ebgqI" // Your Ubidots TOKEN

#define WIFINAME "Hp" // Your SSID

#define WIFIPASS "1122334455" // Your Wifi Pass

Ubidots client(TOKEN);

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");

  Serial.print(topic);

  Serial.print("] ");

  for (int i = 0; i < length; i++)

  {

    Serial.print((char)payload[i]);
  }
}

void setup()
{

  client.setDebug(true);

  Serial.begin(115200);

  client.wifiConnection(WIFINAME, WIFIPASS);

  client.begin(callback);
}

void loop()
{
  if (!client.connected())

  {

    client.reconnect();
  }

  float value1 = analogRead(A0);

  client.add("temperature", value1);

  client.ubidotsPublish("my-new-device");

  client.loop();
}
