#include <iostream>


class tree_t
{
private:
    struct node_t {
        node_t * left;
        node_t * right;
        int value;
    };
private:
    node_t * root_;
public:
    node_t * root() {
        return root_;
    }
    tree_t() {
        root_ = nullptr;
    }

    void insert(int value) {
        if (root_ == nullptr) {
            root_ = new node_t;
            root_->left = nullptr;
            root_->right = nullptr;
            root_->value = value;
        }
        else {
			node_t * ptr = root_;
			while (ptr != nullptr) {
				if (value < ptr->value) {
					if (ptr->left == nullptr) {
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
			}
			//root_ = ptr;
        }
    }
    bool find(int value) const {
        bool res = false;
        if (root_ == nullptr) {
            return false;
        }
        if (root_->value == value) {
            return true;
        }
        node_t *ptr = root_;
        while (ptr != nullptr) {
            if (value < root_->value) {
                if (root_->left->value == value) {
                    return true;
                } else {
                    ptr = ptr->left;
                }
            }
            else if (value > root_->value) {
                    if (root_->right->value == value) {
                        return true;
                    } 
                    else 
                    {
                        ptr = ptr->right;
                    }
                }
            }
        return res;
    }
    void print(std::ostream & stream) const {

    }
};

int main() {

}
