/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void error(ErrorCode err, int lineNo, int colNo) {
  switch (err) {
  case ERR_INVALIDFLOAT:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDFLOAT);
    break;
  case ERR_ENDOFCOMMENT:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_ENDOFCOMMENT);
    break;
  case ERR_IDENTTOOLONG:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_IDENTTOOLONG);
    break;
  case ERR_INVALIDCHARCONSTANT:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDCHARCONSTANT);
    break;
  case ERR_INVALIDSYMBOL:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDSYMBOL);
    break;
  case ERR_INVALIDCONSTANT:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDCONSTANT);
    break;
  case ERR_INVALIDTYPE:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDTYPE);
    break;
  case ERR_INVALIDVAR:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDVAR);
    break;
  case ERR_INVALIDBASICTYPE:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDBASICTYPE);
    break;
  case ERR_INVALIDPARAM:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDPARAM);
    break;
  case ERR_INVALIDSTATEMENT:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDSTATEMENT);
    break;
  case ERR_INVALIDARGUMENTS:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDARGUMENTS);
    break;
  case ERR_INVALIDCOMPARATOR:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDCOMPARATOR);
    break;
  case ERR_INVALIDEXPRESSION:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDEXPRESSION);
    break;
  case ERR_INVALIDTERM:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDTERM);
    break;
  case ERR_INVALIDFACTOR:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDFACTOR);
    break;
  case ERR_INVALIDCONSTDECL:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDCONSTDECL);
    break;
  case ERR_INVALIDTYPEDECL:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDTYPEDECL);
    break;
  case ERR_INVALIDVARDECL:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDVARDECL);
    break;
  case ERR_INVALIDSUBDECL:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDSUBDECL);
    break;
  case ERR_INVALIDFUNCTION:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDFUNCTION);
    break;
  case ERR_INVALIDPROCEDURE:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDPROCEDURE);
    break;
  case ERR_UNDECLARED_TYPE:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_UNDECLARED_TYPE);
    break;
  case ERR_UNDECLARED_IDENT:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_UNDECLARED_IDENT);
    break;
  case ERR_INVALID_LVALUE:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALID_LVALUE);
    break;
  case ERR_INVALID_ARGUMENTS:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALID_ARGUMENTS);
    break;
  case ERR_UNDECLARED_CONSTANT:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_UNDECLARED_CONSTANT);
    break;
  case ERR_UNDECLARED_INT_CONSTANT:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_UNDECLARED_INT_CONSTANT);
    break;
  case ERR_UNDECLARED_VARIABLE:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_UNDECLARED_VARIABLE);
    break;
  case ERR_UNDECLARED_FUNCTION:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_UNDECLARED_FUNCTION);
    break;
  case ERR_UNDECLARED_PROCEDURE:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_UNDECLARED_PROCEDURE);
    break;
  case ERR_DUPLICATE_IDENT:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_DUPLICATE_IDENT);
    break;
  case ERR_TYPE_INCONSISTENCY:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_TYPE_INCONSISTENCY);
    break;
  case ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_PARAMETERS_ARGUMENTS_INCONSISTENCY);
    break;

  }
  exit(0);
}

void missingToken(TokenType tokenType, int lineNo, int colNo) {
  printf("%d-%d:Missing %s\n", lineNo, colNo, tokenToString(tokenType));
  exit(0);
}

void assert(char *msg) {
  printf("%s\n", msg);
}
