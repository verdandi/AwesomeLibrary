#ifndef SEGMENT_TREE_H_
#define SEGMENT_TREE_H_

/*
разработал: Куксов П.А.
e-mail: aimed.fire@gmail.com
*/

#include "defines.h"

#include <vector>
#include <limits>
#include <climits>
#include <utility>

#include "SegmentTreeNode.h"
#include "SegmentTreeFunction.h"

namespace AwesomeLibrary {

template<class T, template<class> class Function, template<class> class TreeNode = SegmentTreeNode> class SegmentTree: public Function<T> {
/*
Класс реализует структуру данных, называемую деревом отрезков.
Физическим хранилищем для дерва избрана куча(массив).
Элементы дерева хранятся в следующем порядке: пусть i - родительский узел, тогда в 
2*i+1 хранится правый дочерний узел узла i, и в 2*i хранится левый дочерний узел
узла i. Все элементы исходных данных являются листьями дерева.
Для удобства дерево делается полным и узлы, в которых нет фактических данных, заполняются
некоторым фиктивным значением, которое никогда не может встретиться в данных.
Замечание: в данном случае узлы дерева располагаются с элемента с номером 1 в куче
*/
public:
#ifdef __ALGORITHM_TEST__
	friend class SegmentTreeTest;
	FRIEND_TEST(SegmentTreeTest, BuildTreeTest);
	FRIEND_TEST(SegmentTreeTest, SecondCallOfFunctionBuildTest);
#endif
	SegmentTree() {}
	explicit SegmentTree (const std::vector<T>& array);
	~SegmentTree () {}

	/*
	построить дерево отрезков по заданному массиву данных
	Принимаемые параметры:
	- array - массив данных
	Возвращаеоме значение:
	- успех либо неудача
	*/
	bool Build(const std::vector<T>& array);

	/*
	получить сумму элементов интервала [i,j]
	Принимаемые параметры:
	- i - левая граница интервала
	- j - правая граница интервала
	Возвращаемое значение:
	сумма элементов на указанном интервале
	*/
	T GetSum(size_t i, size_t j) const;

	/*
	изменить значение элемента в позиции pos
	Принимаемые параметры:
	- pos - позиция элемента в исходном массиве, значение которого
	нужно изменить( диапазон значений - от 0 до <размер массива> - 1)
	- newVal - новое значение элемента
	Возвращаемое значение:
	- true в случае успешно выполненной операции
	*/
	bool SetElem(size_t pos, const T& newVal);

	bool Empty();

	/*
	очистить дерево
	*/
	void Release();

private:
	typedef TreeNode<T> Node;

	size_t sizeOfData_;
	std::vector<Node> storage_;

	SegmentTree(const SegmentTree&);
	SegmentTree& operator=(const SegmentTree&);
};//end of declaration class SegmentTree


template<class T, template<class> class Function, template<class> class TreeNode>
SegmentTree<T, Function, TreeNode>::SegmentTree(const std::vector<T>& array) {
	Build(array);
}//end of template<class T, template<class> class Function, template<class> class TreeNode> SegmentTree::SegmentTree()

template<class T, template<class> class Function, template<class> class TreeNode>
bool SegmentTree<T, Function, TreeNode>::Build(const std::vector<T>& array) {
	if (array.empty()) {
		return false;
	}/* end of if */

	//проверяем не построено ли дерево раньше?
	if (!storage_.empty()) {
		return false;
	}/* end of if */

	//вычисляем ближайшую степень двойки большую заданного размера данных
	size_t powerOf2 = 1;
	sizeOfData_ = array.size();
	while(powerOf2 < sizeOfData_) {
		powerOf2 *= 2;
	}//end of while

	//вычисляем размер кучи для хранения дерева
	size_t sizeOfHeap = powerOf2 * 2;

	//инициализируем кучу
	storage_.resize(sizeOfHeap);

	//копируем данные в кучу начиная c середины кучи (это будут листья дерева)
	for (size_t i = 0, j = (sizeOfHeap / 2); i < sizeOfData_; ++i, ++j) {
		storage_[j] = Node(array[i]);
	}//end of for

	//строим дерево начиная с листьев
	for (size_t i = sizeOfHeap - 1; i > 1; i -= 2) {
		size_t rightChild = i;
		size_t leftChild = i-1;
		size_t parent = i/2;

		if (storage_[rightChild].IsValid() && storage_[leftChild].IsValid()) {
			Node result(Function<T>::Result(storage_[leftChild].GetVal(), storage_[rightChild].GetVal()));
			storage_[parent] = result;
			continue;
		}/* end of if */

		storage_[parent] = storage_[leftChild];
	}//end of for

	return true;
}//end of template<class T, template<class> class Function, template<class> class TreeNode> void SegmentTree<T, Function, TreeNode>::Build()

template<class T, template<class> class Function, template<class> class TreeNode>
T SegmentTree<T, Function, TreeNode>::GetSum(size_t i, size_t j) const {
	//находим позиции левой и правой границы подотрезка в исходном отрезке, заданного
	//индексами i и j (помним, что все элементы исходного массива являются в дереве
	//листовыми и расположены начиная с середины кучи)
	if (i > j) {
		int temp = i;
		i = j;
		j = temp;
	}/* end of if */

	if (j > (sizeOfData_-1)) {
		return int();
	}/* end of if */


	size_t leftBorder = i + (storage_.size() / 2);
	size_t rightBorder = j + (storage_.size() / 2);
	
	Node result;
	//пока границы поиска не пересеклись
	while(leftBorder <= rightBorder) {
		//если левая граница подотрезка указывает на элемент дерева, являющийся правым
		//дочерним элементом своего родителя, то данный элемент участвует в формировании
		//конечного результата
		if ((leftBorder & 1) && storage_[leftBorder].IsValid()) {
			if (result.IsValid()) {
				result.SetVal(Function<T>::Result(result.GetVal(), storage_[leftBorder].GetVal()));
			}/* end of if */
			else{
				result.SetVal(storage_[leftBorder].GetVal());
				result.SetValidation(true);
			}
		}/* end of if */

		//если правая граница подотрезка указывает на элемент дерева, являющийся 
		//левым дочерним элементом своего родителя, то данный элемент участвует в формировании
		//конечного результата
		if (!(rightBorder & 1) && storage_[rightBorder].IsValid()) {
			if (result.IsValid()) {
				result.SetVal(Function<T>::Result(result.GetVal(), storage_[rightBorder].GetVal()));
			}/* end of if */
			else{
				result.SetVal(storage_[rightBorder].GetVal());
				result.SetValidation(true);
			}
		}/* end of if */

		//смещаем границы подотрезка
		leftBorder = (leftBorder+1) / 2;
		rightBorder = (rightBorder-1) / 2;
	}// end of while

	return result.GetVal();
}//end of template<class T, template<class> class Function, template<class> class TreeNode> int SegmentTree<T, Function, TreeNode>::GetSum()

template<class T, template<class> class Function, template<class> class TreeNode>
bool SegmentTree<T, Function, TreeNode>::SetElem(size_t pos, const T& newVal) {
	if (pos > sizeOfData_ - 1) {
		return false;
	}/* end of if */

	size_t realPos = pos + storage_.size() / 2;
	storage_[realPos].SetVal(newVal);
	size_t parent = realPos / 2;
	while(parent >= 1) {
		storage_[parent].SetVal(Function<T>::Result(storage_[parent*2].GetVal(), storage_[parent*2+1].GetVal()));
		parent /= 2;
	}//end of while

	return true;
}//end of template<class T, template<class> class Function, template<class> class TreeNode> void SegmentTree<T, Function, TreeNode>::SetElem()

template<class T, template<class> class Function, template<class> class TreeNode>
bool SegmentTree<T, Function, TreeNode>::Empty() {
	return storage_.empty();
}//end of template<class T, template<class> class Function, template<class> class TreeNode> bool SegmentTree<T, Function, TreeNode>::Empty()

template<class T, template<class> class Function, template<class> class TreeNode>
void SegmentTree<T, Function, TreeNode>::Release() {
	storage_.clear();
}//end of template<class T, template<class> class Function, template<class> class TreeNode> void SegmentTree<T, Function, TreeNode>::Release()

} /* AwesomeLibrary */ 

#endif /* end of include guard: SEGMENT_TREE_H_ */

