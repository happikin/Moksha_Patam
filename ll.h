#include<iostream>
#define BEG 0
#define END 1
typedef unsigned int uint;

//----- cType is shorthand for custom type used in this generic DS library -----//

template<class cType>
struct node
{
    cType data;
    node<cType>* next;
};

template<class cType>
class List
{
    node<cType>* start;
    uint count;
    public:
        List(){start=NULL; count=0;}
        node<cType>* gotoEnd()
        {
            node<cType>* loc=start;
            while(loc->next!=NULL){loc=loc->next;}
            return loc;
        }
        node<cType>* goTo(uint index)
        {
            index-=2;
            node<cType>* loc=start;
            uint i = 0;
            while(i < index)
            {loc=loc->next;i++;}
            return loc;
        }
        node<cType>* end()
        {
            node<cType>*loc=start;
            while(loc->next!=NULL){loc=loc->next;}
            return loc;
        }
        uint getCount(){return count;}
        void insert(cType a,uint index = 0)
        {
            node<cType>*temp;
            node<cType>*loc;
            temp = new node<cType>;
            temp->data = a;
                        
            switch(index)
            {
                case 0: temp->next = start;
                        start = temp;
                        break;
                case 1: loc = gotoEnd();
                        loc->next=temp;
                        temp->next=NULL;
                        break;
                default:
                        std::cout<<"INVALID POSITION VALUE "<<std::endl;
            }
            count++;
        }
        void insertAt(cType value,uint index)
        {
            if(index>count+1 || index<0)
            {std::cout<<"EXEPTION : IndexOutOfRange \n";}
            else
            {
                node<cType>*temp,*loc = goTo(index);   //split the pointer declaration into two lines if error is shown
                temp = new node<cType>;
                temp->data = value;
                temp->next = loc->next;
                loc->next = temp;
                count++;
            }
        }
        void insertRange(List<cType> &l,uint index = 0)   //will insert one list into another list
        {
            if (index == 0)
            {
                node<cType>*ptr=l.end();
                ptr->next=start;
                start = l.start;
                count = l.count + count;
            }
            else if (index == 1)
            {
                end()->next=l.start;
                count = l.count + count;
            }
            else
            {
                std::cout<<"INVALID POSITION CODE"<<std::endl;
            }
        } 
        void insertRangeAt(List<cType> &l,uint index)
        {
            if(index>count+1 || index<0)
            {std::cout<<"EXEPTION : IndexOutOfRange \n";}
            else
            {
                node<cType>*lptr,*sptr;
                lptr=l.gotoEnd();
                sptr = this->goTo(index);
                lptr->next = sptr->next;
                sptr->next=l.start;
                count += l.count;
            }
        }
        node<cType>*findItem(cType item)   //wil return pointer to the node preceding the target node
        {
            node<cType>* loc = start;
            while(loc->next->data!=item)
            {
                loc=loc->next;
                if(loc->next==NULL)
                {
                    return NULL;
                    break;
                }
            }
            return loc;
        }
        void remove(cType item)
        {
            if(start->data==item && start!=NULL)
            {
                node<cType>*ptr = start;
                start=start->next;
                delete ptr;
                count--;
            }
            else
            {
                node<cType>*ptr,*loc = findItem(item);
                if(loc!=NULL)
                {
                    ptr=loc->next;
                    loc->next=ptr->next;
                    delete ptr;
                    count--;
                }
            }
        }
        void getridOf(cType item)
        {
            static node<cType>*sloc = start;
            if(sloc!=NULL)
            {
                if(start->data==item)
                {
                    node<cType>*ptr = start;
                    start=start->next;
                    sloc=start;
                    delete ptr;
                    count--;
                    getridOf(item);
                }
                else
                {
                    node<cType>*ptr,*loc = findItem(item);
                    if(loc!=NULL)
                    {
                        ptr=loc->next;
                        loc->next=ptr->next;
                        sloc=loc;
                        delete ptr;
                        count--;
                        getridOf(item);
                    }
                    else
                    {return;}   
                }
            }
            else
            {return;}
        }
        void removeAt(uint index)
        {
            if(index>count+1 || index<0)
            {std::cout<<"EXEPTION : IndexOutOfRange \n";}
            else
            {
                node<cType>*ptr,*loc = goTo(index);
                ptr=loc->next;
                loc->next=ptr->next;
                delete ptr;
                count--;
            }
        }
        void show()
        {
            node<cType>*loc;
            loc=start;
            std::cout<<"List Data :: ";
            while (loc!=NULL)
            {
                std::cout<<"["<<loc->data<<"]";
                loc=loc->next;
            }
            std::cout<<"\n";
        }
        ~List(){}
};