#pragma once
#include <string>
class User {
    public:
        std::string name;
        std::string information;
        std::string nickname;
        std::string avatar;
    private:                                  //to keep this info in encode type
        std::string key;
        std::string password;
        std::string unique_nickame;
        std::string number_phone;
        std::string melody;
};
