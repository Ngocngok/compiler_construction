/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object* obj);
void freeScope(Scope* scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab* symtab;
Type* intType;
Type* charType;
Type* floatType;

/******************* Type utilities ******************************/

Type* makeIntType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type* makeCharType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type* makeFloatType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_FLOAT;
  return type;
}
Type* makeArrayType(int arraySize, Type* elementType) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type* duplicateType(Type* type) {
  Type* typeTmp = (Type*) malloc(sizeof(Type));
  typeTmp->typeClass = type->typeClass;
  if(typeTmp->typeClass == TP_ARRAY)
  {
    typeTmp->arraySize = type->arraySize;
    typeTmp->elementType = type->elementType;
  }
  return typeTmp;
}

int compareType(Type* type1, Type* type2) {
  if(type1->typeClass == type2->typeClass && type2->typeClass != TP_ARRAY)
    return 1;
  else if(type1->typeClass == type2->typeClass && type2->typeClass == TP_ARRAY)
  {
    return(type1->arraySize == type2->arraySize && compareType(type1->elementType, type2->elementType));
  }
  else
  {
    return 0;
  }
  
  
}

void freeType(Type* type) {
  free(type->elementType);
  free(type);
}

/******************* Constant utility ******************************/

ConstantValue* makeIntConstant(int i) {
  ConstantValue * constantValue = (ConstantValue*) malloc(sizeof(ConstantValue));
  constantValue->type = TP_INT;
  constantValue->intValue = i;
  return constantValue;

}

ConstantValue* makeCharConstant(char ch) {
  ConstantValue * constantValue = (ConstantValue*) malloc(sizeof(ConstantValue));
  constantValue->type = TP_CHAR;
  constantValue->charValue = ch;
  return constantValue;
}

ConstantValue* makeFloatConstant(float fl) {
  ConstantValue * constantValue = (ConstantValue*) malloc(sizeof(ConstantValue));
  constantValue->type = TP_FLOAT;
  constantValue->floatValue = fl;
  return constantValue;
}

ConstantValue* duplicateConstantValue(ConstantValue* v) {
  ConstantValue * constantValue = (ConstantValue*) malloc(sizeof(ConstantValue));
  constantValue->type = v->type;
  if(constantValue->type == TP_INT)
    constantValue->intValue = v->intValue;
  else if(constantValue->type == TP_CHAR)
    constantValue->charValue = v->charValue;
  else
    constantValue->floatValue = v->floatValue;
  
  return constantValue;
}

/******************* Object utilities ******************************/

Scope* createScope(Object* owner, Scope* outer) {
  Scope* scope = (Scope*) malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object* createProgramObject(char *programName) {
  Object* program = (Object*) malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes*) malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program,NULL);
  symtab->program = program;

  return program;
}

Object* createConstantObject(char *name) {
  Object* constant = (Object*) malloc(sizeof(Object));
  strcpy(constant->name, name);
  constant->kind = OBJ_CONSTANT;
  constant->constAttrs = (ConstantAttributes*) malloc(sizeof(ConstantAttributes));
  

  return constant;
}

Object* createTypeObject(char *name) {
  Object* type = (Object*) malloc(sizeof(Object));
  strcpy(type->name, name);
  type->kind = OBJ_TYPE;
  type->typeAttrs = (TypeAttributes*) malloc(sizeof(TypeAttributes));

  return type;
  
}

Object* createVariableObject(char *name) {
  Object* variable = (Object*) malloc(sizeof(Object));
  strcpy(variable->name, name);
  variable->kind = OBJ_VARIABLE;
  variable->varAttrs = (VariableAttributes*) malloc(sizeof(VariableAttributes));

  variable->varAttrs->scope = symtab->currentScope;
  return variable;
  
}

Object* createFunctionObject(char *name) {
  Object* function = (Object*) malloc(sizeof(Object));
  strcpy(function->name, name);
  function->kind = OBJ_FUNCTION;
  function->funcAttrs = (FunctionAttributes*) malloc(sizeof(FunctionAttributes));
  function->funcAttrs->scope = createScope(function, symtab->currentScope);
  function->funcAttrs->paramList = NULL;

  return function;
}

Object* createProcedureObject(char *name) {
  Object* procedure = (Object*) malloc(sizeof(Object));
  strcpy(procedure->name, name);
  procedure->kind = OBJ_PROCEDURE;
  procedure->procAttrs = (ProcedureAttributes*) malloc(sizeof(ProcedureAttributes));
  procedure->procAttrs->scope = createScope(procedure, symtab->currentScope);
  procedure->procAttrs->paramList = NULL;

  return procedure;
}

Object* createParameterObject(char *name, enum ParamKind kind, Object* owner) {
  Object* param = (Object*) malloc(sizeof(Object));
  strcpy(param->name, name);
  param->kind = OBJ_PARAMETER;
  param->paramAttrs = (ParameterAttributes*) malloc(sizeof(ParameterAttributes));
  param->paramAttrs->kind = kind;
  param->paramAttrs->function = owner;

  return param;

}

void freeObject(Object* obj) {
  switch (obj->kind)
  {
  case OBJ_CONSTANT: 
    free(obj->constAttrs->value);
    free(obj->constAttrs);
    free(obj);
    break;
  case OBJ_PARAMETER: 
    free(obj->paramAttrs->type);
    free(obj->paramAttrs);
    free(obj);
    break;
  case OBJ_PROCEDURE: 
    freeScope(obj->procAttrs->scope);
    free(obj->procAttrs);
    free(obj);
    break;
  case OBJ_FUNCTION:
    freeScope(obj->funcAttrs->scope);
    free(obj->funcAttrs);
    free(obj);
    break;
  case OBJ_TYPE:
    free(obj->typeAttrs->actualType);
    free(obj->typeAttrs);
    free(obj);
    break;
  case OBJ_VARIABLE:
    free(obj->varAttrs->type);
    free(obj->varAttrs);
    free(obj);
    break;
  case OBJ_PROGRAM:
    freeScope(obj->progAttrs->scope);
    free(obj);
    break;

  default:
    break;
  }
}

void freeScope(Scope* scope) {
  printf("free scope %s\n", scope->owner->name);
  freeObjectList(scope->objList);
  printf("done free scope %s\n", scope->owner->name);
}

void freeObjectList(ObjectNode *objList) {
  ObjectNode *n = &(*objList);
  ObjectNode *tmp;
  if(n == NULL)
    return;

  while(n->next != NULL)
  {
    tmp = n->next;
    printf("free %s\n", n->object->name);
    freeObject(n->object);
    n = tmp;
  }
  printf("free %s\n", n->object->name);
  freeObject(n->object);
  
}

void freeReferenceList(ObjectNode *objList) {
  // TODO
  // already freed in objectlist
}

void addObject(ObjectNode **objList, Object* obj) {
  ObjectNode* node = (ObjectNode*) malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL) 
    *objList = node;
  else {
    ObjectNode *n = *objList;
    while (n->next != NULL) 
      n = n->next;
    n->next = node;
  }
  //printf("add %s \n",obj->name);
}

Object* findObject(ObjectNode *objList, char *name) {
  ObjectNode *n = &(*objList);
  while(n != NULL)
  {
    if(strcmp(n->object->name, name) == 0)
      return n->object;
    n = n->next;
  }
  return NULL;
}

/******************* others ******************************/

void initSymTab(void) {
  Object* obj;
  Object* param;
  

  symtab = (SymTab*) malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;
  
  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);
  
  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READF");
  obj->funcAttrs->returnType = makeFloatType();
  addObject(&(symtab->globalObjectList), obj);
  
  obj = createProcedureObject("WRITEI");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);
  
  obj = createProcedureObject("WRITEC");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEF");
  param = createParameterObject("f", PARAM_VALUE, obj);
  param->paramAttrs->type = makeFloatType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);
  
  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);
  
  intType = makeIntType();
  charType = makeCharType();
}

void cleanSymTab(void) {
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  //freeType(intType);
  //freeType(charType);
}

void enterBlock(Scope* scope) {
  symtab->currentScope = scope;
}

void exitBlock(void) {
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object* obj) {
  if (obj->kind == OBJ_PARAMETER) 
  {
    Object* owner = symtab->currentScope->owner;
    
    switch (owner->kind) {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);//printf("func");
      break;
    case OBJ_PROCEDURE:
      
      addObject(&(owner->procAttrs->paramList), obj);
      
      break;
    default:
      break;
    }
  }
 
  addObject(&(symtab->currentScope->objList), obj);
}


