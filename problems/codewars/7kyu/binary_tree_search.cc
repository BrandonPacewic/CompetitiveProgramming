// Given a number and a binary tree
// return true if number is in tree else false

struct Node{
    int val;
    Node *left = nullptr;
    Node *right = nullptr;
};

bool search(int n, Node* root) {
    if (root == nullptr) {
        return false;
    }
    if (root->val == n) {
        return true;
    }

    return search(n, root->left) || search(n, root->right);
}