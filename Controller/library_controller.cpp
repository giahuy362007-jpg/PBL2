#include "library_controller.h"

library_controller::library_controller() 
    : b_service("book.txt"), u_service("user.txt"), br_service("borrow.txt"), s_service("shift.txt") {
    current_logged_in_user = nullptr;
}

library_controller::~library_controller() {
    // Các service sẽ tự động gọi Destructor để lưu file txt khi thoát
}

// --- 1. Xử lý đăng nhập ---
bool library_controller::login(std::string id, std::string password) {
    current_logged_in_user = u_service.login(id, password);
    return (current_logged_in_user != nullptr);
}

void library_controller::logout() {
    current_logged_in_user = nullptr;
}

user* library_controller::get_current_user() const {
    return current_logged_in_user;
}

// --- 2. Xử lý Sách ---
linked_list<book> library_controller::search_books(std::string keyword) {
    return b_service.search_books(keyword);
}

bool library_controller::add_new_book(std::string id, std::string title, std::string author, std::string category, int qty, int year) {
    book new_b(id, title, author, category, qty, year);
    return b_service.add_book(new_b);
}

// --- 3. Xử lý Mượn - Trả sách ---
bool library_controller::borrow_book(std::string borrow_id, std::string book_id, std::string user_id, date borrow_date, date due_date) {
    return br_service.create_borrow_ticket(borrow_id, book_id, user_id, borrow_date, due_date, b_service, u_service);
}

bool library_controller::return_book(std::string borrow_id) {
    return br_service.return_book(borrow_id, b_service);
}

// --- 4. Xử lý Ca trực ---
bool library_controller::register_shift(date d, std::string session, std::string admin_id) {
    return s_service.register_shift(d, session, admin_id, u_service);
}

bool library_controller::cancel_shift(date d, std::string session, std::string admin_id) {
    return s_service.cancel_shift(d, session, admin_id);
}