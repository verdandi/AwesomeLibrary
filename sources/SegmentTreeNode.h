#ifndef SEGMENT_TREE_NODE_H_
#define SEGMENT_TREE_NODE_H_

namespace AwesomeLibrary {

template<class T> class SegmentTreeNode {
/*
узел дерева отрезков
*/
public:
	SegmentTreeNode (): val_(T()), isValid_(false) {}
	explicit SegmentTreeNode(const T& val): val_(val), isValid_(true) {}
	SegmentTreeNode(const SegmentTreeNode& otherNode){
		val_ = otherNode.val_;
		isValid_ = otherNode.isValid_;
	}

	~SegmentTreeNode () {}

	SegmentTreeNode& operator=(const SegmentTreeNode& otherNode){
		val_ = otherNode.val_;
		isValid_ = otherNode.isValid_;
		return *this;
	}

	bool operator==(const SegmentTreeNode& otherNode) const {
		return (val_ == otherNode.val_) && (isValid_ == otherNode.isValid_);
	}//end of bool operator==()

	bool operator!=(const SegmentTreeNode& otherNode) const {
		return (val_ != otherNode.val_) || (isValid_ != otherNode.isValid_);
	}//end of bool operator==()

	SegmentTreeNode& operator+=(const SegmentTreeNode& rhs){
		val_ += rhs.val_;
		return *this;
	}

	const T& GetVal() const {
		return val_;
	}//end of int GetVal()

	void SetVal(const T& newVal) {
		val_ = newVal;
	}//end of void SetVal()

	bool IsValid() const {
		return isValid_;
	}//end of bool GetValidation()

	void SetValidation(bool newValidation) {
		isValid_ = newValidation;
	}//end of void SetValidation()

private:
	T val_;
	bool isValid_;
};//end of declaration class SegmentTreeNode

} /* AwesomeLibrary */ 

#endif /* end of include guard: SEGMENT_TREE_NODE_H_ */
