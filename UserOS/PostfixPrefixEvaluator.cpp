#include <iostream>
#include <stack>
#include <string>
using namespace std;

double valueAdder(double operand1,double operand2,char operator1)
{
    switch (operator1)
    {
        case '*':
            return operand1*operand2;
        case '/':
            return operand1/operand2;
        case '+':
            return operand1+operand2;
        case '-':
            return operand1-operand2;
        default:
            return INT32_MAX;
    }
}

double postfixEvaluator(string Expression){
    double value;
    double operand1,operand2;
    stack<double> s;
    for (int i = 0; i < Expression.length(); i++)
    {
        if (Expression[i] < '0')
        {
            operand2=s.top();
            s.pop();
            operand1=s.top();
            s.pop();

            value=valueAdder(operand1, operand2,Expression[i]);
            if(value==INT32_MAX){
                cout<<"Wrong Operator Used!!";
                exit(-1);
            }
            s.push(value);
        }
        else if (Expression[i] >= '0' and Expression[i] <= '9')
        {
            s.push((double)Expression[i]-48);
        }
        else{
            cout<<"Wrong symnol used";
            exit(-1);
        }
    }

    return s.top(); 
}

double prefixEvaluator(string Expression){
    double value;
    double operand1,operand2;
    stack<double> s;
    for (int i = Expression.length()-1; i >=0; i--)
    {
        if (Expression[i] < '0')
        {
            operand1=s.top();
            s.pop();
            operand2=s.top();
            s.pop();

            value=valueAdder(operand1, operand2,Expression[i]);
            if(value==INT32_MAX){
                cout<<"Wrong Operator Used!!";
                exit(-1);
            }
            s.push(value);
        }
        else if (Expression[i] >= '0' and Expression[i] <= '9')
        {
            s.push((double)Expression[i]-48);
        }
        else{
            cout<<"Wrong symnol used";
            exit(-1);
        }
    }

    return s.top(); 
}

int main(){
    string Expression;
    double value;
    int choice;

    cout<<"Press 1 For Postfix Evaluation "<<endl;
    cout<<"Press 2 For Prefix Evaluation "<<endl<<endl;
    cout<<"Enter You Choice : ";
    cin>>choice;

    if(choice==1){
        cout << "Enter the postfix expression : ";
        cin >> Expression;
        
        value=postfixEvaluator(Expression);
        cout << "Value of Expression is : " << value<<endl;
    }
    else if (choice==2){
        cout << "Enter the prefix expression : ";
        cin >> Expression;

        value=prefixEvaluator(Expression);
        cout << "Value of Expression is : " << value<<endl;
    }
    else{
        cout<<"Wrong Choice";
    }

    return 0;
}