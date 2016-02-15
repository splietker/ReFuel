//
// Created by msp on 2/11/16.
//

#ifndef REFUEL_BRIGHTNESSNOTIFIER_H
#define REFUEL_BRIGHTNESSNOTIFIER_H


#include <chrono>
#include <memory>

#include <gtest/gtest_prod.h>
#include <X11/extensions/Xrandr.h>

#include "Notifier.h"

using namespace std::chrono;

class BrightnessNotifier : public Notifier {

public:
    BrightnessNotifier();

private:
    Display *display;

    XRRScreenResources *screen;

    /**
     * Oscillation interval length.
     * Determines the time (in seconds) one oscillation of the notifier takes.
     */
    double oscillationIntervalLength;

    /**
     * Start time of the current oscillation wave.
     */
    system_clock::time_point oscillationStartTime;

    virtual void notificationStart() override;

    virtual void notificationLoop() override;

    virtual void notificationStop() override;

    /**
     * Get brightness of the first screen in the list.
     */
    FRIEND_TEST(BrightnessNotifier, setBrightness);

    FRIEND_TEST(BrightnessNotifier, testNotifier);

    double getBrightness();

    /**
     * Set brightness of all screens.
     */
    FRIEND_TEST(BrightnessNotifier, setBrightness);

    void setBrightness(double brightness);
};


#endif //REFUEL_BRIGHTNESSNOTIFIER_H
