#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <cwctype>
#include <cstring>
#include <iostream>

#include "tree_sitter/parser.h"


namespace {

using std::vector;
using std::string;
using std::map;

enum TokenType {
  TODO,
  TEXT
};

struct Scanner {

  Scanner() {}

  unsigned serialize(char *buffer) {
    return 0;
  }

  void deserialize(const char *buffer, unsigned length) {

  }

  bool scan_todo(TSLexer *lexer, const bool *valid_symbols) {
    string name;

    while (lexer->lookahead) {
      if (isupper(lexer->lookahead)) {
        name += lexer->lookahead;
        lexer->advance(lexer, false);
      } else if (lexer->lookahead == ':') {
        break;
      } else {
        lexer->advance(lexer, true);
        lexer->mark_end(lexer);
        lexer->result_symbol = TEXT;
        return true;
      }
    }

    while (lexer->lookahead && lexer->lookahead != '\n') lexer->advance(lexer, false);

    lexer->mark_end(lexer);
    lexer->result_symbol = TODO;
    return true;
  }

  bool scan_text(TSLexer *lexer) {
    while (lexer->lookahead && !isupper(lexer->lookahead)) {
      lexer->advance(lexer, true);
    }

    lexer->mark_end(lexer);
    lexer->result_symbol = TEXT;
    return true;
  }

  bool scan(TSLexer *lexer, const bool *valid_symbols)
  {
    if (!lexer->lookahead) return false;

    if (valid_symbols[TODO] && valid_symbols[TEXT] && isupper(lexer->lookahead)) {
      return scan_todo(lexer, valid_symbols);
    } else if (valid_symbols[TODO] && valid_symbols[TEXT]) {
      return scan_text(lexer);
    } else {
      lexer->advance(lexer, true);
      lexer->mark_end(lexer);
      lexer->result_symbol = TEXT;
      return true;
    }
  }

};

}


// Source for required functions:
// https://github.com/tree-sitter/tree-sitter/blob/78b54810a62580537b0a2df7eb781e03667d63ba/src/compiler/generate_code/c_code.cc#L546-L552

extern "C" {

void *tree_sitter_TODO_external_scanner_create() {
  return new Scanner();
}

bool tree_sitter_TODO_external_scanner_scan(void *payload, TSLexer *lexer, const bool *valid_symbols) {
  Scanner *scanner = static_cast<Scanner *>(payload);
  return scanner->scan(lexer, valid_symbols);
}

unsigned tree_sitter_TODO_external_scanner_serialize(void *payload, char *buffer) {
  Scanner *scanner = static_cast<Scanner *>(payload);
  return scanner->serialize(buffer);
}

void tree_sitter_TODO_external_scanner_deserialize(void *payload, const char *buffer, unsigned length) {
  Scanner *scanner = static_cast<Scanner *>(payload);
  scanner->deserialize(buffer, length);
}

void tree_sitter_TODO_external_scanner_destroy(void *payload) {
  Scanner *scanner = static_cast<Scanner *>(payload);
  delete scanner;
}

}
