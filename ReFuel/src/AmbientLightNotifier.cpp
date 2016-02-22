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

#include <sstream>

#include <boost/asio/write.hpp>
#include <boost/log/trivial.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "AmbientLightNotifier.h"

AmbientLightNotifier::AmbientLightNotifier() : ioService(), serial(ioService, "/dev/ttyACM0") {
    serial.set_option(boost::asio::serial_port_base::baud_rate(115200));
}

void AmbientLightNotifier::notificationStart() {
    boost::property_tree::ptree pt;
    pt.put("command", "notification_start");
    pt.put("oscillation_interval_length", oscillationIntervalLength);
    pt.put("intensity", intensity);
    sendSerialCommand(pt);
}

void AmbientLightNotifier::notificationLoop() {
}

void AmbientLightNotifier::notificationStop() {
    boost::property_tree::ptree pt;
    pt.put("command", "notification_stop");
    sendSerialCommand(pt);
}

void AmbientLightNotifier::sendSerialCommand(boost::property_tree::ptree &pt) {
    std::stringstream jsonStream;
    boost::property_tree::json_parser::write_json(jsonStream, pt);
    BOOST_LOG_TRIVIAL(debug) << "Sending command to ambient light: " << jsonStream.str() << std::endl;

    boost::asio::write(serial, boost::asio::buffer(jsonStream.str()));
}

void AmbientLightNotifier::setIntensity(double intensity) {
    Notifier::setIntensity(intensity);
    boost::property_tree::ptree pt;
    pt.put("command", "set_intensity");
    pt.put("intensity", intensity);
    sendSerialCommand(pt);
}
