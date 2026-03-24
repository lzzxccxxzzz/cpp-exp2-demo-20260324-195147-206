#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

template <typename T>
class SeqStack {
public:
    explicit SeqStack(int initial_capacity = 16)
        : data_(new T[initial_capacity]), capacity_(initial_capacity), top_(-1) {}

    ~SeqStack() {
        delete[] data_;
    }

    bool empty() const {
        return top_ == -1;
    }

    int size() const {
        return top_ + 1;
    }

    void push(const T& value) {
        if (top_ + 1 == capacity_) {
            expand();
        }
        data_[++top_] = value;
    }

    T pop() {
        if (empty()) {
            throw std::underflow_error("stack is empty");
        }
        return data_[top_--];
    }

    const T& top() const {
        if (empty()) {
            throw std::underflow_error("stack is empty");
        }
        return data_[top_];
    }

private:
    void expand() {
        int new_capacity = capacity_ * 2;
        T* new_data = new T[new_capacity];
        for (int i = 0; i <= top_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    T* data_;
    int capacity_;
    int top_;
};

unsigned long long absoluteValue(long long value) {
    if (value >= 0) {
        return static_cast<unsigned long long>(value);
    }
    return static_cast<unsigned long long>(-(value + 1)) + 1ULL;
}

std::string convertDecimalToBase(long long number, int base) {
    if (base < 1 || base > 9) {
        throw std::invalid_argument("base must be between 1 and 9");
    }

    if (number == 0) {
        return "0";
    }

    const bool negative = number < 0;
    unsigned long long value = absoluteValue(number);

    if (base == 1) {
        std::string unary(static_cast<std::size_t>(value), '1');
        return negative ? "-" + unary : unary;
    }

    SeqStack<char> digit_stack;
    while (value > 0) {
        int digit = static_cast<int>(value % static_cast<unsigned long long>(base));
        digit_stack.push(static_cast<char>('0' + digit));
        value /= static_cast<unsigned long long>(base);
    }

    std::string result;
    if (negative) {
        result.push_back('-');
    }
    while (!digit_stack.empty()) {
        result.push_back(digit_stack.pop());
    }
    return result;
}

bool isOpenBracket(char ch) {
    return ch == '(' || ch == '[';
}

bool isCloseBracket(char ch) {
    return ch == ')' || ch == ']';
}

bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') || (open == '[' && close == ']');
}

bool checkBracketMatching(const std::string& expression, std::string& message) {
    SeqStack<char> bracket_stack;
    SeqStack<int> position_stack;

    for (int i = 0; i < static_cast<int>(expression.size()); ++i) {
        char ch = expression[i];
        if (isOpenBracket(ch)) {
            bracket_stack.push(ch);
            position_stack.push(i);
        } else if (isCloseBracket(ch)) {
            if (bracket_stack.empty()) {
                message = "Extra right bracket at character " + std::to_string(i + 1) + ".";
                return false;
            }

            char open = bracket_stack.pop();
            position_stack.pop();
            if (!isMatchingPair(open, ch)) {
                message = "Bracket type mismatch at character " + std::to_string(i + 1) + ".";
                return false;
            }
        }
    }

    if (!bracket_stack.empty()) {
        int position = position_stack.top();
        message = "Left bracket starting at character " + std::to_string(position + 1) + " is not closed.";
        return false;
    }

    message = "All brackets are matched.";
    return true;
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void runBaseConversion() {
    long long number = 0;
    int base = 0;

    std::cout << "Enter decimal integer n: ";
    if (!(std::cin >> number)) {
        clearInputBuffer();
        std::cout << "Invalid decimal integer input.\n";
        return;
    }

    std::cout << "Enter target base m (1~9): ";
    if (!(std::cin >> base)) {
        clearInputBuffer();
        std::cout << "Invalid base input.\n";
        return;
    }
    clearInputBuffer();

    try {
        std::string converted = convertDecimalToBase(number, base);
        std::cout << number << " in base " << base << " is: " << converted << "\n";
    } catch (const std::exception& ex) {
        std::cout << "Conversion failed: " << ex.what() << "\n";
    }
}

void runBracketCheck() {
    std::string expression;
    std::cout << "Enter expression: ";
    std::getline(std::cin, expression);

    std::string message;
    bool matched = checkBracketMatching(expression, message);
    std::cout << (matched ? "[OK] " : "[FAIL] ") << message << "\n";
}

void printMenu() {
    std::cout << "\n==============================\n";
    std::cout << " Experiment 2: Stack Applications\n";
    std::cout << " 1. Convert decimal number to base m\n";
    std::cout << " 2. Check bracket matching in expression\n";
    std::cout << " 0. Exit\n";
    std::cout << "==============================\n";
    std::cout << "Select: ";
}

int main() {
    while (true) {
        printMenu();

        int choice = -1;
        if (!(std::cin >> choice)) {
            clearInputBuffer();
            std::cout << "Invalid input. Please select again.\n";
            continue;
        }
        clearInputBuffer();

        switch (choice) {
        case 1:
            runBaseConversion();
            break;
        case 2:
            runBracketCheck();
            break;
        case 0:
            std::cout << "Program finished.\n";
            return 0;
        default:
            std::cout << "Unknown option. Please try again.\n";
            break;
        }
    }
}
