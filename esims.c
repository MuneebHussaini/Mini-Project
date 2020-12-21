#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>

int cash_balance = 0; //External variable to store Cash Balance which can be accessed throughout the program

void clear(); //Clears screen when called

void balance(); //Updates cash_balance variable and displays Cash Balance when called

void Employee(); //Displays Employee Interface if Login is successful
int EmployeeLogin(); //Verifies Employee Identity

void CheckStocks(); //Enables Employee to Check Stock Quantity 
void OrderShipments(); //Enables Employee to Order New Shipments
void ViewShipments(); //Enables Employee to View Previous Shipments

void ViewFeatures(); //Enables User to View Features for a single product

void CompareProducts(); //Enables User to Compare Features of several products

//CompareProducts() function branches into 2 functions to handle mobile Feature Comparison and Laptop Feature Comparison
//CompareProducts() also reads the number of products to be compared and passes them to CompareMobiles() and CompareLaptops()
void CompareMobiles(int n);
void CompareLaptops(int n);

void Customer(); //Displays Customer Interface
void CustomerRegistry(); //Enables Customers to create new Customer Accounts
void CustomerLogin(); //Verifies Customer Identity if Customer Account already exists

void LoggedInCustomer(char Account[]); //Displays Logged In Customer Interface, Account name is passed to this function
void RegularCustomer(); //Displays Regular Customer Interface

void BuyProducts(int flag, char Account[]); //Enables Customer to Buy Products
//flag variable is used to toggle between Logged In and Registered Customer, Account name is passed if Customer is Logged In

void PreviousPurchases(char Account[35]); //Enables Logged In Customer to View Previous Purchases made using that Customer Account
int RedeemCoupons(char coupon[]); //Called by BuyProducts() Function if Customer has a Coupon Code and verifies the code

void set_quantity(char id[], int quantity); //Changes Quantity of a product depending on New Purchase/Shipment
int get_quantity(char id[]); //Returns Quantity of selected product

void features(char id[]); //Displays features of product selected when Customer is selecting products to purchase

void product_name(char id[], char name[]); //Assigns Product Name to name[] String
int product_price(char id[]); //Returns Product Price

char* set_product(); //Used across the program to enable User to select product
//set_product() function branches into mobile() and laptop() functions which display Menus to select Mobile/Laptop brand

char* mobiles();
char* laptops();
//mobile() and laptop() functions branch into several functions corresponding to each brand

//Each brand function finally enables User to select product and then returns its ID as a string
char* oneplus_mobiles();
char* xiaomi_mobiles();
char* samsung_mobiles();
char* apple_mobiles();

char* hp_laptops();
char* dell_laptops();
char* asus_laptops();
char* lenovo_laptops();

int main()
{
    int c;
    char s[100];

    //Cash Balance is assigned to the cash_balance variable at the start of the program
    FILE *Balance;
    Balance = fopen("balance.txt", "r");
    fscanf(Balance, "%s", s);
    cash_balance = atoi(s);
    fclose(Balance);

    do //Displays Initial Menu to continue as Employee or Customer or to Exit the Program
    {
        printf("\n\n\t\t\t\tINVENTORY MANAGEMENT SYSTEM\n");
        printf("\n\t\tPRESS:");
        printf("\n\t\t1 TO CONTINUE AS EMPLOYEE");
        printf("\n\t\t2 TO CONTINUE AS CUSTOMER");
        printf("\n\t\t3 TO EXIT");
        printf("\n\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        system("cls");
        switch(c)
        {
            case 1: Employee();
                    clear();
                    break;
            case 2: Customer();
                    clear();
                    break;
            case 3: printf("\n\t\tEXITING THE SYSTEM...\n");
                    break;
            default:printf("\n\t\tINVALID INPUT...\n");
                    break;
        }
    }while(c != 3);
    return 0;
}

void balance() //Updates cash_balance variable and displays Cash Balance when called
{
    FILE *Balance;
    printf("\n\t\tCURRENT CASH BALANCE: %d", cash_balance);
    Balance = fopen("balance.txt", "w"); //Cash Balance is stored in balance.txt
    fprintf(Balance, "%d", cash_balance);
    fclose(Balance);
    clear();
}

void Employee() //Displays Employee Interface when called from Main Menu of main() function, if login is successful
{
    int c;
    c = EmployeeLogin(); //Verifies Employee Identity by calling EmployeeLogin() function
    system("cls");
    if(c == 0) //Program returns to main() function if login fails
    {
        printf("\n\n\t\tLOG IN FAILED DUE TO INCORRECT ID OR PASSWORD\n");
        return;
    }
    printf("\n\t\tLOGGED IN AS EMPLOYEE\n"); //Employee Interface is displayed if Login is successful
    do
    {
        printf("\n\n\t\t\t\tINVENTORY MANAGEMENT SYSTEM\n");
        printf("\n\t\t\t\t\tEMPLOYEE MENU");
        printf("\n\t\tPRESS:");
        printf("\n\t\t1 TO CHECK STOCKS");\
        printf("\n\t\t2 TO CHECK CASH BALANCE");
        printf("\n\t\t3 TO ORDER PRODUCT SHIPMENTS");
        printf("\n\t\t4 TO VIEW PREVIOUS SHIPMENTS");
        printf("\n\t\t5 TO VIEW PRODUCT FEATURES");
        printf("\n\t\t6 TO COMPARE PRODUCT FEATURES");
        printf("\n\t\t7 to EXIT TO MAIN MENU");
        printf("\n\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        system("cls");
        switch(c)
        {
            case 1: CheckStocks();
                    clear();
                    break;
            case 2: balance();
                    break;
            case 3: OrderShipments();
                    clear();
                    break;
            case 4: ViewShipments();
                    clear();
                    break;
            case 5: ViewFeatures();
                    clear();
                    break;
            case 6: CompareProducts();
                    clear();
                    break;
            case 7: printf("\n\t\tEXITING TO MAIN MENU...\n");
                    break;
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(c != 7);
}

int EmployeeLogin() //Verifies Employee Identity
{
    char EmployeeIDs[10][10] = {"101", "102", "103", "104", "105", "106", "107", "108"}; //Valid Employee identities are stored in 2D String
    char Account[10], File[10], Password[31], CorrectPassword[31], *s = ".txt", c;
    int i;
    FILE *EmployeeAccount;
    printf("\n\t\tENTER EMPLOYEE ID: "); //Employee ID is taken as input
    scanf("%s", Account);
    strcpy(File, Account);
    strcat(File, s);
    EmployeeAccount = fopen(File, "r");
    for(i = 0; i < 8; i++)
    {
        if(strcmp(EmployeeIDs[i], Account) == 0)
        {
            printf("\n\t\tENTER PASSWORD: "); //Password is taken as input
            scanf("%s", Password);
            //Passowrd is verified
            fscanf(EmployeeAccount, "%s", CorrectPassword);
            fclose(EmployeeAccount);
            if(strcmp(CorrectPassword, Password) == 0)
            {
                return 1; //Function returns 1 if Password is correct
            }
            else
            {
                return 0; //Function returns 0 if Password is wrong
            }
        }
    }
    return 0; //Function returns 0 if ID entered is not found
}

void CheckStocks() //Enables Employee to Check Stock Quantity 
{
    char id[10], name[100];
    printf("\n\n\t\t\t\t\tCHECK STOCKS");
    strcpy(id, set_product());
    product_name(id, name);
    printf("\n\t\tPRODUCT: %s", name);
    printf("\n\t\tQUANTITY: %d", get_quantity(id)); //Quantity is Displayed using get_quantity() function
}

void OrderShipments() //Enables Employee to Check Stock Quantity 
{
    //Time variables
    time_t rawtime;
    struct tm *timeinfo;

    char *s, *a = "";
    int i, n, cost = 0;
    FILE *fp;
    printf("\n\n\t\t\t\t\tORDER SHIPMENTS");
    printf("\n\n\t\tENTER NUMBER OF DIFFERENT PRODUCTS: "); //Number of Products is taken as input
    scanf("%d", &n);
    char Products[n][10];
    int NewQuantity[n];
    int OldQuantity[n];
    int Prices[n];
    for(i = 0; i < n; i++)
    {
        printf("\n\n\t\tSELECT PRODUCT %d\n", i + 1);
        strcpy(Products[i], set_product()); //Product is Selected
        OldQuantity[i] = get_quantity(Products[i]); //Current Quantity of product is stored in array
        Prices[i] = product_price(Products[i]) * 0.8; //Product Price is stored in array
        printf("\n\n\t\tENTER PRODUCT QUANTITY: ");
        scanf("%d", &NewQuantity[i]); //New Quantity is stored
    }

    //Summary of Products selected is displayed
    printf("\n\n\t\tPRODUCT ID\t\t\tQUANTITY\tPRICE");
    for(i = 0; i < n; i++)
    {
        printf("\n\t\t%s  \t\t\t\t%d\t\t%d", Products[i], NewQuantity[i], Prices[i]);
        cost = cost + (NewQuantity[i] * Prices[i]);
    }

    //Total Cost is Displayed
    printf("\n\n\t\tTOTAL COST: %d", cost);

    if(cost > cash_balance) //Shipment is cancelled if it cannot be afforded
    {
        printf("\n\n\t\tINSUFFICIENT BALANCE AVAILABLE");
        return;
    }

    //Shipment is confirmed
    printf("\n\n\t\tENTER 1 TO CONFIRM SHIPMENT: ");
    scanf("%d", &i);
    if(i != 1)
    {
        printf("\n\n\t\tCONFIRMATION FAILED...");
        return;
    }

    //Cash Balance is updated
    cash_balance = cash_balance - cost;
    balance();

    printf("\n\n\t\tSHIPMENT CONFIRMED");

    //Shipment Details are stored in file along with date and time
    fp = fopen("PreviousShipments.txt", "a");
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fprintf(fp, "\n\n\t\t%s\n", asctime(timeinfo));
    fprintf(fp, "\n\t\tPRODUCT ID\t\t\tQUANTITY\tPRICE%s", a);
    for(i = 0; i < n; i++)
    {
        set_quantity(Products[i], OldQuantity[i] + NewQuantity[i]);
        fprintf(fp, "\n\t\t\t%s  \t\t\t\t%d\t\t\t%d", Products[i], NewQuantity[i], Prices[i]);
    }
    fclose(fp);
}

void ViewShipments() //Enables Employee to View Previous Shipments
{
    FILE *fp;
    char c;
    printf("\n\n\t\t\t\t\tSHIPMENT HISTORY");
    fp = fopen("PreviousShipments.txt", "r"); //Previous Shipment details are stored in PreviousShipments.txt
    c = getc(fp);
    while(c != EOF)
    {
        putch(c);
        c = getc(fp);
    }
    fclose(fp);
}

void Customer() //Displays Customer Interface when called from Main Menu of main() function
{
    int c;
    do
    {
        printf("\n\n\t\t\t\tINVENTORY MANAGEMENT SYSTEM\n");
        printf("\n\t\t\t\t\tCUSTOMER MENU");
        printf("\n\t\tPRESS:");
        printf("\n\t\t1 TO CREATE A NEW ACCOUNT");
        printf("\n\t\t2 TO LOG IN USING AN EXISTING ACCOUNT");
        printf("\n\t\t3 TO CONTINUE WITHOUT LOGGING IN");
        printf("\n\t\t4 TO RETURN TO MAIN MENU");
        printf("\n\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        system("cls");
        switch(c)
        {
            case 1: CustomerRegistry();
                    clear();
                    break;
            case 2: CustomerLogin();
                    clear();
                    break;
            case 3: RegularCustomer();
                    clear();
                    break;
            case 4: printf("\n\t\tEXITING TO MAIN MENU...\n");
                    break;
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(c!=4);
}

void CustomerRegistry() //Enables Customers to create new Customer Accounts
{
    char Account[35], Purchases[37], Password[35], Password1[35], Password2[35], *s = ".txt";
    FILE *CustomerAccount;
    printf("\n\t\tENTER ACCOUNT NAME (Max 30 Characters): "); //New Account Name is taken as input
    scanf("%s", Account);
    strcpy(Purchases, Account);
    strcat(Account, ".txt");
    strcat(Purchases, "PH.txt");
    CustomerAccount = fopen(Account, "r");
    if(CustomerAccount != NULL)
    {
        printf("\n\t\tACCOUNT NAME TAKEN\n");
        fclose(CustomerAccount);
        return;
    }
    printf("\n\t\tENTER PASSWORD (Max 30 Characters): "); //Password is taken as input
    scanf("%s", Password1);
    printf("\n\t\tCONFIRM PASSWORD: "); //Password is confirmed
    scanf("%s", Password2);
    if(strcmp(Password1, Password2) == 0) //New Account is created if Password is confirmed
    {
        strcpy(Password, Password1);
        CustomerAccount = fopen(Account, "w");
        fprintf(CustomerAccount, "%s", Password);
        printf("\n\t\tNEW CUSTOMER ACCOUNT SUCCESSFULLY CREATED\n");
        fclose(CustomerAccount);
        CustomerAccount = fopen(Purchases, "w"); //New Purchase History File is created for Customer
        fclose(CustomerAccount);
    }
    else
    {
        printf("\n\t\tPASSWORD CONFIRMATION FAILED\n");
    }   
}

void CustomerLogin() //Verifies Customer Identity if Customer Account already exists
{
    char Account[35], File[40], Password[35], CorrectPassword[35], c;
    int i;
    FILE *CustomerAccount;
    printf("\n\t\tENTER CUSTOMER ACCOUNT NAME: "); //Account Name is taken as input
    scanf("%s", Account);
    strcpy(File, Account);
    strcat(File, ".txt");
    CustomerAccount = fopen(File, "r");
    if(CustomerAccount == NULL) //If Account is not found
    {
        printf("\n\t\tACCOUNT NAME DOES NOT EXIST\n");
        return;
    }
    printf("\n\t\tENTER PASSWORD: "); //Password is taken as input
    scanf("%s", Password);
    fscanf(CustomerAccount, "%s", CorrectPassword);
    fclose(CustomerAccount);
    if(strcmp(CorrectPassword, Password) == 0) //Password is verified
    {
        printf("\n\t\tLOGGED IN AS REGISTERED CUSTOMER\n");
        clear();
        LoggedInCustomer(Account); //Program moves to Logged In Customer Interface if Login is successful
        return;
    }
    printf("\n\t\tINCCORECT PASSWORD");
    return; //Program returns to Customer Interface if Login fails
}

void LoggedInCustomer(char Account[35]) //Displays Logged In Customer Interface, Account name is passed to this function
{
    int c;
    do
    {
        printf("\n\n\t\t\t\tINVENTORY MANAGEMENT SYSTEM\n");
        printf("\n\t\t\t\t\tCUSTOMER MENU");
        printf("\n\t\tPRESS:");
        printf("\n\t\t1 TO BUY PRODUCTS");
        printf("\n\t\t2 TO VIEW PREVIOUS PURCHASES");
        printf("\n\t\t3 TO VIEW PRODUCT FEATURES");
        printf("\n\t\t4 TO COMPARE PRODUCT FEATURES");
        printf("\n\t\t5 TO EXIT");
        printf("\n\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        system("cls");
        switch(c)
        {
            case 1: BuyProducts(1, Account);
                    clear();
                    break;
            case 2: PreviousPurchases(Account);
                    clear();
                    break;
            case 3: ViewFeatures();
                    clear();
                    break;
            case 4: CompareProducts();
                    clear();
                    break;
            case 5: printf("\n\t\tEXITING TO MAIN MENU...\n");
                    break;
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(c!=5);
}

void RegularCustomer() //Displays Regular Customer Interface
{
    int c;
    do
    {
        printf("\n\n\t\t\t\tINVENTORY MANAGEMENT SYSTEM\n");
        printf("\n\t\t\t\t\tCUSTOMER MENU");
        printf("\n\t\tPRESS:");
        printf("\n\t\t1 TO BUY PRODUCTS");
        printf("\n\t\t2 TO VIEW PRODUCT FEATURES");
        printf("\n\t\t3 TO COMPARE PRODUCT FEATURES");
        printf("\n\t\t4 TO EXIT");
        printf("\n\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1: BuyProducts(0, " ");
                    clear();
                    break;
            case 2: ViewFeatures();
                    clear();
                    break;
            case 3: CompareProducts();
                    clear();
                    break;
            case 4: printf("\n\t\tEXITING TO MAIN MENU...\n");
                    break;
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(c!=4);
}

void BuyProducts(int flag, char Account[35]) //Enables Customer to Buy Products
//flag variable is used to toggle between Logged In and Registered Customer, Account name is passed if Customer is Logged In
{
    //Time variables
    time_t rawtime;
    struct tm *timeinfo;

    char *s, *a = "", name[100], File[40], coupon[10];
    int i, x, price, cost = 0, c = 1, n = 0;
    FILE *fp;
    printf("\n\n\t\t\t\t\tBUY PRODUCTS");
    char Products[10][10];
    int Quantity[10];
    int OldQuantity[10];
    int Prices[10];
    do
    {
        printf("\n\n\t\tSELECT PRODUCT %d\n", n + 1);
        strcpy(Products[n], set_product()); //Product is Selected

        //Product Name, Price and Features are Displayed
        product_name(Products[n], name);
        price = product_price(Products[n]);
        printf("\n\n\t\tPRODUCT: %s", name);
        printf("\n\n\t\tPRICE: %d", price);
        printf("\n\t\tFEATURES:\n");
        features(Products[n]);

        //Customer can confirm selection of product
        printf("\n\t\tENTER 1 TO SELECT THIS PRODUCT TO BUY: ");
        scanf("%d", &c);
        if(c == 1)
        {
            printf("\n\n\t\tPRODUCT: %s SELECTED", name);
            n++;
        }
        else
        {
            printf("\n\n\t\tPRODUCT NOT SELECTED");
        }

        //Customer can choose to continue selection
        printf("\n\t\tENTER 1 TO CONTINUE SELECTING OTHER PRODUCTS: ");
        scanf("%d", &c);
    }while(c == 1);
    printf("\n\n\t\tPRODUCT SELECTION HAS STOPPED");
    if(n == 0)
    {
        return;
    }
    i = 0;
    while(i < n)
    {
        OldQuantity[i] = get_quantity(Products[i]); //Current Quantity of product is stored in array
        Prices[i] = product_price(Products[i]); //Product Price is stored in array
        product_name(Products[i], name);
        printf("\n\n\t\tPRODUCT: %s", name);
        printf("\n\t\tENTER PRODUCT QUANTITY: "); //Product Quantity is taken as input
        scanf("%d", &Quantity[i]);
        if(Quantity[i] > OldQuantity[i]) //Program checks if sufficient stocks are available for purchase
        {
            printf("\n\n\t\t\t\tINSUFFICIENT STOCKS AVAILABLE");
            printf("\n\n\t\t\t\tPLEASE ENTER QUANTITY EQUAL TO OR LESSER THAN %d", OldQuantity[i]);
        }
        else //Iterator is incremented only if sufficient stocks are available
        {
            i++;
        }
    }

    //Summary of Products Selected is displayed
    printf("\n\n\t\tPRODUCT ID\t\t\tQUANTITY\tPRICE");
    for(i = 0; i < n; i++)
    {
        printf("\n\t\t%s  \t\t\t\t%d\t\t%d", Products[i], Quantity[i], Prices[i]);
        cost = cost + (Quantity[i] * Prices[i]);
    }

    //Customer is asked for Coupon Code if they are Logged In
    if(flag == 1)
    {
        printf("\n\n\t\tENTER 1 IF YOU HAVE A COUPON: ");
        scanf("%d", &c);
        if(c == 1)
        {
            printf("\n\t\tENTER COUPON CODE: "); //Coupon Code is taken as input
            scanf("%s", coupon);
            if(RedeemCoupons(coupon)) //Coupon Code is verified
            {
                printf("\n\t\t10%% DISCOUNT APPLIED");
                cost = cost * 0.9; //Discount is applied if Coupon Code is valid
            }
        }
    }

    //Total Cost is Displayed
    printf("\n\n\t\tTOTAL COST: %d", cost);

    //Purchase Initation is confirmed
    printf("\n\n\t\tENTER 1 TO INITIATE PURCHASE: ");
    scanf("%d", &i);
    if(i != 1)
    {
        printf("\n\n\t\tINITIATION FAILED...");
        return;
    }

    //Employee Confirmation is taken after logging in
    printf("\n\n\t\tEMPLOYEE CONFIRMATION REQUIRED");
    printf("\n\n\t\tEMPLOYEE LOG IN");
    int t = 0;
    do
    {
        if(EmployeeLogin())
        {
            clear();
            t = 1;
            printf("\n\n\t\tEMPLOYEE ENTER 1 TO CONFIRM PURCHASE INITATION: ");
            scanf("%d", &c);
        }
        else
        {
            clear();
            printf("\n\n\t\tEMPLOYEE LOG IN FAILED");
            printf("\n\t\tPLEASE TRY AGAIN");
        }
    }while(t == 0);

    //Customer is prompted to complete payment if Employee confirmation is successful
    if(c == 1)
    {
        printf("\n\n\t\tCUSTOMER IS TO COMPLETE PAYMENT");
        //Payment Confirmation is done
        printf("\n\n\t\tENTER 1 TO CONFIRM PAYMENT HAS BEEN COMPLETED: ");
        scanf("%d", &c);

        //Final Purchase Summary is displayed
        if(c == 1)
        {
            printf("\n\n\t\tPRODUCT ID\t\t\tQUANTITY\tPRICE");
            for(i = 0; i < n; i++)
            {
                printf("\n\t\t%s  \t\t\t\t%d\t\t%d", Products[i], Quantity[i], Prices[i]);
            }
            printf("\n\n\t\tTOTAL COST: %d", cost);
            cash_balance = cash_balance + cost;
            balance();
            printf("\n\n\t\tPURCHASE COMPLETED");

            //All products purchased are checked to see if stocks are low
            for(i = 0; i < n; i++)
            {
                set_quantity(Products[i], OldQuantity[i] - Quantity[i]);
                x = get_quantity(Products[i]);
            }

            //Purchase Summary is stored in Purchase History file of Customer if logged in
            if(flag == 1)
            {
                strcpy(File, Account);
                strcat(File, "PH.txt");
                fp = fopen(File, "a");
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                fprintf(fp, "\n\n\t\t%s\n", asctime(timeinfo));
                fprintf(fp, "\n\t\tPRODUCT ID\t\t\tQUANTITY\tPRICE%s", a);
                for(i = 0; i < n; i++)
                {
                    fprintf(fp, "\n\t\t%s  \t\t\t\t%d\t\t\t%d", Products[i], Quantity[i], Prices[i]);
                }
                fclose(fp);
            }
        }
        else
        {
            printf("\n\n\t\tPURCHASE NOT COMPLETED");
        }    
    }
    else
    {
        printf("\n\n\t\tPURCHASE NOT COMPLETED");
    }
}

void PreviousPurchases(char Account[35]) //Enables Logged In Customer to View Previous Purchases made using that Customer Account
{
    FILE *fp;
    char File[40], c;
    strcpy(File, Account);
    strcat(File, "PH.txt");
    printf("\n\n\t\t\t\tPURCHASE HISTORY OF ACCOUNT: %s\n", Account);
    fp = fopen(File, "r"); //Purchase History of Customer is stored in File with PH as suffix to Customer Account name
    c = getc(fp);
    while(c != EOF)
    {
        putch(c);
        c = getc(fp);
    }
    fclose(fp);
}

int RedeemCoupons(char coupon[10]) //Called by BuyProducts() Function if Customer has a Coupon Code and verifies the code
{
    char Coupons[5][10] = {"XY101", "ES323", "TY003", "MH178", "PR149"}; //Valid Coupon Codes are stored in 2D String
    int i;
    for(i = 0; i < 5; i++)
    {
        if(strcmp(Coupons[i], coupon))
        {
            return 1; //Function returns 1 if Coupon Code is valid
        }
    }
    return 0; //Function returns 0 if Coupon Code is invalid
}

void ViewFeatures() //Enables User to View Features for a single product
{
    int c;
    do{
        printf("\n\t\t\t\tSELECT PRODUCT");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT MOBILE");
        printf("\n\t\t2 TO SELECT LAPTOP");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1: CompareMobiles(2);
                    return;
            case 2: CompareLaptops(2);
                    return;
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(1);
}

void CompareProducts() //Enables User to Compare Features for several products
{
    int c, n;
    do{
        printf("\n\t\t\t\tSELECT PRODUCT");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT MOBILE");
        printf("\n\t\t2 TO SELECT LAPTOP");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);

        //Number of products is read and passed to according mobiles/laptops function
        printf("\n\n\t\tENTER NUMBER OF PRODUCTS TO COMPARE: ");
        scanf("%d", &n);
        n = n + 1;
        switch(c)
        {
            case 1: CompareMobiles(n);
                    return;
            case 2: CompareLaptops(n);
                    return;
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(1);
}

void CompareMobiles(int n) //Enables User to Compare Features for several mobiles
{
    int i, j;
    char c, mob[10], file[15], s[100];
    FILE *Mobiles[n];
    Mobiles[0] = fopen("mobile.txt", "r");

    //File Pointer array is used to point towards features file of each mobile selected
    for(i = 1; i < n; i++)
    {
        printf("\n\n\t\t\t\tSELECT MOBILE %d\n", i);
        strcpy(mob, mobiles());
        strcat(mob, "F.txt");
        Mobiles[i] = fopen(mob, "r");
    }

    //Features for each mobile are displayed side by side by printing each file 1 line at a time
    printf("\n\t\t\t\tMOBILES FEATURES:\n\n");
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("\t");
            c = getc(Mobiles[j]);
            while(c != 10)
            {
                putch(c);
                c = getc(Mobiles[j]);
            }
        }
        printf("\n");
    }
    for(i = 0; i < n; i++)
    {
        fclose(Mobiles[i]);
    }
}

void CompareLaptops(int n) //Enables User to Compare Features for several laptops
{
    int i, j;
    char c, lap[10], file[15], s[100];
    FILE *Laptops[n];
    Laptops[0] = fopen("laptop.txt", "r");

    //File Pointer array is used to point towards features file of each mobile selected
    for(i = 1; i < n; i++)
    {
        printf("\n\n\t\t\t\tSELECT LAPTOP %d\n", i);
        strcpy(lap, laptops());
        strcat(lap, "F.txt");
        Laptops[i] = fopen(lap, "r");
    }

    //Features for each mobile are displayed side by side by printing each file 1 line at a time
    printf("\n\t\t\t\tLAPTOPS FEATURES:\n\n");
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("\t");
            c = getc(Laptops[j]);
            while(c != 10)
            {
                putch(c);
                c = getc(Laptops[j]);
            }
        }
        printf("\n");
    }
    for(i = 0; i < n; i++)
    {
        fclose(Laptops[i]);
    }
}

void set_quantity(char id[10], int quantity) //Changes Quantity of a product depending on New Purchase/Shipment
{
    FILE *Product;
    char file[10], s[5];
    strcpy(file, id);
    strcat(file, ".txt");
    Product = fopen(file, "w"); //Product file is opened
    itoa(quantity, s, 10);
    fprintf(Product, "%s", s);
    fclose(Product);
}

int get_quantity(char id[10]) //Returns Quantity of selected prodcut
{
    FILE *Product;
    int quantity;
    char file[10], s[5], name[100];
    strcpy(file, id);
    strcat(file, ".txt");
    Product = fopen(file, "r"); //Product file is opened
    fscanf(Product, "%s", s);
    quantity = atoi(s);
    fclose(Product);

    //Warning is displayed if stocks of product are low
    if(quantity < 10)
    {
        printf("\n\t\tPRODUCT STOCK IS LOW");
        product_name(id, name);
        printf("\n\t\tPRODUCT: %s", name);
        printf("\n\t\tQUANTITY: %d", quantity);
        printf("\n\t\tORDER SHIPMENTS AT EARLIEST\n");
    }
    return quantity;
}

void features(char id[10]) //Displays features of product selected when Customer is selecting products to purchase
{
    FILE *Product, *fp;
    char c, file[10];
    int i; 
    strcpy(file, id);
    strcat(file, "F.txt");
    Product = fopen(file, "r");

    //Product Features are printed
    printf("\n\n\t\t\t\tPRODUCT FEATURES:\n\n");
    if(id[0] == 'M')
    {
        fp = fopen("mobile.txt", "r");
        for(i = 0; i < 8; i++)
        {
            printf("\t");
            c = getc(fp);
            while(c != 10)
            {
                putch(c);
                c = getc(fp);
            }
            printf("\t");
            c = getc(Product);
            while(c != 10)
            {
                putch(c);
                c = getc(Product);
            }
            printf("\n");
        }
    }
    else
    {
        fp = fopen("laptop.txt", "r");
        for(i = 0; i < 8; i++)
        {
            printf("\t");
            c = getc(fp);
            while(c != 10)
            {
                putch(c);
                c = getc(fp);
            }
            printf("\t");
            c = getc(Product);
            while(c != 10)
            {
                putch(c);
                c = getc(Product);
            }
        }
        printf("\n");
    }
    fclose(fp); 
    fclose(Product);
}

void product_name(char id[10], char name[100]) //Assigns Product Name to name[] String
{
    FILE *Product;
    char c, file[10];
    int i = 0;
    strcpy(file, id);
    strcat(file, "N.txt");
    Product = fopen(file, "r");
    c = fgetc(Product);
    while(c != EOF) 
    {
        name[i] = c;
        i++; 
        c = fgetc(Product); 
    }
    name[i] = '\0';
    fclose(Product);
}

int product_price(char id[10]) //Returns Product Price
{
    FILE *Product;
    char s[10], file[10];
    int price;
    strcpy(file, id);
    strcat(file, "P.txt");
    Product = fopen(file, "r");
    fscanf(Product, "%s", s);
    price = atoi(s);
    fclose(Product);
    return price;
}

char* set_product()
//Used across the program to enable User to select product
//set_product() function branches into mobile() and laptop() functions which display Menus to select Mobile/Laptop brand
//mobile() and laptop() functions branch into several functions corresponding to each brand
//Each brand function finally enables User to select product and then returns its ID as a string
{
    int c;
    do{
        printf("\n\t\t\t\tSELECT PRODUCT");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT MOBILE");
        printf("\n\t\t2 TO SELECT LAPTOP");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1: return mobiles();
            case 2: return laptops();
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(1);
}

char* mobiles()
{
    int c;
    do{
        printf("\n\t\t\t\tSELECT MOBILE BRAND");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT ONEPLUS");
        printf("\n\t\t2 TO SELECT XIAOMI");
        printf("\n\t\t3 TO SELECT SAMSUNG");
        printf("\n\t\t4 TO SELECT APPLE");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1: return oneplus_mobiles();
            case 2: return xiaomi_mobiles();
            case 3: return samsung_mobiles();
            case 4: return apple_mobiles();
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(1);
}

char* oneplus_mobiles()
{
    int c;
    do{
        printf("\n\t\t\t\tSELECT ONEPLUS MOBILE");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT ONEPLUS NORD 5G");
        printf("\n\t\t2 TO SELECT ONEPLUS 8");
        printf("\n\t\t3 TO SELECT ONEPLUS 8T");
        printf("\n\t\t4 TO SELECT ONEPLUS 8 PRO");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1: return "M001";
            case 2: return "M002";
            case 3: return "M003";
            case 4: return "M004";
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(1);    
}

char* xiaomi_mobiles()
{
    int c;
    do{
        printf("\n\t\t\t\tSELECT XIAMO MOBILE");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT REDMI 9");
        printf("\n\t\t2 TO SELECT REDMI 9A");
        printf("\n\t\t3 TO SELECT REDMI 9 POWER");
        printf("\n\t\t4 TO SELECT REDMI 9 PRIME");
        printf("\n\t\t5 TO SELECT REDMI NOTE 9");
        printf("\n\t\t6 TO SELECT REDMI NOTE 9 PRO");
        printf("\n\t\t7 TO SELECT REDMI NOTE 9 PRO MAX");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1: return "M101";
            case 2: return "M102";
            case 3: return "M103";
            case 4: return "M104";
            case 5: return "M105";
            case 6: return "M106";
            case 7: return "M107";
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(1);    
}
char* samsung_mobiles()
{
    int c;
    do{
        printf("\n\t\t\t\tSELECT SAMSUNG MOBILE");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT SAMSUNG S10");
        printf("\n\t\t2 TO SELECT SAMSUNG S10 PLUS");
        printf("\n\t\t3 TO SELECT SAMSUNG S20");
        printf("\n\t\t4 TO SELECT SAMSUNG S20+");
        printf("\n\t\t5 TO SELECT SAMSUNG NOTE 10");
        printf("\n\t\t6 TO SELECT SAMSUNG NOTE 20");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1: return "M201";
            case 2: return "M202";
            case 3: return "M203";
            case 4: return "M204";
            case 5: return "M205";
            case 6: return "M206";
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(1);
}
char* apple_mobiles()
{
    int c;
    do{
        printf("\n\t\t\t\tSELECT APPLE MOBILE");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT iPHONE 12");
        printf("\n\t\t2 TO SELECT iPHONE 12 PRO");
        printf("\n\t\t3 TO SELECT iPHONE 12 PRO MAX");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1: return "M301";
            case 2: return "M302";
            case 3: return "M303";
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(1);
}

char* laptops()
{
    int c;
    do{
        printf("\n\t\t\t\tSELECT LAPTOP BRAND");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT HP");
        printf("\n\t\t2 TO SELECT DELL");
        printf("\n\t\t3 TO SELECT ASUS");
        printf("\n\t\t4 TO SELECT LENOVO");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1: return hp_laptops();
            case 2: return dell_laptops();
            case 3: return asus_laptops();
            case 4: return lenovo_laptops();
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(1);
}

char* hp_laptops()
{
    int c;
    do{
        printf("\n\t\t\t\tSELECT HP LAPTOP");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT HP 15");
        printf("\n\t\t2 TO SELECT HP 15S");
        printf("\n\t\t3 TO SELECT HP PAVILION x360");
        printf("\n\t\t4 TO SELECT HP PAVILION GAMING");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1: return "L001";
            case 2: return "L002";
            case 3: return "L003";
            case 4: return "L004";
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(1);
}

char* dell_laptops()
{
    int c;
    do{
        printf("\n\t\t\t\tSELECT DELL LAPTOP");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT DELL INSPIRON 3505");
        printf("\n\t\t2 TO SELECT DELL INSPIRON 3583");
        printf("\n\t\t3 TO SELECT DELL INSPIRON 3593");
        printf("\n\t\t4 TO SELECT DELL INSPIRON 3595");
        printf("\n\t\t5 TO SELECT DELL INSPIRON 5408");
        printf("\n\t\t6 TO SELECT DELL G3 3500");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1: return "L101";
            case 2: return "L102";
            case 3: return "L103";
            case 4: return "L104";
            case 5: return "L105";
            case 6: return "L106";
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(1);
}
char* asus_laptops()
{
    int c;
    do{
        printf("\n\t\t\t\tSELECT ASUS LAPTOP");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT ASUS ZENBOOK 13");
        printf("\n\t\t2 TO SELECT ASUS ZENBOOK 14");
        printf("\n\t\t3 TO SELECT ASUS VIVOBOOK 15");
        printf("\n\t\t4 TO SELECT ASUS TUF GAMING");
        printf("\n\t\t5 TO SELECT ASUS ROG GAMING");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1: return "L201";
            case 2: return "L202";
            case 3: return "L203";
            case 4: return "L204";
            case 5: return "L205";
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(1);
}
char* lenovo_laptops()
{
    int c;
    do{
        printf("\n\t\t\t\tSELECT LENOVO LAPTOP");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT LENOVO IDEAPAD SLIM 3");
        printf("\n\t\t2 TO SELECT LENOVO IDEAPAD S145");
        printf("\n\t\t3 TO SELECT LENOVO IDEAPAD S340");
        printf("\n\t\t4 TO SELECT LENOVO LEGION 5i");
        printf("\n\t\t5 TO SELECT LENOVO LEGION Y540");
        printf("\n\t\t6 TO SELECT LENOVO THINKPAD E14");
        printf("\n\t\t7 TO SELECT LENOVO THINKPAD E15");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
        switch(c)
        {
            case 1: return "L301";
            case 2: return "L302";
            case 3: return "L303";
            case 4: return "L304";
            case 5: return "L305";
            case 6: return "L306";
            case 7: return "L307";
            default:printf("\n\t\tINVALID INPUT...\n");
        }
    }while(1);
}

void clear()
{
    printf("\n\n\t\tPRESS ANY KEY TO CONTINUE");
    getch();
    system("cls");
}