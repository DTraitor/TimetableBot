#include <stdexcept>
#include <cpr/cpr.h>
#include <rapidjson/document.h>
#include "ScheduleAPI.h"
#include "../Types/ScheduleDay.h"

std::string ScheduleAPI::makeGetRequest(const std::string& urlPath) const {
    cpr::Response response = cpr::Get(cpr::Url{urlAPI + urlPath});
    if(response.status_code != 200L){
        std::string exceptionMessage = "Failed to make GET request. Error code: ";
        exceptionMessage += std::to_string(response.status_code);
        exceptionMessage += ". Error message: " + response.error.message;
        throw std::runtime_error(exceptionMessage);
    }
    return response.text;
}

ScheduleDay ScheduleAPI::getDay(const std::string &group_code,
                                const uint16_t &year,
                                const uint8_t &month,
                                const uint8_t &day,
                                const bool &excludeOnetimeChanges,
                                const bool &excludePermanentChanges,
                                const bool &showPlace) const {
    std::string endpoint = "/schedule?";
    endpoint += "group_code=" + group_code;
    endpoint += "&year=" + std::to_string(year);
    endpoint += "&month=" + std::to_string(month);
    endpoint += "&day=" + std::to_string(day);
    endpoint += "&onetimes=" + std::string(excludeOnetimeChanges ? "true" : "false");
    endpoint += "&permanents=" + std::string(excludePermanentChanges ? "true" : "false");
    endpoint += "&show_place=" + std::string(showPlace ? "true" : "false");
    if(!token.empty())
        endpoint += "&token=" + token;

    rapidjson::Document requestResult;
    requestResult.Parse(makeGetRequest(endpoint).c_str());

    return {requestResult, year, month, day};
}
