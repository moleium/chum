#pragma once

#include <string>

namespace chum {

// The different types of symbols that exist. Might be useful to add even
// more information, such as import_data, str_data, etc.
enum class symbol_type {
  invalid,
  code,
  data
};

// Get the string representation of a symbol type.
inline constexpr char const* serialize_symbol_type(symbol_type const type) {
  switch (type) {
  case symbol_type::code: return "code";
  case symbol_type::data: return "data";
  default: return "invalid";
  }
}

// A symbol ID is essentially a pointer to a symbol that can be used to
// quickly lookup the associated symbol.
struct symbol_id {
  // Index into the symbol array.
  std::uint32_t idx;
};

inline constexpr symbol_id invalid_symbol_id{ 0 };

// A symbol represents a memory address that is not known until link-time.
struct symbol {
  // The symbol ID pointing to this symbol.
  symbol_id id = invalid_symbol_id;

  // The symbol type.
  symbol_type type = symbol_type::invalid;

  union {
    // Valid only for code symbols.
    class basic_block* bb;

    // Valid only for data symbols.
    struct {
      struct data_block* db;

      // This is the offset of the data from the start of the data block.
      std::uint32_t offset;
    };
  };

  // An optional name for this symbol.
  std::string name = "";
};

} // namespace chum

