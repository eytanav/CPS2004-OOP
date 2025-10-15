#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>

class BinOp {
private:
    double operand1;
    double operand2;
    char operation;
    bool isValid;

public:
    BinOp() : operand1(0), operand2(0), operation('+'), isValid(false) {}
    
    // Getters
    double getOperand1() const { return operand1; }
    double getOperand2() const { return operand2; }
    char getOperation() const { return operation; }
    bool getIsValid() const { return isValid; }
    
    // Setters with validation
    void setOperands(double op1, double op2, char op) {
        operand1 = op1;
        operand2 = op2;
        operation = op;
        isValid = true;
        
        // Validate operation
        if (op != '+' && op != '-' && op != '*' && op != '/') {
            isValid = false;
            throw std::invalid_argument("Invalid operator. Use +, -, *, or /");
        }
        
        // Validate division by zero
        if (op == '/' && op2 == 0) {
            isValid = false;
            throw std::runtime_error("Division by zero is not allowed");
        }
    }
    
    // Evaluate the expression
    double evaluate() const {
        if (!isValid) {
            throw std::runtime_error("Cannot evaluate invalid operation");
        }
        
        switch (operation) {
            case '+': return operand1 + operand2;
            case '-': return operand1 - operand2;
            case '*': return operand1 * operand2;
            case '/': 
                if (operand2 == 0) {
                    throw std::runtime_error("Division by zero");
                }
                return operand1 / operand2;
            default:
                throw std::runtime_error("Invalid operation");
        }
    }
    
    // Convert to string representation
    std::string toString() const {
        std::ostringstream oss;
        oss << operand1 << " " << operation << " " << operand2;
        return oss.str();
    }
};

void readExpressionsClassVersion() {
    const int MAX_OPS = 100;
    BinOp* operations = new BinOp[MAX_OPS];
    int count = 0;
    
    std::cout << "Enter expressions in format: number op number (e.g., 5 + 3)" << std::endl;
    std::cout << "Enter 'done' to finish \n" << std::endl;

    
    // Approach 2: Using getline with stringstream
    std::string line;
    
    while (count < MAX_OPS) {
        std::cout << "Expression " << (count + 1) << ": ";
        
        if (!std::getline(std::cin, line) || line == "done") {
            break;
        }
        
        if (line.empty()) {
            continue;
        }
        
        std::istringstream iss(line);
        double op1, op2;
        char op;
        
        if (iss >> op1 >> op >> op2) {
            try {
                operations[count].setOperands(op1, op2, op);
                count++;
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        } else {
            std::cout << "Invalid input format! Please use: number operator number" << std::endl;
        }
    }
    
    // Write results to file
    std::ofstream outputFile("results_class.txt");
    if (!outputFile) {
        std::cerr << "Error creating output file!" << std::endl;
        delete[] operations;
        return;
    }
    
    for (int i = 0; i < count; i++) {
        const BinOp& op = operations[i];
        
        if (!op.getIsValid()) {
            outputFile << op.toString() << " = Invalid operation" << std::endl;
            continue;
        }
        
        try {
            double result = op.evaluate();
            outputFile << op.toString() << " = " << result << std::endl;
        } catch (const std::exception& e) {
            outputFile << op.toString() << " = Error: " << e.what() << std::endl;
        }
    }
    
    outputFile.close();
    delete[] operations;
    std::cout << "Results written to results_class.txt" << std::endl;
}

int main() {
    readExpressionsClassVersion();
    return 0;
}