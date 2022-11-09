#ifndef __ASTNODE__
#define __ASTNODE__
#include <iostream>

#include <string>
#include <vector>

#include <assert.h>
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"

using namespace llvm;

extern int spaces;
void printspaces();
void printGrammerInfo(std::string, int);
void printSemanticError(int type, int line, std::string info);

class NIdentifier;
int parseNIdentifier(NIdentifier& nIdentifier);

Value* LogErrorV(const char* Str);
Function* getFunction(std::string Name);
void InitializeModuleAndPassManager();

class Node {
   public:
    int line;
    std::string getNodeName() { return "node"; }
    virtual ~Node() {}
    virtual int parse() { return 0; }
    virtual int handle() { return 0; }
    virtual Value* codegen();
};
/*Expressions*/
class NExpression : public Node {
   public:
    std::string name;
    std::string getNodeName() { return "Exp"; }
    virtual int parse() { return 0; }
    virtual int handle() { return 0; }
    virtual Value* codegen();
};

class NInteger : public NExpression {
   public:
    int value;
    NInteger(int value)
        : value(value) {}
    int parse();
    int handle() { return 0; }
    Value* codegen();
};

class NFloat : public NExpression {
   public:
    double value;
    NFloat(double value)
        : value(value) {}
    int parse();
    Value* codegen();
};

class NChar : public NExpression {
   public:
    char value;
    NChar(char value)
        : value(value) {}
    int parse();
    Value* codegen();
};

class NIdentifier : public NExpression {
   public:
    // std::string name;
    NIdentifier(const std::string& name) { this->name = name; }
    int parse();
    Value* codegen();
};

class NDotOperator : public NExpression {
   public:
    NExpression& exp;
    NIdentifier& id;
    NDotOperator(NExpression& exp, NIdentifier& id)
        : exp(exp), id(id) {}

    int parse();
};

class NListOperator : public NExpression {
   public:
    NExpression& lhs;
    NExpression& rhs;
    NListOperator(NExpression& exp, NExpression& rhs)
        : lhs(lhs), rhs(rhs) {}

    int parse();
};

class NArgs : public NExpression {
   public:
    NExpression& exp;
    NArgs* nArgs = nullptr;
    NArgs(NExpression& exp, NArgs* nArgs)
        : exp(exp), nArgs(nArgs) {}
    std::string getNodeName() { return "Args"; }
    int parse();
    Value* codegen();
};

// int parseNIdentifier(NIdentifier &nIdentifier);
class NMethodCall : public NExpression {
   public:
    NIdentifier& id;
    NArgs* nargs = nullptr;
    NMethodCall(NIdentifier& id, NArgs* nargs)
        : id(id), nargs(nargs) {}
    NMethodCall(NIdentifier& id)
        : id(id) {}
    int parse();
    Value* codegen();
};

class NParenOperator : public NExpression {
   public:
    NExpression& exp;
    NParenOperator(NExpression& exp)
        : exp(exp) {}
    int parse();
    Value* codegen();
};

class NSingleOperator : public NExpression {
   public:
    int op;
    std::string name;
    NExpression& hs;
    NSingleOperator(int op, NExpression& hs)
        : op(op), hs(hs) {}
    NSingleOperator(std::string name, int op, NExpression& hs)
        : name(name), op(op), hs(hs) {}
    int parse();
    Value* codegen();
};

class NBinaryOperator : public NExpression {
   public:
    int op;
    std::string name;
    NExpression& lhs;
    NExpression& rhs;
    NBinaryOperator(NExpression& lhs, int op, NExpression& rhs)
        : lhs(lhs), rhs(rhs), op(op) {}
    NBinaryOperator(std::string name,
                    NExpression& lhs,
                    int op,
                    NExpression& rhs)
        : name(name), lhs(lhs), rhs(rhs), op(op) {}
    int parse();

    Value* codegen();
};

class NAssignment : public NExpression {
   public:
    int op;
    std::string name;
    NExpression& lhs;
    NExpression& rhs;
    NAssignment(NExpression& lhs, int op, NExpression& rhs)
        : lhs(lhs), op(op), rhs(rhs) {}
    NAssignment(std::string& name, NExpression& lhs, int op, NExpression& rhs)
        : name(name), lhs(lhs), op(op), rhs(rhs) {}
    int parse();
    int handle() { return 0; }
    Value* codegen();
};

/*Specifiers*/
class NSpecifier : public Node {
   public:
    std::string type;
    NSpecifier() {}
    NSpecifier(std::string& type)
        : type(type) {}
    std::string getNodeName() { return "Specifier"; }
    int parse();

    Value* codegen();
    Type* getType();
};

/*Declarators*/
class NVarDec : public Node {
   public:
    NIdentifier& Id;
    std::vector<int> v;
    NVarDec(NIdentifier& Id)
        : Id(Id) {}
    std::string getNodeName() { return "VarDec"; }
    int parse();
    Value* codegen(Type* varType, Value* varValue);
};

class NParamDec : public Node {
   public:
    NSpecifier& nSpecifier;
    NVarDec& varDec;
    NParamDec(NSpecifier& nSpecifier, NVarDec& varDec)
        : nSpecifier(nSpecifier), varDec(varDec) {}
    std::string getNodeName() { return "ParamDec"; }
    int parse();
    Value* codegen();
    std::pair<std::string, Type*> getType();
};

class NVarList : public Node {
   public:
    NParamDec& nParamDec;
    NVarList* nVarList = nullptr;
    NVarList(NParamDec& nParamDec, NVarList* nVarList)
        : nParamDec(nParamDec), nVarList(nVarList) {}
    std::string getNodeName() { return "VarList"; }
    int parse();
    Value* codegen();
};

class NFunDec : public Node {
   public:
    NIdentifier& Id;
    NVarList* arguments = nullptr;
    NFunDec(NIdentifier& Id, NVarList* arguments)
        : Id(Id), arguments(arguments) {}
    std::string getNodeName() { return "FunDec"; }
    int parse();
    Function* funcodegen(Type* retType);
};

/*Local Definitions*/

class NDec : public Node {
   public:
    NVarDec& vardec;
    NExpression* exp = nullptr;
    NDec(NVarDec& vardec)
        : vardec(vardec) {}
    NDec(NVarDec& vardec, NExpression* exp)
        : vardec(vardec), exp(exp) {}
    std::string getNodeName() { return "Dec"; }
    int parse();
    Value* codegen(Type* varType);  // mark
};

class NDecList : public Node {
   public:
    NDec& dec;
    NDecList* nDecList = nullptr;
    NDecList(NDec& dec, NDecList* nDecList)
        : dec(dec), nDecList(nDecList) {}
    std::string getNodeName() { return "DecList"; }
    int parse();
    Value* codegen(Type* varType);  // mark
};

class NDef : public Node {
   public:
    NSpecifier& nSpecifier;
    NDecList* nDecList = nullptr;
    NDef(NSpecifier& nSpecifier, NDecList* nDecList)
        : nSpecifier(nSpecifier), nDecList(nDecList) {}
    std::string getNodeName() { return "Def"; }
    int parse();
    Value* codegen();
};

class NDefList : public Node {
   public:
    NDef& nDef;
    NDefList* nDefList = nullptr;
    NDefList(NDef& nDef, NDefList* nDefList)
        : nDef(nDef), nDefList(nDefList) {}
    std::string getNodeName() { return "DefList"; }
    int parse();
    Value* codegen();
};

/*Specifiers*/
class NStructSpecifier : public NSpecifier {
   public:
    NIdentifier* tag = nullptr;
    NDefList* deflist = nullptr;
    NStructSpecifier(NIdentifier* tag)
        : tag(tag) {}
    NStructSpecifier(NIdentifier* tag, NDefList* deflist)
        : tag(tag), deflist(deflist) {}
    int parse();
};
/*Statements*/

class NStatement : public Node {};

class NStmt : public NStatement {
   public:
    int type;
    std::string getNodeName() { return "Stmt"; }
    virtual int parse() { return 0; }
};

class NStmtList : public Node {
   public:
    NStmt& nStmt;
    NStmtList* nStmtList = nullptr;
    NStmtList(NStmt& nStmt, NStmtList* nStmtList)
        : nStmt(nStmt), nStmtList(nStmtList) {}
    std::string getNodeName() { return "StmtList"; }
    int parse();
    Value* codegen();
};

class NCompSt : public NStatement {
   public:
    NDefList* ndeflist = nullptr;
    NStmtList* nstmtlist = nullptr;
    NCompSt(NDefList* ndeflist, NStmtList* nstmtlist)
        : ndeflist(ndeflist), nstmtlist(nstmtlist) {}
    std::string getNodeName() { return "CompSt"; }
    int parse();
    Value* codegen();
};

class NExpStmt : public NStmt {
   public:
    NExpression& exp;
    NExpStmt(NExpression& exp)
        : exp(exp) {}
    // std::string getNodeName() { return "NExpStmt"; }
    int parse();
    Value* codegen();
};

class NCompStStmt : public NStmt {
   public:
    NCompSt& compst;
    NCompStStmt(NCompSt& compst)
        : compst(compst) {}
    int parse();
    Value* codegen();
};

class NRetutnStmt : public NStmt {
   public:
    NExpression& exp;
    NRetutnStmt(NExpression& exp)
        : exp(exp) {}
    int parse();
    Value* codegen();
};

class NIfStmt : public NStmt {
   public:
    NExpression& exp;
    NStmt& stmt;
    NIfStmt(NExpression& exp, NStmt& stmt)
        : exp(exp), stmt(stmt) {}
    int parse();
    Value* codegen();
};

class NIfElseStmt : public NStmt {
   public:
    NExpression& exp;
    NStmt& stmt;
    NStmt& stmt_else;
    NIfElseStmt(NExpression& exp, NStmt& stmt, NStmt& stmt_else)
        : exp(exp), stmt(stmt), stmt_else(stmt_else) {}
    int parse();
    Value* codegen();
};

class NWhileStmt : public NStmt {
   public:
    NExpression& exp;
    NStmt& stmt;
    NWhileStmt(NExpression& exp, NStmt& stmt)
        : exp(exp), stmt(stmt) {}
    int parse();
    Value* codegen();
};

class NBreakStmt : public NStmt {
   public:
    NBreakStmt() {}
    int parse();
    Value* codegen();
};

/*High-level Definitions*/

class NExtDecList : public Node {
   public:
    NVarDec& nVarDec;
    NExtDecList* nExtDecList = nullptr;
    NExtDecList(NVarDec& nVarDec, NExtDecList* nExtDecList)
        : nVarDec(nVarDec), nExtDecList(nExtDecList) {}
    std::string getNodeName() { return "ExtDecList"; }
    int parse();
};

class NExtDef : public Node {
   public:
    NSpecifier& specifier;
    NExtDecList* nextdeclist = nullptr;
    NFunDec* fundec = nullptr;
    NCompSt* compst = nullptr;
    NExtDef(NSpecifier& specifier)
        : specifier(specifier) {}
    NExtDef(NSpecifier& specifier, NExtDecList* nextdeclist)
        : specifier(specifier), nextdeclist(nextdeclist) {}

    NExtDef(NSpecifier& specifier, NFunDec* fundec, NCompSt* compst)
        : specifier(specifier), fundec(fundec), compst(compst) {}
    std::string getNodeName() { return "ExtDef"; }
    int parse();
};

class NExtDefVarDec : public NExtDef {
   public:
    // NExtDefVarDec(NSpecifier &specifier) : NExtDef(specifier) {}
    NExtDefVarDec(NSpecifier& specifier, NExtDecList* nextdeclist)
        : NExtDef(specifier, nextdeclist) {}
    std::string getNodeName() { return "ExtDefVarDec"; }
    Value* codegen();
};

class NExtDefFunDec : public NExtDef {
   public:
    NExtDefFunDec(NSpecifier& specifier, NFunDec* fundec, NCompSt* compst)
        : NExtDef(specifier, fundec, compst) {}
    std::string getNodeName() { return "ExtDefFunDec"; }
    Value* codegen();
};

class NExtDefList : public Node {
   public:
    NExtDef& nExtDef;
    NExtDefList* nExtDefList = nullptr;
    NExtDefList(NExtDef& nExtDef, NExtDefList* nExtDefList)
        : nExtDef(nExtDef), nExtDefList(nExtDefList) {}
    std::string getNodeName() { return "ExtDefList"; }
    int parse();
    Value* codegen();
};

class NProgram : public Node {
   public:
    NExtDefList* nextdeflist;
    NProgram(NExtDefList* nextdeflist)
        : nextdeflist(nextdeflist) {}
    int parse();
    Value* codegen();
};

#endif