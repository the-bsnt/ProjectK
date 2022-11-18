// BANK MANAGEMENT SYSTEM
// project that manages the basic activity of the bank
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
struct acc_details
{
    char accountfname[30];
    char accountlname[30];
    char bankbranch[30];
    char address[30];
    char accounttype[30];
    int accountnumber;
    double balance;
};
void newaccount();
void update_balance(int x);

void account_search(int acn);
void account_details(struct acc_details c);
void show_options();
int getacc();
struct acc_details a, b, c;
FILE *fptr;
int main()
{
    fptr = fopen("bsnt_bank.txt", "r+b");
    if (fptr == NULL)
    {
        fptr = fopen("bsnt_bank.txt", "w+b");
        if (fptr == NULL)
        {
            printf("Sorry! something went wrong in the system.\n");
        }
    }
    printf("********************************WELCOME TO BSNT BANK Private Ltd.********************************\n");
    while (1)
    {
        printf("\n\nWelcome you to bank management system.Here are some options.Choose one of them and follow \nthe guidelines.\n");
        show_options();
        int x;
        scanf("%d", &x);
        fflush(stdin);
        switch (x)
        {
        case 1:
            newaccount();
            break;
        case 2:
            update_balance(x);
            break;
        case 3:
            update_balance(x);
            break;
        case 4:
            // account details;
            printf("Enter the account number of account holder:\n");
            int acn;
            scanf("%d", &acn);
            account_search(acn);
            break;
        case 5:
            // to log out;
            exit(0);
            break;

        default:
            printf("Invalid Option!!! try again;\n");
            break;
        }
        // break;
    }
    fclose(fptr);
    return 0;
}
void show_options()
{
    printf("===================================================================================================\n");
    printf("\nChoose the following options:\n");
    printf("\tpress 1; to create a new account.\n");
    printf("\tpress 2; to diposite the cash.\n");
    printf("\tpress 3; to withdraw the cash.\n");
    printf("\tpress 4; to get Bank Account Details.\n");
    printf("\tpress 5; to exit from the system.\n");
    printf("\tpress 6; to report a problem.\n");
}
int getacc()
{
    int acc;
    struct acc_details x;
    fseek(fptr, 0, SEEK_SET);
    while (fread(&x, sizeof(x), 1, fptr) == 1)
    {
        acc = x.accountnumber;
    }
    if (x.accountnumber == 0)
    {
        return 7771;
    }
    acc = x.accountnumber + 1;
    return acc;
}
void newaccount()
{
    printf("===================================================================================================\n");
    printf("                                        BSNT BANK Pvt Ltd.                                        \n");
    char branch[30], fname[30], lname[30], address[30], acctype[30];
    int actype;
    printf("Enter details of Account Holder;\n\n");
    printf("Enter the last name: \n");
    scanf("%s", lname);
    printf("Enter the first name: \n");
    fflush(stdin);
    scanf("%s", fname);
    printf("Enter the Address of Account Holder;\n");
    fflush(stdin);
    scanf("%s", address);
    printf("Enter the branch of bank\n");
    fflush(stdin);
    scanf("%s", branch);
    printf("Which type of account you want to open:\n1.saving\n2.fixed diposite\n3.current account\n...");
    scanf("%d", &actype);
    if (actype == 3)
    {
        strcpy(a.accounttype, "Current");
    }
    else if (actype == 2)
    {
        strcpy(a.accounttype, "Fixed Diposite");
    }
    else
    {
        strcpy(a.accounttype, "Saving");
    }
    int x = getacc();
    a.accountnumber = x;
    a.balance = 0.00;
    strcpy(a.accountfname, fname);
    strcpy(a.accountlname, lname);
    strcpy(a.address, address);
    strcpy(a.bankbranch, branch);
    fseek(fptr, 0, SEEK_END);
    fwrite(&a, sizeof(a), 1, fptr);
    printf("Getting your account ready .............\nYour account has been successfully created.\n");
    account_details(a);
    fseek(fptr, 0, SEEK_END);
    printf("\t\t\t\t\tenter any key to continue....\n");
    getch();
}
void account_search(int acn)
{
    fseek(fptr, 0, SEEK_SET); // or use rewind
    int isfound = 0;
    while (fread(&b, sizeof(b), 1, fptr) == 1)
    {
        if (acn == b.accountnumber)
        {
            account_details(b);
            isfound++;
            break;
        }
    }
    if (isfound == 0)
    {
        printf("Sorry! Your account is not registered.\n");
    }
    printf("\t\t\t\t\tenter any key to continue....\n");
    getch();
}
void account_details(struct acc_details c)
{
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Your Account details:\n");
    printf("          BSNT Bank pvt ltd.\nBranch:                     %s\n", c.bankbranch);
    printf("Account Name:               %s %s\n", c.accountlname, c.accountfname);
    printf("Account Number:             %d\n", c.accountnumber);
    printf("Account Type:               %s\n", c.accounttype);
    printf("Address of Account Holder:  %s\n", c.address);
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t   The current balance in your account is Rs.%.2f.\n", c.balance);
    printf("----------------------------------------------------------------------------------------------------\n");
}
void update_balance(int x)
{
    double cash;
    int acn, i = 0;
    if (x == 2)
    {
        printf("Enter the Account Number in which you want to deposite amount. \n");
    }
    if (x == 3)
    {
        printf("Enter the Account Number from which you want to withdraw Cash.\n");
    }
    scanf("%d", &acn);
    fseek(fptr, 0, SEEK_SET); // or use rewind
    int isfound = 0;
    while (fread(&b, sizeof(b), 1, fptr) == 1)
    {
        i++;
        if (acn == b.accountnumber)
        {
            account_details(b);
            if (x == 2)
            {
                printf("Enter the Amount you want to deposite.\n");
                scanf("%lf", &cash);
                printf("Please deposit your cash to cash counter.\tThank You.\n\n");
                b.balance = b.balance + cash;
            }
            if (x == 3)
            {
                printf("Enter the Amount you want to withdraw.\n");
                scanf("%lf", &cash);
                if (b.balance < cash)
                {
                    printf("Your do not have enough balance in your account.\n              !!!INSUFFICIENT BALANCE!!!              \n");
                    printf("Your transaction has been declined.\n");
                    printf("----------------------------------------------------------------------------------------------------\n");
                    goto leave;
                }
                printf("Please collect your cash from cash counter.\tThank You.\n\n");

                b.balance = b.balance - cash;
            }
            fseek(fptr, (i - 1) * sizeof(b), SEEK_SET);
            fwrite(&b, sizeof(b), 1, fptr);
            printf("----------------------------------------------------------------------------------------------------\n");
            printf("\nYour new balance in your account is Rs.%.2f.\n", b.balance);
            printf("----------------------------------------------------------------------------------------------------\n");
            isfound++;
            break;
        }
    }
    if (isfound == 0)
    {
        printf("Sorry! Your account is not registered.\n");
    }
leave:
    printf("\t\t\t\t\tenter any key to continue....\n");
    getch();
}