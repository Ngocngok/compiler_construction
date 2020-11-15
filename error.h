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
  ERR_INVALIDFLOAT
} ErrorCode;


#define ERM_ENDOFCOMMENT "End of comment expected!" //c
#define ERM_IDENTTOOLONG "Identification too long!" //c
#define ERM_INVALIDCHARCONSTANT "Invalid const char!" //c
#define ERM_INVALIDSYMBOL "Invalid symbol!" //c
#define ERM_INVALIDCONSTANT "Invalid constant!" //c
#define ERM_INVALIDTYPE "Invalid type!" //c
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

void error(ErrorCode err, int lineNo, int colNo);
void missingToken(TokenType tokenType, int lineNo, int colNo);
void assert(char *msg);

#endif
