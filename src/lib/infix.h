#include <string>
#include <vector>
#include "token.h"
#include "parser.h"

class InfixParser {
  Node* root;
  static size_t index = 0;

  Node* createTree(Node* leftHandSide, int minPrecedence, std::vector<Token> tokens);
  int precedence(std::string op);
  Token& peak(std::vector<Token> tokens);
  Node* nextNode(std::vector<Token> tokens);

public:
  InfixParser(std::vector<Token> tokens);
  ~InfixParser();

  std::string toString();
  double calculate();
};
