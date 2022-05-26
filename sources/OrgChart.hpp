#pragma once
#include <string>
namespace ariel
{
    class OrgChart
    {
    private:

        struct Node // inner private class
        {
            std::string name;
            Node* father = nullptr;
            Node* son = nullptr;
            Node* brother = nullptr;
            Node(){} // constructor
        };

        Node root;
        //TODO search for a node
        Node& search_node(std::string name){return root;}
    public:
        OrgChart():root(){}
        // ~OrgChart();
        OrgChart& add_root(std::string name){root.name = "name"; return *this;}
        OrgChart& add_sub(std::string name, std::string father){return *this;}

        // level_order_iterator inner class
        class level_order_iterator
        {
        private:
            Node* current_node_p;
            std::string placeholder;
        public:
            level_order_iterator(Node* ptr = nullptr):current_node_p(ptr), placeholder("name"){}            
            // unary operators
            const std::string& operator*() const {return current_node_p->name;} 
            const std::string* operator->() const {return &(current_node_p->name);} 
            level_order_iterator& operator++(){return *this;} 
            // binary operators
            bool operator==(const level_order_iterator& itr) const{
                return false;
            }
            bool operator!=(const level_order_iterator& itr) const{
                return false;
            };
        
        };


        level_order_iterator begin(){return level_order_iterator(&root);}
        level_order_iterator end(){return level_order_iterator(&root);}
        level_order_iterator begin_level_order(){return level_order_iterator(&root);}
        level_order_iterator end_level_order(){return level_order_iterator(&root);}
        level_order_iterator begin_reverse_order(){return level_order_iterator(&root);}
        level_order_iterator end_reverse_order(){return level_order_iterator(&root);}
        //cover for mistake in Demo.cpp
        level_order_iterator reverse_order(){return level_order_iterator(&root);}
        level_order_iterator begin_preorder(){return level_order_iterator(&root);}
        level_order_iterator end_preorder(){return level_order_iterator(&root);}
        
        friend std::ostream& operator<< (std::ostream& output, const OrgChart& org){return output;}    
    };

} // namespace ariel
