// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "grammar.tab.hh"


// Unqualified %code blocks.
#line 28 "grammar.yy"

    #include "parsing_driver.h"

#line 50 "grammar.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 142 "grammar.tab.cc"

  /// Build a parser object.
  parser::parser (driver& drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_type_info: // type_info
        value.YY_MOVE_OR_COPY< TypeHolder > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SIGNED_NUM: // SIGNED_NUM
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_SIMPLE_TYPE: // SIMPLE_TYPE
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_call: // func_call
        value.YY_MOVE_OR_COPY< std::unique_ptr<FuncCallNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_decl: // func_decl
        value.YY_MOVE_OR_COPY< std::unique_ptr<FuncDeclNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sentence: // sentence
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_if_clause: // if_clause
      case symbol_kind::S_while_clause: // while_clause
      case symbol_kind::S_arithmetic_operand: // arithmetic_operand
      case symbol_kind::S_arithmetic_expr: // arithmetic_expr
        value.YY_MOVE_OR_COPY< std::unique_ptr<INode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_initialization: // initialization
        value.YY_MOVE_OR_COPY< std::unique_ptr<InitializationNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program_block: // program_block
      case symbol_kind::S_sentence_group: // sentence_group
      case symbol_kind::S_sentence_list: // sentence_list
        value.YY_MOVE_OR_COPY< std::unique_ptr<StatementListNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.YY_MOVE_OR_COPY< std::unique_ptr<VarDeclNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_argument_list: // argument_list
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<INode>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list: // param_list
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<VarDeclNode>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UNSIGNED_NUM: // UNSIGNED_NUM
        value.YY_MOVE_OR_COPY< unsigned int > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_type_info: // type_info
        value.move< TypeHolder > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SIGNED_NUM: // SIGNED_NUM
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_SIMPLE_TYPE: // SIMPLE_TYPE
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_call: // func_call
        value.move< std::unique_ptr<FuncCallNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_decl: // func_decl
        value.move< std::unique_ptr<FuncDeclNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sentence: // sentence
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_if_clause: // if_clause
      case symbol_kind::S_while_clause: // while_clause
      case symbol_kind::S_arithmetic_operand: // arithmetic_operand
      case symbol_kind::S_arithmetic_expr: // arithmetic_expr
        value.move< std::unique_ptr<INode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_initialization: // initialization
        value.move< std::unique_ptr<InitializationNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program_block: // program_block
      case symbol_kind::S_sentence_group: // sentence_group
      case symbol_kind::S_sentence_list: // sentence_list
        value.move< std::unique_ptr<StatementListNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.move< std::unique_ptr<VarDeclNode> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_argument_list: // argument_list
        value.move< std::vector<std::unique_ptr<INode>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<std::unique_ptr<VarDeclNode>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UNSIGNED_NUM: // UNSIGNED_NUM
        value.move< unsigned int > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_type_info: // type_info
        value.copy< TypeHolder > (that.value);
        break;

      case symbol_kind::S_SIGNED_NUM: // SIGNED_NUM
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_SIMPLE_TYPE: // SIMPLE_TYPE
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_func_call: // func_call
        value.copy< std::unique_ptr<FuncCallNode> > (that.value);
        break;

      case symbol_kind::S_func_decl: // func_decl
        value.copy< std::unique_ptr<FuncDeclNode> > (that.value);
        break;

      case symbol_kind::S_sentence: // sentence
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_if_clause: // if_clause
      case symbol_kind::S_while_clause: // while_clause
      case symbol_kind::S_arithmetic_operand: // arithmetic_operand
      case symbol_kind::S_arithmetic_expr: // arithmetic_expr
        value.copy< std::unique_ptr<INode> > (that.value);
        break;

      case symbol_kind::S_initialization: // initialization
        value.copy< std::unique_ptr<InitializationNode> > (that.value);
        break;

      case symbol_kind::S_program_block: // program_block
      case symbol_kind::S_sentence_group: // sentence_group
      case symbol_kind::S_sentence_list: // sentence_list
        value.copy< std::unique_ptr<StatementListNode> > (that.value);
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.copy< std::unique_ptr<VarDeclNode> > (that.value);
        break;

      case symbol_kind::S_argument_list: // argument_list
        value.copy< std::vector<std::unique_ptr<INode>> > (that.value);
        break;

      case symbol_kind::S_param_list: // param_list
        value.copy< std::vector<std::unique_ptr<VarDeclNode>> > (that.value);
        break;

      case symbol_kind::S_UNSIGNED_NUM: // UNSIGNED_NUM
        value.copy< unsigned int > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_type_info: // type_info
        value.move< TypeHolder > (that.value);
        break;

      case symbol_kind::S_SIGNED_NUM: // SIGNED_NUM
        value.move< int > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_SIMPLE_TYPE: // SIMPLE_TYPE
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_func_call: // func_call
        value.move< std::unique_ptr<FuncCallNode> > (that.value);
        break;

      case symbol_kind::S_func_decl: // func_decl
        value.move< std::unique_ptr<FuncDeclNode> > (that.value);
        break;

      case symbol_kind::S_sentence: // sentence
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_if_clause: // if_clause
      case symbol_kind::S_while_clause: // while_clause
      case symbol_kind::S_arithmetic_operand: // arithmetic_operand
      case symbol_kind::S_arithmetic_expr: // arithmetic_expr
        value.move< std::unique_ptr<INode> > (that.value);
        break;

      case symbol_kind::S_initialization: // initialization
        value.move< std::unique_ptr<InitializationNode> > (that.value);
        break;

      case symbol_kind::S_program_block: // program_block
      case symbol_kind::S_sentence_group: // sentence_group
      case symbol_kind::S_sentence_list: // sentence_list
        value.move< std::unique_ptr<StatementListNode> > (that.value);
        break;

      case symbol_kind::S_var_decl: // var_decl
        value.move< std::unique_ptr<VarDeclNode> > (that.value);
        break;

      case symbol_kind::S_argument_list: // argument_list
        value.move< std::vector<std::unique_ptr<INode>> > (that.value);
        break;

      case symbol_kind::S_param_list: // param_list
        value.move< std::vector<std::unique_ptr<VarDeclNode>> > (that.value);
        break;

      case symbol_kind::S_UNSIGNED_NUM: // UNSIGNED_NUM
        value.move< unsigned int > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // Discard the LAC context in case there still is one left from a
    // previous invocation.
    yy_lac_discard_ ("init");

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        if (!yy_lac_establish_ (yyla.kind ()))
          goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    yy_lac_discard_ ("shift");
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_type_info: // type_info
        yylhs.value.emplace< TypeHolder > ();
        break;

      case symbol_kind::S_SIGNED_NUM: // SIGNED_NUM
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_SIMPLE_TYPE: // SIMPLE_TYPE
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_func_call: // func_call
        yylhs.value.emplace< std::unique_ptr<FuncCallNode> > ();
        break;

      case symbol_kind::S_func_decl: // func_decl
        yylhs.value.emplace< std::unique_ptr<FuncDeclNode> > ();
        break;

      case symbol_kind::S_sentence: // sentence
      case symbol_kind::S_statement: // statement
      case symbol_kind::S_assign: // assign
      case symbol_kind::S_if_clause: // if_clause
      case symbol_kind::S_while_clause: // while_clause
      case symbol_kind::S_arithmetic_operand: // arithmetic_operand
      case symbol_kind::S_arithmetic_expr: // arithmetic_expr
        yylhs.value.emplace< std::unique_ptr<INode> > ();
        break;

      case symbol_kind::S_initialization: // initialization
        yylhs.value.emplace< std::unique_ptr<InitializationNode> > ();
        break;

      case symbol_kind::S_program_block: // program_block
      case symbol_kind::S_sentence_group: // sentence_group
      case symbol_kind::S_sentence_list: // sentence_list
        yylhs.value.emplace< std::unique_ptr<StatementListNode> > ();
        break;

      case symbol_kind::S_var_decl: // var_decl
        yylhs.value.emplace< std::unique_ptr<VarDeclNode> > ();
        break;

      case symbol_kind::S_argument_list: // argument_list
        yylhs.value.emplace< std::vector<std::unique_ptr<INode>> > ();
        break;

      case symbol_kind::S_param_list: // param_list
        yylhs.value.emplace< std::vector<std::unique_ptr<VarDeclNode>> > ();
        break;

      case symbol_kind::S_UNSIGNED_NUM: // UNSIGNED_NUM
        yylhs.value.emplace< unsigned int > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: program_block $end
#line 82 "grammar.yy"
                        {drv.tree_ = std::make_unique<Ast>(std::move(yystack_[1].value.as < std::unique_ptr<StatementListNode> > ()));}
#line 832 "grammar.tab.cc"
    break;

  case 3: // program_block: %empty
#line 85 "grammar.yy"
           {yylhs.value.as < std::unique_ptr<StatementListNode> > () = std::make_unique<StatementListNode>();}
#line 838 "grammar.tab.cc"
    break;

  case 4: // program_block: func_decl program_block
#line 86 "grammar.yy"
                              {
        yystack_[0].value.as < std::unique_ptr<StatementListNode> > ()->AddStatement(std::move(yystack_[1].value.as < std::unique_ptr<FuncDeclNode> > ()));
        yylhs.value.as < std::unique_ptr<StatementListNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<StatementListNode> > ());
        yylhs.location = {yystack_[1].location.begin, yystack_[0].location.end};
        }
#line 848 "grammar.tab.cc"
    break;

  case 5: // program_block: sentence program_block
#line 91 "grammar.yy"
                             {
        yystack_[0].value.as < std::unique_ptr<StatementListNode> > ()->AddStatement(std::move(yystack_[1].value.as < std::unique_ptr<INode> > ()));
        yylhs.value.as < std::unique_ptr<StatementListNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<StatementListNode> > ());
        yylhs.location = {yystack_[1].location.begin, yystack_[0].location.end};
        }
#line 858 "grammar.tab.cc"
    break;

  case 6: // program_block: if_clause program_block
#line 96 "grammar.yy"
                              {
        yystack_[0].value.as < std::unique_ptr<StatementListNode> > ()->AddStatement(std::move(yystack_[1].value.as < std::unique_ptr<INode> > ()));
        yylhs.value.as < std::unique_ptr<StatementListNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<StatementListNode> > ());
        yylhs.location = {yystack_[1].location.begin, yystack_[0].location.end};
        }
#line 868 "grammar.tab.cc"
    break;

  case 7: // program_block: while_clause program_block
#line 101 "grammar.yy"
                                 {
        yystack_[0].value.as < std::unique_ptr<StatementListNode> > ()->AddStatement(std::move(yystack_[1].value.as < std::unique_ptr<INode> > ()));
        yylhs.value.as < std::unique_ptr<StatementListNode> > () = std::move(yystack_[0].value.as < std::unique_ptr<StatementListNode> > ());
        yylhs.location = {yystack_[1].location.begin, yystack_[0].location.end};
        }
#line 878 "grammar.tab.cc"
    break;

  case 8: // func_decl: FUNC IDENTIFIER LPAREN param_list RPAREN sentence_group
#line 108 "grammar.yy"
                                                            {
        location_type loc(yystack_[5].location.begin, yystack_[3].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<FuncDeclNode> > () = std::make_unique<FuncDeclNode>(yystack_[4].value.as < std::string > (), std::move(yystack_[0].value.as < std::unique_ptr<StatementListNode> > ()), std::move(yystack_[2].value.as < std::vector<std::unique_ptr<VarDeclNode>> > ()), loc);
        }
#line 888 "grammar.tab.cc"
    break;

  case 9: // func_call: CALL IDENTIFIER LPAREN argument_list RPAREN
#line 116 "grammar.yy"
                                                {
        location_type loc(yystack_[4].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<FuncCallNode> > () = std::make_unique<FuncCallNode>(yystack_[3].value.as < std::string > (), std::move(yystack_[1].value.as < std::vector<std::unique_ptr<INode>> > ()), loc);
        }
#line 898 "grammar.tab.cc"
    break;

  case 10: // param_list: param_list COMMA var_decl
#line 124 "grammar.yy"
                              {
        yystack_[2].value.as < std::vector<std::unique_ptr<VarDeclNode>> > ().emplace(yystack_[2].value.as < std::vector<std::unique_ptr<VarDeclNode>> > ().begin(), std::move(yystack_[0].value.as < std::unique_ptr<VarDeclNode> > ()));
        yylhs.value.as < std::vector<std::unique_ptr<VarDeclNode>> > () = std::move(yystack_[2].value.as < std::vector<std::unique_ptr<VarDeclNode>> > ());
        yylhs.location = {yystack_[2].location.begin, yystack_[0].location.end};
        }
#line 908 "grammar.tab.cc"
    break;

  case 11: // param_list: var_decl
#line 129 "grammar.yy"
               {
        yylhs.value.as < std::vector<std::unique_ptr<VarDeclNode>> > ();
        yylhs.value.as < std::vector<std::unique_ptr<VarDeclNode>> > ().emplace(yylhs.value.as < std::vector<std::unique_ptr<VarDeclNode>> > ().begin(), std::move(yystack_[0].value.as < std::unique_ptr<VarDeclNode> > ()));
        yylhs.location = yystack_[0].location;
        }
#line 918 "grammar.tab.cc"
    break;

  case 12: // param_list: %empty
#line 134 "grammar.yy"
             {}
#line 924 "grammar.tab.cc"
    break;

  case 13: // argument_list: argument_list ARG_DELIMITER IDENTIFIER
#line 138 "grammar.yy"
                                           {
        yystack_[2].value.as < std::vector<std::unique_ptr<INode>> > ().emplace(yystack_[2].value.as < std::vector<std::unique_ptr<INode>> > ().begin(), std::make_unique<VarReferenceNode>(yystack_[0].value.as < std::string > (), yystack_[0].location));
        yylhs.value.as < std::vector<std::unique_ptr<INode>> > () = std::move(yystack_[2].value.as < std::vector<std::unique_ptr<INode>> > ());
        yylhs.location = {yystack_[2].location.begin, yystack_[0].location.end};
        }
#line 934 "grammar.tab.cc"
    break;

  case 14: // argument_list: IDENTIFIER
#line 143 "grammar.yy"
                 {
        yylhs.value.as < std::vector<std::unique_ptr<INode>> > ();
        yylhs.value.as < std::vector<std::unique_ptr<INode>> > ().emplace(yylhs.value.as < std::vector<std::unique_ptr<INode>> > ().begin(), std::make_unique<VarReferenceNode>(yystack_[0].value.as < std::string > (), yystack_[0].location));
        yylhs.location = yystack_[0].location;
        }
#line 944 "grammar.tab.cc"
    break;

  case 15: // argument_list: %empty
#line 148 "grammar.yy"
             {}
#line 950 "grammar.tab.cc"
    break;

  case 16: // sentence_group: LPAREN sentence_list RPAREN
#line 152 "grammar.yy"
                                {
        yylhs.value.as < std::unique_ptr<StatementListNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<StatementListNode> > ());
        yylhs.location = yystack_[1].location;
        }
#line 959 "grammar.tab.cc"
    break;

  case 17: // sentence_list: sentence_list sentence
#line 159 "grammar.yy"
                          {
        yystack_[1].value.as < std::unique_ptr<StatementListNode> > ()->AddStatement(std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()));
        yylhs.value.as < std::unique_ptr<StatementListNode> > () = std::move(yystack_[1].value.as < std::unique_ptr<StatementListNode> > ());
        yylhs.location = {yystack_[1].location.begin, yystack_[0].location.end};
        }
#line 969 "grammar.tab.cc"
    break;

  case 18: // sentence_list: if_clause
#line 164 "grammar.yy"
                {
        yylhs.value.as < std::unique_ptr<StatementListNode> > () = std::make_unique<StatementListNode>();
        yylhs.value.as < std::unique_ptr<StatementListNode> > ()->AddStatement(std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()));
        yylhs.location = yystack_[0].location;
        }
#line 979 "grammar.tab.cc"
    break;

  case 19: // sentence_list: while_clause
#line 169 "grammar.yy"
                   {
        yylhs.value.as < std::unique_ptr<StatementListNode> > () = std::make_unique<StatementListNode>();
        yylhs.value.as < std::unique_ptr<StatementListNode> > ()->AddStatement(std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()));
        yylhs.location = yystack_[0].location;
        }
#line 989 "grammar.tab.cc"
    break;

  case 20: // sentence_list: sentence
#line 174 "grammar.yy"
               {
        yylhs.value.as < std::unique_ptr<StatementListNode> > () = std::make_unique<StatementListNode>();
        yylhs.value.as < std::unique_ptr<StatementListNode> > ()->AddStatement(std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()));
        yylhs.location = yystack_[0].location;
        }
#line 999 "grammar.tab.cc"
    break;

  case 21: // sentence: statement SEMICOLON
#line 182 "grammar.yy"
                        {
        yylhs.value.as < std::unique_ptr<INode> > () = std::move(yystack_[1].value.as < std::unique_ptr<INode> > ());
        yylhs.location = {yystack_[1].location.begin, yystack_[0].location.end};
        }
#line 1008 "grammar.tab.cc"
    break;

  case 22: // statement: arithmetic_expr
#line 189 "grammar.yy"
                    {yylhs.value.as < std::unique_ptr<INode> > () = std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()); yylhs.location = yystack_[0].location;}
#line 1014 "grammar.tab.cc"
    break;

  case 23: // statement: assign
#line 190 "grammar.yy"
             {yylhs.value.as < std::unique_ptr<INode> > () = std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()); yylhs.location = yystack_[0].location;}
#line 1020 "grammar.tab.cc"
    break;

  case 24: // statement: initialization
#line 191 "grammar.yy"
                     {yylhs.value.as < std::unique_ptr<INode> > () = std::move(yystack_[0].value.as < std::unique_ptr<InitializationNode> > ()); yylhs.location = yystack_[0].location;}
#line 1026 "grammar.tab.cc"
    break;

  case 25: // statement: %empty
#line 192 "grammar.yy"
             {yylhs.value.as < std::unique_ptr<INode> > () = nullptr;}
#line 1032 "grammar.tab.cc"
    break;

  case 26: // type_info: SIMPLE_TYPE
#line 196 "grammar.yy"
                {
        if(yystack_[0].value.as < std::string > () == "signed")
            yylhs.value.as < TypeHolder > () = {TypeToken::Signed};
        else if(yystack_[0].value.as < std::string > () == "unsigned")
            yylhs.value.as < TypeHolder > () = {TypeToken::Unsigned};
        else
            yylhs.value.as < TypeHolder > () = {TypeToken::Cell};
        yylhs.location = yystack_[0].location;
        }
#line 1046 "grammar.tab.cc"
    break;

  case 27: // type_info: MATRIX LESS type_info GREATER
#line 205 "grammar.yy"
                                    {
        yylhs.location = {yystack_[3].location.begin, yystack_[0].location.end};
        yylhs.value.as < TypeHolder > () = yystack_[1].value.as < TypeHolder > ();
        yylhs.value.as < TypeHolder > ().MakeMatrixWrap();
        }
#line 1056 "grammar.tab.cc"
    break;

  case 28: // var_decl: type_info IDENTIFIER
#line 213 "grammar.yy"
                         {
        location_type loc(yystack_[1].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<VarDeclNode> > () = std::make_unique<VarDeclNode>(yystack_[0].value.as < std::string > (), yystack_[1].value.as < TypeHolder > (), loc);
        }
#line 1066 "grammar.tab.cc"
    break;

  case 29: // var_decl: CONST type_info IDENTIFIER
#line 218 "grammar.yy"
                                 {
        location_type loc(yystack_[2].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yystack_[1].value.as < TypeHolder > ().MakeConst();
        yylhs.value.as < std::unique_ptr<VarDeclNode> > () = std::make_unique<VarDeclNode>(yystack_[0].value.as < std::string > (), yystack_[1].value.as < TypeHolder > (), loc, true);
        }
#line 1077 "grammar.tab.cc"
    break;

  case 30: // initialization: var_decl
#line 227 "grammar.yy"
             {yylhs.value.as < std::unique_ptr<InitializationNode> > () = std::make_unique<InitializationNode>(std::move(yystack_[0].value.as < std::unique_ptr<VarDeclNode> > ()), nullptr, yystack_[0].location); yylhs.location = yystack_[0].location;}
#line 1083 "grammar.tab.cc"
    break;

  case 31: // initialization: var_decl ASSIGN arithmetic_expr
#line 228 "grammar.yy"
                                      {
        location_type loc(yystack_[2].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<InitializationNode> > () = std::make_unique<InitializationNode>(std::move(yystack_[2].value.as < std::unique_ptr<VarDeclNode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()), loc);
        }
#line 1093 "grammar.tab.cc"
    break;

  case 32: // assign: IDENTIFIER ASSIGN arithmetic_expr
#line 236 "grammar.yy"
                                      {
        auto var_ref_node = std::make_unique<VarReferenceNode>(yystack_[2].value.as < std::string > (), yystack_[2].location);
        location_type loc(yystack_[2].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<AssignNode>(std::move(var_ref_node), std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()), loc);
        }
#line 1104 "grammar.tab.cc"
    break;

  case 33: // if_clause: TESTONCE LPAREN arithmetic_expr RPAREN sentence_group
#line 245 "grammar.yy"
                                                          {
        location_type loc(yystack_[4].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<IfNode>(std::move(yystack_[2].value.as < std::unique_ptr<INode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<StatementListNode> > ()), loc);
        }
#line 1114 "grammar.tab.cc"
    break;

  case 34: // while_clause: TESTREP LPAREN arithmetic_expr RPAREN sentence_group
#line 253 "grammar.yy"
                                                         {
        location_type loc(yystack_[4].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<WhileNode>(std::move(yystack_[2].value.as < std::unique_ptr<INode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<StatementListNode> > ()), loc);
        }
#line 1124 "grammar.tab.cc"
    break;

  case 35: // arithmetic_operand: SIGNED_NUM
#line 261 "grammar.yy"
               {yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<SignedLiteralNode>(yystack_[0].value.as < int > (), yystack_[0].location); yylhs.location = yystack_[0].location;}
#line 1130 "grammar.tab.cc"
    break;

  case 36: // arithmetic_operand: UNSIGNED_NUM
#line 262 "grammar.yy"
                   {yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<UnsignedLiteralNode>(yystack_[0].value.as < unsigned int > (), yystack_[0].location); yylhs.location = yystack_[0].location;}
#line 1136 "grammar.tab.cc"
    break;

  case 37: // arithmetic_operand: IDENTIFIER
#line 263 "grammar.yy"
                 {yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<VarReferenceNode>(yystack_[0].value.as < std::string > (), yystack_[0].location); yylhs.location = yystack_[0].location;}
#line 1142 "grammar.tab.cc"
    break;

  case 38: // arithmetic_operand: func_call
#line 264 "grammar.yy"
                {yylhs.value.as < std::unique_ptr<INode> > () = std::move(yystack_[0].value.as < std::unique_ptr<FuncCallNode> > ()); yylhs.location = yystack_[0].location;}
#line 1148 "grammar.tab.cc"
    break;

  case 39: // arithmetic_expr: arithmetic_operand
#line 268 "grammar.yy"
                       {
        yylhs.location = yystack_[0].location;
        yylhs.value.as < std::unique_ptr<INode> > () = std::move(yystack_[0].value.as < std::unique_ptr<INode> > ());
        }
#line 1157 "grammar.tab.cc"
    break;

  case 40: // arithmetic_expr: arithmetic_expr PLUS arithmetic_expr
#line 272 "grammar.yy"
                                           {
        location_type loc(yystack_[2].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<BinaryOpNode>(BinaryOpKind::Plus, std::move(yystack_[2].value.as < std::unique_ptr<INode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()), loc);
        }
#line 1167 "grammar.tab.cc"
    break;

  case 41: // arithmetic_expr: arithmetic_expr MINUS arithmetic_expr
#line 277 "grammar.yy"
                                            {
        location_type loc(yystack_[2].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<BinaryOpNode>(BinaryOpKind::Minus, std::move(yystack_[2].value.as < std::unique_ptr<INode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()), loc);
        }
#line 1177 "grammar.tab.cc"
    break;

  case 42: // arithmetic_expr: arithmetic_expr STAR arithmetic_expr
#line 282 "grammar.yy"
                                           {
        location_type loc(yystack_[2].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<BinaryOpNode>(BinaryOpKind::Star, std::move(yystack_[2].value.as < std::unique_ptr<INode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()), loc);
        }
#line 1187 "grammar.tab.cc"
    break;

  case 43: // arithmetic_expr: arithmetic_expr SLASH arithmetic_expr
#line 287 "grammar.yy"
                                            {
        location_type loc(yystack_[2].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<BinaryOpNode>(BinaryOpKind::Slash, std::move(yystack_[2].value.as < std::unique_ptr<INode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()), loc);
        }
#line 1197 "grammar.tab.cc"
    break;

  case 44: // arithmetic_expr: arithmetic_expr PERCENT arithmetic_expr
#line 292 "grammar.yy"
                                              {
        location_type loc(yystack_[2].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<BinaryOpNode>(BinaryOpKind::Percent, std::move(yystack_[2].value.as < std::unique_ptr<INode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()), loc);
        }
#line 1207 "grammar.tab.cc"
    break;

  case 45: // arithmetic_expr: MINUS arithmetic_expr
#line 297 "grammar.yy"
                            {
        location_type loc(yystack_[1].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<UnaryOpNode>(UnaryOpKind::Minus, std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()), loc);
        }
#line 1217 "grammar.tab.cc"
    break;

  case 46: // arithmetic_expr: LPAREN arithmetic_expr RPAREN
#line 302 "grammar.yy"
                                    {
        location_type loc(yystack_[2].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<INode> > () = std::move(yystack_[1].value.as < std::unique_ptr<INode> > ());
        }
#line 1227 "grammar.tab.cc"
    break;

  case 47: // arithmetic_expr: arithmetic_expr LESS arithmetic_expr
#line 307 "grammar.yy"
                                           {
        location_type loc(yystack_[2].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<BinaryOpNode>(BinaryOpKind::Less, std::move(yystack_[2].value.as < std::unique_ptr<INode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()), loc);
        }
#line 1237 "grammar.tab.cc"
    break;

  case 48: // arithmetic_expr: arithmetic_expr GREATER arithmetic_expr
#line 312 "grammar.yy"
                                              {
        location_type loc(yystack_[2].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<BinaryOpNode>(BinaryOpKind::Greater, std::move(yystack_[2].value.as < std::unique_ptr<INode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()), loc);
        }
#line 1247 "grammar.tab.cc"
    break;

  case 49: // arithmetic_expr: arithmetic_expr EQUAL arithmetic_expr
#line 317 "grammar.yy"
                                            {
        location_type loc(yystack_[2].location.begin, yystack_[0].location.end);
        yylhs.location = loc;
        yylhs.value.as < std::unique_ptr<INode> > () = std::make_unique<BinaryOpNode>(BinaryOpKind::Equal, std::move(yystack_[2].value.as < std::unique_ptr<INode> > ()), std::move(yystack_[0].value.as < std::unique_ptr<INode> > ()), loc);
        }
#line 1257 "grammar.tab.cc"
    break;


#line 1261 "grammar.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      yy_lac_discard_ ("error recovery");
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "ASSIGN", "MINUS", "PLUS",
  "STAR", "SLASH", "LPAREN", "RPAREN", "PERCENT", "LESS", "GREATER",
  "EQUAL", "CONST", "NEW_LINE", "SEMICOLON", "ARG_DELIMITER", "CALL",
  "FUNC", "TESTREP", "TESTONCE", "TOP", "BOTTOM", "LEFT", "RIGHT",
  "MATRIX", "COMMA", "IDENTIFIER", "SIGNED_NUM", "UNSIGNED_NUM",
  "SIMPLE_TYPE", "$accept", "program", "program_block", "func_decl",
  "func_call", "param_list", "argument_list", "sentence_group",
  "sentence_list", "sentence", "statement", "type_info", "var_decl",
  "initialization", "assign", "if_clause", "while_clause",
  "arithmetic_operand", "arithmetic_expr", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

#if YYDEBUG
    // Execute LAC once. We don't care if it is successful, we
    // only do it for the sake of debugging output.
    if (!yyparser_.yy_lac_established_)
      yyparser_.yy_lac_check_ (yyla_.kind ());
#endif

    for (int yyx = 0; yyx < YYNTOKENS; ++yyx)
      {
        symbol_kind_type yysym = YY_CAST (symbol_kind_type, yyx);
        if (yysym != symbol_kind::S_YYerror
            && yysym != symbol_kind::S_YYUNDEF
            && yyparser_.yy_lac_check_ (yysym))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
      }
    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }




  bool
  parser::yy_lac_check_ (symbol_kind_type yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if YYDEBUG
    YYCDEBUG << "LAC: checking lookahead " << symbol_name (yytoken) << ':';
#endif
    std::ptrdiff_t lac_top = 0;
    while (true)
      {
        state_type top_state = (yylac_stack_.empty ()
                                ? yystack_[lac_top].state
                                : yylac_stack_.back ());
        int yyrule = yypact_[+top_state];
        if (yy_pact_value_is_default_ (yyrule)
            || (yyrule += yytoken) < 0 || yylast_ < yyrule
            || yycheck_[yyrule] != yytoken)
          {
            // Use the default action.
            yyrule = yydefact_[+top_state];
            if (yyrule == 0)
              {
                YYCDEBUG << " Err\n";
                return false;
              }
          }
        else
          {
            // Use the action from yytable.
            yyrule = yytable_[yyrule];
            if (yy_table_value_is_error_ (yyrule))
              {
                YYCDEBUG << " Err\n";
                return false;
              }
            if (0 < yyrule)
              {
                YYCDEBUG << " S" << yyrule << '\n';
                return true;
              }
            yyrule = -yyrule;
          }
        // By now we know we have to simulate a reduce.
        YYCDEBUG << " R" << yyrule - 1;
        // Pop the corresponding number of values from the stack.
        {
          std::ptrdiff_t yylen = yyr2_[yyrule];
          // First pop from the LAC stack as many tokens as possible.
          std::ptrdiff_t lac_size = std::ptrdiff_t (yylac_stack_.size ());
          if (yylen < lac_size)
            {
              yylac_stack_.resize (std::size_t (lac_size - yylen));
              yylen = 0;
            }
          else if (lac_size)
            {
              yylac_stack_.clear ();
              yylen -= lac_size;
            }
          // Only afterwards look at the main stack.
          // We simulate popping elements by incrementing lac_top.
          lac_top += yylen;
        }
        // Keep top_state in sync with the updated stack.
        top_state = (yylac_stack_.empty ()
                     ? yystack_[lac_top].state
                     : yylac_stack_.back ());
        // Push the resulting state of the reduction.
        state_type state = yy_lr_goto_state_ (top_state, yyr1_[yyrule]);
        YYCDEBUG << " G" << int (state);
        yylac_stack_.push_back (state);
      }
  }

  // Establish the initial context if no initial context currently exists.
  bool
  parser::yy_lac_establish_ (symbol_kind_type yytoken)
  {
    /* Establish the initial context for the current lookahead if no initial
       context is currently established.

       We define a context as a snapshot of the parser stacks.  We define
       the initial context for a lookahead as the context in which the
       parser initially examines that lookahead in order to select a
       syntactic action.  Thus, if the lookahead eventually proves
       syntactically unacceptable (possibly in a later context reached via a
       series of reductions), the initial context can be used to determine
       the exact set of tokens that would be syntactically acceptable in the
       lookahead's place.  Moreover, it is the context after which any
       further semantic actions would be erroneous because they would be
       determined by a syntactically unacceptable token.

       yy_lac_establish_ should be invoked when a reduction is about to be
       performed in an inconsistent state (which, for the purposes of LAC,
       includes consistent states that don't know they're consistent because
       their default reductions have been disabled).

       For parse.lac=full, the implementation of yy_lac_establish_ is as
       follows.  If no initial context is currently established for the
       current lookahead, then check if that lookahead can eventually be
       shifted if syntactic actions continue from the current context.  */
    if (yy_lac_established_)
      return true;
    else
      {
#if YYDEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* event)
  {
   /* Discard any previous initial lookahead context because of Event,
      which may be a lookahead change or an invalidation of the currently
      established initial context for the current lookahead.

      The most common example of a lookahead change is a shift.  An example
      of both cases is syntax error recovery.  That is, a syntax error
      occurs when the lookahead is syntactically erroneous for the
      currently established initial context, so error recovery manipulates
      the parser stacks to try to find a new initial context in which the
      current lookahead is syntactically acceptable.  If it fails to find
      such a context, it discards the lookahead.  */
    if (yy_lac_established_)
      {
        YYCDEBUG << "LAC: initial context discarded due to "
                 << event << '\n';
        yy_lac_established_ = false;
      }
  }


  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
         In the first two cases, it might appear that the current syntax
         error should have been detected in the previous state when
         yy_lac_check was invoked.  However, at that time, there might
         have been a different syntax error that discarded a different
         initial context during error recovery, leaving behind the
         current lookahead.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -74;

  const signed char parser::yytable_ninf_ = -26;

  const short
  parser::yypact_[] =
  {
      -2,    26,    26,    12,   -20,   -18,     3,    14,     9,    20,
     -74,   -74,   -74,    25,    39,    -2,   -74,    -2,    24,    30,
      59,   -74,   -74,    -2,    -2,   -74,   135,   -74,   143,   105,
      37,    58,    60,    26,    26,    12,    26,   -74,   -74,   -74,
     -74,   -74,   -74,    26,   -74,   -74,    26,    26,    26,    26,
      26,    26,    26,    26,   -74,   -74,    44,    45,   115,   125,
      61,   135,   135,   143,   143,   -74,   -74,   -74,    54,    54,
      54,   -74,    -4,    -6,   -74,    66,    66,   -74,   -74,    55,
      66,    45,    49,   -74,   -74,   -74,   -74,   -74,    77,   -74,
     -74,   -74,   -74,   -74
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     0,     0,     0,     0,     0,     0,     0,    37,
      35,    36,    26,     0,     0,     3,    38,     3,     0,     0,
      30,    24,    23,     3,     3,    39,    22,    37,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     2,     4,
       5,    21,    28,     0,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     0,    46,    29,    15,    12,     0,     0,
       0,    32,    31,    41,    40,    42,    43,    44,    47,    48,
      49,    14,     0,     0,    11,     0,     0,    27,     9,     0,
       0,     0,    25,    34,    33,    13,     8,    10,    25,    20,
      18,    19,    16,    17
  };

  const signed char
  parser::yypgoto_[] =
  {
     -74,   -74,    73,   -74,   -74,   -74,   -74,   -39,   -74,   -73,
     -74,     1,   -50,   -74,   -74,     0,     2,   -74,    -1
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,    13,    14,    15,    16,    73,    72,    83,    88,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26
  };

  const signed char
  parser::yytable_[] =
  {
      28,    29,     1,    80,    30,    78,     2,    74,    31,    89,
      32,    33,     3,    79,   -25,    93,     4,     5,     6,     7,
      35,    81,    34,    36,     8,    37,     9,    10,    11,    12,
       1,    87,    58,    59,     2,    61,    60,    84,     8,    38,
      41,    86,    62,    12,     4,    63,    64,    65,    66,    67,
      68,    69,    70,     1,    27,    10,    11,     2,    42,     3,
      48,    49,    43,     3,    50,    55,    56,     4,    57,     6,
       7,     8,    71,    77,    82,     8,    12,     9,    10,    11,
      12,     1,    90,    85,    91,     2,    92,     0,    39,     0,
      40,     3,     0,     0,     0,     4,    44,    45,     0,     0,
       0,     0,     0,     8,     0,     9,    10,    11,    12,    46,
      47,    48,    49,     0,    54,    50,    51,    52,    53,    46,
      47,    48,    49,     0,    75,    50,    51,    52,    53,    46,
      47,    48,    49,     0,    76,    50,    51,    52,    53,    46,
      47,    48,    49,     0,     0,    50,    51,    52,    53,    48,
      49,     0,     0,    50,    51,    52,    53
  };

  const signed char
  parser::yycheck_[] =
  {
       1,     2,     4,     9,     3,     9,     8,    57,    28,    82,
      28,     8,    14,    17,    16,    88,    18,    19,    20,    21,
      11,    27,     8,     3,    26,     0,    28,    29,    30,    31,
       4,    81,    33,    34,     8,    36,    35,    76,    26,     0,
      16,    80,    43,    31,    18,    46,    47,    48,    49,    50,
      51,    52,    53,     4,    28,    29,    30,     8,    28,    14,
       6,     7,     3,    14,    10,    28,     8,    18,     8,    20,
      21,    26,    28,    12,     8,    26,    31,    28,    29,    30,
      31,     4,    82,    28,    82,     8,     9,    -1,    15,    -1,
      17,    14,    -1,    -1,    -1,    18,    23,    24,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    28,    29,    30,    31,     4,
       5,     6,     7,    -1,     9,    10,    11,    12,    13,     4,
       5,     6,     7,    -1,     9,    10,    11,    12,    13,     4,
       5,     6,     7,    -1,     9,    10,    11,    12,    13,     4,
       5,     6,     7,    -1,    -1,    10,    11,    12,    13,     6,
       7,    -1,    -1,    10,    11,    12,    13
  };

  const signed char
  parser::yystos_[] =
  {
       0,     4,     8,    14,    18,    19,    20,    21,    26,    28,
      29,    30,    31,    33,    34,    35,    36,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    28,    50,    50,
      43,    28,    28,     8,     8,    11,     3,     0,     0,    34,
      34,    16,    28,     3,    34,    34,     4,     5,     6,     7,
      10,    11,    12,    13,     9,    28,     8,     8,    50,    50,
      43,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    28,    38,    37,    44,     9,     9,    12,     9,    17,
       9,    27,     8,    39,    39,    28,    39,    44,    40,    41,
      47,    48,     9,    41
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    32,    33,    34,    34,    34,    34,    34,    35,    36,
      37,    37,    37,    38,    38,    38,    39,    40,    40,    40,
      40,    41,    42,    42,    42,    42,    43,    43,    44,    44,
      45,    45,    46,    47,    48,    49,    49,    49,    49,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     2,     2,     2,     2,     6,     5,
       3,     1,     0,     3,     1,     0,     3,     2,     1,     1,
       1,     2,     1,     1,     1,     0,     1,     4,     2,     3,
       1,     3,     3,     5,     5,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    82,    82,    85,    86,    91,    96,   101,   108,   116,
     124,   129,   134,   138,   143,   148,   152,   159,   164,   169,
     174,   182,   189,   190,   191,   192,   196,   205,   213,   218,
     227,   228,   236,   245,   253,   261,   262,   263,   264,   268,
     272,   277,   282,   287,   292,   297,   302,   307,   312,   317
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1891 "grammar.tab.cc"

#line 323 "grammar.yy"


void yy::parser::error (const location_type& l, const std::string& m){
    std::cerr << l << ": " << m << '\n';
}
