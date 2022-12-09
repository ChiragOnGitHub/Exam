#include <iostream>
using namespace std;

class Frame
{
    public:

    int message[16];
    int frame_number = 0;

    Frame()
    {
        for(int i = 0; i < 16; i++)
        {
            message[i] = 0 + (rand()%2); 
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

    Frame* f1;
    int* window;
    int windowSize;
    int CurrentWindowSize = 0;
    int FrameCounter = 0;

    Sender(){
        cout<<"Enter the size of window for the sender:";
        cin>>windowSize;

        window = new int[windowSize];
    }

    Frame* SendFrameToWindow(){
        if(CurrentWindowSize == windowSize){
            cout<<"Window is currently Full!! "<<endl;
        }
        else{
            f1 = new Frame(); 
            f1->frame_number = FrameCounter;
            if(FrameCounter == windowSize - 1){
                FrameCounter = 0;
            }
            else{
                FrameCounter++; 
            }

            //check here
            window[CurrentWindowSize] = 1;
            CurrentWindowSize++;

            return f1;
        }
    
    }

    void get_ack(int x){
        if(x < 0)
        {
            cout<<"Negative ACK for frame"<<-x<<endl;
        }

        else 
        {
            window[x] = 0;
            CurrentWindowSize--;
        }
    }

    void display_window(){
        for(int i = 0; i < windowSize; i++){
            cout<<window[i]<<" ";
        }
        cout<<endl;
    }
};


class Reciever
{
    public:

    Frame* f;
    int* frame_buffer;
    int buffer_size;
    int current_buffer_size = 0;

    Reciever(int x){
        buffer_size = x;
        frame_buffer = new int[buffer_size];

        for(int i = 0; i < buffer_size; i++)
        {
            frame_buffer[i] = 0;
        }
    }
    int send_ack(){
        return f->frame_number;
    }
    int send_nack(){
        return -(f->frame_number);
    }
    void recieve_frame(Frame* f1){
        f = f1;
        frame_buffer[f1->frame_number] = 1;
    }
    void display_buffer(){
        for(int i = 0; i < buffer_size; i++)
        {
            cout<<frame_buffer[i]<<" ";
        }

        cout<<endl;
    }
};


int main()
{
    Sender s1;
    Reciever r1(s1.windowSize);
    Frame* f;

    Frame* frame_array[s1.windowSize];

    cout<<endl;
    cout<<"First the sender will send "<<s1.windowSize<<" frames."<<endl<<endl;

    for(int i = 0; i < s1.windowSize; i++)
    {
        frame_array[i] = s1.SendFrameToWindow();

        cout<<"Frame number "<<frame_array[i]->frame_number<<" Sent by Sender is : ";
        frame_array[i]->display();
    }

    cout<<endl;
    cout<<"Sender's Window Buffer is :";
    s1.display_window();
    cout<<endl;

    cout<<"Now the reciever starts receiving the frames and start sending the acknowledgement."<<endl;
    cout<<endl;

    for(int i = 0; i < r1.buffer_size; i++)
    {
        cout<<"The frame "<<frame_array[i]->frame_number<<" received by receiver is : ";
        r1.recieve_frame(frame_array[i]);
        r1.f->display();
        s1.get_ack(r1.f->frame_number);

        cout<<"Sender's Window Buffer is : ";
        s1.display_window();
        cout<<"Receiver's Window Buffer is : ";
        r1.display_buffer();

        cout<<endl;
    }

    cout<<endl;
    cout<<"Acknowledgement for all the frames sent by the sender is successfully received by it.";

    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;

    cout<<"Now we show the case in which acknowledgement is lost or Frame is not received by receiver\n"<<endl;
    cout<<"Please enter frame number which is lost or acknowledgement is not recieved : ";
    int lost_frame;
    cin>>lost_frame;



    cout<<endl;
    cout<<"First the sender sends all the frame:"<<endl;
    for(int i = 0; i < s1.windowSize; i++){
        frame_array[i] = s1.SendFrameToWindow();

        cout<<"Frame number "<<frame_array[i]->frame_number<<" Sent by Sender is : ";
        frame_array[i]->display();
    }

    cout<<endl;

    cout<<"Sender's Window Buffer is : ";
    s1.display_window();

    cout<<endl;
    cout<<"Now the reciever start receiving frames."<<endl;
    cout<<endl;

    for(int i = 0; i < lost_frame; i++)
    {
        cout<<"The frame "<<frame_array[i]->frame_number<<" received by receiver is : ";
        r1.recieve_frame(frame_array[i]);
        r1.f->display();
        s1.get_ack(r1.f->frame_number);

        cout<<"The window buffer of the sender is:";
        s1.display_window();
    }

    cout<<endl;

    cout<<"Now as soon as the reciever recieves frame number "<<lost_frame+1<<" it will buffer it and send a NACK for frame number "<<lost_frame<<endl;
    cout<<"This will cause the sender to send this frame back to the reciever again."<<endl;

}