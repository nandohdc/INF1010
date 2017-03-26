/*
Nome: Fernando Homem da Costa
Matrícula: 1211971
*/


#include "mod1_lista1.h"
#include <iostream>

List::List()
	: first(nullptr)
	, last(nullptr)
{
}


List::List(const List& list)
{
    std::cout << "Object is being copied" << std::endl;
    if(list.first == nullptr && list.last == nullptr){
        this->first = nullptr;
        this->last = nullptr;
    }

    Node* cur = list.first;

    while(cur != nullptr){
        Node* node = new Node();
        node->val = cur->val;
        node->next = nullptr;
        node->prev = this->last;

        if(!this->first){
            this->first = node;
            this->last = node;
        } else{
            this->last->next  = node;
            this->last = node;
        }
        cur = cur->next;
    }
}


List::~List()
{
    std::cout << "Object is being deleted" << std::endl;
    while(this->first->next != nullptr){
        Node* temp = this->first;
        this->first = this->first->next;
        delete(temp);
    }
}


void List::push_back(const int& element)
{
    Node* node = new Node();
    node->val = element;
    node->next = nullptr;
    node->prev = this->last;

    if(!this->first){
        this->first = node;
        this->last = node;
    } else{
        this->last->next  = node;
        this->last = node;
    }

}


void List::push_front(const int& element)
{
    Node* node  =  new Node();
    node->val = element;
    node->next = this->first;
    node->prev = nullptr;

    if(!this->first){
        this->first = node;
        this->last = node;
    } else{
        this->first->prev = node;
        this->first = node;
    }
}


void List::pop_back()
{
   Node* temp = this->last;
    
    this->last = temp->prev;
    this->last->next = nullptr;
    
    std::cout<<"Element Deleted.\n"<<std::endl;
    
    temp->prev = nullptr;
   delete(temp);//Liberando o pointer
}


void List::pop_front()
{
    Node* temp = this->first;
    
    this->first = temp->next;
    this->first->prev = nullptr;
    
    std::cout<<"Element Deleted.\n"<<std::endl;

	temp->next = nullptr;
    delete(temp);//Liberando o pointer
}


unsigned int List::size()
{
    unsigned int lSize = 0;
    struct Node* temp = nullptr;
    if(this->first == nullptr){
        return lSize;
    } else{
        temp = this->first;
        while(temp != nullptr){
            temp = temp->next;
            lSize++;
        }
        return lSize;
    }
    
}


void List::remove(const int& element)
{
    std::cout << "Object is being removed" << std::endl;

    if(this->first == nullptr)
        return;

	if (this->first->val == element) {
		Node* temp = this->first;
		this->first = temp->next;
		this->first->prev = nullptr;
		temp->next = nullptr;
	}

	if (this->last->val == element) {
		Node* temp = this->last;
		this->last = temp->prev;
		this->last->next = nullptr;
		temp->prev = nullptr;
	}

    Node* temp = this->first;
    while(temp->next != nullptr){
        if(temp->val == element){
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            break;
        } else{
            temp = temp->next;
        }
    }
     return;
}


void List::print()
{
    if(this->first == nullptr){
        std::cout<< "The list is empty.\n"<<std::endl;
    } else {
        Node* temp = this->first;
        while(temp != nullptr){
            std::cout<< temp->val << ",";
            temp = temp->next;
        }
		std::cout << std::endl;
    }
}

void List::sort(){

    if(this->size() <= 1){
        std::cout << "Lista possui 1 ou menos elementos."<< std::endl;
        return;
    }
	for (Node* cur = this->first; cur->next != nullptr; cur = cur->next) {
        for(Node* temp = cur->next; temp !=  nullptr; temp = temp->next){
            if(temp->val < cur->val){
				int temp2 = cur->val;
				cur->val = temp->val;
				temp->val = temp2;
            }
        }

    }
}
