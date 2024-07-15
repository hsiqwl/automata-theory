%skeleton "lalr1.cc"
%require "3.8.2"
%header

%define api.token.raw
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires{
    #include "ast.h"
    #include "binary_op.h"
    #include "numeric_literal.h"
    #include "unary_op.h"
    #include <string>
    #include <memory>
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
%nterm <Ast> arithmetic_operand arithmetic_expr
//%nterm <std::string> simple_matrix_type complex_matrix_type
//%nterm <std::string> var_type

%left PLUS MINUS
%left LESS GREATER EQUAL
%left STAR SLASH PERCENT
%left ASSIGN

%%
program:
    arithmetic_expr NEW_LINE YYEOF {drv.tree_ = std::make_unique<Ast>(std::move($1));};

arithmetic_operand:
    SIGNED_NUM {
        $$ = Ast{std::make_unique<NumericLiteralNode>($1)};
    }
    | UNSIGNED_NUM {
        $$ = Ast{std::make_unique<NumericLiteralNode>($1)};
    }
    ;

arithmetic_expr:
    arithmetic_operand {$$ = std::move($1);}
    | arithmetic_expr PLUS arithmetic_expr {$$ = Ast{BinaryOpKind::Plus, std::move($1), std::move($3)};}
    | arithmetic_expr MINUS arithmetic_expr {$$ = Ast{BinaryOpKind::Minus, std::move($1), std::move($3)};}
    | arithmetic_expr STAR arithmetic_expr {$$ = Ast{BinaryOpKind::Star, std::move($1), std::move($3)};}
    | arithmetic_expr SLASH arithmetic_expr {$$ = Ast{BinaryOpKind::Slash, std::move($1), std::move($3)};}
    | arithmetic_expr PERCENT arithmetic_expr {$$ = Ast{BinaryOpKind::Percent, std::move($1), std::move($3)};}
    | MINUS arithmetic_expr {$$ = Ast{UnaryOpKind::Minus, std::move($2)};}
    | LPAREN arithmetic_expr RPAREN {$$ = std::move($2);}
    | arithmetic_expr LESS arithmetic_expr {$$ = Ast{BinaryOpKind::Less, std::move($1), std::move($3)};}
    | arithmetic_expr GREATER arithmetic_expr {$$ = Ast{BinaryOpKind::Greater, std::move($1), std::move($3)};}
    | arithmetic_expr EQUAL arithmetic_expr {$$ = Ast{BinaryOpKind::Equal, std::move($1), std::move($3)};}
    ;


/*//for matrix_t declaration
simple_matrix_type:
    MATRIX LESS SIMPLE_TYPE GREATER {$$ = "matrix_t<" + $3 + ">";}
    ;

complex_matrix_type:
    simple_matrix_type
    | MATRIX LESS complex_matrix_type GREATER {$$ = "matrix_t<" + $3 + ">";}
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
*/
%%

void yy::parser::error (const location_type& l, const std::string& m){
    std::cerr << l << ": " << m << '\n';
}

