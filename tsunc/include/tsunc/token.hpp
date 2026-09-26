#ifndef TSUNC_TOKEN_HPP
#define TSUNC_TOKEN_HPP

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <string_view>

namespace tsunc {

class token {
public:
  enum class kind : std::uint8_t {
    Indentifier,
    Number,
    String,
    Char,
    ShortComment,
    LongComment,

    // Symbols
    LParen, /**< `(` */
    RParen, /**< `)` */
    LBrace, /**< `{` */
    RBrace, /**< `}` */
    LBracket, /**< `[` */
    RBracket, /**< `]` */

    Semicolon, /**< `;` */
    Colon, /**< `:` */
    Comma, /**< `,` */
    Dot, /**< `.` */

    Plus, /**< `+` */
    Minus, /**< `-` */
    Star, /**< `*` */
    Slash, /**< `/` */
    Percent, /**< `%` */
    
    DoubleLT, /**< `<<` */
    DoubleMT, /**< `>>` */
    Ampersand, /**< `&` */
    Pipe, /**< `|` */
    Hat, /**< `^` */
    Tilde, /**< `~` */
    DoubleAmpersand, /**< `&&` */
    DoublePipe, /**< `||` */
    Exclamation, /**< `!` */

    DoublePlus, /**< `++` */
    DoubleMinus, /**< `--` */

    CatEars, /**< `^^` */
    At, /**< `@` */
    Hashtag, /**< `#` */

    Equals, /**< `=` */
    PlusEquals, /**< `+=` */
    MinusEquals, /**< `-=` */
    StarEquals, /**< `*=` */
    SlashEquals,  /**< `/=` */
    PercentEquals, /**< `%=` */
    AmpersandEquals, /**< `&=` */
    PipeEquals, /**< `|=` */
    HatEquals, /**< `^=` */
    DoubleLTEquals, /**< `<<=` */
    DoubleGTEquals, /**< `>>=` */

    DoubleEquals, /**< `==` */
    NotEquals, /**< `!=` */
    LessThan, /**< `<` */
    LessEquals, /**< `<=` */
    GreaterThan, /**< `>` */
    GreaterEquals, /**< `>=` */
    Starship, /**< `<=>` */

    Arrow, /**< `->` */

    // Keywords
    Func, /**< `func` */
    Return, /**< `return` */
    
    S8, /**< `s8` */
    U8, /**< `u8` */ 
    S16, /**< `s16` */
    U16, /**< `u16` */
    S32, /**< `s32` */
    U32, /**< `u32` */
    S64, /**< `s64` */
    U64, /**< `u64` */
 
    // Error
    UnexpectedCharacter,

    EndOfFile,
  };

  union value {
    enum class type : std::uint8_t {
      Null,
      Sv,
      Char,
    };

    std::nullptr_t null = nullptr;
    std::string_view sv;
    char ch;
  };

  struct location {
    std::string_view filepath;
    std::size_t row = 0;
    std::size_t column = 0;
  };
private:
  kind m_kind;
  value m_value;
  location m_location;
public:
  token(location loc, kind kind);
  token(location loc, kind kind, std::string_view sv);
  token(location loc, kind kind, char ch);

  [[nodiscard]] kind get_kind() const;

  [[nodiscard]] bool is(kind kind) const;
  
  template <kind... ks>
  [[nodiscard]] bool is_one_of() const {
    return (is(ks) || ...);
  }

  [[nodiscard]] bool is_not(kind kind) const;

  template <kind... ks>
  [[nodiscard]] bool is_none_of() const {
    return (is_not(ks) && ...);
  }

  [[nodiscard]] location get_location() const;

  [[nodiscard]] value::type get_value_type() const;
  
  [[nodiscard]] value get_raw_value() const;

  [[nodiscard]] std::optional<std::string_view> try_reading_sv() const;
  [[nodiscard]] std::optional<char> try_reading_char() const;

};

std::ostream& operator<<(std::ostream& os, const token &token);

}; // namespace tsunc

#endif
