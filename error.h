/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __ERROR_H__
#define __ERROR_H__
#include "token.h"

typedef enum {
  ERR_ENDOFCOMMENT,
  ERR_IDENTTOOLONG,
  ERR_INVALIDCHARCONSTANT,
  ERR_INVALIDSYMBOL,
  ERR_INVALIDCONSTANT,
  ERR_INVALIDTYPE,
  ERR_INVALIDVAR,
  ERR_INVALIDBASICTYPE,
  ERR_INVALIDPARAM,
  ERR_INVALIDSTATEMENT,
  ERR_INVALIDARGUMENTS,
  ERR_INVALIDCOMPARATOR,
  ERR_INVALIDEXPRESSION,
  ERR_INVALIDTERM,
  ERR_INVALIDFACTOR,
  ERR_INVALIDCONSTDECL,
  ERR_INVALIDTYPEDECL,
  ERR_INVALIDVARDECL,
  ERR_INVALIDSUBDECL,
  ERR_INVALIDFLOAT,
  ERR_INVALIDFUNCTION,
  ERR_INVALIDPROCEDURE, 
  ERR_INVALID_LVALUE,
  ERR_INVALID_ARGUMENTS,
  ERR_UNDECLARED_IDENT,
  ERR_UNDECLARED_CONSTANT,
  ERR_UNDECLARED_INT_CONSTANT,
  ERR_UNDECLARED_TYPE,
  ERR_UNDECLARED_VARIABLE,
  ERR_UNDECLARED_FUNCTION,
  ERR_UNDECLARED_PROCEDURE,
  ERR_DUPLICATE_IDENT,
  ERR_TYPE_INCONSISTENCY,
  ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY,
  ERR_EXPECTED_ASSIGN_SYMBOL,
  ERR_NO_RETURNE_VALUE
} ErrorCode;


#define ERM_ENDOFCOMMENT "End of comment expected!" //c
#define ERM_IDENTTOOLONG "Identification too long!" //c
#define ERM_INVALIDCHARCONSTANT "Invalid const char!" //c
#define ERM_INVALIDSYMBOL "Invalid symbol!" //c
#define ERM_INVALIDCONSTANT "Invalid constant!" //c
#define ERM_INVALIDTYPE "Invalid type!" //c
#define ERM_INVALIDVAR "Invalid variable!" //c
#define ERM_INVALIDBASICTYPE "Invalid basic type!" //c
#define ERM_INVALIDPARAM "Invalid parameter!" //c
#define ERM_INVALIDSTATEMENT "Invalid statement!" //c
#define ERM_INVALIDARGUMENTS "Invalid arguments!" //c
#define ERM_INVALIDCOMPARATOR "Invalid comparator!" //c
#define ERM_INVALIDEXPRESSION "Invalid expression!" //c
#define ERM_INVALIDTERM "Invalid term!" //c
#define ERM_INVALIDFACTOR "Invalid factor!" //c 
#define ERM_INVALIDCONSTDECL "Invalid constant declaration!" //c
#define ERM_INVALIDTYPEDECL "Invalid type declaration!" //c
#define ERM_INVALIDVARDECL "Invalid variable declaration!" //c
#define ERM_INVALIDSUBDECL "Invalid subroutine declaration!"  //?
#define ERM_INVALIDFLOAT "Invalid float!" //c
#define ERM_INVALIDFUNCTION "Invalid function!"
#define ERM_INVALIDPROCEDURE "Invalid procedure!"
#define ERM_UNDECLARED_TYPE "Undeclared type!" //c
#define ERM_UNDECLARED_IDENT "Undeclared identifier!" //c
#define ERM_INVALID_LVALUE "Invalid lvalue in assignment."
#define ERM_INVALID_ARGUMENTS "Wrong arguments."
#define ERM_UNDECLARED_CONSTANT "Undeclared constant."
#define ERM_UNDECLARED_INT_CONSTANT "Undeclared integer constant."
#define ERM_UNDECLARED_VARIABLE "Undeclared variable."
#define ERM_UNDECLARED_FUNCTION "Undeclared function."
#define ERM_UNDECLARED_PROCEDURE "Undeclared procedure."
#define ERM_DUPLICATE_IDENT "Duplicate identifier."
#define ERM_TYPE_INCONSISTENCY "Type inconsistency"
#define ERM_PARAMETERS_ARGUMENTS_INCONSISTENCY "Parameters and arguments inconsistent!"
#define ERM_EXPECTED_ASSIGN_SYMBOL "Expect an assign symbol!"
#define ERM_NO_RETURNE_VALUE "No value returned in current function!"


void error(ErrorCode err, int lineNo, int colNo);
void missingToken(TokenType tokenType, int lineNo, int colNo);
void assert(char *msg);

#endif
