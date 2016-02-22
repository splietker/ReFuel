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

#ifndef REFUEL_NOTIFIER_H
#define REFUEL_NOTIFIER_H


#include <memory>

#include <boost/thread.hpp>

class Notifier {
public:
    Notifier();

    ~Notifier();

    void trigger();

    void reset();

    virtual void setIntensity(double intensity) {
        Notifier::intensity = intensity;
    }

    virtual void setOscillationIntervalLength(double oscillationIntervalLength) {
        Notifier::oscillationIntervalLength = oscillationIntervalLength;
    }

protected:
    /**
     * Notifier intensity.
     * A value in [0,1] describing the intensity of the notification.
     */
    double intensity;

    /**
     * Loop wait time.
     * Determines the the wait time between two iterations of the notificationLoop method.
     */
    double loopWaitTime;

protected:
/**
     * Oscillation interval length.
     * Determines the time (in seconds) one oscillation of the notifier takes.
     */
    double oscillationIntervalLength;

    virtual void notificationStart() = 0;

    virtual void notificationLoop() = 0;

    virtual void notificationStop() = 0;

private:
    std::unique_ptr<boost::thread> notificationThread;

    boost::atomic<bool> notificationThreadStop;

    void notificationThreadFunction();

    void startNotificationThread();

    void stopNotificationThread();
};


#endif //REFUEL_NOTIFIER_H
