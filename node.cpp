#include "node.h"   
#include "date.h"
#include <string> 

using namespace std;  

bool EmptyNode::Evaluate(const Date&  date, const string& event) const { 
		return true;
	};

DateComparisonNode::DateComparisonNode(Comparison new_cmp, const Date& new_date) : cmp(new_cmp), date_(new_date) {};

bool DateComparisonNode::Evaluate(const Date&  date, const string& event) const {
	    if (cmp == Comparison::Less)
			return date < date_; 
		if (cmp == Comparison::Equal) {
			if (date_ == date)
				return true;
			else return false;
		} 
		if (cmp == Comparison::Greater)
			return date_ < date; 
		if (cmp == Comparison::GreaterOrEqual)
			return date_ <= date; 
		if (cmp == Comparison::LessOrEqual)
			return date <= date_; 
		if (cmp == Comparison::NotEqual) {
			if (date_ == date)
				return false;
			else return true;
		} 
		else return false;
	};

EventComparisonNode::EventComparisonNode(Comparison new_cmp, const string& new_value) : cmp(new_cmp), value(new_value) {};

bool EventComparisonNode::Evaluate(const Date&  date, const string& event) const {
		if (cmp == Comparison::Equal)
			return event == value; 
		if (cmp == Comparison::NotEqual) {
			if (event == value)
				return false;
			else return true;
		} 
		if (cmp == Comparison::Less) {
			return event < value;
		} 
		if (cmp == Comparison::Greater) {
			return value < event;
		} 
		if (cmp == Comparison::GreaterOrEqual) {
			return value <= event;
		} 
		if (cmp == Comparison::LessOrEqual) {
			return event <= value;
		}
		else return false;
};

LogicalOperationNode::LogicalOperationNode(LogicalOperation new_op, shared_ptr<Node> new_left, shared_ptr<Node> new_right)
		:op(new_op), left(new_left), right(new_right) {}; 

bool LogicalOperationNode::Evaluate(const Date&  date, const string& event) const {
		if (op == LogicalOperation::And) {
			if (left->Evaluate(date, event) == true && right->Evaluate(date, event) == true)
				return true;
			else return false;
	    } 
		else if (op == LogicalOperation::Or) {
			if (left->Evaluate(date, event) == true || right->Evaluate(date, event) == true)
				return true;
			else return false;
		} 
		else return false; //???
	};