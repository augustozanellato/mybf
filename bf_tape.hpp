#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <assert.h>
template <typename cell_type>
class BrainfuckTape
{
private:
    /* data */
    std::vector<cell_type> tape;
    size_t index = 0;
public:
    BrainfuckTape(/* args */);
    ~BrainfuckTape();
    void advance(int amount = 1);
    void recede(int amount = 1);
    void set(cell_type value);
    cell_type get();
    void increment(int value = 1);
    void decrement(int value = 1);
    size_t get_position();
};

template <typename cell_type>
BrainfuckTape<cell_type>::BrainfuckTape()
{
    tape.push_back(0);
}

template <typename cell_type>
BrainfuckTape<cell_type>::~BrainfuckTape()
{
}

template <typename cell_type>
void BrainfuckTape<cell_type>::advance(int amount)
{
    index += amount;
    while (index + 1 >= tape.size()){
        tape.push_back(0);
    }
}

template <typename cell_type>
void BrainfuckTape<cell_type>::recede(int amount)
{
    index -= amount;
    assert(index >= 0);
}

template <typename cell_type>
void BrainfuckTape<cell_type>::set(cell_type value)
{
    assert(index < tape.size());
    tape[index] = value;
}

template <typename cell_type>
cell_type BrainfuckTape<cell_type>::get()
{
    assert(index < tape.size());
    return tape[index];
}

template <typename cell_type>
void BrainfuckTape<cell_type>::increment(int value)
{
    assert(index < tape.size());
    tape[index] += value;
}

template <typename cell_type>
void BrainfuckTape<cell_type>::decrement(int value)
{
    assert(index < tape.size());
    tape[index] -= value;
}

template <typename cell_type>
size_t BrainfuckTape<cell_type>::get_position(){
    return index;
}

