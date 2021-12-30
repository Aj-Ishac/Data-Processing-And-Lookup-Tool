#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <list>

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
void printhistorySeq(vector<string>&);
void outputTable(vector<Records>);

void SortByName(vector<Records>&, vector<string>&, string, string);
void SortByPrice(vector<Records>&, vector<string>&, string, string);
void SortByQuantity(vector<Records>&, vector<string>&, string, string);

void InsertElement(vector<Records>&, vector<string>&);
void ModifyElement(vector<Records>&, vector<string>&);
void RemoveElement(vector<Records>&, vector<string>&);

void Search(vector<Records>, vector<string>&);
int BinarySearch(vector<Records>, int, int, string);

bool isdigitCheck(string);
bool isalphaCheck(string);
void CapacityCheck(vector<Records>);

void GenerateProductID(vector<Records>&, vector<string>&);
string GenerateKEY(string);

void ImportFile(vector<Records>&, vector<string>&);
void MergeVectors(vector<Records>&, vector<Records>);
void removeDuplicates(vector<Records>&);

int main()
{
    vector<Records> record;

    ifstream inFile("PriceList.txt");
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
    
    //NEXT    
    
    //when importing. configure a system to match 
    //string to name, float to price, int to qty
    
    //output into basefile

    //look into remembering last sortname so user
    //doesn't have to do it everytime they run func dependent on sortname

    //warning dept cleanup

    //output final result to new file

    //inventory changes

    //when duperemove, let user pick which to remove

    //force name input to be under char[12]. set char limit
    //store whatever, only print first x chars in table

    //comments

    //add base table to ui when merging


    cout << "---Base data from file-------------------" << endl;
    printVector(record);
    MenuController(record);

    outputTable(record);

    inFile.close();
    return 0;
}

void MenuController(vector<Records>& record)
{
    bool Repeat = true;
    bool isSorted = false;
    bool invalidChoice;

    char choice[12];
    string Sort_Preference, Sort_Order;
    vector<string> historySeq;


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
                //printtable: pass1, pass2, pass3
                system("cls");

                historySeq.push_back("PrintRecords");
                printhistorySeq(historySeq);

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
                        //sortbyname: pass1, pass2, pass3
                        SortByName(record, historySeq, Sort_Order, Sort_Preference);
                        isSorted = true;
                        break;

                    case '2':
                        //sortbyprice: pass1, pass2, pass3
                        SortByPrice(record, historySeq, Sort_Order, Sort_Preference);
                        isSorted = false;
                        break;

                    case '3':
                        //sortbyqty: pass1, pass2, pass3
                        SortByQuantity(record, historySeq, Sort_Order, Sort_Preference);
                        isSorted = false;
                        break;
                    }
                }
                else
                {
                    system("cls");
                    printhistorySeq(historySeq);
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
                        //insertelement: pass1, pass2, pass3
                        InsertElement(record, historySeq);
                        isSorted = false;
                        break;

                    case '2':
                        //modifyelement: pass1, pass2, pass3
                        if (isSorted == 0)
                        {
                            system("cls");
                            printhistorySeq(historySeq);
                            cout << "---Function requires records to be sorted by name!" << endl;
                            printVector(record);
                            break;
                        }

                        ModifyElement(record, historySeq);
                        isSorted = false;
                        break;

                    case '3':
                        //removelement: pass1, pass2, pass3
                        if (isSorted == 0)
                        {
                            system("cls");
                            printhistorySeq(historySeq);
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
                    printhistorySeq(historySeq);
                    cout << "---Invalid input. Digits valid only." << endl;
                    printVector(record);
                }
                break;

            case '4':
                //generateid: pass1, pass2, pass3
                GenerateProductID(record, historySeq);
                break;

            case '5':
                //search: pass1, pass2, pass3
                if (isSorted == 0)
                {
                    system("cls");
                    printhistorySeq(historySeq);
                    cout << "---Function requires records to be sorted by name!" << endl;
                    printVector(record);

                    break;
                }

                Search(record, historySeq);
                break;

            case '6':
                //import&merge file: pass1, pass2, pass3

                ImportFile(record, historySeq);
                isSorted = false;
                break;

            case '7':
                //duplicate check: pass1, pass2, pass3
                if (isSorted == 0)
                {
                    system("cls");
                    printhistorySeq(historySeq);
                    cout << "---Function requires records to be sorted by name!" << endl;
                    printVector(record);

                    //last = addEnd(last, "DuplicateCheck");
                    break;
                }
                system("cls");

                historySeq.push_back("removeDupes");
                printhistorySeq(historySeq);
                removeDuplicates(record);
                break;

            case '8':
                //diagnostics: later
                break;

            case '9':
                //quit:pass

                cout << endl;
                //last = addEnd(last, "Quit");
                return;

            case '0':
                //restart:pass
                system("cls");
                historySeq.push_back("Restart");
                printhistorySeq(historySeq);
                printVector(record);
                break;
            }
        }
        else
        {
            system("cls");
            printhistorySeq(historySeq);
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
    cout << " 4. Generate Product ID" << endl;
    cout << " 5. Search Element" << endl;
    cout << " 6. Import and Merge File" << endl;
    cout << " 7. Check for Duplicates" << endl;
    cout << " 8. Diagnostics" << endl;
    cout << " 9. Quit" << endl;
    cout << " 0. Restart" << endl;
    cout << "-----------------------------------------" << endl;

    cout << "Input choice (0-9): ";

}

void printVector(vector<Records> vector)
{
    if (vector[0].productID.size() != 0) 
    {

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

void printhistorySeq(vector<string>& historySeq)
{
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
    ofstream outputFile;
    outputFile.open("outputFile.txt");

    outputFile << "[outputFile.txt]" << endl;

    if (vector[0].productID.size() != 0)
    {
        outputFile << "---Vector.size(): " << vector.size() << endl;
        outputFile << "---vector.capacity(): " << vector.capacity() << endl;
        outputFile << "-----------------------------------------" << endl;
        outputFile << endl << "     -ID-        -Name-       -Price-   -Qty-" << endl;
        for (int i = 0; i < (int)vector.size(); i++)
        {
            outputFile << " ";
            outputFile << left << vector[i].productID << "   ";
            outputFile << setw(10) << left << vector[i].name << "   ";
            outputFile << setw(6) << right << fixed << setprecision(2) << vector[i].price << "   ";
            outputFile << setw(6) << right << vector[i].quantity << "   ";
            outputFile << endl;
        }
    }
    else
    {
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

void ImportFile(vector<Records>& record, vector<string>& historySeq)
{
    vector<Records> tempVector;
    string filename;

    cout << endl << "Import (filename.txt): ";
    cin >> filename;
        
    system("cls");
    historySeq.push_back("Import&Merge");
    printhistorySeq(historySeq);

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

void Search(vector<Records> record, vector<string>& historySeq)
{
    string ValueLookup;
    cout << endl << "Search Name: ";
    cin >> ValueLookup;



    int index = BinarySearch(record, 0, record.size(), ValueLookup);

    if(index > -1)
    {

        system("cls");

        historySeq.push_back("Search");
        printhistorySeq(historySeq);

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

void GenerateProductID(vector<Records>& record, vector<string>& historySeq)
{

    for (int i = 0; i < (int)record.size(); i++)
    {
        record[i].productID = GenerateKEY(record[i].name);
    }

    system("cls");

    historySeq.push_back("GenerateID");
    printhistorySeq(historySeq);

    cout << "---Generating product ID on record items." << endl;
    printVector(record);
}

void RemoveElement(vector<Records>& record, vector<string>& historySeq)
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
            system("cls");
            historySeq.push_back("RemoveElement");
            printhistorySeq(historySeq);

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
    printVector(record);
    return;
}

void ModifyElement(vector<Records>& record, vector<string>& historySeq)
{
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
            printhistorySeq(historySeq);

            cout << "---Modified ["
                << record[index].name << ":"
                << record[index].price << ":"
                << record[index].quantity << "] to [";
                /* << InsertName << ":"
                << InsertPrice_Float << ":"
                << InsertQuantity_Int << "] "
                << endl;*/


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
        printhistorySeq(historySeq);

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

void SortByName(vector<Records>& record, vector<string>& historySeq, string OrderPreference, string SortPreference)
{
    string Repeat;

    cout << "Sort By (Ascending/Descending): ";
    cin >> OrderPreference;

    if (OrderPreference == "Ascending" || OrderPreference == "ascending") {

        system("cls");

        historySeq.push_back("SortName-A");
        printhistorySeq(historySeq);

        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.name < b.name; });

        cout << "---Sort By Name: Ascending Order" << endl;
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        return;

    }
    else if (OrderPreference == "Descending" || OrderPreference == "descending") {

        system("cls");

        historySeq.push_back("SortName-D");
        printhistorySeq(historySeq);

        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.name > b.name; });


        cout << "---Sort By Name: Descending Order" << endl;
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        return;

    }
    else
    {
        cout << "Invalid input. " << endl;
        SortByName(record, historySeq,OrderPreference, SortPreference);
    }

}

void SortByPrice(vector<Records>& record, vector<string>& historySeq, string OrderPreference, string SortPreference)
{
    string Repeat;

    cout << "Sort By (Ascending/Descending): ";
    cin >> OrderPreference;

    auto start = high_resolution_clock::now();

    if (OrderPreference == "Ascending" || OrderPreference == "ascending") {

        system("cls");

        historySeq.push_back("SortPrice-A");
        printhistorySeq(historySeq);

        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.price < b.price; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "---Sort By Price: Ascending Order" << endl;
        printVector(record);

        cout << endl;
        cout << "---Time complexity : O(nlogn)" << endl;
        cout << "---Function runtime: ";
        cout << duration.count() << "ms" << endl;

        return;


    }
    else if (OrderPreference == "Descending" || OrderPreference == "descending") {

        system("cls");

        historySeq.push_back("SortPrice-D");
        printhistorySeq(historySeq);

        sort(record.begin(), record.end(), [](Records a, Records b)
            {return a.price > b.price; });

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "---Sort By Price: Descending Order" << endl;
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
        SortByPrice(record, historySeq, OrderPreference, SortPreference);
    }

}

void SortByQuantity(vector<Records>& record, vector<string>& historySeq, string OrderPreference, string SortPreference)
{
    string Repeat;

    cout << "Sort By (Ascending/Descending): ";
    cin >> OrderPreference;


    if (OrderPreference == "Ascending" || OrderPreference == "ascending") {

        system("cls");

        historySeq.push_back("SortQty-A");
        printhistorySeq(historySeq);

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
        printhistorySeq(historySeq);

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
        SortByQuantity(record, historySeq, OrderPreference, SortPreference);
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

    cout << "---Detected duplicates: " << endl;
    for (int current = 1; current < record.size(); current++)
    {
        if (record[current].name == record[previous].name)
        {
            cout << "---index " << current << " ["
                << record[current].name << ":"
                << record[current].price << ":"
                << record[current].quantity << "] " << endl;

            //cout << "---index " << current << ": " << record[current].name << endl;
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