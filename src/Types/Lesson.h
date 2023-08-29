#ifndef TIMETABLE_LESSON_H
#define TIMETABLE_LESSON_H


#include <string>
#include <cstdint>
#include <rapidjson/document.h>
#include "Teacher.h"

using std::uint16_t;

class Lesson {
public:
    explicit Lesson(const rapidjson::Value &json) : teacher(json["lecturers"].GetArray()[0]){
        this->localID = json["local_id"].GetString();
        this->comment = json["comment"].GetString();
        this->name = json["names"].GetArray()[0].GetString();
        this->lessonType = json["lesson_type"].GetString();
        this->location = json["place"].GetString();
        this->beginTime = static_cast<uint16_t>(json["time"].GetInt());
        this->duration = static_cast<uint16_t>(json["duration"].GetInt());
    }
    [[nodiscard]] std::string getTelegramMessage() const;

private:
    std::string localID;
    std::string comment;
    std::string name;
    std::string lessonType;
    Teacher teacher;
    std::string location;
    uint16_t beginTime;
    uint16_t duration;
};


#endif //TIMETABLE_LESSON_H
