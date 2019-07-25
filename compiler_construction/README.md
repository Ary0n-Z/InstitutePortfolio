#Information

This is training task that contains implementation of lexicon scanner and parser for a part of PASCAL programming language. Scanner scan code.txt and generates lexems and constants tables, according to an existing lexicon.

#Grammar rules
##for Scanner
```
<identifier> :: = letter | <identifier>letter | <identifier>digit
<integer> ::= digit | <integer>digit
<letter> ::= 
A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T |
U | V | W | X | Y | Z | a | b | c | d | e | f | g | h | i | j |
k | l | m | n | o | p | q | r | s | t |
u | v | w | x | y | z 
<digit> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
<delimiter> ::= . | : | ; | , | - | + | [ | ] | ( | ) | >
<delimiter2> ::= <colon>=
<colon> ::= :
```
##for Parser
```
<statement>::=<for statement> | <assignment>
<for statement>::=for <var> [:=<exp>]  to <exp> do <statement>
<assignment>::= <var> := <exp>;
<var>:: =i [(<exp>)] 
<exp>:: =<term>{(- | +) <term>}
<fact>:: =<var> | (<exp>) | number_literal
```