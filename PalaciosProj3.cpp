/*Jacqueline Palacios
jpalacio@my.athens.edu
00100531
April 22, 2022
P. 3
*/

#include <iostream>
#include <iomanip>
using namespace std;

//name constants for charts
const int ROW = 7, COL = 8;
//function prototypes
int movieMenu(); //movie menu
int adminOption(); //admin menu
//chart is separated into three different functions. one to create the seats
//one to format the display of the screen
//the third allows the user to choose their seats based on the amount of tickets they have
//and formats the chart based on if the seat is taken, blocked, or available.
void createScreen(char [][COL], int); //
void showChart(char [][COL], int);
void pickSeats(char [][COL], int, int); //respective chart is passed, rows named after, and tickets
int getmovieShowing(int); //selection to pick movie time
int buyTickets(int &, int &); //options for adult and children tickets
int validateTicket(int); //checks for tickets purchased < 0
float calculatePrice(int, int, int); //calculates price of tickets
void showReceipt(float);
int validateRow(int); //validates row
int validateSeat(int); //validates seat/column

int main()
{
  const int MOVIE = 1;
  const int ADMIN = -99;
  int selection = 0;
  int movieOption = 0;
  int adultCount = 0; 
  int childrenCount = 0;
  int movieShowing = 0;
  int adultTickets = 0;
  int childTickets = 0;
  int ticketsBought = 0;
  int sumTickets = 0;
  float movieCost = 0;
  float totalMovieProfits = 0;
  //variables needed for 2D arrays for movies
  char chartFree1[ROW][COL];
  char chartFree2[ROW][COL];
  char chartBeth1[ROW][COL];
  char chartBeth2[ROW][COL];
  //creates the outline for the 4 needed movie charts. They all have their own display.
  //Must be created before or program will continue to make them.
  createScreen(chartFree1, ROW);
  createScreen(chartFree2, ROW);
  createScreen(chartBeth1, ROW);
  createScreen(chartBeth2, ROW);
  
  
  do
  {
    //opportunity for administration to access secret menu
    cout<<"\nTo proceed to movie selection, enter 1."<<endl;
    cin>>selection;

    while(selection != MOVIE && selection != ADMIN)
    {
        cout<<"You have entered an invalid response. Please input 1 to continue: ";
        cin>>selection;
    }


    switch(selection)
    {
      case MOVIE: 
      {
        movieOption = movieMenu();
        //will only execute if either movie option 1 or 2 was selected
        if(movieOption == 1 || movieOption == 2)
        {
          movieShowing = getmovieShowing(movieOption);
          ticketsBought = buyTickets(adultCount, childrenCount);
        }

        if(movieOption == 1)
        {
          if(movieShowing == 1)
          {
            showChart(chartFree1, ROW);
            pickSeats(chartFree1, ROW, ticketsBought);
            adultTickets += adultCount;
            childTickets += childrenCount;
            movieCost = calculatePrice(adultCount, childrenCount, movieShowing);
            totalMovieProfits += movieCost;
            showReceipt(movieCost);
            movieCost = 0; //refreshes the value for each loop when done
            adultCount = 0; //refreshes the value for each loop when done
            childrenCount = 0; //refreshes the value for each loop when done
            showChart(chartFree1, ROW);
          }
          else if(movieShowing == 2)
          {
            showChart(chartFree2, ROW);
            pickSeats(chartFree2, ROW, ticketsBought);
            adultTickets += adultCount;
            childTickets += childrenCount;
            movieCost = calculatePrice(adultCount, childrenCount, movieShowing);
            totalMovieProfits += movieCost;
            showReceipt(movieCost);
            movieCost = 0; //refreshes the value for each loop when done
            adultCount = 0; //refreshes the value for each loop when done 
            childrenCount = 0; //refreshes the value for each loop when done
            showChart(chartFree2, ROW);
          }
        }
        else if(movieOption == 2)
        {
          if(movieShowing == 1)
          {
              showChart(chartBeth1, ROW);
              pickSeats(chartBeth1, ROW, ticketsBought);
              adultTickets += adultCount;
              childTickets += childrenCount;
              movieCost = calculatePrice(adultCount, childrenCount, movieShowing);
              totalMovieProfits += movieCost;
              showReceipt(movieCost);
              movieCost = 0; //refreshes the value for each loop when done
              adultCount = 0; //refreshes the value for each loop when done
              childrenCount = 0; //refreshes the value for each loop when done
              showChart(chartBeth1, ROW);
          }
          else if(movieShowing == 2)
          {
              showChart(chartBeth2, ROW);
              pickSeats(chartBeth2, ROW, ticketsBought);
              adultTickets += adultCount;
              childTickets += childrenCount;
              movieCost = calculatePrice(adultCount, childrenCount, movieShowing);
              totalMovieProfits += movieCost;
              showReceipt(movieCost);
              movieCost = 0; //refreshes the value for each loop when done
              adultCount = 0; //refreshes the value for each loop when done
              childrenCount = 0; //refreshes the value for each loop when done
              showChart(chartBeth2, ROW);
          }
        }
        else if(movieOption == 3)
        {
          break;
        }
        break;
      }

      case ADMIN:
      { 
        do
        {
          int selection = adminOption();

          if(selection == 1)
          {
            cout<<setprecision(2)<<fixed<<showpoint<<endl;
            cout<<"Total Profits: $"<<totalMovieProfits<<endl<<endl;
          }
          else if(selection == 2)
          {
            sumTickets = childTickets + adultTickets;
            cout<<"\nTotal Ticket Sales: "<<sumTickets<<endl<<endl;
          }
          else if(selection == 3)
          {
            cout<<"\nTotal Adult Ticket Sales: "<<adultTickets<<endl;
            cout<<"Total Children Ticket Sales: "<<childTickets<<endl<<endl;
          }
          else if(selection == 4)
          {
          break;
          }
          else if (selection == 5)
          {
            cout<<"Shutting Down..."<<endl;
            return 0;
          }
        } while (selection != 5);
        
          break;
        }
    }
  } while(selection == MOVIE || selection == ADMIN);  
}

//functions begin
void createScreen(char seatingChart[][COL], int ROW)
{
  for(int counter1 = 1; counter1 <= ROW; counter1++)
  {
    for(int counter2 = 1; counter2 <= COL; counter2++)
    {
      seatingChart[counter1][counter2] = '*';
    }
  }
}

void showChart(char chart[][COL], int ROW)
{
  //displays seating chart
  cout<<"---------------------------------------"<<endl;
  cout<<"Seats";
  cout<<setw(2)<<"|";
  for(int counter = 1; counter <= COL; counter++)
  {
      cout<<setw(2)<<right<<counter;
      cout<<setw(2)<<"|";
        
  }
  cout<<"\n---------------------------------------"<<endl;
  
  for(int counter1 = 1; counter1 <= ROW; counter1++)
  {
    cout<<"Row "<<counter1;
    
    for(int counter2 = 1; counter2 <= COL; counter2++)
    {
      cout<<setw(2)<<"|";
      cout<<setw(2)<<chart[counter1][counter2];
    }
    cout<<setw(2)<<"|";
    cout<<endl;
    cout<<"---------------------------------------"<<endl;
    }
}

int adminOption()
{
  int selection;

  cout<<"\nAdministration Options:"<<endl;
  cout<<"1. View Total Profits\n"
      <<"2. View Total Tickets\n"
      <<"3. View Tickets By Type\n"
      <<"4. Return to Main Menu\n"
      <<"5. Shut Down\n"
      <<"Enter your selection 1 through 5: ";
  cin>>selection;

  while(selection < 1 || selection > 5)
  {
    cout<<"You have entered an invalid selection. Please enter a number 1 through 5: ";
    cin>>selection;
    cout<<endl;
  }

  return selection;
}

int movieMenu()
{
    int selection;

    cout<<"___________________________________________________________\n\n";
    cout<<setw(49)<<right<<"Welcome to Athens State Theater\n\n";
    cout<<setw(35)<<right<<"Adult Tickets: $6.00 matinee (before 6pm) $8.00(evening)\n"
        <<setw(35)<<right<<"Child Tickets: $4.00 matinee (before 6pm) $6.00(evening)\n\n"
        <<setw(32)<<right<<"Now Showing\n"
        <<setw(23)<<right<<"Free Birds"<<setw(13)<<right<<"3:30"<<setw(8)<<right<<"6:00\n"
        <<setw(23)<<right<<"Bethooven"<<setw(13)<<right<<"5:30"<<setw(7)<<right<<"7:30"
        <<"\n\nEnter: "
        <<"\n1 for 'Free Birds'\n" 
        <<"2 for 'Bethooven' \n"
        <<"3 for Main Menu\n";
    cin>>selection; 
    
    //input validation
    while(selection < 1 || selection > 3)
    {
        cout<<"You have entered an invalid movie menu option. Please re-enter your choice.\n"
            <<"1 for 'Free Birds'" 
            <<"\n2 for 'Bethooven' "
            <<"\n3 for Main Menu\n";
        cin>>selection;
    }
    return selection;
}

int getmovieShowing(int selection)
{
  int movieShowing;

  if(selection == 1)
  {
    cout<<setw(30)<<right<<"Free Birds"<<endl;
    cout<<"Enter 1 to buy seats for the 3:30 showing\n"
        <<"Enter 2 to buy seats for the 6:00 showing\n";
    cin>>movieShowing;

    while(movieShowing < 1 || movieShowing > 2)
    {
      cout<<"You have input an invalid selection. Please enter either 1 for 3:30 or 2 for 6:00: "<<endl;
      cin>>movieShowing;
      cout<<endl;
    }
  }
  if(selection == 2)
  {
    cout<<setw(30)<<right<<"Bethooven"<<endl;
    cout<<"Enter 1 to buy seats for the 5:30 showing\n"
        <<"Enter 2 to buy seats for the 7:30 showing\n";
    cin>>movieShowing;

    while(movieShowing < 1 || movieShowing > 2)
    {
      cout<<"You have input an invalid selection. Please enter either 1 for 5:30 or 2 for 7:30: "<<endl;
      cin>>movieShowing;
      cout<<endl;
    }
  }
  return movieShowing;
  
}

int validateTicket(int ticket)
{
  while (ticket <= 0)
  {
    cout<<"Invalid number of tickets. Enter a number greater than zero."<<endl;
    cin>>ticket;
  }
  return ticket;
}

int buyTickets(int &adults, int &children)
{

  int selection;
  int numOfTickets = 0;

  cout<<"If you would like to purchase adult tickets select 1\n"
      <<"If you would like to purchase child tickets select 2\n";
  cin>>selection;

  while(selection < 1 || selection > 2)
  {
    cout<<"Invalid menu option. Enter 1 for adult tickets\n"
        <<"Enter 2 for child tickets"<<endl;
    cin>>selection;
  }
  
  do
  {
    if(selection == 1)
    {
      cout<<"Enter the number of Adult Tickets:"<<endl;
      cin>>adults;
      validateTicket(adults);
      numOfTickets += adults;
    }
    else if(selection == 2)
    {
      cout<<"Enter the number of Child Tickets"<<endl;
      cin>>children;
      validateTicket(children);
      numOfTickets += children;
    }
    cout<<"Need additional tickets?\n"
        <<"Enter 1 for Adult tickets\n"
        <<"Enter 2 for Child tickets\n"
        <<"Enter 3 to continue to seat selection\n";
    cin>>selection;

    //input validation
    while(selection < 1 || selection > 3)
    {
      cout<<"You have entered an invalid selection. Please input a valid selection (1-3): ";
      cin>>selection;
      cout<<endl;
    }

  } while (selection != 3);

  return numOfTickets;
}

float calculatePrice(int adult, int child, int movietime)
{
  float adultTicketPrice;
  float childTicketPrice;
  float totalPrice;

  if(movietime == 1)
  {
    adultTicketPrice = 6;
    childTicketPrice = 4;
    totalPrice = (adult * adultTicketPrice) + (child * childTicketPrice);
  }
  else if(movietime == 2)
  {
    adultTicketPrice = 8;
    childTicketPrice = 6;
    totalPrice = (adult * adultTicketPrice) + (child * childTicketPrice);
  }
  return totalPrice;
}

int validateRow(int row)
{
  while(row <= 0 || row > 7)
  {
    cout<<"You have entered an invalid row number. Please choose an empty row numbers 1 through 7: "<<endl;
    cin>>row;
    }
  return row;
}

int validateSeat(int seat)
{
  while(seat <= 0 || seat > 8)
  {
      cout<<"You have entered an invalid seat number. Please choose an empty seat numbers 1 through 8: ";
      cin>>seat;
  }
  return seat;
}

void pickSeats(char chart[][COL], int ROW, int ticketsPurchased)
{

  const char TAKEN = '#';
  const char BLOCKED = 'X';
  const char AVAILABLE = '*';

  int row;
  int seat;

  while(ticketsPurchased > 0)
  {
    //validates the row
    cout<<"Enter the row you would like to sit in: "<<endl;
    cin>>row;
    validateRow(row);

    //validates the seat number
    cout<<"Enter the seat number:"<<endl;
    cin>>seat;
    validateSeat(seat);

    while(chart[row][seat] == BLOCKED || chart[row][seat] == TAKEN)
    {
      cout<<"You have selected an unavailable seat. This seat is either blocked due to Covid Restrictions\n"
          <<"shown by X or already taken shown by #.\n"
          <<"Please enter a different row and seat number.\n"
          <<"Row number: ";
      cin>>row;
      cout<<"Seat number: ";
      cin>>seat;
      cout<<endl;
    }
    //blocks seats in front and behind the taken seat. Leaves two more seats needed to be blocked
    //unless taken.
    chart[row][seat] = TAKEN;
    chart[row - 1 ][seat] = BLOCKED; //front
    chart[row + 1][seat] = BLOCKED; //behind
    ticketsPurchased--;

  }

  //accounts for blocking the rest of the needed seats and marks them accordingly
  //with either *, #, or X
  //to account for correct number of elements, you must either add or sub 1
  for(int counter1 = 1; counter1 <= ROW; counter1++)
  {
    //for loop for COL
    for(int counter2 = 1; counter2 <= COL; counter2++)
    {
      if(chart[counter1][counter2] == TAKEN )
      { 
        if(chart[counter1][counter2 + 1] != BLOCKED || chart[counter1][counter2 + 1] != TAKEN || chart[counter1][counter2 - 1] != BLOCKED || chart[counter1][counter2 - 1] != TAKEN)
        {
          //checks if the seat next to the left it is open. If so, blocks it.
          if(chart[counter1][counter2 - 1] == AVAILABLE)
          {
            chart[counter1][counter2 - 1] = BLOCKED;
          }
          //checks if the seat to the right is open. If so, blocks it.
          else if(chart[counter1][counter2 + 1] == AVAILABLE)
          {
            chart[counter1][counter2 + 1] = BLOCKED;
          }
        }
      }
    } //end for loop for COL
  }
}

void showReceipt(float total)
{
  cout<<setprecision(2)<<fixed<<showpoint;
  cout<<"--------------------------------------------\n"
      <<"Thank you for choosing Athens State Theater!\n"
      <<"Total Amount Due: $"<<total<<" (tax included)\n"
      <<"--------------------------------------------\n";
}