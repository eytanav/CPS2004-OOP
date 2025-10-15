#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

struct BinOp {
    double operand1;
    double operand2;
    char operation;
};

const int MAX_OPS = 100;

void readExpressionsStructVersion() {
    BinOp* operations = new BinOp[MAX_OPS];
    int count = 0;
    
    std::cout << "Enter expressions in format: number op number (e.g., 5 + 3)" << std::endl;
    std::cout << "Enter 'done' to finish" << std::endl;
    
    // Approach 1: Using >> directly on std::istream
    while (count < MAX_OPS) {
        std::cout << "Expression " << (count + 1) << ": ";
        
        double op1, op2;
        char op;
        
        if (std::cin >> op1 >> op >> op2) {
            operations[count].operand1 = op1;
            operations[count].operand2 = op2;
            operations[count].operation = op;
            count++;
        } else {
            // Clear error state and check if user wants to finish
            std::cin.clear();
            std::string input;
            std::cin >> input;
            if (input == "done") {
                break;
            } else {
                std::cout << "Invalid input! Please use format: number op number" << std::endl;
                std::cin.ignore(1000, '\n');
            }
        }
    }
    
    // Write results to file
    std::ofstream outputFile("results_struct.txt");
    if (!outputFile) {
        std::cerr << "Error creating output file!" << std::endl;
        delete[] operations;
        return;
    }
    
    for (int i = 0; i < count; i++) {
        double result;
        const BinOp& op = operations[i];
        
        switch (op.operation) {
            case '+': result = op.operand1 + op.operand2; break;
            case '-': result = op.operand1 - op.operand2; break;
            case '*': result = op.operand1 * op.operand2; break;
            case '/': 
                if (op.operand2 == 0) {
                    outputFile << op.operand1 << " " << op.operation << " " << op.operand2 << " = Error: Division by zero" << std::endl;
                    continue;
                }
                result = op.operand1 / op.operand2; 
                break;
            default:
                outputFile << op.operand1 << " " << op.operation << " " << op.operand2 << " = Error: Invalid operator" << std::endl;
                continue;
        }
        
        outputFile << op.operand1 << " " << op.operation << " " << op.operand2 << " = " << result << std::endl;
    }
    
    outputFile.close();
    delete[] operations;
    std::cout << "Results written to results_struct.txt" << std::endl;
}

int main() {
    readExpressionsStructVersion();
    return 0;
}