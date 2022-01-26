#include <iostream>

#include <string>
#include <vector>

#include <algorithm>
#include <assert.h>
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

#include <fstream>

using namespace llvm;

std::unique_ptr<LLVMContext> theContext;
std::unique_ptr<Module> theModule;
std::unique_ptr<IRBuilder<>> builder;
std::map<std::string, AllocaInst *> namedValues;
std::unique_ptr<legacy::FunctionPassManager> theFPM;

std::map<std::string, AllocaInst *> curNamedValues;

BasicBlock *continueBasicBlock = nullptr;

void InitializeModuleAndPassManager() {
  // Open a new module.
  theContext = std::make_unique<LLVMContext>();
  theModule = std::make_unique<Module>("test", *theContext);

  // theModule->setDataLayout(dL);

  // Create a new builder for the module.
  builder = std::make_unique<IRBuilder<>>(*theContext);

  // Create a new pass manager attached to it.
  theFPM = std::make_unique<legacy::FunctionPassManager>(theModule.get());

  // Promote allocas to registers.
  //theFPM->add(createPromoteMemoryToRegisterPass());
  // Do simple "peephole" optimizations and bit-twiddling optzns.
  //theFPM->add(createInstructionCombiningPass());
  // Reassociate expressions.
  //theFPM->add(createReassociatePass());
  // Eliminate Common SubExpressions.
  //theFPM->add(createGVNPass());
  // Simplify the control flow graph (deleting unreachable blocks, etc).
  //theFPM->add(createCFGSimplificationPass());

  theFPM->doInitialization();
}

int main(int argc, char *argv[]) {
  // Init
  InitializeModuleAndPassManager();

  //默认输出函数putchar
  std::vector<Type *> putArgs;
  std::vector<Value *> argsV;
  putArgs.push_back(Type::getInt32Ty(*theContext));
  FunctionType *putType = FunctionType::get(builder->getInt32Ty(), putArgs, false);
  Function *putFunc = Function::Create(putType, Function::ExternalLinkage, "putchar", theModule.get());
  
  //默认输入函数getchar
  std::vector<Type *> getArgs;
  std::vector<Value *> getArgsV;
  FunctionType *getType = FunctionType::get(builder->getInt32Ty(), getArgs, false);
  Function *getFunc = Function::Create(getType, Function::ExternalLinkage, "getchar", theModule.get());
  
  //设置返回类型
  Type *retType = Type::getInt32Ty(*theContext);
  std::vector<Type *> argsTypes;     //参数类型
  std::vector<std::string> argNames; //参数名
  FunctionType *ft = FunctionType::get(retType, argsTypes, false);
  Function *f = Function::Create(ft, Function::ExternalLinkage, "main", theModule.get());
  //为函数的参数设置名字
  unsigned idx = 0;
  for (auto &arg : f->args()) { arg.setName(argNames[idx++]); }
  //创建第一个基本块 函数入口
  BasicBlock *bb = BasicBlock::Create(*theContext, "entry", f);
  builder->SetInsertPoint(bb);
  
  //根据输入的单字符，判断，如果是'a'，则输出'Y'，否则输出'N'。
  //设置返回类型
  //begin
  AllocaInst *alloca_a = builder->CreateAlloca(Type::getInt32Ty(*theContext), nullptr, "a");
  Value *callgetchar = builder->CreateCall(getFunc, getArgsV, "callgetchar");
  builder->CreateStore(callgetchar, alloca_a);
  Value *load_a = builder->CreateLoad(alloca_a->getAllocatedType(), alloca_a, "a");
  Value *const_0 = ConstantInt::get(*theContext, APInt(32, 'a', true));
  Value *compare_a_0 = builder->CreateICmpEQ(load_a, const_0, "comp");
  Value *condVal = builder->CreateICmpNE(compare_a_0, Constant::getNullValue(compare_a_0->getType()), "cond");
  // 创建条件为真和假应跳转的3个基本块
  BasicBlock *thenb = BasicBlock::Create(*theContext, "then", f);
  BasicBlock *elseb = BasicBlock::Create(*theContext, "else", f);
  BasicBlock *ifcontb = BasicBlock::Create(*theContext, "ifcont", f);
  // 根据condVal值跳转 真为thenb 否则为elseb
  builder->CreateCondBr(condVal, thenb, elseb);
  // 进入thenb基本块
  builder->SetInsertPoint(thenb);
  Value *const_1 = ConstantInt::get(*theContext, APInt(32, 'Y', true));
  builder->CreateStore(const_1, alloca_a);
  Value *load_a1 = builder->CreateLoad(alloca_a->getAllocatedType(), alloca_a, "a");
  argsV.clear();
  argsV.push_back(load_a1);
  builder->CreateCall(putFunc, argsV, "callputchar");
  builder->CreateBr(ifcontb);
  // 进入elseb基本块
  builder->SetInsertPoint(elseb);
  Value *const_2 = ConstantInt::get(*theContext, APInt(32, 'N', true));
  builder->CreateStore(const_2, alloca_a);
  Value *load_a2 = builder->CreateLoad(alloca_a->getAllocatedType(), alloca_a, "a");
  argsV.clear();
  argsV.push_back(load_a2);
  builder->CreateCall(putFunc, argsV, "callputchar");
  builder->CreateBr(ifcontb);
  // 将创建的ifcontb 基本块 插入
  // f->getBasicBlockList().push_back(ifcontb);
  // 进入 infcontb
  builder->SetInsertPoint(ifcontb);

  // end
  //设置返回值
  builder->CreateRet(const_0);
  verifyFunction(*f);
  // Run the optimizer on the function.
  // theFPM->run(*f);
  //输出
  theModule->print(outs(), nullptr);

  return 0;
}