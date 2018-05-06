#include <iostream>
#include <sstream>
#include <string>
//#include <bits/stdc++.h>
using namespace std;
enum Color { RED, BLACK }; // enum это сгруппированный набор целочисленных констант. Называют это перечислением.

template <typename T>
class RBT {
private:
	struct node_t {
		node_t * left;
		node_t * right;
		node_t * parent;
		T value;
		int color;
	};
	node_t * root_;
public:
	RBT() {
		root_ = nullptr;
	}
    	//Вспомогательый метод для установки цвета элемента дерева
	void setColor(node_t *&node, int color) {
		if (node == nullptr)
			return;
		node->color = color;
	}
    	//Вспомогательый метод для плучения цвета дерева
	int getColor(node_t *&node) {
		if (node == nullptr)
			return BLACK;
		return node->color;
	}
    
    	//Функция поиска элемента в дереве, возвращающая переменную типа bool
	bool find(T value) const {
		if (root_ == nullptr) {
			return false;
		}
		node_t *ptr = root_;
		while (ptr != nullptr) {
			if (ptr->value == value) {
				return true;
			}
			else if (value > ptr->value) {
				ptr = ptr->right;
			}
			else if (value < ptr->value) {
				ptr = ptr->left;
			}
		}
		return false;
	}
    
    	//Вспомогательный метод поиска места и вставки узла, вызываемый рекурсивно
	node_t * helpinsert(node_t *&root, node_t *&ptr) {
		//Если корень нулевой, то просто возвращаем вставляемый элемент
		if (root == nullptr)
			return ptr;
        	//Если корень не пустой, то движемся по дереву в поисках[смысла жизни] подходящего места для нашего элемента по 
		//классической схеме, вызывая нашу функцию рекурсивно для продвижения по дереву
		if (ptr->value < root->value) {
			root->left = helpinsert(root->left, ptr);
			root->left->parent = root;
		}
		else if (ptr->value > root->value) {
			root->right = helpinsert(root->right, ptr);
			root->right->parent = root;
		}
		return root;
	}
    	//Вставка непосредственно значения
	void insert(T n) {
		if (!(find(n))) { //УСЛОВИЕ: Если элемент уже есть в дереве, то не вставляем его
			node_t *node = new node_t();
			node->value = n;
			root_ = helpinsert(root_, node);//Используем ранее написанную функцию для добавления узла
			fixInsert(node);//После вставки узла необходимо проверить, сохранилась ли BLACK DEPTH и соответствует ли дерево своим свойствам
		}
		else std::cout << "Sorry, this value has been added before" << std::endl;
	}
    
    	//Метод для регулировки дерева просле вставки в него элемента
	void fixInsert(node_t *&ptr) {
		node_t *parent = nullptr;
		node_t *grandparent = nullptr;
		//Трудности возникают только тогда, когда родитель вставляемого элемента тоже красный, ведь по свойству RBT у красного элемента может быть только черный потомок 
		while ((ptr != root_) && (getColor(ptr) == RED) && (getColor(ptr->parent) == RED)) {
			parent = ptr->parent;
			grandparent = parent->parent;
			if (parent == grandparent->left) {  //Если родитель нашего объекта левый ребенок, то назначаем "дядю" нашего вставляемого элемента
				node_t *uncle = grandparent->right;
				if (getColor(uncle) == RED) { //Если дядя красный, то просто делаем замену цветов:
					setColor(uncle, BLACK); //дядя и родитель становятся красными, а прародитель черным, таким образом сохраняется BLACK DEPTH
					setColor(parent, BLACK);
					setColor(grandparent, RED);
					ptr = grandparent;
				}
				else {//Если дядя черный, то необходимо будет сделать повороты:
					if (ptr == parent->right) { //если наш элемент это правый ребенок, то мы делаем поворот влево
						rotateLeft(parent);
						ptr = parent;
						parent = ptr->parent;
					}
					rotateRight(grandparent);
					swap(parent->color, grandparent->color);
					ptr = parent;
				}
			}
			else {//Если же родитель правый, то также рассматривается 2 случая относительно дяди, если он есть
				node_t *uncle = grandparent->left;
				if (getColor(uncle) == RED) {
					setColor(uncle, BLACK);
					setColor(parent, BLACK);
					setColor(grandparent, RED);
					ptr = grandparent;
				}
				else {
					if (ptr == parent->left) {
						rotateRight(parent);
						ptr = parent;
						parent = ptr->parent;
					}
					rotateLeft(grandparent);
					swap(parent->color, grandparent->color);
					ptr = parent;
				}
			}
		}
		setColor(root_, BLACK); //корень всегда должен быть черным
	}

	//Вспомогательный метод поиска места и удаления узла, вызываемый рекурсивно
	node_t* helpdelete(node_t *&root, int data) {
		//Если корень нулевой, то просто возвращаем вставляемый элемент
		if (root == nullptr)
			return root;
		//Для правого или левого рекурсиво вызываем наш метод
		if (data < root->data)
			return helpdelete(root->left, data);
		if (data > root->data)
			return helpdelete(root->right, data);
		//есди это последний узел, то тоже возвращаем его
		if (root->left == nullptr || root->right == nullptr)
			return root;
		//вводим доп переменную, если находим наш элемент
		node_t *temp = minValueNode(root->right);//это будет минимальное значение в правой ветке
		root->data = temp->data;//минимальное значение правого ряда назначаем в наш узел и рекурсивно вызываем функцию для проверки нужного узла
		return helpdelete(root->right, temp->data);
	}
	
	//Само удаление
	void deleteValue(int data) {
		node_t *node = helpdelete(root, data);
		fixDelete(node);
	}

	//нахождение минимального элемента
	node_t *minValueNode(node_t *&node) {
		node_t *ptr = node;
		while (ptr->left != nullptr)
			ptr = ptr->left;
		return ptr;
	}


	//Веселье после удаления
	void fixDelete(node_t *&node) {
		if (node == nullptr)
			return;

		if (node == root) {
			root = nullptr;
			return;
		}
		// Если родитель или один из его потомков красные
		if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
			node_t *child = (node->left != nullptr ? node->left : node->right);
			//если наш узел левый потомок
			if (node == node->parent->left) {
				node->parent->left = child;//то ставим на его место меньшего сына
				if (child != nullptr)
					child->parent = node->parent;
				setColor(child, BLACK);//и задаем ему черный цвет
				delete (node);
			}
			//если наш узел правый потомок
			else {
				node->parent->right = child;//то ставим также на его место меньшего сына
				if (child != nullptr)
					child->parent = node->parent;
				setColor(child, BLACK);//также окрашиваем в черный
				delete (node);
			}
		}
		//если наш узел черный или у него есть черный сын, то придется все передвигать:
		//для этого также вводим новый цвет DOUBLE_BLACK, который поможет нам лучше ориентироваться в дереве
		else {
			node_t *sibling = nullptr;
			node_t *parent = nullptr;
			node_t *ptr = node;
			setColor(ptr, DOUBLE_BLACK); // по факту это означает, что у нас нет красных сыновей и сам узел черный
			//создаем цикл, чтобы, если что-то сдвинется, то нигде выше не нарушились свойства дерева
			while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
				parent = ptr->parent;
				//если узел левый сын, то назначаем брата и ориентируемся на его цвет
				if (ptr == parent->left) {
					sibling = parent->right;
					//если брат красный
					if (getColor(sibling) == RED) {
						setColor(sibling, BLACK);//то делаем его черным, а
						setColor(parent, RED);//родителя красным
						rotateLeft(parent);//и поворачиваем
					}
					//если брат черный
					else {
						if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) { //смотрим, есть ли у него черные потомки
							setColor(sibling, RED);//делаем его красным
							if (getColor(parent) == RED)
								setColor(parent, BLACK);//если родитель красный, то делаем его черным, а черный, то делаем DOUBLE_BLACK
							else
								setColor(parent, DOUBLE_BLACK);
							ptr = parent;//переносим указатель
						}
						//если у брата один из потомков красный, то смотрим на них
						else {
							//если правый черный, то меняем цвета и поворачиваем вправо
							if (getColor(sibling->right) == BLACK) {
								setColor(sibling->left, BLACK);
								setColor(sibling, RED);
								rotateRight(sibling);
								sibling = parent->right;
							}
							//снова меняем цвета и еще раз поворачиваем
							setColor(sibling, parent->color);
							setColor(parent, BLACK);
							setColor(sibling->right, BLACK);
							rotateLeft(parent);
							break;
						}
					}
				}
				//Если правый сын, то также ориентируемся на брата
				else {
					sibling = parent->left;
					//если он красный, то просто меняем цвет и поворачваем
					if (getColor(sibling) == RED) {
						setColor(sibling, BLACK);
						setColor(parent, RED);
						rotateRight(parent);
					}
					//в ином случае также ориентируемся на сыновей
					else {
						if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
							setColor(sibling, RED);
							if (getColor(parent) == RED)
								setColor(parent, BLACK);
							else
								setColor(parent, DOUBLE_BLACK);
							ptr = parent;
						}
						else {
							if (getColor(sibling->left) == BLACK) {
								setColor(sibling->right, BLACK);
								setColor(sibling, RED);
								rotateLeft(sibling);
								sibling = parent->left;
							}
							setColor(sibling, parent->color);
							setColor(parent, BLACK);
							setColor(sibling->left, BLACK);
							rotateRight(parent);
							break;
						}
					}
				}
			}
			if (node == node->parent->left)
				node->parent->left = nullptr;
			else
				node->parent->right = nullptr;
			delete(node);
			setColor(root, BLACK);
		}
	}

	// Rotate a node x to the left    //
	//        x                y      //
	//       / \              / \     //
	//      a   y    --->    x   c    //
	//         / \          / \       //
	//        b   c        a   b      //
	void rotateLeft(node_t *&ptr) {
		node_t *right_child = ptr->right;
		ptr->right = right_child->left;

		if (ptr->right != nullptr)
			ptr->right->parent = ptr;

		right_child->parent = ptr->parent;

		if (ptr->parent == nullptr)
			root_ = right_child;
		else if (ptr == ptr->parent->left)
			ptr->parent->left = right_child;
		else
			ptr->parent->right = right_child;

		right_child->left = ptr;
		ptr->parent = right_child;
	}

	// Rotate a node x to the right   //
	//        x                y      //
	//       / \              / \     //
	//      y   c    --->    a   x    //
	//     / \                  / \   //
	//    a   b                b   c  //
	void rotateRight(node_t *&ptr) {
		node_t *left_child = ptr->left;
		ptr->left = left_child->right;

		if (ptr->left != nullptr)
			ptr->left->parent = ptr;

		left_child->parent = ptr->parent;

		if (ptr->parent == nullptr)
			root_ = left_child;
		else if (ptr == ptr->parent->left)
			ptr->parent->left = left_child;
		else
			ptr->parent->right = left_child;

		left_child->right = ptr;
		ptr->parent = left_child;
	}

	void print(std::ostream & stream, node_t * ptr, size_t i = 1) const {
		if (ptr) {
			if (ptr->right != nullptr) {
				i++;
				print(stream, ptr->right, i);
				i--;
			}
			for (size_t k = 0; k < i; k++) {
				stream << "--";
			}
			stream << ptr->value << std::endl;
			if (ptr->left != nullptr) {
				i++;
				print(stream, ptr->left, i);
				i--;
			}
		}
	}

	node_t * root() const {
		return root_;
	}
	//Вспомогательный метод для удаления и деструктор(как и для обычного дерева)
	void delete1(node_t * ptr) {
        	if (ptr != nullptr) {
			if (ptr->right) {
	    			delete1(ptr->right);
        			}
        		if (ptr->left) {
	    			delete1(ptr->left);
        			}
			delete ptr;
		}
	}

    ~RBT () {
	if( root_ != nullptr) {
		delete1(root_);
	}
     }
};
