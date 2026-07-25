#ifndef USER_BLOCKCHAIN_HPP
#define USER_BLOCKCHAIN_HPP

#include "header.hpp"
#include "utils.hpp"
#include "rsa.hpp"
#include "path.hpp"

class UserBlockchain {
public:
    void save_all_user_keys();
    void check_and_initialize_keys();
};

#endif 