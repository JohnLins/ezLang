#include <vector>
#include <iostream>
#include <string>
#include "lib/infix.h"
#include "lib/lexer.h"

void format(std::vector<Token>& tokens, std::string indent) {
  size_t ifCounter = 0;

  for (size_t i = 0; i < tokens.size(); ++i) {
    if (tokens[i].type == END) break;
    std::cout << indent;

    // expression and print case
    if (tokens[i].type != COMMAND || tokens[i].token == "print") {
      if (tokens[i].token == "print") {
        std::cout << "print ";
	++i;
      }

      int line = tokens[i].line;
      std::vector<Token> tempTokens;
      tempTokens.push_back(tokens[i]);

      //std::cout << "HERE " << tokens.size() << " " << i << std::endl;
      //if (tokens[1].token == "333") exit(0);

      //i + 1 != tokens.size() && tokens[i + 1].line == line
      while (true) {
        //std::cout << "Inside " << i + 1 << " " << tokens.size() << std::endl;
        //if (tokens.back().token == "333") exit(0);

        if (i + 1 == tokens.size()) break;
	if (tokens[i + 1].line != line) break;

        //std::cout << "In between " << std::endl;
        //if (tokens.back().token == "333") exit(0);

	tempTokens.push_back(tokens[i + 1]);
        ++i;
      }

      //std::cout << "after " << std::endl;
      //if (tokens.back().token == "333") exit(0);

      Token tempToken = Token{0, 0, "END", END};

      //std::cout << "token before, push back after" << std::endl;
      //if (tokens.back().token == "333") exit(0);

      tempTokens.push_back(tempToken);

      //std::cout << "__________top" << std::endl;
      //for (Token token : tempTokens) {
      //  std::cout << token.token << " " << token.type << " " << token.line << " " << token.column << std::endl;
      //}
      //std::cout << "__________bottom" << std::endl;
      //std::cout << "THERE " << std::endl;
      //if (tempTokens.back().token == "333") exit(0);

      InfixParser parser = InfixParser(tempTokens);
      std::cout << parser.toString() << std::endl;
    }

    // while and if case
    else if (tokens[i].token != "else" && tokens[i].token != "else if") {
      if (tokens[i].token == "if") {
        if (ifCounter != 0) {
	  //TODO
	}
	
        std::cout << "if ";
        ++ifCounter;
      }	

      else std::cout << "while ";

      ++i;
      std::vector<Token> condition;

      while (tokens[i].token != "{") {
        condition.push_back(tokens[i]);
	++i;
      }
      condition.push_back(Token{0, 0, "END", END});

      /*
      for (Token token : condition) {
        std::cout << token.token << " " << token.type << std::endl;
      }
      */

      ++i;
      InfixParser parser = InfixParser(condition);
      std::cout << parser.toString() << " {" << std::endl;

      size_t numCurly = 1;
      std::vector<Token> body;

      while (true) {
	if (tokens[i].token == "{") ++numCurly;
	else if (tokens[i].token == "}") --numCurly;

        if (numCurly == 0) break;
        body.push_back(tokens[i]);
	++i;
      }

      format(body, indent + "    ");
      std::cout << indent << "}" << std::endl;
    }

    // else case
    else if (tokens[i].token == "else" || tokens[i].token == "else if") {
      if (ifCounter == 0) {
        //TODO
      }

      --ifCounter;
      std::cout << "else {" << std::endl;

      bool isElseIf = (tokens[i].token == "else if" ? true : false);
      size_t numCurly = 1;
      std::vector<Token> body;

      ++i;

      if (isElseIf) {
        body.push_back(Token{0, 0, "if", COMMAND});

	while (tokens[i].token != "{") {
	  body.push_back(tokens[i]);
	  ++i;
	}

	body.push_back(tokens[i]);
      }

      ++i;

      while (true) {
        if (tokens[i].token == "{") ++numCurly;
        else if (tokens[i].token == "}") --numCurly;

        if (numCurly == 0) {
	  if (!isElseIf || i == tokens.size() - 1 || (tokens[i + 1].token != "else" && tokens[i + 1].token != "else if")) break;

	  while (tokens[i + 1].token != "{") {
            body.push_back(tokens[i]);
	    ++i;
	  }
	}

        body.push_back(tokens[i]);
        ++i;
      }

      if (isElseIf) body.push_back(tokens[i]);

      //std::cout << "__________top else" << std::endl;
      //for (Token token : body) {
	//std::cout << token.token << " " << token.type << std::endl;
      //}
      //std::cout << "__________bottom else" << std::endl;

      format(body, indent + "    ");
      std::cout << indent << "}" << std::endl;
    }

    else {
      std::cout << "this formatting error should never happen" << std::endl;
      exit(1);
    }
  }
}

int main() {
    std::vector<Token> tokens;

    try {
      Lexer lexer = Lexer();
      tokens = lexer.lexer();
    }
    catch (const std::exception& e) {
      std::cout << e.what() << std::endl;
      exit(1);
    }

    try {
      format(tokens, "");
    }
    catch (const std::exception& e) {
      std::cout << e.what() << std::endl;
      exit(2);
    }

    return 0;
}
