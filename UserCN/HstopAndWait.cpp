#include <iostream>
using namespace std;
class Frame{
    public:
    int seq;
    int frameNo;
    Frame(int seq, int frameNo){
        this->seq=seq;
        this->frameNo=frameNo;
    }
};
int ack=1;
int seq=0;

class Sender{
    public:
    Frame *previousFrame;
    Sender (int seq, int frameNo){
        previousFrame=new Frame(seq, frameNo);
    }
    bool send(){
        if (ack==previousFrame->seq)
        {
            previousFrame->frameNo+=1;
            previousFrame->seq=1-ack;
            seq=1-seq;
            return true;
        }
        return false;
   
    }
    void sendFirst(){
        if (previousFrame->seq==0 && previousFrame->frameNo==0 && seq==0)
        {return;}
        else
        {
            previousFrame->seq=0;
            previousFrame->frameNo=0;
            seq=0;
        }
        return;
    }
    ~Sender(){
        delete previousFrame;
    }
   
};


class Receiver{
    public:
    bool receive(){
        if (seq!=ack){
            ack=1-ack;
            return true;
        }
        return false;
    }
   
};


int main(){
    Sender a(0,0);
    Receiver b;
    int count=0;
    for (int i=0; i<5; i++)
    {
        if (i!=0)
        {
            bool sent=a.send();
            if (sent)
            {
                cout << "Sender says :" << endl;
                cout << "Acknowledgement Received" << endl;
                cout << "Sent Frame sequence_number: " << a.previousFrame->seq << endl;
                cout << "           frame_number   : " << a.previousFrame->frameNo << endl << endl;
            }
            else
            {count++;}
            if (count==4)
            {
                cout << "Sender says :" << endl;
                cout << "Acknowledgement not received." << endl;
                cout << "Sending Frame again." << endl;
                cout << "Acknowledgement Received" << endl;
                cout << "Sent Frame sequence_number: " << a.previousFrame->seq << endl;
                cout << "           frame_number   : " << a.previousFrame->frameNo << endl << endl;
                count=0;
            }
        }
        else
        {
            a.sendFirst();
            cout << "Sender says :" << endl;
            cout << "Sent Frame sequence_number: " << a.previousFrame->seq << endl;
            cout << "           frame_number   : " << a.previousFrame->frameNo << endl << endl;
        }
       
        bool received=b.receive();
        if (received)
        {
            cout << "Receiver says :" << endl;
            cout << "Frame received, acknowledgement sent and frame transferred to network layer.\n\n";
        }
        else
        {
            cout << "Receiver says :" << endl;
            cout << "Duplicate Frame, frame discarded" << endl << endl;
        }
       
       
    }
    return 0;
}