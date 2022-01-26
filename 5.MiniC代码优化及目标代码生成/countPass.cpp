#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;
namespace {
struct CountPass : public FunctionPass {
    static char ID;
    CountPass() : FunctionPass(ID) {}
    bool runOnFunction(Function& F) override {
        /********begin*********/
        outs().write_escaped(F.getName()) << ':';
        outs() << F.getBasicBlockList().size() << '\n';
        /******** end *********/
        return false;
    }
};
}  // namespace
char CountPass::ID = 0;
static RegisterPass<CountPass> X("CountPass", "Count Pass", false, false);