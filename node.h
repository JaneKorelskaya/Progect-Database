#pragma once
#include "date.h" 
#include <string> 
#include <memory>  

using namespace std;

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

enum class LogicalOperation {
	Or,
	And,
};

struct Node {
	virtual bool Evaluate(const Date&  date, const string& event) const = 0;
};

class EmptyNode : public Node {
public: 
	bool Evaluate(const Date&  date, const string& event) const override; 
}; 

class DateComparisonNode : public Node {
public: 
	DateComparisonNode(Comparison new_cmp, const Date& new_date);
	bool Evaluate(const Date&  date, const string& event) const override;
private:
	const Comparison cmp; 
	const Date date_;
}; 

class EventComparisonNode : public Node {
public: 
	EventComparisonNode(Comparison new_cmp, const string& new_value);
	bool Evaluate(const Date&  date, const string& event) const override;
private: 
	const Comparison cmp;
	const string value;
}; 

class LogicalOperationNode : public Node {
public: 
	LogicalOperationNode(LogicalOperation new_op, shared_ptr<Node> new_left, shared_ptr<Node> new_right); 
	bool Evaluate(const Date&  date, const string& event) const override;
private: 
	LogicalOperation op;
	shared_ptr<Node> left, right;
}; 