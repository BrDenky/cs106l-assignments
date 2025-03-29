#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(const std::string& source) {
  auto space_iters = find_all(source.begin(), source.end(), isspace);

  std::set<Token> tokens;
  std::transform(
      space_iters.begin(), space_iters.end() - 1,
      space_iters.begin() + 1,
      std::inserter(tokens, tokens.end()),
      [&source](auto it1, auto it2) {
          return Token(source, it1, it2);
      }
  );
  
  std::erase_if(tokens, [](const Token& token) {
      return token.content.empty();
  });
  
  return tokens;
}

std::set<Mispelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  namespace rv = std::ranges::views;
  
  auto misspelled_tokens = source | rv::filter([&dictionary](const Token& token) {
      return !dictionary.contains(token.content);
  });
  
  auto misspellings = misspelled_tokens | rv::transform([&dictionary](const Token& token) {

      auto suggestions_view = dictionary | rv::filter([&token](const std::string& word) {
          return levenshtein(token.content, word) == 1;
      });
      
      std::set<std::string> suggestions(suggestions_view.begin(), suggestions_view.end());
      
      return Mispelling{token, suggestions};
  });
  
  auto valid_misspellings = misspellings | rv::filter([](const Mispelling& m) {
      return !m.suggestions.empty();
  });

  return std::set<Mispelling>(valid_misspellings.begin(), valid_misspellings.end());
}

/* Helper methods */

#include "utils.cpp"