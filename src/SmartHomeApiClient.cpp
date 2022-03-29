#include "SmartHomeApiClient.h"

SmartHomeApiClient::SmartHomeApiClient(const String baseUrl)
    : _baseUrl(baseUrl), _http()
{
}

SmartHomeApiClient::~SmartHomeApiClient()
{
    _http.~HTTPClient();
}

bool SmartHomeApiClient::GetRelays(std::vector<Relay> *&relays)
{
    _http.begin(_baseUrl + "relay");

    auto code = _http.GET();
    if (!code) {
        _http.end();
        Serial.println("Error during http request");
        return false;
    }

    Serial.print("HTTP code=");
    Serial.println(code);

    StaticJsonDocument<1024> doc;

    String response = _http.getString();
    auto error = deserializeJson(doc, response);
    // why stream no work?
    // auto response = _http.getStream();
    // auto error = deserializeJson(doc, response);
    _http.end();

    if (error) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.f_str());
        return false;
    }


    Serial.printf("Elements in response: %d\n", doc.size());
    relays = new std::vector<Relay>();

    for (auto rel : doc.as<JsonArray>())
    {
        auto obj = rel.as<JsonObject>();

        Relay *r = new Relay();
        r->Id = obj["id"].as<GUID>();
        r->Type = obj["type"].as<String>();
        r->Name = obj["name"].as<String>();

        relays->push_back(*r);
    }

    return true;
}