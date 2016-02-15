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

#include <cmath>

#include <boost/log/trivial.hpp>

#include "BrightnessNotifier.h"

BrightnessNotifier::BrightnessNotifier() : oscillationIntervalLength(30) {
    display = XOpenDisplay(0);
    screen = XRRGetScreenResources(display, DefaultRootWindow(display));
}

void BrightnessNotifier::notificationStart() {
    oscillationStartTime = system_clock::now();
}

void BrightnessNotifier::notificationLoop() {
    system_clock::time_point now = system_clock::now();
    milliseconds diffTime = duration_cast<milliseconds>(now - oscillationStartTime);

    /* Next oscillation wave */
    if (diffTime.count() > oscillationIntervalLength * 1000) {
        diffTime = milliseconds(0);
        oscillationStartTime = system_clock::now();
    }

    double rad = (diffTime.count() / (oscillationIntervalLength * 1000)) * 2 * M_PI;
    double newBrightness = 1 - (intensity / 2) + cos(rad) * (intensity / 2);
    BOOST_LOG_TRIVIAL(debug) << "new brightness: " << newBrightness << std::endl;
    setBrightness(newBrightness);
}

void BrightnessNotifier::notificationStop() {
    setBrightness(1);
}

double BrightnessNotifier::getBrightness() {
    double brightness = 0;

    int size = XRRGetCrtcGammaSize(display, screen->crtcs[0]);

    XRRCrtcGamma *gamma = XRRGetCrtcGamma(display, screen->crtcs[0]);

    unsigned short *array = gamma->red;
    int maxIndex = 0;
    for (int i = size - 1; i > 0; i--) {
        if (array[i] < 0xffff) {
            maxIndex = i;
            break;
        }
    }

    int middle = maxIndex / 2;
    double i1 = (double) (middle + 1) / size;
    double v1 = (double) (array[middle]) / 65535;
    double i2 = (double) (maxIndex + 1) / size;
    double v2 = (double) (array[maxIndex]) / 65535;
    if (v2 < 0.0001) { /* The screen is black */
        brightness = 0;
    } else {
        if ((maxIndex + 1) == size)
            brightness = v2;
        else
            brightness = exp((log(v2) * log(i1) - log(v1) * log(i2)) / log(i1 / i2));
    }

    XRRFreeGamma(gamma);

    if (brightness > 1) {
        brightness = 1;
    }

    return brightness;
}

void BrightnessNotifier::setBrightness(double brightness) {
    if (brightness > 1) {
        brightness = 1;
    } else if (brightness < 0) {
        brightness = 0;
    }

    for (int crtcIndex = 0; crtcIndex < screen->ncrtc; crtcIndex++) {
        int size = XRRGetCrtcGammaSize(display, screen->crtcs[crtcIndex]);

        XRRCrtcGamma *gamma = XRRAllocGamma(size);

        for (int i = 0; i < size; i++) {
            unsigned short gammaValue = (unsigned short) ((double) i / (double) (size - 1) * brightness * 65535.0);
            gamma->red[i] = gammaValue;
            gamma->green[i] = gammaValue;
            gamma->blue[i] = gammaValue;
        }

        XRRSetCrtcGamma(display, screen->crtcs[crtcIndex], gamma);

        free(gamma);
    }
}
