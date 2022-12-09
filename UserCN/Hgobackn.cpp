#include <iostream>
#include <math.h>

using namespace std;

class Frame{
    public:
    int error;
    int seqNo;
    int frameNo;
};

class Window{
    public:
    Frame *frames;
    int numFrames;
};

class Sender{
    public:
    int totalFrames;
    int numWin;
    int maxSize;
    Window *windows;
    Sender(int bits, int totalFrames){
        this->totalFrames=totalFrames;
        maxSize=pow(2,bits)-1;
        if (totalFrames%maxSize!=0)
        {numWin=totalFrames/maxSize+1;}
        else
        {numWin=totalFrames/maxSize;}
        windows=new Window[numWin];
        for (int i=0; i<numWin; i++)
        {
            int count=-(i*maxSize);
            if (totalFrames < (i+1)*maxSize)
            {count+=totalFrames;}
            else
            {count+=(i+1)*maxSize;}
            (windows[i]).frames=new Frame[count];
            windows[i].numFrames=count;
            for (int j=i*maxSize; j<count+i*maxSize; j++)
            {
                int index=j%maxSize;
                windows[i].frames[index].seqNo=index;
                windows[i].frames[index].frameNo=j;
            }        
        }
    }
    void display(){
        for (int i=0; i<numWin; i++)
        {
            cout << "Window " << i+1 << " : ";
            for (int j=0; j<windows[i].numFrames; j++)
            {
                cout << windows[i].frames[j].seqNo+1 << " " << windows[i].frames[j].frameNo+1 << "     ";
            }
            cout << endl;
        }
    }
    void displayCurrent_Window(int curr){
        for (int i=0; i<windows[curr].numFrames; i++)
        {cout << "F" << windows[curr].frames[i].frameNo+1 << "  ";}
        cout << endl;
    }
    ~Sender(){
        for (int i=0; i<numWin;i++)
        {
            delete [] windows[i].frames;  
        }
        delete [] windows;
    }
};

class Receiver{
    public:
    int receive(Window window){
        for (int i=0; i<window.numFrames; i++)
        {
            if (window.frames[i].error==1)
            {return i;}
        }
        return -1;
    }
};



int main(){
    cout << "Hello World" << endl;
    int bits;
    int number;
    cout << "Total bits for sequencing : ";
    cin >> bits;
    cout << "Total number of frames to be transmitted : ";
    cin >> number;
    Sender s(bits, number);
    cout << "Window size for transmission : " << s.maxSize << endl;
    Receiver r;
   
    int option;
    int start=0;
    bool end=false;
    for (int i=0; i<s.numWin; i++)
    {
        for (int j=start; j<s.windows[i].numFrames; j++)
        {
           
       
            cout << endl << "===================================" << endl;
            cout << "Current Window : ";
            s.displayCurrent_Window(i);
            cout << "Enter 1 to send frame." << endl;
            cout << "Enter 2 to send frame with error." << endl;
            cout << "Enter 3 to quit." << endl;
            cout << endl << "Your option : ";
            cin >> option;
            cout << endl;
            switch(option)
            {
                case 1:
                    cout << "F" << s.windows[i].frames[j].frameNo+1 << " sent." << endl;
                    s.windows[i].frames[j].error=0;
                    break;
                case 2:
                    cout << "F" << s.windows[i].frames[j].frameNo+1 << " sent." << endl;
                    s.windows[i].frames[j].error=1;
                    break;
                case 3:
                    end=true;
                    break;
            }
            cout << "===========================================" << endl;
            if (end)
            {break;}
        }
        if (end)
        {break;}
        cout << "All Frames in this window sent." << endl;
        start=r.receive(s.windows[i]);
        if (start!=-1)
        {
            cout << "Receiver discarded F" << s1.windows[i].frames[start].frameNo+1 << " and every subsequent frame." << endl;
            cout << "Send F" << s1.windows[i].frames[start].frameNo+1 << " and every subsequent frame again." << endl;
            i--;
        }
        else
        {
            start=0;
            cout << "All frames in this window received successfully." << endl;
        }
    }
    cout << "End of Program." << endl;
   
   
   
    return 0;
}