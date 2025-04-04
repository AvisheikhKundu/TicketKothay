#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

typedef struct BinarySearchTree BST;

struct BinarySearchTree
{
    int PassnNo;
    char name[20];
    struct BinarySearchTree *left;
    struct BinarySearchTree *right;
};

BST *root = NULL;

int cost(BST *r);
void status();
void busLists();
void DisplaySeat(int bus[33]);
void cancel(int x);
BST *reservationInfo(BST *, int, int *);
BST *insert(BST **r, int custID);

int busSeat[32][9] = {0};

void greenColor()
{
    printf("\033[1;32m");
}

void resetColor()
{
    printf("\033[0m");
}

BST *reservationInfo(BST *r, int s, int *custIDmatched)
{
    if (r == NULL)
        return NULL;
    BST *presentnode = r;
    while (presentnode)
    {
        if (presentnode->PassnNo == s)
        {
            *custIDmatched = 1;
            greenColor();
            printf("\n-----------------------------------------------------------------");
            printf("\n||              NAME: %10s                               ||", (presentnode->name));
            printf("\n||              CUSTOMER ID: %d                              ||", presentnode->PassnNo);
            printf("\n||              BUS NUMBER: %d                                  ||", (presentnode->PassnNo) / 1000);
            printf("\n||              SEAT NUMBER: %d                                 ||", (presentnode->PassnNo) % 100);
            printf("\n||              TICKET COST: Tk.%d                           ||", cost(presentnode));
            printf("\n-----------------------------------------------------------------");
            resetColor();
            getch();
            return r;
        }
        presentnode = presentnode->left;
    }
    return NULL;
}

BST *insert(BST **r, int custId)
{
    if (*r == NULL)
    {
        *r = (BST *)malloc(sizeof(BST));
        (*r)->PassnNo = custId;
        if (*r == NULL)
        {
            printf("No memory…");
            return NULL;
        }
        else
        {
            (*r)->left = (*r)->right = NULL;
            printf("\n   ENTER THE PERSON NAME: ");
            scanf("%s", &((*r)->name));
        }
    }
    else
    {
        if ((*r)->PassnNo > custId)
        {
            (*r)->left = insert(&((*r)->left), custId);
        }
        else if ((*r)->PassnNo < custId)
        {
            (*r)->right = insert(&((*r)->right), custId);
        }
    }
    return *r;
}

void DisplaySeat(int bus[33])
{
    for (int i = 1; i <= 32; i++)
    {
        greenColor();
        if (i < 10 && i > 0)
        {
            printf("0%d .", i);
        }
        else
        {
            printf("%d .", i);
        }

        resetColor();
        {
            if (bus[i] == 0)
                printf("EMPTY ");
            else
                printf("BOOKED");
        }
        printf("         ");
        if (i % 4 == 0)
            printf("\n");
    }
}

void login()
{
    char userName[20] = "user";
    char passWord[20] = "Avisheikh001";
    char matchPass[20];
    char matchUser [20];
    int value;

    greenColor();
    printf("\n\n=========================================================================================\n");
    printf("\n\t\t\t\tWELCOME TO TicketKothay Application\n\n\t\t\t\t     \'Have a safe Journey\'");
    printf("\n\n=========================================================================================\n\n");
    resetColor();

login:
    {
        printf("\n\nUser  Name: ");
        gets(matchUser );

        printf("\nPassWord: ");
        gets(matchPass);
    }

    value = strcmp(passWord, matchPass);
    if (value != 0)
    {
        greenColor();
        printf("\nINVALID DETAILS TRY AGAIN...\n");
        resetColor();
        goto login;
    }
    else
    {
        printf("\nLOGGED IN SUCCESSFULLY...\n");
    }
}

int cost(BST *r)
{
    int cost, buscost;
    buscost = (r->PassnNo) / 1000;
    switch (buscost % 3)
    {
    case 1:
        return 2000;
        break;
    case 2:
        return 1000;
        break;
    case 0:
        return 1500;
        break;
    default:
        return 0;
        break;
    }
}

void status()
{
    int busNum;
    busLists();
busInput:
    printf("\n\nENTER YOUR BUS NUMBER : ");
    scanf("%d", &busNum);
    if (busNum <= 0 || busNum >= 10)
    {
        greenColor();
        printf("\n  PLEASE ENTER CORRECT BUS NUMBER !!\n");
        resetColor();
        goto busInput;
    }
    printf("\n");
    DisplaySeat(busSeat[busNum]);
    getch();
}

void busLists()
{
    greenColor();
    printf("-------------------------------------------------------------------------------------------------");
    printf("\nBus.No\tName\t\t\t\tDestinations  \t\tCharges  \t\tTime\n");
    printf("-------------------------------------------------------------------------------------------------");
    printf("\n1\tSaintmartin Paribahan     \tDhaka to Cox's Bazar  \tTK.2000     \t\t10:00  PM");
    printf("\n2\tAK_Travels                \tDhaka To Sylhet       \tTk.1000     \t\t01:30  PM");
    printf("\n3\tEna Paribahan             \tDhaka To Kuakata      \tTk.1500     \t\t03:50  PM");
    printf("\n4\tSuper Deluxe              \tDhaka To Dinajpur     \tTk.2000     \t\t07:00  AM");
    printf("\n5\tSkyLine                   \tDhaka To Khulna       \tTk.1000     \t\t12:05  AM");
    printf("\n6\tRoyal Express             \tDhaka to Chuadanga    \tTk.1500     \t\t09:30  AM");
    printf("\n7\tShohag Paribahan          \tDhaka To Benapole     \tTk.2000     \t\t11:00  PM");
    printf("\n8\tHanif Paribahan           \tDhaka To Bogura       \tTk.1000     \t\t08:15  AM");
    printf("\n9\tSoudia Paribahan          \tDhaka To Chattogram   \tTk.1000     \t\t07:00  PM");
    printf("\n");
    printf("\n   PRESS 'ENTER' KEY TO CONTINUE ");
    getch();
}

void cancel(int randomNum)
{
    int reservationNo;
    int seatNumber;
    int choice;
    char c;
    int seatCancel;

aa:
    {
        printf("\nENTER YOUR RESERVATION NUMBER : ");
        scanf("%d", &reservationNo);
        if (reservationNo == randomNum)
        {
            printf("\nRESERVATION NUMBER IS IT CORRECT ? %d \nENTER (Y/N) : ", reservationNo);
            scanf(" %c", &c);
            if (c == 'y' || c == 'Y')
            {
                printf("\n\n============================================\n\n");
                printf("   ENTER THE BUS NUMBER: ");
                scanf("%d", &choice);

                printf("\n HOW MANY SEATS DO WANT TO CANCEL : ");
                scanf("%d", &seatCancel);
                for (int i = 0; i < seatCancel; i++)
                {
                    printf("   \nENTER THE SEAT NUMBER: ");
                    scanf("%d", &seatNumber);

                    busSeat[choice][seatNumber] = 0;
                }
                printf("\n\nYOUR RESERVATION HAS BEEN CANCELLED !!\n\n");
                printf("\n  PRESS 'ENTER' KEY TO CONTINUE \n");
                getch();
                DisplaySeat(busSeat[choice]);
            }
            else if (c == 'n' || c == 'N')
            {
                printf("\nYOUR RESERVATION CANCELLATION HAS BEEN DENIED\n");
            }
        }
        else
        {
            printf("\nNOT FOUND!! ENTER THE CORRECT RESERVATION NUMBER\n");
            goto aa;
        }
    }
}

int main()
{
    srand(time(0));
    int randomNum = rand();
    int num, i, custID, reservationNo;
    BST *root1;
    login();
main:
    do
    {
        printf("\n\n====================================================================\n\n");
        printf("\t\t\t\033[1;32mBUS RESERVATION\033[0m\t\t");
        printf("\n\n=====================================================================\n");
        printf("\n====================");
        greenColor();
        printf("  MAIN MENU ");
        resetColor();
        printf("=====================\n\n");
        printf("   \033[1;32m[1]\033[0m VIEW BUS LIST \n\n");
        printf("   \033[1;32m[2]\033[0m BOOK TICKETS\n\n");
        printf("   \033[1;32m[3]\033[0m CANCEL BOOKING\n\n");
        printf("   \033[1;32m[4]\033[0m BUSES SEATS INFO\n\n");
        printf("   \033[1;32m[5]\033[0m RESERVATION INFO\n\n");
        printf("   \033[1;32m[6]\033[0m EXIT\n");
        printf("\n=====================================================\n");
        printf("\n   ENTER YOUR CHOICE: ");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            busLists();
            break;
        case 2:
            busLists();
            int CustId, choice, seats;
        busChoice:
            printf("\n\nCHOOSE YOUR BUS  : ");
            scanf("%d", &choice);
            if (choice <= 0 || choice > 9)
            {
                greenColor();
                printf("\nENTER VALID BUS NUMBER !! \n");
                resetColor();
                getch();
                goto busChoice;
            }
            printf("\n");
            DisplaySeat(busSeat[choice]);
        busSeatChoice:
            printf("\n\nNO. OF SEATS YOU NEED TO BOOK : ");
            scanf("%d", &seats);
            if (seats <= 0)
            {
                greenColor();
                printf("\nENTER VALID SEAT NUMBER!!\n");
                resetColor();
                goto busSeatChoice;
            }
            else if (seats > 32)
            {
                greenColor();
                printf("\nENTER VALID SEAT NUMBER WE HAVE ONLY 32 SEATS IN A BUS !!\n");
                resetColor();
                goto busSeatChoice;
            }

            int totalCost = 0;
            int seatNumber;
            for (int i = 1; i <= seats; i++)
            {
                printf("\n\n==================================================================================\n\n");
            seat:
                printf("   ENTER THE SEAT NUMBER: ");
                scanf("%d", &seatNumber);
                if (seatNumber <= 0 || seatNumber > 32)
                {
                    greenColor();
                    printf("\n   ENTER VALID SEAT NUMBER!!\n\n");
                    resetColor();
                    goto seat;
                }
                if (busSeat[choice][seatNumber] == 1)
                {
                    greenColor();
                    printf("\n   SEAT ALREADY BOOKED! CHOOSE ANOTHER SEAT!!\n\n");
                    resetColor();
                    goto seat;
                }

                CustId = choice * 1000 + seatNumber;
                busSeat[choice][seatNumber] = 1;
                root = insert(&root, CustId);
                greenColor();
                printf("\n   YOUR CUSTOMER ID IS : %d", CustId);
                resetColor();

               
                totalCost += cost(root);
            }

            
            printf("\n\n==================================================================================\n");
            printf("   TOTAL COST FOR YOUR BOOKING: Tk.%d", totalCost);
            printf("\n   DO YOU WANT TO PROCEED WITH PAYMENT? (Y/N): ");
            char paymentConfirmation;
            scanf(" %c", &paymentConfirmation);

            if (paymentConfirmation == 'Y' || paymentConfirmation == 'y')
            {
                greenColor();
                printf("\n   PLEASE CHOOSE A PAYMENT METHOD:\n");
                printf("   [1] Mobile Banking\n");
                printf("   [2] Credit/Debit Card\n");
                resetColor();
                int paymentMethod;
                scanf("%d", &paymentMethod);

                if (paymentMethod == 1)
                {
                    
                    int bankChoice;
                    greenColor();
                    printf("\n   SELECT YOUR MOBILE BANKING OPTION:\n");
                    printf("   [1] Bkash\n");
                    printf("   [2] Nagad\n");
                    printf("   [3] Rocket\n");
                    resetColor();
                    scanf("%d", &bankChoice);

                    char accountNumber[50];
                    char accountPassword[20];
                    greenColor();
                    printf("\n   ENTER YOUR ACCOUNT NUMBER: ");
                    resetColor();
                    scanf("%s", accountNumber);
                    greenColor();
                    printf("\n   ENTER YOUR ACCOUNT PASSWORD: ");
                    resetColor();
                    scanf("%s", accountPassword);

                    
                    char confirmation[10];
                    greenColor();
                    printf("\n   CONFIRM PAYMENT? (Type 'CONFIRM' to confirm or 'CANCEL' to cancel): ");
                    resetColor();
                    scanf("%s", confirmation);

                    if (strcmp(confirmation, "CONFIRM") == 0 || strcmp(confirmation, "confirm") == 0)
                    {
                        greenColor();
                        printf("\n   PAYMENT SUCCESSFUL VIA %s! YOUR TICKETS ARE CONFIRMED.\n", 
                               bankChoice == 1 ? "Bkash" : bankChoice == 2 ? "Nagad" : "Rocket");
                        resetColor();
                    }
                    else
                    {
                        greenColor();
                        printf("\n   PAYMENT CANCELED.\n");
                        resetColor();
                        
                        for (int i = 1; i <= seats; i++)
                        {
                            busSeat[choice][seatNumber] = 0; 
                        }
                    }
                }
                else if (paymentMethod == 2)
                {
                    
                    char cardInfo[50];
                    greenColor();
                    printf("\n   ENTER YOUR CARD DETAILS (Card Number, Expiry Date, CVV): ");
                    resetColor();
                    scanf(" %[^\n]s", cardInfo);
                    greenColor();
                    printf("\n   PAYMENT SUCCESSFUL VIA CARD! YOUR TICKETS ARE CONFIRMED.\n");
                    resetColor();
                }
                else
                {
                    greenColor();
                    printf("\n   INVALID PAYMENT METHOD! CANCELLING TRANSACTION.\n");
                    resetColor();
                }

                printf("\n   YOUR RESERVATION NUMBER IS : %d", randomNum);
                printf("\n   PLEASE NOTE DOWN YOUR RESERVATION NUMBER FOR CANCEL BOOKING TICKETS!!\n");
            }
            else
            {
                
                for (int i = 1; i <= seats; i++)
                {
                    busSeat[choice][seatNumber] = 0; 
                }
                greenColor();
                printf("\n   PAYMENT CANCELED. SEATS HAVE BEEN RELEASED.\n");
                resetColor();
            }
            printf("\nPRESS 'ENTER' KEY TO CONTINUE ");
            getch();
            break;

        case 3:
            cancel(randomNum);
            break;
        case 4:
            status();
            break;
        case 5:
        takingReservationNo:
            printf("\n   ENTER YOUR RESERVATION NUMBER :");
            scanf("%d", &reservationNo);
            if (randomNum == reservationNo)
            {
            cust:
                printf("\n   ENTER YOUR CUSTOMER ID :");
                scanf("%d", &custID);
                int custIDmatched = 0;
                root1 = reservationInfo(root, custID, &custIDmatched);
                if (custIDmatched == 0)
                {
                    greenColor();
                    printf("\n   ENTER CORRECT CUSTOMER ID!!\n");
                    resetColor();
                    goto cust;
                }
            }
            else
            {
                greenColor();
                printf("\n INVALID RESERVATION NUMBER PLEASE ENTER CORRECT RESERVATION NUMBER !!\n");
                resetColor();
                goto takingReservationNo;
            }
            break;
        default:
            greenColor();
            printf("\n\n   INVALID INPUT CHOOSE CORRECT OPTION\n");
            resetColor();
            break; 
        }
    } while (num != 6);
    printf("\n\n=====================================================================\n\n");
    printf("THANK YOU FOR USING TicketKothay Application !!\n");
    printf("\n\nPRESS ANY KEY TO EXIT THE END PROGRAM !! \n");
    printf("\n\n");
    getch();
    return 0;
}