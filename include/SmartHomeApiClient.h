#ifndef SMART_HOME_API_CLIENT_H
#define SMART_HOME_API_CLIENT_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "Structs.h"

class SmartHomeApiClient
{
    public:
        SmartHomeApiClient(const String baseUrl);
        ~SmartHomeApiClient();

        bool GetRelays(std::vector<Relay> *&relays);

    private:
        String _baseUrl;
        HTTPClient _http;
};

#endif