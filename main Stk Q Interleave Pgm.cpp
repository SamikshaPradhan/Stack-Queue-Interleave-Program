/* 
   Program: Stk Q Interleave Pgm
   Description: Algorithm to Interleave the first half of the queue with second half
My Encoding Algorithm
Following are the steps used to encode a list of words:
1. Push the first half elements of queue to stack.
2. Enqueue back the stack elements.
3. Dequeue the first half elements of the queue and enqueue them back.
4. Again push the first half elements into the stack.
5. Interleave the elements of queue and stack.

I have an encode data file (a text file of words) that I need decoded.  The algorithm I used to encode the data
is shown above.  Your problem, to decode the encoded data.  The input will be a ‘…txt’ file of words which
consists of a list of words that have been encoded as described above.   Write a program to input the txt file
and print out the decoded results. Restrictions:   You must use aggregate Stack and Queue class. To solve this
problem, you can have ONE Queue and ONE Stack and only one of each.  The input data will be loaded into a Queue
to start with and from the Queue start your algorithm to decode the text.  (Decoding as you read in your data will
not be acceptable.) */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;
ifstream infile;
ofstream outfile;

const int CAPACITY = 215; // max no of elements that can be stored
typedef string ElementType;

class List
{
private:
    ElementType myAry[CAPACITY];
    int pos; // current index
    int used; // next index or the length of the list or the no. of elements or no. of used indices
public:
    List() // default constructor
    {
        used = 0;
        pos = 0;
        /*for(int i=0; i<used; i++)
        {
            myAry[i] = 0;
        }*/
    }
    List(List &l) // copy constructor: use it only after the first object is filled with data
    {
        pos = 0;
        used = l.size();
        if (used > 0)
        {
            for(int i=0; i<used; i++)
            {
                l.setPos(i);
                myAry[i] = l.getElement();
            }
        }
    }
    void display()
    {
        for(int i=0; i<used; i++)
         {
             cout << myAry[i] << " ";
             outfile << myAry[i] << " ";
         }
    }
    bool empty()
    {
        return (used == 0);
    }
    void first() // first makes current position at the beginning of the list
    {
        pos = 0;
    }
    void last() // last makes current position at the end of the list
    {
        if(used != 0) // otherwise, if no list, then pos = -1
        {
            pos = used - 1;
        }
    }
    void prev() // places current position at the previous element in the list
    {
        if((pos - 1) >= 0)
        {
            pos--;
        }
    }
    void next() // places current position at the next element in the list
    {
        if((pos + 1) < used) // if 5 elements, then used = 6
        {
            pos++;
        }
    }
    int getPos()
    {
        if(pos < used)
            return pos;
    }
    void setPos(int value)
    {
        if(pos>=0 && pos<used)
            pos = value;
    }
    void insertBefore(ElementType v)
    {
        if(used == 0)
        {
            myAry[0] = v;
            pos = 0;
            used = 1;
        }
        else if( (used+1) <= CAPACITY)
        {
            for(int i=used; i>pos; i--)
            {
            myAry[i] = myAry[i-1];
            }
            myAry[pos] = v;
            used++;
        }
        else if( (used+1) > CAPACITY)
        {
            cout << "Full capacity!!\n";
            outfile << "Full capacity!!\n";
        }
    }
    void insertAfter(ElementType v)
    {
        if(used == 0)
        {
            myAry[0] = v;
            pos = 0;
            used = 1;
        }
        else if( (used+1) <= CAPACITY)
        {
            for(int i=used; i>pos; i--)
            {
                myAry[i] = myAry[i-1];
            }
            myAry[pos+1] = v;
            pos++;
            used++;
        }
        else if( (used+1) > CAPACITY)
        {
            cout << "Full Capacity!!\n";
            outfile << "Full Capacity!!\n";
        }
    }
    ElementType getElement()
    {
        if(pos < used)
            return myAry[pos];
    }
    int size()
    {
        return used;
    }
    void replace(int v)
    {
        if(pos < used)
            myAry[pos] = v;
    }
    void erase()
    {
        if(used == 0)
        {
            return;
        }
        else if(used == 1 && pos == 0)
        {
            pos = 0;
            used = 0;
        }
        else if(pos == (used-1))
        {
            pos--;
            used--;
        }
        else if(pos < (used-1))
        {
            for(int i=pos; i<(used-1); i++)
            {
                myAry[i] = myAry[i+1];
            }
            used--;
        }
    }
    void clear()
    {
        used = 0;
        pos = 0;
    }
    friend ostream &operator <<(ostream &out, const List &l)
    {
        if (l.used == 0)
        {
            cout << "{ }";
            outfile << "{ }";
        }
        else
        {
        cout << "{ ";
        outfile << "{ ";
        for(int i=0; i<((l.used)-1); i++)
        {
            cout << l.myAry[i] << ", ";
            outfile << l.myAry[i] << ", ";
        }
        cout << l.myAry[(l.used)-1] << " }";
        outfile << l.myAry[(l.used)-1] << " }";
        }
    }
    friend bool operator ==(const List &a, const List &b)
    {
        if(a.used != b.used)
            return false;
        else
        {
            int count = 0;
            for(int i = 0; i<a.used; i++)
            {
                if(a.myAry[i] == b.myAry[i])
                    count++;
            }
            if(count == a.used)
                return true;
        }
    }
    friend bool operator !=(const List &a, const List &b)
    {
        if (a==b)
            return false;
        else
            return true;
    }
    friend void operator +=(List &a, List &b) // adds items of another list to a list
    {                        // no const because a needs to change
        if( (a.size() + b.size()) <= CAPACITY )
        {
            for(int i=0; i<b.size(); i++)
            {
                a.myAry[a.used] = b.myAry[i];
                (a.used)++;
            }
        }
    }
    friend List operator +(List &a, List &b) // returns a new list with the items of two lists
    {                                        // no const because += is used which doesn't take const
        if( (a.size() + b.size()) <= CAPACITY )
        {
            List answer;
            answer += a;
            answer += b;
            return answer;
        }
    }
    void operator =(List &b) // like copy constructor // does't need friend, but a = b works
    {                        // no const because not friend
        if (b.size() == 0)
            used =0;
        else if ((b.size()>0) && (b.size()<=CAPACITY))
        {
            used = b.used; // don't forget //
            for(int i=0; i<b.size(); i++)
            {
                b.setPos(i);
                myAry[i] = b.getElement();
            }
        }
    }
};
//////////////////////////////STACK CLASS//////////////////////////////////////////////////////////////////////////////////////////////////
class stack
{
private:
    List myStack;
public:
    void push(ElementType v)
    {
        myStack.last();
        myStack.insertAfter(v); // checks if full
    }
    void pop()
    {
        myStack.last();
        myStack.erase(); //checks if empty
    }
    bool empty()
    {
        return myStack.empty();
    }
    int size()
    {
        return myStack.size();
    }
    ElementType top()
    {
        myStack.last();
        return myStack.getElement();
    }
    void show() // display output
    {
        cout << myStack; // << is overloaded to display List so don't do output << or it will print twice
    }
    ElementType max()
    {
        if(myStack.size()>0 && myStack.size()<=CAPACITY)
        {
            myStack.setPos(0);
            ElementType m = myStack.getElement(); // data in index 0
            for(int i=0; i<myStack.size(); i++)
            {
                myStack.setPos(i);
                if (m < myStack.getElement())
                    m = myStack.getElement();
            }
            return m;
        }
    }
};
//////////////// QUEUE   /////////////////////////////////////////////////////////////////////////////////////////////////////
class Q
{
private:
    List myQ;
public:
    void enq(ElementType v)
    {
        if(myQ.size() <= CAPACITY)
        {
            myQ.last();
            myQ.insertAfter(v); // checks if full
        }
    }
    void deq()
    {
        if(myQ.size() != 0)
        {
            myQ.first();
            myQ.erase(); // checks if full
        }
    }
    void showQ() // display output
    {
        for(int i=0; i<myQ.size(); i++) // myAry is private to List class. so cannot use
        {
            myQ.setPos(i);
            cout << myQ.getElement() << " ";
            outfile << myQ.getElement() << " ";
        }
    }
    int size()
    {
        return myQ.size();
    }
    ElementType front()
    {
        myQ.first();
        return myQ.getElement();
    }

};


int main()
  {//infile.open("try.txt");
      infile.open("QStkinput.txt");
        if(!infile)
        {
            cout << "File not found." << endl;
            return 0;
        }
    outfile.open("Stk Q Interleave Output.txt");

    string x;
    Q q;
    stack s;
    int loop;
    while(infile >> x)
    {
        q.enq(x);
    }
//1. Interleave the elements in stack and queue
    loop = q.size()/2;
    for(int i=0; i<loop; i++)
    {
        s.push(q.front());
        q.deq();
        q.enq(q.front());
        q.deq();
    }
//2. Enqueue the stack elements into queue
    loop = s.size();
    for(int i=0; i<loop; i++)
    {
        q.enq(s.top());
        s.pop();
    }
//3. Dequeue the first half of the queue and enqueue them back t the queue
    loop = q.size()/2;
    for(int i=0; i<loop; i++)
    {
        q.enq(q.front());
        q.deq();
    }
//4. Push the first half of the queue into the stack
    loop = q.size()/2;
    for(int i=0; i<loop; i++)
    {
        s.push(q.front());
        q.deq();
    }
//5. Enqueue the stack elements into the queue
    loop = s.size();
    for(int i=0; i<loop; i++)
    {
        q.enq(s.top());
        s.pop();
    }
//6. Dequeue the first half elements of the queue and enqueue them back into the the queue
    loop = q.size()/2;
    for(int i=0; i<loop; i++)
    {
        q.enq(q.front());
        q.deq();
    }
    cout << "\n Decoded data:\n\n\t ";
    q.showQ();

    cout << "\n\n";
    infile.close();
	outfile.close();
	return 0;
  }
