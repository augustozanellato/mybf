#pragma once
enum class BrainfuckOpcode: char {
    MOVE_RIGHT = '>',
    MOVE_LEFT = '<',
    INCREMENT = '+',
    DECREMENT = '-',
    OUTPUT = '.',
    INPUT = ',',
    OPEN_LOOP = '[',
    CLOSE_LOOP = ']'
};

bool is_bf_opcode(char c){
    BrainfuckOpcode op = static_cast<BrainfuckOpcode>(c);
    return op == BrainfuckOpcode::MOVE_RIGHT
        || op == BrainfuckOpcode::MOVE_LEFT
        || op == BrainfuckOpcode::INCREMENT
        || op == BrainfuckOpcode::DECREMENT
        || op == BrainfuckOpcode::OUTPUT
        || op == BrainfuckOpcode::INPUT
        || op == BrainfuckOpcode::OPEN_LOOP
        || op == BrainfuckOpcode::CLOSE_LOOP;
}