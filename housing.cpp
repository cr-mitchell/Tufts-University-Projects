// housing.cpp
// by: Charles Mitchell
// date: 03-09-2022

/* In this two week long project, we were asked to a query from students 
at Tufts University to look for off campus housing and rent the house if it
is available. You can also check if you would rent a house if you would have 
neighbors */

#include <iostream>
#include <fstream>

using namespace std;

const int ROWS = 50;
const int COLS = 20;


struct House
{
    bool   no_house_here;
    int    id;             
    string lot_code;      
    float price;
    int bedrooms;
    string color;
    string availability;
};


House read_one_house(ifstream& input_file);
void print_house(House h);
int col_from_lot(string lot);
int row_from_lot(string lot);
void fill_with_no_houses(int rows, int cols, House all_houses[ROWS][COLS]);
bool read_all_house_data(string filename, House all_houses[ROWS][COLS]);
void user_input(House all_houses[ROWS][COLS]);
bool is_available(int house_id, House all_houses[ROWS][COLS]);
int matching_houses(float max_price, string desired_color,
                       int desired_bedrooms, House all_houses[ROWS][COLS],
                       House results[ROWS * COLS]); 
int num_neighbors(int house_id, House all_houses[ROWS][COLS]);
int rent_house(int house_id, House all_houses[ROWS][COLS]);
void run_command_loop(House all_houses[ROWS][COLS]);
void handle_is_available(House all_houses[ROWS][COLS]);
void handle_matching_houses(House all_houses[ROWS][COLS]); 
void handle_num_neighbors(House all_houses[ROWS][COLS]); 
int handle_rent_houses(House all_houses[ROWS][COLS]); 


int main(int argc, char *argv[])
{
    //checks to see if the argument count on the command line is 2
    if (argc != 2) {
        cerr << "ERROR: You must provide the name of the file." << endl;
        return 1;
    }
    
    // stores the filename into a string variable
    string filename = argv[1];
    
    // creates a structure 2D array from the house struct 
    House all_houses[ROWS][COLS];
    
    // calls this function to fill each "box" in the array with no houses
    fill_with_no_houses(ROWS, COLS, all_houses);
    
    // stores the return value from read_all_house_data into a bool variable
    bool output = read_all_house_data(filename, all_houses);
    
    if (output != 1) {
        cerr << "ERROR: File could not be read." << argv[1] << endl;
        return 1;
    }
    
    // initizalizes the housing query 
    run_command_loop(all_houses);
    
    return 0;
}


/* 
read_one_house
Parameters: inputed file entered in the command line
Purpose:  collects information from the file into the House struct
Returns: a filled house struct with information from the file
*/
House read_one_house(ifstream& input_file)
{
    House get_house;  

    input_file >> get_house.id;
    input_file >> get_house.lot_code;
    input_file >> get_house.price;
    input_file >> get_house.bedrooms;
    input_file >> get_house.color;
    input_file >> get_house.availability;
    
    get_house.no_house_here = false;
    
    return get_house;
}


/* 
print_house
Parameters: a House stuct with information from the inuted file
Purpose: prints the data from the House struct 
Returns: nothing
*/
void print_house(House h)
{
    cout << "Id: " << h.id;
    cout << " Lot: " << h.lot_code;
    cout << " Color: " << h.color;
    cout << " Price: " << h.price;
    cout << " Bedrooms: " << h.bedrooms;
    if (h.availability == "available") {
        cout << " Available: Yes" << endl;
    } else if (h.availability == "booked") {
        cout << " Available: No" << endl;
    }
}


/* 
col_from_lot
Parameters: an inputed string given a lot code
Purpose: converts the letter in the lot code into a number that the 2D
        struct can be assigned to
Returns: the converted letter into a number
*/
int col_from_lot(string lot)
{
    int convert;
    convert = lot[0] - 65;
    
    return convert;

}


/* 
row_from_lot
Parameters: an inputed string given a lot code
Purpose: converts the numbers in the lot code into a number that the 2D
         array can be assigned to
Returns: the converted numbers into a number that starts at 0
*/
int row_from_lot(string lot)
{
    int length = lot.length(); 
    int num1 = 0;
    int convert1 = 0;
     
    for (int i = 0; i < length; i++) {
        if (lot[i] >= '0' and lot[i] <= '9') {
            num1 = lot[i] - '0'; 
            convert1 = (convert1 * 10) + num1;                          
        }
    }
    
    return convert1 - 1;
}


/* 
fill_with_no_houses
Parameters: an inputed integer for the row and column the user wants to get 
            a house from and the all_houses 2D array
Purpose: fills the 2D array with the boolean value true that no house is in
         that slot
Returns: nothing
*/
void fill_with_no_houses(int rows, int cols, House all_houses[ROWS][COLS])
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            all_houses[i][j].no_house_here = true;
        }
    } 
}


/* 
read_all_house_data
Parameters: an inputed string with a choosen filename and the all_houses 2D 
            array
Purpose: opens and closes an inputed file if the file exists. fills the 
         all_houses 2D array with collected data from the file via a loop.
Returns: true or false
*/
bool read_all_house_data(string filename, House all_houses[ROWS][COLS])
{
    ifstream input_file;
    input_file.open(filename);
    
    if (not input_file.is_open()) {
        cerr << "fileread.cpp: could not open file: " << filename << endl;
        return false;
    } 
    
    int numhouses;
    input_file >> numhouses;
    
    House temporary;
    int rows;
    int cols;
    
    for (int i = 0; i < numhouses; i++) {
        temporary = read_one_house(input_file);
        
        cols = col_from_lot(temporary.lot_code);
        rows = row_from_lot(temporary.lot_code);
        
        all_houses[rows][cols] = temporary;
    } 
    
    input_file.close();
    return true;
}


/* 
user_input
Parameters: all_houses 2D array
Purpose: takes in users row and column of choice and collects the data from 
         the the filled 2D array in the selected row and column and prints it
Returns: nothing
*/
void user_input(House all_houses[ROWS][COLS])
{
    bool value = true;
    int row;
    int col;
    
    while (value) {
        cout << "Enter row: ";
        cin >> row;
        if (row < 0) {
            value = false;
        } else if (row >= 0) {
            cout << "Enter col: ";
            cin >> col;
        }
        
        if (all_houses[row][col].no_house_here == true) {
            cout << "No house" << endl;
        } else if (all_houses[row][col].no_house_here == false) {
            print_house(all_houses[row][col]);
        }
    }
}


/* 
is_available
Parameters: inputed integer containg house_id of choice and all_houses 2D array 
Purpose: this function checks to see if the inputted house_id is available. It 
         returns true if it's available, and false otherwise. Of course, if 
         there's no house with a given ID, then that's considered unavailable,
         too
Returns: true or false
*/
bool is_available(int house_id, House all_houses[ROWS][COLS])
{    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (house_id == all_houses[i][j].id) {
                if (all_houses[i][j].availability == "available") {
                    return true;
                } 
            } 
        }
    } 
    return false;
}


/* 
matching_houses
Parameters: inputed float with max price, string of desired color, integer
            of number of bedrooms. the all_houses 2D array and a 1D array 
            to fill with matching houses
Purpose: this function goes through the housing array and finds every house 
         that matches the price, color, and bedroom specifications that are 
         inputted. It copies each matching house into the results array. The
         first match goes into slot 0, the second into slot 1, etc. The houses 
         must be put into the array in "row major" order: that is, if houses
         A1, A2, B1, and B2 all match, then the correct order in the results 
         array is: A1, B1, A2, B2. When it is done, it returns the number of 
         matching houses that were stored in the array. (The caller then knows 
         how many slots in the array contain houses that match the query.)
Returns: integer with the size of the 1D array
*/
int matching_houses(float max_price, string desired_color,
                    int desired_bedrooms, House all_houses[ROWS][COLS],
                    House results[ROWS * COLS])
{    
    int size = 0;
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            
            if ((max_price >= all_houses[i][j].price) and
                (desired_color == all_houses[i][j].color) and
                (desired_bedrooms <= all_houses[i][j].bedrooms)) {
                    
                results[size] = all_houses[i][j];
                size++;
            }
        }
    }
    return size;
}


/* 
num_neighbors
Parameters: inputed integer containg house_id of choice and all_houses 2D array
Purpose: this function counts how many neighbors the given house_id has and
         returns the number of neighbors. A neighbor is an occupied house 
         within 1 lot of the given house in the grid, either to the right, 
         left, top, bottom, or diagonally. (The most neighbors you can have is 
         therefore 8 if all of the houses around your house are rented.) If 
         there is no house with the given ID, then there are 0 neighbors. 
         (The fuction does NOT print anything: it just returns 0.)
Returns: the integer of number of neighbors
*/
int num_neighbors(int house_id, House all_houses[ROWS][COLS])
{
    string collectcode;
    int row, col;
    int neighbors = 0;
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (house_id == all_houses[i][j].id) {
                collectcode = all_houses[i][j].lot_code;
            }
        }
    }
    col = col_from_lot(collectcode);
    row = row_from_lot(collectcode);
    
    if (all_houses[row + 1][col + 1].availability == "booked") {
        neighbors++;
    } if (all_houses[row][col + 1].availability == "booked") {
        neighbors++;
    } if (all_houses[row + 1][col].availability == "booked") {
        neighbors++;
    } if (all_houses[row + 1][col - 1].availability == "booked") {
        neighbors++;
    } if (all_houses[row][col - 1].availability == "booked") {
        neighbors++;
    } if (all_houses[row - 1][col - 1].availability == "booked") {
        neighbors++;
    } if (all_houses[row - 1][col].availability == "booked") {
        neighbors++;
    } if (all_houses[row - 1][col + 1].availability == "booked") {
        neighbors++;
    } return neighbors;
}


/* 
rent_house
Parameters: inputed integer containg house_id of choice and all_houses 2D array
Purpose: this function attempts to rent a house. If the given house does not 
         exist, it returns 0. If the given house exists and is available, the
         function updates the House structure to record that the house is 
         booked and returns 1. If the given house exists but is unavailable, 
         the function returns 2
Returns: returns 1, 2, or 3
*/
int rent_house(int house_id, House all_houses[ROWS][COLS])
{    
    int x;
    int y;
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (house_id == all_houses[i][j].id) {
                x = i;
                y = j;
            }
        }
    }
    
    if (all_houses[x][y].availability == "available") {
        all_houses[x][y].availability = "booked";
        return 1;
    } else if (all_houses[x][y].availability == "booked") {
        return 2;
    } else {
        return 0;
    } 
} 


/* 
run_command_loop
Parameters: all_houses 2D array
Purpose: performs a do while loop to basically open a query window and gives 
         users options to either check if a house is available, find a houses
         based on their wants, number of neighbors at a certain house, and 
         to actually rent a house all using the handler functions.
Returns: nothing
*/
void run_command_loop(House all_houses[ROWS][COLS])
{    
    char command;
    
    do {
        cout << "query-> ";
        cin >> command;
        
        if (command == 'a') {
            handle_is_available(all_houses);
        } else if (command == 'm') {
            handle_matching_houses(all_houses); 
        } else if (command == 'n') {
            handle_num_neighbors(all_houses);
        } else if (command == 'r') {
            int renthouse = handle_rent_houses(all_houses);
            if (renthouse == 1) {
                return;
            }
        } else if (command != 'a' or command != 'm' or command != 'n' or
                   command != 'r' or command != 'q') {
            cout << "Unknown command " << command << endl;           
        }
    } while (command != 'q');
} 


/* 
handle_is_available
Parameters: all_houses 2D array
Purpose: takes the returned value from is_available function and prints the 
         information that the house is available or is not available
Returns: nothing
*/
void handle_is_available(House all_houses[ROWS][COLS])
{
    bool available;
    int input;
    
    cin >> input;
    
    available = is_available(input, all_houses);
    
    if (available == true) {
        cout << "House " << input << " is available" << endl;
    } else if (available == false) {
        cout << "Sorry, House " << input << " is not available" << endl;
    } 
}


/* 
handle_matching_houses
Parameters: all_houses 2D array
Purpose: takes the returned value from mathcing_houses function and performs a 
         loop less than the value of of the returned ineger. In the loop, a 
         temporary array takes the stored data and sends it to the print_house
         function.
Returns: nothing
*/
void handle_matching_houses(House all_houses[ROWS][COLS]) 
{
    House temp[ROWS * COLS];
    float mprice;
    string dcolor;
    int bed;
    
    cin >> mprice;
    cin >> dcolor;
    cin >> bed;
    
    int getsize = matching_houses(mprice, dcolor, bed, all_houses, temp);
    
    for (int i = 0; i < getsize; i++) {
        print_house(temp[i]);
    }
}


/* 
handle_num_neighbors
Parameters: all_houses 2D array
Purpose: takes the returned value from num_neighbors function and prints it out 
         in between a pair of strings.
Returns: nothing
*/
void handle_num_neighbors(House all_houses[ROWS][COLS]) 
{
    int input; 
    cin >> input;
    
    int neighs = num_neighbors(input, all_houses);
    
    cout << "You have " << neighs << " neighbors!" << endl;
}


/* 
handle_rent_houses
Parameters: all_houses 2D array
Purpose: takes the returned value from rent_houses function and performs 
         conditionals with that returned value and prints out specific
         strings depending on the returned value
Returns: returned value from rent_house function
*/
int handle_rent_houses(House all_houses[ROWS][COLS]) 
{
    int input;
    cin >> input;
    
    int conclusion = rent_house(input, all_houses);
    
    if (conclusion == 1) {
        cout << "Congrats, you rented a house! Hope your door knobs don't";
        cout << " fall off" << endl;
    } else if (conclusion == 2) {
        cout << "Too late...I hear the dumpster behind hill has some open";
        cout << " spaces" << endl;
    } else if (conclusion == 0) {
        cout << "You can't rent a house that doesn't exist, but good try";
        cout << endl;
    }
    return conclusion;
} 
