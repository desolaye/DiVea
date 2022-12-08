
#include <stack>
#include <string>

class Compute {
 private:
  std::stack<std::string> stack_;
  std::stack<std::string> tempStack_;
  double res_ = 0;

 public:
  Compute(){};
  ~Compute(){};

  void doCompute() {

  }

  void setStack(std::stack<std::string> stack) { 
    while(stack.size()) {
      std::string str = stack.top();
      stack.pop();
      stack_.push(str);
    }
  }
};