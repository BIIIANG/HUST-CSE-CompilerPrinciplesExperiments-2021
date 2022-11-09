#include "astnode.h"
#include "parser.hpp"

#include <fstream>

extern int yylineno;
extern char *yytext;
extern FILE *yyin;
int allerror;
extern "C" {
extern int yylex(void);
}

int yycolumn = 1;
int spaces = 0;

NProgram *p = nullptr;
int grammererror = 0;
using namespace llvm;

std::unique_ptr<LLVMContext> theContext;
std::unique_ptr<Module> theModule;
std::unique_ptr<IRBuilder<>> builder;
std::map<std::string, AllocaInst *> namedValues;
std::unique_ptr<legacy::FunctionPassManager> theFPM;

std::map<std::string, AllocaInst *> curNamedValues;

BasicBlock *continueBasicBlock = nullptr;
int main(int argc, char *argv[]) {
  yyin = fopen(argv[1], "r");
  if (!yyin)
    return 1;
  yylineno = 1;
  allerror = 0;
  // yylex();
  yyparse();
  if (allerror)
    return 1;
  if (p) {
    //p->parse();
    // Init
    InitializeModuleAndPassManager();
    if (p->codegen()) {
      theModule->print(outs(), nullptr);
    }
  }
  return 0;
}