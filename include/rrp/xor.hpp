//https://wyliemaster.github.io/gddocs/#/topics/encryption/xor
#pragma once

#include <string_view>
#include <string>

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
/*
#define RRP_XOR_IVM_W_GETTER(T, index, name, xor_key)                                                               \
    ::rrp::IndexedValueMap<T, index, IndexedValueXoredBase64<xor_key, IndexedValueXorBase>> m_##name;                                                     \
    std::string name()                                                                                                 \
    {                                                                                                                  \
        return xor_cycle(::rrp::base64::decode(m_##name.value), xor_key);                                                                  \
    }                                                                                                                  \
    T& name##_raw()                                                                                                    \
    {                                                                                                                  \
        return m_##name.value;                                                                                         \
    }

*/

}