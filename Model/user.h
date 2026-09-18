#pragma once

#include <string>

class user {
private:
    std::string id;
    std::string name;
    std::string password;
    std::string role;

public:
    user();
    user(std::string id, std::string name, std::string password, std::string role);

    std::string get_id() const;
    std::string get_name() const;
    std::string get_password() const;
    std::string get_role() const;

    void set_id(std::string id);
    void set_name(std::string name);
    void set_password(std::string password);
    void set_role(std::string role);
};