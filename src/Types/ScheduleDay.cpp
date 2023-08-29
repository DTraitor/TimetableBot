#include "ScheduleDay.h"

ScheduleDay::ScheduleDay(const rapidjson::Value &json, const uint16_t &year, const uint8_t &month, const uint8_t &day) {
    this->dayNumber = static_cast<uint8_t>(json["day_number"].GetInt());
    this->weekNumber = static_cast<uint8_t>(json["week_number"].GetInt());
    this->year = year;
    this->month = month;
    this->day = day;

    this->firstSubgroup.reserve(json["first_subgroup"].Size());
    for(auto &value : json["first_subgroup"].GetArray()){
        this->firstSubgroup.emplace_back(value);
    }

    if(json["second_subgroup"].IsNull()){
        singleSubgroup = true;
        return;
    }

    this->secondSubgroup.reserve(json["second_subgroup"].Size());
    for(auto &value : json["second_subgroup"].GetArray()){
        this->secondSubgroup.emplace_back(value);
    }
}

std::string ScheduleDay::getTelegramMessage() const {
    std::string reply = "<b>Пари на ";
    if(day < 10)
        reply += "0";
    reply += std::to_string(day);
    reply += ".";
    if(month < 10)
        reply += "0";
    reply += std::to_string(month);
    reply += " (";
    reply += getWeekDayString();
    reply += " ";
    reply += std::to_string(weekNumber);
    reply += "):</b>\n\n";

    reply += "<b>Перша підгрупа:</b>\n";
    for (const Lesson &lesson : firstSubgroup) {
        reply += lesson.getTelegramMessage() + "\n";
    }

    if(singleSubgroup)
        return reply;

    reply += "\n<b>Друга підгрупа:</b>\n";
    for (const Lesson &lesson : secondSubgroup) {
        reply += lesson.getTelegramMessage() + "\n";
    }

    return reply;
}

std::string ScheduleDay::getWeekDayString() const {
    switch (dayNumber) {
        case 0:
            return "Неділя";
        case 1:
            return "Понеділок";
        case 2:
            return "Вівторок";
        case 3:
            return "Середа";
        case 4:
            return "Четвер";
        case 5:
            return "П'ятниця";
        case 6:
            return "Субота";
        default:
            return "Невідомо";
    }
}
