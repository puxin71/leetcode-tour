#include <iostream>
#include <memory>
#include <string.h>
#include <vector>

/*
- release memory of linked list, not from the head
Because of the way the nodes are linked, when you manually delete or when the head node goes out of scope all the nodes in the list are recursively deleted! What do you think will happen if you create a large list of nodes, e.g. a few millions of nodes, and you delete the header or the header goes out of scope ? Because of the recursive destruction of the subsequent nodes there is a good chance that you will get a stack overflow error.

On Linux and macOS you can check the default stack size for an executable with:

ulimit -s

Due to the above, we don’t want the user to be able to manually erase the head of the list. We will create a List struct that will safely manage the list nodes creation and destruction

*/

struct Node {
    int data;
    std::unique_ptr<Node> next;
    // define Node constructor
    Node(int data) : data(data), next(nullptr) {}
    ~Node() {
        std::cout << "Destroying node with val: " << data << std::endl;
    }
};

std::ostream& operator<<(std::ostream &os, const std::vector<int> list);
std::vector<int> convertToIntList(std::string digits);

struct Singly {
    Singly() : head(nullptr) {}

    // function declaration must terminate with a comman
    friend std::ostream& operator<<(std::ostream &os, const Singly &list) {
        Node *head = list.head.get();
        // stringbuilder? https://www.fluentcpp.com/2017/12/19/build-strings-from-plain-string-up-to-boost-karma/
        // release memory by poping from the head
        while(head) {
            if (head->next) {
                os << head->data << ' ';
            } else {
                os << head->data;
            }
            head = head->next.get();
        }
        return os;
    }

    void push(int data) {
        auto node{std::make_unique<Node>(data)};
        if (!head) {
            head = std::move(node);
            return;
        }
        node->next = std::move(head);
        head = std::move(node);
    }

    void pushAll(const std::vector<int>& intList) {
        std::cout << "intList: " << intList << std::endl;
        for (int i : intList) {
            push(i);
        }  
    }

    int pop() {
        int data = head->data;
        head = std::move(head->next);
        return data;
    }
    ~Singly() {
        /*
        with a 10 millions nodes list, the program should have a normal termination without overflowing the stack:
        */
        while(head) {
            /*
            in other words, when you use std::move(x), you're allowing the compiler to cannibalize x. Thus if x has, say, its own buffer in memory - after std::move()ing the compiler can have another object own it instead
            */
            head = std::move(head->next); 
        }
    }
    
private:
    std::unique_ptr<Node> head;
};

std::ostream& operator<<(std::ostream &os, const std::vector<int> list) {
    for (int i : list) {
        os << i;
    }
    return os;
}

std::vector<int> convertToIntList(std::string digits) {
    // allocate the \'0' char for the char array
    char char_array[digits.length() + 1];
    strcpy(char_array, digits.c_str());
    std::vector<int> intList;
    for (int i = 0; i < digits.length(); i++) {
        // since the character '0' has the ASCII code of 48
        intList.push_back(char_array[i] - '0');
    }
    return intList;
}

int main() {
    std::cout << "Hello World!\n";
    auto intList = convertToIntList("1234");
    
    Singly reversedIntList;
    reversedIntList.pushAll(intList);
    std::cout << "reversedIntList: [" << reversedIntList << "]" << std::endl;
    
    Singly revertedIntList;
    for (int i = 0; i < intList.size(); i++) {
        revertedIntList.push(reversedIntList.pop());
    }
    std::cout << "revertedIntList: [" << revertedIntList << "]" << std::endl;
    std::cout << "hello world" << std::endl;
}