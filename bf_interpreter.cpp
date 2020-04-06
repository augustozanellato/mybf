#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <fstream>
#include <math.h>

#include "bf_tape.hpp"
#include "bf_opcode.hpp"

constexpr bool debug = false;

int read_bf_program(std::vector<BrainfuckOpcode>& program, std::unordered_map<size_t, size_t>& optimization_map, const std::string& filename)
{
    std::ifstream input_file;
    input_file.open(filename, std::ios::in);
    bool prev_op_optimize_sum = false;
    bool prev_op_optimize_shift = false;
    int sum = 0;
    size_t pc = 0;
    for (char c; input_file >> c; ){
        if (!is_bf_opcode(c)){
            continue;
        }
        BrainfuckOpcode current_op = static_cast<BrainfuckOpcode>(c);
        bool curr_op_optimize_sum = current_op == BrainfuckOpcode::INCREMENT || current_op == BrainfuckOpcode::DECREMENT;
        bool curr_op_optimize_shift = current_op == BrainfuckOpcode::MOVE_LEFT || current_op == BrainfuckOpcode::MOVE_RIGHT;

        if (!curr_op_optimize_shift && prev_op_optimize_shift){
            program.push_back(sum > 0 ? BrainfuckOpcode::MOVE_RIGHT : BrainfuckOpcode::MOVE_LEFT);
            optimization_map[pc++] = abs(sum);
        } else if (!curr_op_optimize_sum && prev_op_optimize_sum){
            program.push_back(sum > 0 ? BrainfuckOpcode::INCREMENT : BrainfuckOpcode::DECREMENT);
            optimization_map[pc++] = abs(sum);
        }

        if (curr_op_optimize_sum){
            if (!prev_op_optimize_sum)
                sum = 0;
            sum += current_op == BrainfuckOpcode::INCREMENT ? 1 : -1;
        } else if (curr_op_optimize_shift) {
            if (!prev_op_optimize_shift)
                sum = 0;
            sum += current_op == BrainfuckOpcode::MOVE_RIGHT ? 1 : -1;
        } else {
            program.push_back(current_op);
            pc++;
        }
        prev_op_optimize_sum = curr_op_optimize_sum;
        prev_op_optimize_shift = curr_op_optimize_shift;
    }
    input_file.close();
    return pc;
}

void optimize_jumps(std::unordered_map<size_t, size_t>& optimization_map, const std::vector<BrainfuckOpcode>& program){
    std::stack<size_t> jump_stack;
    for (size_t i = 0; i < program.size(); i++){
        if (program[i] == BrainfuckOpcode::OPEN_LOOP){
            jump_stack.push(i);
        } else if (program[i] == BrainfuckOpcode::CLOSE_LOOP) {
            const int jump_dst = jump_stack.top();
            optimization_map[jump_dst] = i;
            optimization_map[i] = jump_dst;
            jump_stack.pop();
        }
    }
}

int main(int argc, char const *argv[])
{
    std::string filename = argc > 1 ? argv[1] : "../hello.bf";
    std::vector<BrainfuckOpcode> program;
    std::unordered_map<size_t, size_t> optimization_map;
    
    const int pc_max = read_bf_program(program, optimization_map, filename);
    int pc = 0;

    optimize_jumps(optimization_map, program);

    if constexpr (debug){
        pc = 0;
        //TODO dump human readable version of the interpreted code
        
    }
    BrainfuckTape<uint8_t> tape_memory;

    pc = 0;

    while (pc < pc_max){
        BrainfuckOpcode current_op = program[pc];
        switch (current_op){
            case (BrainfuckOpcode::INCREMENT):
                tape_memory.increment(optimization_map[pc]);
                break;
            case (BrainfuckOpcode::DECREMENT):
                tape_memory.decrement(optimization_map[pc]);
                break;
            case (BrainfuckOpcode::MOVE_LEFT):
                tape_memory.recede(optimization_map[pc]);
                break;
            case (BrainfuckOpcode::MOVE_RIGHT):
                tape_memory.advance(optimization_map[pc]);
                break;
            case (BrainfuckOpcode::OUTPUT):
                std::cout << static_cast<char>(tape_memory.get());
                break;
            case (BrainfuckOpcode::INPUT):
                tape_memory.set(std::cin.get());
                break;
            case (BrainfuckOpcode::OPEN_LOOP):
                if (tape_memory.get() == 0){
                    pc = optimization_map[pc];
                }
                break;
            case (BrainfuckOpcode::CLOSE_LOOP):
                if (tape_memory.get() != 0){
                    pc = optimization_map[pc];
                }
                break;
        }
        pc++;
    }
    std::cout << '\n';
    return 0;
}
