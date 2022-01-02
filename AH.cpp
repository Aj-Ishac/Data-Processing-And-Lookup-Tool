#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct Records {

    string name;
    //string productID;
    float price = 0;
    int quantity = 0;

};

void printVector(vector<Records>);
void MenuController(vector<Records>&);
void printMainMenu(vector<Records>);
void printHistorySeq(vector<string>&);
void outputTable(vector<Records>);

void SortByName(vector<Records>&, vector<string>&, string, bool&, bool&);
void quicksort(vector<Records>&, bool, bool, bool&);
void SortByPrice(vector<Records>&, vector<string>&, string);
void SortByQuantity(vector<Records>&, vector<string>&, string);

void InsertElement(vector<Records>&, vector<string>&);
void ModifyElement(vector<Records>&, vector<string>&);
void RemoveElement(vector<Records>&, vector<string>&);

void Search(vector<Records>, vector<string>&);
int BinarySearch(vector<Records>, int, int, string);

bool isdigitCheck(string);
bool isalphaCheck(string);
void CapacityCheck(vector<Records>);

//void GenerateProductID(vector<Records>&, vector<string>&);
//string GenerateKEY(string);

void ImportFile(vector<Records>&, vector<string>&);
void MergeVectors(vector<Records>&, vector<Records>);
void removeDuplicates(vector<Records>&, vector<string>&);

/*
The project is designed to compile data fed to the program to process, sort, and present records of inventory items.
The project imports an initial third party data "basefile.txt" allowing for the following data manipulation processes:

 1. Sort By: Name/Price/Quantity
 2. Element: Insert/Modify/Remove
 3. Search Element
 4. Import and Merge File
 5. Check for Duplicates
 6. Output Records on File

The following functions use BinarySearch for O(nlogn) time complexity 
and as such require the data to be sorted by name at least once:

 Modify Element
 Remove Element
 Search Element
 Check for Duplicates

When SortbyName(Ascending/Descending) is ran, the last Ascending or Descending preference will be saved for later use.
Everytime a SortbyName-dependent function is ran, a Bool check will run against the vector to confirm if it is sorted or not.

If SortbyName(Ascending/Descending) has not been run at least once before the listed events are ran, user will be prompted to do so.
If SortbyName has been run at least once and the vector currently is not sorted, 
the SortbyName(Ascending/Descending) preference will be used to sort before a SortbyName-dependent function is ran.
This is to prevent the user from needing to manually SortbyName every time the vector is modified and thus not sorted.
*/

int main()
{
    //check for choice length. invalid if it is, prevents crash

    //vector used for the base data
    vector<Records> record;

    ifstream inFile("basefile.txt");

    //throw error if file can't open
    if (!inFile)
    {
        cerr << "File cannot be opened. " << endl;
        system("PAUSE");
        exit(1);
    }

    //file -> struct input -> vector
    string templine;
    while (getline(inFile, templine))
    {
        Records tempV;

        inFile >> tempV.name;
        inFile >> tempV.price;
        inFile >> tempV.quantity;

        record.push_back(tempV);
    }
   
    cout << "---Base data from file-------------------" << endl;

    printVector(record);
    MenuController(record);

    inFile.close();
    return 0;
}

void MenuController(vector<Records>& record)
{  
    //Menu controller used to for the user to interface through the various functions to process and output data.

    bool Repeat = true;
    bool isSorted = false;
    bool sortedName_A = false;
    bool sortedName_D = false;
    bool invalidChoice;
    
    char choice[12];
    string Sort_Order;
    vector<string> historySeq;

    string input_diag;
    bool bool_diag;

    do {

        printMainMenu(record);
        cin >> choice;
        
        //checks if choice[] input is alphabetical.forces a try again if so
        invalidChoice = isalphaCheck(choice);
        if (invalidChoice == false)
        {
            switch (choice[0])
            {
            case '1':
                //print table:
                system("cls");

                historySeq.push_back("PrintRecords");
                printHistorySeq(historySeq);

                cout << "---Printing Records." << endl;
                printVector(record);
                break;

            case '2':

                cout << endl;
                cout << " 1. Sort by Name" << endl;
                cout << " 2. Sort by Price" << endl;
                cout << " 3. Sort by Quantity" << endl << endl;

                cout << "Input choice (1-3): ";
                cin >> choice;

                //checks if choice[] input is alphabetical. forces a try again if it is
                invalidChoice = isalphaCheck(choice);
                if (invalidChoice == false)
                {
                    
                    switch (choice[0])
                    {
                    case '1':
                        //sortbyname:
                        SortByName(record, historySeq, Sort_Order, sortedName_A, sortedName_D);
                        isSorted = true;
                        break;

                    case '2':
                        //sortbyprice:
                        SortByPrice(record, historySeq, Sort_Order);
                        isSorted = false;
                        break;

                    case '3':
                        //sortbyqty:
                        SortByQuantity(record, historySeq, Sort_Order);
                        isSorted = false;
                        break;
                    }
                }
                else
                {
                    system("cls");
                    printHistorySeq(historySeq);
                    cout << "---Invalid input. Digits valid only." << endl;
                    printVector(record);
                }
                break;

            case '3':

                cout << endl;
                cout << " 1. Insert Element" << endl;
                cout << " 2. Modify Element" << endl;
                cout << " 3. Remove Element" << endl << endl;

                cout << "Input choice (1-3): ";
                cin >> choice;


                //checks if choice[] input is alphabetical.forces a try again if so
                invalidChoice = isalphaCheck(choice);
                if (invalidChoice == false)
                {
                    switch (choice[0])
                    {
                    case '1':
                        //insertelement:
                        InsertElement(record, historySeq);
                        isSorted = false;
                        break;

                    case '2':
                        //modifyelement:
                        quicksort(record, sortedName_A, sortedName_D, isSorted);

                        if (isSorted == 0)
                        {
                            system("cls");
                            printHistorySeq(historySeq);
                            cout << "---Function requires records to be sorted by name!" << endl;
                            printVector(record);
                            break;
                        }

                        ModifyElement(record, historySeq);
                        isSorted = false;
                        break;

                    case '3':
                        //removelement:
                        quicksort(record, sortedName_A, sortedName_D, isSorted);

                        if (isSorted == 0)
                        {
                            system("cls");
                            printHistorySeq(historySeq);
                            cout << "---Function requires records to be sorted by name!" << endl;
                            printVector(record);
                            break;
                        }

                        RemoveElement(record, historySeq);
                        break;
                    }

                }
                else
                {
                    system("cls");
                    printHistorySeq(historySeq);
                    cout << "---Invalid input. Digits valid only." << endl;
                    printVector(record);
                }
                break;

            case '4':
                //search:
                quicksort(record, sortedName_A, sortedName_D, isSorted);

                if (isSorted == 0)
                {
                    system("cls");
                    printHistorySeq(historySeq);
                    cout << "---Function requires records to be sorted by name!" << endl;
                    printVector(record);

                    break;
                }

                Search(record, historySeq);
                break;

            case '5':
                //import&merge file:

                ImportFile(record, historySeq);
                isSorted = false;
                break;

            case '6':
                //duplicate check:
                quicksort(record, sortedName_A, sortedName_D, isSorted);

                if (isSorted == 0)
                {
                    system("cls");
                    printHistorySeq(historySeq);
                    cout << "---Function requires records to be sorted by name!" << endl;
                    printVector(record);

                    break;
                }

                removeDuplicates(record, historySeq);
                break;

            case '7':
                //store records on file
                outputTable(record);
                historySeq.push_back("StoreRecords");
                printVector(record);
                break;

            case '8':
                //restart:
                system("cls");
                historySeq.push_back("Restart");
                printHistorySeq(historySeq);
                printVector(record);
                break;

            case '9':
                //quit:
                cout << endl;
                return;

            default:
                system("cls");
                printHistorySeq(historySeq);
                cout << "---Invalid input." << endl;
                printVector(record);
            }
        }
        else
        {
            //if input not valid
            system("cls");
            printHistorySeq(historySeq);
            cout << "---Invalid input. Digits valid only." << endl;
            printVector(record);
        }
    } while (Repeat);
}

void printMainMenu(vector<Records> record)
{   

    cout << endl;
    cout << "    Beginning of the Menu Controller" << endl;
    cout << "-----------------------------------------" << endl;
    cout << " 1. Print Records" << endl;
    cout << " 2. Sort By: Name/Price/Quantity" << endl;
    cout << " 3. Element: Insert/Modify/Remove" << endl;
    cout << " 4. Search Element" << endl;
    cout << " 5. Import and Merge File" << endl;
    cout << " 6. Check for Duplicates" << endl;
    cout << " 7. Store Records on File" << endl;
    cout << " 8. Restart" << endl;
    cout << " 9. Quit" << endl;
    cout << "-----------------------------------------" << endl;

    cout << "Input choice (1-9): ";

}

void printVector(vector<Records> vector)
{
        cout << "---Vector.size(): " << vector.size() << endl;
        cout << "-----------------------------------------" << endl;
        cout << endl << "  -Name-       -Price-    -Qty-" << endl;
        for (int i = 0; i < (int)vector.size(); i++) {
            cout << " ";
            cout << setw(10) << left << vector[i].name.substr(0, 10) << "   ";
            cout << setw(6) << right << fixed << setprecision(2) << vector[i].price << " ";
            cout << setw(8) << right << vector[i].quantity << "   ";
            cout << endl;
        }
}

void printHistorySeq(vector<string>& historySeq)
{
    /*
    Vector of size 5 to store strings of actions user runs.
    Functions run push a string of function name onto historySeq vector.
    Prints historySeq vector contents to be used as history of actions used by the user.
    */

    //remove historySeq[0] when vector.size() reaches 5. cap size() at 5.
    if (historySeq.size() > 4)
        historySeq.erase(historySeq.begin());

    //only print history: when size() not empty
    if (historySeq.size() != 0)
    {
        cout << "History: ";

        //historySeq print
        for (int i = 0; i < (int)historySeq.size(); i++)
        {
            cout << historySeq[i] << " >> ";
        }

        cout << endl;
        cout << "-----------------------------------------" << endl;
    }        
    //deallocate excess memory down to vector size()
    historySeq.shrink_to_fit();
    cout << endl;
}

void outputTable(vector<Records> vector)
{
    //output current iteration of the base data table into a filename.txt of the user's choice. 

    string filename;
    cout << endl << "Input file name to store records (filename.txt): ";
    cin >> filename;

    system("cls");
    ofstream outputFile;
    outputFile.open(filename);
    outputFile << "[" << filename << "]" << endl;

        outputFile << "---Vector.size(): " << vector.size() << endl;
        outputFile << "---vector.capacity(): " << vector.capacity() << endl;
        outputFile << "-----------------------------------------" << endl;
        outputFile << endl << "  -Name-       -Price-    -Qty-" << endl;
        for (int i = 0; i < (int)vector.size(); i++) {
            outputFile << " ";
            outputFile << setw(10) << left << vector[i].name << "   ";
            outputFile << setw(6) << right << fixed << setprecision(2) << vector[i].price << " ";
            outputFile << setw(8) << right << vector[i].quantity << "   ";
            outputFile << endl;
        }

        cout << "---Records have been stored under " << filename << ". " << endl;

        outputFile.close();
} 

void MergeVectors(vector<Records>& vector1, vector<Records> vector2)
{
    //reserve memory for vector merge and insert vector2 at the back of vector1
    vector1.reserve(vector1.size() + vector2.size());
    vector1.insert(vector1.end(), vector2.begin(), vector2.end());

    cout << endl << "---Merged Data Table" << endl;
    printVector(vector1);
}

void ImportFile(vector<Records>& record, vector<string>& historySeq)
{
    /*
    Prompts user to input filename.txt of the file to merge with the base data table.
    Checks if filename.txt exists, prompts error if not.
    Reads the data from filename.txt into a tempV and pushes to local tempVector.
    Calls MergeVectors(record, tempVector) that reserves memory of record.size() tempVector.size()
    Releases memory from tempVector.
    */

    vector<Records> tempVector;
    string filename;

    cout << endl << "Import (filename.txt): ";
    cin >> filename;
        
    system("cls");
    historySeq.push_back("Import&Merge");
    printHistorySeq(historySeq);

    ifstream inFile;
    inFile.open(filename);

    if (!inFile.is_open())
    {
        cerr << "---File cannot be opened. " << endl;
        printVector(record);
        return;
    }
    
    string templine;
    while (getline(inFile, templine))
    {
        Records tempV;

        inFile >> tempV.name;
        inFile >> tempV.price;
        inFile >> tempV.quantity;

        tempVector.push_back(tempV);
    }
    
    cout << "---Base Data Table" << endl;
    printVector(record);

    cout << endl << "---Imported Data Table" << endl;
    printVector(tempVector);

    MergeVectors(record, tempVector);
    cout << "-----------------------------------------" << endl;

    inFile.close();    
    tempVector.clear();
    tempVector.shrink_to_fit();

    return;
}

void Search(vector<Records> record, vector<string>& historySeq)
{
    /*
    Requires vector to be SortbyName at least once in the program's lifetime, else prompts user to do so.
    Prompts user to input name to lookup through the vector.
    If ValueLookup exists, prints index # and [name:price:quantity] of the search name.
    */

    string ValueLookup;
    cout << endl << "Search Name: ";
    cin >> ValueLookup;

    int index = BinarySearch(record, 0, record.size(), ValueLookup);

    if(index > -1)
    {

        system("cls");

        historySeq.push_back("Search");
        printHistorySeq(historySeq);

        cout << "---Index of " << index << ": ["
            << record[index].name << ":"
            << record[index].price << ":"
            << record[index].quantity << "] " << endl;

        printVector(record);
       
    }
}

int BinarySearch(vector<Records> record, int low, int high, string ValueLookup)
{
    if (record[0].name < record[1].name)
    {
        //if sorted in ascending order
        if (low <= high)
        {
            int mid = (low + high) / 2;
            if (ValueLookup == record[mid].name)
                return mid;

            if (ValueLookup < record[mid].name)
                return BinarySearch(record, low, mid - 1, ValueLookup);
            if (ValueLookup > record[mid].name)
                return BinarySearch(record, mid + 1, high, ValueLookup);
        }
    }
    else
    {
        //if sorted in descending order
        if (low <= high)
        {
            int mid = (low + high) / 2;
            if (ValueLookup == record[mid].name)
                return mid;
            
            if (ValueLookup > record[mid].name)
                return BinarySearch(record, low, mid - 1, ValueLookup);
            if (ValueLookup < record[mid].name)
                return BinarySearch(record, mid + 1, high, ValueLookup);
        }
    }

    system("cls");
    cout << "---Failed to find input. " << endl;
    printVector(record);
    return -1;
}

/*string GenerateKEY(string NameToID)
{
    string EncodedID;
    int CharsToEncode_Above4[5];
    int CharsToEncode_Below4[3];
    int DashCounterFront = 0;
    int DashCounterBack = 0;

    //defining characters extracted to be used as ID
    //0, 1, (length()/2), (length-1) , (length-2)
    
    //if string name greater than 4 characters
    CharsToEncode_Above4[0] = NameToID[0];
    CharsToEncode_Above4[1] = NameToID[1];
    CharsToEncode_Above4[2] = NameToID[NameToID.length() / 2];
    CharsToEncode_Above4[3] = NameToID[NameToID.length() - 2];
    CharsToEncode_Above4[4] = NameToID[NameToID.length() - 1];

    //if string name less than 4 characters
    CharsToEncode_Below4[0] = NameToID[0];
    CharsToEncode_Below4[1] = NameToID[NameToID.length() / 2];
    CharsToEncode_Below4[2] = NameToID[NameToID.length() - 1];

    //KEY CODE

    //a-z -> (38-64)
    //if even - return values (51-64) 
    //encode: string -> (int / 2) + 3
    //decode: int (48-61)*2 - 3 -> string
    //if odd - return values (38-50)
    //encode: string -> (int / 2) - 10
    //decode: int [(((38-50)+10)*2)+1] -> string
    //A-Z -> (65-90)

    for (int j = 0; j < 5; j++)
    {
        if (CharsToEncode_Above4[j] % 2 == 0)
        {
            CharsToEncode_Above4[j] = ((CharsToEncode_Above4[j] / 2) + 3);
        }
        else
        {
            CharsToEncode_Above4[j] = ((CharsToEncode_Above4[j] / 2) - 10);
        }
        if (DashCounterFront == 2)
        {
            EncodedID += "-";
            DashCounterFront = 0;

        }
        DashCounterFront++;
        EncodedID += to_string(CharsToEncode_Above4[j]);
    }

    return EncodedID;
}*/

/*void GenerateProductID(vector<Records>& record, vector<string>& historySeq)
{

    for (int i = 0; i < (int)record.size(); i++)
    {
        record[i].productID = GenerateKEY(record[i].name);
    }

    system("cls");

    historySeq.push_back("GenerateID");
    printHistorySeq(historySeq);

    cout << "---Generating product ID on record items." << endl;
    printVector(record);
}*/

void RemoveElement(vector<Records>& record, vector<string>& historySeq)
{
    /*
    Prompts user to input element name to remove.
    Binarysearch name to extract index.
    Prompts user confirmation to remove [name:price:quantity].
    Yes, removes index from the vector.
    No, breaks out of the function.
    */

    string Confirmation;
    string ElementToRemove;
    int index;

    cout << endl << "Element to remove: ";
    cin >> ElementToRemove;

    index = BinarySearch(record, 0, record.size(), ElementToRemove);

    if(index > -1)
    {
        cout << endl;
        cout << "Confirm ["
            << record[index].name << ":"
            << record[index].price << ":"
            << record[index].quantity << "] to remove? (Y/N): ";

        cin >> Confirmation;

        if ((Confirmation == "Y" || Confirmation == "y"
            || Confirmation == "Yes" || Confirmation == "yes"))
        {
            system("cls");
            historySeq.push_back("RemoveElement");
            printHistorySeq(historySeq);

            cout << "---Removed ["
                << record[index].name << ":"
                << record[index].price << ":"
                << record[index].quantity << "] at index " 
                << index << "." << endl;

            record.erase(record.begin() + (index));

            printVector(record);
            return;
        }
    }

    system("cls");
    cout << "---Failed to find input. " << endl;
    printVector(record);
    return;
}

void ModifyElement(vector<Records>& record, vector<string>& historySeq)
{
    /*
    Prompts user to input ElementToModify.
    Binarysearch to look up index of ElementToModify.
    If value exists, allows user to overrite [name:price:quantity]
    Option for the user to input "nochange" if they choose to leave value unchanged.

    Checks to only accept characters for name.
    Checks to only accept digits for price, with the exception of "nochange".
    Checks to only accept digits for quantity, with the exception of "nochange".

    Prompts user confirmation to remove [name:price:quantity].
    Yes, replaces non-"nochange" overrite values into index# of the ElementToModify.
    No, breaks out of the function.
    */

    string ModifyInput;
    string ElementToModify;
    int index;

    string InsertName;
    string InsertPrice;
    string InsertQuantity;

    int InsertQuantity_Int = 0;
    float InsertPrice_Float = 0;

    bool Repeat;
    string Confirmation;

    cout << endl << "Enter Name of element to modify: ";
    cin >> ElementToModify;

    index = BinarySearch(record, 0, record.size(), ElementToModify);

    if (index > -1)
    {
        cout << endl << "Type 'nochange' for element variables you wish to keep unchanged." << endl;
        cout << "Modifying ["
            << record[index].name << ":"
            << record[index].price << ":"
            << record[index].quantity << "] at index " << index << "." << endl << endl;

        do {

            Repeat = false;

            cout << "Input Name: ";
            cin >> InsertName;
            
            if (InsertName != "nochange")
                Repeat = isdigitCheck(InsertName);
           
        } while (Repeat);

        do {

            Repeat = false;

            cout << "Input Price: ";
            cin >> InsertPrice;
            
            if (InsertPrice != "nochange")
                Repeat = isalphaCheck(InsertPrice);  

        } while (Repeat);

        if (InsertPrice != "nochange")
            InsertPrice_Float = stof(InsertPrice);

        do {

            Repeat = false;

            cout << "Input Quantity: ";
            cin >> InsertQuantity;

            if (InsertQuantity != "nochange")
                Repeat = isalphaCheck(InsertQuantity);

        } while (Repeat);

        if (InsertQuantity != "nochange")
            InsertQuantity_Int = stof(InsertQuantity);

        cout << endl;
        cout << "Confirm [";

            if (InsertName != "nochange")
                cout << InsertName << ":";
            else
                cout << record[index].name << ":";

            
            if (InsertPrice != "nochange") 
                cout << InsertPrice << ":";
            else
                cout << record[index].price << ":";


            if (InsertQuantity != "nochange")
                cout << InsertQuantity << "]? (Y/N): ";
            else
                cout << record[index].quantity << "]? (Y/N): ";


        cin >> Confirmation;

        if ((Confirmation == "Y" || Confirmation == "y" || Confirmation == "Yes" || Confirmation == "yes"))
        {
            system("cls");

            historySeq.push_back("ModifyElement");
            printHistorySeq(historySeq);

            cout << "---Modified ["
                << record[index].name << ":"
                << record[index].price << ":"
                << record[index].quantity << "] to [";

            if(InsertName != "nochange")
            {
                record[index].name = InsertName;
                cout << InsertName << ":";
            }
            else
                cout << record[index].name << ":";

            if (InsertPrice != "nochange")
            {
                record[index].price = InsertPrice_Float;
                cout << InsertPrice_Float << ":";
            }
            else
                cout << record[index].price << ":";

            if (InsertQuantity != "nochange")
            {
                record[index].quantity = InsertQuantity_Int;
                cout << InsertQuantity_Int << "] " << endl;
            }
            else
                cout << record[index].quantity << "] " << endl;

            printVector(record);
            return;
        }
    }

    system("cls");
    cout << "---Failed to find input. " << endl;
    printVector(record);
    return;
}

void InsertElement(vector<Records>& record, vector<string>& historySeq)
{
    /*
    Prompts user to input values of a new element to be inserted into the vector [name:price:quantity].
    Checks to only accept characters for name.
    Checks to only accept digits for price.
    Checks to only accept digits for quantity.

    Prompts user confirmation to insert [name:price:quantity].
    Yes, inserts element in the vector
    No, breaks out of the function.
    */

    Records DummyElement;

    string InsertName;
    string InsertPrice;
    string InsertQuantity;

    string Confirmation_One;
    string Confirmation_Two;

    bool Repeat = false;

    cout << endl <<  "Inserting element into database.." << endl;
    cout << "Input [name:price:quantity]" << endl << endl;

    //confirm string InsertName only contains characters
    //error into loop if digit detected
    do {

        Repeat = false;

        cout << "Input Name: ";
        cin >> InsertName;

        Repeat = isdigitCheck(InsertName);

    } while (Repeat);

    //assign InsertName to DummyElement.name after input restriction passes

    //confirm string InsertPrice only contains digits
    //error into loop if character detected
    do {

        Repeat = false;

        cout << "Input Price: ";
        cin >> InsertPrice;

        Repeat = isalphaCheck(InsertPrice);

    } while (Repeat);

    //convert string InsertPrice to float InsertPrice_Float
    //assign InsertPrice_Float to DummyElement.price after input restriction pass
    float InsertPrice_Float = stof(InsertPrice);

    //confirm int InsertQuantity only contains integers
    //error into loop if character detected.
    do {

        Repeat = false;

        cout << "Input Quantity: ";
        cin >> InsertQuantity;

        Repeat = isalphaCheck(InsertQuantity);

    } while (Repeat);

    //convert string InsertPrice to int InsertPrice_Int
    //assign InsertPrice_Int to DummyElement.quantity after input restriction pass
    int InsertQuantity_Int = stof(InsertQuantity);

    cout << endl;
    cout << "Confirm ["
        << InsertName << ":"
        << InsertPrice_Float << ":"
        << InsertQuantity_Int << "]? (Y/N): ";

    cin >> Confirmation_One;

    if (Confirmation_One == "Y" || Confirmation_One == "y" 
        || Confirmation_One == "Yes" || Confirmation_One == "yes")
    {
        DummyElement.name = InsertName;
        DummyElement.price = InsertPrice_Float;
        DummyElement.quantity = InsertQuantity_Int;


        record.push_back(DummyElement);

        system("cls");

        historySeq.push_back("InsertElement");
        printHistorySeq(historySeq);

        cout << "---Inserted ["
            << DummyElement.name << ":"
            << DummyElement.price << ":"
            << DummyElement.quantity << "]" << endl;

        printVector(record);
        return;
    }

    system("cls");
    printVector(record);
    return;
}

void SortByName(vector<Records>& record, vector<string>& historySeq, string OrderPreference, bool& sortedName_A, bool& sortedName_D)
{
    /*
    Prompts user to input sort preference (ascending/descending).
    If input matches preference input string, sort based on preference

    If ascending preference is chosen:
    Returns bool sortedName_A = true and bool sortedName_D = false to be used as saved preference.
    If descending preference is chosen:
    Returns bool sortedName_A = false and bool sortedName_D = true to be used as saved preference.

    If preference input is invalid:
    Repeat.
    */

    string Repeat;

    cout << "Sort By (Ascending/Descending): ";
    cin >> OrderPreference;

    if (OrderPreference == "Ascending" || OrderPreference == "ascending") {

        system("cls");

        historySeq.push_back("SortName-A");
        printHistorySeq(historySeq);

        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.name < b.name; });

        cout << "---Sort By Name: Ascending Order" << endl;
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;

        sortedName_A = true;
        sortedName_D = false;
        return;

    }
    else if (OrderPreference == "Descending" || OrderPreference == "descending") {

        system("cls");

        historySeq.push_back("SortName-D");
        printHistorySeq(historySeq);

        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.name > b.name; });

        cout << "---Sort By Name: Descending Order" << endl;
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        
        sortedName_A = false;
        sortedName_D = true;
        return;

    }
    else
    {
        cout << "Invalid input. " << endl;
        SortByName(record, historySeq, OrderPreference, sortedName_A, sortedName_D);
    }

}

void SortByPrice(vector<Records>& record, vector<string>& historySeq, string OrderPreference)
{
    /*
    Prompts user to input sort preference (ascending/descending).
    If input matches preference input string, sort based on preference
    If preference input is invalid:
    Repeat.
    */

    string Repeat;

    cout << "Sort By (Ascending/Descending): ";
    cin >> OrderPreference;

    if (OrderPreference == "Ascending" || OrderPreference == "ascending") {

        system("cls");

        historySeq.push_back("SortPrice-A");
        printHistorySeq(historySeq);

        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.price < b.price; });

        cout << "---Sort By Price: Ascending Order" << endl;
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        return;


    }
    else if (OrderPreference == "Descending" || OrderPreference == "descending") {

        system("cls");

        historySeq.push_back("SortPrice-D");
        printHistorySeq(historySeq);

        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.price > b.price; });

        cout << "---Sort By Price: Descending Order" << endl;
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        return;

    }
    else
    {
        cout << "Invalid input. " << endl;
        SortByPrice(record, historySeq, OrderPreference);
    }

}

void SortByQuantity(vector<Records>& record, vector<string>& historySeq, string OrderPreference)
{
    /*
    Prompts user to input sort preference (ascending/descending).
    If input matches preference input string, sort based on preference
    If preference input is invalid:
    Repeat.
    */

    string Repeat;

    cout << "Sort By (Ascending/Descending): ";
    cin >> OrderPreference;


    if (OrderPreference == "Ascending" || OrderPreference == "ascending") {

        system("cls");

        historySeq.push_back("SortQty-A");
        printHistorySeq(historySeq);

        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.quantity < b.quantity; });

        cout << "---Sort By Quantity: Ascending Order" << endl;

        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        return;

    }
    else if (OrderPreference == "Descending" || OrderPreference == "descending") {

        system("cls");

        historySeq.push_back("SortQty-D");
        printHistorySeq(historySeq);

        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.quantity > b.quantity; });


        cout << "---Sort By Quantity: Descending Order" << endl;
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        return;

    }
    else
    {
        cout << "Invalid input. " << endl;
        SortByQuantity(record, historySeq, OrderPreference);
    }

}

bool isdigitCheck(string InputToCheck)
{
    /*
    Checks string input if it contains digits.
    Returns true if digits are found.
    Return false if no digits are found.
    */

    for (int i = 0; i < (int)InputToCheck.size(); i++)
    {
        if (isdigit(InputToCheck[i]))
        {
            cin.clear();
            cin.ignore();

            cout << endl << "---Invalid input. Try again!" << endl;
            cout << "---Characters valid only." << endl << endl;
            return true;
        }
    }
    return false;
}

bool isalphaCheck(string InputToCheck)
{   
    /*
    Checks string input if it contains characters.
    Returns true if characters are found.
    Return false if no characters are found.
    */

    for (int i = 0; i < (int)InputToCheck.size(); i++)
    {
        if (isalpha(InputToCheck[i]))
        {
            cin.clear();
            cin.ignore();

            cout << endl << "---Invalid input. Try again!" << endl;
            cout << "---Digits valid only." << endl << endl;
            return true;
        }
    }
    return false;
}

void CapacityCheck(vector<Records> testVector)
{
    /*
    Prints size() of vector.
    Prints capacity() of vector.
    */

    cout << endl;
    cout << "vector size: " << testVector.size() << endl;
    cout << "vector capacity: " << testVector.capacity() << endl;
    cout << endl;
}

void removeDuplicates(vector<Records>& record, vector<string>& historySeq)
{
    /*
    Breaks function if size() = 0.
    Runs for loop over the vector with an if statement checking for (record[current].name == record[previous].name)
    For every success if statement check, detected_dupes++.

    For dupes detected:
    Allows user to input which of the two duplicates to remove based on index#.
    Releases excess memory from elements that have been removed.

    If no dupes detected:
    Breaks function informing user that no dupes have been detected.
    */

    if (record.size() == 0)
    {
        return;
    }

    int previous = 0;
    int detected_dupes = 0;
    int dupetoRemove;
    bool Repeat = false;

    system("cls");

    historySeq.push_back("removeDupes");
    printHistorySeq(historySeq); 

    cout << "---Checking for duplicates." << endl;
    printVector(record);

    cout << endl << "---Detected duplicates: " << endl;

    for (int current = 1; current < (int)record.size(); current++)
    {
        
        if (record[current].name == record[previous].name)
        {
            
            cout << "---index " << previous << " ["
                << record[previous].name << ":"
                << record[previous].price << ":"
                << record[previous].quantity << "]" << endl;

            cout << "---index " << current << " ["
                << record[current].name << ":"
                << record[current].price << ":"
                << record[current].quantity << "] " << endl;

            
                cout << "Indicate index # of the duplicate to remove: ";
                cin >> dupetoRemove;
                cout << endl;

                if (dupetoRemove == previous)
                {
                    record.erase(record.begin() + previous);
                }
                else if (dupetoRemove == current)
                {
                    record.erase(record.begin() + current);
                }
                else
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid input." << endl;
                    cout << "Input the index number of the duplicate to remove." << endl;
                    removeDuplicates(record, historySeq);
                }       
            detected_dupes++;
        }      
        previous++;
    }
    

    if (detected_dupes == 0)
    {
        system("cls");

        historySeq.push_back("removeDupes");
        printHistorySeq(historySeq);

        cout << "---No duplicates detected." << endl;
        printVector(record);

        return;
    }

    system("cls");
    printHistorySeq(historySeq);
    printVector(record);

    record.shrink_to_fit();
    return;
}

void quicksort(vector<Records>& record, bool sortedName_A, bool sortedName_D, bool& isSorted)
{
    /*
    Mirror of SortbyName to auto sort based on saved SortbyName(Ascending/Descending) preference.
    */

    if (isSorted == 0)
    {
        if (sortedName_A == 1)
        {
            cout << "was sorted A: true, issorted = false" << endl;
            sort(record.begin(), record.end(), [](Records a, Records b)
                {return a.name < b.name; });

            isSorted = true;
            return;
        }
        else if (sortedName_D == 1)
        {
            cout << "was sorted D: true, issorted = false" << endl;
            sort(record.begin(), record.end(), [](Records a, Records b)
                {return a.name > b.name; });

            isSorted = true;
            return;
        }
    }

    return;
}

