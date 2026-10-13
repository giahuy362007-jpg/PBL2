#include "user.h"

using namespace std;

// constructors
user::user() {
    this->id = "";
    this->name = "";
    this->password = "";
    this->role = ""; 
}

user::user(string id, string name, string password, string role) {
    this->id = id;
    this->name = name;
    this->password = password;
    this->role = role;
}

// getters
string user::get_id() const { return id; }
string user::get_name() const { return name; }
string user::get_password() const { return password; }
string user::get_role() const { return role; }

// setters
void user::set_id(string id) { this->id = id; }
void user::set_name(string name) { this->name = name; }
void user::set_password(string password) { this->password = password; }
void user::set_role(string role) { this->role = role; }

istream& operator>>(istream& in, user& u) {
    cout << "Ma nguoi dung: "; getline(in >> ws, u.id);
    cout << "Ho ten: "; getline(in, u.name);
    cout << "Mat khau: "; getline(in, u.password);
    cout << "Vai tro: "; getline(in, u.role);
    return in;
}

ostream& operator<<(ostream& out, const user& u) {
    out << "Ma nguoi dung: " << u.id << '\n'
        << "Ho ten: " << u.name << '\n'
        << "Mat khau: [an]" << '\n'
        << "Vai tro: " << u.role;
    return out;
}