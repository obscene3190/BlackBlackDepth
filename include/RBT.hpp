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
		bool equals(node_t * a, node_t *b) const {
        	if (a==nullptr && b==nullptr) return(true);
        	else if (a!=nullptr && b!=nullptr)
        	{
            		return(
                    		a->value == b->value &&
                   		equals(a->left, b->left) &&
                    		equals(a->right, b->right)
            		);
        }
        	else return(false);
    }

    ~RBT () {
	if( root_ != nullptr) {
		delete1(root_);
	}
     }
};
