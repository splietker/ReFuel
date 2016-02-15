//
// Created by msp on 2/10/16.
//

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
