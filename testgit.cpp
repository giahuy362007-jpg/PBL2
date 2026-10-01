#include <iostream>
#include <string>
#include "Controller/library_controller.h"

using namespace std;

// Menu dành cho Admin hoặc Manager
void show_admin_menu() {
    cout << "\n================ ADMIN / MANAGER MENU ================\n";
    cout << "1. Tim kiem sach\n";
    cout << "2. Them sach moi\n";
    cout << "3. Dang ky ca truc\n";
    cout << "4. Muon sach\n";
    cout << "5. Tra sach\n";
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