#include <iostream>
#include <vector>
#include <string>

struct Node {
    int val;
    Node *left, *right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

Node* buildTree() {
    int val;
    if (!(std::cin >> val) || val == -2 || val == -1) {
        return nullptr;
    }
    Node* root = new Node(val);
    root->left = buildTree();
    root->right = buildTree();
    return root;
}

// Special buildTree that handles the -2 sentinel properly for the whole sequence
// but since -1 is also used for empty nodes in the extended preorder,
// we need to be careful.

// Actually, the extended preorder format is: root, left_subtree, right_subtree.
// -1 means the current node is null.
// -2 means end of input stream.

Node* readNode() {
    int val;
    if (!(std::cin >> val) || val == -2) return nullptr;
    if (val == -1) return nullptr;
    Node* root = new Node(val);
    root->left = readNode();
    root->right = readNode();
    return root;
}

bool prune(Node*& root) {
    if (!root) return true;
    bool left_empty = prune(root->left);
    bool right_empty = prune(root->right);

    if (left_empty) {
        delete root->left;
        root->left = nullptr;
    }
    if (right_empty) {
        delete root->right;
        root->right = nullptr;
    }

    return root->val == 0 && !root->left && !root->right;
}

void printTree(Node* root) {
    if (!root) {
        std::cout << "-1 ";
        return;
    }
    std::cout << root->val << " ";
    printTree(root->left);
    printTree(root->right);
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = readNode();

    // consume remaining -2 if any
    int val;
    while (std::cin >> val && val != -2);

    if (prune(root)) {
        delete root;
        root = nullptr;
    }

    if (!root) {
        // If the whole tree is pruned, the output should probably be -1
        // based on the logic that an empty tree's preorder is -1.
        std::cout << "-1" << std::endl;
    } else {
        printTree(root);
        std::cout << std::endl;
    }

    deleteTree(root);

    return 0;
}
