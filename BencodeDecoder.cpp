#include "BencodeDecoder.h"
#include "Tokenizer.h"

#include <boost/lexical_cast.hpp>

#include <stdexcept>
#include <deque>


Value BencodeDecoder::decode(const std::string& encoded)
{
  std::vector<std::string> tokens;
  Tokenizer::tokenize(encoded, tokens);

  // TODO: make tokenizer return a deque??
  std::deque<std::string> tokensDeque;
  for (unsigned int i = 0; i < tokens.size(); i++)
    tokensDeque.push_back(tokens[i]);

  return decode(tokensDeque);
}

Value BencodeDecoder::decode(std::deque<std::string>& tokens)
{
  if (tokens.empty())
    throw std::invalid_argument("Encoded data is too short");

  if (tokens.front() == "i") {
    if (tokens.size() < 3)
      throw std::invalid_argument("Encoded data is too short");

    if (tokens[2] != "e")
      throw std::invalid_argument("Incorrect encoding: does not end with 'e'");

    if (tokens[1] == "-0")
      throw std::invalid_argument("Negative zero is not allowed");

    try {
      int value = boost::lexical_cast<int>(tokens[1]);
      tokens.pop_front(); // eat the "i"
      tokens.pop_front(); // eat the the number
      tokens.pop_front(); // eat the "e"
      return Value(value);
    }
    catch (boost::bad_lexical_cast&) {
      throw std::invalid_argument("Incorrect integer: " + tokens[1]);
    }
  }
  else if (tokens.front() == "s") {
    tokens.pop_front(); // eat the "s"
    std::string value = tokens.front();
    tokens.pop_front(); // eat the value
    return Value(value);
  }
  else if (tokens.front() == "l") {
    ValueVector vec;
    tokens.pop_front(); // eat the "l"
    while (tokens.front() != "e")
      vec.push_back(decode(tokens));

    return vec;
  }


  return Value(0);
}

