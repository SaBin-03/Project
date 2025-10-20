#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <sstream>
#include <fstream>

using namespace std;

class bank_record
{
public:
    string accHolder_name, accHolder_address, accHolder_phnum;
    int accHolder_accnum;
    double accHolder_balance;
    bank_record(string name, string address, string phnumber, int accnumber)
    {
        accHolder_name = name;
        accHolder_address = address;
        accHolder_phnum = phnumber;
        accHolder_accnum = accnumber;
        accHolder_balance = 0.0;
    }

    void displayAcc()
    {
        cout << "==============================================" << endl;
        cout << "Name = " << accHolder_name << endl;
        cout << "ACCOUNT number = " << accHolder_accnum << endl;
        cout << "Address = " << accHolder_address << endl;
        cout << "Phone number = " << accHolder_phnum << endl;
        cout << "Balance = $" << accHolder_balance << endl;
        cout << "==============================================" << endl;
    }
    string saveTofile(){
        stringstream ss;
        ss << "==============================================" << endl;
        ss << "Name = " << accHolder_name << endl;
        ss << "ACCOUNT number = " << accHolder_accnum << endl;
        ss << "Address = " << accHolder_address << endl;
        ss << "Phone number = " << accHolder_phnum << endl;
        ss << "Balance = $" << accHolder_balance << endl;
        ss << "==============================================" << endl;
        return ss.str();
    }
    
};

class bank_system
{
public:
    vector<bank_record> accholder_details;
    double deposite_money;
    
    void savefile(){

        ofstream file;
        file.open("file_bank_system.txt");
        for (auto &&record : accholder_details)
        {
            file << record.saveTofile();
        }
        
    }

    void createAcc()
    {
        string name, address, phnumber;
        int accnumber;

        srand(time(0));
        accnumber = 1 + rand() % 1000;

        cout << "Name of the Account holder : " << endl;
        getline(cin, name);
        // cin.ignore();

        cout << "Address of the Account holder : " << endl;
        getline(cin, address);
        // cin.ignore();

        cout << "Phone number of the Account holer : " << endl;
        getline(cin, phnumber);
        // cin.ignore();

        bank_record rec(name, address, phnumber, accnumber);
        accholder_details.push_back(rec);
        savefile();
        cout << "-- Bank Account is created successfully! --" << endl;
        cout << "== Your Account number is " << accnumber << " ==" << endl;
    }

    void previousAcc()
    {
        int searchAcc_num;
        cout << "Enter your Account number : " << endl;
        cin >> searchAcc_num;

        bool found = false;

        for (auto &&rec : accholder_details)
        {
            if (rec.accHolder_accnum == searchAcc_num)
            {
                rec.displayAcc();
                found = true;
                break;
            }
        }
        if (!found)
            cout << "❌ No records found!" << endl;
    }
    
    void moneyManage()
    {
        int searchAcc_num;
        cout << "Enter your Account number : " << endl;
        cin >> searchAcc_num;
        
        bool found = false;
        
        for (auto &&rec : accholder_details)
        {
            if (rec.accHolder_accnum == searchAcc_num)
            {
                int options;
                double deposited_money,balance,withdrawn_money;
                
                do
                {
                    cout << "1. Deposite money" << endl;
                    cout << "2. Withdraw money" << endl;
                    cout << "3. Check Balance" << endl;
                    cout << "4. Exit" << endl;

                    cout << "Enter the options :" << endl;
                    cin >> options;

                    switch (options)
                    {
                    case 1:
                        cout << "Enter the amount to be deposited $";
                        cin >> deposited_money;
                        rec.accHolder_balance += deposited_money;
                        cout << "✅ Deposited $" << deposited_money << " successfully!" << endl;
                        
                        
                        break;
                    case 2:
                        cout << "Enter the amount to be withdrawn $";
                        cin >> withdrawn_money;
                        if(withdrawn_money <= rec.accHolder_balance){
                            rec.accHolder_balance -= withdrawn_money;
                            cout << "✅ Withdrawn $" << withdrawn_money << " successfully!" << endl;
                        }    
                        else cout << "❌ Insufficient balance!" << endl;
                        
                        
                        break;
                    case 3:
                        cout << "💰 Current Balance: $" << rec.accHolder_balance << endl;
                        break;

                    case 4:
                        cout << "Exiting Money Management..." << endl;
                        break;
                        

                    default : 
                        cout << "❌ Invalid Choice!" << endl; 
                        break;
                    }
                    found = true;

                } while (options != 4);
            }
        }
        if (!found)
            cout << "❌ Account not found!" << endl;
    }
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    bank_system bank;
    int choice;
    do
    {
        cout << "---Welcome To Our Bank---" << endl;
        cout << "1. Create your bank account" << endl;
        cout << "2. Existing account" << endl;
        cout << "3. Money Management" << endl;
        cout << "4. Exit." << endl;

        cout << "--Users Choice--" << endl;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            bank.createAcc();
            break;

        case 2:
            bank.previousAcc();
            break;

        case 3:
            bank.moneyManage();
            break;

        case 4:
            cout << "👋 Thank you for banking with us!" << endl;
            break;

        default:
            cout << "❌ Invalid choice!" << endl;
            break;
        }

    } while (choice != 4);
}
