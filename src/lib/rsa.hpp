#ifndef RSA_HPP
#define RSA_HPP

#include "header.hpp"

class RSAHelper {
public:
    static void generate_and_save_keys(const vector<string>& user_names, 
                                       const string& pub_filename, 
                                       const string& priv_filename);

    static string sign_message(const string& message, const string& private_key_b64);

    static bool verify_signature(const string& message, const string& hex_signature, const string& public_key_b64);
};

#endif 