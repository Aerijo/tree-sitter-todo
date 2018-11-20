#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <cwctype>
#include <cstring>

#include "tree_sitter/parser.h"

#define RETURN_AS_TEXT \
  lexer->advance(lexer, true); \
  lexer->mark_end(lexer); \
  lexer->result_symbol = TEXT; \
  return true;


namespace {

using std::string;

enum TokenType {
  TODO_TOKEN,
  TODO_BODY,
  TEXT
};

struct Scanner {

  bool ignore_case = false;
  bool get_entire_line = true;
  bool require_word_boundary = true;

  bool require_delim = false; // TODO: support this
  char delim_character = '\0';

  std::set<string> todo_names = {
    "TODO",
    "FIXME",
    "CHANGED",
    "XXX",
    "IDEA",
    "HACK",
    "NOTE",
    "REVIEW",
    "NB",
    "BUG",
    "QUESTION",
    "COMBAK",
    "TEMP",
    "DEBUG",
    "OPTIMIZE",
    "WARNING"
  };

  Scanner() {
    // TODO: Add user defined words and settings here
  }

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
      } else if (islower(lexer->lookahead)) {
        if (ignore_case) {
          name += toupper(lexer->lookahead);
          lexer->advance(lexer, false);
        } else {
          RETURN_AS_TEXT
        }
      } else {
        if (!require_word_boundary || !(isdigit(lexer->lookahead) || lexer->lookahead == '_')) {
          break;
        } else {
          RETURN_AS_TEXT
        }
      }
    }

    lexer->mark_end(lexer);

    if (todo_names.find(name) != todo_names.end()) {
      lexer->result_symbol = TODO_TOKEN;
    } else {
      lexer->result_symbol = TEXT;
    }

    return true;
  }

  bool scan_todo_body(TSLexer *lexer) {
    if (lexer->lookahead == '\n') {
      RETURN_AS_TEXT
    };

    while (lexer->lookahead && lexer->lookahead != '\n') {
      lexer->advance(lexer, false);
    }

    lexer->mark_end(lexer);
    lexer->result_symbol = TODO_BODY;
    return true;
  }

  bool scan_text(TSLexer *lexer) {
    bool next_can_be_todo = true;

    while (lexer->lookahead) {
      if (next_can_be_todo && isupper(lexer->lookahead)) break;

      next_can_be_todo = !(isalnum(lexer->lookahead) || lexer->lookahead == '_');
      lexer->advance(lexer, true);
    }

    lexer->mark_end(lexer);
    lexer->result_symbol = TEXT;
    return true;
  }

  bool scan(TSLexer *lexer, const bool *valid_symbols)
  {
    if (!lexer->lookahead) return false;

    if (valid_symbols[TODO_BODY] && get_entire_line) {
      return scan_todo_body(lexer);
    }

    if (valid_symbols[TODO_TOKEN] && valid_symbols[TEXT] && isupper(lexer->lookahead)) {
      return scan_todo(lexer, valid_symbols);
    } else if (valid_symbols[TODO_TOKEN] && valid_symbols[TEXT]) {
      return scan_text(lexer);
    } else {
      RETURN_AS_TEXT
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
