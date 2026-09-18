#pragma once

#include <string>

class book {
private:
    std::string id;
    std::string title;
    std::string author;
    std::string category;
    int quantity;
    int year;

public:
    book();
    book(std::string id, std::string title, std::string author, std::string category, int quantity, int year);

    std::string get_id() const;
    std::string get_title() const;
    std::string get_author() const;
    std::string get_category() const;
    int get_quantity() const;
    int get_year() const;

    void set_id(std::string id);
    void set_title(std::string title);
    void set_author(std::string author);
    void set_category(std::string category);
    void set_quantity(int quantity);
    void set_year(int year);
};