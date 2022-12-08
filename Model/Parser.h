#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <list>
#include <stack>
#include <string>

enum class P {
  ZERO,
  LOW,
  MIDDLE,
  HIGH,
  FUNCTION,
};

namespace dv {
class Parser {
 private:
  std::string input_ = "";
  std::stack<std::string> stack_;
  std::stack<std::string> tempStack_;
  std::string tempStr_ = "";
  P priority_ = P::ZERO;

 public:
  Parser() {}
  ~Parser() {}

  void parse(std::string s) {
    priority_ = P::ZERO;
    input_ = s;

    while (input_.length()) {
      char firstCh = input_.front();

      if (std::isdigit(firstCh) || firstCh == '.') tempStr_.push_back(firstCh);
      if (isOperator_(firstCh)) operatorParser_(firstCh);
      bracketsParser_(firstCh);
      if (firstCh == 'X') tempStr_.push_back(firstCh);
      if (isFunc_(firstCh)) funcParser_(firstCh);

      input_ = input_.erase(0, 1);
    }

    if (tempStr_ != "") {
      stack_.push(tempStr_);
      tempStr_ = "";
    }

    while (tempStack_.size()) {
      std::string oper = tempStack_.top();
      tempStack_.pop();
      stack_.push(oper);
    }

    std::cout << "Stack: ";
    while (stack_.size()) {
      std::string str = stack_.top();
      stack_.pop();
      std::cout << str << " ";
    }

    std::cout << std::endl;
  }

  std::stack<std::string> getStack() { return stack_; }

 private:
  void setPriority_(P p) { priority_ = p; }

  void operatorParser_(char firstCh) {
    P prior = checkPriority_(firstCh);
    P oldPrior = getPriority_();
    setPriority_(prior);

    if (tempStr_ != "") {
      stack_.push(tempStr_);
      tempStr_ = "";
    } else {
      stack_.push("0");
    }

    if (oldPrior < prior) {
      tempStack_.push(std::string(1, firstCh));
    } else {
      while (tempStack_.size()) {
        std::string oper = tempStack_.top();
        if (oper == "(") break;

        tempStack_.pop();
        stack_.push(oper);
      }
      tempStack_.push(std::string(1, firstCh));
    }
  }

  /*
  TO-DO:
    EXCEPTION FOR INVALID NUMBER OF BRACKETS
  */
  void bracketsParser_(char firstCh) {
    if (firstCh == '(') {
      tempStack_.push(std::string(1, firstCh));
    }

    if (firstCh == ')') {
      if (tempStr_ != "") {
        stack_.push(tempStr_);
        tempStr_ = "";
      }

      while (tempStack_.size()) {
        std::string oper = tempStack_.top();
        if (oper == "(") {
          tempStack_.pop();
          break;
        }

        tempStack_.pop();
        stack_.push(oper);
      }
    }
  }

  void funcParser_(char firstCh) {
    input_ = input_.erase(0, 1);
    char secCh = input_.front();
    std::cout << "First char: " << firstCh;
    std::cout << "Second char: " << std::endl;

    if (firstCh == 'l' && secCh == 'n') {
      tempStack_.push("ln");
    } else if (firstCh == 'a' || secCh == 'q') {
      if (secCh == 'q') tempStack_.push("q");
      if (secCh == 's') tempStack_.push("as");
      if (secCh == 'c') tempStack_.push("ac");
      if (secCh == 't') tempStack_.push("at");

      input_ = input_.erase(0, 2);
    } else {
      if (firstCh == 'c') tempStack_.push("c");
      if (firstCh == 't') tempStack_.push("t");
      if (firstCh == 's') tempStack_.push("s");
      if (firstCh == 'l') tempStack_.push("lg");

      input_ = input_.erase(0, 1);
    }
  }

  bool isOperator_(char ch) {
    for (char operCh : {'+', '-', '*', '/', '^', '%'}) {
      if (ch == operCh) return true;
    }
    return false;
  }

  bool isFunc_(char ch) {
    for (char operCh : {'l', 't', 'a', 's', 'c'}) {
      if (ch == operCh) return true;
    }
    return false;
  }

  P getPriority_() { return priority_; }

  P checkPriority_(char ch) {
    for (char operCh : {'%', '+', '-'}) {
      if (ch == operCh) return P::LOW;
    }

    for (char operCh : {'*', '/'}) {
      if (ch == operCh) return P::MIDDLE;
    }

    if (ch == '^') return P::HIGH;
    return P::FUNCTION;
  }
};

}  // namespace dv

#endif  // PARSER_H_