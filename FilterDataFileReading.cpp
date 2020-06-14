
/***********************************************************************
* Program:
*    Assignment 03, DIGITAL FORENSICS  
*    Brother MacBeth, CS165
* Author:
*    Filipe Ferreira
* Summary: 
*    This assigment will be responsible for taking information
*    from a file and storing it into an array in a struct
*    it will display the information based on the input of the user
*    Estimated:  4.0 hrs   
*    Actual:     3.5 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctype.h>

using namespace std;

//Max number of lines 
#define MAX_LINES 500
#define TIME_WINDOW 2

//The model of struct to hold given info
struct Info
{
   string files;
   string names;
   long timeStamp;
};

/**********************************************************************
* Prompt the user for the file's name
**********************************************************************/
void getFileNames(string &fileName)
{
   cout << "Enter the access record file: ";
   cin >> fileName;
}

/**********************************************************************
* This Fuction check for the codition and throw the error message
**********************************************************************/
void parseline(const string &lineRead, Info &data)
{
   stringstream ss;
   ss.str(lineRead);

   //Assign the item to the struct types
   ss >> data.files;
   ss >> data.names;
   ss >> data.timeStamp;

   //Check for the codition and throw anything that is an exception
   if (ss.fail())
   {
      throw string("Error parsing line: ");
   }
   
   if (data.timeStamp < 1000000000 or
       data.timeStamp > 10000000000)
   {
      throw string("Error parsing line: ");
   }
    
}

/**********************************************************************
* This Fuction will read the file into our array of structs
*********************************************************************/
void readFile(string &fileName, Info data[], int &lines)
{
   string lineRead;

   ifstream fin(fileName);
   
   //A message will be display in case the fail does not open
   if (fin.fail())
   {
      cout << "Error reading the file " << fileName << endl;
           
      cout << "Please re-enter the file: ";
      cin  >> fileName;
      
      readFile(fileName, data, lines);
   }
      
   //The conditions is set to read the file until its true
   while (getline(fin,lineRead))
   {
      //Check for exception and disply a Error Message
      try
      {
         parseline(lineRead, data[lines]);
         lines++;
      }
      catch (const string &text)
      {
         cout <<  text << lineRead << endl;
      }
   }

   fin.close();

   cout << endl;
}

/**********************************************************************
* This fuction will get the information on the time Window
**********************************************************************/
void getTimeWindow(long timeWindow[])
{
   cout << "Enter the start time: ";
   cin  >> timeWindow[0];
   cout << "Enter the end time: ";
   cin  >> timeWindow[1];
   cout << endl;
}

/**********************************************************************
* This function will loop throgh the information and display the
* the ones that are beetwin the time window
**********************************************************************/
void display(const Info data[], const long timeWindow[],
             const int lines)
{
   //The Headers for the information
   cout << "The following records match your criteria:\n" << endl; 
   cout << setw(15) << "Timestamp" << setw(20) << "File"
        << setw(20) << "User" << endl;
   cout << "--------------- ------------------- -------------------\n";

   //This loop will determine the 
   for (int i = 0; i < lines; i++)
   {
      if (data[i].timeStamp > timeWindow[0]
          && data[i].timeStamp < timeWindow[1])
      {
         cout << setw(15) << data[i].timeStamp
              << setw(20) << data[i].files << setw(20)
              << data[i].names << endl;
      }
   }
   cout << "End of records\n"; 
}

/**********************************************************************
* This is out driven fuction where all will start
**********************************************************************/
int main()
{
   //Our struct that will hold the information
   Info data[MAX_LINES];

   string fileName;
   int lines = 0; //The numbers of lines read from the file
   long timeWindow[TIME_WINDOW];

   //Here we get our file Name
   getFileNames(fileName);
   readFile(fileName, data, lines);
   getTimeWindow(timeWindow);
   display(data, timeWindow,lines);

   return 0;
}


