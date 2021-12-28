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
void printMainMenu(vector<Records>);

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
bool isSortedCheck(vector<Records> record);

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
    
    //NEXT
    //switch input: only take first letter or fix multichar input
    
    //sort funcs with wrong input breaks func without sorting
    //sorted bool still marking as true even though it is not sorted
    //breaking other sort dependent funcs  
    //solution: force restart in the sort funcs to stay in function till completed
     
    //pass file name as parameter for ImportFile()
    
    //when importing. configure a system to match string to name, float to price, int to qty
    
    //output into basefile

    //warning dept cleanup

    //more specifics on what to remove with removeduplicate func

    //output final result to new file

    //implement history sequence. array[5] to print at the top of every clearscr

    cout << "---Base data from file-------------------" << endl;
    printVector(record);
    bool isSortedforBS = false;
    MenuController(record);

    inFile.close();
    return 0;
}
//https://docs.github.com/en/get-started/quickstart/hello-world
//print, sort(name, price, qty), insert, modify, remove, generateproductid, importvectors
//(make sure is sorted) search, remove dupes, 
void printMainMenu(vector<Records> record)
{   

    cout << endl;
    cout << "    Beginning of the Menu Controller" << endl;
    cout << "-----------------------------------------" << endl;
    cout << " 1. Print Records" << endl;
    cout << " 2. Sort By: Name/Price/Quantity" << endl;
    cout << " 3. Element: Insert/Modify/Remove" << endl;
    cout << " 4. Generate Product ID" << endl;
    cout << " 5. Search Element" << endl;
    cout << " 6. Import and Merge File" << endl;
    cout << " 7. Check for Duplicates" << endl;
    cout << " 8. Diagnostics" << endl;
    cout << " 9. Quit" << endl;
    cout << " 0. Restart" << endl;
    cout << "-----------------------------------------" << endl;

    cout << "Input choice (0-7): ";

}

void MenuController(vector<Records>& record)
{
    bool Repeat = true;
    bool isSorted = false;
    string Sort_Preference, Sort_Order;

    char choice;
    
    do {

        printMainMenu(record);
        cin >> choice;

        switch (choice)
        {
        case '1':
            //printtable: pass1, pass2
            system("cls");
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

            switch (choice)
            {
            case '1':
                //sortbyname: pass1, pass2
                SortByName(record, Sort_Order, Sort_Preference);
                isSorted = true;
                break;

            case '2':
                //sortbyprice: pass1, pass2 
                SortByPrice(record, Sort_Order, Sort_Preference);
                isSorted = false;
                break;

            case '3':
                //sortbyqty: pass1, pass2
                SortByQuantity(record, Sort_Order, Sort_Preference);
                isSorted = false;
                break;
            }
            break;

        case '3':

            cout << endl;
            cout << " 1. Insert Element" << endl;
            cout << " 2. Modify Element" << endl;
            cout << " 3. Remove Element" << endl << endl;

            cout << "Input choice (1-3): ";
            cin >> choice;

            switch (choice)
            {
            case '1':
                //insertelement: pass1, pass2
                InsertElement(record);
                isSorted = false;
                break;

            case '2':
                //modifyelement: pass1, pass2
                if (isSorted == 0)
                {
                    system("cls");
                    cout << "---Function requires records to be sorted by name!" << endl;
                    printVector(record);
                    break;
                }

                ModifyElement(record);
                isSorted = false;
                break;

            case '3':
                //removelement: pass1, pass2
                if (isSorted == 0)
                {
                    system("cls");
                    cout << "---Function requires records to be sorted by name!" << endl;
                    printVector(record);
                    break;
                }

                RemoveElement(record);
                break;
            }
            break;

        case '4':
            //generateid: pass1, pass2
            GenerateProductID(record);            
            break;

        case '5':
            //search: pass1, pass2
            if (isSorted == 0)
            {
                system("cls");
                cout << "---Function requires records to be sorted by name!" << endl;
                printVector(record);
                break;
            }

            Search(record);
            break;
        
        case '6':
            //import&merge file: pass1, pass2

            ImportFile(record);
            isSorted = false;
            break;
        
        case '7':
            //duplicate check: pass1, pass2
            if (isSorted == 0)
            {
                system("cls");
                cout << "---Function requires records to be sorted by name!" << endl;
                printVector(record);
                break;
            }

            removeDuplicates(record);
            break;

        case '8':
            //diagnostics: later
            break;

        case '9':
            //quit:pass
            return;

        case '0':
            //restart:pass
            system("cls");
            printVector(record);
            break;
        }

    }while (Repeat);
}
void printVector(vector<Records> vector)
{
    if (vector[0].productID.size() != 0) {

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
    //reserve memory for vector merge and insert vector2 at the back of vector1
    vector1.reserve(vector1.size() + vector2.size());
    vector1.insert(vector1.end(), vector2.begin(), vector2.end());

    cout << endl << "---Merged Data Table" << endl;
    printVector(vector1);
}

void ImportFile(vector<Records>& record)
{
    vector<Records> tempVector;
    string filename;

    cout << endl << "Import (filename.txt): ";
    cin >> filename;
        
    system("cls");
    //printVector(record);

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

    cout << "---Imported Data Table" << endl;
    printVector(tempVector);

    MergeVectors(record, tempVector);
    cout << "-----------------------------------------" << endl;

    inFile.close();    
    tempVector.clear();
    tempVector.shrink_to_fit();

    return;
}

void Search(vector<Records> record)
{
    string ValueLookup;
    cout << endl << "Search Name: ";
    cin >> ValueLookup;



    int index = BinarySearch(record, 0, record.size(), ValueLookup);

    if(index > -1)
    {

        system("cls");
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

string GenerateKEY(string NameToID)
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
}

void GenerateProductID(vector<Records>& record)
{

    for (int i = 0; i < (int)record.size(); i++)
    {
        record[i].productID = GenerateKEY(record[i].name);
    }

    system("cls");
    cout << "---Generating product ID on record items." << endl;
    printVector(record);
}

void RemoveElement(vector<Records>& record)
{
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
            record.erase(record.begin() + (index));

            system("cls");

            cout << "---Removed ["
                << record[index].name << ":"
                << record[index].price << ":"
                << record[index].quantity << "] at index " 
                << index << "." << endl;

            printVector(record);
            return;
        }
    }
    system("cls");
    printVector(record);
    return;
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

    if (index > -1)
    {
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

            record[index].name = InsertName;
            record[index].price = InsertPrice_Float;
            record[index].quantity = InsertQuantity_Int;

            system("cls");

                cout << "---Modified ["
                << record[index].name << ":"
                << record[index].price << ":"
                << record[index].quantity << "] to ["
                << InsertName << ":"
                << InsertPrice_Float << ":"
                << InsertQuantity_Int << "] "
                << endl;

            printVector(record);
            return;

        }
    }

    system("cls");
    printVector(record);
    return;
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

    cout << "Inserting element into database.." << endl << endl;
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


        record.push_back(DummyElement);

        system("cls");

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

void SortByName(vector<Records>& record, string OrderPreference, string SortPreference)
{
    string Repeat;

    cout << "Sort By (Ascending/Descending): ";
    cin >> OrderPreference;
    system("cls");

    auto start = high_resolution_clock::now();

    if (OrderPreference == "Ascending" || OrderPreference == "ascending") {
        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.name < b.name; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "---Sort By Name: Ascending Order---------" << endl;
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        cout << "---Function runtime: ";
        cout << duration.count() << "ms" << endl;
        return;

    }
    else if (OrderPreference == "Descending" || OrderPreference == "descending") {
        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.name > b.name; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "---Sort By Name: Descending Order--------" << endl;
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        cout << "---Function runtime: ";
        cout << duration.count() << "ms" << endl;
        return;

    }
    else
    {
        cout << "Invalid input. " << endl;
        return;
    }

}

void SortByPrice(vector<Records>& record, string OrderPreference, string SortPreference)
{
    string Repeat;

    cout << "Sort By (Ascending/Descending): ";
    cin >> OrderPreference;
    system("cls");

    auto start = high_resolution_clock::now();

    if (OrderPreference == "Ascending" || OrderPreference == "ascending") {
        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.price < b.price; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "---Sort By Price: Ascending Order--------" << endl;
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        cout << "---Function runtime: ";
        cout << duration.count() << "ms" << endl;

        return;


    }
    else if (OrderPreference == "Descending" || OrderPreference == "descending") {
        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.price > b.price; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "---Sort By Price: Descending Order-------" << endl;
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        cout << "---Function runtime: ";
        cout << duration.count() << "ms" << endl;

        return;

    }
    else
    {
        cout << "Invalid input. " << endl;
        return;
    }

}

void SortByQuantity(vector<Records>& record, string OrderPreference, string SortPreference)
{
    string Repeat;

    cout << "Sort By (Ascending/Descending): ";
    cin >> OrderPreference;
    system("cls");

    auto start = high_resolution_clock::now();

    if (OrderPreference == "Ascending" || OrderPreference == "ascending") {
        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.quantity < b.quantity; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "---Sort By Quantity: Ascending Order-----" << endl;

        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        cout << "---Function runtime: ";
        cout << duration.count() << "ms" << endl;

        return;

    }
    else if (OrderPreference == "Descending" || OrderPreference == "descending") {
        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.quantity > b.quantity; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "---Sort By Quantity: Descending Order----" << endl;
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        cout << "---Function runtime: ";
        cout << duration.count() << "ms" << endl;

        return;

    }
    else
    {
        cout << "Invalid input. " << endl;
        return;
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
    
    system("cls");

    for (int current = 1; current < record.size(); current++)
    {
        if (record[current].name == record[previous].name)
        {
            cout << "---index " << current << ": " << record[current].name << endl;
            record.erase(record.begin() + current);
            detected_dupes++;
        }
        previous++;
    }

    if (detected_dupes == 0)
    {
        system("cls");
        cout << "---No duplicates detected." << endl;
        printVector(record);
    }
    else
    {
        cout << "---has been removed and excess memory has been released. " << endl;
        printVector(record);

    }

    record.shrink_to_fit();
    return;
}

bool isSortedCheck(vector<Records> record)
{

    if(record.size() == 0 || record.size() == 1)
        return true;

    //for ascending order name sort case
    if(record[0].name < record[1].name)
    {
        for (int i = 2; i < record.size(); i++)
        {
            if (record[i - 1].name > record[i].name)
            {
                return false;
            }
        }
    }
    else
    {
        for (int i = 2; i < record.size(); i++)
        {
            if (record[i - 1].name < record[i].name)
            {
                return false;
            }
        }
    }

    return true;
}
