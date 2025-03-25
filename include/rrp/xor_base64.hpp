
#include "rrp/base64.h" // IWYU pragma: export
#include "rrp/xor.hpp"  // IWYU pragma: export

#define RRP_B64_XOR_IVM_W_GETTER(T, index, name, xor_key)                                                              \
    ::rrp::IndexedValueMap<T, index, IndexedValueXored<xor_key, IndexedValueXoredBase64Base>> m_##name;                \
    std::string name()                                                                                                 \
    {                                                                                                                  \
        return xor_cycle(::rrp::base64::decode(m_##name.value), xor_key);                                              \
    }                                                                                                                  \
    T& name##_raw()                                                                                                    \
    {                                                                                                                  \
        return m_##name.value;                                                                                         \
    }
