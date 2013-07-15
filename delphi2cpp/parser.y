%{
#undef FILE

#define YYDEBUG 0

#include "ioutils.h"

#pragma hdrstop

enums_t enums;
stringlist_t hpps;
namespace
{
char *p;
string type_name, class_name, vars, wrk_func_name, wrk_func_params,
  func_name, func_rtype, last_partype;
char *const_types[] =
{
  "@unknown@",
  "bool",
  "int",
  "double",
  "void *",
  "char",
  "AnsiString"
};
int gn_cnt, section;
bool in_intf, in_arrbrack, stmt_need;
stringlist_t msg_hndlrs, units;
stringlist_t::iterator slst_p;
enum_descr_t *enum_descr_p;
}
//---------------------------------------------------------------------------
#define use_srcunit units.push_back(src_name)
#define POST_ERROR yyerrok; newline(); \
  write_cpp("/" "* HERE WAS AN ERROR; continue from line %i */", line_no);
#define max(a, b) ((a) > (b) ? (a) : (b))
//---------------------------------------------------------------------------
string &make_list(string &src)
{
  return tmp_string.assign(src.begin(), src.length() - 2);
}
//---------------------------------------------------------------------------
string &make_list(string &src, const string &prefix, bool needpostfix)
{
  int i;
  p = src.begin();
  tmp_string.clear();
  while (*p)
  {
    for (i = 0; p[i] != ','; i++);
    tmp_string += prefix + string(p, i) +
      (needpostfix ? ", const int " + string(p, i) + "_Size" : string("")) +
      ", ";
    p += i + 2;
  }
  tmp_string.resize(tmp_string.length() - 2);
  return tmp_string; 
}
//---------------------------------------------------------------------------
string &gen_name(void)
{
  return tmp_string = src_name + "__" + itoa(++gn_cnt, buf, 10);
}
//---------------------------------------------------------------------------
void check_name(void)
{
  if (type_name.empty()) type_name = gen_name();
}
//---------------------------------------------------------------------------
void print_asm(void)
{
  newline();
  write_cpp("asm");
  newline();
  write_cpp("{");
  indent++;
  while (*p)
  {
    int i;
    for (i = 0; p[i] != '\x01'; i++);
    p[i] = '\0';
    if (i)
    {
      newline();
      write_cpp("%s", p);
    }
    p += i + 1;
  }
  indent--;
  newline();
  write_cpp("}");
}
//---------------------------------------------------------------------------
void find_enum_descr(string name)
{
  enum_descr_p = &enums[strupr(name.begin())];
  if (*enum_descr_p->lower.begin() == '@')
    yywarning("unknown range");
}
//---------------------------------------------------------------------------
%}
%expect 5
%token <code>
  IDENTIFIER CONSTANT
  UNIT PROGRAM
  // sections
  USES INTERFACE IMPLEMENTATION INITIALIZATION FINALIZATION
  LABEL TYPE CONST VAR ABSOLUTE FUNCTION
  // typedecls
  PACKED FILE SET ARRAY OF FIELDED VISIBILITY PROPERTY STRING
  // func-proc spec
  EXTERNAL FORWARD
  // statements
  BEGIN END ASMSTMT GOTO RAISE IF THEN ELSE
  FOR TO DOWNTO DO WHILE REPEAT UNTIL
  CASE WITH TRY FINALLY EXCEPT ON
  INHERITED
  // operators
  ';' ','

%nonassoc <code> '=' ':'
%left <code> COMPARE EQ TWOFULLSTOP '^' IN IS
%left <code> '+' '-' OR XOR
%left <code> '*' '/' MOD DIV AND SHIFT AS
%right <code> NOT '@'
%left <code> '[' ']' '(' ')' '.'

%type <i>  classword varconstspec direction
%type <call_conv> funcspecs
%type <code>
  pascalcode
  programhead initialization finalization
  uses unitlist unitreq
  identifierlist 
  primary primarylist expr expr_neq exprlist rangelist range
  //for statements
  stmt stmtlist end labelmark ifthen 
  casegrouplist listcaselist_poor listcaselist_rich listcasehead elsecasehead 
  asmstmt
  tryhead exceptlist onexceptlist_poor onexceptlist_rich onexcept onelse
  //for sctns
  intfdescrlist impldescrlist
  commondescr
  constsctn varsctn typesctn labelsctn funcdef
  //for type desription
  typedef typedescr smptypedescr mpacktypedescr
  enumconstlist arridxdescrlist
  singlenametype
  //for record/class/object
  dependency memberlist memberlist_rich
  indexes proptype propspec propspec_paired
  rcopart rcasegroup rcaselist rcaselist_poor
  fieldlist_rich fieldlist_poor defaultspec
  //for const/var desription
  typedinit
  initializer initializerlist initlist initlist_rich initlist_poor smallinit
  //for func/proc desription
  funchead funcname funcrtype
  paramdef formalparams formalparamslist formalparamstype mayinitializer
  importlist objspec
  funcbody

%start pascalcode
%%
//---------------------------------------------------------------------------
pascalcode:
    programhead
    {
      open_output();
      write_cpp(DIVISOR_LINE);
      if (use_vcl)
        write_cpp("\n\n#include <vcl.h>\n#pragma hdrstop\n");
      if (use_starray)
      {
        write_cpp("\n#include <dstarray.h>\n");
        write_cpp(DIVISOR_LINE);
      }
    }
    impldescrlist
    BEGIN
    {
      indent = 0;
      newline();
      write_cpp(create_winmain ?
        "WINAPI WinMain(HANDLE, HANDLE,	LPSTR lpszCommandLine, int cmdShow)\n{"
        : "#pragma argsused\nint main(int argc, char* argv[])\n{");

      indent = 1;
      wrk_func_name = "@";
      use_srcunit;
    }
      stmtlist
    end '.'
    {
      newline();
      write_cpp("return 0;\n}");
      YYACCEPT;
    }
  | UNIT IDENTIFIER ';'
    {
      src_name = $2;
      open_output(false);

      write_cpp(DIVISOR_LINE);
      write_cpp("\n#ifndef %sH\n#define %sH\n", src_name.begin(), src_name.begin());
      write_cpp(DIVISOR_LINE);
      if (use_starray)
      {
        write_cpp("\n#include <dstarray.h>\n");
        write_cpp(DIVISOR_LINE);
      }
      in_intf = true;
      use_srcunit;
    }
    INTERFACE
    uses
    intfdescrlist
    IMPLEMENTATION
    {
      indent = 0;
      newline();
      write_cpp("#endif");
      in_intf = false;

      open_output(true);
      write_cpp(DIVISOR_LINE);
      if (use_vcl)
        write_cpp("\n\n#include <vcl.h>\n#pragma hdrstop\n");
    }
    uses
    {
      if (!vars.empty())
        write_cpp("%s", vars.begin());
    }
      impldescrlist
    initialization
    finalization
    END '.'
    {
      YYACCEPT;
    }
  ;
//---------------------------------------------------------------------------
programhead:
    /* empty */ {}
  | PROGRAM IDENTIFIER ';'
    {
      src_name = $2;
    }
  ;
initialization:
    /* empty */ { }
  | INITIALIZATION
    {
      write_cpp("\n#pragma startup %s_initialization\n"
        "static void %s_initialization(void)\n{",
        src_name.begin(), src_name.begin());
      indent = 1;
      wrk_func_name = "@";
    }
      stmtlist
    {
      indent = 0;
      newline();
      write_cpp("}\n");
      write_cpp(DIVISOR_LINE);
      wrk_func_name.clear();
    }
  ;
finalization:
    /* empty */ { }
  | FINALIZATION
    {
      write_cpp("\n#pragma exit %s_finalization\n"
        "static void %s_finalization(void)\n{",
        src_name.begin(), src_name.begin());
      indent = 1;
      wrk_func_name = "@";
    }
      stmtlist
    {
      indent = 0;
      newline();
      write_cpp("}\n");
      write_cpp(DIVISOR_LINE);
      wrk_func_name.clear();
    }
  ;
//---------------------------------------------------------------------------
uses:
    /* empty */ { }
  | USES
    {
      section = USES;
    }
    unitlist ';'
    {
      write_cpp("\n");
      write_cpp(DIVISOR_LINE);
    }
  ;
unitlist:
    unitreq
  | unitlist ',' unitreq
  ;
unitreq:
    IDENTIFIER
    {
      newline();
      units.push_back($1);
      for (slst_p = hpps.begin(); slst_p != hpps.end(); slst_p++)
        if (stricmp(slst_p->begin(), $1.begin()) == 0)
        {
          write_cpp("#include <%s.hpp>", $1.begin());
          goto hpp_add;
        }
      write_cpp("#include \"%s.h\"", $1.begin());
      hpp_add:
    }
  | IDENTIFIER IN CONSTANT
    {
      newline();
      units.push_back($1);
      if ($3.length() > 4 && stricmp($3.end() - 4, ".pas"))
      {
        $3.end()[-3] = 'h';
        $3.end()[-2] = '\"';
        $3.end()[-1] = '\0';
      }
      write_cpp("#include %s", $3.begin());
    }
  ;
//---------------------------------------------------------------------------
intfdescrlist:
    /* empty */ { }
  | intfdescrlist commondescr
  | intfdescrlist funchead
    {
      newline();
      write_cpp("%s;", $2.begin());
      class_name.clear();
    }
  ;
impldescrlist:
    /* empty */ { }
  | impldescrlist commondescr
  | impldescrlist funcdef
  | impldescrlist error ';'
    {
      POST_ERROR;
    }
  ;
funcdef:
    funchead
    {
      wrk_func_name = func_name;
      indent = 0;
      newline();
      write_cpp("%s\n{", $1.begin());
      indent = 1;
      if (func_rtype != "void")
      {
        newline();
        write_cpp("%s Result;", func_rtype);
      }
      wrk_func_params.clear();
      if ($1.end()[-1] == ')' && strcmp($1.end() - 6, "(void)"))
      {
        p = $1.end() - 1;
        for (;;)
        {
          *p = '\0';
          do
            p--;
          while (isdigit(*p) || isalpha(*p) || *p == '_');
          wrk_func_params = string(p + 1) + ", " + wrk_func_params;
          while (*p != ',')
          {
            p--;
            if (*p == '(')
              goto ready;
          }
        }
        ready:
        wrk_func_params.resize(wrk_func_params.length() - 2);
      }
    }
      impldescrlist
    funcbody ';'
    {
      indent = 1;
      if (func_rtype != "void")
      {
        newline();
        write_cpp("return Result;");
      }
      indent = 0;
      newline();
      write_cpp("}\n");
      write_cpp(DIVISOR_LINE);
      wrk_func_name.clear();
      class_name.clear();
    }
  ;
//---------------------------------------------------------------------------
funcbody:
    BEGIN
    {
      indent = 1;
    }
      stmtlist
    end
  | asmstmt
    {
      indent = 1;
      p = $1.begin();
      print_asm();
    }
  ;
//---------------------------------------------------------------------------
commondescr:
    typesctn
    {
     if (indent == 0)
      {
        newline();
        write_cpp(DIVISOR_LINE);
      }
    }
  | constsctn
    {
     if (indent == 0)
      {
        newline();
        write_cpp(DIVISOR_LINE);
      }
    }
  | varsctn
    {
     if (indent == 0)
      {
        newline();
        write_cpp(DIVISOR_LINE);
      }
    }
  | labelsctn
  | funchead FORWARD ';'
    {
      newline();
      write_cpp("%s;", $1.begin());
      class_name.clear();
    }
  | funchead EXTERNAL expr importlist ';'
    {
      newline();
      write_cpp("__declspec(dllimport) %s;\n//from: %s%s", $1.begin(),
        $3.begin(), $4.begin());
      class_name.clear();  
    }
  ;
labelsctn:
    LABEL exprlist ';'
    {
      section = LABEL;
    }
  | LABEL error ';'
    {
      section = LABEL;
      POST_ERROR;
    }
  ;
constsctn:
    CONST
    {
      section = CONST;
    }
  | constsctn IDENTIFIER EQ expr ';'
    {
      newline();
      write_cpp("const %s %s = %s;", const_types[$<i>4], $2.begin(), $4.begin());
      if ($<i>4 == 0) yywarning("unknown type of constant");
    }
  | constsctn typedinit
  | constsctn error ';'
    {
      POST_ERROR;
    }
  ;
varsctn:
    VAR
    {
      section = VAR;
    }
  | varsctn identifierlist ':' typedescr ';'
    {
      newline();
      make_list($2);
      if (in_intf)
      {
        write_cpp("extern ");
        vars += "\n" + $4 + " " + tmp_string + ";";
      }
      write_cpp("%s %s;", $4.begin(), tmp_string.begin());
    }
  | varsctn identifierlist ':' typedescr ABSOLUTE primary ';'
    {
      newline();
      tmp_string = $2.substr(0, $2.find(','));
      if (in_intf)
      {
        write_cpp("extern ");
        vars += "\n" + $4 + " &" + tmp_string + " = *reinterpret_cast<" +
          $4 + "*>(&(" + $6 + "));";
        write_cpp("%s &%s;", $4.begin(), tmp_string.begin());
      }
      else
        write_cpp("%s &%s = *reinterpret_cast<%s*>(&(%s));",
          $4.begin(), tmp_string.begin(), $4.begin(), $6.begin());
    }
  | varsctn typedinit
  | varsctn error ';'
    {
      POST_ERROR;
    }
  ;
typesctn:
    TYPE
    {
      section = TYPE;
    }
  | typesctn IDENTIFIER EQ
    {
      type_name = $2;
    }
    typedef
  | typesctn error ';'
    {
      POST_ERROR;
    }
  ;
//---------------------------------------------------------------------------
importlist:
    /* empty */
    {
      $$.clear();
    }
  | importlist IDENTIFIER expr
    {
      $$ = $1 + ';' + $2 + ": " + $3;
    }
  ;
//---------------------------------------------------------------------------
typedef:
    typedescr ';'
  | TYPE typedescr ';'
  | FIELDED dependency ';'
    {
      newline();
      check_name;
      if ($2.empty())
      {
        write_cpp("extern %s %s;", ($1[0] == 'r' ? "struct" : "class"),
          type_name.begin());
      }
      else
      {
        write_cpp("class %s : public %s\n{\npublic:", type_name.begin(),
          $2.begin());
        indent++;
        newline();
        write_cpp("%s(@) : %s(@) {}\n};", type_name.begin(), $2.begin());
        yywarning("need a constructor");
      }
      type_name.clear();
    }
  ;
//---------------------------------------------------------------------------
typedescr:
    smptypedescr
  | STRING
    {
      if (!type_name.empty())
      {
        newline();
        $$ = type_name;
        write_cpp("typedef String %s;", type_name.begin());
        type_name.clear();
      }
      else $$ = $1;
    }
  | STRING '[' expr ']'
    {
      newline();
      check_name();
      $$ = type_name;
      write_cpp("typedef SmallString<%s> %s;", $3.begin(), type_name.begin());
      type_name.clear();
    }
  | '^' STRING
    {
      newline();
      check_name();
      $$ = type_name;
      write_cpp("typedef String *%s;", type_name.begin());
      type_name.clear();
    }
  | '^' primary
    {
      newline();
      check_name();
      $$ = type_name;
      write_cpp("typedef %s *%s;", $2.begin(), type_name.begin());
      type_name.clear();
    }
  | FIELDED OF IDENTIFIER
    {
      if (!type_name.empty())
      {
        newline();
        $$ = type_name;
        write_cpp("typedef TMetaClass %s;", type_name.begin());
        type_name.clear();
      }
      else $$ = "TMetaClass";
    }
  | FILE
    {
      if (!type_name.empty())
      {
        newline();
        $$ = type_name;
        write_cpp("typedef void* %s;", $1.begin(), type_name.begin());
        type_name.clear();
      }
      else $$ = "void *";
    }
   | FILE OF
     {
      if (!type_name.empty())
      {
        newline();
        $$ = type_name;
        write_cpp("typedef void* %s;", $1.begin(), type_name.begin());
        type_name.clear();
      }
      else $$ = "void *";
    }
    typedescr
  | mpacktypedescr
  | PACKED
    {
      newline();
      write_cpp("#pragma pack(push, 1)");
    }
    mpacktypedescr
    {
      newline();
      $$ = $3;
      write_cpp("#pragma pack(pop)");
    }
  | FUNCTION
    {
      check_name();
      func_name = type_name;
    }
    paramdef funcrtype objspec
    {
      newline();
      $$ = type_name;
      write_cpp("typedef %s (%s*%s)(%s);", func_rtype.begin(),
        $5.begin(),
        func_name.begin(), $3.begin());
      type_name.clear();
    }
  | SET OF
    {
      check_name();
      $<code>$ = type_name;
      type_name.clear();
    }
    smptypedescr
    {
      newline();
      $$ = $<code>3;
      find_enum_descr($$);
      write_cpp("typedef Set<%s, %s, %s> %s;", $4.begin(),
        enum_descr_p->lower.begin(), enum_descr_p->upper.begin(), $$.begin());
      type_name.clear();
    }
  ;
smptypedescr:
    primary
    {
      if (!type_name.empty())
      {
        newline();
        $$ = type_name;
        write_cpp("typedef %s %s;", $1.begin(), type_name.begin());
        type_name.clear();
      }
      else $$ = $1;
    }
  | '(' enumconstlist ')'
    {
      check_name();
      newline();
      $$ = type_name;
      write_cpp("enum %s {%s};", type_name.begin(), $2);
      static enum_descr_t tmp = enum_descr_t("", "");
      tmp.lower.assign($2.begin(), $2.find(','));
      static int i;
      i = $2.rfind(' ', $2.length() - 1);
      tmp.upper.assign($2.begin() + i + 1, $2.length() - i - 1);
      strupr(type_name.begin());
      enums.insert(make_pair(type_name, tmp));
      type_name.clear();
    }
   | expr_neq TWOFULLSTOP expr_neq
    {  
      check_name();
      $$ = type_name;
      if (!in_arrbrack)
      {
        newline();
        write_cpp("enum %s {min%s = %s, max%s = %s};",
          type_name.begin(), type_name.begin(),
          $1.begin(), type_name.begin(), $3.begin());
      }
      enums.insert(make_pair(strupr(type_name.begin()),
        enum_descr_t($1, $3)));
      type_name.clear();
    }
  ;
mpacktypedescr:
    ARRAY OF
    {
      check_name();
      $<code>$ = type_name;
      type_name.clear();
    }
    typedescr
    {
      newline();
      write_cpp("typedef DynamicArray<%s> %s;", $4.begin(), $<code>3.begin());
      $$ = $<code>3;
    }
  | ARRAY '['
    {
      check_name();
      in_arrbrack = true;
      $<code>$ = type_name;
      type_name.clear();
    }
    arridxdescrlist ']'
    {
      in_arrbrack = false;
    }
    OF typedescr
    {
      newline();
      if (use_starray)
      {
        write_cpp("typedef %s, %s>", $4.begin(), $8.begin());
        for (int i = $<i>4; i > 1; i--)
          write_cpp(" >");
        write_cpp(" %s;", $<code>3.begin());
      }
      else
        write_cpp("typedef %s %s%s;", $8.begin(), $<code>3.begin(), $4.begin());

      $$ = $<code>3;
    }
  | FIELDED dependency
    {
      check_name();
      newline();
      write_cpp("%s %s", ($1[0] == 'r' ? "struct" : "class"), type_name.begin());
      if ($1[0] == 'c' && $2.empty()) $2 = "TObject";
      if (!$2.empty())
        write_cpp(" : public %s", $2.begin());
      newline();
      write_cpp("{");
      if (!$2.empty())
      {
        indent++;
        newline();
        write_cpp("typedef %s inherited;", $2.begin());
        indent--;
      }
      if ($1[0] != 'r')
      {
        newline();
        write_cpp($1[0] == 'c' ? "__published:" : "public:");
      }
      indent++;
      if ($1[0] != 'r') class_name = type_name;
      $$ = type_name;
      type_name.clear();
      msg_hndlrs.clear();
    }
    memberlist END
    {
      if (!msg_hndlrs.empty())
      {
        write_cpp("\nprotected:");
        newline();
        write_cpp("BEGIN_MESSAGE_MAP");
        indent++;
        for (slst_p = msg_hndlrs.begin(); slst_p != msg_hndlrs.end(); slst_p++)
        {
          newline();
          write_cpp("VCL_MESSAGE_HANDLER(%s);", slst_p->begin());
        }
        indent--;
        newline();
        write_cpp("END_MESSAGE_MAP(inherited);");
      }
      indent--;
      newline();
      write_cpp("};");
      if ($1[0] != 'r') class_name.clear();
      $$ = $<code>3;
    }
  ;
//---------------------------------------------------------------------------
singlenametype:
    ':' primary
    {
      $$ = $2;
    }
  | ':' STRING
    {
      $$ = "String";
    }
//---------------------------------------------------------------------------
enumconstlist:
    IDENTIFIER ',' IDENTIFIER
    {
      $$ = $1 + ", " + $3;
    }
  | enumconstlist ',' IDENTIFIER
    {
      $$ = $1 + ", " + $3;
    }
  ;
//---------------------------------------------------------------------------
objspec:
    /* empty */
    {
     $$.clear();
    }
  | OF FIELDED
    {
      $$ = "__closure ";
    }
  ;
//---------------------------------------------------------------------------  
arridxdescrlist:
    smptypedescr
    {
      find_enum_descr($1);
      if (use_starray)
      {
        $<i>$ = 1;
        $$ = "StaticArray<" + enum_descr_p->lower + ", " + enum_descr_p->upper;
      }
      else
        $$ = '[' + enum_descr_p->upper + " - " + enum_descr_p->lower + " + 1]";
    }
  | arridxdescrlist ',' smptypedescr
    {
      find_enum_descr($3);
      $$ = $1;
      if (use_starray)
      {
        $<i>$ = $<i>1 + 1;
        $$ += ", StaticArray<" + enum_descr_p->lower + ", " + enum_descr_p->upper;
      }
      else
        $$ += '[' + enum_descr_p->upper + " - " + enum_descr_p->lower + " + 1]";
    }
  ;
//---------------------------------------------------------------------------
dependency:
    /* empty */
    {
      $$.clear();
    }
  | '(' primarylist ')'
    {
      $$ = $2.substr(0, $2.find(','));
    }
  ;
memberlist:
    fieldlist_poor
  | memberlist_rich
  | fieldlist_rich CASE rcopart OF
    {
      newline();
      write_cpp("union");
      newline();
      write_cpp("{");
      indent++;
    }
    rcaselist 
    {
      indent--;
      newline();
      write_cpp("};");
    }
  ;
fieldlist_rich:
    /* empty */ {}
  | fieldlist_poor ';'
  | memberlist error ';'
    {
      POST_ERROR;
    }
  | memberlist_rich VISIBILITY
    {
      indent--;
      newline();
      write_cpp("%s", $2.begin());
      indent++;
    }
  ;
fieldlist_poor:
    fieldlist_rich identifierlist ':' typedescr
    {
      newline();
      write_cpp("%s %s;", $4.begin(), make_list($2).begin());
    }
  ;
memberlist_rich:
    fieldlist_rich
  | memberlist_rich funchead
    {
      newline();
      write_cpp("%s;", $2.begin());
    }
  | memberlist_rich PROPERTY IDENTIFIER indexes proptype propspec ';' defaultspec
    {
      newline();
      write_cpp("__property %s%s%s", $5.begin(), $3.begin(), $4.begin());
      if (!$6.empty())
      {
        write_cpp(" =");
        indent++;
        newline();
        write_cpp("{%s}", make_list($6).begin());
        indent--;
      }
      write_cpp(";");
      if (!$8.empty()) write_cpp("//default property!");
    }
  ;  
defaultspec:
    /* empty */
    {
      $$.clear();
    }
  | IDENTIFIER ';'
  ;
indexes:
    /* empty */
    {
      $$.clear();
    }
  | '[' formalparamslist ']'
    {
      $2 += ", ";
      p = $2.begin();
      $$.clear();
      int i;
      while (*p)
      {
        for (i = 0; p[i] != ','; i++);
        $$ += '[' + string(p, i) + ']';
        p += i + 2;
      }
    }
  ;
proptype:
    /* empty */
    {
      $$.clear();
    }
  | singlenametype
    {
      $$ = $1 + " ";
    }
  ;
propspec:
    propspec_paired
  | propspec_paired IDENTIFIER
    {
      $$ = $1 + "nodefault, ";
    }
  ;
propspec_paired:
    /* empty */
    {
      $$.clear();
    }
  | propspec_paired IDENTIFIER expr
    {
      $$ = $1 + strlwr($2.begin()) + " = " + $3 + ", ";
    }
  ;
rcopart:
    smptypedescr
  | IDENTIFIER ':' smptypedescr
    {
      newline();
      write_cpp("%s %s;", $3.begin(), $1.begin());
    }
  ;
rcaselist:
    rcaselist_poor
  | rcaselist_poor ';'
  ;
rcaselist_poor:
    rcasegroup
  | rcaselist_poor ';' rcasegroup
  ;
rcasegroup:
    rangelist ':' '('
    { 
      newline();
      write_cpp("struct");
      newline();
      write_cpp("{");
      indent++;
    }
    memberlist ')'
    {
      indent--;
      newline();
      write_cpp("};");
    }
  ;
//---------------------------------------------------------------------------
typedinit:
    identifierlist ':' typedescr EQ initializer ';'
    {
      newline();
      if (section == CONST) write_cpp("const ");
      write_cpp("%s %s = %s;", $3.begin(), $1.substr(0, $1.find(',')).begin(),
        $5.begin());
    }
  | identifierlist ':' error ';'
    {
      POST_ERROR;
    }
  ;
initializer:
    expr
  | '(' initializerlist ')'
    {
      $$ = "{" + $2 + "}";
    }
  | '(' initlist ')'
    {
      indent ++;
      $$ = "\n";
      $$.append(indent * tab_stops, ' ');
      $$ += "{\n";
      int i;
      indent++;
      p = $2.begin();
      while (*p)
      {
        for (i = 0; p[i] != '\n'; i++);
        i++;
        $$.append(indent * tab_stops, ' ');
        $$.append(p, i);
        p += i;
      }
      $$.end()[-1] = '\n';
      indent--;
      $$.append(indent * tab_stops, ' ');
      $$ += "}";
      indent--;
    }
  ;
initializerlist:
    initializer
  | initializerlist ',' initializer
    {
      $$ = $1 + ",\n" + $3;
    }
  ;
initlist:
    initlist_rich
  | initlist_poor
  ;
initlist_rich:
    initlist_poor ';'
  ;
initlist_poor:
    smallinit
    {
      $$ = $1 + ",\n";
    }
  | initlist_rich smallinit
    {
      $$ = $1 + $2 + ",\n";
    }
  ;
smallinit:
    IDENTIFIER ':' initializer
    {
      $$ = "/*" + $1 + "*/" + $3;
    }
  ;
//---------------------------------------------------------------------------
identifierlist:
    IDENTIFIER
    {
      $$ = $1 + ", ";
    }
  | identifierlist ',' IDENTIFIER
    {
      $$ = $1 + $3 + ", ";
    }
  ;
//---------------------------------------------------------------------------
funchead:
    classword FUNCTION funcname paramdef funcrtype ';' funcspecs
    {
      switch ($7)
      {
        case 'm':
          tmp_string = "__msfastcall ";
          break;
        case 'c':
        case '-':
          tmp_string = "__cdecl ";
          break;
        case '\0':
          tmp_string = "__pascal ";
          break;
        case 'r':
          tmp_string = "__fastcall ";
          break;
        case 's':
          tmp_string = "__stdcall ";
          break;
        case 'f':
          tmp_string = "__safecall ";
          if (func_rtype != "void")
          {
            if ($4 == "void") $4.clear();
            $4 += ", ";
            $4 += func_rtype + " &" + func_name + "_result";
          }  
          func_rtype = "HRESULT";
          break;
        default:
          tmp_string.clear();
      }
      if ($2[0] == 'c' || $2[0] == 'd')
      {
        $1 = 0;
        func_name = class_name;
        if ($3.find(":") != -1) $3 = func_name + "::";
        else $3.clear();
        if ($2[0] != 'c')
        {
          func_name = "~" + func_name;
          $4 = "void";
        }
        $3 += func_name;
        $5.clear();
      }
      else
      {
        if ($2[0] == 'f' && func_rtype == "void")
        {
          func_rtype = "@unknown@";
          yywarning("unknown function return type");
        }
        $5 = func_rtype + " ";
      }
      if ($1)
      {
        $$ = "static ";
        if ($4 == "void") $4 = "TMetaClass *vmt";
        else $4 = "TMetaClass *vmt, " + $4;
      }
      else $$.clear();
      switch ($<i>7 & 0x3)
      {
        case 1:
          $$ = "virtual ";
          break;
        case 3:
          $$ = "DYNAMIC ";
          break;
      }
      $$ += $5 + tmp_string + $3 + '(' + $4 + ')';
      if ($<i>7 & 0x4) $$ += " = 0";
    }
  ;
classword:
   /* empty */
    {
      $$ = 0;
    }
  | FIELDED
    {
      $$ = FIELDED;
    }
  ;
funcrtype:
   /* empty */
    {
      func_rtype = "void";
    }
  | singlenametype
    {
      func_rtype = $1;
    }
  ;
funcname:
    IDENTIFIER
    {
      func_name = $1;
    }
  | IDENTIFIER '.' IDENTIFIER
    {
      $$ = $1 + "::" + $3;
      func_name = $3;
      class_name = $1;
    }
  ;
funcspecs:
    /* empty */
    {
      $$ = default_call;
      $<i>$ = 0;
    }
  | funcspecs IDENTIFIER ';'
    {
      char *funcspecs[] = {"ABSTRACT",
        "VIRTUAL", "OVERRIDE", "REINTRODUCE", "DYNAMIC",
        "PASCAL", "REGISTER", "CDECL", "STDCALL", "SAFECALL"};
      int i;
      for (i = 0; i < ARRAYSIZE(funcspecs); i++)
        if (stricmp($2.begin(), funcspecs[i]) == 0)
          break;
      switch (i)
      {
        case 0:
          if (class_name.empty())
            yyerror("functions cannot be abstact outside classes");
          else
            $<i>$ |= 0x4;
          break;
        case 1:
        case 2:
        case 3:
          $<i>$ = 0x1;
          break;
        case 4:
          $<i>$ = 0x3;
          break;
        case 5:
          $$ = '\0';
          break;
        case 6:
          $$ = 'r';
          break;
        case 7:
          $$ = 'c';
          break;
        case 8:
          $$ = 's';
          break;
        case 9:
          $$ = 'f';
          break;
      }
    }
  | funcspecs IDENTIFIER expr ';'
    {
      $<i>$ = 0;
      msg_hndlrs.push_back($3 + ", " + last_partype + ", " + func_name);
    }
  ;
paramdef:
    /* empty */
    {
      $$ = "void";
    }
  | '(' ')'
    {
      $$ = "void";
    }
  | '(' formalparamslist ')'
    {
      $$ = $2;
    }
  ;
formalparamslist:
    formalparams
  | formalparamslist ';' formalparams
    {
      $$ = $1 + ", " + $3;
    }
  ;
formalparams:
    varconstspec identifierlist formalparamstype mayinitializer
    {
      switch ($1)
      {
        case 0:
          if ($<i>3 == ARRAY) $3 = "const " + $3;
          break;
        case VAR:
          if ($<i>3 == IDENTIFIER) $3 += "&";
          break;
        case CONST:
          $3 = "const " + $3;
          break;
      }
      if (!$4.empty())
      {
        $2.resize($2.find(','));
        $$ = $3 + $2 + $4;
        if ($<i>3 == ARRAY) $$ += ", const int " + $2 + "_Size";
      }
      else $$ = make_list($2, $3, $<i>3 == ARRAY);
    }
  ;
mayinitializer:
    /* empty */
    {
      $$.clear();
    }
  | EQ initializer
    {
      $$ = " = " + $2;
    }
  ;
varconstspec:
    /* empty */
    {
      $$ = 0;
    }
  | VAR
    {
      $$ = VAR;
    }
  | CONST
    {
      $$ = CONST;
    }
  ;
formalparamstype:
    /* empty */
    {
      $$ =  "void *";
      $<i>$ = 0;
    }
  | singlenametype
    {
      $$ = $1 + " ";
      $<i>$ = IDENTIFIER;
      last_partype = $1;
    }
  | ':' ARRAY OF primary
    {
      $$ = $4 + " *";
      $<i>$ = ARRAY;
    }
  | ':' ARRAY OF CONST
    {
      $$ = "TVarRec *";
      $<i>$ = ARRAY;
    }
  ;
//---------------------------------------------------------------------------
end:
    END
  | error END
    {
      POST_ERROR;
    }
  ;
stmtlist:
    stmt
  | stmtlist ';' stmt
  | stmtlist error ';'
    {
      POST_ERROR;
    }
    stmt
  ;
labelmark:
    CONSTANT ':'
  | IDENTIFIER ':'
  ;
stmt:
    /* empty */
    {
      if (stmt_need) write_cpp(";");
      stmt_need = false;
    }
  | labelmark
    {
      stmt_need = false;
      newline();
      write_cpp("%s:", $1.begin());
    }
    stmt
  | BEGIN
    {
      stmt_need = false;
      indent--;
      newline();
      write_cpp("{");
      indent++;
    }
      stmtlist
    end
    {
      indent--;
      newline();
      write_cpp("}");
      indent++;
    }
  | asmstmt
    {
      stmt_need = false;
      p = $1.begin();
      print_asm();
    }
  | RAISE expr
    {
      stmt_need = false;
      newline();
      write_cpp("throw %s;", $2.begin());
    }
  | tryhead
    FINALLY
    {
      stmt_need = false;
      newline();
      write_cpp("__finally");
      newline();
      write_cpp("{");
      indent++;
    }
      stmtlist
    end
    {
      indent--;
      newline();
      write_cpp("}");
    }
  | tryhead
    EXCEPT
      exceptlist
    END
  | GOTO expr
    {
      newline();
      write_cpp("goto %s;", $2.begin());
    }
  | INHERITED
    {
      stmt_need = false;
      newline();
      write_cpp("inherited::%s(%s);", wrk_func_name.begin(), wrk_func_params.begin());
    }
  | primary
    {
      stmt_need = false;
      newline();
      if (stricmp($1.begin(), "break") == 0)
        write_cpp("break;");
      else if (stricmp($1.begin(), "continue") == 0)
        write_cpp("continue;");
      else if (stricmp($1.begin(), "halt") == 0)
        write_cpp("return%s", func_rtype == "void" ? ";" : " Result;");
      else if (stricmp($1.begin(), "exit") == 0)
        write_cpp("exit(0);");
      else write_cpp("%s%s", $1.begin(), ($1.end()[-1] == ')' ? ";" : "();"));
    }
  | primary '=' expr
    {
      stmt_need = false;
      newline();
      write_cpp("%s = %s;", $1.begin(), $3.begin());
    }
  | ifthen
  | ifthen ELSE
    {
      newline();
      write_cpp("else");
      indent++;
      stmt_need = true;
    }
     stmt
    {
      indent--;
    }
  | WITH exprlist DO
    {
      newline();
      yywarning("WITH statement");
      write_cpp("/* WARNING: WITH!!! (%s) */", make_list($2).begin());
      indent++;
      stmt_need = true;
    }
      stmt
    {
      indent--;
    }
  | CASE expr OF
    {
      stmt_need = false;
      newline();
      write_cpp("switch (%s)", $2.begin());
      newline();
      write_cpp("{");
      indent++;
    }
      casegrouplist
    END
    {
      indent--;
      newline();
      write_cpp("}");
    }
  | FOR primary '=' expr direction expr DO
    {
      stmt_need = false;
      newline();
      if (no_tmp) $<no_calc>6 = true;
      if (!$<no_calc>6)
      {
        write_cpp("{");
        indent++;
        newline();
        write_cpp("int %s = %s;", gen_name().begin(), $6.begin());
        newline();
        $6 = tmp_string;
      }
      write_cpp($5 == TO ? "for (%s = %s; %s <= %s; %s++)"
        : "for (%s = %s; %s >= %s; %s--)",
        $2.begin(), $4.begin(),
        $2.begin(), $6.begin(),
        $2.begin());
      indent++;
      stmt_need = true;
    }
    stmt
    {
      indent--;
      if (!$<no_calc>6)
      {
        indent--;
        newline();
        write_cpp("}");
      }
    }
  | WHILE expr DO
    {
      newline();
      write_cpp("while (%s)", $2.begin());
      indent++;
      stmt_need = true;
    }
    stmt
    {
      indent--;
    }
  | REPEAT
    {
      stmt_need = false;
      newline();
      write_cpp("do");
      newline();
      write_cpp("{");
      indent++;
    }
      stmtlist
    UNTIL expr
    {
      indent--;
      newline();
      write_cpp("}");
      newline();
      write_cpp("while (!(%s));", $5.begin());
    }
  ;
asmstmt:
    ASMSTMT
  | ASMSTMT expr
  ;
tryhead:
    TRY
    {
      stmt_need = false;
      newline();
      write_cpp("try");
      newline();
      write_cpp("{");
      indent++;
    }
    stmtlist
    {
      indent--;
      newline();
      write_cpp("}");
    }
  ;
exceptlist:
    {
      newline();
      write_cpp("catch(...)");
      newline();
      write_cpp("{");
      indent++;
    }
    stmtlist
    {
      indent--;
      newline();
      write_cpp("}");
    }
  | onexceptlist_poor
  | onexceptlist_rich
  | onexceptlist_rich onelse
  | onelse
  ;
onexceptlist_poor:
    onexcept
  | onexceptlist_rich onexcept
  ;
onexceptlist_rich:
    onexceptlist_poor ';'
  | onexceptlist_poor error ';'
  ;
onexcept:
    ON IDENTIFIER ':' primary DO
    {
      newline();
      write_cpp("catch(%s &%s)", $4.begin(), $2.begin());
      newline();
      write_cpp("{");
      indent++;
    }
    stmt
    {
      indent--;
      newline();
      write_cpp("}");
    }
  | ON primary DO
    {
      newline();
      write_cpp("catch(%s &)", $2.begin());
      newline();
      write_cpp("{");
      indent++;
    }
    stmt
    {
      indent--;
      newline();
      write_cpp("}");
    }
  ;
onelse:
    ELSE
    {
      newline();
      write_cpp("catch(...)");
      newline();
      write_cpp("{");
      indent++;
    }
    stmtlist
    {
      indent--;
      newline();
      write_cpp("}");
    }
  ;
direction:
    TO
    {
      $$ = TO;
    }
  | DOWNTO
    {
      $$ = DOWNTO;
    }
  ;
casegrouplist:
    listcaselist_poor
  | listcaselist_rich
  | listcaselist_rich elsecasehead
    {
      newline();
      write_cpp("default:");
      indent++;
    }
      stmtlist
    {
      indent--;
    }
  ;
listcaselist_rich:
    /* empty  */ { }
  | listcaselist_poor ';'
  ;
listcaselist_poor:
    listcaselist_rich listcasehead
    {
      int i;
      p = $2.begin();
      while (*p)
      {
        for (i = 0; p[i] != ','; i++);
        newline();
        p[i] = '\0';
        write_cpp("case %s:", p);
        p += i + 2;
      }
      indent++;
    }
      stmt
    {
      newline();
      write_cpp("break;");
      indent--;
    }
  ;
listcasehead:
    rangelist ':'
  | error ':'
    {
      POST_ERROR;
      $$.clear();
    }
  ;
elsecasehead:
    ELSE
  | error ELSE
    {
      POST_ERROR;
    }
  ;
ifthen:
    IF expr THEN
    {
      newline();
      write_cpp("if (%s)", $2.begin());
      indent++;
      stmt_need = true;
    }
    stmt
    {
      stmt_need = false;
      indent--;
    }
  ;
//---------------------------------------------------------------------------
primary:
    IDENTIFIER
    {
      $<i>$ = TYPE_UNKNOWN;
      $<no_calc>$ = true;
      $$ = $1;
      if (stricmp($1.begin(), wrk_func_name.begin()) == 0)
        $$ = "Result";
      else if (!class_name.empty() && stricmp($1.begin(), "Self") == 0)
        $$ = "this";
      else $<no_calc>$ = false;
    }
  | INHERITED IDENTIFIER
    {
      $<i>$ = TYPE_UNKNOWN;
      $<no_calc>$ = false;
      $$ = "inherited::" + $2;
    }
  | primary '(' exprlist ')'
    {
      if (stricmp($1.begin(), "SIZEOF") == 0)
      {
        $<i>$ = TYPE_INT;
        $<no_calc>$ = true;
        $$ = "sizeof(" + make_list($3) + ")";
      }
      else
      if (stricmp($1.begin(), "ParamStr") == 0 ||
          stricmp($1.begin(), "System::ParamStr") == 0)
      {
        $<i>$ = TYPE_STRING;
        $<no_calc>$ = true;
        $$ = "std::__argv[" + make_list($3) + "]";
      }
      else
      {
        $<i>$ = TYPE_UNKNOWN;
        $<no_calc>$ = false;
        $$ = $1 + "(" + make_list($3) + ")";
      }
    }
  | primary '[' exprlist ']'
    {
      $<i>$ = TYPE_UNKNOWN;
      $<no_calc>$ = false;
      $$ = $1;
      int i;
      p = $3.begin();
      while (*p)
      {
        for (i = 0; p[i] != ','; i++);
        $$ += '[' + string(p, i) + ']';
        p += i + 2;
      }
    }
  | primary '.' IDENTIFIER
    {
      $<i>$ = TYPE_UNKNOWN;
      $<no_calc>$ = false;
      $2 = '.';
      for (slst_p = units.begin(); slst_p != units.end(); slst_p++)
        if (stricmp(slst_p->begin(), $1.c_str()) == 0)
        {
          $1 = *slst_p;
          $2 = "::";
          break;
        }
      if (strcmp($1.begin(), "this") == 0) $2 = "->";  
      $$ = $1 + $2 + $3;
    }
  | '@' primary
    {
      $<i>$ = TYPE_PTR;
      $$ = "&" + $1;
    }
  | primary '^'
    {
      $<i>$ = TYPE_UNKNOWN;
      $$ = "*(" + $1 + ")";
    }
  | '(' expr ')'
    {
      $<i>$ = $<i>2;
      $$ = "(" + $2 + ")";
    }
  ;
primarylist:
    primary
    {
      $$ = $1 + ", ";
    }
  | primarylist ',' primary
    {
      $$ = $1 + $3 + ", ";
    }
  ;
expr:
    expr_neq
  | expr EQ expr
    {
      $<i>$ = TYPE_BOOL;
      $<no_calc>$ = $<no_calc>1 && $<no_calc>3;
      $$ = $1 + " = " + $3;
    }
  | expr COMPARE expr
    {
      $<i>$ = TYPE_BOOL;
      $<no_calc>$ = $<no_calc>1 && $<no_calc>3;
      $$ = $1 + " " + $2 + " " + $3;
    }
  | primary IS primary
    {
      $<i>$ = TYPE_BOOL;
      $<no_calc>$ = false;
      $$ = "dynamic_cast<" + $3 + ">(" + $1 + ") != NULL";
    }
  | expr IN expr
    {
      $<i>$ = TYPE_BOOL;
      $<no_calc>$ = false;
      $$ = $3 + ".Contains(" + $1 + ")";
    }
  ;
expr_neq:
    primary
    {
      if (stricmp($1.begin(), "ParamCount") == 0 ||
          stricmp($1.begin(), "System::ParamCount") == 0)
      {
        $<i>$ = TYPE_INT;
        $<no_calc>$ = true;
        $$ = "std::__argc";
      }
    }
  | CONSTANT
    {
      $<no_calc>$ = true;
    }
  | '[' ']'
    {
      $$ = "{@@}";
      yywarning("set or array value definition");
    }
  | '[' rangelist ']'
    {
      $$ = "{@" + make_list($2) + "@}";
      yywarning("set or array value definition");
    }
  | expr_neq '+' expr_neq
    {
      $<i>$ = max($<i>1, $<i>3);
      $<no_calc>$ = $<no_calc>1 && $<no_calc>3;
      $$ = $1 + ($1.end()[-1] == '\"' && $3.begin()[0] == '\"' ? " " : " + ") + $3;
    }
  | expr_neq '-' expr_neq
    {
      $<i>$ = max($<i>1, $<i>3);
      $<no_calc>$ = $<no_calc>1 && $<no_calc>3;
      $$ = $1 + " - " + $3;
    }
  | expr_neq '*' expr_neq
    {
      $<i>$ = max($<i>1, $<i>3);
      $<no_calc>$ = $<no_calc>1 && $<no_calc>3;
      $$ = $1 + " * " + $3;
    }
  | expr_neq '/' expr_neq
    {
      $<i>$ = TYPE_DOUBLE;
      $<no_calc>$ = $<no_calc>1 && $<no_calc>3;
      $$ = $1 + " / " + $3;
    }
  | expr_neq DIV expr_neq
    {
      $<i>$ = TYPE_INT;
      $<no_calc>$ = $<no_calc>1 && $<no_calc>3;
      $$ = $1 + " / " + $3;
    }
  | expr_neq MOD expr_neq
    {
      $<i>$ = TYPE_INT;
      $<no_calc>$ = $<no_calc>1 && $<no_calc>3;
      $$ = $1 + " % " + $3;
    }
  | expr_neq SHIFT expr_neq
    {
      $<i>$ = TYPE_INT;
      $<no_calc>$ = $<no_calc>1 && $<no_calc>3;
      $$ = $1 + $2 + $3;
    }
  | '-' expr_neq %prec NOT
    {
      $<i>$ = $<i>2;
      $<no_calc>$ = $<no_calc>2;
      $$ = "-" + $2;
    }
  | '+' expr_neq %prec NOT
    {
      $<i>$ = $<i>2;
      $<no_calc>$ = $<no_calc>2;
      $$ = "+" + $2;
    }
  | expr_neq AND expr_neq
    {
      $<i>$ = max($<i>1, $<i>3);
      $<no_calc>$ = $<no_calc>1 && $<no_calc>3;
      $$ = "(" + $1 +
            ($<i>$ == TYPE_BOOL ? " && " : " & ") +
            $3 + ")";
    }
  | expr_neq OR expr_neq
    {
      $<i>$ = max($<i>1, $<i>3);
      $<no_calc>$ = $<no_calc>1 && $<no_calc>3;
      $$ = "(" + $1 +
            ($<i>$ == TYPE_BOOL ? " || " : " | ") +
            $3 + ")";
    }
  | expr_neq XOR expr_neq
    {
      $<i>$ = TYPE_INT;
      $<no_calc>$ = $<no_calc>1 && $<no_calc>3;
      $$ = "(" + $1 + " ^ " + $3 + ")";
    }
  | NOT expr_neq
    {
      $<i>$ = $<i>2;
      $<no_calc>$ = $<no_calc>2;
      $$ = ($<i>$ == TYPE_BOOL ? "!" : "~") + $2;
    }
  | primary AS primary
    {
      $<i>$ = TYPE_PTR;
      $<no_calc>$ = false;
      $$ = "dynamic_cast<" + $3 + ">(" + $1 + ")";
    }
  ;
exprlist:
    /* empty */
    {
      $$ = ", ";
    }
  | expr
    {
      $$ = $1 + ", ";
    }
  | exprlist ',' expr
    {
      $$ = $1 + $3 + ", ";
    }
  ;
rangelist:
    range
    {
      $$ = $1 + ", ";
    }
  | rangelist ',' range
    {
      $$ = $1 + $3 + ", ";
    }
  ;
range:
    expr
  | expr TWOFULLSTOP expr
    {
      $$ = "@from(" + $1 + ") to (" + $3 + ")@";
      yywarning("range between two expressions");
    }
  ;
%%
//---------------------------------------------------------------------------
void translate(void)
{
#if YYDEBUG
  yydebug = 1;
  freopen("pas2cpp.txt", "w+", stderr);
#endif
  ADD_ZERO_BASED("BOOL", "1");

  ADD_ZERO_BASED("CHAR", "0xFF");
  ADD_ZERO_BASED("SIGNED CHAR", "0xFF");
  ADD_ZERO_BASED("UNSIGNED CHAR", "0xFF");
  ADD_ZERO_BASED("WCHAR_T", "0xFFFF");

  ADD_ZERO_BASED("INT", "0xFFFFFFFF");
  ADD_ZERO_BASED("UNSIGNED LONG", "0xFFFFFFFF");
  ADD_ZERO_BASED("LONG", "0xFFFFFFFF");
  ADD_ZERO_BASED("SHORT", "0xFFFF");
  ADD_ZERO_BASED("BYTE", "0xFF");
  ADD_ZERO_BASED("WORD", "0xFFFF");
  ADD_ZERO_BASED("DWORD", "0xFFFFFFFF");

  units.push_back("System");
  units.push_back("Sysinit");

  int parse_ret = 1;
  try
  {
    parse_ret = yyparse();
  }
  catch(...)
  {
    fprintf(stderr, "An error occured!\n");
    return;
  }
  if (parse_ret)
    printf("File was not fully translated, stop at line %d.\n", line_no);
  else
    printf("File was fully translated.\n");
}
//---------------------------------------------------------------------------
