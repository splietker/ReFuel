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

#ifndef REFUEL_AMBIENTLIGHTNOTIFIER_H
#define REFUEL_AMBIENTLIGHTNOTIFIER_H

#include <boost/asio/serial_port.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Notifier.h"

class AmbientLightNotifier : public Notifier {
public:
    AmbientLightNotifier();

private:
    boost::asio::io_service ioService;

    boost::asio::serial_port serial;

    virtual void notificationStart() override;

    virtual void notificationLoop() override;

    virtual void notificationStop() override;

    void sendSerialCommand(boost::property_tree::ptree& pt);

public:
    virtual void setIntensity(double intensity) override;
};


#endif //REFUEL_AMBIENTLIGHTNOTIFIER_H
