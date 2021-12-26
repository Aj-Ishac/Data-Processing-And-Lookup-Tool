#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

struct Records {

    string name;
    string productID;
    float price;
    int quantity;

};

void printVector(vector<Records>);
void MenuController(vector<Records>&);
char printMenu(char);

void SortByName(vector<Records>&, string, string);
void SortByPrice(vector<Records>&, string, string);
void SortByQuantity(vector<Records>&, string, string);

void InsertElement(vector<Records>&);
void ModifyElement(vector<Records>&);
void RemoveElement(vector<Records>&);

void Search(vector<Records>);
int BinarySearch(vector<Records>, int, int, string);

bool isdigitCheck(string);
bool isalphaCheck(string);
void CapacityCheck(vector<Records>);

void GenerateProductID(vector<Records>&);
string GenerateKEY(string);

void ImportFile(vector<Records>&);
void MergeVectors(vector<Records>&, vector<Records>);
void removeDuplicates(vector<Records>&);


int main()
{
    vector<Records> record;

    ifstream inFile("PriceList.txt");

    //check if file can open
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

    //this is a test of prints
    
    //NEXT
    //put sorts back to how they were.
    //no need to have cins outside if we return bool to know if sorted or not
    //menu rework - implement back feature
    //pass file name as parameter for ImportFile()
    //guarantee a/d sort if calling binary search or remove duplicates
    //figure out how to add two letters to ID
    //consistency on input output (case being element funcs)
    //when importing. configure a system to match string to name, float to price, int to qty

    cout << "---Base data from file-------------------" << endl;
    printVector(record);

    cout << endl << "You are at the beginning of the MenuController" << endl;
    MenuController(record);

    //ModifyElement(record);
    //InsertElement(record);

    //SortByName(record, OrderPreference, SortPreference);
    //SortByPrice(record, OrderPreference, SortPreference);
    //SortByQuantity(record, OrderPreference, SortPreference);

    //Search(record);
    //ImportFile(record);
    //RemoveElement(record);
    
    //ImportFile(record);
    //MenuController(record);

    //removeDuplicates(record);
    //GenerateProductID(record);
    printVector(record);

    inFile.close();
    return 0;
}

//print, sort(name, price, qty), insert, modify, remove, generateproductid, importvectors
//(make sure is sorted) search, remove dupes, 
char printMenu(char choice)
{
    cout << " 1. Print Records" << endl;
    cout << " 2. Element: Insert/Modify/Remove" << endl;
    cout << " 3. Sort By: Name/Price/Quantity" << endl;
    cout << " 4. Generate Product ID" << endl;
    cout << " 5. Search Element" << endl;
    cout << " 6. Import and Merge File" << endl;
    cout << " 7. Check for Duplicates" << endl;
    cout << " 8. Diagnostics" << endl;
    cout << " 0. Restart" << endl << endl;
    cout << " Input choice (0-7): ";
    cin >> choice;
    cout << endl << endl;

    return choice;
}

void MenuController(vector<Records>& record)
{
    bool Repeat = false;
    string Sort_By, Sort_Order;

    char choice = 0;
    choice = printMenu(choice);

    switch (choice)
    {
    case 1:
        printVector(record);
        break;

    case 2:
        cout << " 1. Insert Element" << endl;
        cout << " 2. Modify Element" << endl;
        cout << " 3. Remove Element" << endl << endl;

        cout << " Input choice (1-3): ";
        cin >> choice;
        cout << endl << endl;

        switch (choice)
        {
        case 1:
            InsertElement(record);
            break;
        case 2:
            ModifyElement(record);
            break;
        case 3:
            RemoveElement(record);
            break;
        }

    case 3:
        cout << " 1. Sort by Name" << endl;
        cout << " 2. Sort by Price" << endl;
        cout << " 3. Sort by Quantity" << endl;

        cout << " Input choice (1-3): ";
        cin >> choice;
        cout << endl << endl;

        switch (choice)
        {
        case 1:
            //SortByName(record, Sort_Order, Sort_By);
            //return bool to indicate is sorted for dependencies
        case 2:
            //SortByPrice(record, Sort_Order, Sort_By);

        case 3:
            //SortByQuantity(record, Sort_Order, Sort_By);

        }
        break;

    case 4:
        GenerateProductID(record);
        break;

    case 5:
        Search(record);
        break;

    case 6:
        //import merge file
        //pass file name as parameter
        break;
    case 7:
        //duplicate check
        //confirm that is sorted
        break;

    case 8:
        //diagnostics
        break;
    case 0:
        //restart
        break;
    }
}
void printVector(vector<Records> vector)
{
    cout << endl;
    if (vector[0].productID.size() != 0) {

        CapacityCheck(vector);
        cout << "---Vector.size(): " << vector.size() << endl;
        cout << "-----------------------------------------" << endl;
        cout << endl << "     -ID-        -Name-       -Price-   -Qty-" << endl;
        for (int i = 0; i < (int)vector.size(); i++)
        {
            cout << " ";
            cout << left << vector[i].productID << "   ";
            cout << setw(10) << left << vector[i].name << "   ";
            cout << setw(6) << right << fixed << setprecision(2) << vector[i].price << "   ";
            cout << setw(6) << right << vector[i].quantity << "   ";
            cout << endl;
        }
    }
    else
    {
        CapacityCheck(vector);
        cout << "---Vector.size(): " << vector.size() << endl;
        cout << "-----------------------------------------" << endl;
        cout << endl << "  -Name-       -Price-    -Qty-" << endl;
        for (int i = 0; i < (int)vector.size(); i++) {
            cout << " ";
            cout << setw(10) << left << vector[i].name << "   ";
            cout << setw(6) << right << fixed << setprecision(2) << vector[i].price << " ";
            cout << setw(8) << right << vector[i].quantity << "   ";
            cout << endl;
        }
    }

}

void MergeVectors(vector<Records>& vector1, vector<Records> vector2)
{
    cout << endl << "Merging the two vectors..."<< endl;
    vector1.reserve(vector1.size() + vector2.size());
    vector1.insert(vector1.end(), vector2.begin(), vector2.end());

    printVector(vector1);
}

void ImportFile(vector<Records>& record)
{
    vector<Records> tempVector;

    ifstream inFile("3rdpartyimport.txt");

    if (!inFile)
    {
        cerr << "File cannot be opened. " << endl;
        system("PAUSE");
        exit(1);
    }
    
    //cplusplus.com/forum/beginner/99799/
    string templine;
    while (getline(inFile, templine))
    {
        Records tempV;

        inFile >> tempV.name;
        inFile >> tempV.price;
        inFile >> tempV.quantity;

        tempVector.push_back(tempV);
    }

    MergeVectors(record, tempVector);
    cout << "----------------------------------------" << endl;
    printVector(tempVector);
    
    tempVector.clear();
    tempVector.shrink_to_fit();
}

void Search(vector<Records> record)
{
    string ValueLookup;
    cout << endl << endl << "Input Name to search: " << ValueLookup;
    cin >> ValueLookup;

    int index = BinarySearch(record, 0, record.size(), ValueLookup);
    cout << ValueLookup << " index: " << index << endl << endl;
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


}

string GenerateKEY(string NameToID)
{
    string EncodedID;
    int CharsToEncode_Above4[5];
    int CharsToEncode_Below4[3];
    int DashCounter = 0;

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

    cout << "NameToID: " << NameToID.size() << endl;

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
            if (DashCounter == 2)
            {
                EncodedID += "-";
                DashCounter = 0;
            }
            DashCounter++;
            EncodedID += to_string(CharsToEncode_Above4[j]);
        }
    
    return EncodedID;
}

void GenerateProductID(vector<Records>& record)
{
    cout << endl << "Generating product ID on record items..." << endl << endl;
    for (int i = 0; i < (int)record.size(); i++)
    {
        record[i].productID = GenerateKEY(record[i].name);
    }
}

void RemoveElement(vector<Records>& record)
{
    string Confirmation;
    string ElementToRemove;
    int index;

    cout << " Element to remove: " << ElementToRemove;

    index = BinarySearch(record, 0, record.size(), ElementToRemove);

    cout << endl;
    cout << "Confirm ["
        << record[index].name << ":"
        << record[index].price << ":"
        << record[index].quantity << "] to remove? (Y/N): ";

    cin >> Confirmation;

    if ((Confirmation == "Y" || Confirmation == "y" 
        || Confirmation == "Yes" || Confirmation == "yes"))
    {

        cout << endl << " ["
            << record[index].name << ":"
            << record[index].price << ":"
            << record[index].quantity << "] at index " << index << " has been removed." << endl << endl;

        record.erase(record.begin() + (index));
    }
}

void ModifyElement(vector<Records>& record)
{
    string ModifyInput;
    string ElementToModify;
    int index;

    string InsertName;
    string InsertPrice;
    string InsertQuantity;
    bool Repeat;

    string Confirmation;

    cout << endl << "Enter Name of element to modify: ";
    cin >> ElementToModify;

    index = BinarySearch(record, 0, record.size(), ElementToModify);

    cout << endl << "Modifying ["
        << record[index].name << ":"
        << record[index].price << ":"
        << record[index].quantity << "] at index " << index << "." << endl;

    do {

        Repeat = false;

        cout << "Input Name: ";
        cin >> InsertName;

        Repeat = isdigitCheck(InsertName);

    } while (Repeat);

    do {

        Repeat = false;

        cout << "Input Price: ";
        cin >> InsertPrice;

        Repeat = isalphaCheck(InsertPrice);

    } while (Repeat);
    float InsertPrice_Float = stof(InsertPrice);

    do {

        Repeat = false;

        cout << "Input Quantity: ";
        cin >> InsertQuantity;

        Repeat = isalphaCheck(InsertQuantity);

    } while (Repeat);
    int InsertQuantity_Int = stof(InsertQuantity);

    cout << endl;
    cout << "Confirm ["
        << record[index].name << ":"
        << record[index].price << ":"
        << record[index].quantity << "]? (Y/N): ";

    cin >> Confirmation;

    if ((Confirmation == "Y" || Confirmation == "y" || Confirmation == "Yes" || Confirmation == "yes"))
    {
        cout << endl;
        cout << " ["
            << record[index].name << ":"
            << record[index].price << ":"
            << record[index].quantity << "] has been modified to ["
            << InsertName << ":"
            << InsertPrice_Float << ":"
            << InsertQuantity_Int << "] "
            << endl << endl;

        record[index].name = InsertName;
        record[index].price = InsertPrice_Float;
        record[index].quantity = InsertQuantity_Int;

    }
}

void InsertElement(vector<Records>& record)
{
    Records DummyElement;

    string InsertName;
    string InsertPrice;
    string InsertQuantity;

    string Confirmation_One;
    string Confirmation_Two;

    bool Repeat = false;

    cout << endl << "---Inserting data into database---------- " << endl << endl;
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
    cout << "Confirm  ["
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

        cout << endl;
        cout << "Inserted ["
            << DummyElement.name << ":"
            << DummyElement.price << ":"
            << DummyElement.quantity << "]";

        cout << endl << endl;

        record.push_back(DummyElement);

    }
    else
    {
        cout << "Restart/Quit?: ";
        cin >> Confirmation_Two;

        if (Confirmation_Two == "Restart" || Confirmation_Two == "restart" 
            || Confirmation_Two == "R" || Confirmation_Two == "r")
        {
            InsertElement(record);
        }

    }
    
    cout << endl;
    return;
 
}

void SortByName(vector<Records>& record, string OrderPreference, string SortPreference)
{
    string Repeat;

    cout << "Sort By (Ascending/Descending): ";
    cin >> OrderPreference;

    auto start = high_resolution_clock::now();

    if (OrderPreference == "Ascending" || OrderPreference == "ascending") {
        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.name < b.name; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << endl << "---Sort By Name--------Ascending Order---";
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        cout << "---Function runtime: ";
        cout << duration.count() << "ms" << endl;

    }
    else if (OrderPreference == "Descending" || OrderPreference == "descending") {
        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.name > b.name; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << endl << "---Sort By Name-------Descending Order---";
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        cout << "---Function runtime: ";
        cout << duration.count() << "ms" << endl;

    }
    else if (OrderPreference == "Repeat" || OrderPreference == "repeat")
    {
        SortByName(record, OrderPreference, SortPreference);
    }
    else
    {
        cout << endl << "Invalid input. Try again! " << endl;
        SortByName(record, OrderPreference, SortPreference);
    }

    cout << endl << "Repeat? (Y/N): ";
    cin >> Repeat;

    if (Repeat == "Y" || Repeat == "y" || Repeat == "Yes" || Repeat == "yes")
    {
        cout << endl << "Sort by (Name/Price/Quantity) : " << SortPreference << endl;
        SortByName(record, OrderPreference, SortPreference);
    }
    else
    {
        cout << endl;
        //MenuController(record);
        return;
    }
}

void SortByPrice(vector<Records>& record, string OrderPreference, string SortPreference)
{
    string Repeat;

    cout << "Sort By (Ascending/Descending): ";
    cin >> OrderPreference;

    auto start = high_resolution_clock::now();

    if (OrderPreference == "Ascending" || OrderPreference == "ascending") {
        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.price < b.price; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << endl << "---Sort By Price-------Ascending Order---";
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        cout << "---Function runtime: ";
        cout << duration.count() << "ms" << endl;

    }
    else if (OrderPreference == "Descending" || OrderPreference == "descending") {
        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.price > b.price; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << endl << "---Sort By Price------Descending Order---";
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        cout << "---Function runtime: ";
        cout << duration.count() << "ms" << endl;

    }
    else if (OrderPreference == "Repeat" || OrderPreference == "repeat")
    {
        SortByPrice(record, OrderPreference, SortPreference);
    }
    else
    {
        cout << endl << "Invalid input. Try again! " << endl;
        SortByPrice(record, OrderPreference, SortPreference);
    }

    cout << endl << "Repeat? (Y/N): ";
    cin >> Repeat;

    if (Repeat == "Y" || Repeat == "y" || Repeat == "Yes" || Repeat == "yes")
    {
        cout << endl << "Sort by (Name/Price/Quantity) : " << SortPreference << endl;
        SortByPrice(record, OrderPreference, SortPreference);
    }
    else
    {
        cout << endl;
        //MenuController(record);
    }
}

void SortByQuantity(vector<Records>& record, string OrderPreference, string SortPreference)
{
    string Repeat;

    cout << "Sort By (Ascending/Descending): ";
    cin >> OrderPreference;

    auto start = high_resolution_clock::now();

    if (OrderPreference == "Ascending" || OrderPreference == "ascending") {
        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.quantity < b.quantity; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << endl << "---Sort By Quantity----Ascending Order---";
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        cout << "---Function runtime: ";
        cout << duration.count() << "ms" << endl;

    }
    else if (OrderPreference == "Descending" || OrderPreference == "descending") {
        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.quantity > b.quantity; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << endl << "---Sort By Quantity---Descending Order---";
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        cout << "---Function runtime: ";
        cout << duration.count() << "ms" << endl;

    }
    else if (OrderPreference == "Repeat" || OrderPreference == "repeat")
    {
        SortByQuantity(record, OrderPreference, SortPreference);
    }
    else
    {
        cout << endl << "Invalid input. Try again! " << endl;
        SortByQuantity(record, OrderPreference, SortPreference);
    }

    cout << endl << "Repeat? (Y/N): ";
    cin >> Repeat;

    if (Repeat == "Y" || Repeat == "y" || Repeat == "Yes" || Repeat == "yes")
    {
        cout << endl << "Sort by (Name/Price/Quantity) : " << SortPreference << endl;
        SortByQuantity(record, OrderPreference, SortPreference);
    }
    else
    {
        cout << endl;
        //MenuController(record);
    }
}

bool isdigitCheck(string InputToCheck)
{
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
    cout << endl;
    cout << "vector size: " << testVector.size() << endl;
    cout << "vector capacity: " << testVector.capacity() << endl;
    cout << endl;
}

void removeDuplicates(vector<Records>& record) 
{
    
    if (record.size() == 0)
    {
        return;
    }

    int previous = 0;
    int detected_dupes = 0;

    for (int current = 1; current < record.size(); current++)
    {
        if (record[current].name == record[previous].name)
        {
            cout << " index " << current << ": " << record[current].name << endl;
            record.erase(record.begin() + current);
            detected_dupes++;
        }
        previous++;
    }

    if (detected_dupes == 0)
    {
        cout << " No duplicates detected." << endl;
    }
    else
    {
        cout << " has been removed and excess memory has been released. " << endl;
    }

    record.shrink_to_fit();
    return;
}

//bug:
//warning dept building up
//replace dowhile with while(repeat = 1)
//dowhile is exitcontrol loop, while is entry control loop
//before any binary search parent func, make sure vec is sorted else possble crashes
//find a way to put sorting preference outside to use as reference for funcs that rely on bsearch parent funcs
//pass parameter with sort preference to call for specific sort with preference before bsearch if not already sorted
//insertelement at the very bottom needs adjusting with paramter in restart statement missing
//sort funcs need parameter cleanup

//progress:   
//remove O(1)
//search ID/Name
//edit value - constructor based O(1)
//verify capacity
//https://www.codesdope.com/cpp-stdvector/
//bulk import data from second file
//output to new file
//menucontroller needs major work. move bulk from funcs like sortx to menucontroller, cleanup general funcs (hint: unneeded parameters)
//detect duplicates in name and verify with user on action to take