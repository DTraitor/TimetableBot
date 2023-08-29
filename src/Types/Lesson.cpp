#include <regex>
#include <algorithm>
#include "Lesson.h"

Lesson::Lesson(const rapidjson::Value &json) {
    this->localID = json["localID"].GetString();
    if(!json["comment"].IsNull())
        this->comment = json["comment"].GetString();
    this->name = json["name"].GetString();
    this->lessonType = json["type"].GetString();
    this->teacher = json["teacher"].GetString();
    this->location = json["location"].GetString();
    this->beginTime = static_cast<uint16_t>(json["beginTime"].GetInt());
    this->duration = static_cast<uint16_t>(json["duration"].GetInt());
}

std::string Lesson::getTelegramMessage() const {
    std::string result;

    //Integer division is below
    if((beginTime / 60) < 10)
        result += "0";
    result += std::to_string(beginTime / 60);
    result += ".";
    if((beginTime % 60) < 10)
        result += "0";
    result += std::to_string(beginTime % 60);

    result += " - ";

    uint16_t endTime = beginTime + duration;
    if((endTime / 60) < 10)
        result += "0";
    result += std::to_string(endTime / 60);
    result += ".";
    if((endTime % 60) < 10)
        result += "0";
    result += std::to_string(endTime % 60);

    result += " | ";
    result += name;
    result += " | ";
    result += lessonType;
    result += " | ";
    result += teacher;
    result += " | ";

    if(location == "--hidden--"){
        result += "Невідомо";
        return result;
    }

    if(std::regex_match(location, std::regex("^https:\\/\\/.*$"))){
        result += "<a href=\"" + location + "\">Посилання</a>";
        return result;
    }

    result += location;
    return result;
}
