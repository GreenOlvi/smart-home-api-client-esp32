#ifndef SMART_HOME_API_CLIENT_H
#define SMART_HOME_API_CLIENT_H

#include <Arduino.h>
#include <Client.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "Structs.h"

class SmartHomeApiClient
{
    public:
        SmartHomeApiClient(WiFiClient &client, const String baseUrl);
        ~SmartHomeApiClient();

        bool GetRelays(std::vector<Relay> *&relays);
        bool ToggleRelay(const GUID id);

    private:
        String _baseUrl;
        WiFiClient &_client;
        HTTPClient _http;
};

#endif