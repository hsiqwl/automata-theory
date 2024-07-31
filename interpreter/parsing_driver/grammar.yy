%skeleton "lalr1.cc"
%require "3.8.2"
%header

%define api.token.raw
%define api.token.constructor
%define api.value.type variant
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
    ARG_DELIMITER
    CALL
    FUNC
    TESTREP
    TESTONCE
    TOP
    BOTTOM
    LEFT
    RIGHT
    MATRIX
    COMMA
;

%token <std::string> IDENTIFIER
%token <int> SIGNED_NUM
%token <unsigned int> UNSIGNED_NUM
%token <std::string> SIMPLE_TYPE
%nterm <std::unique_ptr<INode>> arithmetic_operand arithmetic_expr assign statement sentence
%nterm <std::unique_ptr<VarDeclNode>> var_decl
%nterm <std::unique_ptr<InitializationNode>> initialization
%nterm <std::unique_ptr<StatementListNode>> sentence_list sentence_group
%nterm <TypeHolder> type_info

%left PLUS MINUS
%left LESS GREATER EQUAL
%left STAR SLASH PERCENT
%left ASSIGN

%%
program:
    program_block YYEOF {}

program_block:
    %empty {}
    | func_decl program_block {}
    | sentence program_block {}
    | if_clause program_block {}
    | for_clause program_block {}

func_decl:
    FUNC IDENTIFIER LPAREN param_list RPAREN sentence_group {}
    ;

func_call:
    CALL IDENTIFIER LPAREN argument_list RPAREN {}
    ;

param_list:
    param_list COMMA var_decl {}
    | var_decl {}
    ;

argument_list:
    argument_list ARG_DELIMITER IDENTIFIER {}
    | IDENTIFIER
    ;

sentence_group:
    LPAREN sentence_list RPAREN {$$ = std::move($2);}
    ;

sentence_list:
    sentence_list sentence{
        $1->AddStatement(std::move($2));
        $$ = std::move($1);
        }
    | if_clause {}
    | for_clause {}
    | sentence {$$ = std::make_unique<StatementListNode>();}
    ;

sentence:
    statement SEMICOLON {$$ = std::move($1);}
    ;

statement:
    arithmetic_expr {$$ = std::move($1);}
    | assign {$$ = std::move($1);}
    | initialization {$$ = std::move($1);}
    | %empty {}
    ;

type_info:
    SIMPLE_TYPE {
        if($1 == "signed")
            $$ = {TypeToken::Signed};
        else if($1 == "unsigned")
            $$ = {TypeToken::Unsigned};
        else
            $$ = {TypeToken::Cell};
        }
    | MATRIX LESS type_info GREATER {
        $$ = $3;
        $$.MakeMatrixWrap();
        }
    ;

var_decl:
    type_info IDENTIFIER {$$ = std::make_unique<VarDeclNode>($2, $1);}
    | CONST type_info IDENTIFIER {
        $2.MakeConst();
        $$ = std::make_unique<VarDeclNode>($3, $2, true);}
    ;

initialization:
    var_decl {$$ = std::make_unique<InitializationNode>(std::move($1));}
    | var_decl ASSIGN arithmetic_expr {$$ = std::make_unique<InitializationNode>(std::move($1), std::move($3));}
    ;

assign:
    IDENTIFIER ASSIGN arithmetic_expr {
        auto var_ref_node = std::make_unique<VarReferenceNode>($1);
        $$ = std::make_unique<AssignNode>(std::move(var_ref_node), std::move($3));
        }
    ;

if_clause:
    TESTONCE LPAREN arithmetic_expr RPAREN sentence_group
    ;

for_clause:
    TESTREP LPAREN arithmetic_expr RPAREN sentence_group
    ;

arithmetic_operand:
    SIGNED_NUM {$$ = std::make_unique<SignedLiteralNode>($1);}
    | UNSIGNED_NUM {$$ = std::make_unique<UnsignedLiteralNode>($1);}
    | IDENTIFIER {$$ = std::make_unique<VarReferenceNode>($1);}
    | func_call {}
    ;

arithmetic_expr:
    arithmetic_operand {
        $$ = std::move($1);
        }
    | arithmetic_expr PLUS arithmetic_expr {
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Plus, std::move($1), std::move($3));
        }
    | arithmetic_expr MINUS arithmetic_expr {
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Minus, std::move($1), std::move($3));
        }
    | arithmetic_expr STAR arithmetic_expr {
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Star, std::move($1), std::move($3));
        }
    | arithmetic_expr SLASH arithmetic_expr {
    $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Slash, std::move($1), std::move($3));
        }
    | arithmetic_expr PERCENT arithmetic_expr {
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Percent, std::move($1), std::move($3));
        }
    | MINUS arithmetic_expr {
        $$ = std::make_unique<UnaryOpNode>(UnaryOpKind::Minus, std::move($2));
        }
    | LPAREN arithmetic_expr RPAREN {
        $$ = std::move($2);
        }
    | arithmetic_expr LESS arithmetic_expr {
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Less, std::move($1), std::move($3));
        }
    | arithmetic_expr GREATER arithmetic_expr {
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Greater, std::move($1), std::move($3));
        }
    | arithmetic_expr EQUAL arithmetic_expr {
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Equal, std::move($1), std::move($3));
        }
    ;

%%

void yy::parser::error (const location_type& l, const std::string& m){
    std::cerr << l << ": " << m << '\n';
}