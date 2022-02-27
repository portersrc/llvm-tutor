#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "helloworld"

STATISTIC(HelloWorldCounter, "Counts number of functions greeted");

namespace {
  // HelloWorld - The first implementation, without getAnalysisUsage.
  struct HelloWorld : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    HelloWorld() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      ++HelloWorldCounter;
      errs() << "HelloWorld cporter: ";
      errs().write_escaped(F.getName()) << '\n';
      return false;
    }
  };
}

char HelloWorld::ID = 0;
static RegisterPass<HelloWorld> X("helloworld", "HelloWorld Pass");

namespace {
  // HelloWorld2 - The second implementation with getAnalysisUsage implemented.
  struct HelloWorld2 : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    HelloWorld2() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      ++HelloWorldCounter;
      errs() << "HelloWorld cporter: ";
      errs().write_escaped(F.getName()) << '\n';
      return false;
    }

    // We don't modify the program, so we preserve all analyses.
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
    }
  };
}

char HelloWorld2::ID = 0;
static RegisterPass<HelloWorld2>
Y("helloworld2", "HelloWorld Pass (with getAnalysisUsage implemented)");
