#pragma once
#include <string>
#include <vector>
#include <iostream>
namespace ariel
{  
    class OrgChart
    {
    private:
        int _mod_count;
        // inner struct
        struct Node
        {
            std::string name;
            Node* father = nullptr;
            Node* next = nullptr;
            Node* prev = nullptr;
            std::vector<Node*> children;
            int level;
            bool mark = false;
            Node(std::string name):name(name){}
            };
        // vector stores data by level order
        std::vector<Node*> _data;
        // root and beginning of last level
        Node *root;
        Node *last_level;
        // Return next step in pre-order
        Node* next_pre_order(Node * curr_node){return curr_node;}
        // TODO search for a node, return reference
        Node* search_node(std::string name);
        // Node* search_node(std::string name)
        // {
        //     Node *pnode = nullptr;
        //     for(Node *node  : _data){
        //         if (node->name == name)
        //         {
        //             pnode = node;
        //         }
        //     }
        //     if(!pnode){
        //         throw "employer doesn't exist";}
        //     // std::cout << "searched for "<< name << "\nchildren:" << std::endl;
        //     return pnode;
        // }
    public:
        OrgChart():_mod_count(0),root(nullptr),last_level(nullptr){}
        ~OrgChart();
        OrgChart& add_root(std::string name);
        OrgChart& add_sub(std::string name, std::string father);


        // level_order_iterator inner class
        class level_order_iterator
        {
        private:
            Node* current_node_p;
        public:
            level_order_iterator(Node* ptr = nullptr):current_node_p(ptr){}
            // unary operators
            const std::string& operator*() const {return current_node_p->name;} 
            const std::string* operator->() const {return &(current_node_p->name);} 
            level_order_iterator& operator++(){
                current_node_p = current_node_p->next;
                return *this;} 
            // binary operators
            bool operator==(const level_order_iterator& itr) const{
                return current_node_p == itr.current_node_p;
                // return true;
            }
            bool operator!=(const level_order_iterator& itr) const{
                return !(*this == itr);
                // return true;
            };
        
        };
        
        
        // reverse_level_order_iterator inner class
        class reverse_level_order_iterator
        {
        private:
            Node* current_node_p;
        public:
            reverse_level_order_iterator(Node* ptr = nullptr):current_node_p(ptr){}
            // unary operators
            const std::string& operator*() const {return current_node_p->name;} 
            const std::string* operator->() const {return &(current_node_p->name);} 
            reverse_level_order_iterator& operator++();
            // binary operators
            bool operator==(const reverse_level_order_iterator& itr) const{
                return current_node_p == itr.current_node_p;
            }
            bool operator!=(const reverse_level_order_iterator& itr) const{
                return !(*this == itr);
            };
        
        };

        // preorder_iterator inner class
        class preorder_iterator
        {
        private:
            Node* current_node_p;
            // Return next step in pre-order
            Node* next_pre_order(Node * curr_node);
        public:
            preorder_iterator(Node* ptr = nullptr):current_node_p(ptr){}            
            // unary operators
            const std::string& operator*() const {return current_node_p->name;} 
            const std::string* operator->() const {return &(current_node_p->name);} 
            preorder_iterator& operator++();
            // binary operators
            bool operator==(const preorder_iterator& itr) const{
                return false;
            }
            bool operator!=(const preorder_iterator& itr) const{
                return false;
            };
        
        };


        level_order_iterator begin(){return level_order_iterator((root));}
        level_order_iterator end(){return level_order_iterator(nullptr);}
        level_order_iterator begin_level_order(){return begin();}
        level_order_iterator end_level_order(){return end();}
        reverse_level_order_iterator begin_reverse_order(){return reverse_level_order_iterator(last_level);}
        reverse_level_order_iterator end_reverse_order(){return nullptr;}
        //cover for mistake in Demo.cpp
        reverse_level_order_iterator reverse_order(){return end_reverse_order();}
        preorder_iterator begin_preorder(){return preorder_iterator((root));}
        preorder_iterator end_preorder(){return preorder_iterator(nullptr);}
        
        friend std::ostream& operator<< (std::ostream& output, const OrgChart& org);    
    };

} // namespace ariel
