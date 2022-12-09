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
    int numFrames;
    Frame *frames;
};

class Sender{
    public:
    int totalFrames;
    int maxSize;
    int remainingFrames;
    Window win;
    Frame *allFrames;
    Sender(int bits, int totalFrames){
        this->totalFrames=totalFrames;
        this->remainingFrames=totalFrames;
        maxSize=pow(2,bits-1);
        allFrames=new Frame[totalFrames];
        for (int i=0; i<totalFrames; i++)
        {
            allFrames[i].frameNo=i;
            allFrames[i].error=1;
        }
        if (maxSize<=totalFrames)
        {
            win.frames=new Frame[maxSize];
            win.numFrames=maxSize;
        }
        else
        {
            win.frames=new Frame[totalFrames];
            win.numFrames=totalFrames;
        }
        for (int i=0; i<win.numFrames; i++)
        {
            win.frames[i]=allFrames[i];
            win.frames[i].seqNo=i;
        }
       
    }
    void displayCurrent_Window(){
        for (int i=0; i<win.numFrames; i++)
        {
            cout << "F" << win.frames[i].frameNo+1 << "  ";
        }
        cout << endl;
    }
    ~Sender(){
        delete [] allFrames;
        delete [] win.frames;
    }
};

class Receiver{
    public:
    int receive(Sender &s){
        int size=0;
        bool error=false;
        if (s.maxSize<s.remainingFrames)
        {size=s.maxSize;}
        else
        {
            size=s.remainingFrames;
        }
       
        Window temp=s.win;
        if (size==0)
        {
            s.win.frames=NULL;
            delete [] temp.frames;
            return -1;        
        }
        s.win.frames=new Frame[size];
        s.win.numFrames=size;
        int index=0;
        int lastFrame=0;
        for (int i=0; i<temp.numFrames; i++)
        {   
            lastFrame=temp.frames[i].frameNo;
            if (temp.frames[i].error==1)
            {
                s.win.frames[index]=temp.frames[i];
                s.win.frames[index].seqNo=index;
                index++;
                error=true;
            }
        }
        for (int i=lastFrame+1; index<s.win.numFrames; i++)
        {
            if (s.allFrames[i].error!=0)
            {
                s.win.frames[index]=s.allFrames[i];
                s.win.frames[index].seqNo=index;
                index++;
            }
        }
        delete [] temp.frames;
        if (error)
        {return s.win.frames[0].frameNo;}
        return -1;
    }
   
};

int main(){
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
    while (s.win.frames!=NULL)
    {
        for (int j=0; j<s.win.numFrames; j++)
        {
           
       
            cout << endl << "===================================" << endl;
            cout << "Current Window : ";
            s.displayCurrent_Window();
            cout << "Enter 1 to send frame." << endl;
            cout << "Enter 2 to send frame with error." << endl;
            cout << "Enter 3 to quit." << endl;
            cout << endl << "Your option : ";
            cin >> option;
            cout << endl;
            switch(option)
            {
                case 1:
                    cout << "F" << s.win.frames[j].frameNo+1 << " sent." << endl;
                    s.win.frames[j].error=0;
                    s.remainingFrames--;
                    break;
                case 2:
                    cout << "F" << s.win.frames[j].frameNo+1 << " sent." << endl;
                    s.win.frames[j].error=1;
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
        start=r.receive(s);
       
        if (start!=-1)
        {
            cout << "Receiver discarded F" << start+1 << " and only the subsequent accepted frames are stored. The window is appropriately modified." << endl;
            cout << "Send F" << start+1 << " again." << endl;
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