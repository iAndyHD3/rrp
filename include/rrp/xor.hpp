//https://wyliemaster.github.io/gddocs/#/topics/encryption/xor
#pragma once

#include <string_view>
#include <string>
#include "reflect"
#include <iostream>


namespace rrp
{

inline std::string xor_singular(std::string_view str, int key)
{
    std::string ret;
    ret.reserve(str.size());
    auto it = ret.begin();
    for(auto& c : str)
    {
        *it = static_cast<char>(static_cast<int>(c) ^ key);
        ++it;
    }
    return ret;
}

inline std::string xor_cycle(std::string input, std::string_view key) {
	const size_t keyLen = key.size();
	size_t gjpCurrent = 0;
	for(auto& character : input) {
		character ^= key[gjpCurrent];
		gjpCurrent = (gjpCurrent + 1) % keyLen;
	}
	return input;
}

template<typename T, reflect::fixed_string KEY>
struct XorWrapper
{
    static T parse(std::string_view str)
    {
        std::cout << "input: " << str << "\n";
        auto x = xor_cycle(str, KEY);
        std::cout << "output: " <<  x << '\n';
        return T:: template parse<T>(x);
    }
};


}