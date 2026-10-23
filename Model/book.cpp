#include "book.h"

using namespace std;

// constructors
book::book() {
    this->id = "";
    this->title = "";
    this->author = "";
    this->category = "";
    this->quantity = 0;
    this->year = 0;
}

book::book(string id, string title, string author, string category, int quantity, int year) {
    this->id = id;
    this->title = title;
    this->author = author;
    this->category = category;
    this->quantity = quantity;
    this->year = year;
}

// getters
string book::get_id() const { return id; }
string book::get_title() const { return title; }
string book::get_author() const { return author; }
string book::get_category() const { return category; }
int book::get_quantity() const { return quantity; }
int book::get_year() const { return year; }

// setters
void book::set_id(string id) { this->id = id; }
void book::set_title(string title) { this->title = title; }
void book::set_author(string author) { this->author = author; }
void book::set_category(string category) { this->category = category; }
void book::set_quantity(int quantity) {
    if (quantity >= 0) {
        this->quantity = quantity;
    }
}
void book::set_year(int year) { this->year = year; }

// Tăng trước (++b)
book& book::operator++() {
    quantity++;
    return *this;
}

// Tăng sau (b++)
book book::operator++(int) {
    book temp = *this;
    quantity++;
    return temp;
}

// Giảm trước (--b) (Có chặn không cho âm)
book& book::operator--() {
    if (quantity > 0) {
        quantity--;
    }
    return *this;
}

// Giảm sau (b--)
book book::operator--(int) {
    book temp = *this;
    if (quantity > 0) {
        quantity--;
    }
    return temp;
}

istream& operator>>(istream& in, book& b) {
    cout << "Ma sach: "; getline(in >> ws, b.id);
    cout << "Ten sach: "; getline(in, b.title);
    cout << "Tac gia: "; getline(in, b.author);
    cout << "The loai: "; getline(in, b.category);
    cout << "So luong: "; in >> b.quantity;
    while (in && b.quantity < 0) { 
        cout << "So luong phai >= 0, nhap lai: "; 
        in >> b.quantity; 
    }
    cout << "Nam xuat ban: "; in >> b.year;
    in.ignore(10000, '\n');
    return in;
}

ostream& operator<<(ostream& out, const book& b) {
    out << "Ma sach: " << b.id << '\n'
        << "Ten sach: " << b.title << '\n'
        << "Tac gia: " << b.author << '\n'
        << "The loai: " << b.category << '\n'
        << "So luong: " << b.quantity << '\n'
        << "Nam xuat ban: " << b.year;
    return out;
}
