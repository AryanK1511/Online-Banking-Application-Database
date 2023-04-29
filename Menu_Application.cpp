/*
    ========== DBS311 (NCC) Group Assignment 2 ==========
    Group Members:
    1) Aryan Khurana => 145282216
    2) Bhanu Rakshita Paul => 143428217
    3) Shivkumar Virendranath Raval => 168146215
*/

#include"occi.h"
#include<iostream>
#include <iomanip>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

// OCCI Variables
Environment* env = nullptr;
Connection* conn = nullptr;

// Function prototypes
void selectLoanDetail(Connection* conn);
void updateLoanDetail(Connection* conn);
void insertLoanDetail(Connection* conn);
void deleteLoanDetail(Connection* conn);
void selectCustomer(Connection* conn);
void updateCustomer(Connection* conn);
void insertCustomer(Connection* conn);
void deleteCustomer(Connection* conn);
void selectLog(Connection* conn);
void updateLog(Connection* conn);
void insertLog(Connection* conn);
void deleteLog(Connection* conn);

// Class to handle a loan detail record
class LoanDetail
{
public:
    int err{};
    int loan_id{};
    double loan_amount{};
    double annual_interest{};
    string loan_date{};
    string maturity_date{};
    long account_number{};
    long approved_by{};
    LoanDetail() = default;
};

// Class to handle a customer record
class Customer
{
public:
    int custId{ 0 };
    string custName{};
    string custEmail{};
    string custPwd{};
    string custAddress{};
    int custadvisor{ 0 };
    long custPhone{ 0 };
};

// Class to handle a customer record
class Log
{
    int err = 0;
    double logId;
    double userId{};
    string logLocation{};
    int logSuccess{};
    string logTime{};
};

// Creating an object
LoanDetail loanDetail;

int main()
{
    // User Variables
    string str{};
    string user{};
    string pass{};
    string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

    // Providing our group details
    cout << "============================" << endl;
    cout << "\nGROUP 8 DBS311 ASSIGNMENT 2\n" << endl;
    cout << "============================" << endl;
    cout << "\nGroup Members: " << endl;
    cout << left << setw(35) << "1) Aryan Khurana";
    cout << "145282216" << endl;
    cout << left << setw(35) << "2) Bhanu Rakshita Paul";
    cout << "143428217" << endl;
    cout << left << setw(35) << "3) Shivkumar Virendranath Raval";
    cout << "168146215" << endl;
    cout << "\n============================\n" << endl;

    // Displaying a menu to the user
    size_t userChoice{ 0 };
    do
    {
        cout << "==================================" << endl;
        cout << "*** ONLINE BANKING SYSTEM ***" << endl;
        cout << "==================================" << endl;
        cout << "---------- ARYAN ----------" << endl;
        cout << "1) Create a Loan Detail" << endl;
        cout << "2) Update a Loan Detail" << endl;
        cout << "3) Delete a Loan Detail" << endl;
        cout << "4) Read a Loan Detail" << endl;
        cout << "---------- BHANU ----------" << endl;
        cout << "5) Create a Customer" << endl;
        cout << "6) Update a Customer's Address" << endl;
        cout << "7) Delete a Customer" << endl;
        cout << "8) Read a Customer's contact info" << endl;
        cout << "---------- SHIV ----------" << endl;
        cout << "9) Create a Log" << endl;
        cout << "10) Update a Log" << endl;
        cout << "11) Delete a Log" << endl;
        cout << "12) Read a Log" << endl;
        cout << "---------------------------" << endl;
        cout << "0) EXIT" << endl;
        cout << "---------------------------" << endl;
        cout << "Enter an option (0 - 12): ";
        cin >> userChoice;
        cout << endl;

        // Logging in to whichever database is chosen
        if (userChoice == 1 || userChoice == 2 || userChoice == 3 || userChoice == 4)
        {
            user = "dbs311_231ncc13";
            pass = "37011139";
        }

        else if (userChoice == 5 || userChoice == 6 || userChoice == 7 || userChoice == 8)
        {
            user = "dbs311_231ncc28";
            pass = "73722142";
        }

        else if (userChoice == 9 || userChoice == 10 || userChoice == 11 || userChoice == 12)
        {
            user = "dbs311_231ncc31";
            pass = "73211062";
        }

        // Initializing the cononection with oracle using OCCI
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(user, pass, srv);

        // Handling the user's request based upon their choice
        switch (userChoice)
        {
        case 0:
            break;
        case 1:
            insertLoanDetail(conn);
            cout << endl;
            break;
        case 2:
            updateLoanDetail(conn);
            cout << endl;
            break;
        case 3:
            deleteLoanDetail(conn);
            cout << endl;
            break;
        case 4:
            selectLoanDetail(conn);
            cout << endl;
            break;
        case 5:
            insertCustomer(conn);
            cout << endl;
            break;
        case 6:
            updateCustomer(conn);
            cout << endl;
            break;
        case 7:
            deleteCustomer(conn);
            cout << endl;
            break;
        case 8:
            selectCustomer(conn);
            cout << endl;
            break;
        case 9:
            insertLog(conn);
            cout << endl;
            break;
        case 10:
            updateLog(conn);
            cout << endl;
            break;
        case 11:
            deleteLog(conn);
            cout << endl;
            break;
        case 12:
            selectLog(conn);
            cout << endl;
            break;
        default:
            cout << "\nINVALID OPTION: Please try again ...\n" << endl;
            break;
        }

    } while (userChoice != 0);

    // Terminating the Connection
    env->terminateConnection(conn);
    Environment::terminateEnvironment(env);

    return 0;
}

// ========== Executes the PL/SQL Procedure to select Loan Details ==========
void selectLoanDetail(Connection* conn)
{
    cout << "---------- SELECT -----------" << endl;
    // Taking user input
    cout << "Loan ID: ";
    cin >> loanDetail.loan_id;

    // Using the procedure
    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN spLoandetailsSelect(:1, :2, :3, :4, :5, :6, :7, :8); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(loanDetail.err));
        stmt->setInt(2, loanDetail.loan_id);
        stmt->registerOutParam(3, Type::OCCIINT, sizeof(loanDetail.loan_amount));
        stmt->registerOutParam(4, Type::OCCISTRING, sizeof(loanDetail.loan_date));
        stmt->registerOutParam(5, Type::OCCISTRING, sizeof(loanDetail.maturity_date));
        stmt->registerOutParam(6, Type::OCCISTRING, sizeof(loanDetail.annual_interest));
        stmt->registerOutParam(7, Type::OCCIINT, sizeof(loanDetail.account_number));
        stmt->registerOutParam(8, Type::OCCIINT, sizeof(loanDetail.approved_by));

        // Executing and storing the output(s)
        stmt->executeUpdate();
        loanDetail.err = stmt->getInt(1);
        loanDetail.loan_amount = stmt->getInt(3);
        loanDetail.loan_date = stmt->getString(4);
        loanDetail.maturity_date = stmt->getString(5);
        loanDetail.annual_interest = stod(stmt->getString(6));
        loanDetail.account_number = stmt->getInt(7);
        loanDetail.approved_by = stmt->getInt(8);

        // Retrieve output parameters and print data on console
        std::cout << "Loan Amount: " << loanDetail.loan_amount << std::endl;
        std::cout << "Loan Date: " << loanDetail.loan_date << std::endl;
        std::cout << "Maturity Date: " << loanDetail.maturity_date << std::endl;
        std::cout << "Annual Interest: " << loanDetail.annual_interest << std::endl;
        std::cout << "Account Number: " << loanDetail.account_number << std::endl;
        std::cout << "Approved By: " << loanDetail.approved_by << std::endl;

        // Checking for errors
        if (loanDetail.err > 0)
        {
            cout << "\nSUCCESS: " << loanDetail.err << " row(s) selected." << endl;
        }
        else
        {
            cout << "\nERROR: No rows selected." << endl;
        }

        // Terminating the statement
        conn->terminateStatement(stmt);
    }
    catch (SQLException & sqlExcp)
    {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
}

// ========== Executes the PL/SQL Procedure to update a Loan Detail ==========
void updateLoanDetail(Connection* conn)
{
    cout << "------------ Update -----------" << endl;

    // Taking user input
    cout << "Loan ID: ";
    cin >> loanDetail.loan_id;
    cout << "Loan Amount: ";
    cin >> loanDetail.loan_amount;

    // Using the query
    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN spLoanDetailsUpdate(:1, :2, :3); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(loanDetail.err));
        stmt->setNumber(2, loanDetail.loan_id);
        stmt->setNumber(3, loanDetail.loan_amount);

        // Executing and storing the output(s)
        stmt->executeUpdate();
        loanDetail.err = stmt->getInt(1);

        // Checking for errors
        if (loanDetail.err > 0)
        {
            cout << "\nSUCCESS: " << loanDetail.err << " row(s) updated." << endl;
        }
        else
        {
            cout << "\nERROR: No rows updated." << endl;
        }

        // Terminating the connection
        conn->terminateStatement(stmt);
    }
    catch (SQLException & sqlExcp)
    {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
}

// ========== Executes the PL/SQL Procedure to insert a loan detail ==========
void insertLoanDetail(Connection* conn)
{
    cout << "---------- Insert -----------" << endl;

    // Taking user input
    cout << "Loan ID: ";
    cin >> loanDetail.loan_id;
    cout << "Loan Amount: ";
    cin >> loanDetail.loan_amount;
    cout << "Loan Date (yyyy-mm-dd) : ";
    cin >> loanDetail.loan_date;
    cout << "Maturity Date (yyyy-mm-dd) : ";
    cin >> loanDetail.maturity_date;
    cout << "Annual Interest: ";
    cin >> loanDetail.annual_interest;
    cout << "Account Number: ";
    cin >> loanDetail.account_number;
    cout << "Employee number of the employee that approved the loan: ";
    cin >> loanDetail.approved_by;

    // Using the query
    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN spLoanDetailsInsert(:1, :2, :3, to_date(:4, 'yyyy-mm-dd'), to_date(:5, 'yyyy-mm-dd'), :6, :7, :8); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(loanDetail.err));
        stmt->setNumber(2, loanDetail.loan_id);
        stmt->setNumber(3, loanDetail.loan_amount);
        stmt->setString(4, loanDetail.loan_date);
        stmt->setString(5, loanDetail.maturity_date);
        stmt->setNumber(6, loanDetail.annual_interest);
        stmt->setNumber(7, loanDetail.account_number);
        stmt->setNumber(8, loanDetail.approved_by);

        // Executing and storing the output(s)
        stmt->executeUpdate();
        loanDetail.err = stmt->getInt(1);

        // Checking for errors
        if (loanDetail.err > 0)
        {
            cout << "\nSUCCESS: " << loanDetail.err << " row(s) inserted." << endl;
        }
        else
        {
            cout << "\nERROR: No rows inserted." << endl;
            cout << "This could be due to a constraint violation, data type mismatch, or some other error." << endl;
            cout << "TIP: Ensure that the account number and the approved by already exist." << endl;
        }

        // Terminating the connection
        conn->terminateStatement(stmt);
    }
    catch (SQLException & sqlExcp)
    {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
}

// ========== Executes the PL/SQL Procedure to delete a Loan Detail ==========
void deleteLoanDetail(Connection* conn)
{
    cout << "---------- Delete ----------" << endl;

    // Taking user input
    cout << "Loan ID: ";
    cin >> loanDetail.loan_id;

    // Using the query
    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN spLoanDetailsDelete(:1, :2); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(loanDetail.err));
        stmt->setNumber(2, loanDetail.loan_id);

        // Executing and storing the output(s)
        stmt->executeUpdate();
        loanDetail.err = stmt->getInt(1);

        // Checking for errors
        if (loanDetail.err > 0)
        {
            cout << "\nSUCCESS: " << loanDetail.err << " row(s) deleted." << endl;
        }
        else
        {
            cout << "\nERROR: No rows deleted." << endl;
        }

        // Terminating the connection
        conn->terminateStatement(stmt);
    }
    catch (SQLException & sqlExcp)
    {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
}

// ========== Executes the PL/SQL Procedure to select a customer ==========
void selectCustomer(Connection* conn)
{
    cout << "***** You have selected to read customer's contact details *****" << endl;
    int err = 0;
    int cid;
    int customer_id = 0;
    string customer_name = "";
    string customer_phone = "";
    string customer_email = "";

    cout << "Enter customer ID: ";
    cin >> cid;

    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN spCustomersSelect(:1, :2, :3, :4, :5, :6); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
        stmt->setNumber(2, cid);
        stmt->registerOutParam(3, Type::OCCIINT, sizeof(customer_id));
        stmt->registerOutParam(4, Type::OCCISTRING, sizeof(customer_name));
        stmt->registerOutParam(5, Type::OCCISTRING, sizeof(customer_phone));
        stmt->registerOutParam(6, Type::OCCISTRING, sizeof(customer_email));

        stmt->executeUpdate();
        err = stmt->getInt(1);
        customer_id = stmt->getInt(3);
        customer_name = stmt->getString(4);
        customer_phone = stmt->getString(5);
        customer_email = stmt->getString(6);

        if (err > 0)
        {
            cout << "\n SUCCESS: New customer found sucessfully: " << endl;
            cout << "Customer ID:    " << customer_id << endl;
            cout << "Customer name:  " << customer_name << endl;
            cout << "Customer phone: " << customer_phone << endl;
            cout << "Customer email: " << customer_email << endl;
        }
        else
        {
            cout << "ERROR: Couldn't find record" << err << endl << endl;
        }

        conn->terminateStatement(stmt);
    }
    catch (SQLException & sqlExcp)
    {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
}

// ========== Executes the PL/SQL Procedure to update a customer ==========
void updateCustomer(Connection* conn)
{
    cout << "*****You have chosen to update a customer*****" << endl;
    int err = 0;
    int customer_id;
    string newAddress;
    cout << "Customer ID: ";
    cin >> customer_id;
    cout << "Enter new address:";
    cin >> newAddress;

    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN spCustomersUpdate(:1, :2, :3); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
        stmt->setNumber(2, customer_id);
        stmt->setString(3, newAddress);

        stmt->executeUpdate();
        err = stmt->getInt(1);

        if (err > 0)
        {
            cout << "\n SUCCESS: customer updated sucessfully!\n" << endl;
        }
        else
        {
            cout << "ERROR: Couldn't upate record \n" << endl;
        }

        conn->terminateStatement(stmt);
    }
    catch (SQLException & sqlExcp)
    {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
}

// ========== Executes the PL/SQL Procedure to insert a customer ==========
void insertCustomer(Connection* conn)
{
    cout << "***** You've selected to insert a record *****" << endl;
    Customer newCustomer;
    int err = 0;
    string address;
    cout << "Customer ID: ";
    cin >> newCustomer.custId;
    cout << "Customer name: ";
    cin >> newCustomer.custName;
    cout << "Customer email: ";
    cin >> newCustomer.custEmail;
    cout << "Customer password: ";
    cin >> newCustomer.custPwd;
    cout << "Customer address:";
    cin >> newCustomer.custAddress;
    cout << "Customer advisor: ";
    cin >> newCustomer.custadvisor;
    cout << "Customer phone: ";
    cin >> newCustomer.custPhone;

    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN spCustomersInsert(:1, :2, :3, :4, :5, :6, :7, :8); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
        stmt->setNumber(2, newCustomer.custId);
        stmt->setString(3, newCustomer.custName);
        stmt->setString(4, newCustomer.custEmail);
        stmt->setString(5, newCustomer.custPwd);
        stmt->setString(6, newCustomer.custAddress);
        stmt->setNumber(7, newCustomer.custadvisor);
        stmt->setNumber(8, newCustomer.custPhone);

        stmt->executeUpdate();
        err = stmt->getInt(1);

        if (err > 0)
        {
            cout << "\n SUCCESS: New customer inserted sucessfully!\n" << endl;
        }
        else
        {
            cout << "ERROR: Couldn't insert record \n" << endl;
        }

        conn->terminateStatement(stmt);
    }
    catch (SQLException & sqlExcp)
    {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
}

// ========== Executes the PL/SQL Procedure to delete a customer ==========
void deleteCustomer(Connection* conn)
{
    cout << "*****You have chosen to delete customer*****" << endl;
    int err = 0;
    int customer_id;
    cout << "Customer ID: ";
    cin >> customer_id;

    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN spCustomersDelete(:1, :2); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
        stmt->setNumber(2, customer_id);

        stmt->executeUpdate();
        err = stmt->getInt(1);

        if (err > 0)
        {
            cout << "\n SUCCESS: customer deleted sucessfully!\n" << endl;
        }
        else
        {
            cout << "ERROR: Couldn't delete record \n" << endl;
        }

        conn->terminateStatement(stmt);
    }
    catch (SQLException & sqlExcp)
    {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
}

// ========== Executes the PL/SQL Procedure to select a log ==========
void selectLog(Connection* conn)
{
    int err = 0;
    double logId;
    double userId{};
    string logLocation{};
    int logSuccess{};
    string logTime{};

    cout << "\n---------READ LOG CHECKED---------" << endl;
    cout << "Input LOG ID to READ its details" << endl;
    cout << "Log ID:";
    cin >> logId;
    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN  spLogsSelect(:1,:2,:3,:4,:5,:6); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
        stmt->setNumber(2, logId);
        stmt->registerOutParam(3, Type::OCCIINT, sizeof(userId));
        stmt->registerOutParam(4, Type::OCCISTRING, sizeof(logLocation));
        stmt->registerOutParam(5, Type::OCCIINT, sizeof(logSuccess));
        stmt->registerOutParam(6, Type::OCCISTRING, sizeof(logTime));

        stmt->executeUpdate();
        err = stmt->getInt(1);
        userId = stmt->getInt(3);
        logLocation = stmt->getString(4);
        logSuccess = stmt->getInt(5);
        logTime = stmt->getString(6);

        if (err > 0)
        {
            cout << endl << "Here is detail for Log Id " << logId << endl;
            cout << "\nCustomer ID  : " << userId << endl;
            cout << "Log Location : " << logLocation << endl;
            cout << "log Success  : " << logSuccess << endl;
            cout << "log Time     : " << logTime << endl;
        }
        else
        {
            cout << "ERROR: No Log Found" << err << endl;
            cout << logId << " could be INVALID login ID" << endl;
        }

        conn->terminateStatement(stmt);
    }
    catch (SQLException & sqlExcp)
    {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
}

// ========== Executes the PL/SQL Procedure to update a log ==========
void updateLog(Connection* conn)
{
    int err = 0;
    double logId;
    string logLocation{};
    int logSuccess{};

    cout << "\n---------UPDATE LOG CHECKED---------" << endl;
    cout << "\nInput LOG ID to UPDATE its details" << endl;
    cout << "Log ID: ";
    cin >> logId;
    cout << "Enter new Log Location: ";
    cin >> logLocation;
    cout << "Enter new Log Success: ";
    cin >> logSuccess;
    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN  spLogsUPDATE(:1,:2,:3,:4); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
        stmt->setNumber(2, logId);
        stmt->setString(3, logLocation);
        stmt->setNumber(4, logSuccess);

        stmt->executeUpdate();
        err = stmt->getInt(1);

        if (err > 0)
        {
            cout << endl << "Details for Log Id " << logId << " has been UPDATED" << endl;
        }
        else
        {
            cout << "ERROR: UPDATE NOT SUCCESSFUL" << err << endl;
            cout << logId << " could be INVALID login ID" << endl;
        }

        conn->terminateStatement(stmt);
    }
    catch (SQLException & sqlExcp)
    {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
}

// ========== Executes the PL/SQL Procedure to insert a log ==========
void insertLog(Connection* conn)
{
    int err = 0;
    double logId;
    double userId{};
    string logLocation{};
    int logSuccess{};
    string logTime{};

    cout << "\n---------CREATE LOG CHECKED---------" << endl;
    cout << "Enter Log ID: " << endl;
    cin >> logId;
    cout << "Enter Customer ID: " << endl;
    cin >> userId;
    cout << "Enter Log Location: " << endl;
    cin >> logLocation;
    cout << "Enter Log Success: " << endl;
    cin >> logSuccess;
    cout << "Enter Log Date(yyyy-mm-dd):" << endl;
    cin >> logTime;
    try {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN  spLogsInsert(:1,:2,:3,:4,:5,to_date(:6, 'yyyy-mm-dd')); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
        stmt->setNumber(2, logId);
        stmt->setNumber(3, userId);
        stmt->setString(4, logLocation);
        stmt->setNumber(5, logSuccess);
        stmt->setString(6, logTime);

        stmt->executeUpdate();
        err = stmt->getInt(1);

        if (err > 0) {
            cout << "\n SUCCESS:" <<logId << " login details INSERTED!" << endl;
        }
        else {
            cout << "\nERROR: Inserting UNSUCCESSFUL" << err << endl;
        }

        conn->terminateStatement(stmt);
    }
    catch (SQLException& sqlExcp) {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
}

// ========== Executes the PL/SQL Procedure to delete a log ==========
void deleteLog(Connection* conn)
{
    int err = 0;
    double logId;

    cout << "\n---------DELETE LOG CHECKED---------" << endl;
    cout << "Enter Log ID: " << endl;
    cin >> logId;

    try
    {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN  spLogsDELETE(:1,:2); END;");
        stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
        stmt->setNumber(2, logId);

        stmt->executeUpdate();
        err = stmt->getInt(1);

        if (err > 0)
        {
            cout << "\n SUCCESS:" << logId << "'s login details DELETED!" << endl;
        }
        else
        {
            cout << "\nERROR: Deleting UNSUCCESSFUL" << err << endl;
            cout << logId << " could be INVALID login ID" << endl;
        }

        conn->terminateStatement(stmt);
    }
    catch (SQLException & sqlExcp)
    {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
}
