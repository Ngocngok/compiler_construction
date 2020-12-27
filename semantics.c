/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;

Object* lookupObject(char* name)
{
    Scope* currentScope = symtab->currentScope;
    Object* object;

    while (currentScope != NULL)
    {
        object = findObject(currentScope->objList, name);

        if (object != NULL)
        {
            return object;
        }

        currentScope = currentScope->outer;
    }

    // Lookup globalObjectList
    return findObject(symtab->globalObjectList, name);
}


void checkFreshIdent(char* name)
{
    if (findObject(symtab->currentScope->objList, name) != NULL)
    {
        error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
    }
}

Object* checkDeclaredIdent(char* name)
{
    
    Object* object = lookupObject(name);

    if (object == NULL)
    {
        error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
    }
    return object;
}

Object* checkDeclaredConstant(char* name)
{
    Object* object = lookupObject(name);

    if (object == NULL)
    {
        error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);
    }
    else if (object->kind != OBJ_CONSTANT)
    {
        error(ERR_INVALIDCONSTANT, currentToken->lineNo, currentToken->colNo);
    }

    return object;
}

Object* checkDeclaredType(char* name)
{
    Object* object = lookupObject(name);

    if (object == NULL)
    {
        error(ERR_UNDECLARED_TYPE, currentToken->lineNo, currentToken->colNo);
    }
    else if (object->kind != OBJ_TYPE)
    {
        error(ERR_INVALIDTYPE, currentToken->lineNo, currentToken->colNo);
    }

    return object;
}

Object* checkDeclaredVariable(char* name)
{
    Object* object = lookupObject(name);

    if (object == NULL)
    {
        error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);
    }
    else if (object->kind != OBJ_VARIABLE)
    {
        error(ERR_INVALIDVAR, currentToken->lineNo, currentToken->colNo);
    }

    return object;
}

Object* checkDeclaredVariable1(char* name)
{
    Object* object = lookupObject(name);

    if (object == NULL)
    {
        error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);
    }
    else
    {
        switch (object->kind)
        {
        case OBJ_VARIABLE:
        case OBJ_CONSTANT:
        case OBJ_FUNCTION:
            break;
        case OBJ_PARAMETER:
            if (object->paramAttrs->function != symtab->currentScope->owner)
            {
                error(ERR_INVALIDVAR, currentToken->lineNo, currentToken->colNo);
            }
            break;
        default:
            error(ERR_INVALIDVAR, currentToken->lineNo, currentToken->colNo);
            break;
        }
    }

    return object;
}

Object* checkDeclaredFunction(char* name)
{
    Object* object = lookupObject(name);

    if (object == NULL)
    {
        error(ERR_UNDECLARED_FUNCTION, currentToken->lineNo, currentToken->colNo);
    }
    else if (object->kind != OBJ_FUNCTION)
    {
        error(ERR_INVALIDFUNCTION, currentToken->lineNo, currentToken->colNo);
    }
    
    return object;
}

Object* checkDeclaredProcedure(char* name)
{
    Object* object = lookupObject(name);

    if (object == NULL)
    {
        error(ERR_UNDECLARED_PROCEDURE, currentToken->lineNo, currentToken->colNo);
    }
    else if (object->kind != OBJ_PROCEDURE)
    {
        error(ERR_INVALIDPROCEDURE, currentToken->lineNo, currentToken->colNo);
    }
    
    return object;
}

Object* checkDeclaredLValueIdent(char* name)
{
    Object* object = lookupObject(name);

    if (object == NULL)
    {
        error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);
    }
    else
    {
        switch (object->kind)
        {
        case OBJ_VARIABLE:
            break;
        case OBJ_FUNCTION:
            if (object != symtab->currentScope->owner)
            {
                error(ERR_INVALID_LVALUE, currentToken->lineNo, currentToken->colNo);
            }
            break;
        case OBJ_PARAMETER:
            if (object->paramAttrs->function != symtab->currentScope->owner)
            {
                error(ERR_INVALID_LVALUE, currentToken->lineNo, currentToken->colNo);
            }
            break;
        default:
            error(ERR_INVALID_LVALUE, currentToken->lineNo, currentToken->colNo);
            break;
        }
    }

    return object;
}


void checkIntType(Type* type) {
    if(type->typeClass != TP_INT)
    {
        error(ERR_TYPE_INCONSISTENCY,currentToken->lineNo, currentToken->colNo);
    }
}

void checkCharType(Type* type) {
    if(type->typeClass != TP_CHAR)
    {
        error(ERR_TYPE_INCONSISTENCY,currentToken->lineNo, currentToken->colNo);
    }
}

void checkFloatType(Type* type) {
    if(type->typeClass != TP_FLOAT)
    {
        error(ERR_TYPE_INCONSISTENCY,currentToken->lineNo, currentToken->colNo);
    }
}

void checkAllowedTypeForExp(Type* type) {
    switch (type->typeClass)
    {
    case TP_INT:
    case TP_FLOAT:
        break;
    default: error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
        break;
    }
}

void checkAllowedTypeForConst(enum TypeClass type) {
    switch (type)
    {
    case TP_INT:
    case TP_FLOAT:
        break;
    default: error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
        break;
    }
}

void checkBasicType(Type* type) {
    switch (type->typeClass)
    {
    case TP_INT:
    case TP_FLOAT:
    case TP_CHAR:
        break;
    default: error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
        break;
    }
}

void checkArrayType(Type* type) {
  // TODO
}

void checkTypeEquality(Type* type1, Type* type2) 
{
    if(type1->typeClass != type2->typeClass)
    {
        error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
    }
}

void checkParamArg(Type* type1, Type* type2)
{
    if(type1->typeClass != type2->typeClass)
    {
        error(ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
    }
}