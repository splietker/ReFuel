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

#include <chrono>
#include <thread>
#include <gtest/gtest.h>

#include <BrightnessNotifier.h>

TEST(BrightnessNotifier, setBrightness) {
    BrightnessNotifier brightnessNotifier;

    double newBrightness = 0.5;
    brightnessNotifier.setBrightness(newBrightness);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    double epsilon = 0.05;
    double currentBrightness = brightnessNotifier.getBrightness();
    ASSERT_GT(currentBrightness, newBrightness - epsilon);
    ASSERT_LT(currentBrightness, newBrightness + epsilon);
    brightnessNotifier.setBrightness(1);
}

TEST(BrightnessNotifier, testNotifier) {
    BrightnessNotifier brightnessNotifier;
    brightnessNotifier.setIntensity(0.5);

    brightnessNotifier.trigger();

    std::this_thread::sleep_for(std::chrono::seconds(30));

    brightnessNotifier.reset();

    ASSERT_GT(brightnessNotifier.getBrightness(), 1 - 0.05);
}
