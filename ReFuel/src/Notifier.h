//
// Created by msp on 2/10/16.
//

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

    void setIntensity(double intensity) {
        Notifier::intensity = intensity;
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
