#ifndef TIMETABLEBOT_TEACHER_H
#define TIMETABLEBOT_TEACHER_H


#include <string>
#include <rapidjson/document.h>


class Teacher {
public:
    explicit Teacher(const rapidjson::Value &json);
    [[nodiscard]] std::string getTelegramMessage() const;
private:
    std::string code;
    std::string name;
    std::string surname;
    std::string patronymic;
};

#endif //TIMETABLEBOT_TEACHER_H
