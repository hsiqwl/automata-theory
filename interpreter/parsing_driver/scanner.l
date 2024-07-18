%{
#include <string>
#include "parsing_driver.h"
#include "grammar.tab.hh"
%}

%option noyywrap nounput noinput debug

id [a-zA-Z_][a-zA-Z_0-9]*
signed_number [0-9]+
unsigned_number [0-9]+u
simple_type signed|unsigned|Cell
ws [ \t]

%{
    #define YY_USER_ACTION drv.move_location_column(yyleng);
%}

%%
%{
    drv.location_step();
    const yy::location& loc = drv.get_location();
%}

{ws}+ drv.location_step();
\n drv.move_location_line(); drv.location_step(); return yy::parser::make_NEW_LINE(loc);
"-" return yy::parser::make_MINUS(loc);
"+" return yy::parser::make_PLUS(loc);
"*" return yy::parser::make_STAR(loc);
"/" return yy::parser::make_SLASH(loc);
"(" return yy::parser::make_LPAREN(loc);
")" return yy::parser::make_RPAREN(loc);
"<-" return yy::parser::make_ASSIGN(loc);
"%" return yy::parser::make_PERCENT(loc);
"<" return yy::parser::make_LESS(loc);
">" return yy::parser::make_GREATER(loc);
"=" return yy::parser::make_EQUAL(loc);
"const" return yy::parser::make_CONST(loc);
"matrix" return yy::parser::make_MATRIX(loc);
{simple_type} return yy::parser::make_SIMPLE_TYPE(std::string(yytext), loc);
{id} return yy::parser::make_IDENTIFIER(yytext, loc);
{signed_number} return yy::parser::make_SIGNED_NUM(std::stol(std::string(yytext)), loc);
{unsigned_number} return yy::parser::make_UNSIGNED_NUM(std::stol(std::string(yytext)), loc);
. {
    throw yy::parser::syntax_error(loc, "invalid Symbol:" + std::string(yytext));
}

<<EOF>> return yy::parser::make_YYEOF(loc);
%%

void driver::scan_begin(){
    yy_flex_debug = trace_scanning;
    if(file.empty() || file == "-"){
        yyin = stdin;
    }else if (!(yyin = fopen(file.c_str(), "r"))){
        std::cerr << "cannot open file" << '\n';
        exit(EXIT_FAILURE);
    }
}

void driver::scan_end(){
    fclose(yyin);
}