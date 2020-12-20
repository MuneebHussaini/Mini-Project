#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>

int cash_balance = 0;

void clear();

void balance();

void Employee();
int EmployeeLogin();
void CheckStocks();
void OrderShipments();
void ViewShipments();

void ViewFeatures();
void CompareProducts();
void CompareMobiles(int n);
void CompareLaptops(int n);

void Customer();
void CustomerRegistry();
void CustomerLogin();
void LoggedInCustomer(char Account[]);
void RegularCustomer();
void BuyProducts(int flag, char Account[]);
void PreviousPurchases(char Account[35]);
int RedeemCoupons(char coupon[]);

void set_quantity(char id[], int quantity);
int get_quantity(char id[]);

void features(char id[]);
void product_name(char id[], char name[]);
int product_price(char id[]);

char* set_product();

char* mobiles();
char* oneplus_mobiles();
char* xiaomi_mobiles();
char* samsung_mobiles();
char* apple_mobiles();

char* laptops();
char* hp_laptops();
char* dell_laptops();
char* asus_laptops();
char* lenovo_laptops();

int main()
{
    int c;
    char s[100];
    FILE *Balance;
    Balance = fopen("balance.txt", "r");
    fscanf(Balance, "%s", s);
    cash_balance = atoi(s);
    fclose(Balance);
    do
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

void balance()
{
    FILE *Balance;
    printf("\n\t\tCURRENT CASH BALANCE: %d", cash_balance);
    Balance = fopen("balance.txt", "w");
    fprintf(Balance, "%d", cash_balance);
    fclose(Balance);
    clear();
}

void Employee()
{
    int c;
    c = EmployeeLogin();
    system("cls");
    if(c == 0)
    {
        printf("\n\n\t\tLOG IN FAILED DUE TO INCORRECT ID OR PASSWORD\n");
        return;
    }
    printf("\n\t\tLOGGED IN AS EMPLOYEE\n");
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

int EmployeeLogin()
{
    char EmployeeIDs[10][10] = {"101", "102", "103", "104", "105", "106", "107", "108"};
    char Account[10], File[10], Password[31], CorrectPassword[31], *s = ".txt", c;
    int i;
    FILE *EmployeeAccount;
    printf("\n\t\tENTER EMPLOYEE ID: ");
    scanf("%s", Account);
    strcpy(File, Account);
    strcat(File, s);
    EmployeeAccount = fopen(File, "r");
    for(i = 0; i < 8; i++)
    {
        if(strcmp(EmployeeIDs[i], Account) == 0)
        {
            printf("\n\t\tENTER PASSWORD: ");
            scanf("%s", Password);
            fscanf(EmployeeAccount, "%s", CorrectPassword);
            fclose(EmployeeAccount);
            if(strcmp(CorrectPassword, Password) == 0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    return 0;
}

void CheckStocks()
{
    char id[10], name[100];
    printf("\n\n\t\t\t\t\tCHECK STOCKS");
    strcpy(id, set_product());
    product_name(id, name);
    printf("\n\t\tPRODUCT: %s", name);
    printf("\n\t\tQUANTITY: %d", get_quantity(id));
}

void OrderShipments()
{
    time_t rawtime;
    struct tm *timeinfo;
    char *s, *a = "";
    int i, n, cost = 0;
    FILE *fp;
    printf("\n\n\t\t\t\t\tORDER SHIPMENTS");
    printf("\n\n\t\tENTER NUMBER OF DIFFERENT PRODUCTS: ");
    scanf("%d", &n);
    char Products[n][10];
    int NewQuantity[n];
    int OldQuantity[n];
    int Prices[n];
    for(i = 0; i < n; i++)
    {
        printf("\n\n\t\tSELECT PRODUCT %d\n", i + 1);
        strcpy(Products[i], set_product());
        OldQuantity[i] = get_quantity(Products[i]);
        Prices[i] = product_price(Products[i]) * 0.8;
        printf("\n\n\t\tENTER PRODUCT QUANTITY: ");
        scanf("%d", &NewQuantity[i]);
    }
    printf("\n\n\t\tPRODUCT ID\t\t\tQUANTITY\tPRICE");
    for(i = 0; i < n; i++)
    {
        printf("\n\t\t%s  \t\t\t\t%d\t\t%d", Products[i], NewQuantity[i], Prices[i]);
        cost = cost + (NewQuantity[i] * Prices[i]);
    }

    printf("\n\n\t\tTOTAL COST: %d", cost);
    if(cost > cash_balance)
    {
        printf("\n\n\t\tINSUFFICIENT BALANCE AVAILABLE");
        return;
    }
    printf("\n\n\t\tENTER 1 TO CONFIRM SHIPMENT: ");
    scanf("%d", &i);
    if(i != 1)
    {
        printf("\n\n\t\tCONFIRMATION FAILED...");
        return;
    }
    cash_balance = cash_balance - cost;
    balance();
    printf("\n\n\t\tSHIPMENT CONFIRMED");
    fp = fopen("PreviousShipments.txt", "a");
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fprintf(fp, "\n\n\t\t%s\n", asctime(timeinfo));
    fprintf(fp, "\n\t\tPRODUCT ID\t\t\tQUANTITY\tPRICE%s", a);
    for(i = 0; i < n; i++)
    {
        set_quantity(Products[i], OldQuantity[i] + NewQuantity[i]);
        fprintf(fp, "\n\t\t\%s  \t\t\t\t%d\t\t\t%d", Products[i], NewQuantity[i], Prices[i]);
    }
    fclose(fp);
}

void ViewShipments()
{
    FILE *fp;
    char c;
    printf("\n\n\t\t\t\t\tSHIPMENT HISTORY");
    fp = fopen("PreviousShipments.txt", "r");
    c = getc(fp);
    while(c != EOF)
    {
        putch(c);
        c = getc(fp);
    }
    fclose(fp);
}

void Customer()
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

void CustomerRegistry()
{
    char Account[35], Purchases[37], Password[35], Password1[35], Password2[35], *s = ".txt";
    FILE *CustomerAccount;
    printf("\n\t\tENTER ACCOUNT NAME (Max 30 Characters): ");
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
    printf("\n\t\tENTER PASSWORD (Max 30 Characters): ");
    scanf("%s", Password1);
    printf("\n\t\tCONFIRM PASSWORD: ");
    scanf("%s", Password2);
    if(strcmp(Password1, Password2) == 0)
    {
        strcpy(Password, Password1);
        CustomerAccount = fopen(Account, "w");
        fprintf(CustomerAccount, "%s", Password);
        printf("\n\t\tNEW CUSTOMER ACCOUNT SUCCESSFULLY CREATED\n");
        fclose(CustomerAccount);
        CustomerAccount = fopen(Purchases, "w");
        fclose(CustomerAccount);
    }
    else
    {
        printf("\n\t\tPASSWORD CONFIRMATION FAILED\n");
    }   
}

void CustomerLogin()
{
    char Account[35], File[40], Password[35], CorrectPassword[35], c;
    int i;
    FILE *CustomerAccount;
    printf("\n\t\tENTER CUSTOMER ACCOUNT NAME: ");
    scanf("%s", Account);
    strcpy(File, Account);
    strcat(File, ".txt");
    CustomerAccount = fopen(File, "r");
    if(CustomerAccount == NULL)
    {
        printf("\n\t\tACCOUNT NAME DOES NOT EXIST\n");
        return;
    }
    printf("\n\t\tENTER PASSWORD: ");
    scanf("%s", Password);
    fscanf(CustomerAccount, "%s", CorrectPassword);
    fclose(CustomerAccount);
    if(strcmp(CorrectPassword, Password) == 0)
    {
        printf("\n\t\tLOGGED IN AS REGISTERED CUSTOMER\n");
        clear();
        LoggedInCustomer(Account);
        return;
    }
    printf("\n\t\tINCCORECT PASSWORD");
    return;
}

void LoggedInCustomer(char Account[35])
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

void RegularCustomer()
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

void BuyProducts(int flag, char Account[35])
{
    time_t rawtime;
    struct tm *timeinfo;
    char *s, *a = "", name[100], File[40], coupon[10];
    int i, x, cost = 0, c = 1, n = 0;
    FILE *fp;
    printf("\n\n\t\t\t\t\tBUY PRODUCTS");
    char Products[10][10];
    int Quantity[10];
    int OldQuantity[10];
    int Prices[10];
    do
    {
        printf("\n\n\t\tSELECT PRODUCT %d\n", n + 1);
        strcpy(Products[n], set_product());
        product_name(Products[n], name);
        printf("\n\n\t\tPRODUCT: %s", name);
        printf("\n\t\tFEATURES:\n");
        features(Products[n]);
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
        OldQuantity[i] = get_quantity(Products[i]);
        Prices[i] = product_price(Products[i]);
        product_name(Products[i], name);
        printf("\n\n\t\tPRODUCT: %s", name);
        printf("\n\t\tENTER PRODUCT QUANTITY: ");
        scanf("%d", &Quantity[i]);
        if(Quantity[i] > OldQuantity[i])
        {
            printf("\n\n\t\t\t\tINSUFFICIENT STOCKS AVAILABLE");
            printf("\n\n\t\t\t\tPLEASE ENTER QUANTITY EQUAL TO OR LESSER THAN %d", OldQuantity[i]);
        }
        else
        {
            i++;
        }
    }
    printf("\n\n\t\tPRODUCT ID\t\t\tQUANTITY\tPRICE");
    for(i = 0; i < n; i++)
    {
        printf("\n\t\t%s  \t\t\t\t%d\t\t%d", Products[i], Quantity[i], Prices[i]);
        cost = cost + (Quantity[i] * Prices[i]);
    }
    if(flag == 1)
    {
        printf("\n\n\t\tENTER 1 IF YOU HAVE A COUPON: ");
        scanf("%d", &c);
        if(c == 1)
        {
            printf("\n\t\tENTER COUPON CODE: ");
            scanf("%s", coupon);
            if(RedeemCoupons(coupon))
            {
                printf("\n\t\t10%% DISCOUNT APPLIED");
                cost = cost * 0.9;
            }
        }
    }
    printf("\n\n\t\tTOTAL COST: %d", cost);
    printf("\n\n\t\tENTER 1 TO INITIATE PURCHASE: ");
    scanf("%d", &i);
    if(i != 1)
    {
        printf("\n\n\t\tINITIATION FAILED...");
        return;
    }
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
    if(c == 1)
    {
        printf("\n\n\t\tCUSTOMER IS TO COMPLETE PAYMENT");
        printf("\n\n\t\tENTER 1 TO CONFIRM PAYMENT HAS BEEN COMPLETED: ");
        scanf("%d", &c);
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
            for(i = 0; i < n; i++)
            {
                set_quantity(Products[i], OldQuantity[i] - Quantity[i]);
                x = get_quantity(Products[i]);
            }
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

void PreviousPurchases(char Account[35])
{
    FILE *fp;
    char File[40], c;
    strcpy(File, Account);
    strcat(File, "PH.txt");
    printf("\n\n\t\t\t\tPURCHASE HISTORY OF ACCOUNT: %s\n", Account);
    fp = fopen(File, "r");
    c = getc(fp);
    while(c != EOF)
    {
        putch(c);
        c = getc(fp);
    }
    fclose(fp);
}

int RedeemCoupons(char coupon[10])
{
    char Coupons[5][10] = {"XY101", "ES323", "TY003", "MH178", "PR149"};
    int i;
    for(i = 0; i < 5; i++)
    {
        if(strcmp(Coupons[i], coupon))
        {
            return 1;
        }
    }
    return 0;
}

void ViewFeatures()
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

void CompareProducts()
{
    int c, n;
    do{
        printf("\n\t\t\t\tSELECT PRODUCT");
        printf("\n\n\t\tPRESS:");
        printf("\n\t\t1 TO SELECT MOBILE");
        printf("\n\t\t2 TO SELECT LAPTOP");
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &c);
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

void CompareMobiles(int n)
{
    int i, j;
    char c, mob[10], file[15], s[100];
    FILE *Mobiles[n];
    Mobiles[0] = fopen("mobile.txt", "r");
    for(i = 1; i < n; i++)
    {
        printf("\n\n\t\t\t\tSELECT MOBILE %d\n", i);
        strcpy(mob, mobiles());
        strcat(mob, "F.txt");
        Mobiles[i] = fopen(mob, "r");
    }
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

void CompareLaptops(int n)
{
    int i, j;
    char c, lap[10], file[15], s[100];
    FILE *Laptops[n];
    Laptops[0] = fopen("laptop.txt", "r");
    for(i = 1; i < n; i++)
    {
        printf("\n\n\t\t\t\tSELECT LAPTOP %d\n", i);
        strcpy(lap, laptops());
        strcat(lap, "F.txt");
        Laptops[i] = fopen(lap, "r");
    }
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

void set_quantity(char id[10], int quantity)
{
    FILE *Product;
    char file[10], s[5];
    strcpy(file, id);
    strcat(file, ".txt");
    Product = fopen(file, "w");
    itoa(quantity, s, 10);
    fprintf(Product, "%s", s);
    fclose(Product);
}

int get_quantity(char id[10])
{
    FILE *Product;
    int quantity;
    char file[10], s[5], name[100];
    strcpy(file, id);
    strcat(file, ".txt");
    Product = fopen(file, "r");
    fscanf(Product, "%s", s);
    quantity = atoi(s);
    fclose(Product);
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

void features(char id[10])
{
    FILE *Product, *fp;
    char c, file[10];
    int i; 
    strcpy(file, id);
    strcat(file, "F.txt");
    Product = fopen(file, "r");
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

void product_name(char id[10], char name[100])
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

int product_price(char id[10])
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