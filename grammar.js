module.exports = grammar({
  name: "TODO",

  externals: $ => [
    $.todo,
    $._text
  ],

  extras: $ => [
    /[^A-Z]+/
  ],

  rules: {
    program: $ => repeat(choice($.todo, $._text)),
  }
})
