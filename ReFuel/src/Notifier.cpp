//
// Created by msp on 2/11/16.
//

#include <chrono>
#include <thread>
#include <boost/log/trivial.hpp>

#include "Notifier.h"

Notifier::Notifier() : loopWaitTime(0.1) {
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
