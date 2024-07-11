%skeleton "lalr1.cc"
%require "3.8.2"
%header

%define api.token.raw
%define api.token.constructor
%define api.value_.type_ variant
%define parse.assert

%code requires{
    #include "ast.h"
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
    std::unique_ptr<INode> root;
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
%nterm <std::unique_ptr<INode>> arithmetic_operand arithmetic_expr
//%nterm <std::string> simple_matrix_type complex_matrix_type
//%nterm <std::string> var_type

%left PLUS MINUS
%left LESS GREATER EQUAL
%left STAR SLASH PERCENT
%left ASSIGN

%%
program:
    arithmetic_expr NEW_LINE YYEOF {drv.set_ast(ast(std::move($1)));}

arithmetic_operand:
    SIGNED_NUM {
        $$ = std::make_unique<operand_node>("signed");
    }
    | UNSIGNED_NUM {
        $$ = std::make_unique<operand_node>("unsigned");
    }
    ;

arithmetic_expr:
    arithmetic_operand { $$=std::move($1); root = std::move($$);}
    | arithmetic_expr PLUS arithmetic_expr {$$ = std::make_unique<BinaryOpNode>(operation_type::plus, std::move($1), std::move($3));}
    | arithmetic_expr MINUS arithmetic_expr {$$ = std::make_unique<BinaryOpNode>(operation_type::minus, std::move($1), std::move($3));}
    | arithmetic_expr STAR arithmetic_expr {$$ = std::make_unique<BinaryOpNode>(operation_type::star, std::move($1), std::move($3));}
    | arithmetic_expr SLASH arithmetic_expr {$$ = std::make_unique<BinaryOpNode>(operation_type::slash, std::move($1), std::move($3));}
    | arithmetic_expr PERCENT arithmetic_expr {$$ = std::make_unique<BinaryOpNode>(operation_type::percent, std::move($1), std::move($3));}
    | MINUS arithmetic_expr {$$ = std::make_unique<BinaryOpNode>(operation_type::minus, std::move($2));}
    | LPAREN arithmetic_expr RPAREN {$$ = std::move($2);}
    | arithmetic_expr LESS arithmetic_expr {$$ = std::make_unique<BinaryOpNode>(operation_type::less, std::move($1), std::move($3));}
    | arithmetic_expr GREATER arithmetic_expr {$$ = std::make_unique<BinaryOpNode>(operation_type::greater, std::move($1), std::move($3));}
    | arithmetic_expr EQUAL arithmetic_expr {$$ = std::make_unique<BinaryOpNode>(operation_type::equal, std::move($1), std::move($3));}
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

