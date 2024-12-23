#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value) {
        data = value;
        left = right = nullptr;
        height = 1;
    }
};

int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(Node* node) {
    if (node == nullptr)
        return;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* insert(Node* node, int value) {
    if (node == nullptr)
        return new Node(value);

    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    else
        return node;

    updateHeight(node);

    int balance = getBalance(node);

    if (balance > 1 && value < node->left->data)
        return rotateRight(node);

    if (balance < -1 && value > node->right->data)
        return rotateLeft(node);

    if (balance > 1 && value > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && value < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void preOrder(Node* root) {
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if (root == nullptr)
        return;
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

void postOrder(Node* root) {
    if (root == nullptr)
        return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

int main() {
    Node* root = nullptr;
    int arr[] = {17, 23, 201, 98, 67, 83, 13, 23, 10, 191, 84, 58};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    cout << "Duyet cay theo thu tu truoc (Preorder): ";
    preOrder(root);
    cout << "\n";

    cout << "Duyet cay theo thu tu giua (Inorder): ";
    inOrder(root);
    cout << "\n";

    cout << "Duyet cay theo thu tu sau (Postorder): ";
    postOrder(root);
    cout << "\n";

    return 0;
}
