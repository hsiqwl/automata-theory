%skeleton "lalr1.cc"
%require "3.8.2"
%header

%define api.token.raw
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires{
    #include "symbol_table.h"
    #include "signed_variable.h"
    #include "unsigned_variable.h"
    #include "cell_variable.h"
    #include "array_variable.h"

    #include <string>
    #include <iostream>
    #include <stdexcept>

    class driver;
}

%param {driver& drv}

%locations

%define parse.trace
%define parse.error detailed
%define parse.lac full

%code{
    #include "parsing_driver.h"
    symbol_table sym_tab;
}

%define api.token.prefix {TOK_}
%token
    ASSIGN
    MINUS
    PLUS
    STAR
    SLASH
    LPAREN
    RPAREN
    PERCENT
    LESS
    GREATER
    EQUAL
    CONST
    NEW_LINE
    SEMICOLON
    PARAM_DELIMITER
    CALL
    FUNC
    TESTREP
    TESTONCE
    TOP
    BOTTOM
    LEFT
    RIGHT
    MATRIX
;

%token <std::string> IDENTIFIER
%token <int> SIGNED_NUM
%token <unsigned int> UNSIGNED_NUM
%token <std::string> SIMPLE_TYPE
%nterm <int> arithmetic_operand arithmetic_expr
%nterm <std::string> simple_matrix_type complex_matrix_type
%nterm <std::string> var_type

%left PLUS MINUS
%left LESS GREATER EQUAL
%left STAR SLASH PERCENT
%left ASSIGN

%%
line:
    line arithmetic_expr NEW_LINE {std::cout << $2 << '\n';}
    | %empty
    ;

arithmetic_operand:
    SIGNED_NUM
    | UNSIGNED_NUM {$$ = static_cast<int>($1);}
    | IDENTIFIER {
        const std::string& var_name = $1;
        if(sym_tab.var_declared(var_name)){
            auto& var = sym_tab.get_var_by_name(var_name);

        }
    }
    ;

arithmetic_expr:
    arithmetic_operand { $$=$1;}
    | arithmetic_expr PLUS arithmetic_expr {$$ = $1 + $3;}
    | arithmetic_expr MINUS arithmetic_expr {$$ = $1 - $3;}
    | arithmetic_expr STAR arithmetic_expr {$$ = $1 * $3;}
    | arithmetic_expr SLASH arithmetic_expr {$$ = $1 / $3;}
    | arithmetic_expr PERCENT arithmetic_expr {$$ = $1 % $3;}
    | MINUS arithmetic_expr {$$ = -$2;}
    | LPAREN arithmetic_expr RPAREN {$$ = $2;}
    | arithmetic_expr LESS arithmetic_expr {if($1 < $3) $$ = 1; else $$ = 0;}
    | arithmetic_expr GREATER arithmetic_expr {if($1 > $3) $$ = 1; else $$ = 0;}
    | arithmetic_expr EQUAL arithmetic_expr {if($1 == $3) $$ = 1; else $$ = 0;}
    ;

//for matrix declaration
simple_matrix_type:
    MATRIX LESS SIMPLE_TYPE GREATER {$$ = "matrix<" + $3 + ">";}
    ;

complex_matrix_type:
    simple_matrix_type
    | MATRIX LESS complex_matrix_type GREATER {$$ = "matrix<" + $3 + ">";}
    ;

var_type:
    SIMPLE_TYPE
    | complex_matrix_type
    ;

declaration:
    CONST var_type IDENTIFIER ASSIGN arithmetic_expr {}
    | var_type IDENTIFIER {}
    | var_type IDENTIFIER ASSIGN arithmetic_expr {}
    ;

%%

void yy::parser::error (const location_type& l, const std::string& m){
    std::cerr << l << ": " << m << '\n';
}

