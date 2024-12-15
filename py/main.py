import sys

def brainfuck_interpreter(code, input_data=''):
    code = ''.join(filter(lambda x: x in ['>', '<', '+', '-', '.', ',', '[', ']'], code))
    tape = [0] * 30000
    code_ptr = 0
    tape_ptr = 0
    input_ptr = 0
    output = []
    loop_stack = []

    while code_ptr < len(code):
        command = code[code_ptr]

        if command == '>':
            tape_ptr += 1
        elif command == '<':
            tape_ptr -= 1
        elif command == '+':
            tape[tape_ptr] = (tape[tape_ptr] + 1) % 256
        elif command == '-':
            tape[tape_ptr] = (tape[tape_ptr] - 1) % 256
        elif command == '.':
            output.append(chr(tape[tape_ptr]))
        elif command == ',':
            if input_ptr < len(input_data):
                tape[tape_ptr] = ord(input_data[input_ptr])
                input_ptr += 1
            else:
                tape[tape_ptr] = 0
        elif command == '[':
            if tape[tape_ptr] == 0:
                open_brackets = 1
                while open_brackets != 0:
                    code_ptr += 1
                    if code[code_ptr] == '[':
                        open_brackets += 1
                    elif code[code_ptr] == ']':
                        open_brackets -= 1
            else:
                loop_stack.append(code_ptr)
        elif command == ']':
            if tape[tape_ptr] != 0:
                code_ptr = loop_stack[-1]
            else:
                loop_stack.pop()

        code_ptr += 1

    return ''.join(output)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python main.py <brainfuck_code_file> [input_data]")
    else:
        with open(sys.argv[1], 'r') as file:
            code = file.read()
        input_data = sys.argv[2] if len(sys.argv) > 2 else ''
        print(brainfuck_interpreter(code, input_data))