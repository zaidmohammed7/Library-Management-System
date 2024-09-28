/****************************
 * Project 1: Library Management System
 *
 * Course: CS 251, Fall 2023
 * System: WindowsOS using VSCode
 * Program Language: C++
 * Student Author: Zaid Khan Mohammed
 * *** **********************/

// Run the program and follow on screen prompts to browse the library!

//including libraries   
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

// Function declarations
void removeExtraWhitespace(string& text);
void printMenu();
void addItem(vector<string>& bookTitles, vector<string>& bookISBNs, vector<int>& booksCheckoutStats, const string& bookTitle, const string& bookISBN, int bookCheckoutStatus);
void displayLibrary(const vector<string>& bookTitles, const vector<string>& bookISBNs, const vector<int>& booksCheckoutStats);
void clearLibrary(vector<string>& bookTitles, vector<string>& bookISBNs, vector<int>& booksCheckoutStats);
void loadFromFile(vector<string>& bookTitles, vector<string>& bookISBNs, vector<int>& booksCheckoutStats,const string& filename);
void outputToFile(const vector<string>& bookTitles,const vector<string>& bookISBNs,const vector<int>& booksCheckoutStats, const string& filename);
void printCheckoutStats(const vector<int>& booksCheckoutStats);
void searchLibrary(const vector<string>& bookTitles,const vector<string>& bookISBNs,const vector<int>& booksCheckoutStats);
void removeEntry(vector<string>& bookTitles, vector<string>& bookISBNs, vector<int>& booksCheckoutStats);
void printInvalid(const vector<string>& bookTitles,const vector<string>& bookISBNs,const vector<int>& booksCheckoutStats);


int main()
{
    //declaring variables
    string command;
    vector<string> bookTitles;
    vector<string> bookISBNs;
    vector<int> booksCheckoutStats;
    string bookTitle;
    string bookISBN;
    string filename;
    int bookCheckoutStatus;

    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;
    do 
    {
        // Output the menu and acquire a user selection
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";
        getline(cin, command);
        cout << endl;
        // Carrying out task defined by user
        if (command=="a" || command=="A"){
            cout<<"What is the book title? ";
            getline(cin,bookTitle);
            cout<<endl;
            if (bookTitle.find(',')!=string::npos){
                cout<<"The book title cannot contain commas.\n"<<endl;
                continue;
            }
            cout<<"What is the 13-digit ISBN (with hyphens)? ";
            getline(cin,bookISBN);
            cout<<endl;
            addItem(bookTitles,bookISBNs,booksCheckoutStats,bookTitle,bookISBN,0);
            cout<<"The Following Entry Was Added\n-----------------------------\n";
            cout<<bookTitle<<" --- "<<bookISBN<<" --- "<<"In Library"<<endl;
        }
        else if (command=="d" || command=="D"){
            displayLibrary(bookTitles,bookISBNs,booksCheckoutStats);
        }
        else if (command=="c" || command=="C"){
            clearLibrary(bookTitles,bookISBNs,booksCheckoutStats);
        }
        else if (command=="l" || command=="L"){
            cout<<"What database to read from? ";
            getline(cin,filename);
            cout<<endl;
            loadFromFile(bookTitles,bookISBNs,booksCheckoutStats,filename);
        }
        else if (command=="o" || command=="O"){
            cout<<"Where should the database output to? ";
            getline(cin,filename);
            cout<<endl;
            outputToFile(bookTitles,bookISBNs,booksCheckoutStats,filename);
        }
        else if (command=="p" || command=="P"){
            printCheckoutStats(booksCheckoutStats);
        }
        else if (command=="s" || command=="S"){
            searchLibrary(bookTitles,bookISBNs,booksCheckoutStats);
        }
        else if (command=="r" || command=="R"){
            removeEntry(bookTitles,bookISBNs,booksCheckoutStats);
        }
        else if (command=="i" || command=="I"){
            printInvalid(bookTitles,bookISBNs,booksCheckoutStats);
        }
        else if(command!="x" && command!="X"){
            cout<<"Unknown command."<<endl;
        }

        cout << endl;
    } while (!(command == "x" || command == "X"));

    return 0;
}

//Function definitions

// Remove all leading and trailing whitespace
void removeExtraWhitespace(string& text){
    int start=0; // Stores index of first non-whitespace character
    int end=text.size()-1; // Stores index of last non-whitespace character
    for (int i=0;i<text.size();++i){
        if (!isspace(text[i])){
            start=i;
            break;
        }
    }
    for (int i=0;i<text.size();++i){
        if (!isspace(text[i])){
            end=i;
        }
    }
    text=text.substr(start,end-start+1);
}


// Print out the main menu of the management system
void printMenu()
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;    
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;    
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;      
    cout << "S - Search For A Library Entry" << endl;    
    cout << "X - Exit Program" << endl;
}


// Add entry to library
void addItem(vector<string>& bookTitles, vector<string>& bookISBNs, vector<int>& booksCheckoutStats, const string& bookTitle, const string& bookISBN, int bookCheckoutStatus){
    // Push required book data to end of library vectors
    bookTitles.push_back(bookTitle);
    bookISBNs.push_back(bookISBN);
    booksCheckoutStats.push_back(bookCheckoutStatus);
}


// Display all books in library
void displayLibrary(const vector<string>& bookTitles, const vector<string>& bookISBNs, const vector<int>& booksCheckoutStats){
    vector<string> checkoutStatusText={"In Library","Checked Out","On Loan","Unknown State"}; // Useful for interpreting checkout status
    cout<<"Your Current Library\n--------------------\n";
    if (bookTitles.size()==0){
        cout<<"The library has no books."<<endl;
        return;
    }
    // Iterating through entire library and printing all entries
    for (int i=0;i<bookTitles.size();++i){
        if (booksCheckoutStats.at(i)<0 || booksCheckoutStats.at(i)>3){
            cout<<bookTitles.at(i)<<" --- "<<bookISBNs.at(i)<<" --- "<<"Invalid State"<<endl; // Printing appropriate message for invalid checkout status
        }
        else{
            cout<<bookTitles.at(i)<<" --- "<<bookISBNs.at(i)<<" --- "<<checkoutStatusText.at(booksCheckoutStats.at(i))<<endl;
        }
    }
}


// Deleting all entries from library
void clearLibrary(vector<string>& bookTitles, vector<string>& bookISBNs, vector<int>& booksCheckoutStats){
    int vecSize=bookTitles.size();
    for (int i=0;i<vecSize;++i){
        bookTitles.pop_back();
        bookISBNs.pop_back();
        booksCheckoutStats.pop_back();
    }
    cout<<"Your library is now empty."<<endl;
}


// Reading new entries from a file
void loadFromFile(vector<string>& bookTitles, vector<string>& bookISBNs, vector<int>& booksCheckoutStats,const string& filename){
    string line;
    string bookTitle;
    string bookISBN;
    int bookCheckoutStatus;
    int numLines=0;
    ifstream inFS(filename);
    //inFS.open(filename);
    if (!inFS.is_open()){ // Checking if file was opened successfully
        cout<<"Could not find the database file."<<endl;
        return;
    }
    while (!inFS.eof()){
        // Setting default values
        bookISBN="000-0-00-000000-0";
        bookCheckoutStatus=0;
        getline(inFS,line);
        int commaIndex=line.find(',');
        if (commaIndex==string::npos){
            bookTitle=line; // If book ISBN and checkout status was not given 
        }
        else {
            bookTitle=line.substr(0,commaIndex);
            string lineTemp=line.substr(commaIndex+2,line.size()-commaIndex-2);
            int commaIndex2=lineTemp.find(',');
            if (commaIndex2==string::npos){
                bookISBN=lineTemp; // If book checkout status was not given
            }
            else{
                bookISBN=lineTemp.substr(0,commaIndex2);
                bookCheckoutStatus=lineTemp.at(commaIndex2+2)-48; // Converting char to int
            }
        }
        // Removing leading and trailing whitespace before adding data to library
        removeExtraWhitespace(bookTitle);
        removeExtraWhitespace(bookISBN);
        addItem(bookTitles,bookISBNs,booksCheckoutStats,bookTitle,bookISBN,bookCheckoutStatus); // Adding entry
        ++numLines;
    }
    cout<<"Read in "<<numLines<<" lines from the file."<<endl;
    inFS.close();
}


// Printing library data to another file
void outputToFile(const vector<string>& bookTitles,const vector<string>& bookISBNs,const vector<int>& booksCheckoutStats,const string& filename){
    int numLines=0;
    ofstream outFS; // File stream object
    outFS.open(filename);
    // Iterating through library and writing all entries to file
    for (int i=0;i<bookTitles.size();++i){
        outFS<<bookTitles.at(i)<<", "<<bookISBNs.at(i)<<", "<<booksCheckoutStats.at(i)<<endl;
        ++numLines;
    }
    cout<<numLines<<" lines of data written to output.csv"<<endl;
    outFS.close();
}


// Printing all book's checkout stats
void printCheckoutStats(const vector<int>& booksCheckoutStats){
    int inLibrary=0;
    int checkedOut=0;
    int onLoan=0;
    int unknown=0;
    int other=0;
    cout<<"Your Current Library's Stats\n----------------------------"<<endl;
    cout<<"Total Books: "<<booksCheckoutStats.size()<<endl;
    // Iterating through library and counting all checkout stats
    for (int i=0;i<booksCheckoutStats.size();++i){
        if (booksCheckoutStats.at(i)==0){
            ++inLibrary;
        }
        else if(booksCheckoutStats.at(i)==1){
            ++checkedOut;
        }
        else if(booksCheckoutStats.at(i)==2){
            ++onLoan;
        }
        else if(booksCheckoutStats.at(i)==3){
            ++unknown;
        }
        else{
            ++other;
        }
    }
    // Printing data
    cout<<"   In Library: "<<inLibrary<<endl;
    cout<<"   Checked Out: "<<checkedOut<<endl;
    cout<<"   On Loan: "<<onLoan<<endl;
    cout<<"   Unknown: "<<unknown<<endl;
    cout<<"   Other: "<<other<<endl;
}


// Search library for specific entry
void searchLibrary(const vector<string>& bookTitles,const vector<string>& bookISBNs,const vector<int>& booksCheckoutStats){
    string userChoice;
    int matchIndex=-1; // Setting default value to know if any match was found
    vector<string> checkoutStatusText={"In Library","Checked Out","On Loan","Unknown State"};
    cout<<"Would you like to search by (1) name or (2) ISBN.\nEnter the numeric choice: ";
    getline(cin,userChoice);
    cout<<endl;
    if (userChoice!="1" && userChoice!="2"){
        cout<<"Invalid search by choice option."<<endl;
        return;
    }
    if (userChoice=="1"){
        cout<<"Enter the book name: ";
        string bookTitle;
        getline(cin,bookTitle);
        cout<<endl;
        // Searching library for book and storing index of last found instance
        for (int i=0;i<bookTitles.size();++i){
            if (bookTitles.at(i)==bookTitle){
                matchIndex=i;
            }
        }
    }
    else if (userChoice=="2"){
        cout<<"Enter the book 13-digit ISBN (with dashes): ";
        string bookISBN;
        getline(cin,bookISBN);
        cout<<endl;
        // Searching library for book and storing index of last found instance
        for (int i=0;i<bookISBNs.size();++i){
            if (bookISBNs.at(i)==bookISBN){
                matchIndex=i;
            }
        }
    }
    cout<<"The Following Are Your Search Results\n-------------------------------------"<<endl;
    if (matchIndex==-1){
        cout<<"No matching entry found in the library."<<endl;
        return;
    }
    else{
        // Printing matching book's data
        if (booksCheckoutStats.at(matchIndex)<0 || booksCheckoutStats.at(matchIndex)>3){
            cout<<bookTitles.at(matchIndex)<<" --- "<<bookISBNs.at(matchIndex)<<" --- "<<"Invalid State"<<endl;
        }
        else{
            cout<<bookTitles.at(matchIndex)<<" --- "<<bookISBNs.at(matchIndex)<<" --- "<<checkoutStatusText.at(booksCheckoutStats.at(matchIndex))<<endl;
        }
    }
}


// Remove specific entry from library
void removeEntry(vector<string>& bookTitles, vector<string>& bookISBNs, vector<int>& booksCheckoutStats){
    string userChoice;
    int matchIndex=-1;
    vector<string> checkoutStatusText={"In Library","Checked Out","On Loan","Unknown State"};
    cout<<"Would you like remove by (1) name or (2) ISBN.\nEnter the numeric choice: ";
    getline(cin,userChoice);
    cout<<endl;
    if (userChoice!="1" && userChoice!="2"){
        cout<<"Invalid remove by choice option."<<endl;
        return;
    }
    if (userChoice=="1"){
        cout<<"Enter the book name: ";
        string bookTitle;
        getline(cin,bookTitle);
        cout<<endl;
        // Searching for book
        for (int i=0;i<bookTitles.size();++i){
            if (bookTitles.at(i)==bookTitle){
                matchIndex=i;
            }
        }
    }
    else if (userChoice=="2"){
        cout<<"Enter the book 13-digit ISBN (with dashes): ";
        string bookISBN;
        getline(cin,bookISBN);
        cout<<endl;
        // Searching for book
        for (int i=0;i<bookISBNs.size();++i){
            if (bookISBNs.at(i)==bookISBN){
                matchIndex=i;
            }
        }
    }
    cout<<"The Following Entry Was Removed From The Library\n------------------------------------------------"<<endl;
    if (matchIndex==-1){
        cout<<"No matching entry found in the library."<<endl;
        return;
    }
    else{
        // Storing book data to print after removal
        string bookTitle=bookTitles.at(matchIndex);
        string bookISBN=bookISBNs.at(matchIndex);
        int bookCheckoutStatus=booksCheckoutStats.at(matchIndex);
        // Actually removing the book
        bookTitles.erase(bookTitles.begin()+matchIndex);
        bookISBNs.erase(bookISBNs.begin()+matchIndex);
        booksCheckoutStats.erase(booksCheckoutStats.begin()+matchIndex);
        // Printing removed book's data
        if (bookCheckoutStatus<0 || bookCheckoutStatus>3){
            cout<<bookTitle<<" --- "<<bookISBN<<" --- "<<"Invalid State"<<endl;
        }
        else{
            cout<<bookTitle<<" --- "<<bookISBN<<" --- "<<checkoutStatusText.at(bookCheckoutStatus)<<endl;
        }
    }
}


// Printing any invalid library entries
void printInvalid(const vector<string>& bookTitles,const vector<string>& bookISBNs,const vector<int>& booksCheckoutStats){
    vector<string> checkoutStatusText={"In Library","Checked Out","On Loan","Unknown State"};
    cout<<"The Following Library Entries Have Invalid Data\n-----------------------------------------------"<<endl;
    // Checking if library has books
    if (bookTitles.size()==0){
        cout<<"The library has no books."<<endl;
        return;
    }
    int numInvalid=0;
    // Iterating through entire library searching for invalid entries
    for (int i=0;i<bookTitles.size();++i){
        if (booksCheckoutStats.at(i)<0 || booksCheckoutStats.at(i)>3){ // Case 1: Invalid checkout status
            // Printing entry's data 
            if (booksCheckoutStats.at(i)<0 || booksCheckoutStats.at(i)>3){
                cout<<bookTitles.at(i)<<" --- "<<bookISBNs.at(i)<<" --- "<<"Invalid State"<<endl;
            }
            else{
                cout<<bookTitles.at(i)<<" --- "<<bookISBNs.at(i)<<" --- "<<checkoutStatusText.at(booksCheckoutStats.at(i))<<endl;
            }
            ++numInvalid;
        }
        else{
            if (bookISBNs.at(i).size()!=17){ // Case 2: Incorrect number of characters/digits in book ISBN 
                // Printing entry's data
                if (booksCheckoutStats.at(i)<0 || booksCheckoutStats.at(i)>3){
                cout<<bookTitles.at(i)<<" --- "<<bookISBNs.at(i)<<" --- "<<"Invalid State"<<endl;
                }
                else{
                    cout<<bookTitles.at(i)<<" --- "<<bookISBNs.at(i)<<" --- "<<checkoutStatusText.at(booksCheckoutStats.at(i))<<endl;
                }
                ++numInvalid;
            }
            else{// Checking if all 12 digits correctly calculate 13th digit of boom ISBN
                // Storing all digits in book ISBN in separate variables 
                int num1=bookISBNs.at(i).at(0)-48;
                int num2=bookISBNs.at(i).at(1)-48;
                int num3=bookISBNs.at(i).at(2)-48;
                int num4=bookISBNs.at(i).at(4)-48;
                int num5=bookISBNs.at(i).at(6)-48;
                int num6=bookISBNs.at(i).at(7)-48;
                int num7=bookISBNs.at(i).at(9)-48;
                int num8=bookISBNs.at(i).at(10)-48;
                int num9=bookISBNs.at(i).at(11)-48;
                int num10=bookISBNs.at(i).at(12)-48;
                int num11=bookISBNs.at(i).at(13)-48;
                int num12=bookISBNs.at(i).at(14)-48;
                int num13=bookISBNs.at(i).at(16)-48;
                int checkDigit=10-((num1+3*num2+num3+3*num4+num5+3*num6+num7+3*num8+num9+3*num10+num11+3*num12)%10); // Calculating weighted sum and check digit
                if (checkDigit==10){ // Edge case when weighted sum is 0 and checkDigit=10
                    checkDigit=0;
                }
                if (checkDigit!=num13){
                    // Printing entry's data if invalid book ISBN
                    if (booksCheckoutStats.at(i)<0 || booksCheckoutStats.at(i)>3){
                        cout<<bookTitles.at(i)<<" --- "<<bookISBNs.at(i)<<" --- "<<"Invalid State"<<endl;
                    }
                    else{
                        cout<<bookTitles.at(i)<<" --- "<<bookISBNs.at(i)<<" --- "<<checkoutStatusText.at(booksCheckoutStats.at(i))<<endl;
                    }
                    ++numInvalid;
                }
            }
        }
    }
    if (numInvalid==0){
        cout<<"The library has no invalid entries."<<endl;
    }
}
