#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>

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
void cancel(int randomNum);
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

int cost(BST *r)
{
    int cost, buscost;
    buscost = (r->PassnNo) / 1000; // Fixed typo here
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

void cancel(int randomNum)
{
    int reservationNo;
    int seatNumber;
    int choice;
    char c;
    int seatCancel;
aa:
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
            goto aa;
        }
    }
    else
    {
        printf("\nNOT FOUND!! ENTER THE CORRECT RESERVATION NUMBER\n");
        goto aa;
    }
}

int main()
{
    srand(time(0));
    int randomNum = rand();
    int num, i, custID, reservationNo;
    BST *root1;
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("bus_reservations.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS Reservations("
                                   "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "CustomerID INT, "
                                   "BusNumber INT, "
                                   "SeatNumber INT, "
                                   "ReservationNumber INT);";

    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    login();
main:
    do
    {
        printf("\n\n====================================================================\n\n");
        printf("\t\t\t\033[1;32mBUS RESERVATION\033[0m\t\t");
        printf("\n\n=====================================================================\n"); // Fixed missing terminating " character
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
            int seatNumber;
            for (int i = 1; i <= seats; i++)
            {
                printf("\n\n==================================================================================\n\n");
            seat:
                printf("   ENTER THE SEAT NUMBER: ");
                scanf("%d", &seatNumber);
                if (seatNumber <= 0)
                {
                    greenColor();
                    printf("\n   ENTER VALID SEAT NUMBER!!\n\n");
                    resetColor();
                    goto seat;
                }
                else if (seatNumber > 32)
                {
                    greenColor();
                    printf("\n   ENTER VALID SEAT NUMBER WE HAVE ONLY 32 SEATS IN A BUS !!\n\n");
                    resetColor();
                    goto seat;
                }
                CustId = choice * 1000 + seatNumber;
                busSeat[choice][seatNumber] = 1;
                root = insert(&root, CustId);
                greenColor();
                printf("\n   YOUR CUSTOMER ID IS : %d", CustId);
                resetColor();
                printf("\n\n==================================================================================\n\n");

                const char *sql_insert = "INSERT INTO Reservations (CustomerID, BusNumber, SeatNumber, ReservationNumber) VALUES (?, ?, ?, ?);";
                sqlite3_stmt *stmt;

                rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);

                if (rc != SQLITE_OK) {
                    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 1;
                }

                sqlite3_bind_int(stmt, 1, CustId);
                sqlite3_bind_int(stmt, 2, choice);
                sqlite3_bind_int(stmt, 3, seatNumber);
                sqlite3_bind_int(stmt, 4, randomNum);

                rc = sqlite3_step(stmt);

                if (rc != SQLITE_DONE) {
                    fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
                }

                sqlite3_finalize(stmt);
            }
            printf("\nYOUR RESERVATION NUMBER IS : ");
            greenColor();
            printf("%d\n", randomNum);
            printf("\nPLEASE NOTE DOWN YOUR RESERVATION NUMBER FOR CANCEL BOOKING TICKETS!!\n");
            resetColor();
            printf("PRESS 'ENTER' KEY TO CONTINUE ");
            getch();
            break;
        case 3:
            cancel(randomNum);
            break;
        case 4:
            status(randomNum);
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
    } while (num != 6); // Fixed missing semicolon
    printf("\n\n=====================================================================\n\n");
    printf("THANK YOU FOR USING TicketKothay Application !!\n");
    printf("\n\nPRESS ANY KEY TO EXIT THE END PROGRAM !! \n");
    printf("\n\n");
    getch();
    sqlite3_close(db);
    return 0;
}