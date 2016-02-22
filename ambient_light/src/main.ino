#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include <avr/power.h>

#include "ambient_light.h"

static const int PIN = 13;
static const int NUMPIXELS = 60;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);

  strip.begin();
  strip.setBrightness(255);
}

static const size_t BUFFER_SIZE = 200;

void loop() {
  static AmbientLight ambient_light(strip);

  if (Serial.available() > 0) {
    char buffer[BUFFER_SIZE];
    byte bytes_read = Serial.readBytesUntil('}', buffer, BUFFER_SIZE - 1);
    // Manually append '}', because missing else
    buffer[bytes_read] = '}';
    buffer[bytes_read + 1] = '\0';

    StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(buffer);
    const char* command = root["command"];

    if (strcmp(command, "notification_start") == 0) {
      ambient_light.oscillation_interval_length(root["oscillation_interval_length"]);
      ambient_light.intensity(root["intensity"]);
      ambient_light.StartNotification();
    } else if (strcmp(command, "notification_stop") == 0) {
      ambient_light.StopNotification();
    } else if (strcmp(command, "set_intensity") == 0) {
      ambient_light.intensity(root["intensity"]);
    }
    else {
      Serial.print("ERROR: received unknown command \"");
      Serial.print(command);
      Serial.println("\"");
    }
  }

  if (millis() % 20 == 0) {
    ambient_light.Refresh();
  }
}
