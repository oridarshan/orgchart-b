#include "OrgChart.hpp"
#include <queue>

namespace ariel
{

    OrgChart::~OrgChart()
    {
        for(Node *node : _data){
            delete(node);
        }
    }
    //TODO remove or reactivate
    OrgChart::Node* OrgChart::search_node(std::string name)
    {
        OrgChart::Node *pnode = nullptr;
        for(Node *node  : _data){
            if (node->name == name)
            {
                pnode = node;
            }
        }
        if(!pnode){
            throw "employer doesn't exist";}
            //TODO delete prints
        // std::cout << "searched for "<< name << "\nchildren:" << std::endl;
        return pnode;
    }

    OrgChart& OrgChart::add_root(std::string name)
    {
        if (_data.size() == 0){
            Node *root =new Node(name);
            root->newline = true;
            _data.push_back(root);
        }
        else{
            std::cout << "before root changed: "<< *this << std::endl;
            _data.at(0)->name = "name";
            std::cout << "after root changed: "<< *this << std::endl;
        }
        return *this;
    }
    
    OrgChart& OrgChart::add_sub(std::string father, std::string name)
    {
        //TODO delete prints
        std::cout << "before adding " << name << ":\n" << *this << std::endl;
        if (_data.empty())
        {
            std::cout << "can't add sub before root" << std::endl;
            throw "can't add sub before root";
        }
        // find father
        Node *predecessor = search_node(father);
        // construct new node
        Node *new_node =new Node(name);
        new_node->father = predecessor;
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
        
        _data = new_order;
        //TODO delete prints
        std::cout << "after adding " << name << ":\n" << *this << std::endl;
                
        return *this;
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