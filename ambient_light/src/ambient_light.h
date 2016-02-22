#ifndef _AMBIENT_LIGHT_NOTIFIER_H_
#define _AMBIENT_LIGHT_NOTIFIER_H_

#include <Adafruit_NeoPixel.h>


class AmbientLight {
public:
  AmbientLight(Adafruit_NeoPixel& strip);

  void StartNotification();

  void StopNotification();

  void oscillation_interval_length(int oscillation_interval_length);

  void intensity(float intensity);

  /**
   * Recalculates the color according to the current time.
   */
  void Refresh();

private:
  void RedrawStrip();

  enum NotificationState {
    STOPPED,
    RUNNING,
    RESETTING
  };

  Adafruit_NeoPixel& strip_;

  float color_fraction_;

  NotificationState state_;

  unsigned long start_time_;

  int oscillation_interval_length_;

  float intensity_;
};

#endif  /* _AMBIENT_LIGHT_NOTIFIER_H_ */
