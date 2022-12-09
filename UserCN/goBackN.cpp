#include <iostream>
using namespace std;

class Frame
{
    public:

    int message[16];
    int frame_number;

    Frame()
    {
        for(int i = 0; i < 16; i++)
        {
            message[i] =rand()%2; 
        }
    }

    void display()
    {
        for(int i = 0; i< 16; i++)
        {
            cout<<message[i]<<" ";
        }
        cout<<endl;
    }

};




class Sender
{
    public:

    Frame* frame;  
    int WindowSize;
    int CurrentWindowSize = 0; 
    int FrameCount = 0;

    Sender(){
        cout<<"Enter Sender's Window size : ";
        cin>>WindowSize;
    }

    Frame* send_frame(){
        if(CurrentWindowSize == WindowSize)
        {
            cout<<"Maximum window size allowed is reached"<<endl;
        }

        else
        {
            frame = new Frame(); 
            frame->frame_number = FrameCount;

            if(FrameCount == WindowSize - 1) 
            {
                FrameCount = 0;
            }
            else{
                FrameCount++;
            }

            CurrentWindowSize++;
            return frame;
        }
    }

    void get_ack(){
        CurrentWindowSize--;
    }
};




class Reciever
{
    public:

    Frame* frame;
    bool WindowOpen = true;


    void recieve_frame(Frame* f){
        if(WindowOpen == false)
        {
            cout<<"Frame cannot be received"<<endl;
            return;
        }

        frame = f;
        WindowOpen = true;
    } 
    
    void SentFrameToNetworkLayer()
    {
        WindowOpen = true;
    }
};

int main()
{
    Sender s1;
    Reciever r1;
    Frame* f;

    Frame* frame_array[s1.WindowSize];

    cout<<endl;
    cout<<"First the sender will send "<<s1.WindowSize<<" frames."<<endl<<endl;

    for(int i = 0; i < s1.WindowSize; i++)
    {
        frame_array[i] = s1.send_frame();

        cout<<"Frame number "<<frame_array[i]->frame_number<<" Sent by Sender is : ";
        frame_array[i]->display();
    }

    cout<<endl;
    cout<<"Now the reciever starts receiving the frames and start sending the acknowledgement."<<endl;
    cout<<endl;

    for(int i = 0; i < s1.WindowSize; i++)
    {
        cout<<"The frame "<<frame_array[i]->frame_number<<" received by receiver is : ";
        r1.recieve_frame(frame_array[i]);
        r1.frame->display();
        r1.SentFrameToNetworkLayer();
        s1.get_ack();
    }
    cout<<endl;

    cout<<"Acknowledgement for all the frames sent by the sender is successfully received here.";

    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;

    cout<<"Now we show the case in which acknowledgement is lost or Frame is not received by receiver\n"<<endl;
    cout<<"Please enter frame number which is lost or acknowledgement is not recieved : ";
    int lost_frame;
    cin>>lost_frame;

    if(lost_frame >= s1.WindowSize)
    {
        cout<<"Frame number lost cannot be greater than window size"<<endl;
        return -1;
    }

    cout<<endl;
    cout<<"First the sender sends all the frame ."<<endl;
    cout<<endl;
    for(int i = 0; i < s1.WindowSize; i++)
    {
        frame_array[i] = s1.send_frame();

        cout<<"Frame number "<<frame_array[i]->frame_number<<" Sent by Sender is : ";
        frame_array[i]->display();
    }

    cout<<endl;
    cout<<"Now the reciever start receiving frames."<<endl;
    cout<<endl;

    for(int i = 0; i < lost_frame; i++)
    {
        cout<<"The frame "<<frame_array[i]->frame_number<<" received by receiver is : ";
        r1.recieve_frame(frame_array[i]);
        r1.frame->display();
        r1.SentFrameToNetworkLayer();
        s1.get_ack();
    }
    cout<<endl;
    cout<<endl;
    cout<<"as acknowledgement for these "<<lost_frame<<" frames has been received by sender.";
    cout<<" it will send "<<lost_frame<<" more new frames which are : "<<endl;


    for(int i = 0; i < lost_frame; i++)
    {
        f = s1.send_frame();
        f -> display();
    }

    cout<<endl;
    cout<<"Now since the ack for the frame number  "<<lost_frame<<" is not received"<<endl;
    cout<<"The sender will send all "<<s1.WindowSize<<" frames currently present in the window again."<<endl;
}