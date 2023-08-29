#ifndef TIMETABLE_LESSON_H
#define TIMETABLE_LESSON_H


#include <string>
#include <cstdint>
#include <rapidjson/document.h>

using std::uint16_t;

class Lesson {
public:
    explicit Lesson(const rapidjson::Value &json);
    [[nodiscard]] std::string getTelegramMessage() const;

private:
    std::string localID;
    std::string comment;
    std::string name;
    std::string lessonType;
    std::string teacher;
    std::string location;
    uint16_t beginTime;
    uint16_t duration;
};


#endif //TIMETABLE_LESSON_H
