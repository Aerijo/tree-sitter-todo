module.exports = grammar({
  name: "TODO",

  externals: $ => [
    $.todo_token,
    $.todo_body,
    $._text
  ],

  extras: $ => [
    /[^A-Z]+/
  ],

  rules: {
    program: $ => repeat(choice($.todo, $._text)),

    todo: $ => seq($.todo_token, ':', $.todo_body)
  }
})
