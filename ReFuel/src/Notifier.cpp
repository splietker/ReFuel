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
#include <boost/log/trivial.hpp>

#include "Notifier.h"

Notifier::Notifier() : loopWaitTime(0.1), oscillationIntervalLength(30){
}

Notifier::~Notifier() {
    stopNotificationThread();
}

void Notifier::trigger() {
    stopNotificationThread();
    startNotificationThread();
}

void Notifier::reset() {
    stopNotificationThread();
}

void Notifier::notificationThreadFunction() {
    BOOST_LOG_TRIVIAL(debug) << "Notification notificationLoop started";
    notificationStart();
    while (not notificationThreadStop) {
        notificationLoop();
        std::this_thread::sleep_for(std::chrono::milliseconds((long int) (loopWaitTime * 1000)));
    }
    notificationStop();
}

void Notifier::startNotificationThread() {
    notificationThreadStop = false;
    notificationThread = std::make_unique<boost::thread>(boost::thread(
            boost::bind(&Notifier::notificationThreadFunction, this)));
}

void Notifier::stopNotificationThread() {
    if (not notificationThread) {
        return;
    }

    notificationThreadStop = true;
    notificationThread->interrupt();
    notificationThread->join();
    notificationThread.reset();
}
