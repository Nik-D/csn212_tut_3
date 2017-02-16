#include<iostream>
#include<queue>
#include<utility>
using namespace std;
 struct Node
{
     pair<int,int> i;
    int maxValue;
    Node *left, *right;
};
class iTree
{
    Node *root;
public:
    iTree()
    {
        root = NULL;
    }
     Node *createNewNode(pair<int,int>i)
    {
        Node *newNode = new Node;
        newNode->i = i;
        newNode->maxValue = i.second;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
     void insert_interval(Node *node,pair<int,int>i)
    {
        if(root==NULL)
        {
            root = createNewNode(i);
        }
        else
        {
            Node *point = node;
            if(point->maxValue<i.second)point->maxValue = i.second;
            if(i.first<point->i.first)
            {
                if(point->left==NULL)
                {
                   Node *newNode = createNewNode(i);
                    point->left = newNode;
                }
                else insert_interval(point->left,i);
            }
            else
            {
                if(point->right==NULL)
                {
                   Node *newNode = createNewNode(i);
                    point->right = newNode;
                }
               else insert_interval(point->right,i);
            }
        }
    }
    Node *get_root()
    {
        return root;
    }
     void tree_show()
    {
        queue <Node *> print_q;
        if(root!=NULL)print_q.push(root);
        else cout<<"Tree is empty"<<endl;
        while(!print_q.empty())
        {
            Node *node = print_q.front();
            print_q.pop();
            cout<<"i: "<<node->i.first<<", "<<node->i.second<<endl;
            cout<<"Max: "<<node->maxValue<<endl;
            if(node->left!=NULL)print_q.push(node->left);
            if(node->right!=NULL)print_q.push(node->right);
        }
    }
    bool checkOverlap(pair<int,int>i1, pair<int,int>i2)
    {
        if(i1.first<=i2.second && i2.first<=i1.second)
            return true;
        return false;
    }
    Node *search_over(Node *node,pair<int, int>i)
    {
       Node *match = NULL;
       if(node!=NULL)
        {
           if(checkOverlap((node->i),i))
                match = node;
            else
            {
              if(node->left!=NULL && node->left->maxValue>=i.first)
                    match = search_over(node->left,i);
                else match = search_over(node->right,i);
            }
        }
        return match;
    }
    Node *del_interval(Node *node,pair<int,int> i)
    {
        if(node==NULL)
            return node;
        if(i.first<node->i.first)
            node->left = del_interval(node->left,i);
        else if(i.first>=node->i.first&&(i!=node->i))
            node->right = del_interval(node->right,i);
        else if(i == node->i)
        {
            if(node->left==NULL)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if(node->right==NULL)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            Node *temp = node->right;
            while(temp->left!=NULL)
            {
                temp = temp->left;
            }

            node->i = temp->i;
            node->maxValue = temp->maxValue;
            node->right = del_interval(node->right,temp->i);
        }
        return node;
    }
    int fix_max_v(Node *node)
    {

        int maxValue=0;



        if(node==NULL)

            return maxValue;



        maxValue = max(node->i.second,max(fix_max_v(node->left),fix_max_v(node->right)));
        node->maxValue = maxValue;
        return maxValue;

    }

};

int main()
{
    iTree tree;
    while(true)
    {

        cout<<"1 to insert \n2 to print \n3 to search \n4 to delete \n5 to exit:\n";
        int opt; cin>>opt;
        if(opt ==1)

        {

            cout<<"Enter to insert\n";

            pair<int,int>i;

            cin>>i.first>>i.second;

            tree.insert_interval(tree.get_root(),i);

        }
        if(opt==2)

        {
            tree.tree_show();
        }

        if (opt ==3)
        {

            cout<<"Enter to Search: \n";

            pair<int,int>i;

            cin>>i.first>>i.second;

            Node *ret_node = tree.search_over(tree.get_root(),i);

            if(ret_node==NULL)

            {

                cout<<"not present"<<endl;

            }

            else

            {

                cout<<"Low: "<<ret_node->i.first<<", High: "<<ret_node->i.second<<endl;

            }

        }

        if (opt==4)

        {

            cout<<"Enter to Delete: \n";

            pair<int,int>i;

            cin>>i.first>>i.second;

            tree.del_interval(tree.get_root(),i);
            tree.fix_max_v(tree.get_root());
        }
        if(opt==5)
            break;
    }
}
