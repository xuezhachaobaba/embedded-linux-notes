#include<cstdio>
#include<memory>

struct Node{
    // std::shared_ptr<Node> next;
    std::weak_ptr<Node> next;
    ~Node(){
        std::printf("~Node\n");
    }
};

int main(){

    auto a = std::make_shared<Node>();
    // auto b = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->next = b;
    b->next  = a;
    return 0;
}
//我猜是4次
// ./07

// =================================================================
// ==441891==ERROR: LeakSanitizer: detected memory leaks