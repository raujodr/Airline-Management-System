class Stack{
    queue<int> q1, q2;
    int curr_size;
    public:
    Stack(){
        curr_size = 0;
    }
    
    void push(int x){
        //Enqueue x to q2;
        q2.push(x);
        curr_size++;
        
        //One by one dequeue from q1 and enqueue to q2;
        while (!q1.empty()){
            q2.push(q1.front());
            q1.pop();
        }
        
        //Swap q1 and q2;
        queue<int> q = q1;
        q1 = q2;
        q2 = q;
    }
    
    void pop(){
        if (q1.empty())
            return;
        q1.pop();
        curr_size--;
    }
    
    
    int top(){
        if (q1.empty())
            return -1;
        return q1.front();
    }
    
    int size(){
        return curr_size;
    }
};

int main() {
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    
    cout << "current size: " << s.size() << "\n";
    cout << s.top() << "\n";
    s.pop();
    cout << s.top() << "\n";
    s.pop();
    cout << s.top() << "\n";
    cout << "current size: " << s.size() << "\n";
    
    return 0;
}
