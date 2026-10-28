#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// Represents a stack that can store up to 50 integers.

class stack{
    public:
        stack();
        void push(int value);
        int pop();
        void dup();
        void add();
        void sub();
        void mul();
        int peek()const;
        void print() const;
        int size()const;
    private:
        int data[50];
        int top;
};

// Represents 100 memory cells that store values from 0 to 255.
class memory{
    public:
        memory();
        void setValue(int address, int value);
        int getValue(int address)const;
        void print()const;
    private:
        unsigned char mem[100];

};

string getCommand(string line);
int getNumber(string text,bool& valid);
void HLT(const stack& s, const memory& m);
int JMP(int line,int count);
int JZ(stack& s, int line, int current,int count);
int JNP(stack& s, int line, int current,int count);
bool isAddress(string line);


int main(int argc, char* argv[])
{   
    string instructions[500];   
    int count = 0;
    string line;
    stack s1;
    memory m1;

    // Check command line arguments.
    if(argc != 3){
        cout<<"Invalid arguments!"<<endl;
        return 1;
    }

    int option=argv[2][0]-'0';

    if(option<0 || option>2 || argv[2][1]!='\0')
    {
        cout<<"Invalid option!"<<endl;
        return 1;
    }

    ifstream file(argv[1]);

    if(!file.is_open()){
        cout<<"File could not be opened!"<<endl;
    return 1;
    }

    // Read instructions from the file.
    while(getline(file,line))
    {
        if(count>=500)
        {
            cout<<"Error at line "<<count+1<<": Too many instructions!"<<endl;
         return 1;
        }

        instructions[count]=line;
        count++;
    }

    // Execute instructions one by one
    int i=0;

    while(i<count)
    {   
        int current=i;
        int nextline=i+1;
        bool halt=false;

        string command=getCommand(instructions[i]);

        // Check unknown instructions
        if(command!="PUSH" && command!="POP" && command!="PRN" &&
        command!="ADD" && command!="SUB" && command!="MUL" &&
        command!="DUP" && command!="INP" && command!="HLT" &&
        command!="JMP" && command!="JZ" && command!="JNP")
        {
            cout<<"Error at line "<<i+1<<": Unknown instruction!"<<endl;
            return 1;
        }       

        // Check syntax
        bool valid=true;
        int number=getNumber(instructions[i],valid);

        if(!valid)
        {
            cout<<"Error at line "<<i+1<<": Syntax error!"<<endl;
            return 1;
        }
        if(
            ((command=="POP" || command=="JZ" || command=="JNP" || command=="DUP") && s1.size()<1)
            ||
            (command=="PRN" && !isAddress(instructions[i])&& s1.size()<1)
            ||
            ((command=="ADD" || command=="SUB" || command=="MUL")&& s1.size()<2)
        )
        {
            cout<<"error at line "<<i+1<<": stack underflow"<<endl;
            return 1;
        }
        // Check stack overflow
        if(
            ((command=="PUSH" || command=="INP") && s1.size()>=50)
            || 
            (command=="DUP" && s1.size()>=50)
        )
        {
            cout<<"Error at line "<<i+1<<": Stack overflow!"<<endl;
            return 1;
        }
        // Check memory address
        if((command=="PUSH" || command=="POP" || command=="PRN")
            && isAddress(instructions[i]))
        {
            if(number<0 || number>=100)
            {
                cout<<"Error at line "<<i+1<<": Invalid memory address!"<<endl;
                return 1;
            }
        } 

        // Print instructions for options 1 and 2.
        if(option==1 || option==2)
        {
            cout<<instructions[current];

            if(command=="PRN" || command=="INP" || command=="HLT")
            {
                cout<<endl;
            }
            else
            {
                cout<<" - ";
                }
        }

         if(command=="PUSH")
        {
            if(isAddress(instructions[i]))
            {
                s1.push(m1.getValue(number));
            }
            else
            {
                s1.push(number);
            }
        }

        else if(command=="ADD")
        {
            s1.add();
        }

        else if(command=="PRN")
        {
           if(isAddress(instructions[i]))
            {
                cout<<m1.getValue(number)<<endl;
            }
            else
            {
                cout<<s1.peek()<<endl;
            }
        }

        else if(command=="POP")
        {
             if(isAddress(instructions[i]))
            {
                int value=s1.peek();

                if(value<0 || value>255)
                {
                    cout<<"Error at line "<<i+1<<": Invalid memory value!"<<endl;
                    return 1;
                }

                s1.pop();
                m1.setValue(number,value);
            }
            else
            {
                s1.pop();
            }
        }

        else if(command=="DUP")
        {
            s1.dup();
        }

         else if(command=="SUB")
        {
            s1.sub();
        }

         else if(command=="MUL")
        {
            s1.mul();
        }
        
        else if(command=="INP")
        {
            int value;
            cout<<"Enter an integer: ";
            if(cin >> value){
                s1.push(value);
            }else{
                cout<<"Error at line "<<i+1<<": Invalid input!"<<endl;
                return 1;
            }
            
        }
        
        else if(command=="HLT")
        {
            HLT(s1,m1);
            halt=true;
        }

        else if(command=="JMP")
        {
            nextline=JMP(number,count);
        }

        else if(command == "JZ")
        {   
            nextline=JZ(s1,number,i,count);
        }

        else if(command == "JNP")
        {
            nextline=JNP(s1,number,i,count);
        }
        if(nextline==-1)
        {
            cout<<"Error at line "<<i+1<<": Invalid jump address!"<<endl;
            return 1;
        }

        // Print the stack and memory after execution.
        if((option==1 || option==2) && !halt)
        {
            s1.print();

            if(option==2)
            {
                m1.print();
            }
        }

        if(halt){
            break;
        }
        i=nextline;
    }

    return 0;
}

// Initializes an empty stack.
stack::stack(){
    top=-1;
}

// Adds a value to the top of the stack
void stack::push(int value){
    top++;
    data[top]=value;
    
}

// Removes and returns the top value.
int stack::pop(){
    int temp;
    temp=data[top];
    top--;
    return temp;
    
}

// Returns the top value without removing it.
int stack:: peek()const{
     return data[top];
}

// Prints all values in the stack
void stack:: print()const{
    int i;
    
    cout<< "stack: [";
    for(i=0;i<=top;i++){

        cout<<data[i];
        if(i<top){
            cout<<", ";
        }
    }
    cout<<"]"<<endl;  

}

// Copies the top value of the stack.
void stack:: dup(){
    top++;
    data[top]=data[top-1];
}

// Adds the top two values of the stack.
void stack::add(){
    data[top-1]=data[top-1]+data[top];
    top--;
}

// Subtracts the top value from the second value.
void stack::sub(){
    data[top-1]=data[top-1]-data[top];
    top--;
}

// Multiplies the top two values of the stack.
void stack::mul(){
    data[top-1]=data[top-1]*data[top];
    top--;
}

// Initializes all memory cells to zero.
memory::memory(){
    for(int i=0;i<100;i++){
        mem[i]=0;
    }
}

// Stores a value at the given memory address.
void memory::setValue(int address, int value){
    mem[address]=value;
}

// Returns the value at the given memory address.
int memory::getValue(int address)const{
    
    return mem[address];
}
// Prints all memory cells.

void memory:: print()const{
    cout<<"memory: [";
    for(int i=0;i<100;i++){
        cout<<static_cast<int>(mem[i]);
        if(i<99){
            cout<<", ";
        }
    }
    cout<<"]"<<endl;
} 

// Prints the final stack and memory contents.
void HLT(const stack& s,const memory& m)
{
    s.print();
    m.print();
}

// Returns the target line for an unconditional jump.
int JMP(int line,int count)
{
    if(line<1 || line>count){
        return -1;
    }
    return line - 1;
}

// Jumps to the target line if the top value is zero.
int JZ(stack& s, int line, int current,int count)
{
    int value = s.pop();

    if(value == 0)
    {
        if(line<1 || line>count)
        {
            return -1;
        }

        return line-1;
    }

    return current+1;
}

// Jumps to the target line if the top value is zero or negative.
int JNP(stack& s, int line, int current,int count)
{
    int value = s.pop();

    if(value <= 0)
    {    
        if(line<1 || line>count)
        {
            return -1;
        }
        return line-1;
    }

    return current+1;
}

// Extracts the instruction name from a line.
string getCommand(string line)
{
    string command="";
    int i=0;

    while(i<line.length() && (line[i]==' ' || line[i]=='\t'))
    {
        i++;
    }

    while(i<line.length() && line[i]!=' ' &&
          line[i]!='\t' && line[i]!=';')
    {
        command+=line[i];
        i++;
    }

    return command;
}

// Reads an integer operand and checks its syntax.
int getNumber(string text, bool& valid)
{
    valid=true;

    int comment=text.find(';');
    if(comment>=0)
    {
        text=text.substr(0,comment);
    }

    string command=getCommand(text);
    int i=0;

    while(i<text.length() && (text[i]==' ' || text[i]=='\t'))
        i++;

    i+=command.length();

    while(i<text.length() && (text[i]==' ' || text[i]=='\t'))
        i++;

    // Commands without numbers
    if(command=="ADD" || command=="SUB" || command=="MUL" ||
       command=="DUP" || command=="INP" || command=="HLT")
    {
        if(i<text.length())
            valid=false;

        return 0;
    }

    // POP and PRN may have no operand
    if(i>=text.length())
    {
        if(command!="POP" && command!="PRN")
            valid=false;

        return 0;
    }

    bool address=false;

    if(text[i]=='#')
    {
        address=true;
        i++;
    }

    if((command=="POP" || command=="PRN") && !address)
        valid=false;

    if((command=="JMP" || command=="JZ" || command=="JNP") && address)
        valid=false;

    int sign=1;

    if(i<text.length() && text[i]=='-')
    {
        sign=-1;
        i++;
    }
    else if(i<text.length() && text[i]=='+')
    {
        i++;
    }

    if(i>=text.length() || text[i]<'0' || text[i]>'9')
    {
        valid=false;
        return 0;
    }

    long long value=0;

    while(i<text.length() && text[i]>='0' && text[i]<='9')
    {
        value=value*10+(text[i]-'0');

        if(value>2147483648LL)
        {
            valid=false;
            return 0;
        }

        i++;
    }

    while(i<text.length() && (text[i]==' ' || text[i]=='\t'))
        i++;

    if(i<text.length())
        valid=false;

    if(sign==1 && value>2147483647LL)
        valid=false;

    if(!valid)
        return 0;

    return static_cast<int>(value*sign);
}

// Checks if the instruction uses a memory address.
bool isAddress(string line)
{
    int i=0;

    while(i<line.length() && (line[i]==' ' || line[i]=='\t'))
        i++;

    while(i<line.length() && line[i]!=' ' &&
          line[i]!='\t' && line[i]!=';')
        i++;

    while(i<line.length() && (line[i]==' ' || line[i]=='\t'))
        i++;

    return i<line.length() && line[i]=='#';
}
// Returns the number of values in the stack.
int stack::size()const{
    return top+1;
}