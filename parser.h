/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */
#ifndef __PARSER_H__
#define __PARSER_H__
#include "token.h"
#include "semantics.h"

void scan(void);
void eat(TokenType tokenType);

void compileProgram(void);
void compileBlock(void);
void compileBlock2(void);
void compileBlock3(void);
void compileBlock4(void);
void compileBlock5(void);
void compileConstDecls(void);
void compileConstDecl(void);
void compileTypeDecls(void);
void compileTypeDecl(void);
void compileVarDecls(void);
void compileVarDecl(void);
void compileSubDecls(void);
void compileFuncDecl(void);
void compileProcDecl(void);
void compileUnsignedConstant(void);
ConstantValue* compileConstant(void);
ConstantValue* compileConstant2(void);
Type* compileType(void);
Type* compileBasicType(void);
void compileParams(void);
void compileParams2(void);
void compileParam(void);
void compileStatements(void);
void compileStatements2(void);
void compileStatement(void);
void compileAssignSt(void);
void compileCallSt(void);
void compileGroupSt(void);
void compileIfSt(void);
void compileElseSt(void);
void compileWhileSt(void);
void compileForSt(void);
void compileArguments(Object* procedure);
void compileArguments2(ObjectNode* objectNode);
void compileCondition(void);
Type* compileCondition2(void);
Type* compileExpression(void);
Type* compileExpression2(void);
Type* compileExpression3(void);
Type* compileTerm(void);
Type* compileTerm2(Type* previousType);
Type* compileFactor(void);
Type* compileIndexes(Type* arrayType);
Type* compileLValue(void);

int compile(char *fileName);

#endif
