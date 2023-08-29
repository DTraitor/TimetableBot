#ifndef TIMETABLEBOT_SCHEDULEAPI_H
#define TIMETABLEBOT_SCHEDULEAPI_H


#include <string>
#include <cstdint>
#include <utility>

class ScheduleDay;

using std::uint8_t;
using std::uint16_t;

class ScheduleAPI {
public:
    explicit ScheduleAPI(std::string tokenAPI = "") : token(std::move(tokenAPI)) {}
    [[nodiscard]] std::string makeGetRequest(const std::string& urlPath) const;
    [[nodiscard]] ScheduleDay getDay(
            const std::string &group_code,
            const uint16_t &year,
            const uint8_t &month,
            const uint8_t &day,
            const bool &excludeOnetimeChanges = true,
            const bool &excludePermanentChanges = true,
            const bool &showPlace = false) const;
private:
    const std::string urlAPI = "https://api.crwnd.dev/schedule/violet";
    const std::string token;
};


#endif //TIMETABLEBOT_SCHEDULEAPI_H
