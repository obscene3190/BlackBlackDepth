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
    tree_t() {
        root_->value = nullptr;
    }
    
    node_t root_() {
        return root_;
    }
    
    void insert(int value) {
        if (root_ = nullptr) {
            root_ = new node_t;
        }
        bool res = true;
        while(res == 1) {
            if (root_->value == nullptr) {
                root_->value  = value;
                res = false;
            }
            else if(value < root_->value) {
                root_ = root_->left;
            }
            else if(value > root_->value) {
                root_ = root_->right;
            }
        }
    }
    bool find(int value) const {
        bool res = false;
        while(value != root_->value) {
            if( value == root_->value ) {
                res = true;
                return res;
            }
            else if (value < root_->value) {
                root_ = root_->left;
            }
            else if (value > root_->value) {
                root_ = root_->right;
            }
        }
        return res;
    }
    void print(std::ostream & stream) const {

    }
};

int main() {

}
