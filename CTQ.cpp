#include <iostream>
#include <string>
using namespace std;

/* ===================== CAU 1 ===================== */
struct TreeNode {
    string name;
    int weight; // kg trung binh; 0 = nhom phan loai, chua phai 1 loai cu the
    TreeNode *firstChild;
    TreeNode *nextSibling;
};

TreeNode* newNode(string name, int weight) {
    TreeNode *n = new TreeNode();
    n->name = name;
    n->weight = weight;
    n->firstChild = n->nextSibling = NULL;
    return n;
}

TreeNode* findNode(TreeNode *root, string name) {
    if (root == NULL) return NULL;
    if (root->name == name) return root;
    TreeNode *f = findNode(root->firstChild, name);
    if (f) return f;
    return findNode(root->nextSibling, name);
}

// b) them 1 loai dong vat la con cua loai (nhom) ten x
bool addSpecies(TreeNode *root, string parentName, string name, int weight) {
    TreeNode *parent = findNode(root, parentName);
    if (!parent) return false;
    TreeNode *child = newNode(name, weight);
    if (!parent->firstChild) parent->firstChild = child;
    else {
        TreeNode *cur = parent->firstChild;
        while (cur->nextSibling) cur = cur->nextSibling;
        cur->nextSibling = child;
    }
    return true;
}

// c) kiem tra loai ten x co ton tai trong cay
bool existsSpecies(TreeNode *root, string name) {
    return findNode(root, name) != NULL;
}

// d) liet ke loai co can nang TB duoi 50kg hoac tren 200kg
// (chi xet node co weight>0, tuc la loai thuc su, bo qua nhom phan loai)
void listByWeight(TreeNode *root) {
    if (!root) return;
    if (root->weight > 0 && (root->weight < 50 || root->weight > 200))
        cout << "  - " << root->name << " (" << root->weight << " kg)" << endl;
    listByWeight(root->firstChild);
    listByWeight(root->nextSibling);
}

void freeTree(TreeNode *root) {
    if (!root) return;
    freeTree(root->firstChild);
    freeTree(root->nextSibling);
    delete root;
}

/* ===================== CAU 2 (ma tran ke) ===================== */
#define MAXN 100
struct MGraph {
    int n;
    int m[MAXN][MAXN];
};

void initMGraph(MGraph &g, int n) {
    g.n = n;
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            g.m[i][j] = 0;
}

// b) tram k noi truc tiep voi bao nhieu tram khac, la tram nao
void directNeighborsM(MGraph &g, int k) {
    int cnt = 0;
    for (int i = 0; i < g.n; i++) if (g.m[k][i]) cnt++;
    cout << "Tram " << k << " noi truc tiep voi " << cnt << " tram: ";
    for (int i = 0; i < g.n; i++) if (g.m[k][i]) cout << i << " ";
    cout << endl;
}

int bfsPathM(MGraph &g, int x, int y, int path[]) {
    int prev[MAXN], visited[MAXN] = {0};
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 0; i < g.n; i++) prev[i] = -1;
    queue[rear++] = x; visited[x] = 1;
    while (front < rear) {
        int u = queue[front++];
        if (u == y) break;
        for (int v = 0; v < g.n; v++)
            if (g.m[u][v] && !visited[v]) { visited[v] = 1; prev[v] = u; queue[rear++] = v; }
    }
    if (!visited[y]) return -1;
    int len = 0, cur = y, tmp[MAXN];
    while (cur != -1) { tmp[len++] = cur; cur = prev[cur]; }
    for (int i = 0; i < len; i++) path[i] = tmp[len - 1 - i];
    return len;
}

// c) tram x noi voi tram y phai qua it nhat bao nhieu tram trung gian, la tram nao
void reportConnectionM(MGraph &g, int x, int y) {
    int path[MAXN];
    int len = bfsPathM(g, x, y, path);
    if (len == -1) { cout << "Tram " << x << " va tram " << y << " khong ket noi." << endl; return; }
    if (g.m[x][y]) cout << "Tram " << x << " va tram " << y << " noi TRUC TIEP." << endl;
    else {
        cout << "Tram " << x << " va tram " << y << " phai qua " << (len - 2) << " tram trung gian: ";
        for (int i = 1; i < len - 1; i++) cout << path[i] << " ";
        cout << endl;
    }
}

// d) so cum ket noi, moi cum gom nhung tram nao
void connectedComponentsM(MGraph &g) {
    int visited[MAXN] = {0}, comp = 0;
    for (int s = 0; s < g.n; s++) {
        if (visited[s]) continue;
        comp++;
        int queue[MAXN], front = 0, rear = 0;
        queue[rear++] = s; visited[s] = 1;
        cout << "Cum " << comp << ": " << s << " ";
        while (front < rear) {
            int u = queue[front++];
            for (int v = 0; v < g.n; v++)
                if (g.m[u][v] && !visited[v]) { visited[v] = 1; cout << v << " "; queue[rear++] = v; }
        }
        cout << endl;
    }
    cout << "Tong so cum ket noi: " << comp << endl;
}

/* ===================== MAIN ===================== */
int main() {
    cout << "========== CAU 1: CAY PHAN LOAI DONG VAT ==========" << endl;
    /*
       Animals(0)
        |- Mammals(0) -- Tiger(190)
        |- Birds(0)
        |- Reptiles(0) -- Monkey(40)
    */
    TreeNode *root = newNode("Animals", 0);
    TreeNode *mammals = newNode("Mammals", 0);
    TreeNode *birds = newNode("Birds", 0);
    TreeNode *reptiles = newNode("Reptiles", 0);
    root->firstChild = mammals;
    mammals->nextSibling = birds;
    birds->nextSibling = reptiles;
    mammals->firstChild = newNode("Tiger", 190);
    reptiles->firstChild = newNode("Monkey", 40);

    string qName;
    cout << "Nhap ten loai dong vat can kiem tra: ";
    cin.ignore();
    getline(cin, qName);

    if (existsSpecies(root, qName))
        cout << "=> \"" << qName << "\" CO trong cay." << endl;
    else
        cout << "=> \"" << qName << "\" KHONG co trong cay." << endl;

    cout << "Cac loai co can nang TB duoi 50kg hoac tren 200kg:" << endl;
    listByWeight(root);

    freeTree(root);

    cout << "\n========== CAU 2: TRAM SAC XE DIEN (MA TRAN KE) ==========" << endl;
    MGraph g;
    initMGraph(g, 7);
    int matrix[7][7] = {
        {0,1,1,0,0,1,0},
        {1,0,0,1,0,0,1},
        {1,0,0,0,1,0,1},
        {0,1,0,0,0,1,0},
        {0,0,1,0,0,0,1},
        {1,0,0,1,0,0,0},
        {0,1,1,0,1,0,0}
    };
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            g.m[i][j] = matrix[i][j];

    directNeighborsM(g, 1);
    reportConnectionM(g, 0, 3);
    connectedComponentsM(g);

    return 0;
}