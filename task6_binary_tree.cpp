#include <iostream>

template<class T>
struct Tree {
    T value;
    Tree* left;
    Tree* right;

    Tree(T _value) : value(_value), left(NULL), right(NULL) {
    }

    Tree(T _value, Tree* _left, Tree* _right) : value(_value), left(_left),
        right(_right) {
    }
};

template<class T>
class BTree {
public:

    BTree() {
        root = NULL;
    }

    ~BTree() {
        clear(root);
    }

    void clear(Tree<T>* node) {
        if (node) {
            clear(node->left);
            clear(node->right);

            delete node;
        }
    }

    void add(T val) {
        if (root) {
            insert(root, val);
        } else {
            root = new Tree<T>(val);
        }
    }

    void insert(Tree<T>* root, T val) {
        if (root->value > val) {
            if (!root->left) {
                root->left = new Tree<T>(val);
            } else {
                insert(root->left, val);
            }
        } else {
            if (!root->right) {
                root->right = new Tree<T>(val);
            } else {
                insert(root->right, val);
            }
        }
    }

    void print(Tree<T>* node) {
        if (node) {
            print(node->left);
            printNode(node);
            print(node->right);
        }
    }

    Tree<T>* getRoot() const {
        return root;
    }

private:
    Tree<T>* root;

    void printNode(Tree<T>* node) {
        std::cout << node->value << ", ";
    }

};

int main() {
    BTree<int>* tree = new BTree<int>();
    tree->add(100);
    tree->add(10);
    tree->add(25);
    tree->add(500);
    tree->add(50);
    tree->add(0);

    tree->print(tree->getRoot());
    std::cout << std::endl;

    delete tree;

    system("pause");

    return 0;
}
