#ifndef MODEL_H_
#define MODEL_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "../View/Button.h"
#include "Compute.h"
#include "Parser.h"

namespace dv {

class Model {
 private:
  int maxXSize_ = 18;
  bool isXCommed_ = false;
  bool isCommed_ = false;
  bool isOperandLast_ = false;

  std::string xValue_ = "";
  std::string displayValue_ = "0";
  std::string strToAdd_ = "";

  Parser* parser_ = nullptr;
  Compute* compute_ = nullptr;

 public:
  Model() {
    parser_ = new Parser();
    compute_ = new Compute();
  }
  ~Model() {
    delete parser_;
    delete compute_;
  }

  void handleButtonClick(T type, std::string& s) {
    char lastCh = displayValue_.back();
    strToAdd_ = s;

    switch (type) {
      case (T::Number):
        handleNumInput_(lastCh);
        break;

      case (T::Comma):
        handleCommaInput_(lastCh);
        break;

      case (T::Operand):
        handleOperandInput_(lastCh);
        break;

      case (T::OBracets):
        handleOBracetsInput_(lastCh);
        break;

      case (T::CBracets):
        handleCBracetsInput_(lastCh);
        break;

      case (T::X):
        handleXInput_(lastCh);
        break;

      case (T::Function):
        handleFuncInput_(lastCh);
        break;

      case (T::Equal):
        parser_->parse(displayValue_);
        compute_->setStack(parser_->getStack());
        compute_->doCompute();
        break;

      case (T::AC):
        displayValue_ = "0";
        isCommed_ = false;
        isOperandLast_ = false;
        break;

      default:
        break;
    }
  }

  void handleTextInput(sf::Uint32 code) {
    if (code > 47 && code < 58 && xValue_.length() < maxXSize_) {
      xValue_.push_back(code);

    } else if (code == 8 && xValue_.length() > 0) {
      if (xValue_.back() == '.') {
        isXCommed_ = false;
        maxXSize_--;
      }
      if (xValue_.length() > 0) xValue_.pop_back();

    } else if (code == '.' && !isXCommed_ && xValue_.length() < maxXSize_) {
      isXCommed_ = true;
      maxXSize_++;
      if (xValue_ == "") xValue_.push_back('0');
      xValue_.push_back('.');
    }
  }

  std::string getXValue() { return xValue_; }
  std::string getDisplayValue() { return displayValue_; }

 private:
  void handleNumInput_(char lastCh) {
    if (displayValue_ == "0") displayValue_.pop_back();

    if (lastCh == ')' || lastCh == 'X') {
      displayValue_.append("*");
    }

    displayValue_.append(strToAdd_);
    isOperandLast_ = false;
  }

  void handleCommaInput_(char lastCh) {
    if (isOperandLast_) {
      displayValue_.append("0");
    }

    if (lastCh == '(') {
      displayValue_.append("0");
    }

    if (lastCh == ')' || lastCh == 'X') {
      displayValue_.append("*");
      displayValue_.append("0");
    }

    if (!isCommed_) {
      displayValue_.append(strToAdd_);
      isCommed_ = !isCommed_;
      isOperandLast_ = false;
    }
  }

  void handleOperandInput_(char lastCh) {
    if (displayValue_ == "-") {
      displayValue_.pop_back();
      displayValue_.append("0");
      isOperandLast_ = false;
    }

    if (displayValue_ == "0" && strToAdd_ == "-") displayValue_.pop_back();
    if (lastCh == '(') displayValue_.append("0");

    if (lastCh == '.') {
      replaceLast_(strToAdd_);
      isOperandLast_ = !isOperandLast_;
      isCommed_ = false;

    } else if (!isOperandLast_) {
      displayValue_.append(strToAdd_);
      isOperandLast_ = !isOperandLast_;
      isCommed_ = false;
    } else {
      replaceLast_(strToAdd_);
    }
  }

  void handleOBracetsInput_(char lastCh) {
    isCommed_ = false;
    isOperandLast_ = false;

    if (displayValue_ == "0") {
      displayValue_ = strToAdd_;
    } else if (std::isdigit(lastCh) || lastCh == ')' || lastCh == 'X') {
      displayValue_.append("*");
      displayValue_.append(strToAdd_);

    } else if (lastCh == '.') {
      replaceLast_("*");
      displayValue_.append(strToAdd_);
    } else {
      displayValue_.append(strToAdd_);
    }
  }

  void handleCBracetsInput_(char lastCh) {
    isCommed_ = false;
    isOperandLast_ = false;

    if (displayValue_ == "0") {
    } else if (std::isdigit(lastCh) || lastCh == ')' || lastCh == 'X') {
      displayValue_.append(strToAdd_);
    } else if (lastCh == '(') {
      displayValue_.append("0");
      displayValue_.append(strToAdd_);
    } else {
      replaceLast_(strToAdd_);
    }
  }

  void handleXInput_(char lastCh) {
    if (displayValue_ == "0") {
      displayValue_ = strToAdd_;
    } else if (std::isdigit(lastCh) || lastCh == ')' || lastCh == 'X') {
      displayValue_.append("*");
      displayValue_.append(strToAdd_);

    } else if (lastCh == '.') {
      replaceLast_("*");
      displayValue_.append(strToAdd_);
    } else {
      displayValue_.append(strToAdd_);
    }

    isCommed_ = false;
    isOperandLast_ = false;
  }

  void handleFuncInput_(char lastCh) {
    if (displayValue_ == "0") {
      displayValue_ = strToAdd_;
    } else if (std::isdigit(lastCh) || lastCh == ')' || lastCh == 'X') {
      displayValue_.append("*");
      displayValue_.append(strToAdd_);

    } else if (lastCh == '.') {
      replaceLast_("*");
      displayValue_.append(strToAdd_);
    } else {
      displayValue_.append(strToAdd_);
    }

    displayValue_.append("(");

    isCommed_ = false;
    isOperandLast_ = false;
  }

  void replaceLast_(std::string s) {
    displayValue_.pop_back();
    displayValue_.append(s);
  }
};

}  // namespace dv

#endif  // MODEL_H_