#pragma once
#include <string>
#include <vector>
#include <rrp/rrp.hpp>

namespace rrp::base64
{
inline const char base64_url_alphabet[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_'};

inline std::string encode(std::string_view in)
{
    std::string out;
    int val = 0, valb = -6;
    size_t len = in.length();
    unsigned int i = 0;
    for (i = 0; i < len; i++)
    {
        unsigned char c = in[i];
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0)
        {
            out.push_back(base64_url_alphabet[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6)
    {
        out.push_back(base64_url_alphabet[((val << 8) >> (valb + 8)) & 0x3F]);
    }
    return out;
}

inline std::string decode(std::string_view in)
{
    std::string out;
    std::vector<int> T(256, -1);
    unsigned int i;
    for (i = 0; i < 64; i++)
        T[base64_url_alphabet[i]] = i;

    int val = 0, valb = -8;
    for (i = 0; i < in.length(); i++)
    {
        unsigned char c = in[i];
        if (T[c] == -1)
            break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0)
        {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

template <typename T> struct Base64Wrapper {
    static T parse(std::string_view str)
    {
        return T::template parse<T>(decode(str));
    }
};


#define RRP_B64_IVM_W_GETTER(T, index, name)                                                                           \
    ::rrp::IndexedValueMap<T, index, IndexedValueBase64> m_##name;                                                                         \
    std::string name()                                                                                                 \
    {                                                                                                                  \
        return ::rrp::base64::decode(m_##name.value);                                                                  \
    }                                                                                                                  \
    T& name##_raw()                                                                                                    \
    {                                                                                                                  \
        return m_##name.value;                                                                                         \
    }

} // namespace rrp::base64