#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 9
#define STATE_COUNT 5
#define SYMBOL_COUNT 5
#define ALIAS_COUNT 0
#define TOKEN_COUNT 3
#define EXTERNAL_TOKEN_COUNT 2
#define MAX_ALIAS_SEQUENCE_LENGTH 0

enum {
  sym_todo = 1,
  sym__text = 2,
  sym_program = 3,
  aux_sym_program_repeat1 = 4,
};

static const char *ts_symbol_names[] = {
  [sym_todo] = "todo",
  [sym__text] = "_text",
  [ts_builtin_sym_end] = "END",
  [sym_program] = "program",
  [aux_sym_program_repeat1] = "program_repeat1",
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [sym_todo] = {
    .visible = true,
    .named = true,
  },
  [sym__text] = {
    .visible = false,
    .named = true,
  },
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_program] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_program_repeat1] = {
    .visible = false,
    .named = false,
  },
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  switch (state) {
    case 0:
      if (lookahead == 0)
        ADVANCE(1);
      if ((lookahead < 'A' || lookahead > 'Z'))
        SKIP(0);
      END_STATE();
    case 1:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    default:
      return false;
  }
}

static TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0, .external_lex_state = 1},
  [1] = {.lex_state = 0, .external_lex_state = 1},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0, .external_lex_state = 1},
  [4] = {.lex_state = 0, .external_lex_state = 1},
};

enum {
  ts_external_token_todo,
  ts_external_token__text,
};

static TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {
  [ts_external_token_todo] = sym_todo,
  [ts_external_token__text] = sym__text,
};

static bool ts_external_scanner_states[2][EXTERNAL_TOKEN_COUNT] = {
  [1] = {
    [ts_external_token_todo] = true,
    [ts_external_token__text] = true,
  },
};

static uint16_t ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [sym_todo] = ACTIONS(1),
    [sym__text] = ACTIONS(1),
    [ts_builtin_sym_end] = ACTIONS(1),
  },
  [1] = {
    [sym_program] = STATE(2),
    [aux_sym_program_repeat1] = STATE(3),
    [sym_todo] = ACTIONS(3),
    [sym__text] = ACTIONS(3),
    [ts_builtin_sym_end] = ACTIONS(5),
  },
  [2] = {
    [ts_builtin_sym_end] = ACTIONS(7),
  },
  [3] = {
    [aux_sym_program_repeat1] = STATE(4),
    [sym_todo] = ACTIONS(9),
    [sym__text] = ACTIONS(9),
    [ts_builtin_sym_end] = ACTIONS(11),
  },
  [4] = {
    [aux_sym_program_repeat1] = STATE(4),
    [sym_todo] = ACTIONS(13),
    [sym__text] = ACTIONS(13),
    [ts_builtin_sym_end] = ACTIONS(16),
  },
};

static TSParseActionEntry ts_parse_actions[] = {
  [0] = {.count = 0, .reusable = false},
  [1] = {.count = 1, .reusable = true}, RECOVER(),
  [3] = {.count = 1, .reusable = true}, SHIFT(3),
  [5] = {.count = 1, .reusable = true}, REDUCE(sym_program, 0),
  [7] = {.count = 1, .reusable = true}, ACCEPT_INPUT(),
  [9] = {.count = 1, .reusable = true}, SHIFT(4),
  [11] = {.count = 1, .reusable = true}, REDUCE(sym_program, 1),
  [13] = {.count = 2, .reusable = true}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(4),
  [16] = {.count = 1, .reusable = true}, REDUCE(aux_sym_program_repeat1, 2),
};

void *tree_sitter_TODO_external_scanner_create();
void tree_sitter_TODO_external_scanner_destroy(void *);
bool tree_sitter_TODO_external_scanner_scan(void *, TSLexer *, const bool *);
unsigned tree_sitter_TODO_external_scanner_serialize(void *, char *);
void tree_sitter_TODO_external_scanner_deserialize(void *, const char *, unsigned);

#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_TODO() {
  static TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .symbol_metadata = ts_symbol_metadata,
    .parse_table = (const unsigned short *)ts_parse_table,
    .parse_actions = ts_parse_actions,
    .lex_modes = ts_lex_modes,
    .symbol_names = ts_symbol_names,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .lex_fn = ts_lex,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .external_scanner = {
      (const bool *)ts_external_scanner_states,
      ts_external_scanner_symbol_map,
      tree_sitter_TODO_external_scanner_create,
      tree_sitter_TODO_external_scanner_destroy,
      tree_sitter_TODO_external_scanner_scan,
      tree_sitter_TODO_external_scanner_serialize,
      tree_sitter_TODO_external_scanner_deserialize,
    },
  };
  return &language;
}
