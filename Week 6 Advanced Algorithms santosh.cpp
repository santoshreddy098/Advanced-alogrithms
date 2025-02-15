#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>  // Added for sort
using namespace std;

// Node structure for Huffman Tree
struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;
    
    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

// Comparison class for priority queue
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Store Huffman codes in a vector
void storeHuffmanCodes(Node* root, string str, vector<pair<char, string>>& huffmanCodes) {
    if (!root)
        return;
    
    // If this is a leaf node, store the code
    if (!root->left && !root->right) {
        huffmanCodes.push_back({root->data, str});
    }
    
    // Recurse on left and right children
    storeHuffmanCodes(root->left, str + "0", huffmanCodes);
    storeHuffmanCodes(root->right, str + "1", huffmanCodes);
}

// Function to compare Huffman codes for sorting
bool compareHuffmanCodes(const pair<char, string>& a, const pair<char, string>& b) {
    if (a.second.length() != b.second.length())
        return a.second.length() < b.second.length();
    return a.second < b.second;
}

// Build Huffman Tree and print codes
void buildHuffmanTree(string S, int f[], int N) {
    // Create a priority queue
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    // Create leaf nodes and add them to priority queue
    for (int i = 0; i < N; i++) {
        Node* node = new Node(S[i], f[i]);
        pq.push(node);
    }
    
    // Build Huffman Tree
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        
        Node* right = pq.top();
        pq.pop();
        
        Node* parent = new Node('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        
        pq.push(parent);
    }
    
    // Get root of Huffman Tree
    Node* root = pq.top();
    
    // Store Huffman codes
    vector<pair<char, string>> huffmanCodes;
    storeHuffmanCodes(root, "", huffmanCodes);
    
    // Sort codes using the comparison function
    sort(huffmanCodes.begin(), huffmanCodes.end(), compareHuffmanCodes);
    
    // Print Huffman codes
    for (const auto& code : huffmanCodes) {
        cout << code.second << " ";
    }
    cout << endl;
    
    // Print explanation
    cout << "Explanation: Huffman codes will be:" << endl;
    for (const auto& code : huffmanCodes) {
        cout << code.first << " : " << code.second << endl;
    }
    
    // Clean up memory
    while (!pq.empty()) {
        Node* temp = pq.top();
        pq.pop();
        delete temp;
    }
}

int main() {
    string S = "abcdef";
    int f[] = {5, 9, 12, 13, 16, 45};
    int N = S.length();
    
    buildHuffmanTree(S, f, N);
    
    return 0;
}