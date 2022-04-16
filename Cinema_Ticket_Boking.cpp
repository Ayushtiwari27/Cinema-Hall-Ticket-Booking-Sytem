#include <iostream>
using namespace std;

//node class for a circular linked list
class node
{
public:
    int seatc, seatr;   //seat's column and seat's row numbers
    int status;         //status stores whether the seat is booked or not
    node *next, *prev;
};

class cinema
{
public:

    node *head[10], *last[10];      //an array storing heads of each linked list of individual row
    
    //constructing which runs while object is created and traverse through all the elements of the 
    //linked list in the head array and makes every element status to not booked.
    cinema()                
    {
        for (int j = 0; j < 10; j++)
        {
            head[j] = last[j] = NULL;
            node *temp;
            for (int i = 1; i <= 7; i++)
            {
                temp = create_node(i, j + 1);
                if (head[j] == last[j] && head[j] == NULL)
                {
                    head[j] = last[j] = temp;
                    head[j]->next = last[j]->next = NULL;
                    head[j]->prev = last[j]->prev = NULL;
                }
                else
                {
                    temp->next = head[j];
                    head[j]->prev = temp;
                    head[j] = temp;
                    head[j]->prev = last[j];
                    last[j]->next = head[j];
                }
            }
        }
    }


    //creating a new node
    node *create_node(int x, int y)
    {
        node *temp;
        temp = new (node);
        temp->seatc = x;
        temp->seatr = y;
        temp->status = 1;
        temp->next = NULL;
        temp->prev = NULL;
        return temp;
    }

    //BOOKING A SEAT
    void book()
    {
        int n;
        char c;
        cout << "\nDo you want to book multiple seat (y/n)?  ";     //allowing multiple seats booking
        cin >> c;
        if (c == 'y' || c == 'Y' )
        {
            cout << "\nHow many seats do you want to book? : ";
            cin >> n;
        }
        else
        {
            n = 1; //if only one seat is to be booked set n=1
        }
        while (n--)     //booking  (multiple) seats
        {
            int x, y;
        lb2:
            cout << "\nEnter row and column: ";
            cin >> x >> y;
            if (x < 1 || x > 10 || y < 1 || y > 7)  //if seat number entered is out of the range error pops up
            {
                cout << "\n>>Enter correct seat number to book \n";
                goto lb2;               //again allowing to book seat
            }
            node *temp;
            temp = head[x - 1];
            for (int i = 0; i < 7; i++)
            {
                if (temp->seatc == y)
                {
                    if (temp->status == 1)  //checking status of the seat
                    {
                        temp->status = 0;          //changing status of the seat when booked only if not booked already
                        cout << ">>Seat Booked\n";
                    }
                    else
                    {
                        cout << ">>SORRY !! Already booked!!\n";
                    }
                }
                temp = temp->next;
            }
        }
        display();
    }

    //CANCELING A SEAT
    void cancel()
    {
        int x, y;
    lb3:
        cout << "\nEnter row and column: ";
        cin >> x >> y;
        if (x < 1 || x > 10 || y < 1 || y > 7)      //if seat number entered is out of the range error pops up
        {
            cout << "\n>>Enter correct seat number to cancel \n";
            goto lb3;
        }
        node *temp;
        temp = head[x - 1];
        for (int i = 0; i < 7; i++)
        {
            if (temp->seatc == y)
            {
                if (temp->status == 0)      //checking if seat is already booked
                {
                    temp->status = 1;           //toggling status of the seat
                    cout<<">>Seat Cancelled\n";
                }
                else
                {
                    cout << "----- SEAT NOT BOOKED -----\n";
                }
            }
            temp = temp->next;
        }
        display();
    }

    //DISPLAY AVAILABLE SEATS
    void avail()
    {
        node *temp;
        cout << "\nAvailable seats are: \n";
        for (int j = 0; j < 10; j++)
        {
            temp = last[j];
            for (int i = 0; i < 7; i++)
            {
                if (temp->status == 1)
                    cout << temp->seatr << "-" << temp->seatc << "\t";      //displaying seat numbers which are available
                else
                {
                    cout << " X\t";         //if seat is not available then display a cross (X)
                }
                temp = temp->prev;
            }
            cout << "\n";
        }
    }

    //DISPLAY CURRENT SEAT STATUS
    void display()
    {
        node *temp;
        cout << "\n-----------------------------------------------------------------------------------------------------------\n";
        cout << "                                                Screen   \n";
        cout << "-----------------------------------------------------------------------------------------------------------\n";
        for (int j = 0; j < 10; j++)
        {
            temp = last[j];
            for (int i = 0; i < 7; i++)
            {
                cout << temp->seatr << "-" << temp->seatc << " :";
                if (temp->status == 1)
                {
                    cout << "|___| " << "\t";       //display for empty seats
                }

                else
                {
                    cout << "|_B_| " << "\t";       // display for booked seats
                }

                temp = temp->prev;
            }
            cout << "\n";
        }
    }
};

//MAIN FUNCTION
int main()
{
    //creating class object
    cinema t;

    //calling display function to display the seat layout of the  hall
    t.display();

    while (1)
    {
        cout << "\n\n\n-------------------- MENU -------------------\n";
        cout << "\n1. Book Seat";
        cout << "\n2. Cancel a Seat";
        cout << "\n3. Display Available Seats ";
        cout << "\n4. Exit";

        int ch;
        cout << "\n\n>>Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1: // BOOK FUNCTION CALL
            t.book();
            continue;

        case 2: // CANCEL FUNCTION CALL
            t.cancel();
            continue;

        case 3: // AVAILABLE FUNCTION CALL
            t.avail();
            continue;

        case 4: // EXIT
            cout << "-- Thank You!! --";
            break;

        default:
            cout << "\n----Wrong Input----\nEnter Valid choice\n";
            continue;
        }
        break;
    }

    return 0;
}
