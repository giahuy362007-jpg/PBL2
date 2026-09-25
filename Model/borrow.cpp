#include "borrow.h"

using namespace std;

// constructors
borrow::borrow() {
    this->id = "";
    this->book_id = "";
    this->user_id = "";
    this->borrow_date = "";
    this->due_date = "";
    this->status = ""; //
}

borrow::borrow(string id, string book_id, string user_id, string borrow_date, string due_date, string status) {
    this->id = id;
    this->book_id = book_id;
    this->user_id = user_id;
    this->borrow_date = borrow_date;
    this->due_date = due_date;
    this->status = status;
}

// getters
string borrow::get_id() const { return id; }
string borrow::get_book_id() const { return book_id; }
string borrow::get_user_id() const { return user_id; }
string borrow::get_borrow_date() const { return borrow_date; }
string borrow::get_due_date() const { return due_date; }
string borrow::get_status() const { return status; }

// setters
void borrow::set_id(string id) { this->id = id; }
void borrow::set_book_id(string book_id) { this->book_id = book_id; }
void borrow::set_user_id(string user_id) { this->user_id = user_id; }
void borrow::set_borrow_date(string borrow_date) { this->borrow_date = borrow_date; }
void borrow::set_due_date(string due_date) { this->due_date = due_date; }
void borrow::set_status(string status) { this->status = status; }