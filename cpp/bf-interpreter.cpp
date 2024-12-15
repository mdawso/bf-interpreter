#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

std::string brainfuck_interpreter(const std::string& code, const std::string& input_data = "") {
    std::vector<char> tape(30000, 0);
    std::string output;
    std::stack<int> loop_stack;
    size_t code_ptr = 0, tape_ptr = 0, input_ptr = 0;

    while (code_ptr < code.size()) {
        char command = code[code_ptr];

        switch (command) {
            case '>':
                tape_ptr++;
                break;
            case '<':
                tape_ptr--;
                break;
            case '+':
                tape[tape_ptr] = (tape[tape_ptr] + 1) % 256;
                break;
            case '-':
                tape[tape_ptr] = (tape[tape_ptr] - 1) % 256;
                break;
            case '.':
                output += tape[tape_ptr];
                break;
            case ',':
                if (input_ptr < input_data.size()) {
                    tape[tape_ptr] = input_data[input_ptr++];
                } else {
                    tape[tape_ptr] = 0;
                }
                break;
            case '[':
                if (tape[tape_ptr] == 0) {
                    int open_brackets = 1;
                    while (open_brackets != 0) {
                        code_ptr++;
                        if (code[code_ptr] == '[') open_brackets++;
                        if (code[code_ptr] == ']') open_brackets--;
                    }
                } else {
                    loop_stack.push(code_ptr);
                }
                break;
            case ']':
                if (tape[tape_ptr] != 0) {
                    code_ptr = loop_stack.top();
                } else {
                    loop_stack.pop();
                }
                break;
        }
        code_ptr++;
    }

    return output;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <brainfuck_code_file> [input_data]" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::string input_data = (argc > 2) ? argv[2] : "";

    std::cout << brainfuck_interpreter(code, input_data) << std::endl;

    return 0;
}