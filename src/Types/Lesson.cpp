#include <regex>
#include <algorithm>
#include "Lesson.h"

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
    result += teacher.getTelegramMessage();
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
