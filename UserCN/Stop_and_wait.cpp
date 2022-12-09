#include <iostream>
#include <cstdlib>
using namespace std;

class Frame
{
public:
    int message[16]; 
    int ack;                      
    int frame_number;             

    Frame()
    {
        for (int i = 0; i < 16; i++)
        {
            message[i] = 0 + (rand() % 2); 
        }
    }

    void display()
    {
        for (int i = 0; i < 16; i++)
        {
            cout << message[i] << " ";
        }

        cout << endl;
    } 
};

class Sender 
{
public:
    Frame *frame1;
    Frame *frame2;
    int frame_expected = 1;
    int frame_ack_expected = 1;
    int frame_to_send = 0;
    int ack_to_send = 0;

    void create_frame()
    {
        Frame *f = new Frame();
        f->ack = this->ack_to_send;

        this->frame1 = f; 
    }
    int recieve_frame(Frame *f) 
    {
        if (f->frame_number == this->frame_expected) 
        {                                            
            this->frame2 = f;                        

            if (f->frame_number == 0) 
            {
                this->frame_expected = 1; 
            }

            else
            {
                this->frame_expected = 0; 
            }

            ack_to_send = f->frame_number; 

            return 1; 
        }

        else
        {
            return -1; 
        }
    }

    void send_frame(Frame *f) 
    {
        this->frame_ack_expected = f->frame_number; 

        if (f->frame_number == 0) 
        {
            this->frame_to_send = 1;
        }

        else
        {
            this->frame_to_send = 0;
        }
    }
};

class Reciever 
{
public:
    Frame *frame1;          
    Frame *frame2;              
    int frame_expected = 0;     
    int frame_ack_expected = 0; 
    int frame_to_send = 0;      
    int ack_to_send = 1;        
  

    void create_frame() 
    {
        Frame *f = new Frame();
        f->ack = this->ack_to_send;

        this->frame1 = f;
    }

    int recieve_frame(Frame *f) 
    {
        if (f->frame_number == this->frame_expected)
        {
            this->frame2 = f;

            if (f->frame_number == 0)
            {
                this->frame_expected = 1;
            }

            else
            {
                this->frame_expected = 0;
            }

            ack_to_send = f->frame_number;

            return 1;
        }

        else
        {
            return -1;
        }
    }
    void send_frame(Frame *f) 
    {
        this->frame_ack_expected = f->frame_number; 

        if (f->frame_number == 0) 
        {
            this->frame_to_send = 1;
        }

        else
        {
            this->frame_to_send = 0;
        }
    }
};

int main()
{
    Sender s;
    Reciever r;

    cout << "The sender creates a frame and sends it to the reciever." << endl;
    s.create_frame();
    s.send_frame(s.frame1);
    cout << "The message that is to be sent:" << endl;
    s.frame1->display();
    cout << "The frame number is:" << s.frame1->frame_number << endl;
    cout << "The next frame that will be sent is:" << s.frame_to_send << endl;
    cout << "The frame for which acknowledgement is expected with the next message is:" << s.frame_ack_expected << endl;

    int i = r.recieve_frame(s.frame1);

    // if (i = 1)
    // {
    //     if (r.frame_expected == 1)
    //     {
    //         r.frame_expected = 0;
    //     }

    //     else
    //     {
    //         r.frame_expected = 1;
    //     }
    // }

    cout << "\n\nThe values at the reciever side are:" << endl;
    cout << "The message that will be sent to the network layer is:";
    r.frame2->display();
    cout << "The frame for which acknowledgement will be sent is:" << r.ack_to_send << endl;
    cout << endl;

    cout << "\nNow the sender starts the timer. If acknowledgement arrives then the timer is stopped; otherwise the frame is resent." << endl;
    cout << "The message was recieved successfully.\n"<< endl;

    cout << "Now the receiver creates a frame and send it to the sender:" << endl;
    r.create_frame();
    r.send_frame(r.frame1);
    cout << "The message that is to be sent:" << endl;
    r.frame1->display();
    cout << "The acknowledgement sent with the frame is:" << r.ack_to_send << endl;

    int j = s.recieve_frame(r.frame1);
    if (j = 1)
    {
        if (s.frame_expected == 1)
        {
            cout << "The frame was recieved successfully." << endl;
            s.frame_expected = 0;
        }

        else
        {
            s.frame_expected = 1;
        }
    }

    cout << "Now the sender and the reciever flips the side and the cycle continues." << endl;
    return 0;
}