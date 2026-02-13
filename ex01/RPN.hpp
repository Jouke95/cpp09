#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN {
	private:
		bool isOperator(const std::string& input);
		bool isNumber(const std::string& input);
		int performOperation(int a, int b, const std::string& op);
		int popValue(std::stack<int>& stack);

	public:
		RPN();
		~RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		bool calculate(const std::string& input, int& result);
};

#endif
