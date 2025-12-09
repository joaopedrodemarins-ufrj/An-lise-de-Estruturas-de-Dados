#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class AutoSortingTree {
private:
    struct Node {
        float value;
        bool red;
        Node* left;
        Node* right;
        Node* parent;
    };

    Node* root;
    Node* NIL;

    Node* createNode(float value) {
        Node* n = new Node;
        n->value = value;
        n->red = true;
        n->left = NIL;
        n->right = NIL;
        n->parent = nullptr;
        return n;
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != NIL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void insertFix(Node* z) {
        while (z->parent && z->parent->red) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y->red) {
                    z->parent->red = false;
                    y->red = false;
                    z->parent->parent->red = true;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->red = false;
                    z->parent->parent->red = true;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y->red) {
                    z->parent->red = false;
                    y->red = false;
                    z->parent->parent->red = true;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->red = false;
                    z->parent->parent->red = true;
                    leftRotate(z->parent->parent);
                }
            }
            if (z == root) break;
            if (!z->parent || !z->parent->parent) break;
        }
        root->red = false;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != NIL) {
            v->parent = u->parent;
        } else {
            v->parent = u->parent;
        }
    }

    Node* minimum(Node* x) const {
        while (x->left != NIL) {
            x = x->left;
        }
        return x;
    }

    void deleteFix(Node* x) {
        while (x != root && !x->red) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->red) {
                    w->red = false;
                    x->parent->red = true;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (!w->left->red && !w->right->red) {
                    w->red = true;
                    x = x->parent;
                } else {
                    if (!w->right->red) {
                        w->left->red = false;
                        w->red = true;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->red = x->parent->red;
                    x->parent->red = false;
                    w->right->red = false;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;
                if (w->red) {
                    w->red = false;
                    x->parent->red = true;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (!w->right->red && !w->left->red) {
                    w->red = true;
                    x = x->parent;
                } else {
                    if (!w->left->red) {
                        w->right->red = false;
                        w->red = true;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->red = x->parent->red;
                    x->parent->red = false;
                    w->left->red = false;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->red = false;
    }

    void deleteNode(Node* z) {
        Node* y = z;
        Node* x;
        bool yOriginalRed = y->red;
        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalRed = y->red;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->red = z->red;
        }
        delete z;
        if (!yOriginalRed) {
            if (x == NIL) {
                if (root != NIL) deleteFix(root);
            } else {
                deleteFix(x);
            }
        }
    }

    void inorder(Node* node, vector<float>& out) const {
        if (node == NIL) return;
        inorder(node->left, out);
        out.push_back(node->value);
        inorder(node->right, out);
    }

    void rangeCollect(Node* node, float x, float y, vector<float>& out) const {
        if (node == NIL) return;
        if (node->value > x) rangeCollect(node->left, x, y, out);
        if (node->value >= x && node->value <= y) out.push_back(node->value);
        if (node->value < y) rangeCollect(node->right, x, y, out);
    }

    void minCollect(Node* node, int& amount, vector<float>& out) const {
        if (node == NIL || amount <= 0) return;
        minCollect(node->left, amount, out);
        if (amount > 0) {
            out.push_back(node->value);
            amount--;
        }
        minCollect(node->right, amount, out);
    }

    void maxCollect(Node* node, int& amount, vector<float>& out) const {
        if (node == NIL || amount <= 0) return;
        maxCollect(node->right, amount, out);
        if (amount > 0) {
            out.push_back(node->value);
            amount--;
        }
        maxCollect(node->left, amount, out);
    }

public:
    AutoSortingTree() {
        NIL = new Node;
        NIL->red = false;
        NIL->left = NIL;
        NIL->right = NIL;
        NIL->parent = nullptr;
        root = NIL;
    }

    vector<float> getContent() const {
        vector<float> out;
        inorder(root, out);
        return out;
    }

    void printSorted() const {
        vector<float> out;
        inorder(root, out);
        for (int i = 0; i < (int)out.size(); i++) {
            cout << out[i] << endl;
        }
    }

    vector<float> insert(float value) {
        Node* z = createNode(value);
        Node* y = nullptr;
        Node* x = root;
        while (x != NIL) {
            y = x;
            if (value < x->value) x = x->left;
            else x = x->right;
        }
        z->parent = y;
        if (y == nullptr) {
            root = z;
        } else if (value < y->value) {
            y->left = z;
        } else {
            y->right = z;
        }
        if (z->parent == nullptr) {
            z->red = false;
            z->left = NIL;
            z->right = NIL;
            return getContent();
        }
        if (z->parent->parent == nullptr) {
            return getContent();
        }
        z->left = NIL;
        z->right = NIL;
        insertFix(z);
        return getContent();
    }

    vector<float> remove(float value) {
        Node* z = root;
        while (z != NIL) {
            if (value == z->value) break;
            else if (value < z->value) z = z->left;
            else z = z->right;
        }
        if (z == NIL) return getContent();
        deleteNode(z);
        if (root == nullptr) root = NIL;
        return getContent();
    }

    vector<float> min(int amount = 1) const {
        vector<float> out;
        if (amount <= 0) return out;
        int a = amount;
        minCollect(root, a, out);
        return out;
    }

    vector<float> max(int amount = 1) const {
        vector<float> out;
        if (amount <= 0) return out;
        int a = amount;
        maxCollect(root, a, out);
        return out;
    }

    vector<float> rangeQuery(float x, float y) const {
        vector<float> out;
        if (x > y) return out;
        rangeCollect(root, x, y, out);
        return out;
    }

    float median() const {
        vector<float> v;
        inorder(root, v);
        int n = v.size();
        if (n == 0) throw runtime_error("Arvore vazia");
        if (n % 2 == 1) {
            return v[n/2];
        } else {
            return (v[n/2 - 1] + v[n/2]) / 2.0f;
        }
    }
};
