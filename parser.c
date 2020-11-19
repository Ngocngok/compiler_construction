/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>

#include "reader.h"
#include "scanner.h"
#include "parser.h"
#include "error.h"

Token *currentToken;
Token *lookAhead;

void scan(void) {
  Token* tmp = currentToken;
  currentToken = lookAhead;
  lookAhead = getValidToken();
  free(tmp);
}

void eat(TokenType tokenType) {
  if (lookAhead->tokenType == tokenType) {
    printToken(lookAhead);
    scan();
  } else missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
}

void compileProgram(void) {
  assert("Parsing a Program ....");
  eat(KW_PROGRAM);
  eat(TK_IDENT);
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_PERIOD);
  assert("Program parsed!");
}

void compileBlock(void) {
  assert("Parsing a Block ....");
  if (lookAhead->tokenType == KW_CONST) {
    eat(KW_CONST);
    compileConstDecl();
    compileConstDecls();
    compileBlock2();
  }
  else compileBlock2();
  assert("Block parsed!");
}

void compileBlock2(void) {
  if (lookAhead->tokenType == KW_TYPE) {
    eat(KW_TYPE);
    compileTypeDecl();
    compileTypeDecls();
    compileBlock3();
  }
  else compileBlock3();
}

void compileBlock3(void) {
  if (lookAhead->tokenType == KW_VAR) {
    eat(KW_VAR);
    compileVarDecl();
    compileVarDecls();
    compileBlock4();
  }
  else compileBlock4();
}

void compileBlock4(void) {
  compileSubDecls();
  compileBlock5();
}

void compileBlock5(void) {
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
}

void compileConstDecls(void) {
  while(lookAhead->tokenType == TK_IDENT)
  {
    compileConstDecl();
  }

}

void compileConstDecl(void) {
  if(lookAhead->tokenType == TK_IDENT)
  {
    eat(TK_IDENT);
    eat(SB_EQ);
    compileConstant();
    eat(SB_SEMICOLON);
  }
  else
   error(ERR_INVALIDCONSTDECL, lookAhead->lineNo, lookAhead->colNo);
}

void compileTypeDecls(void) {
  while(lookAhead->tokenType == TK_IDENT)
  {
    compileTypeDecl();
  }
}

void compileTypeDecl(void) {
  if(lookAhead->tokenType == TK_IDENT)
  {
    eat(TK_IDENT);
    eat(SB_EQ);
    compileType();
    eat(SB_SEMICOLON);
  }
  else
    error(ERR_INVALIDTYPEDECL, lookAhead->lineNo, lookAhead->colNo);
}

void compileVarDecls(void) {
  while(lookAhead->tokenType == TK_IDENT)
  {
    compileVarDecl();
  }
}

void compileVarDecl(void) {
  if(lookAhead->tokenType == TK_IDENT)
  {
    eat(TK_IDENT);
    eat(SB_COLON);
    compileType();
    eat(SB_SEMICOLON);
  }
  else 
    error(ERR_INVALIDVARDECL, lookAhead->lineNo, lookAhead->colNo);
}

void compileSubDecls(void) {
  assert("Parsing subtoutines ....");

  while (lookAhead->tokenType == KW_FUNCTION || lookAhead->tokenType == KW_PROCEDURE)
  {
    if(lookAhead->tokenType == KW_PROCEDURE)
    {
      compileProcDecl();
    }
    else compileFuncDecl();
  }


  assert("Subtoutines parsed ....");
}

void compileFuncDecl(void) {
  assert("Parsing a function ....");

  if(lookAhead->tokenType == KW_FUNCTION)
  {
    eat(KW_FUNCTION);
    eat(TK_IDENT);
    compileParams();
    eat(SB_COLON);
    compileBasicType();
    eat(SB_SEMICOLON);
    compileBlock();
    eat(SB_SEMICOLON);
  }
  else return;

  assert("Function parsed ....");
}

void compileProcDecl(void) {
  assert("Parsing a procedure ....");

  if(lookAhead->tokenType == KW_PROCEDURE)
  {
    eat(KW_PROCEDURE);
    eat(TK_IDENT);
    compileParams();
    eat(SB_SEMICOLON);
    compileBlock();
    eat(SB_SEMICOLON);
  }
  else return;

  assert("Procedure parsed ....");
}

void compileUnsignedConstant(void) {
  switch (lookAhead->tokenType)
  {
  case TK_NUMBER: eat(TK_NUMBER);
    break;
  case TK_CHAR: eat(TK_CHAR);
    break;
  case TK_IDENT: eat(TK_IDENT);
    break;

  default:
    error(ERR_INVALIDCONSTANT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }

}

void compileConstant(void) {
  switch (lookAhead->tokenType)
  {
  case SB_PLUS:
    eat(SB_PLUS);
    compileConstant2();
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    compileConstant2();
    break;
  case TK_CHAR:
    eat(TK_CHAR);
    break;
  default:
    compileConstant2();
    break;
  }
}

void compileConstant2(void) {
  switch (lookAhead->tokenType)
  {
  case TK_FLOAT:
    eat(TK_FLOAT);
    break;
  case TK_IDENT: //what this ?
    eat(TK_IDENT);
    break;
  case TK_NUMBER:
    eat(TK_NUMBER);
    break;
  default:
    error(ERR_INVALIDCONSTANT, lookAhead->lineNo, lookAhead->colNo);
  }

}

void compileType(void) {
  switch (lookAhead->tokenType)
  {
  case KW_FLOAT: eat(KW_FLOAT);
    break;
  case KW_INTEGER: eat(KW_INTEGER);
    break;
  case KW_CHAR: eat(KW_CHAR);
    break;
  case TK_IDENT: eat(TK_IDENT);
    break;
  case KW_ARRAY:
    eat(KW_ARRAY);
    eat(SB_LSEL);
    eat(TK_NUMBER);
    eat(SB_RSEL);
    eat(KW_OF);
    compileType();
    break;
  default:
    error(ERR_INVALIDTYPE, lookAhead->lineNo, lookAhead->colNo);
  }

}

void compileBasicType(void) {
  switch (lookAhead->tokenType)
  {
  case KW_INTEGER: eat(KW_INTEGER);
    break;
  case KW_CHAR: eat(KW_CHAR);
    break;
  case KW_FLOAT: eat(KW_FLOAT);
    break;
  default:
    error(ERR_INVALIDBASICTYPE, lookAhead->lineNo, lookAhead->colNo);
  }
}


// error occur when write function() without declare proper parammeters insides
void compileParams(void) {
  if(lookAhead->tokenType == SB_LPAR)
  {
    eat(SB_LPAR);
    if(lookAhead->tokenType == TK_IDENT || lookAhead->tokenType == KW_VAR)
    {
      compileParam();
      compileParams2();
    }
    else
      error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
    
    eat(SB_RPAR);
  }
}

void compileParams2(void) {
  while(lookAhead->tokenType == SB_SEMICOLON)
  {
    eat(SB_SEMICOLON);
    eat(TK_IDENT);
    eat(SB_COLON);
    compileBasicType();
  }
}

void compileParam(void) {
  if(lookAhead->tokenType == KW_VAR)
  {
    eat(KW_VAR);
  }
  eat(TK_IDENT);
  eat(SB_COLON);
  compileBasicType();

}

void compileStatements(void) {
  compileStatement();
  compileStatements2();
}

void compileStatements2(void) {
  if(lookAhead->tokenType == SB_SEMICOLON)
  {
    eat(SB_SEMICOLON);
    compileStatement();
    compileStatements2();
  }

}

void compileStatement(void) {
  switch (lookAhead->tokenType) {
  case TK_IDENT:
    compileAssignSt();
    break;
  case KW_CALL:
    compileCallSt();
    break;
  case KW_BEGIN:
    compileGroupSt();
    break;
  case KW_IF:
    compileIfSt();
    break;
  case KW_WHILE:
    compileWhileSt();
    break;
  case KW_FOR:
    compileForSt();
    break;
    // EmptySt needs to check FOLLOW tokens
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
    break;
    // Error occurs
  default:
    error(ERR_INVALIDSTATEMENT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileAssignSt(void) {
  assert("Parsing an assign statement ....");

  //variable
  eat(TK_IDENT);
  compileIndexes();
  switch(lookAhead->tokenType)
  {
    case SB_ASSIGN: eat(SB_ASSIGN); compileExpression(); break;
    case SB_TIMESASSIGN: eat(SB_TIMESASSIGN); compileExpression();break;
    case SB_MINUSASSIGN: eat(SB_MINUSASSIGN); compileExpression();break;
    case SB_PLUSASSIGN: eat(SB_PLUSASSIGN); compileExpression();break;
    case SB_SLASHASSIGN: eat(SB_SLASHASSIGN); compileExpression();break;
  }
  

  assert("Assign statement parsed ....");
}

void compileCallSt(void) {
  assert("Parsing a call statement ....");

  eat(KW_CALL);
  //procedureIdent
  eat(TK_IDENT);
  compileArguments();


  assert("Call statement parsed ....");
}

void compileGroupSt(void) {
  assert("Parsing a group statement ....");

  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);

  assert("Group statement parsed ....");
}

void compileIfSt(void) {
  assert("Parsing an if statement ....");
  eat(KW_IF);
  compileCondition();
  eat(KW_THEN);
  compileStatement();
  if (lookAhead->tokenType == KW_ELSE)
    compileElseSt();
  assert("If statement parsed ....");
}

void compileElseSt(void) {
  eat(KW_ELSE);
  compileStatement();
}

void compileWhileSt(void) {
  assert("Parsing a while statement ....");

  eat(KW_WHILE);
  compileCondition();
  eat(KW_DO);
  compileStatements();

  assert("While statement parsed ....");
}

void compileForSt(void) {
  assert("Parsing a for statement ....");

  eat(KW_FOR);
  eat(TK_IDENT);
  eat(SB_ASSIGN);
  compileExpression();
  eat(KW_TO);
  compileExpression();
  eat(KW_DO);
  compileStatements();


  assert("For statement parsed ....");
}

void compileArguments(void) {
  if(lookAhead->tokenType == SB_LPAR)
  {
    eat(SB_LPAR);
    switch (lookAhead->tokenType)
    {
    case SB_PLUS:
    case SB_MINUS:
    case TK_NUMBER:
    case TK_CHAR:
    case TK_FLOAT:
    case TK_IDENT:
    case SB_LPAR:
      compileExpression();
      compileArguments2();
      break;

    default: error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
      break;
    }
    
    eat(SB_RPAR);
  }

}

void compileArguments2(void) {
  switch(lookAhead->tokenType)
  {
    case SB_COMMA:  
      eat(SB_COMMA);
      compileExpression();
      compileArguments2();
      break;
    case SB_RPAR:
      break;
    default : error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
  }
  
}

void compileCondition(void) {
  compileExpression();
  compileCondition2();
}

void compileCondition2(void) {
  switch (lookAhead->tokenType)
  {
  case SB_EQ:
    eat(SB_EQ);
    compileExpression();
    break;
  case SB_NEQ:
    eat(SB_NEQ);
    compileExpression();
    break;
  case SB_LT:
    eat(SB_LT);
    compileExpression();
    break;
  case SB_GT:
    eat(SB_GT);
    compileExpression();
    break;
  case SB_LE:
    eat(SB_LE);
    compileExpression();
    break;
  case SB_GE:
    eat(SB_GE);
    compileExpression();
    break;
  case SB_PLUS:
    eat(SB_PLUS);
    compileExpression2();
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    compileExpression2();
    break;
  default: error(ERR_INVALIDCOMPARATOR, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileExpression(void) {
  assert("Parsing an expression");

  switch (lookAhead->tokenType)
  {
  case SB_PLUS:
    eat(SB_PLUS);
    compileExpression2();
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    compileExpression2();
    break;
  default: compileExpression2();
    break;
  }

  assert("Expression parsed");
}

void compileExpression2(void) {
  compileTerm();
  compileExpression3();
}


void compileExpression3(void) {
  switch (lookAhead->tokenType)
  {
  case SB_PLUS:
    eat(SB_PLUS);
    compileTerm();
    compileExpression3();
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    compileTerm();
    compileExpression3();
    break;
  case KW_TO:
  case KW_DO:
  case SB_RPAR:
  case SB_COMMA:
  case SB_EQ:
  case SB_NEQ:
  case SB_LE:
  case SB_LT:
  case SB_GE:
  case SB_GT:
  case SB_RSEL:
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
  case KW_THEN:
    break;
  default: error(ERR_INVALIDEXPRESSION, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileTerm(void) {
  compileFactor();
  compileTerm2();
}

void compileTerm2(void) {
  switch (lookAhead->tokenType)
  {
  case SB_TIMES:
    eat(SB_TIMES);
    compileFactor();
    compileTerm2();
    break;
  case SB_SLASH:
    eat(SB_SLASH);
    compileFactor();
    compileTerm2();
    break;
  case SB_MOD:
    eat(SB_MOD);
    compileFactor();
    compileTerm2();
    break;
  
  case SB_PLUS:
  case SB_MINUS:
  case KW_TO:
  case KW_DO:
  case SB_RPAR:
  case SB_COMMA:
  case SB_EQ:
  case SB_NEQ:
  case SB_LE:
  case SB_LT:
  case SB_GE:
  case SB_GT:
  case SB_RSEL:
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
  case KW_THEN:
    break;
  default: error(ERR_INVALIDTERM, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileFactor(void) {
  switch (lookAhead->tokenType)
  {
  case TK_NUMBER: eat(TK_NUMBER);
    break;
  case TK_CHAR: eat(TK_CHAR);
    break;
  case TK_FLOAT: eat(TK_FLOAT);
    break;
  case TK_IDENT: eat(TK_IDENT);
    if(lookAhead->tokenType == SB_LSEL)
    {
      compileIndexes();
      break;
    }
    else if(lookAhead->tokenType == SB_LPAR)
    {
      compileArguments();
      break;
    }
    else break;
  case SB_LPAR: eat(SB_LPAR); compileExpression(); eat(SB_RPAR); break;

  default: error(ERR_INVALIDFACTOR, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileIndexes(void) {
  if (lookAhead->tokenType == SB_LSEL) {
    eat(SB_LSEL);
    compileExpression();
    eat(SB_RSEL);
  }
}

int compile(char *fileName) {
  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;

  currentToken = NULL;
  lookAhead = getValidToken();

  compileProgram();

  free(currentToken);
  free(lookAhead);
  closeInputStream();
  return IO_SUCCESS;

}