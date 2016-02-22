#include <inttypes.h>

#include "ambient_light.h"

const float Pi = 3.14159;

AmbientLight::AmbientLight(Adafruit_NeoPixel& strip) : strip_(strip) {
  color_fraction_ = 0;
  RedrawStrip();
}

void AmbientLight::Refresh() {
  if (state_ == RUNNING) {
    // Calculate readian for cosine function
    float diffTime = (millis() - start_time_) % (oscillation_interval_length_ * 1000);
    float rad = (diffTime / (oscillation_interval_length_ * 1000)) * 2 * M_PI;
    color_fraction_ = (intensity_ / 2) - cos(rad) * (intensity_ / 2);
  } else if (state_ == RESETTING) {
    color_fraction_ -= 0.001;
    if (color_fraction_ <= 0) {
      color_fraction_ = 0;
      state_ = STOPPED;
    }
  }
  RedrawStrip();
}

void AmbientLight::StartNotification() {
  start_time_ = millis();
  state_ = RUNNING;
}

void AmbientLight::StopNotification() {
  if (state_ == RUNNING) {
    state_ = RESETTING;
  }
}

void AmbientLight::oscillation_interval_length(int oscillation_interval_length) {
  oscillation_interval_length_ = oscillation_interval_length;
  if (oscillation_interval_length_ == 0) {
    oscillation_interval_length_ = 30;
  }
}

void AmbientLight::intensity(float intensity) {
  intensity_ = intensity;
  if (intensity_ > 1) {
    intensity_ = 1;
  } else if (intensity_ < 0) {
    intensity_ = 0;
  }
}

void AmbientLight::RedrawStrip() {
  uint8_t white_r = 190,
          white_g = 220,
          white_b = 180;
  uint8_t blue_r = 0,
          blue_g = 80,
          blue_b = 255;

  uint8_t new_r = color_fraction_ * blue_r + (1 - color_fraction_) * white_r;
  uint8_t new_g = color_fraction_ * blue_g + (1 - color_fraction_) * white_g;
  uint8_t new_b = color_fraction_ * blue_b + (1 - color_fraction_) * white_b;
  
  for(int i = 0; i < strip_.numPixels(); i++){
    strip_.setPixelColor(i, new_r, new_g, new_b);
  }

  strip_.show();
}
