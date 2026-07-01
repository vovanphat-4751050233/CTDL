#include <iostream>
#include <string>
using namespace std;

// a) Khai báo tổ chức dữ liệu - 2 struct
struct Sach {
    string tenSach;
    int soTrang;        // khóa
};

struct Node {
    Sach info;
    Node *left, *right;
};

Node* taoNode(string ten, int trang) {
    Node *p = new Node();
    p->info.tenSach = ten;
    p->info.soTrang = trang;
    p->left = p->right = nullptr;
    return p;
}

// b) Thêm một cuốn sách vào cây
Node* themSach(Node *root, string ten, int trang) {
    if (root == nullptr) return taoNode(ten, trang);
    if (trang < root->info.soTrang)
        root->left = themSach(root->left, ten, trang);
    else if (trang > root->info.soTrang)
        root->right = themSach(root->right, ten, trang);
    // trùng số trang thì bỏ qua
    return root;
}

// c) Liệt kê sách có số trang < 200 hoặc > 400
void lietKe(Node *root) {
    if (root == nullptr) return;
    lietKe(root->left);
    if (root->info.soTrang < 200 || root->info.soTrang > 400)
        cout << root->info.tenSach << " - " << root->info.soTrang << " trang" << endl;
    lietKe(root->right);
}

// d) Kiểm tra sách tên x có tồn tại trong cây không
bool timTheoTen(Node *root, const string &x) {
    if (root == nullptr) return false;
    if (root->info.tenSach == x) return true;
    return timTheoTen(root->left, x) || timTheoTen(root->right, x);
}

// e) Hàm main
int main() {
    Node *root = nullptr;

    root = themSach(root, "CTDL va GT", 450);
    root = themSach(root, "LTCB", 300);
    root = themSach(root, "LTHDT", 500);
    root = themSach(root, "Cam nang lap trinh", 250);
    root = themSach(root, "LTW", 320);

    cout << "Cac sach duoi 200 trang hoac tren 400 trang:" << endl;
    lietKe(root);

    string ten;
    cout << "\nNhap ten sach can kiem tra: ";
    getline(cin, ten);

    if (timTheoTen(root, ten))
        cout << "Sach \"" << ten << "\" co trong cay." << endl;
    else
        cout << "Sach \"" << ten << "\" khong co trong cay." << endl;

    return 0;
}