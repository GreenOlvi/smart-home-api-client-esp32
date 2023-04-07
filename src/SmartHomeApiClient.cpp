#include "SmartHomeApiClient.h"

SmartHomeApiClient::SmartHomeApiClient(WiFiClient &client, const String baseUrl)
    : _client(client), _baseUrl(baseUrl), _http()
{
}

SmartHomeApiClient::~SmartHomeApiClient()
{
    _http.~HTTPClient();
}

bool SmartHomeApiClient::GetRelays(std::vector<Relay> *&relays)
{
    _http.begin(_client, _baseUrl + "relay");

    auto code = _http.GET();
    if (!code)
    {
        _http.end();
        Serial.println("Error during http request");
        return false;
    }

    StaticJsonDocument<2048> doc;

    String response = _http.getString();
    auto error = deserializeJson(doc, response);
    // why stream no work?
    // auto response = _http.getStream();
    // auto error = deserializeJson(doc, response);
    _http.end();

    if (error)
    {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.f_str());
        return false;
    }

    relays = new std::vector<Relay>(doc.size());

    int i = 0;
    for (auto rel : doc.as<JsonArray>())
    {
        auto obj = rel.as<JsonObject>();
        (*relays)[i].Id = obj["id"].as<GUID>();
        (*relays)[i].Type = obj["type"].as<String>();
        (*relays)[i].Name = obj["name"].as<String>();
        i++;
    }

    return true;
}

bool SmartHomeApiClient::ToggleRelay(const GUID id)
{
    _http.begin(_client, _baseUrl + "relay/" + id + "/state");
    _http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    auto code = _http.POST("value=toggle");

    if (!code)
    {
        _http.end();
        return false;
    }

    auto response = _http.getString();
    _http.end();

    return true;
}