#include<iostream>
#include<conio.h>
#include<fstream>
#include<string>
#include<cstdio>
#include<sstream>
#include<cstdlib>
#include<windows.h>
#include<mysql.h>



using namespace std;


int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;



class db_connectivity{


public:
    
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
        {
            cout << "Database Connected" << endl;
            cout << "Press any key to continue..." << endl;
            
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
        conn = mysql_real_connect(conn, "localhost", "root", "", "bsmsdb", 3308, NULL, 0);
        if (conn)
        {
            cout << "Database Connected To MySql" << conn << endl;
            cout << "Press any key to continue..." << endl;
            
            system("cls");
        }
        else
            cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
};



void addProduct();
void updateProduct();
void deleteProduct();
void searchProduct();
void viewProduct();
void PurchaseProduct();
void SoldProducts();
void AvailableProducts();
void quit();




bool signUp() {
    string username, password, name, IDnum, email, phone;

    getline(cin, name);

    cout << "Please Enter Your Name: " << endl;
    getline(cin, name);
    cout << "Please Enter a New Username: " << endl;
    getline(cin, username);
    cout << "Please Make a New Password: " << endl;
    getline(cin, password);
    cout << "Please Enter Your ID Number: " << endl;
    getline(cin, IDnum);
    cout << "Please Enter Your Email: " << endl;
    getline(cin, email);
    cout << "Please Enter Your Phone number: " << endl;
    getline(cin, phone);
    
    

    string insert_query = "insert into adminfile (a_username, a_password, a_name, a_idnum, a_email, a_phone ) values ('" + username + "','" + password + "','" + name + "','" + IDnum + "','" + email + "','" + phone + "')";

    const char* q = insert_query.c_str(); // c_str converts string to constant char

    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << endl << "Successfully added in database." << endl;
        Sleep(2000);
        system("cls");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}
    

  


bool loginFile() {

    string username, password;

   

    cout << "Please enter your username: " << endl;
    cin >> username;
    cout << "Please enter your password: " << endl;
    cin >> password;

    string login_query = "select * from adminfile where a_username  = '" + username + "' and a_password = '" + password + "'";
    const char* qn = login_query.c_str(); // c_str converts string to constant char
    qstate = mysql_query(conn, qn);


    if (!qstate)
    {
        res = mysql_store_result(conn); 
        if ((row = mysql_fetch_row(res)))
        {
            cout << "Logged in sucessfully!" << endl;
            system("Pause");
            return 1;
        }
        else
        {
            cout << "Wrong username or password" << endl;
            system("Pause");
            return 0;

        }
    }
    else
    {
       cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

    }
    

}





int main()
{



    while (1) {

        string ch;

        system("CLS");

        db_connectivity::ConnectionFunction();
        

        cout << " ********************************************************************************************************************** " << endl;
        cout << " *********************************************                           ********************************************** " << endl;
        cout << " ********************************************                             ********************************************* " << endl;
        cout << " *******************************************  Bookstore Management System  ******************************************** " << endl;
        cout << " ********************************************                             ********************************************* " << endl;
        cout << " *********************************************                           ********************************************** " << endl;
        cout << " **********************************************************************************************************************\n\n " << endl;
        
        
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Quit\n\n\n";

        cout << "Your Choice: ";

        cin >> ch;
        
            if (ch == "2") {
                bool signStatus = signUp();
            }
            else if (ch == "1") {
                bool status = loginFile();
                if (status) {
                    break;
                }
                else {
                    cout << "Wrong Credentials! Please try again...!" << endl;
                    _getch();
                }
            }
            else if (ch == "3") {
                return 0;
            }
            else {
                cout << "Wrong Credentials! Please try again...!"<< endl;
                _getch();
            }
            
        

    }


    while (1) {
        string choice;

        system("CLS");

        cout << " ********************************************************************************************************************** " << endl;
        cout << " *********************************************                           ********************************************** " << endl;
        cout << " ********************************************                             ********************************************* " << endl;
        cout << " *******************************************  Bookstore Management System  ******************************************** " << endl;
        cout << " ********************************************                             ********************************************* " << endl;
        cout << " *********************************************                           ********************************************** " << endl;
        cout << " **********************************************************************************************************************\n\n " << endl;

        cout << "1. Add Product" << endl;
        cout << "2. Update Product" << endl;
        cout << "3. Delete Product" << endl;
        cout << "4. Search Product" << endl;
        cout << "5. View Product" << endl;
        cout << "6. Purchase Product" << endl;
        cout << "7. Sold Products" << endl;
        cout << "8. Available Products" << endl;
        cout << "0. Quit\n\n\n";

        cout << "Your Choice: ";

        cin >> choice;



        if (choice == "1") {
            system("CLS");
            addProduct();
        }
        else if (choice == "2") {
            system("CLS");
            updateProduct();
        }
        else if (choice == "3") {
            system("CLS");
            deleteProduct();
        }
        else if (choice == "4") {
            system("CLS");
            searchProduct();
        }
        else if (choice == "5") {
            system("CLS");
            viewProduct();
        }
        else if (choice == "6") {
            system("CLS");
            PurchaseProduct();

        }
        else if (choice == "7") {
            system("CLS");
            SoldProducts();
        }
        else if (choice == "8") {
            system("CLS");
            AvailableProducts();
        }
        else if (choice == "0") {
           break;

        }
        else {
            cout << "Wrong input!! Please try again!" << endl;
            _getch();
        }
    }


    return 0;
}




void addProduct() {
    string ISBN, title, author, edition, publication, price, quantity;
    getline(cin, ISBN);
    cout << " ********************************************************************************************************************** " << endl;
    cout << " ************************************************ *** ADD PRODUCT *** ************************************************* " << endl;
    cout << " **********************************************************************************************************************\n\n " << endl;
    
        cout << "Enter ISBN : ";
        getline(cin, ISBN);
        
        cout << "Enter Title : ";
        getline(cin, title);
        
        cout << "Enter Author : ";
        getline(cin, author);
        
        cout << "Enter Edition : ";
        getline(cin, edition);

        cout << "Enter Publication : ";
        getline(cin, publication);

        cout << "Enter Price : ";
        getline(cin, price);

        cout << "Enter Quantity : ";
        getline(cin, quantity);

        

        string insert_query = "insert into bookinfo (b_ISBN, b_title, b_author, b_edition, b_publication, price, b_quantity) values ('" + ISBN + "','" + title + "','" + author + "','" + edition + "','" + publication + "','" + price + "','" + quantity + "')";

        const char* q = insert_query.c_str(); // c_str converts string to constant char

        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << endl << "Successfully added in Database." << endl;
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }


        cout << "\n Product added Succesfully!\n";
        cout << "Press any key to continue....";
        _getch();
    
    
};




void PurchaseProduct(){
    
    system("CLS");

    cout << " ********************************************************************************************************************** " << endl;
    cout << " ********************************************* *** PURCHASE PRODUCT *** *********************************************** " << endl;
    cout << " **********************************************************************************************************************\n\n " << endl;

    // Variables
    char choose;
    string getId = "";
    string itemId[1500];
    int qnt[1500];
    string q;
    string itemName[1500];
    char CHOOSEmodifyORpurchase;
    int itemIndex = 0;
    float totalPrice = 0.0;
    bool purchase, itemFalse = false;

    string ISBN[1500];
    string edition[1500];
    string title[1500];
    string author[1500];
    string publication[1500];
    string price[1500];
    string storeQuantity[1500];
    int storeIndex = 0, storeIndexN = 0;
    // Variables End

    cout << "PURCHASE PRODUCT" << endl << endl;
   

    qstate = mysql_query(conn, "select * from bookinfo");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            if (atoi(row[6]) >= 0)
            {
                cout << "b_ISBN: " << row[0] << "\nb_title: " << row[1] << "\nb_author: " << row[2] << "\nb_edition: " << row[3] << "\nb_publication: " << row[4] << "\nprice: " << row[5]  << endl << endl;
                ISBN[storeIndex] = row[0];
                title[storeIndex] = row[1];
                author[storeIndex] = row[2];
                edition[storeIndex] = row[3];
                publication[storeIndex] = row[4];
                price[storeIndex] = row[5];
                storeQuantity[storeIndex] = row[6];
                storeIndex++;
            }
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    char ch;
    
    for (itemIndex = 0;;itemIndex++)
    {
        cout << "Enter a Book ISBN (e to exit): ";
        cin >> getId;
        if (getId == "e")
        {
            break;
        }
        else
        {
            while (1) {
            cout << "Enter Quantity: ";
            cin >> q;
            try {
                if (stoi(q)) {
                    break;
                }
                else {
                    cout << "Invalid " << endl;
                }
            }
            catch (exception e) {
                cout << "Invalid " << endl;

            }
        }
            for (int i = 0; i < storeIndex; i++)
            {
                if (getId == ISBN[i])
                {
                    int quant = stoi(q);

                    if ((stoi(storeQuantity[i]) < quant)) {
                        cout << "Stock amount : " << storeQuantity[i] << endl;
                        cout << "Insert valid quantity" << endl;
                        itemFalse = true;
                        break;
                    }
                    else {
                        itemId[itemIndex] = getId;
                        qnt[itemIndex] = stoi(q);
                        itemFalse = false;
                        break;
                    }
                }
                else
                {
                    itemFalse = true;
                }
            }
            if (itemFalse == true)
            {
                cout << "Enter a valid ISBN." << endl;
                itemIndex--;
                itemFalse = false;
                
            }
            
        }
    }

    cout << "You chose these Book ISBN: ";
    for (int i = 0; i < itemIndex; i++)
    {
        cout << itemId[i] << " ";
    }

CHOOSEmodifyORpurchase:
    cout << endl << "Do you want to modify products(m) or purchase these products(p): ";
    cin >> CHOOSEmodifyORpurchase;

    if (CHOOSEmodifyORpurchase == 'm')
    {
        for (int i = 0;;i++)
        {
            cout << "Remove Book ISBN (q to quit): ";
            cin >> getId;
            if (getId == "q")
            {
                break;
            }
            else
            {
                
                for (int j = 0;j < itemIndex;j++)
                {
                    if (itemId[j] == getId)
                    {
                        for (int k = j; k < itemIndex; k++)
                        {
                            itemId[k] = itemId[k + 1];
                        }
                        itemId[itemIndex--] = "\0";
                    }
                }
            }
        }

        cout << "You chose these Books ISBN: ";
        for (int i = 0; i < itemIndex; i++)
        {
            cout << itemId[i] << " ";
        }

        goto CHOOSEmodifyORpurchase;
    }
    else if (CHOOSEmodifyORpurchase == 'p')
    {

        bool purchase = false;

        for (int i = 0; i < itemIndex; i++)
        {
            string price_query = "select price from bookinfo where b_ISBN = '"+itemId[i]+"'";
            const char* price_q = price_query.c_str(); // c_str converts string to constant char

            qstate = mysql_query(conn, price_q);
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            totalPrice = totalPrice + atoi(row[0]) * qnt[i];


            int tmp = qnt[i];
            string tmpstr;
            stringstream streamqnt;
            streamqnt << tmp;
            streamqnt >> tmpstr;

            string quantity;
            stringstream strquan;
            strquan << tmp;
            strquan >> quantity;

            string insert_query = "update bookinfo set sold = sold +" + quantity + ", b_quantity = b_quantity - " + quantity + " where b_ISBN = '" + itemId[i] + "'";
            const char* q = insert_query.c_str(); // c_str converts string to constant char

            qstate = mysql_query(conn, q);
            
            purchase = true;

        }

        if (purchase == true)
        {
            cout << endl << "Purchase Successfully Done!" << endl;
            cout << endl << "Total Price: " << totalPrice <<" RM "<< endl;
        }
    }

    // Exit Code
    cout << "Press any key to continue....";
    _getch();
}





void updateProduct() {
   
    system("CLS");

    cout << " ********************************************************************************************************************** " << endl;
    cout << " *********************************************** *** UPDATE PRODUCT *** *********************************************** " << endl;
    cout << " **********************************************************************************************************************\n\n " << endl;

    string updateISBN, choice;

    
    string ISBN, title, author, edition, publication, price, quantity;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForISBN = 0;

    string bookISBN = "";
    string booktitle = "";
    string bookauthor = "";
    string bookedition = "";
    string bookpublication = "";
    int bookprice = "";
    string bookquantity = "";



    while (1) {
        system("CLS");

    try
    {
        cout << endl;
        cout << "Enter ISBN: ";
        cin >> ISBN;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid ISBN." << endl;
        HaveException = true;
        system("CLS");
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << ISBN;
        streamid >> strid;


        if (NotInDatabase == false)
        {
                string findbyid_query = "select * from bookinfo where b_ISBN = '" + ISBN + "'";
                const char* qi = findbyid_query.c_str();
                qstate = mysql_query(conn, qi);

                if (!qstate)
                {
                    int found = 0;
                    res = mysql_store_result(conn);
                    cout << endl;
                    while ((row = mysql_fetch_row(res)))
                    {
                        found = 1;
                        cout << "ISBN: " << row[0] << "\nTITLE: " << row[1] << "\nAUTHOR: " << row[2] << "\nEDITION: " << row[3] << "\nPUBLICATION: " << row[4] << "\nPRICE: " << row[5] << "\nQUANTITY: " << row[6] << endl << endl;
                        
                        booktitle = row[1];
                        bookauthor = row[2];
                        bookedition = row[3];
                        bookpublication = row[4];
                        bookprice = row[5];
                        bookquantity = row[6];

                    }
                    if (found == 0) {
                        cout << "Not found" << endl;
                        _getch();
                        continue;
                    }
                }
                else
                {
                    cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
                }

                cin.ignore(1, '\n');
               
                cout << "Enter Title (N to not change): ";
                getline(cin, title);
                if (title == "N")
                {
                    title = booktitle;
                }
                cout << "Enter Author (N to not change): ";
                getline(cin, author);
                if (author == "N")
                {
                    author = bookauthor;
                }
                cout << "Enter Edition (N to not change): ";
                getline(cin, edition);
                if (edition == "N")
                {
                    edition = bookedition;
                }
                cout << "Enter Publication (N to not change): ";
                cin >> publication;
                if (publication == "N")
                {
                    publication = bookpublication;
                }
                cout << "Enter Price (N to not change): ";
                cin >> price;
                if (price == "N")
                {
                    price = bookprice;
                }
                cout << "Enter Quantity (N to not change): ";
                cin >> quantity;
                if (quantity == "N")
                {
                    quantity = bookquantity;
                }


                string update_query = "update bookinfo set b_title='" + title + "', b_author='" + author + "', b_edition ='" + edition + "', b_publication ='" + publication + "', price ='" + price + "', b_quantity ='" + quantity + "' where b_ISBN='" + ISBN + "'";
                const char* qu = update_query.c_str();
                qstate = mysql_query(conn, qu);
                

                if (!qstate)
                {
                    cout << endl << "Successfully Saved In Database!" << endl;
                }
                else
                {
                    cout << "Failed To Update!" << mysql_errno(conn) << endl;
                }


                int flag = 0;
                while (1) {

                    cout << "\nDo you wanna update any product?\n[1]Yes\n[2]No\n\nYour choice : ";
                    cin >> choice;

                    if (choice == "2") {
                        flag = 1;
                        break;
                    }
                    else if (choice != "1") {
                        cout << "Wrong Input!!" << endl;
                    }
                    else if (choice == "1") {
                        break;
                    }
                }
                if (flag == 1) {
                    break;

                }

            }

        



        }
    
    }

        
        
    

};





void deleteProduct() {
    
    cout << " ********************************************************************************************************************** " << endl;
    cout << " *********************************************** *** DELETE PRODUCT *** *********************************************** " << endl;
    cout << " **********************************************************************************************************************\n\n " << endl;

    string ISBN;
    
    
    
    bool HaveException = false, NotInDatabase = false;


    try
    {
        cout << endl;
        cout << "Enter ISBN: ";
        cin >> ISBN;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid TITLE." << endl;
        HaveException = true;
        system("CLS");
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << ISBN;
        streamid >> strid;

        if (NotInDatabase == false)
        {
            string delete_query = "delete from bookinfo where b_ISBN = '" + ISBN + "'";
            const char* qd = delete_query.c_str();
            qstate = mysql_query(conn, qd);

            if (!qstate)
            {
                cout << "Successfully Deleted From Database." << endl;
            }
            else
            {
                cout << "Failed To Delete!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Book Not Found in database." << endl;
        }
    }

    

    cout << "Press any key to continue....";
    _getch();

};





void AvailableProducts(){
    
    system("CLS");

    cout << " ********************************************************************************************************************** " << endl;
    cout << " ********************************************* *** AVAILABLE PRODUCT *** ********************************************** " << endl;
    cout << " **********************************************************************************************************************\n\n " << endl;

    // Variables
    char choose;
    // Variables End

    
    cout << "Products In Stock" << endl << endl;

    qstate = mysql_query(conn, "select b_title, b_author, price, b_quantity from bookinfo");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            if (atoi(row[3]) > 0)
            {
                cout << "TITLE: " << row[0] << "\nAUTHOR: " << row[1] << "\nPRICE: " << row[2] << "\nQUANTITY: " << row[3] << endl << endl;
            }
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    cout << "Press any key to continue....";
    _getch();
}





void searchProduct() {
    
    cout << " ********************************************************************************************************************** " << endl;
    cout << " ********************************************** *** SEARCH PRODUCT *** ************************************************ " << endl;
    cout << " **********************************************************************************************************************\n\n " << endl;

    string ISBN;
    int choice;
    bool print = false;
    while (1) {
        system("CLS");
        int found = 0;

        cout << "Search Product\n";
        
        cout << "ENTER ISBN : ";
        cin >> ISBN;

        string findbyid_query = "select * from bookinfo where b_ISBN = '" + ISBN + "'";
        const char* qi = findbyid_query.c_str();
        qstate = mysql_query(conn, qi);

        if (!qstate)
        {
            res = mysql_store_result(conn);
            while ((row = mysql_fetch_row(res)))
            {
                found = 1;
                cout << "ISBN: " << row[0] << "\nTITLE: " << row[1] << "\nAUTHOR: " << row[2] << "\nEDITION: " << row[3] << "\nPUBLICATION: " << row[4] << "\nPRICE: " << row[5] << "\nQUANTITY: " << row[6] << endl << endl;
            }
            if (found == 0) {
                cout << "Not Found" << endl;

                cout << "\nDo you wanna continue searching?\n[1]Yes\n[2]No\n\nYour choice : ";
                cin >> choice;

                if (choice == 2) {
                    break;
                }else
                    continue;
            }
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        cout << "\nDo you wanna continue searching?\n[1]Yes\n[2]No\n\nYour choice : ";
        cin >> choice;
        
        if (choice == 2) {
            break;
        }
    }



};





void SoldProducts(){

    system("CLS");

    cout << " ********************************************************************************************************************** " << endl;
    cout << " ************************************************ *** SOLD PRODUCT *** ************************************************ " << endl;
    cout << " **********************************************************************************************************************\n\n " << endl;

    // Variables
    char choose;
    // Variables End


    

    qstate = mysql_query(conn, "select b_title, b_author, b_edition, b_publication, price, sum(sold) from bookinfo group by b_title");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "TITLE: " << row[0] << "\nAUTHOR: " << row[1] << "\nEDITION: " << row[2] << "\nPUBLICATION: " << row[3] << "\nPRICE: " << row[4] << "\nSOLD AMOUNT: " << row[5] << endl << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    // Exit Code
    cout << "Press any key to continue....";
    _getch();

}





void viewProduct() {
    
    cout << " ********************************************************************************************************************** " << endl;
    cout << " ************************************************ *** VIEW PRODUCT *** ************************************************ " << endl;
    cout << " **********************************************************************************************************************\n\n " << endl;

    qstate = mysql_query(conn, "select * from bookinfo");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "ISBN: " << row[0] << "\nTITLE: " << row[1] << "\nAUTHOR: " << row[2] << "\nEDITION: " << row[3] << "\nPUBLICATION: " << row[4] << "\nPRICE: "<<row[5]<< "\nQUANTITY: " << row[6] << endl << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    
    cout << "Press any key to continue....";
    _getch();

}
void quit() {
    _exit(1);
};












