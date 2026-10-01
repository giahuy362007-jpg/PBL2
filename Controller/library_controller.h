#pragma once
#include <string>
#include "../Service/book_service.h"
#include "../Service/user_service.h"
#include "../Service/borrow_service.h"
#include "../Service/shift_service.h"

class library_controller {
private:
    book_service b_service;
    user_service u_service;
    borrow_service br_service;
    shift_service s_service;
    
    user* current_logged_in_user;

public:
    library_controller();
    ~library_controller();

    // --- 1. Quản lý phiên đăng nhập & Phân quyền ---
    bool login(std::string id, std::string password);
    void logout();
    user* get_current_user() const;

    // --- 2. Nghiệp vụ Quản lý Sách ---
    linked_list<book> search_books(std::string keyword);
    bool add_new_book(std::string id, std::string title, std::string author, std::string category, int qty, int year);

    // --- 3. Nghiệp vụ Mượn - Trả sách ---
    bool borrow_book(std::string borrow_id, std::string book_id, std::string user_id, date borrow_date, date due_date);
    bool return_book(std::string borrow_id);

    // --- 4. Nghiệp vụ Quản lý Ca trực ---
    bool register_shift(date d, std::string session, std::string admin_id);
    bool cancel_shift(date d, std::string session, std::string admin_id);
};