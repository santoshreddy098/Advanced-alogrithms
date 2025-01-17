#include <iostream>
#include <vector>
using namespace std;

// Define the structure to store row, column, and value for each non-zero element
struct Element {
    int row;
    int col;
    int value;
};

class SparseMatrix {
private:
    int rows;
    int cols;
    vector<Element> elements; // Store non-zero elements dynamically

public:
    // Constructor to initialize the sparse matrix
    SparseMatrix(int r, int c) {
        rows = r;
        cols = c;
    }

    // Function to input the full matrix
    void inputFullMatrix() {
        cout << "Enter the elements of the matrix row by row (including zeroes):\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int value;
                cin >> value;
                if (value != 0) { // Only store non-zero elements
                    elements.push_back({i, j, value});
                }
            }
        }
    }

    // Function to display the compact representation of the sparse matrix
    void displayCompactMatrix() {
        cout << "Compact Representation of Sparse Matrix:\n";
        cout << "Row\tColumn\tValue\n";
        for (const auto &elem : elements) {
            cout << elem.row << "\t" << elem.col << "\t" << elem.value << endl;
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
