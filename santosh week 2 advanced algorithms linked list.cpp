#include <iostream>
using namespace std;

// Define a node in the linked list
struct Node {
    int row;
    int col;
    int value;
    Node* next;

    // Constructor to initialize a node
    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    int rows;
    int cols;
    Node* head;

public:
    // Constructor to initialize the sparse matrix
    SparseMatrix(int r, int c) : rows(r), cols(c), head(nullptr) {}

    // Function to add a non-zero element to the linked list
    void addElement(int row, int col, int value) {
        Node* newNode = new Node(row, col, value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Function to input the full matrix and generate the linked list
    void inputFullMatrix() {
        cout << "Enter the elements of the matrix row by row (including zeroes):\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int value;
                cin >> value;
                if (value != 0) { // Only add non-zero elements to the linked list
                    addElement(i, j, value);
                }
            }
        }
    }

    // Function to display the compact representation of the sparse matrix
    void displayCompactMatrix() {
        if (!head) {
            cout << "The matrix has no non-zero elements." << endl;
            return;
        }

        cout << "Compact Representation of Sparse Matrix:\n";
        cout << "Row\tColumn\tValue\n";
        Node* temp = head;
        while (temp) {
            cout << temp->row << "\t" << temp->col << "\t" << temp->value << endl;
            temp = temp->next;
        }
    }

    // Destructor to free memory
    ~SparseMatrix() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    int rows, cols;

    // Input dimensions of the matrix
    cout << "Enter number of rows and columns: ";
    cin >> rows >> cols;

    // Create a SparseMatrix object
    SparseMatrix sparse(rows, cols);

    // Input the full matrix
    sparse.inputFullMatrix();

    // Display the compact representation
    sparse.displayCompactMatrix();

    return 0;
}
