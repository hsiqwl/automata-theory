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
%nterm <std::unique_ptr<INode>> arithmetic_operand arithmetic_expr var_decl assign statement
%nterm <std::unique_ptr<StatementListNode>> statement_list
%nterm <std::string> type_info

%left PLUS MINUS
%left LESS GREATER EQUAL
%left STAR SLASH PERCENT
%left ASSIGN

%%
program:
    statement_list YYEOF {drv.tree_ = std::make_unique<Ast>(std::move($1));}
    ;

statement_list:
    statement_list statement NEW_LINE {
        $1->AddStatement(std::move($2));
        $$ = std::move($1);
        }
    | %empty {$$ = std::make_unique<StatementListNode>();}

statement:
    arithmetic_expr {$$ = std::move($1);}
    | assign {$$ = std::move($1);}
    | var_decl {$$ = std::move($1);}
    ;

arithmetic_operand:
    SIGNED_NUM {$$ = std::make_unique<NumericLiteralNode>($1);}
    | UNSIGNED_NUM {$$ = std::make_unique<NumericLiteralNode>($1);}
    | IDENTIFIER {$$ = std::make_unique<VarReferenceNode>($1);}
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

type_info:
    SIMPLE_TYPE {$$ = $1;}
    | MATRIX LESS type_info GREATER {$$ = "matrix<" + $3 + ">";}
    ;

var_decl:
    type_info IDENTIFIER {$$ = std::make_unique<VarDeclNode>($2, $1);}
    | CONST type_info IDENTIFIER {$$ = std::make_unique<VarDeclNode>($3, $2, true);}
    ;

assign:
    IDENTIFIER ASSIGN arithmetic_expr {
        auto var_ref_node = std::make_unique<VarReferenceNode>($1);
        $$ = std::make_unique<AssignNode>(std::move(var_ref_node), std::move($3));
        }
    | var_decl ASSIGN arithmetic_expr {
          auto& var_node = static_cast<VarDeclNode&>(*$1);
          auto var_ref_node = std::make_unique<VarReferenceNode>(var_node.GetName());
          auto assign_node = std::make_unique<AssignNode>(std::move(var_ref_node), std::move($3));
          auto stmt_list = std::make_unique<StatementListNode>();
          stmt_list->AddStatement(std::move($1));
          stmt_list->AddStatement(std::move(assign_node));
          $$ = std::move(stmt_list);
        }
    ;

%%

void yy::parser::error (const location_type& l, const std::string& m){
    std::cerr << l << ": " << m << '\n';
}

