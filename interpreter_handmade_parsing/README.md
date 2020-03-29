# Interpreter: Handmade Parsing
This is the second part of the interpreter handmade implementation. After extracting the tokens in the
lexing part, the tokens are processed and given a representatin in a programming structure during the
parsing phase. In this particular example, the elements in the mathematical expression are converted in
`Elements` structs that implement an eval function. At the end of the parsing phase, a call to the
resulting eval function returns the numerical result.
