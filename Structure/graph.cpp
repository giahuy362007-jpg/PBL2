#include"graph.h"

template <typename t>
graph<t>::graph(int cap) {
    this->capacity = cap;
    this->num_vertices = 0;
    
    // Khởi tạo mảng động chứa dữ liệu đỉnh
    this->vertices = new t[capacity];
    
    // Khởi tạo mảng động chứa các danh sách liên kết
    this->adj_list = new linked_list<int>[capacity]; 
}

template <typename t>
graph<t>::~graph() {
    clear();
}

template <typename t>
bool graph<t>::add_vertex(t data) {
    if (num_vertices >= capacity) return false; // Đồ thị đã đầy
    
    vertices[num_vertices] = data;
    num_vertices++;
    return true;
}

template <typename t>
bool graph<t>::add_edge(int src_index, int dest_index, bool is_directed) {
    // Kiểm tra tính hợp lệ của index
    if (src_index < 0 || src_index >= num_vertices || 
        dest_index < 0 || dest_index >= num_vertices) {
        return false;
    }
    
    // Dùng hàm push_back của linked_list để thêm cạnh nối
    adj_list[src_index].push_back(dest_index);
    
    // Nếu là đồ thị vô hướng (mượn A có B, thì mượn B cũng có A)
    if (!is_directed) {
        adj_list[dest_index].push_back(src_index);
    }
    
    return true;
}

template <typename t>
int graph<t>::get_num_vertices() const {
    return num_vertices;
}

template <typename t>
t graph<t>::get_vertex_data(int index) const {
    return vertices[index];
}

template <typename t>
linked_list<int>& graph<t>::get_adj_list(int index) const {
    return adj_list[index];
}

template <typename t>
void graph<t>::clear() {
    delete[] vertices;
    delete[] adj_list; // Gọi destructor của linked_list để giải phóng từng node
    num_vertices = 0;
}