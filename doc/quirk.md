<style>
    body { color: black; background-color: beige; }
</style>

module ::= (statements | definition)* 'ENDMARKER'

![](img/module.svg)

definition ::= function | structure

![](img/definition.svg)

statements ::= stmt_row | compound

![](img/statements.svg)

stmt_row ::= (small | 'pass') (';' (small | 'pass'))* 'NEWLINE'

![](img/stmt_row.svg)

small ::= call_or_asg | return | 'break' | 'continue'

![](img/small.svg)

call_or_asg ::= designator (':' type)? ('=' expression)?

![](img/call_or_asg.svg)

type ::= 'NAME'

![](img/type.svg)

return ::= 'return' (expression)?

![](img/return.svg)

compound ::= if | while

![](img/compound.svg)

if ::= 'if' expression ':' suite ('elif' expression ':' suite)* ('else' ':' suite)?

![](img/if.svg)

while ::= 'while' expression ':' suite

![](img/while.svg)

suite ::= stmt_row | stmt_col

![](img/suite.svg)

stmt_col ::= 'NEWLINE' 'INDENT' (statements)+ ''DEDENT'

![](img/stmt_col.svg)

function ::= 'def' 'NAME' '(' (parameters)? ')' ('->' type)? ':' suite

![](img/function.svg)

parameters ::= parameter (',' parameter)*

![](img/parameters.svg)

parameter ::= 'NAME' (':' type)?

![](img/parameter.svg)

expressions ::= expression (',' expression)*

![](img/expressions.svg)

expression ::= or

![](img/expression.svg)

or ::= and ('or' and)*

![](img/or.svg)

and ::= not ('and' not)*

![](img/and.svg)

not ::= ('not' not) | comparison

![](img/not.svg)

comparison ::= bor (relation bor)*

![](img/comparison.svg)

relation ::= '<' | '>' | '==' | '<=' | '>=' | '!='

![](img/relation.svg)

bor ::= bxor ('|' bxor)*

![](img/bor.svg)

bxor ::= band ('^' band)*

![](img/bxor.svg)

band ::= shift ('&' shift)*

![](img/band.svg)

shift ::= arith (('<<' | '>>') arith)*

![](img/shift.svg)

arith ::= term (('-' | '+') term)*

![](img/arith.svg)

term ::= factor (('*' | '/' | '%' | '//') factor)*

![](img/term.svg)

factor ::= power | (('+' | '-' | '~') factor)

![](img/factor.svg)

power ::= designator ('**' factor)?

![](img/power.svg)

designator ::= atom (selector)*

![](img/designator.svg)

atom ::= list | 'NAME' | 'NUMBER' | 'True' | 'False' | 'None' | ('(' expression ')')

![](img/atom.svg)

selector ::= ('(' expressions? ')')
           | ('[' expressions ']')
           | ('.' 'NAME')

![](img/selector.svg)

list ::= '[' expressions? ']'

![](img/list.svg)

structure ::= 'struct' 'NAME' ':' fields

![](img/structure.svg)

fields ::= field_row | field_col

![](img/fields.svg)

field_row ::= field (';' (field | pass))* 'NEWLINE'

![](img/field_row.svg)

field_col ::= 'NEWLINE' 'INDENT' field_row field_row* 'DEDENT'

![](img/field_col.svg)

field ::= 'NAME' (':' type)? ('=' expression)?

![](img/field.svg)
