#pragma once
#include <cstddef>
#include <panda/string.h>
#include <panda/basic_string.h>

namespace panda { namespace encode {

using std::size_t;

inline size_t encode_base32_getlen (size_t source_len) { return (source_len + 4) / 5 * 8; }
inline size_t decode_base32_getlen (size_t source_len) { return source_len * 5 / 8; }

size_t encode_base32 (const std::string_view source, char* dest, bool upper = false);
size_t decode_base32 (const std::string_view source, char* dest);

inline panda::string encode_base32 (const std::string_view source, bool upper = false) {
    panda::string ret;
    char* buf = ret.reserve(encode_base32_getlen(source.length()));
    auto len = encode_base32(source, buf, upper);
    ret.length(len);
    return ret;
}

inline panda::string decode_base32 (const std::string_view source) {
    panda::string ret;
    char* buf = ret.reserve(decode_base32_getlen(source.length()));
    auto len = decode_base32(source, buf);
    ret.length(len);
    return ret;
}

}}
