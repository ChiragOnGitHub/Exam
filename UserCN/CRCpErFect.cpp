#include <iostream>
#include <math.h>
using namespace std;


int numOfDigit(long long int bin){
    int count=0;
    while (bin!=0)
    {
        bin/=10;
        count++;
    }
    return count;
}

long long int decToBin(int number){
    long long int bin=0;
    long long int factor=1;
    while (number!=0)
    {
        bin+=factor*(number%2);
        number/=2;
        factor*=10;
    }
    return bin;
}

void codeGenerator(int generator, int message){
    int bitsInGenerator,bitsInFrame;
    long long int frame,remainder,CRCcode;
    int temp,result;

    bitsInGenerator=numOfDigit(decToBin(generator));
    frame=message*pow(2,bitsInGenerator-1);
    bitsInFrame=numOfDigit(decToBin(frame));

    for (int i=bitsInGenerator; i<=bitsInFrame; i++){
        if (i!=bitsInGenerator){
            temp=frame/pow(2,bitsInFrame-i);
            result=(result*2)+(temp & 1);
        }
        else{
            result=frame/pow(2,bitsInFrame-i);
        }
        if (result >= pow(2,bitsInGenerator-1)){
            result = result xor generator;
        }
    }
    
    remainder=result;
    CRCcode=frame xor remainder;

    cout<<"Message in Binary is : "<<decToBin(message)<<endl;
    cout<<"Generator in Binary is : "<<decToBin(generator)<<endl;
    cout<<"Remainder is : "<<decToBin(remainder)<<endl;
    cout<<"CRC code is : "<<decToBin(CRCcode)<<endl;   

    return;
}

int main(){
    int mess,gen;
    cout << "Enter message in decimal : ";
    cin >> mess;
    cout << "Enter generator in decimal : ";
    cin >> gen;

    codeGenerator(gen,mess);

}