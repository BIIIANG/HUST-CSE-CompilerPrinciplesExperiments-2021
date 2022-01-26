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
  putArgs.push_back(Type::getInt32Ty(*theContext));
  FunctionType *putType = FunctionType::get(builder->getInt32Ty(), putArgs, false);
  Function *putFunc = Function::Create(putType, Function::ExternalLinkage, "putchar", theModule.get());

  //设置返回类型
  Type *retType = Type::getInt32Ty(*theContext);
  std::vector<Type *> argsTypes;     //参数类型
  std::vector<std::string> argNames; //参数名
  //无参，所以不push内容
  //得到函数类型
  FunctionType *ft = FunctionType::get(retType, argsTypes, false);
  //创建函数
  Function *f = Function::Create(ft, Function::ExternalLinkage, "main", theModule.get());
  //为函数的参数设置名字
  unsigned idx = 0;
  for (auto &arg : f->args()) {
    arg.setName(argNames[idx++]);
  }
  //创建第一个基本块 函数入口
  BasicBlock *bb = BasicBlock::Create(*theContext, "entry", f);
  builder->SetInsertPoint(bb);
  // 为参数变量申请空间
  // 无参
  // 创建第一个变量 a
  AllocaInst *alloca_a = builder->CreateAlloca(Type::getInt32Ty(*theContext), nullptr, "a");
  // 得到常量1
  Value *const_1 = ConstantInt::get(*theContext, APInt(32, 'H', true));
  // 初始化
  builder->CreateStore(const_1, alloca_a);
  Function *calleeF = theModule->getFunction("putchar");
  // 处理参数
  std::vector<Value *> argsV;
  Value *load_a4 = builder->CreateLoad(alloca_a->getAllocatedType(), alloca_a, "a");
  argsV.push_back(load_a4);
  // 判断参数是否符合 自行处理
  Value *callputchar = builder->CreateCall(calleeF, argsV, "callputchar");
  // begin
  Value *const_2 = ConstantInt::get(*theContext, APInt(32, 'U', true));
  argsV.clear();
  argsV.push_back(const_2);
  Value *callputchar_2 = builder->CreateCall(calleeF, argsV, "callputchar");
  Value *const_3 = ConstantInt::get(*theContext, APInt(32, 'S', true));
  argsV.clear();
  argsV.push_back(const_3);
  Value *callputchar_3 = builder->CreateCall(calleeF, argsV, "callputchar");
  Value *const_4 = ConstantInt::get(*theContext, APInt(32, 'T', true));
  argsV.clear();
  argsV.push_back(const_4);
  Value *callputchar_4 = builder->CreateCall(calleeF, argsV, "callputchar");
  Value *const_5 = ConstantInt::get(*theContext, APInt(32, 'C', true));
  argsV.clear();
  argsV.push_back(const_5);
  Value *callputchar_5 = builder->CreateCall(calleeF, argsV, "callputchar");
  Value *const_6 = ConstantInt::get(*theContext, APInt(32, 'S', true));
  argsV.clear();
  argsV.push_back(const_6);
  Value *callputchar_6 = builder->CreateCall(calleeF, argsV, "callputchar");
  Value *const_7 = ConstantInt::get(*theContext, APInt(32, 'E', true));
  argsV.clear();
  argsV.push_back(const_7);
  Value *callputchar_7 = builder->CreateCall(calleeF, argsV, "callputchar");
  // end
  //设置返回值
  builder->CreateRet(const_1);
  verifyFunction(*f);
  // Run the optimizer on the function.
  // theFPM->run(*f);
  //输出
  theModule->print(outs(), nullptr);

  return 0;
}