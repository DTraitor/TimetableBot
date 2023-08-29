#ifndef TIMETABLEBOT_SCHEDULEDAY_H
#define TIMETABLEBOT_SCHEDULEDAY_H


#include <vector>
#include <cstdint>
#include "Lesson.h"

using std::uint16_t;
using std::uint8_t;

class ScheduleDay {
public:
    ScheduleDay(const rapidjson::Value &json, const uint16_t &year, const uint8_t &month, const uint8_t &day);
    [[nodiscard]] std::string getTelegramMessage() const;
    [[nodiscard]] std::string getWeekDayString() const;

private:
    std::vector<Lesson> firstSubgroup;
    std::vector<Lesson> secondSubgroup;
    bool singleSubgroup;
    uint8_t weekNumber;
    uint8_t dayNumber;
    uint16_t year;
    uint8_t month;
    uint8_t day;
};


#endif //TIMETABLEBOT_SCHEDULEDAY_H
