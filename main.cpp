#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Nhúng các file model từ thư mục model/
#include "model/book.h"
#include "model/borrow.h"
#include "model/date.h"
#include "model/shift.h"
#include "model/user.h"

// Nhúng các file cấu trúc dữ liệu từ thư mục structure/
#include "structure/linked_list.h"
#include "structure/queue.h"
#include "structure/stack.h"

using namespace std;

// Hàm in Menu chính ra màn hình
void print_main_menu() {
    cout << "\n=========================================\n";
    cout << "      HE THONG QUAN LY THU VIEN\n";
    cout << "=========================================\n";
    cout << "1. Quan ly sach\n";
    cout << "2. Quan ly doc gia & admin\n";
    cout << "3. Quan ly muon / tra sach\n";
    cout << "4. Quan ly lich truc\n";
    cout << "5. Test doc du lieu (book.txt) & Class Date\n";
    cout << "0. Thoat chuong trinh\n";
    cout << "=========================================\n";
    cout << "Moi ban nhap lua chon: ";
}

// Hàm test hệ thống đọc file và ngày tháng
void test_system() {
    cout << "\n--- TEST CLASS DATE ---\n";
    date d(1, 10, 2026); // Khởi tạo ngày thử nghiệm
    cout << "Ngay chay thu: " << d << " - " << d.get_day_of_week() << "\n\n";

    cout << "--- TEST DOC FILE VA LINKED LIST ---\n";
    linked_list<book> my_library;
    
    // Mở file book.txt từ thư mục data/
    ifstream file("data/book.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, title, author, category, temp_qty, temp_year;
            
            // Cắt chuỗi theo dấu ';'
            getline(ss, id, ';');
            getline(ss, title, ';');
            getline(ss, author, ';');
            getline(ss, category, ';');
            getline(ss, temp_qty, ';');
            getline(ss, temp_year, ';');
            
            if(!id.empty()) {
                // Tạo đối tượng book và đẩy vào danh sách liên kết
                book new_book(id, title, author, category, stoi(temp_qty), stoi(temp_year));
                my_library.push_back(new_book);
            }
        }
        file.close();
        cout << "=> Doc du lieu tu 'data/book.txt' THANH CONG!\n";
    } else {
        cout << "=> LOI: Khong the mo file 'data/book.txt'. Vui long kiem tra lai thu muc!\n";
        return;
    }

    // In kết quả kiểm tra ra màn hình
    cout << "=> Tong so sach hien co: " << my_library.get_size() << " cuon.\n";
    cout << "Danh sach chi tiet:\n";
    node<book>* current = my_library.get_head();
    while (current != nullptr) {
        book b = current->get_data();
        cout << "   [" << b.get_id() << "] " << b.get_title() 
             << " - " << b.get_author() << " (Nam: " << b.get_year() << ", SL: " << b.get_quantity() << ")\n";
        current = current->get_next();
    }
}

int main() {
    int choice;
    bool is_running = true;

    while (is_running) {
        print_main_menu();
        
        // Kiểm tra lỗi nếu người dùng nhập chữ thay vì nhập số
        if (!(cin >> choice)) { 
            cin.clear(); // Xóa cờ lỗi của cin
            cin.ignore(10000, '\n'); // Xóa bỏ toàn bộ ký tự rác trong bộ đệm
            cout << "\n---> Lua chon khong hop le. Vui long nhap bang so!\n";
            continue;
        }

        // Xóa dấu Enter trong bộ đệm
        cin.ignore(256, '\n'); 

        switch (choice) {
            case 1:
                cout << "\n---> Tinh nang Quan ly sach dang phat trien...\n";
                // Gọi hàm quản lý sách ở đây
                break;
            case 2:
                cout << "\n---> Tinh nang Quan ly doc gia & admin dang phat trien...\n";
                // Gọi hàm quản lý độc giả ở đây
                break;
            case 3:
                cout << "\n---> Tinh nang Quan ly muon / tra sach dang phat trien...\n";
                // Gọi hàm mượn/trả ở đây
                break;
            case 4:
                cout << "\n---> Tinh nang Quan ly lich truc dang phat trien...\n";
                // Gọi hàm quản lý lịch trực ở đây
                break;
            case 5:
                test_system(); // Gọi hàm test đọc file book.txt và test class date
                break;
            case 0:
                cout << "\n---> Tam biet! Chuong trinh ket thuc.\n";
                is_running = false;
                break;
            default:
                cout << "\n---> Lua chon khong hop le. Vui long nhap lai (0-5)!\n";
                break;
        }
    }

    return 0;
}