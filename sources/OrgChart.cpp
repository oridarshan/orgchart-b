#include "OrgChart.hpp"
#include <queue>

namespace ariel
{
    OrgChart::OrgChart(const OrgChart &other):root(nullptr),last_level(nullptr)
    {
        add_root(other.root->name);
        for (size_t i = 1; i < other._data.size(); i++)
        {
            add_sub(other._data.at(i)->father->name, other._data.at(i)->name);
        }
        
    }
    OrgChart& OrgChart::operator=(const OrgChart& other) {
        if (this==&other){
            return *this;
        }
        //free old memory
        for(Node *node : _data){
            delete(node);
        }
        //add new data
        add_root(other.root->name);
        for (size_t i = 1; i < other._data.size(); i++)
        {
            add_sub(other._data.at(i)->father->name, other._data.at(i)->name);
        }
        return *this;
    }

    OrgChart::~OrgChart()
    {
        for(Node *node : _data){
            delete(node);
        }
    }
    //TODO remove or reactivate
    OrgChart::Node* OrgChart::search_node(const std::string &name)
    {
        OrgChart::Node *pnode = nullptr;
        for(Node *node  : _data){
            if (node->name == name)
            {
                pnode = node;
            }
        }
        if(!bool(pnode)){
            throw "employer doesn't exist";}
            //TODO delete prints
        // std::cout << "searched for "<< name << "\nchildren:" << std::endl;
        return pnode;
    }

    OrgChart& OrgChart::add_root(const std::string &name)
    {
        if (_data.empty()){
            Node *new_root =new Node(name);
            new_root->level = 0;
            _data.push_back(new_root);
            root = new_root;
            last_level = new_root;
        }
        else{
            _data.at(0)->name = name;
            root->name = name;
        }
        return *this;
    }
    
    OrgChart& OrgChart::add_sub(const std::string &father, const std::string &name)
    {
        //TODO delete prints
        // std::cout << "before adding " << name << ":\n" << *this << std::endl;
        if (_data.empty())
        {
            // std::cout << "can't add sub before root" << std::endl;
            throw "can't add sub before root";
        }
        // find father
        Node *predecessor = search_node(father);
        // construct new node
        Node *new_node =new Node(name);
        new_node->father = predecessor;
        new_node->level = predecessor->level+1;
        predecessor->children.push_back(new_node);
        // add node and update prev-next to all nodes
        // _data.push_back(new_node);
        std::vector<Node*> new_order;
        std::queue<Node*> temp;
        // chart cant be empty
        temp.push(_data.at(0));
        while (!temp.empty())
        {
            Node *curr_node = temp.front();
            for (Node *pchild : curr_node->children){
                temp.push(pchild);
            }
            new_order.push_back(curr_node);
            temp.pop();
        }
        //loop over new order and update pointers
        for (size_t i = 0; i < new_order.size(); i++)
        {
            if (i!=0)
            {
                new_order.at(i-1)->next = new_order.at(i);
                new_order.at(i)->prev = new_order.at(i-1);
            }
        }
        root = new_order.front();
        for (size_t i = new_order.size() - 1; i >= 1; i--)
        {
            if (new_order.at(i)->level != new_order.at(i-1)->level)
            {
                last_level = new_order.at(i);
                break;
            }
            if(i == 0){throw "only 1 level after adding sub";}
        }
        
        _data = new_order;
        //TODO delete prints
        // std::cout << "after adding " << name << ":\n" << *this << std::endl;
                
        return *this;
    }

    OrgChart::reverse_level_order_iterator& OrgChart::reverse_level_order_iterator::operator++(){
        if (bool(current_node_p->next) &&
             current_node_p->next->level == current_node_p->level)
        {
            current_node_p = current_node_p->next;
            return *this;
        }
        if (bool(current_node_p->father))
        {
            Node *next_rev = current_node_p->father;
            while (bool(next_rev->prev) &&
                 next_rev->prev->level== next_rev->level)
            {
                next_rev = next_rev->prev;
            }
            current_node_p = next_rev;
            return *this;
        }
        // we are at root
        current_node_p = nullptr;
        return *this;
        }
    
    OrgChart::preorder_iterator& OrgChart::preorder_iterator::operator++()
    {
        Node *next = next_pre_order(this->current_node_p);
        current_node_p = next;
        return *this;
    } 

    OrgChart::Node* OrgChart::preorder_iterator::next_pre_order(Node * curr_node){
        if(!bool(curr_node)){return nullptr;}
        //loop over chilren, return first unmarked (and mark it)
        for (Node *pchild : curr_node->children){
            if (!pchild->mark)
            {
                pchild->mark = true;
                return pchild;
            }
        }
        //visited all the tree (at root)
        if (!bool(curr_node->father))
        {
            //reset marks
            reset_marks(curr_node);
            return nullptr;
        }
        
        //already visited all sub-trees, find next child for father
        return next_pre_order(curr_node->father);
    }

    void OrgChart::preorder_iterator::reset_marks(Node *root){
        std::queue<Node*> temp;
        temp.push(root);
        while (!temp.empty())
        {
            Node *curr_node = temp.front();
            for (Node *pchild : curr_node->children){
                temp.push(pchild);
            }
            curr_node->mark = false;
            temp.pop();
        }
    }



    std::ostream& operator<< (std::ostream& output, const OrgChart& org)
    {
        std::string res;
        res += "Root->";
        for (const OrgChart::Node *node : org._data){
            res += node->name;
            res += "---";
        }
        res += "\n";
        return (output << res);
    }
}