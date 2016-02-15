/*
 * Copyright 2016 Malte Splietker
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 *         limitations under the License.
 */

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
