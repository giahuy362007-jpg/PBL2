#pragma once

#include <string>

class borrow {
private:
    std::string id;
    std::string book_id;
    std::string user_id;
    std::string borrow_date;
    std::string due_date;
    std::string status;

public:
    borrow();
    borrow(std::string id, std::string book_id, std::string user_id, std::string borrow_date, std::string due_date, std::string status);

    std::string get_id() const;
    std::string get_book_id() const;
    std::string get_user_id() const;
    std::string get_borrow_date() const;
    std::string get_due_date() const;
    std::string get_status() const;

    void set_id(std::string id);
    void set_book_id(std::string book_id);
    void set_user_id(std::string user_id);
    void set_borrow_date(std::string borrow_date);
    void set_due_date(std::string due_date);
    void set_status(std::string status);
};