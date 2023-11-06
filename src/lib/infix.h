#include <string>
#include <vector>
#include <memory>
#include "token.h"
#include "node.h"

struct Node {
  std::string value;
  TokenType returnType;

  Node(TokenType type = NUMBER) : returnType(type) {}
  virtual ~Node() {};
  virtual double getValue() = 0;
  virtual std::string toString() = 0;
};

struct NumNode : public Node {
  double getValue();
  std::string toString();
};

struct VarNode : public Node {
  double getValue();
  std::string toString();
};

struct BoolNode : public Node {
  BoolNode() : Node(BOOL) {}

  double getValue();
  std::string toString();
};

struct OpNode : public Node {
  Node* lhs;
  Node* rhs;

  OpNode(TokenType type = NUMBER) : Node(type) {}
  ~OpNode();
  virtual double getValue();
  std::string toString();
};

struct AssignNode : public OpNode {
  double getValue();
};

struct CompareNode : public OpNode {
  CompareNode() : OpNode(BOOL) {}

  double getValue();
};

struct LogicNode : public OpNode {
  LogicNode() : OpNode(BOOL) {}

  double getValue();
};

//______________________________________________________________________________

class InfixParser {
  Node* root;
  int index = -1;
  size_t parenNum = 0;
  bool updateVariables = true;
  std::vector<std::pair<std::string, Node*>> variableBuffer;

  Node* createTree(Node* leftHandSide, int minPrecedence, std::vector<Token> tokens);
  int precedence(std::string op);
  Token& peak(std::vector<Token> tokens);
  Node* nextNode(std::vector<Token> tokens);

public:
  InfixParser(std::vector<Token> tokens);
  ~InfixParser();

  std::string toString();
  std::string calculate();
};
