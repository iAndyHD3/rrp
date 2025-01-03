//https://wyliemaster.github.io/gddocs/#/topics/encryption/xor

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

}