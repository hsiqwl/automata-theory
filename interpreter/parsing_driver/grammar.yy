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
%nterm <std::unique_ptr<INode>> arithmetic_operand arithmetic_expr assign statement sentence if_clause while_clause
%nterm <std::unique_ptr<VarDeclNode>> var_decl
%nterm <std::unique_ptr<InitializationNode>> initialization
%nterm <std::unique_ptr<StatementListNode>> sentence_list sentence_group program_block
%nterm <std::unique_ptr<FuncDeclNode>> func_decl
%nterm <std::unique_ptr<FuncCallNode>> func_call
%nterm <std::vector<std::unique_ptr<VarDeclNode>>> param_list
%nterm <std::vector<std::unique_ptr<INode>>> argument_list
%nterm <TypeHolder> type_info

%left PLUS MINUS
%left LESS GREATER EQUAL
%left STAR SLASH PERCENT
%left ASSIGN

%%
program:
    program_block YYEOF {drv.tree_ = std::make_unique<Ast>(std::move($1));}

program_block:
    %empty {$$ = std::make_unique<StatementListNode>();}
    | func_decl program_block {
        $2->AddStatement(std::move($1));
        $$ = std::move($2);
        @$ = {@1.begin, @2.end};
        }
    | sentence program_block {
        $2->AddStatement(std::move($1));
        $$ = std::move($2);
        @$ = {@1.begin, @2.end};
        }
    | if_clause program_block {
        $2->AddStatement(std::move($1));
        $$ = std::move($2);
        @$ = {@1.begin, @2.end};
        }
    | while_clause program_block {
        $2->AddStatement(std::move($1));
        $$ = std::move($2);
        @$ = {@1.begin, @2.end};
        }

func_decl:
    FUNC IDENTIFIER LPAREN param_list RPAREN sentence_group {
        location_type loc(@1.begin, @3.end);
        @$ = loc;
        $$ = std::make_unique<FuncDeclNode>($2, std::move($6), std::move($4), loc);
        }
    ;

func_call:
    CALL IDENTIFIER LPAREN argument_list RPAREN {
        location_type loc(@1.begin, @5.end);
        @$ = loc;
        $$ = std::make_unique<FuncCallNode>($2, std::move($4), loc);
        }
    ;

param_list:
    param_list COMMA var_decl {
        $1.emplace($1.begin(), std::move($3));
        $$ = std::move($1);
        @$ = {@1.begin, @3.end};
        }
    | var_decl {
        $$;
        $$.emplace($$.begin(), std::move($1));
        @$ = @1;
        }
    | %empty {}
    ;

argument_list:
    argument_list ARG_DELIMITER IDENTIFIER {
        $1.emplace($1.begin(), std::make_unique<VarReferenceNode>($3, @3));
        $$ = std::move($1);
        @$ = {@1.begin, @3.end};
        }
    | IDENTIFIER {
        $$;
        $$.emplace($$.begin(), std::make_unique<VarReferenceNode>($1, @1));
        @$ = @1;
        }
    | %empty {}
    ;

sentence_group:
    LPAREN sentence_list RPAREN {
        $$ = std::move($2);
        @$ = @2;
        }
    ;

sentence_list:
    sentence_list sentence{
        $1->AddStatement(std::move($2));
        $$ = std::move($1);
        @$ = {@1.begin, @2.end};
        }
    | if_clause {
        $$ = std::make_unique<StatementListNode>();
        $$->AddStatement(std::move($1));
        @$ = @1;
        }
    | while_clause {
        $$ = std::make_unique<StatementListNode>();
        $$->AddStatement(std::move($1));
        @$ = @1;
        }
    | sentence {
        $$ = std::make_unique<StatementListNode>();
        $$->AddStatement(std::move($1));
        @$ = @1;
        }
    ;

sentence:
    statement SEMICOLON {
        $$ = std::move($1);
        @$ = {@1.begin, @2.end};
        }
    ;

statement:
    arithmetic_expr {$$ = std::move($1); @$ = @1;}
    | assign {$$ = std::move($1); @$ = @1;}
    | initialization {$$ = std::move($1); @$ = @1;}
    | %empty {$$ = nullptr;}
    ;

type_info:
    SIMPLE_TYPE {
        if($1 == "signed")
            $$ = {TypeToken::Signed};
        else if($1 == "unsigned")
            $$ = {TypeToken::Unsigned};
        else
            $$ = {TypeToken::Cell};
        @$ = @1;
        }
    | MATRIX LESS type_info GREATER {
        @$ = {@1.begin, @4.end};
        $$ = $3;
        $$.MakeMatrixWrap();
        }
    ;

var_decl:
    type_info IDENTIFIER {
        location_type loc(@1.begin, @2.end);
        @$ = loc;
        $$ = std::make_unique<VarDeclNode>($2, $1, loc);
        }
    | CONST type_info IDENTIFIER {
        location_type loc(@1.begin, @3.end);
        @$ = loc;
        $2.MakeConst();
        $$ = std::make_unique<VarDeclNode>($3, $2, loc, true);
        }
    ;

initialization:
    var_decl {$$ = std::make_unique<InitializationNode>(std::move($1), nullptr, @1); @$ = @1;}
    | var_decl ASSIGN arithmetic_expr {
        location_type loc(@1.begin, @3.end);
        @$ = loc;
        $$ = std::make_unique<InitializationNode>(std::move($1), std::move($3), loc);
        }
    ;

assign:
    IDENTIFIER ASSIGN arithmetic_expr {
        auto var_ref_node = std::make_unique<VarReferenceNode>($1, @1);
        location_type loc(@1.begin, @3.end);
        @$ = loc;
        $$ = std::make_unique<AssignNode>(std::move(var_ref_node), std::move($3), loc);
        }
    ;

if_clause:
    TESTONCE LPAREN arithmetic_expr RPAREN sentence_group {
        location_type loc(@1.begin, @5.end);
        @$ = loc;
        $$ = std::make_unique<IfNode>(std::move($3), std::move($5), loc);
        }
    ;

while_clause:
    TESTREP LPAREN arithmetic_expr RPAREN sentence_group {
        location_type loc(@1.begin, @5.end);
        @$ = loc;
        $$ = std::make_unique<WhileNode>(std::move($3), std::move($5), loc);
        }
    ;

arithmetic_operand:
    SIGNED_NUM {$$ = std::make_unique<SignedLiteralNode>($1, @1); @$ = @1;}
    | UNSIGNED_NUM {$$ = std::make_unique<UnsignedLiteralNode>($1, @1); @$ = @1;}
    | IDENTIFIER {$$ = std::make_unique<VarReferenceNode>($1, @1); @$ = @1;}
    | func_call {$$ = std::move($1); @$ = @1;}
    ;

arithmetic_expr:
    arithmetic_operand {
        @$ = @1;
        $$ = std::move($1);
        }
    | arithmetic_expr PLUS arithmetic_expr {
        location_type loc(@1.begin, @3.end);
        @$ = loc;
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Plus, std::move($1), std::move($3), loc);
        }
    | arithmetic_expr MINUS arithmetic_expr {
        location_type loc(@1.begin, @3.end);
        @$ = loc;
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Minus, std::move($1), std::move($3), loc);
        }
    | arithmetic_expr STAR arithmetic_expr {
        location_type loc(@1.begin, @3.end);
        @$ = loc;
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Star, std::move($1), std::move($3), loc);
        }
    | arithmetic_expr SLASH arithmetic_expr {
        location_type loc(@1.begin, @3.end);
        @$ = loc;
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Slash, std::move($1), std::move($3), loc);
        }
    | arithmetic_expr PERCENT arithmetic_expr {
        location_type loc(@1.begin, @3.end);
        @$ = loc;
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Percent, std::move($1), std::move($3), loc);
        }
    | MINUS arithmetic_expr {
        location_type loc(@1.begin, @2.end);
        @$ = loc;
        $$ = std::make_unique<UnaryOpNode>(UnaryOpKind::Minus, std::move($2), loc);
        }
    | LPAREN arithmetic_expr RPAREN {
        location_type loc(@1.begin, @3.end);
        @$ = loc;
        $$ = std::move($2);
        }
    | arithmetic_expr LESS arithmetic_expr {
        location_type loc(@1.begin, @3.end);
        @$ = loc;
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Less, std::move($1), std::move($3), loc);
        }
    | arithmetic_expr GREATER arithmetic_expr {
        location_type loc(@1.begin, @3.end);
        @$ = loc;
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Greater, std::move($1), std::move($3), loc);
        }
    | arithmetic_expr EQUAL arithmetic_expr {
        location_type loc(@1.begin, @3.end);
        @$ = loc;
        $$ = std::make_unique<BinaryOpNode>(BinaryOpKind::Equal, std::move($1), std::move($3), loc);
        }
    ;
%%

void yy::parser::error (const location_type& l, const std::string& m){
    std::cerr << l << ": " << m << '\n';
}