#ifndef LIST_H_
#define LIST_H_

#include "ListOperations.h"

namespace AwesomeLibrary {

template<class Key, template<class> class Operations> class List;

namespace Private {

template<class Key, template<class> class Operations> class ListIterator: public Operations<Key> {
/*
 * Итератор для контейнера List
*/
public:
typedef typename Operations<Key>::Node Node;

	ListIterator (): node_(0) {}
	~ListIterator () {}

	ListIterator(const ListIterator& otherIter){
		node_ = otherIter.node_;
	}


	ListIterator& operator=(const ListIterator& otherIter){
		node_ = otherIter.node_;
		return *this;
	}

	bool operator==(const ListIterator& otherIter){
		return node_ == otherIter.node_;
	}

	bool operator!=(const ListIterator& otherIter){
		return node_ != otherIter.node_;
	}

	Key& operator*() const {
		return node_->item_;
	}//end of const T& operator*()

	/*
	 * Перевести итератор на следующий элемент списка
	*/
	ListIterator& operator++() {
		node_ = node_->next_;
		return *this;
	}//end of Iterator operator++()

	/*
	 * Перевести итератор на предыдущий элемент списка
	*/
	ListIterator& operator--() {
		node_= node_->previous_;
		return *this;
	}//end of Iterator& operator--()

private:
	friend class List<Key, Operations>;

	//этим конструктором может пользоваться только класс List
	ListIterator(Node* node): node_(node) {}

	Node* node_;
};//end of declaration class ListIterator

} /* Private */ 

template<class Key, template<class> class Operations>
class List: public Operations<Key> {
/*
 * Данный класс реализует структуру двусвязный список.
 * Класс принимает шаблонные параметры:
 * - Key - тип ключей, которые должны храниться в списке.
 * - Operations - класс, реализующий стратегию выполнения операций
 *   со списком в контексте узлов списка.
 * Класс Operations должен реализовывать следующие функции:
 * - void InsertNode(Node* newNode, Node*& head);
 * Вставить узел node в начало списка c вершиной head
 * - Node* FindNode(Node* node, Node* head) const;
 * найти узел с заданным ключем в списке с вершиной head
 * - Node* FindMinimum(Node* head) const;
 * Найти элемент списка, содержащий минимальный ключ
 * - Node* FindMaximum(Node* head) const;
 * Найти элемент списка, содержащий максимальный ключ
 * - Node* FindSuccessor(Node* node) const;
 * Найти элемент списка с ключем следующим по порядку за ключем заданного элемента
 * - Node* FindPredecessor(Node* node) const;
 * Найти элемент списка с ключем предыдущим по порядку за ключем заданного элемента
 * - void DeleteNode(Node* node, Node*& head);
*/

public:
#ifdef __ALGORITHM_TEST__
	friend class ListTest;
	FRIEND_TEST(ListTest, Destructor);
	FRIEND_TEST(ListTest, Insert);
#endif

	typedef Private::ListIterator<Key, Operations> Iterator; 

	List (): head_(0) {}
	~List ();

	/*
	функция
		void Insert(const Key& newKey);
	вставляет в список новый элемент, c заданным ключем
	Принимаемые параметры:
	newKey - элемент, который необходимо вставить в дерево
	*/
	void Insert(const Key& newKey);

	/*
	Функция
		Iterator Begin()
	Возвращает итератор, указывающий на голову спииска
	В случае если список пустой, возвращает итератор проинициализированный 0
	*/
	Iterator Begin() const;

	/*
	Функция
		Iterator End();
	Возвращает итератор, проинициализированный нулем
	*/
	Iterator End() const;

	/*
	Функция
		Iterator Minimum() const
	Возвращает итератор, указывающий на элемент с минимальным ключем
	В случае, если список пустой возвращает итератор, проинициализированный 0
	*/
	Iterator Minimum() const;

	/*
	Функция
		Iterator Maximum();
	Возвращает итератор, указывающий на элемент с максимальным ключем
	В случае, если список пустой возвращает итератор, проинициализированный 0
	*/
	Iterator Maximum() const;

	/*
	Функция
		Iterator Successor(const Key& key);
	Возвращает итератор на элемент списка с ключем, который следует
	по порядку за заданным.
	В случем если такой элемент не находится или дерево пустое, возвращает итератор,
	проинициализированный 0.
	Принимаемые параметры:
	- key - заданный ключ
	*/
	Iterator Successor(const Key& key) const;

	/*
	Функция
		Iterator Predecessor(const Key& key) const;
	возвращает итератор на элемент списка с ключем, который предшествует заданному.
	В случае если такой элемент не находится или дерево пустое, возвращает итератор,
	проинициализированный 0
	Принимаемые параметры:
	key - искомый ключ
	*/
	Iterator Predecessor(const Key& key) const;

	/*
	Функция
		void Delete(const Key& key);
	Удаляет элемент с заданным ключем из дерева.
	Принимаемые параметры:
	- key - удаляемый ключ
	*/
	void Delete(const Key& key);

	/*
	функция
		bool Find(const Key& key)
	возвращает true если обнаружит в дереве элемент item
	и false, если дерево пустое или элемент не найден
	*/
	Iterator Find(const Key& key) const;

	/*
	 * проверить пуст ли список
	 * Возвращаемое значение:
	 * true если список пуст, false -  в противном случае
	*/
	bool Empty() const;

private:
	typedef typename Operations<Key>::Node Node;

	Node* head_;
};//end of declaration class List

template<class Key, template<class> class Operations>
void List<Key, Operations>::Insert(const Key& newKey){
	Node* newNode = new Node(newKey);
	Operations<Key>::InsertNode(newNode, head_);
}

template<class Key, template<class> class Operations>
typename List<Key, Operations>::Iterator List<Key, Operations>::Begin() const {
	return Iterator(head_);
}

template<class Key, template<class> class Operations> typename List<Key, Operations>::Iterator List<Key, Operations>::End() const {
	return Iterator(0);
}//end of template<class Key, template<class> class Operations> typename List<Key, Operations>::Iterator List<Key, Operations>::End()

template<class Key, template<class> class Operations>
typename List<Key, Operations>::Iterator List<Key, Operations>::Minimum() const {
	if ( head_ == 0 ) {
		return Iterator(0);
	}//end of if 

	return Iterator(Operations<Key>::FindMinimum(head_));
}//end of template<class Key, template<class> class Operations> typename List<Key, Operations>::Iterator List<Key, Operations>::Minimum()

template<class Key, template<class> class Operations>
typename List<Key, Operations>::Iterator List<Key, Operations>::Maximum() const {
	if ( head_ == 0 ) {
		return Iterator(0);
	}//end of if 

	return Iterator(Operations<Key>::FindMaximum(head_));
}//end of template<class Key, template<class> class Operations> typename List<Key, Operations>::Iterator List<Key, Operations>::Maximum()

template<class Key, template<class> class Operations>
typename List<Key, Operations>::Iterator
List<Key, Operations>::Successor(const Key& key) const {
	if ( head_ == 0 ) {
		return Iterator(0);
	}//end of if 

	Node node(key);
	Node* fNode = Operations<Key>::FindNode(&node, head_);
	if ( fNode == 0 ) {
		return Iterator(0);
	}//end of if 

	return Iterator(Operations<Key>::FindSuccessor(fNode));
}//end of template<class Key, template<class> class Operations> typename List<Key, Operations>::Iterator List<Key, Operations>::Successor()

template<class Key, template<class> class Operations>
typename List<Key, Operations>::Iterator
List<Key, Operations>::Predecessor(const Key& key) const {
	if ( head_ == 0 ) {
		return Iterator(0);
	}//end of if 

	Node node(key);
	Node* fNode = Operations<Key>::FindNode(&node, head_);
	if ( fNode == 0 ) {
		return Iterator(0);
	}//end of if 

	return Iterator(Operations<Key>::FindPredecessor(fNode));
}//end of template<class Key, template<class> class Operations> typename List<Key, Operations>::Iterator List<Key, Operations>::Predecessor()

template<class Key, template <class> class Operations> void List<Key, Operations>::Delete(const Key& key) {
	if ( head_ == 0 ) {
		return;
	}//end of if 

	Node node(key);
	Node* fNode = Operations<Key>::FindNode(&node, head_);
	if ( fNode == 0 ) {
		return;
	}//end of if 

	Operations<Key>::DeleteNode(fNode, head_);
	delete fNode;
}//end of template<class Key, Oerations> void List<Key, Operations>::Delete()

template<class Key, template <class> class Operations>
typename List<Key, Operations>::Iterator
List<Key, Operations>::Find(const Key& key) const {
	if ( head_ == 0 ) {
		return Iterator(0);
	}//end of if 

	Node node(key);
	return Iterator(Operations<Key>::FindNode(&node, head_));
}//end of template<class Key, Operations> List<Key, Operations>::Find()

template<class Key, template<class> class Operations> bool List<Key, Operations>::Empty() const {
	return head_ == 0 ? true : false;
}//end of template<class Key, template<class> class Operations> bool List<Key, Operations>::Empty()

template<class Key, template<class> class Operations>
List<Key, Operations>::~List(){
#ifdef __ALGORITHM_TEST__
#define DestructorTest 1
	std::ofstream out("test_log.txt");
#else
#define DestructorTest 0
#endif

	Node* node = head_;
	Node* nextNode = 0;
	while ( node != 0 ) {
		nextNode = node->next_;
		if ( DestructorTest ) {
			out << "delete" << node->item_;
		}//end of if 

		delete node;
		node = 0;
		node = nextNode;
	}//end of while
}

} /* AwesomeLibrary */ 

#endif /* end of include guard: LIST_H_ */

