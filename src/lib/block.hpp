#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "header.hpp"

class Block {
private:
    int block_id;
    json block_data;
    string block_prev_hash;
    string block_curr_hash;
    string block_time;
    int block_nonce;
    int mining_time;
    bool isvalid;

public:
    Block(json data);
    string hash_sha256();

    friend class Blockchain;
};

#endif 
