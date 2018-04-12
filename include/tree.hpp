#include <iostream>
#include <sstream>
#include <string>

template <typename T> class tree_t
{
private:
    struct node_t {
        node_t * left;
        node_t * right;
        T value;
    };
private:
    node_t * root_;
public:
    
    tree_t() {
        root_ = nullptr;
    }

    void insert(T value) {
        if (root_ == nullptr) {
            root_ = new node_t;
            root_->value = value;
            root_->left = nullptr;
            root_->right = nullptr;
        }
        else {
			node_t * ptr = root_;
			while (ptr != nullptr) {
				if (value < ptr->value) {
					if (ptr->left == nullptr) {
						ptr->left = new node_t;
						ptr = ptr->left;
						ptr->value = value;
						ptr->left = nullptr;
						ptr->right = nullptr;
						return;
					}
					else {
						ptr = ptr->left;
					}
				}
				else if (value >= ptr->value) {
					if (ptr->right == nullptr) {
						ptr->right = new node_t;
						ptr = ptr->right;
						ptr->value = value;
						ptr->left = nullptr;
						ptr->right = nullptr;
						return;
					}
					else {
						ptr = ptr->right;
					}
				}
				else {
					ptr->value = value;
					ptr->left = nullptr;
					ptr->right = nullptr;
					return;
				}
			}
        }
    }

    bool find(T value) const {
        if (root_ == nullptr) {
            return false;
        }
        node_t *ptr = root_;
        while (ptr != nullptr) {
            if (ptr->value == value) {
            	return true;
            }
	    else if ( value > ptr->value) {
		ptr = ptr->right;
	    }
	    else if ( value < ptr->value) {
		ptr = ptr->left;
	    }
	}
        return false;
    }
    
    void print(std::ostream & stream ,  node_t * ptr, size_t i = 1) const {
	if (ptr) {
		if (ptr->right != nullptr) {
			i++;
			print(stream ,ptr->right, i);
			i--;
		}
		for (size_t k = 0; k < i; k++) {
			stream << "--";
		}
		stream << ptr->value << std::endl;
	 	if (ptr->left != nullptr) {
			i++;
			print(stream ,ptr->left, i);
			i--;
			}
		}
    }
    
    node_t * root() const {
        return root_;
    }
    
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

    bool operator==(tree_t &other) const
    {
        node_t * a, * b;
        a = root_;
        b = other.root();
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
    ~tree_t () {
	if( root_ != nullptr) {
		delete1(root_);
	}
     }
};

template <typename T>
bool read(tree_t<T> & tree, std::istream & stream) {
    char op;
    T value;
    if( stream >> op && ( op == '=' || op == '+' || op == '?' || op == 'q')) {
	    if (op == 'q') {
	        return false;
    	}
    	else if (op == '=') {
	    tree.print(std::cout, tree.root(), 1);
	    }
    	else if ((op == '+' || op == '?') && stream >> value) {
	    if (op == '+') {
		tree.insert(value);
	    }
	else if (op == '?') {
		std::cout << tree.find(value) << std::endl;
	     }
    	}
     }
     return true;
}
