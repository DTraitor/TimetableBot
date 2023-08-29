#include "Teacher.h"

Teacher::Teacher(const rapidjson::Value &json) {
    this->code = json["code"].GetString();
    this->name = json["name"].GetString();
    this->surname = json["surname"].GetString();
    this->patronymic = json["patronymic"].GetString();
}

std::string Teacher::getTelegramMessage() const {
    return surname + ' ' + name.substr(0, 2) + '.' + patronymic.substr(0, 2) + '.';
}
