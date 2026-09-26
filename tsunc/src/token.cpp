#include <stdexcept>
#include <tsunc/token.hpp>

namespace tsunc {

token::token(location loc, kind kind) : m_location(loc), m_kind(kind) {
  if (get_value_type() != token::value::type::Null) throw std::invalid_argument { "invalid token kind for null value" };
}

token::token(location loc, kind kind, std::string_view sv) : m_location(loc), m_kind(kind) {
  if (get_value_type() != token::value::type::Sv) throw std::invalid_argument { "invalid token kind for sv value" };
  m_value.sv = sv;
}

token::token(location loc, kind kind, char ch) : m_location(loc), m_kind(kind) {
  if (get_value_type() != token::value::type::Char) throw std::invalid_argument { "invalid token kind for char value" };
  m_value.ch = ch;
}

token::kind token::get_kind() const { return m_kind; }

bool token::is(kind kind) const {
  return m_kind == kind;
}

bool token::is_not(kind kind) const {
  return m_kind != kind;
}

token::location token::get_location() const {
  return m_location;
}

token::value::type token::get_value_type() const {
  switch (m_kind) {
  case kind::Indentifier:  
  case kind::Number:      
  case kind::ShortComment:
  case kind::LongComment:
  case kind::String: return token::value::type::Sv;
  case kind::Char: return token::value::type::Char;

  case kind::LParen:
  case kind::RParen:
  case kind::LBrace:
  case kind::RBrace:
  case kind::LBracket:
  case kind::RBracket: return token::value::type::Null;
 
  case kind::Semicolon:
  case kind::Colon: 
  case kind::Comma:
  case kind::Dot: return token::value::type::Null;

  case kind::Plus:
  case kind::Minus:
  case kind::Star:
  case kind::Slash:
  case kind::Percent: return token::value::type::Null;

  case kind::DoubleLT:
  case kind::DoubleMT:
  case kind::Ampersand:
  case kind::Pipe:
  case kind::Hat:
  case kind::Tilde:
  case kind::DoubleAmpersand:
  case kind::DoublePipe:
  case kind::Exclamation: return token::value::type::Null;
                      
  case kind::DoublePlus:
  case kind::DoubleMinus: return token::value::type::Null;

  case kind::CatEars:
  case kind::At:
  case kind::Hashtag: return token::value::type::Null;

  case kind::Equals:
  case kind::PlusEquals:
  case kind::MinusEquals:
  case kind::StarEquals:
  case kind::SlashEquals:
  case kind::PercentEquals:
  case kind::AmpersandEquals:
  case kind::PipeEquals:
  case kind::HatEquals:
  case kind::DoubleLTEquals:
  case kind::DoubleGTEquals: return token::value::type::Null;
                      
  case kind::DoubleEquals:
  case kind::NotEquals:
  case kind::LessThan:
  case kind::LessEquals:
  case kind::GreaterThan:
  case kind::GreaterEquals:
  case kind::Starship: return token::value::type::Null;

  case kind::Arrow: return token::value::type::Null;

  case kind::Func:
  case kind::Return: return token::value::type::Null;

  case kind::S8:
  case kind::U8:
  case kind::S16:
  case kind::U16:
  case kind::S32:
  case kind::U32:
  case kind::S64:
  case kind::U64: return token::value::type::Null;

  case kind::UnexpectedCharacter: return token::value::type::Char;

  case kind::EndOfFile: return token::value::type::Null;
  }

  // just in case...
  return token::value::type::Null;
}

token::value token::get_raw_value() const {
  return m_value;
}

std::optional<std::string_view> token::try_reading_sv() const {
  if (get_value_type() != token::value::type::Sv) return {};
  return m_value.sv;
}

std::optional<char> token::try_reading_char() const {
  if (get_value_type() != token::value::type::Char) return {};
  return m_value.ch;
}

std::ostream& operator<<(std::ostream& os, const token &token) {
  token::value val = token.get_raw_value(); 

  switch (token.get_kind()) {
  case token::kind::Indentifier: return os << val.sv; 
  case token::kind::Number: return os << val.sv; 
  case token::kind::String: return os << '"' << val.sv << '"';
  case token::kind::Char: return os << '\'' << val.sv << '\'';
  case token::kind::ShortComment: return os << "//" << val.sv;
  case token::kind::LongComment: return os << "/*" << val.sv << "*/";

  case token::kind::LParen: return os << '(';
  case token::kind::RParen: return os << ')';
  case token::kind::LBrace: return os << '{';
  case token::kind::RBrace: return os << '}';
  case token::kind::LBracket: return os << '[';
  case token::kind::RBracket: return os << ']';
 
  case token::kind::Semicolon: return os << ';';
  case token::kind::Colon: return os << ':';
  case token::kind::Comma: return os << ',';
  case token::kind::Dot: return os << '.';
  
  case token::kind::Plus: return os << '+';
  case token::kind::Minus: return os << '-';
  case token::kind::Star: return os << '*';
  case token::kind::Slash: return os << '/';
  case token::kind::Percent: return os << '%';
  
  case token::kind::DoubleLT: return os << ">>";
  case token::kind::DoubleMT: return os << "<<";
  case token::kind::Ampersand: return os << '&';
  case token::kind::Pipe: return os << '|';
  case token::kind::Hat: return os << '^';
  case token::kind::Tilde: return os << '~';
  case token::kind::DoubleAmpersand: return os << "&&";
  case token::kind::DoublePipe: return os << "||";
  case token::kind::Exclamation: return os << '!';
  
  case token::kind::DoublePlus: return os << "++";
  case token::kind::DoubleMinus: return os << "--";
  
  case token::kind::CatEars: return os << "^^";
  case token::kind::At: return os << '@';
  case token::kind::Hashtag: return os << '#';
  
  case token::kind::Equals: return os << '=';
  case token::kind::PlusEquals: return os << "+=";
  case token::kind::MinusEquals: return os << "-=";
  case token::kind::StarEquals: return os << "*=";
  case token::kind::SlashEquals: return os << "/=";
  case token::kind::PercentEquals: return os << "%=";
  case token::kind::AmpersandEquals: return os << "&=";
  case token::kind::PipeEquals: return os << "|=";
  case token::kind::HatEquals: return os << "^=";
  case token::kind::DoubleLTEquals: return os << "<<=";
  case token::kind::DoubleGTEquals: return os << ">>=";
  
  case token::kind::DoubleEquals: return os << "==";
  case token::kind::NotEquals: return os << "!=";
  case token::kind::LessThan: return os << '<';
  case token::kind::LessEquals: return os << "<=";
  case token::kind::GreaterThan: return os << '>';
  case token::kind::GreaterEquals: return os << ">=";
  case token::kind::Starship: return os << "<=>";
  
  case token::kind::Arrow: return os << "->";
  
  case token::kind::Func: return os << "func";
  case token::kind::Return: return os << "return";
  
  case token::kind::S8: return os << "s8";
  case token::kind::U8: return os << "u8";
  case token::kind::S16: return os << "s16";
  case token::kind::U16: return os << "u16";
  case token::kind::S32: return os << "s32";
  case token::kind::U32: return os << "u32";
  case token::kind::S64: return os << "s64";
  case token::kind::U64: return os << "u64";
  
  case token::kind::UnexpectedCharacter: return os << "Unexpected character " << val.ch;
  case token::kind::EndOfFile: return os << "EOF";
  }

  return os;
}
};
