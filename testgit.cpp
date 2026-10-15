#include <iostream>
#include <string>
#include "Controller/library_controller.h"

using namespace std;
#include <limits>

// 1. Ràng buộc nhập số nguyên trong khoảng [min_val, max_val]
int input_int(string prompt, int min_val = 0, int max_val = 2147483647) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min_val && value <= max_val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
            return value;
        }
        cout << "[Loi] Du lieu khong hop le (Phai la so tu " << min_val << " den " << max_val << ")! Vui long nhap lai.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// 2. Ràng buộc nhập chuỗi không được để trống
string input_string(string prompt) {
    string str;
    while (true) {
        cout << prompt;
        getline(cin >> ws, str);
        if (!str.empty()) {
            return str;
        }
        cout << "[Loi] Truong nay khong duoc de trong! Vui long nhap lai.\n";
    }
}

// 3. Ràng buộc nhập ca trực (chỉ chấp nhận "sang" hoặc "chieu")
string input_session(string prompt) {
    string session;
    while (true) {
        cout << prompt;
        cin >> session;
        if (session == "sang" || session == "chieu") {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return session;
        }
        cout << "[Loi] Ca truc chi duoc nhap 'sang' hoac 'chieu'! Vui long nhap lai.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// 4. Ràng buộc nhập ngày tháng hợp lệ
date input_valid_date(string prompt) {
    while (true) {
        cout << prompt;
        int d, m, y;
        if (cin >> d >> m >> y) {
            date dt(d, m, y);
            if (dt.is_valid()) { // Sử dụng hàm is_valid() có sẵn trong class date
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return dt;
            }
        }
        cout << "[Loi] Ngay thang khong ton tai hoac sai dinh dang! Vui long nhap lai.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
// Menu dành cho Admin hoặc Manager
void show_admin_menu() {
    cout << "\n================ ADMIN / MANAGER MENU ================\n";
    cout << "1. Tim kiem sach\n";
    cout << "2. Them sach moi\n";
    cout << "3. Dang ky ca truc\n";
    cout << "4. Muon sach\n";
    cout << "5. Tra sach\n";
    cout << "6. Sua thong tin sach\n";
    cout << "7. Xem toan bo lich truc\n";
    cout << "8. Rut ten khoi ca truc (Huy dang ky ca nhan)\n";
    cout << "9. Xoa toan bo mot ca truc\n";
    cout << "10. Tinh luong ca truc (200.000 VND / buoi)\n";
    cout << "0. Dang xuat\n";
    cout << "======================================================\n";
    cout << "Chon chuc nang: ";
}

// Menu dành cho Độc giả (User)
void show_user_menu() {
    cout << "\n=================== USER MENU ===================\n";
    cout << "1. Tim kiem sach\n";
    cout << "0. Dang xuat\n";
    cout << "=================================================\n";
    cout << "Chon chuc nang: ";
}

int main() {
    // Khởi tạo bộ điều khiển trung tâm (Tự động load dữ liệu từ các file txt)
    library_controller controller;

    cout << "=====================================================\n";
    cout << "     HE THONG QUAN LY THU VIEN (CONSOLE VERSION)     \n";
    cout << "=====================================================\n";

    while (true) {
        cout << "\n----------------- DANG NHAP -----------------\n";
        string id, password;
        cout << "Nhap Ma tai khoan (ID) [Go 'thoat' de tat chuong trinh]: ";
        cin >> id;
        
        if (id == "thoat" || id == "exit") {
            cout << "Dang thoat he thong. Tam biet!\n";
            break;
        }

        cout << "Nhap Mat khau: ";
        cin >> password;

        // Gọi Controller xử lý đăng nhập
        if (controller.login(id, password)) {
            user* u = controller.get_current_user();
            cout << "\n[Thanh cong] Xin chao, " << u->get_name() 
                 << " | Vai tro: " << u->get_role() << "\n";

            bool is_logged_in = true;
            string role = u->get_role();

            while (is_logged_in) {
                if (role == "admin" || role == "manager") {
                    show_admin_menu();
                    int choice;
                    cin >> choice;

                    if (choice == 1) {
                        // Tìm kiếm sách
                        string keyword;
                        cout << "Nhap tu khoa tim kiem (Ten/Tac gia/The loai): ";
                        cin.ignore();
                        getline(cin, keyword);

                        linked_list<book> results = controller.search_books(keyword);
                        cout << "\n--- KET QUA TIM KIEM ---\n";
                        node<book>* curr = results.get_head();
                        while (curr != nullptr) {
                            book b = curr->get_data();
                            cout << "- [" << b.get_id() << "] " << b.get_title() 
                                 << " | Tac gia: " << b.get_author() 
                                 << " | Ton kho: " << b.get_quantity() << "\n";
                            curr = curr->get_next();
                        }
                    }
                    else if (choice == 2) {
                        // Thêm sách mới
                        string b_id, title, author, cat;
                        int qty, year;
                        cout << "Nhap Ma sach (ID): "; cin >> b_id;
                        cout << "Nhap ten sach: "; cin.ignore(); getline(cin, title);
                        cout << "Nhap tac gia: "; getline(cin, author);
                        cout << "Nhap the loai: "; getline(cin, cat);
                        cout << "So luong: "; cin >> qty;
                        cout << "Nam xuat ban: "; cin >> year;

                        if (controller.add_new_book(b_id, title, author, cat, qty, year)) {
                            cout << "[Thanh cong] Da them sach moi vao kho va luu file!\n";
                        } else {
                            cout << "[Loi] Trung ma sach hoac khong the them!\n";
                        }
                    }
                    else if (choice == 3) {
                        // Đăng ký ca trực
                        int d, m, y;
                        string session, adm_id;
                        cout << "Nhap ngay truc (DD MM YYYY): "; cin >> d >> m >> y;
                        cout << "Nhap ca truc ('sang' hoac 'chieu'): "; cin >> session;
                        cout << "Nhap Ma Admin/Manager dang ky: "; cin >> adm_id;

                        date shift_date(d, m, y);
                        if (controller.register_shift(shift_date, session, adm_id)) {
                            cout << "[Thanh cong] Dang ky ca truc thanh cong!\n";
                        } else {
                            cout << "[Loi] Dang ky that bai (Ca truc da day 4 nguoi hoac sai ID)!\n";
                        }
                    }
                    else if (choice == 4) {
                        // Mượn sách
                        string br_id, b_id, u_id;
                        int d1, m1, y1, d2, m2, y2;
                        cout << "Nhap Ma phieu muon: "; cin >> br_id;
                        cout << "Nhap Ma sach muon: "; cin >> b_id;
                        cout << "Nhap Ma nguoi muon: "; cin >> u_id;
                        cout << "Ngay muon (DD MM YYYY): "; cin >> d1 >> m1 >> y1;
                        cout << "Ngay hen tra (DD MM YYYY): "; cin >> d2 >> m2 >> y2;

                        date b_date(d1, m1, y1);
                        date due_date(d2, m2, y2);

                        if (controller.borrow_book(br_id, b_id, u_id, b_date, due_date)) {
                            cout << "[Thanh cong] Lap phieu muon va tru kho thanh cong!\n";
                        } else {
                            cout << "[Loi] Muon sach that bai (Trung ma phieu, het sach hoac sai ID)!\n";
                        }
                    }
                    else if (choice == 5) {
                        // Trả sách
                        string br_id;
                        cout << "Nhap Ma phieu muon can tra: "; cin >> br_id;

                        if (controller.return_book(br_id)) {
                            cout << "[Thanh cong] Tra sach thanh cong, da hoan lai so luong vao kho!\n";
                        } else {
                            cout << "[Loi] Tra sach that bai (Khong tim thay ma phieu hoac da tra roi)!\n";
                        }
                    }
                   else if (choice == 6) {
                        // Sửa sách (Tận dụng toán tử >> của class book)
                        string old_id;
                        cout << "Nhap Ma sach (ID) cu can sua: "; 
                        cin >> old_id;

                        cout << "--- Nhap thong tin moi cho sach ---\n";
                        book data_b;
                        cin >> data_b; // Gọi operator>> đã overload trong book.cpp

                        if (controller.update_book_info(old_id, data_b)) {
                            cout << "[Thanh cong] Cap nhat thong tin sach thanh cong!\n";
                        } else {
                            cout << "[Loi] Cap nhat that bai (Khong tim thay ma cu hoac ma moi bi trung)!\n";
                        }
                    }
                    else if (choice == 7) {
                        // Xem toàn bộ danh sách ca trực
                        controller.show_all_shifts();
                    }
                    else if (choice == 8) {
                        // Rút tên 1 Admin khỏi ca trực (cancel_shift đã có sẵn trong controller)
                        int d, m, y;
                        string session, adm_id;
                        cout << "Nhap ngay truc (DD MM YYYY): "; cin >> d >> m >> y;
                        cout << "Nhap ca truc ('sang' hoac 'chieu'): "; cin >> session;
                        cout << "Nhap Ma Admin can rut ten: "; cin >> adm_id;

                        date shift_date(d, m, y);
                        if (controller.cancel_shift(shift_date, session, adm_id)) {
                            cout << "[Thanh cong] Da rut ten Admin " << adm_id << " khoi ca truc!\n";
                        } else {
                            cout << "[Loi] Khong tim thay ca truc hoac Admin khong co trong ca nay!\n";
                        }
                    }
                    else if (choice == 9) {
                        // Xóa toàn bộ ca trực (Hủy cả buổi trực)
                        int d, m, y;
                        string session;
                        cout << "Nhap ngay truc can xoa (DD MM YYYY): "; cin >> d >> m >> y;
                        cout << "Nhap ca truc can xoa ('sang' hoac 'chieu'): "; cin >> session;

                        date shift_date(d, m, y);
                        if (controller.delete_shift(shift_date, session)) {
                            cout << "[Thanh cong] Da xoa toan bo ca truc (" << session << " - " << shift_date << ")!\n";
                        } else {
                            cout << "[Loi] Khong tim thay ca truc nay de xoa!\n";
                        }
                    }
                    else if (choice == 10) {
                        // Tính lương theo số buổi trực (200.000 VNĐ/buổi)
                        string adm_id;
                        int month, year;
                        cout << "Nhap Ma Admin/Manager can tinh luong: "; cin >> adm_id;
                        cout << "Nhap thang can tinh (Nhap 0 neu muon tinh tat ca cac thang): "; cin >> month;
                        cout << "Nhap nam can tinh (Nhap 0 neu muon tinh tat ca cac nam): "; cin >> year;

                        long long salary = controller.get_admin_salary(adm_id, month, year);
                        int num_shifts = salary / 200000;

                        cout << "\n--- KET QUA TINH LUONG ---\n";
                        cout << "- Ma nhan vien: " << adm_id << "\n";
                        cout << "- Tong so buoi da truc: " << num_shifts << " buoi\n";
                        cout << "- Don gia: 200,000 VND / buoi\n";
                        cout << "=> TONG LUONG: " << salary << " VND\n";
                    }
                    else if (choice == 0) {
                        controller.logout();
                        is_logged_in = false;
                        cout << "Da dang xuat khoi tai khoan.\n";
                    }
                    else {
                        cout << "[Loi] Lua chon khong hop le!\n";
                    }
                } 
                else if (role == "user") {
                    show_user_menu();
                    int choice;
                    cin >> choice;

                    if (choice == 1) {
                        // Tìm kiếm sách cho độc giả
                        string keyword;
                        cout << "Nhap tu khoa tim kiem sach: ";
                        cin.ignore();
                        getline(cin, keyword);

                        linked_list<book> results = controller.search_books(keyword);
                        cout << "\n--- KET QUA TIM KIEM ---\n";
                        node<book>* curr = results.get_head();
                        while (curr != nullptr) {
                            book b = curr->get_data();
                            cout << "- [" << b.get_id() << "] " << b.get_title() 
                                 << " | Tac gia: " << b.get_author() 
                                 << " | Con lai: " << b.get_quantity() << "\n";
                            curr = curr->get_next();
                        }
                    }
                    else if (choice == 0) {
                        controller.logout();
                        is_logged_in = false;
                        cout << "Da dang xuat khoi tai khoan.\n";
                    }
                    else {
                        cout << "[Loi] Lua chon khong hop le!\n";
                    }
                }
            }
        } else {
            cout << "[Loi] Dang nhap that bai! Sai Ma ID hoac Mat khau.\n";
        }
    }

    return 0;
}
/*

*/