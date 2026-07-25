#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include "header.hpp"
#include "block.hpp"
#include "utils.hpp"

class Blockchain {
private:
    int difficulty;
    vector<Block> chain;
    string str_difficulty;

public:
    int total_time = 0;
    Blockchain(int difficulty);

    void genesis_block();
    void add_block(json data);
    bool isvalid_block(Block block, Block prev_block);
    bool isvalid_chain();
    void print_block(Block block);
};

#endif 
