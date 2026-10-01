#include "shift_service.h"

shift_service::shift_service(std::string filename) {
    data_file = filename;
    load_data();
}

shift_service::~shift_service() {
    save_data(); // Tự động lưu file khi tắt chương trình
}

// --- Tạo khóa định danh cho Hash Table (VD: 01/10/2026_sang) ---
std::string shift_service::generate_key(date d, std::string session) const {
    std::stringstream ss;
    ss << d.get_day() << "/" << d.get_month() << "/" << d.get_year() << "_" << session;
    return ss.str();
}

// --- Tách dòng từ shift.txt (Định dạng: 01/10/2026;sang;AD01,AD02)[cite: 30] ---
void shift_service::parse_line(std::string line, shift& s) {
    std::stringstream ss(line);
    std::string date_str, session, admins_str;

    std::getline(ss, date_str, ';');
    std::getline(ss, session, ';');
    std::getline(ss, admins_str, ';');

    // Parse ngày (DD/MM/YYYY)
    int d, m, y;
    char slash;
    std::stringstream ss_d(date_str);
    ss_d >> d >> slash >> m >> slash >> y;
    date shift_date(d, m, y);

    s = shift(shift_date, session);

    // Parse danh sách admin cách nhau bởi dấu phẩy
    std::stringstream ss_adm(admins_str);
    std::string admin_id;
    while (std::getline(ss_adm, admin_id, ',')) {
        if (!admin_id.empty()) {
            s.add_admin(admin_id); // Tự động thêm vào mảng tối đa 4 người[cite: 20, 21]
        }
    }
}

// --- 1. ĐỌC DỮ LIỆU TỪ FILE ---
bool shift_service::load_data() {
    std::ifstream file(data_file);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        shift s;
        parse_line(line, s);
        
        shift_list.push_back(s);
        node<shift>* new_node = shift_list.get_tail(); 
        
        // Đăng ký vào bảng băm với khóa ngày_ca
        std::string key = generate_key(s.get_shift_date(), s.get_session());
        shift_index.insert(key, new_node);
    }
    file.close();
    return true;
}

// --- 2. GHI DỮ LIỆU XUỐNG FILE ---
bool shift_service::save_data() {
    std::ofstream file(data_file, std::ios::trunc);
    if (!file.is_open()) return false;

    node<shift>* curr = shift_list.get_head();
    while (curr != nullptr) {
        shift s = curr->get_data();
        file << s.get_shift_date() << ";" 
             << s.get_session() << ";" 
             << s.get_all_admins_string() << "\n";
        curr = curr->get_next();
    }
    file.close();
    return true;
}

// --- 3. ĐĂNG KÝ CA TRỰC CHO ADMIN ---
bool shift_service::register_shift(date shift_date, std::string session, std::string admin_id, user_service& u_service) {
    // Kiểm tra xem user có tồn tại và có phải là admin/manager không
    node<user>* user_node = u_service.get_user_by_id(admin_id);
    if (user_node == nullptr) return false;
    
    std::string role = user_node->get_data().get_role();
    if (role != "admin" && role != "manager") return false;

    std::string key = generate_key(shift_date, session);
    node<shift>* shift_node = shift_index.find(key);

    if (shift_node == nullptr) {
        // Nếu ca trực chưa tồn tại trong ngày hôm đó -> Tạo mới
        shift new_shift(shift_date, session);
        new_shift.add_admin(admin_id);

        shift_list.push_back(new_shift);
        shift_index.insert(key, shift_list.get_tail());
        return true;
    } else {
        // Nếu ca đã tồn tại -> Lấy ra cập nhật (tuân thủ quy tắc lấy data, sửa, rồi set_data ngược lại vào node)
        shift target_shift = shift_node->get_data();
        
        if (!target_shift.add_admin(admin_id)) {
            return false; // Thất bại (do đầy 4 người hoặc đã đăng ký rồi)[cite: 20, 21]
        }

        shift_node->set_data(target_shift);
        return true;
    }
}

// --- 4. HỦY ĐĂNG KÝ CA TRỰC ---
bool shift_service::cancel_shift(date shift_date, std::string session, std::string admin_id) {
    std::string key = generate_key(shift_date, session);
    node<shift>* shift_node = shift_index.find(key);
    if (shift_node == nullptr) return false;

    shift target_shift = shift_node->get_data();
    if (!target_shift.remove_admin(admin_id)) {
        return false; // Không tìm thấy admin này trong ca[cite: 20, 21]
    }

    // Nếu ca trực trống sạch bóng admin -> Xóa luôn ca trực đó khỏi danh sách
    if (target_shift.get_current_count() == 0) {
        shift_index.remove(key);
        shift_list.remove_node(shift_node);
    } else {
        shift_node->set_data(target_shift);
    }

    return true;
}

// --- 5. TRA CỨU CA TRỰC ---
node<shift>* shift_service::get_shift(date shift_date, std::string session) {
    std::string key = generate_key(shift_date, session);
    return shift_index.find(key);
}