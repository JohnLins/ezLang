#pragma once
#include <variant>
#include <memory>
#include <ostream>
#include <vector>
#include "token.h"
#include <sstream>
//#include "scrypt.h"

struct Value;
extern Value parseBlock(std::vector<Token>& tokens, std::map<std::string, Value> variables);
class Function {
    public:
        std::vector<Token> arguments;
        std::vector<Token> block;

        Value getValue(std::vector<Value> argVals, std::map<std::string, Value> variables);
};

//class Function;
struct Value : public std::variant<double, 
                                    bool,
				   std::shared_ptr<Function>,
				    std::shared_ptr<std::vector<Value>>
                                    > { //std::nullptr_t
    using variant::variant;

    
};

using Array = std::shared_ptr<std::vector<Value>>;
//using Func = std::shared_ptr<Function>;

std::ostream& operator << (std::ostream& stream, const Value& value);

bool operator==(const Value& lhs, const Value& rhs);
bool operator!=(const Value& lhs, const Value& rhs);


/*extern Value parseBlock(std::vector<Token>& tokens, std::map<std::string, Value> variables);
class Function {
    public:
        std::vector<Token> arguments;
        std::vector<Token> block;

//        Value getValue(std::vector<Value> argVals, std::map<std::string, Value> variables);
};*/
