#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 9
#define STATE_COUNT 7
#define SYMBOL_COUNT 7
#define ALIAS_COUNT 0
#define TOKEN_COUNT 4
#define EXTERNAL_TOKEN_COUNT 3
#define MAX_ALIAS_SEQUENCE_LENGTH 0

enum {
  sym_todo_token = 1,
  sym_todo_body = 2,
  sym__text = 3,
  sym_program = 4,
  sym_todo = 5,
  aux_sym_program_repeat1 = 6,
};

static const char *ts_symbol_names[] = {
  [sym_todo_token] = "todo_token",
  [sym_todo_body] = "todo_body",
  [sym__text] = "_text",
  [ts_builtin_sym_end] = "END",
  [sym_program] = "program",
  [sym_todo] = "todo",
  [aux_sym_program_repeat1] = "program_repeat1",
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [sym_todo_token] = {
    .visible = true,
    .named = true,
  },
  [sym_todo_body] = {
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
  [sym_todo] = {
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
  [1] = {.lex_state = 0, .external_lex_state = 2},
  [2] = {.lex_state = 0, .external_lex_state = 1},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 0, .external_lex_state = 2},
  [5] = {.lex_state = 0, .external_lex_state = 2},
  [6] = {.lex_state = 0, .external_lex_state = 2},
};

enum {
  ts_external_token_todo_token,
  ts_external_token_todo_body,
  ts_external_token__text,
};

static TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {
  [ts_external_token_todo_token] = sym_todo_token,
  [ts_external_token_todo_body] = sym_todo_body,
  [ts_external_token__text] = sym__text,
};

static bool ts_external_scanner_states[3][EXTERNAL_TOKEN_COUNT] = {
  [1] = {
    [ts_external_token_todo_token] = true,
    [ts_external_token_todo_body] = true,
    [ts_external_token__text] = true,
  },
  [2] = {
    [ts_external_token_todo_token] = true,
    [ts_external_token__text] = true,
  },
};

static uint16_t ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [sym_todo_token] = ACTIONS(1),
    [sym_todo_body] = ACTIONS(1),
    [sym__text] = ACTIONS(1),
    [ts_builtin_sym_end] = ACTIONS(1),
  },
  [1] = {
    [sym_program] = STATE(3),
    [sym_todo] = STATE(4),
    [aux_sym_program_repeat1] = STATE(4),
    [sym_todo_token] = ACTIONS(3),
    [sym__text] = ACTIONS(5),
    [ts_builtin_sym_end] = ACTIONS(7),
  },
  [2] = {
    [sym_todo_token] = ACTIONS(9),
    [sym_todo_body] = ACTIONS(11),
    [sym__text] = ACTIONS(9),
    [ts_builtin_sym_end] = ACTIONS(9),
  },
  [3] = {
    [ts_builtin_sym_end] = ACTIONS(13),
  },
  [4] = {
    [sym_todo] = STATE(6),
    [aux_sym_program_repeat1] = STATE(6),
    [sym_todo_token] = ACTIONS(3),
    [sym__text] = ACTIONS(15),
    [ts_builtin_sym_end] = ACTIONS(17),
  },
  [5] = {
    [sym_todo_token] = ACTIONS(19),
    [sym__text] = ACTIONS(19),
    [ts_builtin_sym_end] = ACTIONS(19),
  },
  [6] = {
    [sym_todo] = STATE(6),
    [aux_sym_program_repeat1] = STATE(6),
    [sym_todo_token] = ACTIONS(21),
    [sym__text] = ACTIONS(24),
    [ts_builtin_sym_end] = ACTIONS(27),
  },
};

static TSParseActionEntry ts_parse_actions[] = {
  [0] = {.count = 0, .reusable = false},
  [1] = {.count = 1, .reusable = true}, RECOVER(),
  [3] = {.count = 1, .reusable = true}, SHIFT(2),
  [5] = {.count = 1, .reusable = true}, SHIFT(4),
  [7] = {.count = 1, .reusable = true}, REDUCE(sym_program, 0),
  [9] = {.count = 1, .reusable = true}, REDUCE(sym_todo, 1),
  [11] = {.count = 1, .reusable = true}, SHIFT(5),
  [13] = {.count = 1, .reusable = true}, ACCEPT_INPUT(),
  [15] = {.count = 1, .reusable = true}, SHIFT(6),
  [17] = {.count = 1, .reusable = true}, REDUCE(sym_program, 1),
  [19] = {.count = 1, .reusable = true}, REDUCE(sym_todo, 2),
  [21] = {.count = 2, .reusable = true}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(2),
  [24] = {.count = 2, .reusable = true}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(6),
  [27] = {.count = 1, .reusable = true}, REDUCE(aux_sym_program_repeat1, 2),
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
