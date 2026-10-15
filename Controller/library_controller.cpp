#include "library_controller.h"

library_controller::library_controller() 
    : b_service("Data/book.txt"), u_service("Data/user.txt"), 
      br_service("Data/borrow.txt"), s_service("Data/shift.txt") {
    current_logged_in_user = nullptr;
    request_file = "Data/request.txt";
    position_file = "Data/position.txt";
    
    load_requests();
    load_positions(); // Đọc dữ liệu vị trí sách từ file
}
library_controller::~library_controller() {
    save_requests();
}

// --- Quản lý File cho Hàng đợi Đăng ký sách ---
void library_controller::load_requests() {
    std::ifstream file(request_file);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string req_id, b_id, u_id, b_date_str, due_date_str, status;
        std::getline(ss, req_id, ';');
        std::getline(ss, b_id, ';');
        std::getline(ss, u_id, ';');
        std::getline(ss, b_date_str, ';');
        std::getline(ss, due_date_str, ';');
        std::getline(ss, status, ';');

        int d1, m1, y1, d2, m2, y2;
        char slash;
        std::stringstream ss_b(b_date_str); ss_b >> d1 >> slash >> m1 >> slash >> y1;
        std::stringstream ss_d(due_date_str); ss_d >> d2 >> slash >> m2 >> slash >> y2;

        borrow req(req_id, b_id, u_id, date(d1, m1, y1), date(d2, m2, y2), status);
        book_request_queue.push(req);
    }
    file.close();
}

void library_controller::save_requests() {
    std::ofstream file(request_file, std::ios::trunc);
    if (!file.is_open()) return;

    while (!book_request_queue.is_empty()) {
        borrow req = book_request_queue.front();
        book_request_queue.pop();
        file << req.get_id() << ";"
             << req.get_book_id() << ";"
             << req.get_user_id() << ";"
             << req.get_borrow_date() << ";"
             << req.get_due_date() << ";"
             << req.get_status() << "\n";
    }
    file.close();
}

// ================= 1. PHIÊN ĐĂNG NHẬP =================
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

std::string library_controller::get_current_role() const {
    if (current_logged_in_user == nullptr) return "";
    return current_logged_in_user->get_role();
}

// ================= 2. QUẢN LÝ SÁCH =================
linked_list<book> library_controller::search_books(std::string keyword) {
    return b_service.search_books(keyword);
}

linked_list<book> library_controller::get_related_books(std::string category, std::string exclude_book_id) {
    linked_list<book> result;
    linked_list<book> same_cat = b_service.search_books(category);
    node<book>* curr = same_cat.get_head();
    while (curr != nullptr) {
        if (curr->get_data().get_id() != exclude_book_id) {
            result.push_back(curr->get_data());
        }
        curr = curr->get_next();
    }
    return result;
}

bool library_controller::add_new_book(std::string id, std::string title, std::string author, std::string category, int qty, int year) {
    book new_b(id, title, author, category, qty, year);
    return b_service.add_book(new_b);
}

bool library_controller::update_book_info(std::string old_id, book book_n) {
    return b_service.update_book(old_id, book_n);
}

bool library_controller::delete_book(std::string id) {
    return b_service.delete_book(id);
}

node<book>* library_controller::get_book_by_id(std::string id) {
    return b_service.get_book_by_id(id);
}

// ================= 3. QUẢN LÝ MƯỢN - TRẢ =================
bool library_controller::borrow_book(std::string borrow_id, std::string book_id, std::string user_id, date borrow_date, date due_date) {
    return br_service.create_borrow_ticket(borrow_id, book_id, user_id, borrow_date, due_date, b_service, u_service);
}

bool library_controller::return_book(std::string borrow_id) {
    return br_service.return_book(borrow_id, b_service);
}

bool library_controller::delete_borrow(std::string borrow_id) {
    return br_service.delete_borrow_ticket(borrow_id);
}

// ================= 4. HÀNG ĐỢI ĐĂNG KÝ SÁCH (USER QUEUE) =================
bool library_controller::register_book_request(std::string req_id, std::string book_id, std::string user_id, date b_date, date due_date) {
    if (b_service.get_book_by_id(book_id) == nullptr) return false;
    borrow ticket(req_id, book_id, user_id, b_date, due_date, "Cho duyet");
    book_request_queue.push(ticket);
    return true;
}

bool library_controller::has_pending_requests() const {
    return !book_request_queue.is_empty();
}

borrow library_controller::peek_next_request() const {
    return book_request_queue.front();
}

bool library_controller::approve_next_request() {
    if (book_request_queue.is_empty()) return false;
    borrow req = book_request_queue.front();

    // Tạo phiếu mượn chính thức và trừ số lượng trong kho
    if (borrow_book(req.get_id(), req.get_book_id(), req.get_user_id(), req.get_borrow_date(), req.get_due_date())) {
        book_request_queue.pop();
        return true;
    }
    return false; // Hết sách hoặc trùng mã phiếu
}

bool library_controller::reject_next_request() {
    if (book_request_queue.is_empty()) return false;
    book_request_queue.pop();
    return true;
}

int library_controller::get_pending_request_count() const {
    return book_request_queue.get_size();
}

// ================= 5. CA TRỰC =================
bool library_controller::register_shift(date d, std::string session, std::string admin_id) {
    return s_service.register_shift(d, session, admin_id, u_service);
}

bool library_controller::cancel_shift(date d, std::string session, std::string admin_id) {
    return s_service.cancel_shift(d, session, admin_id);
}

linked_list<shift> library_controller::get_my_shifts(std::string admin_id) {
    return s_service.get_shifts_by_admin(admin_id);
}

long long library_controller::get_admin_salary(std::string admin_id, int month, int year) {
    return s_service.calculate_salary(admin_id, month, year, 200000);
}

bool library_controller::delete_shift(date d, std::string session) {
    return s_service.delete_entire_shift(d, session);
}

void library_controller::show_all_shifts() {
    s_service.display_all();
}

// ================= 6. QUẢN LÝ TÀI KHOẢN (MANAGER) =================
bool library_controller::add_new_user(std::string id, std::string name, std::string password, std::string role) {
    user new_u(id, name, password, role);
    return u_service.add_user(new_u);
}

bool library_controller::update_user_info(std::string old_id, user updated_user) {
    return u_service.update_user(old_id, updated_user);
}

bool library_controller::delete_user(std::string id) {
    return u_service.delete_user(id);
}

node<user>* library_controller::get_user_by_id(std::string id) {
    return u_service.get_user_by_id(id);
}

// --- Đọc dữ liệu từ file position.txt (Định dạng: b001;it;a1) ---
void library_controller::load_positions() {
    std::ifstream file(position_file);
    if (!file.is_open()) {
        file.open("position.txt"); // Dự phòng nếu file nằm ở thư mục gốc
    }
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string b_id, cat, shelf;
        std::getline(ss, b_id, ';');
        std::getline(ss, cat, ';');
        std::getline(ss, shelf, ';');

        // Chuẩn hóa mã sách về chữ in thường để so khớp không phân biệt hoa/thường
        b_id = search_algo::to_lower(search_algo::trim(b_id));
        shelf = search_algo::trim(shelf);

        position_list.push_back(book_location(b_id, cat, shelf));
    }
    file.close();
}

// --- Tìm vị trí kệ theo mã sách ---
std::string library_controller::get_book_shelf(std::string book_id) {
    std::string target_id = search_algo::to_lower(search_algo::trim(book_id));
    node<book_location>* curr = position_list.get_head();

    while (curr != nullptr) {
        if (curr->get_data().book_id == target_id) {
            return curr->get_data().shelf;
        }
        curr = curr->get_next();
    }
    return "Chua xep ke"; // Trường hợp sách mới thêm chưa có trong sơ đồ
}