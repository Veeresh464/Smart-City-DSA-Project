#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#define null 0
#define MaxQueue 25
#define MaxPlace 25
#define totalhotels 40
#define _INT_MAX_ 999999999
//========================================================================================Manoj Railway=========================================================================================
//*************************************Timng*********************************************************
typedef struct Timings
{
    int Hour, Minutes;
} Timings;

//********************************************************************************Structures for Ticket***********************************************************************************
typedef struct TraindetailsForTicket
{
    char TrainName[30];
    int TrainNo;
    Timings Time;
    char TicketType[3];
    int price;
} TraindetailsForTicket;

typedef struct ticket
{
    char PName[30];
    long long int AdharNumber;
    int Age;
    char Gender;
    int TicketNo;
    char Source[20];
    char Destination[20];
    TraindetailsForTicket Train;
    struct ticket *Next;
} Ticket;

typedef struct PassengerQueue
{
    int trainNo;
    Ticket queue[MaxQueue];
    int front;
    int rear;

} Queue;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//*****************************************************************Train Details Structures For system***********************************************************************************
typedef struct TrainDetailsForSystem
{
    char TrainName[30];
    int TrainNo;
    Timings Time;
    char Source[30];
    char Destination[30];
    int price[5];     // 0-1AC,1-2AC ,2-3AC,3-SL,4-GN
    int seats[5];     // ALREADY BOOKED
    int seatsLeft[5]; // REMAING SEATS
    struct TrainDetailsForSystem *next;
} TrainDetailsForSystem;
//-------------------------------------------------------------------------------------end------------------------------------------------------------------------------------------------
typedef struct doubleLinkedList
{
    TrainDetailsForSystem *ptr;
    struct doubleLinkedList *next;
    struct doubleLinkedList *prev;

} SkipList;
// ***************************************************Programs for Creating,Reading and Insertion of New Train **************************************************************************
TrainDetailsForSystem *CreatingTrainNode()
{
    TrainDetailsForSystem *temp = (TrainDetailsForSystem *)malloc(sizeof(TrainDetailsForSystem));
    if (temp != NULL)
    {
        temp->next = NULL;
        temp->TrainName[0] = '\0';
        temp->TrainNo = 0;
        temp->Time.Hour = 0;
        temp->Time.Minutes = 0;
        temp->Source[0] = '\0';
        temp->Destination[0] = '\0';
        for (int i = 0; i < 5; i++)
        {
            temp->price[i] = 0;
            temp->seats[i] = 0;
            temp->seatsLeft[i] = 0;
        }
    }
    return temp;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PrintTrainInfo(TrainDetailsForSystem *Train)
{
    printf("------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Train Number:%d ||", Train->TrainNo);
    printf("Train Name:%s", Train->TrainName);
    printf("Start-Destination:%s To %s", Train->Source, Train->Destination);
    printf("Timing:%d:%d\n", Train->Time.Hour, Train->Time.Minutes);
    printf("Prices: 1AC:%d 2AC:%d 3AC:%d SL:%d GN:%d\n", Train->price[0], Train->price[1], Train->price[2], Train->price[3], Train->price[4]);
    printf("Available Seats in different categories:\n");
    printf("1AC\t2AC\t3AC\tSL:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("%d\t", Train->seats[i]);
    }
    printf("\n");
    printf("Seats Left:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("%d\t", Train->seatsLeft[i]);
    }
    printf("\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------\n");

    return;
}
//********************************************Linked List is Created for the strctures extracted from the Train.txt ********************************************************************

TrainDetailsForSystem *InsertionNewTrain(TrainDetailsForSystem *TrainList, TrainDetailsForSystem *NewTrain)
{
    if (TrainList == NULL)
    {
        TrainList = NewTrain;
        return TrainList;
    }
    else if (TrainList->next == NULL)
    {
        if (TrainList->TrainNo > NewTrain->TrainNo)
        {
            NewTrain->next = TrainList;
            TrainList = NewTrain;
        }
        else
        {
            TrainList->next = NewTrain;
        }
        return TrainList;
    }
    else
    {
        if (TrainList->TrainNo > NewTrain->TrainNo)
        {
            NewTrain->next = TrainList;
            TrainList = NewTrain;
        }
        else
        {
            TrainDetailsForSystem *Temp = TrainList;
            while (Temp->next != NULL && Temp->next->TrainNo < NewTrain->TrainNo)
            {
                Temp = Temp->next;
            }
            NewTrain->next = Temp->next;
            Temp->next = NewTrain;
        }
    }
    return TrainList;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/***************************SKIP LIST******************************/
SkipList *CreateSkipListNode()
{
    SkipList *temp;
    temp = (SkipList *)malloc(sizeof(SkipList));
    temp->ptr;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

SkipList *Linking(TrainDetailsForSystem *TrainList)
{
    SkipList *low, *mid, *up;
    low = CreateSkipListNode();
    mid = CreateSkipListNode();
    up = CreateSkipListNode();

    low->ptr = TrainList;
    mid->ptr = TrainList;
    up->ptr = TrainList;

    TrainDetailsForSystem *temp = TrainList;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    up->ptr = temp;

    temp = TrainList;
    while (temp->next->next != NULL)
    {
        mid->ptr = temp;
        temp = temp->next;
    }

    low->next = mid;
    mid->next = up;

    up->prev = mid;
    mid->prev = low;
    return low;
}
//****************************************************************************Searching*****************************************************************************************************
//================================Searching details of Train When customers book ticket ,to aasign the Name Price,seat  of Train by the system==========================================
// TrainDetailsForSystem *SearchingTrain(TrainDetailsForSystem *TrainList, int Train_No, SkipList *Sklist)
// {
//     if (TrainList == NULL)
//         return NULL;

//     TrainDetailsForSystem *temp = TrainList;

//     while (temp != NULL)
//     {
//         if (temp->TrainNo == Train_No)
//         {
//             return temp;
//         }
//         else
//         {
//             temp = temp->next;
//         }
//     }
//     return NULL;
// }

TrainDetailsForSystem *SearchingTrain(TrainDetailsForSystem *TrainList, int Train_No, SkipList *Sklist)
{
    if (TrainList == NULL)
        return NULL;

    TrainDetailsForSystem *start = TrainList;
    TrainDetailsForSystem *end = NULL;
    if (Sklist->ptr->TrainNo == Train_No)
    {
        return Sklist->ptr;
    }
    else if (Sklist->ptr->TrainNo > Train_No)
    {
        if (Sklist->prev->ptr->TrainNo == Train_No)
        {
            return Sklist->prev->ptr;
        }
        else
        {
            start = Sklist->prev->ptr;
            end = Sklist->ptr;
        }
    }
    else
    {
        if (Sklist->next->ptr->TrainNo == Train_No)
        {
            return Sklist->next->ptr;
        }
        else
        {
            start = Sklist->ptr;
            end = Sklist->next->ptr;
        }
    }

    do
    {
        if (start->TrainNo == Train_No)
            return start;
        else
            start = start->next;
    } while (start != end);

    return NULL;
}
//==============================================Searching By the customers to check if a train avilable on that route===============================================================================

int SearchTrain(TrainDetailsForSystem *TrainList, char TSource[30], char Tdestination[30])
{
    int flag = 0;
    if (TrainList == NULL)
    {
        return flag;
    }
    TrainDetailsForSystem *temp = TrainList;

    while (temp != NULL)
    {
        if ((strcmp(temp->Source, TSource) == 0) && (strcmp(temp->Destination, Tdestination) == 0))
        {

            PrintTrainInfo(temp);
            flag = 1;
        }

        temp = temp->next;
    }
    return flag;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//===================================================================================Applied Function For Generating A Ticket============================================================

Ticket *GeneratingTicket()
{
    Ticket *Temp;
    Temp = (Ticket *)malloc(sizeof(Ticket));
    Temp->Next = NULL;
    return Temp;
}

int TicketNoValue(long int adharno)
{
    int value = 0;
    for (int i = 1; i <= 4; i++)
    {
        value = value * 10 + adharno % 10;
        adharno = adharno / 10;
    }
    return abs(value);
}

int TrainTicketPrice(char str[3])
{
    if (strcmp(str, "1AC") == 0)
        return 0;
    else if (strcmp(str, "2AC") == 0)
        return 1;
    else if (strcmp(str, "3AC") == 0)
        return 2;
    else if (strcmp(str, "SL") == 0)
        return 3;
    else if (strcmp(str, "GN") == 0)
        return 4;
}

Ticket *SystemAssignedInfo(TrainDetailsForSystem *TrainList, Ticket *temp, SkipList *sklist)
{

    temp->TicketNo = temp->Train.TrainNo + TicketNoValue(TicketNoValue(temp->AdharNumber));
    TrainDetailsForSystem *t = SearchingTrain(TrainList, temp->Train.TrainNo, sklist);
    strcpy(temp->Train.TrainName, t->TrainName);
    temp->Train.price = t->price[TrainTicketPrice(temp->Train.TicketType)];
    temp->Train.Time.Hour = t->Time.Hour;
    temp->Train.Time.Minutes = t->Time.Minutes;
    t->seatsLeft[TrainTicketPrice(temp->Train.TicketType)] = TrainList->seatsLeft[TrainTicketPrice(temp->Train.TicketType)] - 1;
}
//---------------------------    ---------------------------      -------Info Asked when a ticket is created-----------------------     -----------------------------------
Ticket *GetDetails(TrainDetailsForSystem *TrainList, int TrainNumberforChecking, char *classstr, SkipList *sklist)
{
    int i = 0;
    char ch;
    Ticket *temp = GeneratingTicket();
    if (temp == NULL)
    {
        return NULL;
    }
    else
    {
        //------------------------------------------------------------------------------------
        temp->Train.TrainNo = TrainNumberforChecking;
        strcpy(temp->Train.TicketType, classstr);
        //------------------------------------------------------------------------------------
        printf("Enter Name:");
        fflush(stdin);
        fgets(temp->PName, sizeof(temp->PName), stdin);
        printf("Enter Adhar No:");
        scanf("%lld", &temp->AdharNumber);
        printf("Enter Age:");
        scanf("%d", &temp->Age);
        printf("Enter Gender:");
        scanf(" %c", &temp->Gender);
        printf("Enter Starting-point:");
        fflush(stdin);
        fgets(temp->Source, sizeof(temp->Source), stdin);
        i = 0;
        while (temp->Source[i] != '\0')
        {
            ch = temp->Source[i];
            ch = toupper(ch);
            temp->Source[i] = ch;
            i++;
        }
        printf("Enter Destination:");
        fgets(temp->Destination, sizeof(temp->Destination), stdin);
        i = 0;
        while (temp->Destination[i] != '\0')
        {
            ch = temp->Destination[i];
            ch = toupper(ch);
            temp->Destination[i] = ch;
            i++;
        }

        SystemAssignedInfo(TrainList, temp, sklist);
    }
    return temp;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//******************************************************WaitingList*********************************************************************************************

//******************************************************************************Passengers List of Passengers Booked Ticket******************************************************************************************

Ticket *PassengerDetailInsertion(Ticket *PassengerList, Ticket *NewPassenger)
{
    if (PassengerList == NULL)
    {
        PassengerList = NewPassenger;
        return PassengerList;
    }
    Ticket *Temp = PassengerList;
    while (Temp->Next != NULL)
    {
        Temp = Temp->Next;
    }
    Temp->Next = NewPassenger;
    return PassengerList;
}

//************************Prints details of Ticket Booked By Passenger**************************************

void PrintTrainTicket(Ticket *NewPassenger)
{
    printf("---------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Name:%s AdharNo:%lld\n", NewPassenger->PName, NewPassenger->AdharNumber);
    printf("TicketNo:%d  Timings:%d:%d\n", NewPassenger->TicketNo, NewPassenger->Train.Time.Hour, NewPassenger->Train.Time.Minutes);
    printf("Start to Destination:%s to %s", NewPassenger->Source, NewPassenger->Destination);
    printf("Train Name: %s    TrainNo:%d\n", NewPassenger->Train.TrainName, NewPassenger->Train.TrainNo);
    printf("Price:%d   Class:%s\n", NewPassenger->Train.price, NewPassenger->Train.TicketType);
    printf("---------------------------------------------------------------------------------------------------------------------------------\n");
    return;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//**********************************************************************Booked Ticket Deletion********************************************************************************************

Ticket *BookedTicketDeletion(Ticket *PassengersList, int TicketNoForDeletion, Queue *q)
{
    int flag = 0;
    Ticket *prev = NULL;
    if (PassengersList == NULL)
    {
        printf("1");
        printf("No Ticket Booked with Given Number.\n");
        return PassengersList;
    }
    if (PassengersList->Next == NULL && PassengersList->TicketNo == TicketNoForDeletion)
    {
        free(PassengersList);
        PassengersList = NULL;
        flag = 1;
    }

    else if (PassengersList->TicketNo == TicketNoForDeletion)
    {
        prev = PassengersList;
        PassengersList = PassengersList->Next;
        free(prev);
        flag = 1;
    }
    else
    {
        Ticket *temp = PassengersList;
        prev = NULL;

        while (temp->Next != NULL)
        {
            if (temp->TicketNo == TicketNoForDeletion)
            {
                prev->Next = temp->Next;
                free(temp);
                temp = NULL;
                flag = 1;
                return PassengersList;
            }
            prev = temp;
            temp = temp->Next;
        }
    }
    if (flag)
    {
        printf("Thank You Ticket with Ticket number :%d has cancelled Successfully.\n", TicketNoForDeletion);
    }
    else
    {
        printf("No Ticket Booked with Given Number.\n");
    }
    return PassengersList;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int CheckAvailabilityoofTicket(TrainDetailsForSystem *Trainlist, int TrainNo, char *str, SkipList *sklist)
{
    // return 2 for can book,1 for waiting list,0 for exit
    TrainDetailsForSystem *t = SearchingTrain(Trainlist, TrainNo, sklist);
    int class = TrainTicketPrice(str);
    int choice;

    if (t->seatsLeft[class] == 0)
    {
        printf("The Seats of this class are booked already.Here you can do these things.\n");
        printf("Select seats in different class.\n");
        printf("Booking in Waiting List.\n");
        printf("(Note:Waiting List Tickets are not cancelled until system cancels it autometically and amoount is refunded after cancellation.\n)");
        printf("Enter 1 for waiting List,0 for exit.\n");
        scanf("%d", &choice);
        if (choice == 1)
            return 1;
        else
            return 0;
    }
    else
        return 2;
}

// //*****************************Waiting List ****************************************************************
void assigningstructurequeue(TrainDetailsForSystem *TrainList, Queue q[MaxQueue])
{
    int i = 0;
    TrainDetailsForSystem *t = TrainList;
    do
    {
        q[i].trainNo = TrainList->TrainNo;
        i++;
        t = t->next;
        q[i].front = -1;
        q[i].rear = 0;
    } while (t != NULL);
}

int enqueuePassenger(Queue q[MaxQueue], Ticket *t)
{
    int Number = t->Train.TrainNo;
    int index = -1;
    for (int i = 0; i < MaxQueue; i++)
    {
        if (q[i].trainNo == Number)
            index = i;
    }
    if (q[index].front == MaxQueue - 1)
    {
        return 0;
    }
    {
        q[index].front++;
        strcpy(q[index].queue[q->front].PName, t->PName);
        q[index].queue[q->front].AdharNumber = t->AdharNumber;
        q[index].queue[q->front].Age = t->Age;
        q[index].queue[q->front].Gender = t->Gender;
        q[index].queue[q->front].TicketNo = t->TicketNo;
        strcpy(q[index].queue[q->front].Source, t->Source);
        strcpy(q[index].queue[q->front].Destination, t->Destination);
        q[index].queue[q->front].Train.price = t->Train.price;
        q[index].queue[q->front].Train.TrainNo = t->Train.TrainNo;
        strcpy(q[index].queue[q->front].Train.TrainName, t->Train.TrainName);
        strcpy(q[index].queue[q->front].Train.TicketType, t->Train.TicketType);
        q[index].queue[q->front].Train.Time.Hour = t->Train.Time.Hour;
        q[index].queue[q->front].Train.Time.Minutes = t->Train.Time.Minutes;
        return 1;
    }
    return 0;
}

Ticket *SystemAssignedInfoforWaitingList(TrainDetailsForSystem *TrainList, Ticket *temp, SkipList *sklist)
{

    temp->TicketNo = temp->Train.TrainNo + TicketNoValue(TicketNoValue(temp->AdharNumber));
    TrainDetailsForSystem *t = SearchingTrain(TrainList, temp->Train.TrainNo, sklist);
    strcpy(temp->Train.TrainName, t->TrainName);
    temp->Train.price = t->price[TrainTicketPrice(temp->Train.TicketType)];
    temp->Train.Time.Hour = t->Time.Hour;
    temp->Train.Time.Minutes = t->Time.Minutes;
}

Ticket *GetDetailsforWaitingList(TrainDetailsForSystem *TrainList, int trainNumber, char *str, SkipList *sklist)
{
    int i = 0;
    char ch;
    Ticket *temp = GeneratingTicket();
    if (temp == NULL)
    {
        return NULL;
    }
    else
    {
        //------------------------------------------------------------------------------------
        temp->Train.TrainNo = trainNumber;
        strcpy(temp->Train.TicketType, str);

        //------------------------------------------------------------------------------------
        printf("Enter Name:");
        fflush(stdin);
        fgets(temp->PName, sizeof(temp->PName), stdin);
        printf("Enter Adhar No:");
        scanf("%lld", &temp->AdharNumber);
        printf("Enter Age:");
        scanf("%d", &temp->Age);
        printf("Enter Gender:");
        scanf(" %c", &temp->Gender);
        printf("Enter Starting-point:");
        fflush(stdin);
        fgets(temp->Source, sizeof(temp->Source), stdin);
        i = 0;
        while (temp->Source[i] != '\0')
        {
            ch = temp->Source[i];
            ch = toupper(ch);
            temp->Source[i] = ch;
            i++;
        }
        printf("Enter Destination:");
        fgets(temp->Destination, sizeof(temp->Destination), stdin);
        i = 0;
        while (temp->Destination[i] != '\0')
        {
            ch = temp->Destination[i];
            ch = toupper(ch);
            temp->Destination[i] = ch;
            i++;
        }

        SystemAssignedInfoforWaitingList(TrainList, temp, sklist);
    }
    return temp;
}
//=================================================================================Manoj Railway End========================================================================================

//==================================================================================Manoj Tourist Spots Begin================================================================================
//****************************Tourist Spot Structure for details**************

typedef struct Tourist_Spots
{
    int key;
    char PlaceName[40];
    char Address[50];
    int EntryPrice[2]; // Children and adult
    float Rating;
    char Description[150]; // Short description about the location
} TouristPlace;
//------------------------------------------------------------------------------

//********************************Matrix Representation of Graph*****************
typedef struct MatrixGraph
{
    int matrix[MaxPlace][MaxPlace];
} MatrixGraph;

MatrixGraph *CreateMatrixGraph()
{
    MatrixGraph *Temp;
    Temp = (MatrixGraph *)malloc(sizeof(MatrixGraph));
    for (int i = 0; i < MaxPlace; i++)
    {
        for (int j = 0; j < MaxPlace; j++)
        {
            Temp->matrix[i][j] = -1;
        }
    }
    return Temp;
}

//*************************Traversal********************************
//-------------------------BFS-----------------------------
typedef struct queue
{
    int array[MaxPlace];
    int front;
    int rear;
} queue;

int isFull(queue *q)
{
    if (q->front == MaxPlace - 1)
        return 1;
    return 0;
}

int isEmpty(queue *q)
{
    if (q->rear > q->front)
        return 1;
    return 0;
}

void enqueue(queue *q, int data)
{
    if (isFull(q))
    {
        printf("Queue is full.\n");
        return;
    }
    q->front++;
    q->array[q->front] = data;
    return;
}

int dequeue(queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is Empty.\n");
        return -1;
    }
    int n;
    n = q->array[q->rear];
    q->rear++;
    return n;
}

void DisplayPlaces(TouristPlace *t)
{
    printf("--------------------------------------------------------------------------------\n");
    printf("Key:%d\n", t->key);
    printf("Place Name:%s\n", t->PlaceName);
    printf("Location:%s\n", t->Address);
    printf("Entry Prices:for adult:%d Children:%d\n", t->EntryPrice[0], t->EntryPrice[1]);
    printf("Ratings:%.1f\n", t->Rating);
    printf("Description:\n");
    printf("%s\n", t->Description);

    printf("--------------------------------------------------------------------------------\n");
    return;
}

void BFS(MatrixGraph *Map, TouristPlace array[], int SourceIndex)
{
    queue q;
    q.front = -1;
    q.rear = 0;
    int currentNode;
    int Visited[MaxPlace];
    for (int i = 0; i < MaxPlace; i++)
        Visited[i] = 0;
    Visited[SourceIndex] = 1;
    enqueue(&q, SourceIndex);
    while (!isEmpty(&q))
    {
        currentNode = dequeue(&q);

        DisplayPlaces(&array[currentNode]);
        for (int i = 0; i < MaxPlace; i++)
        {
            if (Map->matrix[currentNode][i] != -1 && !Visited[i])
            {
                enqueue(&q, i);
                Visited[i] = 1;
            }
        }

        printf("\n");
    }
    return;
}

//-------------------------Dikstras Algorithm----------------------------------

int MinimumWeightedIndex(int Distance[MaxPlace], int Visited[MaxPlace])
{
    int min = __INT_MAX__;
    int min_index;
    for (int i = 0; i < MaxPlace; i++)
    {
        if (Distance[i] <= min && Visited[i] == 0)
        {
            min = Distance[i], min_index = i;
        }
    }
    return min_index;
}

void printNearbyPlaces(TouristPlace array[], int Distance[], int order[], int n, int Startingindex)
{
    printf("========================================================================\n");
    printf("Nearby Tourist Spots to %s are:\n", array[Startingindex].PlaceName);
    printf("========================================================================\n");
    printf("        Key          Place Name               Distance(in KM)\n");
    for (int i = 1; i < n; i++)
    {
        printf("%d)       %d           %s         ->              %d\n", i, array[order[i]].key, array[order[i]].PlaceName, Distance[order[i]]);
    }
    printf("-----------------------------------------------------------------------\n");

    int choice;
    TouristPlace *ptr;
    int indexValue;
    while (1)
    {
        printf("Enter 1 to know Details of Any Location,2 for exit:\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Enter Key of Place:");
            scanf("%d", &indexValue);

            if (indexValue >= 0 && indexValue < n)
            {
                ptr = &array[indexValue];
                DisplayPlaces(ptr);
            }
            else
            {
                printf("Invalid Key.\n");
                continue;
            }
        }
        else
        {
            break;
        }
    }
}

void DikstrasAlgorithm(MatrixGraph *GraphofPlaces, TouristPlace array[], int n, int Startingindex)
{
    int Visited[MaxPlace];
    int Distance[MaxPlace];
    int min_index;
    int order[MaxPlace];
    for (int i = 0; i < MaxPlace; i++)
    {
        Visited[i] = 0;
        Distance[i] = __INT_MAX__;
    }

    Distance[Startingindex] = 0;

    for (int i = 0; i < MaxPlace; i++)
    {
        min_index = MinimumWeightedIndex(Distance, Visited);
        Visited[min_index] = 1;
        order[i] = min_index;
        for (int v = 0; v < MaxPlace; v++)
        {
            if (GraphofPlaces->matrix[min_index][v] != -1 && !Visited[v] && Distance[min_index] + GraphofPlaces->matrix[min_index][v] < Distance[v] && Distance[min_index] != __INT_MAX__)
            {

                Distance[v] = Distance[min_index] + GraphofPlaces->matrix[min_index][v];
            }
        }
    }
    printNearbyPlaces(array, Distance, order, n, Startingindex);

    return;
}

//*******************************************Sorting **************************************************
// Insertion Sorting

void InsertionSorting(TouristPlace array[], int n)
{
    TouristPlace Tour[n];
    for (int i = 0; i < n; i++)
    {
        Tour[i].key = array[i].key;
        strcpy(Tour[i].PlaceName, array[i].PlaceName);
        strcpy(Tour[i].Address, array[i].Address);
        strcpy(Tour[i].Description, array[i].Description);
        Tour[i].EntryPrice[0] = array[i].EntryPrice[0];
        Tour[i].EntryPrice[1] = array[i].EntryPrice[1];
        Tour[i].Rating = array[i].Rating;
    }
    int j;
    TouristPlace temp;
    for (int i = 1; i < n; i++) // Fix: Change i > 0 to i >= 0
    {
        j = i - 1;
        temp.key = Tour[i].key;
        strcpy(temp.PlaceName, Tour[i].PlaceName);
        strcpy(temp.Address, Tour[i].Address);
        strcpy(temp.Description, Tour[i].Description);
        temp.EntryPrice[0] = Tour[i].EntryPrice[0];
        temp.EntryPrice[1] = Tour[i].EntryPrice[1];
        temp.Rating = Tour[i].Rating;
        while (j >= 0 && Tour[j].EntryPrice[1] > temp.EntryPrice[1])
        {
            Tour[j + 1].key = Tour[j].key;
            strcpy(Tour[j + 1].PlaceName, Tour[j].PlaceName);
            strcpy(Tour[j + 1].Address, Tour[j].Address);
            strcpy(Tour[j + 1].Description, Tour[j].Description);
            Tour[j + 1].EntryPrice[0] = Tour[j].EntryPrice[0];
            Tour[j + 1].EntryPrice[1] = Tour[j].EntryPrice[1];
            Tour[j + 1].Rating = Tour[j].Rating;
            j--;
        }
        Tour[j + 1].key = temp.key;
        strcpy(Tour[j + 1].PlaceName, temp.PlaceName);
        strcpy(Tour[j + 1].Address, temp.Address);
        strcpy(Tour[j + 1].Description, temp.Description);
        Tour[j + 1].EntryPrice[0] = temp.EntryPrice[0];
        Tour[j + 1].EntryPrice[1] = temp.EntryPrice[1];
        Tour[j + 1].Rating = temp.Rating;
    }
    for (int i = 0; i < n; i++)
    {
        TouristPlace *ptr = &Tour[i];
        DisplayPlaces(ptr);
    }
    return;
}

// Selection Sort
void SelectionSorting(TouristPlace array[], int n)
{
    TouristPlace Tour[n];
    for (int i = 0; i < n; i++)
    {
        Tour[i].key = array[i].key;
        strcpy(Tour[i].PlaceName, array[i].PlaceName);
        strcpy(Tour[i].Address, array[i].Address);
        strcpy(Tour[i].Description, array[i].Description);
        Tour[i].EntryPrice[0] = array[i].EntryPrice[0];
        Tour[i].EntryPrice[1] = array[i].EntryPrice[1];
        Tour[i].Rating = array[i].Rating;
    }

    int Max;
    float Rating;
    TouristPlace temp;
    for (int i = 0; i < n; i++)
    {
        Rating = Tour[i].Rating;
        Max = i;
        for (int j = i + 1; j < n; j++)
        {
            if (Tour[j].Rating > Rating)
            {
                Max = j;
            }
        }

        if (i != Max)
        {
            temp.key = Tour[i].key;
            strcpy(temp.PlaceName, Tour[i].PlaceName);
            strcpy(temp.Address, Tour[i].Address);
            strcpy(temp.Description, Tour[i].Description);
            temp.EntryPrice[0] = Tour[i].EntryPrice[0];
            temp.EntryPrice[1] = Tour[i].EntryPrice[1];
            temp.Rating = Tour[i].Rating;

            Tour[i].key = Tour[Max].key;
            strcpy(Tour[i].PlaceName, Tour[Max].PlaceName);
            strcpy(Tour[i].Address, Tour[Max].Address);
            strcpy(Tour[i].Description, Tour[Max].Description);
            Tour[i].EntryPrice[0] = Tour[Max].EntryPrice[0];
            Tour[i].EntryPrice[1] = Tour[Max].EntryPrice[1];
            Tour[i].Rating = Tour[Max].Rating;

            Tour[Max].key = temp.key;
            strcpy(Tour[Max].PlaceName, temp.PlaceName);
            strcpy(Tour[Max].Address, temp.Address);
            strcpy(Tour[Max].Description, temp.Description);
            Tour[Max].EntryPrice[0] = temp.EntryPrice[0];
            Tour[Max].EntryPrice[1] = temp.EntryPrice[1];
            Tour[Max].Rating = temp.Rating;
        }
    }

    for (int i = 0; i < n; i++)
    {
        TouristPlace *ptr = &Tour[i];
        DisplayPlaces(ptr);
    }
    return;
}
//------------------------------------Veeresh code begin--------------------------------------------------------------
struct data
{
    char placename[20];
    int key;
};

struct node
{
    struct data place;
    struct node *linkf;
};

struct hashTable
{
    struct node **head;
    int tableSize;
    int noofhkeys;
};

int nearprime(int n)
{
    for (int i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            n = n + 1;
            i = 1;
        }
    }
    return n;
}

//-----------------------------------------------------------------------------------------------------------
// START OF HASHING FOR STORING THE DETAILS OF PLACES FROM FILE TO THE RAM
//-----------------------------------------------------------------------------------------------------------

void init(struct hashTable *h)
{
    int ts;
    printf("Enter total approximate places\n");
    scanf("%d", &ts);
    printf("As you entered total approx places is = %d\n", ts);
    ts = nearprime(ts);
    printf("So the table size preffered to use for hash is %d\n", ts);
    h->tableSize = ts;
    h->noofhkeys = 0;
    h->head = (struct node **)malloc(h->tableSize * sizeof(struct node *));
    for (int i = 0; i < h->tableSize; i++)
    {
        h->head[i] = null;
    }
}

int hash(struct hashTable *h, int key)
{
    int idx = abs(key) % h->tableSize;
    return idx;
}

void addkey(struct hashTable *h, int key, char place[])
{
    int idx = hash(h, key);
    struct node *p;
    p = (struct node *)malloc(sizeof(struct node));
    strcpy(p->place.placename, place);
    p->place.key = key;
    p->linkf = null;
    if (h->head[idx] == null)
    {
        h->head[idx] = p;
    }
    else
    {
        struct node *start = h->head[idx];
        while (start->linkf != null)
        {
            start = start->linkf;
        }
        start->linkf = p;
    }
    h->noofhkeys++;
}

int deletekey(struct hashTable *h, int key)
{
    int idx = hash(h, key);
    struct node *curr, *prev, *next;
    curr = h->head[idx];
    prev = null;
    while (curr != null && curr->place.key != key)
    {
        prev = curr;
        curr = curr->linkf;
    }
    if (curr == null)
    {
        return 0;
    }
    else if (curr == h->head[idx])
    {
        h->head[idx] = curr->linkf;
        printf("Place deleated=%s key=%d \n", curr->place.placename, curr->place.key);
        free(curr);
        h->noofhkeys--;
        return 1;
    }
    else
    {
        prev->linkf = curr->linkf;
        printf("Place deleated=%s key=%d \n", curr->place.placename, curr->place.key);
        free(curr);
        h->noofhkeys--;
        return 1;
    }
    return 0;
}

void disp(struct hashTable *h)
{
    for (int i = 0; i < h->tableSize; i++)
    {
        struct node *start = h->head[i];
        while (start != null)
        {
            printf("Place Name=%s Key=%d ", start->place.placename, start->place.key);
            start = start->linkf;
        }
        printf("\n");
    }
}

int searchkey(struct hashTable *h, int key)
{
    int idx = hash(h, key);
    if (h->head[idx] == null)
    {
        return 0;
    }
    else
    {
        struct node *start = h->head[idx];
        while (start != null)
        {
            if (start->place.key == key)
            {
                printf("Place name=%s\n", start->place.placename);
                return 1;
            }
            start = start->linkf;
        }
        return 0;
    }
}

void deletetable(struct hashTable *h)
{
    for (int i = 0; i < h->tableSize; i++)
    {
        struct node *curr = h->head[i];
        while (curr != null)
        {
            h->head[i] = curr->linkf;
            free(curr);
            curr = h->head[i];
        }
    }
    h->noofhkeys = 0;
}

void editplaces(struct hashTable *h)
{
    printf("\n");
    void addkey(struct hashTable * h, int key, char place[]);
    int deletekey(struct hashTable * h, int key);
    int searchkey(struct hashTable * h, int key);
    void deletetable(struct hashTable * h);
    void disp(struct hashTable * h);
    FILE *file;

    int ch, key, ans;
    do
    {
        printf("0--Back to main menu\n");
        printf("1--Add places\n");
        printf("2--Delete places\n");
        printf("3--Search places\n");
        printf("4--Delete complete places(delete table)\n");
        printf("5--Display places (display table)\n");
        printf("6--Exit(to completely exit from program)\n");

        printf("Enter your choise\n");
        scanf("%d", &ch);

        switch (ch)
        {

        case 1:
            printf("Started reading\n");
            char places[100];

            file = fopen("Places.txt", "r");
            if (file == null)
            {
                fprintf(stderr, "Error in opening the file\n");
                break;
            }

            while (fscanf(file, "%d", &key) == 1)
            {

                fscanf(file, "%[^\n]", places);
                addkey(h, key, places);
            }
            fclose(file);
            printf("Add -- Successful\n");
            printf("\n");
            break;

        case 2:
            printf("Enter the key of the place to be deleted\n");
            scanf("%d", &key);
            ans = deletekey(h, key);
            if (ans == 1)
            {
                printf("Key with its place is found and deleated\n");
            }
            else
            {
                printf("Key with its place is not found thus not deleated\n");
            }
            printf("\n");
            break;

        case 3:
            printf("Enter the place-key that ypu want to search\n");
            scanf("%d", &key);
            ans = searchkey(h, key);
            if (ans == 1)
            {
                printf("The place-key found\n");
            }
            else
            {
                printf("The place-key not found\n");
            }
            printf("\n");
            break;

        case 4:
            deletetable(h);
            printf("Deleated\n");
            printf("\n");
            break;

        case 5:
            disp(h);
            printf("\n");
            break;

        case 6:
            deletetable(h);
            exit(0);
            printf("\n");
            break;
        }

    } while (ch != 0);
}

//-----------------------------------------------------------------------------------------------------------
// START OF HASHING FOR STORING THE DETAILS OF HOSPITAL FROM FILE TO THE RAM
//-----------------------------------------------------------------------------------------------------------

struct hospitaldetails
{
    char Hname[20];
    int hospkey;
    int nearplace;
    char govt;
    int rating;
    int totalcap;
    int beingused;
};

struct nodeHospital
{
    struct hospitaldetails hd;
    struct nodeHospital *linkf;
};

struct hashHospital
{
    struct nodeHospital **head;
    int tableSize;
    int noofhkeys;
};

int hashH(struct hashHospital *h, int key)
{
    int idx = abs(key) % h->tableSize;
    return idx;
}

void init_hashHospital(struct hashHospital *h)
{
    int ts;
    printf("Enter approximate places where hospitals are in the cities.\n");
    scanf("%d", &ts);
    printf("As you entered total approx hospital is = %d\n", ts);
    ts = nearprime(ts);
    printf("So the table size preffered to use for hash is %d\n", ts);
    h->tableSize = ts;
    h->noofhkeys = 0;
    h->head = (struct nodeHospital **)malloc(h->tableSize * sizeof(struct nodeHospital *));
    for (int i = 0; i < h->tableSize; i++)
    {
        h->head[i] = null;
    }
}

void addhospital(struct hashHospital *h, int place_Key, char hospname[], int hospkey, int hosprating, int hosptotcapacity, int hospcurrcapacity, char govt)
{

    int idx = hashH(h, place_Key);
    struct nodeHospital *p;
    p = (struct nodeHospital *)malloc(sizeof(struct nodeHospital));
    strcpy(p->hd.Hname, hospname);
    p->hd.govt = govt;
    p->hd.nearplace = place_Key;
    p->hd.hospkey = hospkey;
    p->hd.rating = hosprating;
    p->hd.totalcap = hosptotcapacity;
    p->hd.beingused = hospcurrcapacity;
    p->linkf = null;
    if (h->head[idx] == null)
    {
        h->head[idx] = p;
    }
    else
    {
        struct nodeHospital *start = h->head[idx];
        while (start->linkf != null)
        {
            start = start->linkf;
        }
        start->linkf = p;
    }
    h->noofhkeys++;
}

int deletehospital(struct hashHospital *h, int key, int hkey)
{
    int idx = hashH(h, key);
    struct nodeHospital *curr, *prev, *next;
    curr = h->head[idx];
    prev = null;
    while (curr != null && curr->hd.hospkey != hkey)
    {
        prev = curr;
        curr = curr->linkf;
    }
    if (curr == null)
    {
        return 0;
    }
    else if (curr == h->head[idx])
    {
        h->head[idx] = curr->linkf;
        printf("Hospital deleated=%s | Place-key=%d | Hospital-key=%d\n", curr->hd.Hname, curr->hd.nearplace, curr->hd.hospkey);
        free(curr);
        h->noofhkeys--;
        return 1;
    }
    else
    {
        prev->linkf = curr->linkf;
        printf("Hospital deleated=%s | Place-key=%d | Hospital-key=%d\n", curr->hd.Hname, curr->hd.nearplace, curr->hd.hospkey);
        free(curr);
        h->noofhkeys--;
        return 1;
    }
    return 0;
}

void deletetothospital(struct hashHospital *h)
{
    for (int i = 0; i < h->tableSize; i++)
    {
        struct nodeHospital *curr = h->head[i];
        while (curr != null)
        {
            h->head[i] = curr->linkf;
            free(curr);
            curr = h->head[i];
        }
    }
    h->noofhkeys = 0;
}

void disphospital(struct hashHospital *h)
{
    for (int i = 0; i < h->tableSize; i++)
    {
        struct nodeHospital *start = h->head[i];
        while (start != null)
        {
            printf("Hospital name=%s | Place-key=%d | Hospital-key=%d | Rating=%d | Govt=%c | Tot-cap=%d | Cur-cap=%d ||", start->hd.Hname, start->hd.nearplace, start->hd.hospkey, start->hd.rating, start->hd.govt, start->hd.totalcap, start->hd.beingused);
            start = start->linkf;
        }
        printf("\n");
    }
}

int searchHospital(struct hashHospital *h, int Pkey, int Hkey)
{
    int idx = hashH(h, Pkey);
    if (h->head[idx] == null)
    {
        return 0;
    }
    else
    {
        struct nodeHospital *start = h->head[idx];
        while (start != null)
        {
            if (start->hd.hospkey == Hkey)
            {
                printf("Hospital=%s\n", start->hd.Hname);
                return 1;
            }
            start = start->linkf;
        }
        return 0;
    }
}

void edithospital(struct hashHospital *h, struct hashTable *hp)
{

    void addhospital(struct hashHospital * h, int place_Key, char hospname[], int hospkey, int hosprating, int hosptotcapacity, int hospcurrcapacity, char govt);
    int deletehospital(struct hashHospital * h, int key, int hkey);
    void deletetothospital(struct hashHospital * h);
    void disphospital(struct hashHospital * h);
    FILE *file;

    int ch, key, ans;
    do
    {
        printf("0--Back to main menu\n");
        printf("1--Add hospitals\n");
        printf("2--Delete hospitals\n");
        printf("3--Delete fullcity hospital(delete table)\n");
        printf("4--Display fullcity hospital(display table)\n");
        printf("5--Search hospital\n");
        printf("6--Exit(to completely exit from program)\n");

        printf("Enter your choise\n");
        scanf("%d", &ch);

        switch (ch)
        {
            // problem identified is in start we are addind approx hospital and we are not checking while adding the hospital how much we have added.
        case 1:
            printf("Starting add\n");
            char hospname[100];
            int place_Key;
            int hospkey;
            int hosprating;
            int hosptotcapacity;
            int hospcurrcapacity;
            char govt;

            file = fopen("Hospital.txt", "r");
            if (file == null)
            {
                fprintf(stderr, "Error in opening the file\n");
                break;
            }
            while (fscanf(file, "%d %99s %d %d %d %d %c",
                          &place_Key, hospname, &hospkey, &hosprating, &hosptotcapacity, &hospcurrcapacity, &govt) == 7)
            {
                // Process the key and other variables as needed
                // For example, print them
                printf("Test -- Initialized\n");
                ans = searchkey(hp, place_Key);
                if (ans == 1)
                {
                    printf("Place exists\n");
                    printf("Test -- Success\n");
                    addhospital(h, place_Key, hospname, hospkey, hosprating, hosptotcapacity, hospcurrcapacity, govt);
                }
                else
                {
                    printf("Test -- Failed ,becz place with place-key is not matching, So the hospital can't be added\n");
                }
            }
            fclose(file);
            printf("Add hospital -- Successful\n");
            printf("\n");
            break;

        case 2:
            printf("Enter the place-key to delete hospital\n");
            scanf("%d", &key);
            int hkey;
            printf("Enter the hospital key\n");
            scanf("%d", &hkey);
            ans = deletehospital(h, key, hkey);
            if (ans == 1)
            {
                printf("Place-key found and hospital deleated\n");
            }
            else
            {
                printf("place-key or hospital key not found hospital not deleated\n");
            }
            printf("\n");
            break;

        case 3:
            deletetothospital(h);
            printf("Deleted\n");
            printf("\n");
            break;

        case 4:
            disphospital(h);
            printf("\n");
            break;

        case 5:
            printf("Enter place key\n");
            int tix, ans, tiy;
            scanf("%d", &tix);
            printf("Enter hospital key\n");
            scanf("%d", &tiy);

            ans = searchHospital(h, tix, tiy);
            if (ans == 1)
            {
                printf("The hospital-key found\n");
            }
            else
            {
                printf("The hospital-key not found\n");
            }
            printf("\n");
            break;

        case 6:
            deletetothospital(h);
            exit(0);
            printf("\n");
            break;
        }

    } while (ch != 0);
}

struct sorthosparray
{
    int rank;
    int hospitalkey;
};

void heapifyhospital(struct sorthosparray arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].rank < arr[largest].rank)
        largest = left;

    if (right < n && arr[right].rank < arr[largest].rank)
        largest = right;

    if (largest != i)
    {
        struct sorthosparray temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapifyhospital(arr, n, largest);
    }
}

void heapSort(struct sorthosparray arr[], int n)
{

    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyhospital(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        struct sorthosparray temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapifyhospital(arr, i, 0);
    }
}

void sorthospital(struct hashHospital *hH, struct hashTable *hP)
{
    int size = hH->noofhkeys;

    struct sorthosparray *p = (struct sorthosparray *)malloc(size * sizeof(struct sorthosparray));

    int index = 0;
    for (int i = 0; i < hH->tableSize; i++)
    {
        struct nodeHospital *start = hH->head[i];
        while (start != null)
        {
            p[index].rank = start->hd.rating;
            p[index].hospitalkey = start->hd.hospkey;
            index++;
            start = start->linkf;
        }
    }

    heapSort(p, size);

    printf("Sorted Hospitals based on Rank (Descending Order):\n");
    for (int i = 0; i < size; i++)
    {
        printf("Hospital Key: %d, Rank: %d\n", p[i].hospitalkey, p[i].rank);
    }

    free(p);
}

//---------------------------------------------------------------------------------------------------------------------
// START OF DIJKSTRAS ALGORITHM FOR THE SHORTEST DISTANCE HOSPITAL
//---------------------------------------------------------------------------------------------------------------------

int map[100];
int available[100];

struct vertex
{
    int dest;
    int wt;
};

struct nodeH
{
    struct vertex data;
    struct nodeH *next;
};

struct heap
{
    struct vertex a[100];
    int size;
};

void readGraph(struct nodeH *graph[], int, int *);
struct vertex extractMin(struct heap *);
void displayArray(int *, int);
void swapInt(int *, int *);
void swap(struct vertex *, struct vertex *);
void heapify(struct heap *, int);
void decreaseKey(struct heap *, int, int);
void dijkstra(struct nodeH *graph[100], int, int, int[]);
int isHeapEmpty(struct heap *);
void displayGraph(struct nodeH *graph[], int);
void addEdgeGraph(struct nodeH *graph[], int, int);
void initHeap(struct heap *);

void addEdgeGraph(struct nodeH *graph[], int src, int des)
{
    int w;
    struct nodeH *p = (struct nodeH *)malloc(sizeof(struct nodeH));
    p->data.dest = des;
    printf("enter wt\n");
    scanf("%d", &w);
    p->data.wt = w;
    p->next = NULL;
    if (graph[src] == NULL)
    {
        graph[src] = p;
    }
    else
    {
        struct nodeH *q;
        q = graph[src];
        while (q->next)
        {
            q = q->next;
        }
        q->next = p;
    }
}

void readGraph(struct nodeH *graph[], int v, int *grapharray)
{
    int i, j, e;
    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            printf("is thr edge from %d to %d\n", i, j);
            scanf("%d", &e);
            if (e == 1)
            {
                addEdgeGraph(graph, i, j);
                grapharray[i] = 1;
                grapharray[j] = 1;
            }
        }
    }
}

void displayGraph(struct nodeH *graph[], int v)
{
    int i;
    for (i = 0; i < v; i++)
    {
        struct nodeH *p = graph[i];
        printf("%d->", i);
        while (p)
        {
            printf("%d,%d\t", p->data.dest, p->data.wt);
            p = p->next;
        }
        printf("\n");
    }
}

void editgraph(struct nodeH *graph[], int v, int *grapharray)
{
    readGraph(graph, v, grapharray);
    displayGraph(graph, v);
}

void displayHeap(struct heap *h)
{
    int i;
    for (i = 0; i < h->size; i++)
    {
        printf("%d %d\n", h->a[i].dest, h->a[i].wt);
    }
}

struct vertex extractMin(struct heap *h)
{
    struct vertex u = h->a[0];
    h->a[0] = h->a[h->size - 1];
    h->size--;
    map[u.dest] = -1;
    map[h->a[0].dest] = 0;
    heapify(h, 0);
    return u;
}

void heapify(struct heap *h, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int min = i;

    if (left < h->size && h->a[left].wt < h->a[min].wt)
        min = left;

    if (right < h->size && h->a[right].wt < h->a[min].wt)
        min = right;

    if (min != i)
    {
        swap(&h->a[i], &h->a[min]);
        // change
        swapInt(&map[h->a[i].dest], &map[h->a[min].dest]);
        heapify(h, min);
    }
}

void decreaseKey(struct heap *h, int i, int k)
{
    h->a[i].wt = k;
    while (i && h->a[i].wt < h->a[(i - 1) / 2].wt)
    {
        swap(&h->a[i], &h->a[(i - 1) / 2]);
        // change
        swapInt(&map[h->a[i].dest], &map[h->a[(i - 1) / 2].dest]);
        i = (i - 1) / 2;
    }
}

void initHeap(struct heap *h)
{
    h->size = 0;
}

int isHeapEmpty(struct heap *h)
{
    return h->size == 0;
}

void swap(struct vertex *a, struct vertex *b)
{
    struct vertex temp = *a;
    *a = *b;
    *b = temp;
}

void swapInt(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void displayArray(int a[], int v)
{
    int i;
    for (i = 0; i < v; i++)
    {
        printf("%d->", i);
        printf("%d\n", a[i]);
    }
}

void dijkstra(struct nodeH *graph[100], int v, int src, int distance[])
{
    struct heap h;
    initHeap(&h);

    int i;

    for (i = 0; i < v; i++)
    {
        h.a[i].dest = i;
        h.a[i].wt = INT_MAX;
        map[i] = i;
        available[i] = 1;
    }

    h.size = v;

    decreaseKey(&h, map[src], 0);

    struct vertex u, e;
    int nv, ni, nw;

    while (!isHeapEmpty(&h))
    {
        u = extractMin(&h);

        distance[u.dest] = u.wt;

        struct nodeH *p = graph[u.dest];
        while (p)
        {
            e = p->data;
            nv = e.dest;
            nw = e.wt;
            ni = map[e.dest];

            if (map[nv] != -1 && (u.wt + nw) < h.a[ni].wt)
            {
                decreaseKey(&h, ni, u.wt + nw);
            }

            p = p->next;
        }
    }
    printf("Distance Array is\n");

    displayArray(distance, v);
}

// PRIMS ALGO FOR BEST ROUTE CONNECTING ALL HOSPITAL

void primshosp(struct nodeH *graph[100], int v, int src)
{
    struct heap h;
    initHeap(&h);
    int ans[100][2] = {INT_MAX};

    int i;
    for (i = 0; i < v; i++)
    {
        h.a[i].dest = i;
        h.a[i].wt = INT_MAX;
        map[i] = i;
        available[i] = 1;
    }
    h.size = v;

    decreaseKey(&h, src, 0);

    struct vertex u, e;
    int nv, ni, nw;

    while (!isHeapEmpty(&h))
    {
        u = extractMin(&h);

        struct nodeH *p = graph[u.dest];
        while (p)
        {
            e = p->data;
            nv = e.dest;
            nw = e.wt;
            ni = map[e.dest];

            if (ni != -1 && nw < h.a[ni].wt)
            {
                decreaseKey(&h, ni, nw);
                ans[nv][0] = u.dest;
                ans[nv][1] = nw;
            }

            p = p->next;
        }
    }

    for (int k = 0; k < v; k++)
    {
        printf("v=%d --> ", k);
        for (int j = 0; j < 2; j++)
        {
            printf("%d ", ans[k][j]);
        }
        printf("\n");
    }
}

//-----------------------------------------------------------------------------------------------------------------------------
// START OF SUBORDINATE FUNCTIONS FOR THE HOSPITAL
//-----------------------------------------------------------------------------------------------------------------------------

void showGovernmentHospital(struct hashHospital *hH, int tot_Places)
{
    int countHosp = 0;
    printf("The details of the Government hospital are\n");
    for (int i = 0; i < tot_Places; i++)
    {
        struct nodeHospital *h = hH->head[i];
        while (h)
        {
            if (h->hd.govt == 'Y')
            {
                printf("Hospital name = %s, Hosptial key = %d, Near place = %d, Govt=%c, Rating = %d, Total capacity = %d, occupied = %d\n", h->hd.Hname, h->hd.hospkey, h->hd.nearplace, h->hd.govt, h->hd.rating, h->hd.totalcap, h->hd.beingused);
                countHosp++;
            }
            h = h->linkf;
        }
    }
    printf("Total government hospital = %d\n", countHosp);
}

void showPrivateHospital(struct hashHospital *hH, int tot_Places)
{
    int countHosp = 0;
    printf("The details of the private hospital are\n");
    for (int i = 0; i < tot_Places; i++)
    {
        struct nodeHospital *h = hH->head[i];
        while (h)
        {
            if (h->hd.govt == 'N')
            {
                printf("Hospital name = %s, Hosptial key = %d, Near place = %d, Govt=%c, Rating = %d, Total capacity = %d, occupied = %d\n", h->hd.Hname, h->hd.hospkey, h->hd.nearplace, h->hd.govt, h->hd.rating, h->hd.totalcap, h->hd.beingused);
                countHosp++;
            }
            h = h->linkf;
        }
    }
    printf("Total private hospital = %d\n", countHosp);
}

void getTotAvailableBed(struct hashHospital *hH, int *available, int tot_Places)
{
    int ans;
    for (int i = 0; i <= tot_Places; i++)
    {
        struct nodeHospital *h = hH->head[i];
        while (h)
        {
            ans = h->hd.totalcap - h->hd.beingused;
            available[h->hd.hospkey] = ans;
            h = h->linkf;
        }
    }
}

void displayHospitalBedCheck(struct hashHospital *hH, int *available)
{
    for (int i = 0; i < hH->noofhkeys; i++)
    {
        printf("Hospital-key = %d, available beds = %d\n", i, available[i]);
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------
// START FOR THE CODE FOR APPOINTMENT
struct appointment
{
    char name[30];
    int hospitalKey;
    int placekey;
    float time;
};

struct nodeForBST
{
    struct appointment patDetail;
    struct nodeForBST *right;
    struct nodeForBST *left;
};

void initroot(struct nodeForBST *root[], int hosp)
{
    for (int i = 0; i < hosp; i++)
    {
        root[i] = null;
    }
}

int addAppointment(struct nodeForBST *root[], struct appointment *k)
{
    struct nodeForBST *p = (struct nodeForBST *)malloc(sizeof(struct nodeForBST));
    strcpy(p->patDetail.name, k->name);
    p->patDetail.hospitalKey = k->hospitalKey;
    p->patDetail.time = k->time;
    if ((root[p->patDetail.hospitalKey]) == null)
    {
        root[p->patDetail.hospitalKey] = p;
    }
    else
    {
        struct nodeForBST *par = null;
        struct nodeForBST *cur = root[k->hospitalKey];
        while (cur != null)
        {
            par = cur;
            if (p->patDetail.time < cur->patDetail.time)
            {
                cur = cur->left;
            }
            else if (p->patDetail.time > cur->patDetail.time)
            {
                cur = cur->right;
            }
            else
            {
                perror("Sorry time is clashing with other patients. Take another time and submit again\n");
                free(p);
                return 0;
            }
        }
        if (p->patDetail.time < p->patDetail.time)
        {
            par->left = p;
        }
        else
        {
            par->right = p;
        }
    }
    return 1;
}

int deleteAppointment(struct nodeForBST *root[], float time, int hkey)
{
    if (root[hkey] == null)
    {
        printf("No appointments found at entered hospital-key\n");
        return 0;
    }

    else
    {
        // go to key
        struct nodeForBST *par = null;
        struct nodeForBST *cur = root[hkey];
        while (cur != null && cur->patDetail.time != time)
        {
            par = cur;
            if (time < cur->patDetail.time)
            {
                cur = cur->left;
            }
            if (time > cur->patDetail.time)
            {
                cur = cur->right;
            }
        }
        if (cur == null) // condition for the time not available
            return 0;

        // case 1: for branch
        if (cur->left == null && cur->right == null)
        {
            if (cur == root[hkey])
                root[hkey] = null;
            else if (cur == par->left)
                par->left = null;
            else if (cur == par->right)
                par->right = null;
            free(cur);
            return 1;
        }

        // case 2: for half node
        if ((cur->left == null && cur->right != null) || (cur->left != null && cur->right == null))
        {
            if (cur == root[hkey])
            {
                if (cur->left != null)
                {
                    root[hkey] = cur->left;
                }
                else if (cur->right != null)
                {
                    root[hkey] = cur->right;
                }
            }
            else if (cur == par->left)
            {
                if (cur->left != null)
                {
                    par->left = cur->left;
                }
                else if (cur->right != null)
                {
                    par->left = cur->right;
                }
            }
            else if (cur == par->right)
            {
                if (cur->left != null)
                {
                    par->right = cur->left;
                }
                else if (cur->right != null)
                {
                    par->right = cur->right;
                }
            }
            free(cur);
            return 1;
        }

        // case 3: for both node
        if (cur->left != null && cur->right != null)
        {
            struct nodeForBST *temp = null;
            struct nodeForBST *in = cur;
            in = cur->right;
            while (in->left != null)
            {
                temp = in;
                in = in->left;
            }
            if (temp != null)
            {
                temp->left = in->right;
            }
            in->right = cur->left;

            if (cur->right != in)
                in->right = cur->left;

            if (cur == root[hkey])
                *root = in;

            else if (cur == par->left)
                par->left = in;

            else if (cur == par->right)
                par->right = in;

            free(cur);
            return 1;
        }
    }
}

void displayAppointments(struct nodeForBST *root)
{
    if (root == null)
    {
        return;
    }
    displayAppointments(root->left);
    printf("Name=%s Time=%0.2f ,", root->patDetail.name, root->patDetail.time);
    displayAppointments(root->right);
}
//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------

void detailsabouthospital(struct hashHospital *hH, struct hashTable *hP)
{
    printf("\n");
    int ch, src, v, tix, tiy; // temporpary int x
    float tfx, tfy, tfz;
    int tot_Places = hP->noofhkeys;
    printf("Total places=%d\n", tot_Places);
    v = tot_Places;
    printf("So the vertices for graph will be %d\n", v);
    int tot_Hospital = hH->noofhkeys;
    int distancearray[100];
    struct nodeH *graph[100] = {NULL};
    struct nodeForBST *root[tot_Hospital];
    int hospitalBedCheck[hH->noofhkeys];
    int grapharray[50] = {null};

    do
    {
        printf("1--sort the hospital based on rank\n");
        printf("2--edit graph hospital\n");
        printf("3--Hospital near me\n");
        printf("4--Get me shortest route connecting all hospitals\n");
        printf("5--Show details of all government hospital in city\n");
        printf("6--Show private hospital in the city\n");
        printf("7--Book appointment\n");
        printf("8--Get total available bed accordance to the hospital\n");

        printf("Enter the choise\n");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            sorthospital(hH, hP);
            printf("\n");
            break;

        case 2:
            editgraph(graph, v, grapharray);
            for (int i = 0; i < v; i++)
            {
                printf("%d ", grapharray[i]);
            }
            printf("\n");
            printf("\n");
            break;

        case 3:
            printf("Enter source:");
            scanf("%d", &src);
            dijkstra(graph, v, src, distancearray);
            for (int i = 0; i < v; i++)
            {
                printf("%d ", grapharray[i]);
            }
            printf("\n");
            printf("\n");
            break;

        case 4:
            printf("Enter source:");
            scanf("%d", &src);
            primshosp(graph, v, src);
            for (int i = 0; i < v; i++)
            {
                printf("%d ", grapharray[i]);
            }
            printf("\n");
            printf("\n");
            break;

        case 5:
            showGovernmentHospital(hH, tot_Places);
            printf("\n");
            break;

        case 6:
            showPrivateHospital(hH, tot_Places);
            printf("\n");
            break;

        case 7:
            initroot(root, tot_Hospital);
            int select;
            do
            {
                printf("0--Main menu\n");
                printf("1--Add appointment\n");
                printf("2--Remove appointment\n");
                printf("3--Display appointment list of the hospital in sorted manner\n");
                printf("Enter your choise\n");

                scanf("%d", &select);
                switch (select)
                {
                case 1:
                    printf("Enter Name, hospital-key, place-key, timing details\n");
                    struct appointment temp;
                    scanf("%s%d%d%f", temp.name, &temp.hospitalKey, &temp.placekey, &temp.time);
                    tix = searchHospital(hH, temp.placekey, temp.hospitalKey);
                    if (tix == 1)
                    {
                        tiy = addAppointment(root, &temp);
                        if (tiy == 1)
                            printf("You appointment is successfully allocted. Thankyou\n");
                        else
                            printf("Time clash. Plz try again\n");
                    }
                    else
                    {
                        printf("The hospital-key entered not found\n");
                    }
                    printf("\n");
                    break;

                case 2:
                    printf("Enter you appointment timing and hospital-key and place-key\n");
                    scanf("%f%d%d", &tfx, &tix, &tiy);
                    int a = searchHospital(hH, tiy, tix);
                    if (a == 1)
                    {
                        printf("Hospital found\n");
                        tiy = deleteAppointment(root, tfx, tix);
                        if (tiy == 1)
                        {
                            printf("Your appointment removed\n");
                        }
                        else
                        {
                            printf("Your appointment failed to be removed due to error in timings\n");
                        }
                        printf("\n");
                        break;
                    }
                    else
                    {
                        printf("Hospital not found\n");
                        printf("\n");
                        break;
                    }

                case 3:
                    printf("Enter the hospital-key\n");
                    scanf("%d", &tix);
                    displayAppointments(root[tix]);
                    printf("\n");
                    printf("\n");
                    break;
                }
            } while (select != 0);

            break;

        case 8:
            getTotAvailableBed(hH, hospitalBedCheck, tot_Places);
            displayHospitalBedCheck(hH, hospitalBedCheck);
            printf("\n");
            break;
        }

    } while (ch != 0);
}

// END OF HOSPITALS FUNCTIONALITY
//=============================================================================================================================================
//=============================================================================================================================================
// START OF HOTEL FOR STORING INTO THE RAM
struct hotelDetails
{
    char hotelName[20];
    int hotelKey;
    int nearPlace;
    int rating;
    int totalRooms;
    int occupiedRooms;
};

struct nodeHotel
{
    struct hotelDetails hotel;
    struct nodeHotel *linkf;
};

struct hashHotel
{
    struct nodeHotel **head;
    int tableSize;
    int noOfKeys;
};

int hashHotel(struct hashHotel *h, int key)
{
    int idx = abs(key) % h->tableSize;
    return idx;
}

void init_HashHotel(struct hashHotel *h)
{
    int ts;
    printf("Enter approximate places where hotels are in the cities.\n");
    scanf("%d", &ts);
    printf("As you entered total approx hotels is = %d\n", ts);
    ts = nearprime(ts);
    printf("So the table size preferred to use for hash is %d\n", ts);
    h->tableSize = ts;
    h->noOfKeys = 0;
    h->head = (struct nodeHotel **)malloc(h->tableSize * sizeof(struct nodeHotel *));
    for (int i = 0; i < h->tableSize; i++)
    {
        h->head[i] = null;
    }
}

void addHotel(struct hashHotel *h, int placeKey, char hotelName[], int hotelKey, int hotelRating, int totalRooms, int occupiedRooms)
{
    int idx = hashHotel(h, placeKey);
    struct nodeHotel *p;
    p = (struct nodeHotel *)malloc(sizeof(struct nodeHotel));
    strcpy(p->hotel.hotelName, hotelName);
    p->hotel.nearPlace = placeKey;
    p->hotel.hotelKey = hotelKey;
    p->hotel.rating = hotelRating;
    p->hotel.totalRooms = totalRooms;
    p->hotel.occupiedRooms = occupiedRooms;
    p->linkf = null;

    if (h->head[idx] == null)
    {
        h->head[idx] = p;
    }
    else
    {
        struct nodeHotel *start = h->head[idx];
        while (start->linkf != null)
        {
            start = start->linkf;
        }
        start->linkf = p;
    }
    h->noOfKeys++;
}

int deleteHotel(struct hashHotel *h, int key, int hotelKey)
{
    int idx = hashHotel(h, key);
    struct nodeHotel *curr, *prev;
    curr = h->head[idx];
    prev = null;
    while (curr != null && curr->hotel.hotelKey != hotelKey)
    {
        prev = curr;
        curr = curr->linkf;
    }
    if (curr == null)
    {
        return 0;
    }
    else if (curr == h->head[idx])
    {
        h->head[idx] = curr->linkf;
        printf("Hotel deleted=%s | Place-key=%d | Hotel-key=%d\n", curr->hotel.hotelName, curr->hotel.nearPlace, curr->hotel.hotelKey);
        free(curr);
        h->noOfKeys--;
        return 1;
    }
    else
    {
        prev->linkf = curr->linkf;
        printf("Hotel deleted=%s | Place-key=%d | Hotel-key=%d\n", curr->hotel.hotelName, curr->hotel.nearPlace, curr->hotel.hotelKey);
        free(curr);
        h->noOfKeys--;
        return 1;
    }
    return 0;
}

void deleteTotHotel(struct hashHotel *h)
{
    for (int i = 0; i < h->tableSize; i++)
    {
        struct nodeHotel *curr = h->head[i];
        while (curr != null)
        {
            h->head[i] = curr->linkf;
            free(curr);
            curr = h->head[i];
        }
    }
    h->noOfKeys = 0;
}

void displayHotel(struct hashHotel *h)
{
    for (int i = 0; i < h->tableSize; i++)
    {
        struct nodeHotel *start = h->head[i];
        while (start != null)
        {
            printf("Hotel name=%s | Place-key=%d | Hotel-key=%d | Rating=%d | Total-rooms=%d | Occupied-rooms=%d\n",
                   start->hotel.hotelName, start->hotel.nearPlace, start->hotel.hotelKey, start->hotel.rating,
                   start->hotel.totalRooms, start->hotel.occupiedRooms);
            start = start->linkf;
        }
        printf("\n");
    }
}

int searchHotel(struct hashHotel *h, int placeKey, int hotelKey)
{
    int idx = hashHotel(h, placeKey);
    if (h->head[idx] == null)
    {
        return 0;
    }
    else
    {
        struct nodeHotel *start = h->head[idx];
        while (start != null)
        {
            if (start->hotel.hotelKey == hotelKey)
            {
                printf("Hotel=%s\n", start->hotel.hotelName);
                return 1;
            }
            start = start->linkf;
        }
        return 0;
    }
}

void editHotel(struct hashHotel *h, struct hashTable *hP)
{

    void addHotel(struct hashHotel * h, int placeKey, char hotelName[], int hotelKey, int hotelRating, int totalRooms, int occupiedRooms);
    int deleteHotel(struct hashHotel * h, int place_key, int hotkey);
    void deleteTotHotel(struct hashHotel * h);
    void displayHotel(struct hashHotel * h);
    int searchHotel(struct hashHotel * h, int placeKey, int hotelKey);
    FILE *file;

    int ch, key, ans;
    do
    {
        printf("0--Back to main menu\n");
        printf("1--add hotel\n");
        printf("2--delete hotel\n");
        printf("3--Search hotel\n");
        printf("4--delete fullcity hotel\n");
        printf("5--Display fullcity hotel\n");
        printf("Enter choise\n");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Starting add\n");
            FILE *file;
            int placeKey, hotelKey, rating, totalRooms, occupiedRooms;
            char hotelName[20];

            file = fopen("Hotel.txt", "r");
            if (file == null)
            {
                fprintf(stderr, "Error in opening the Hotels file\n");
                break;
            }

            while (fscanf(file, "%d %s %d %d %d %d", &placeKey, hotelName, &hotelKey, &rating, &totalRooms, &occupiedRooms) == 6)
            {
                printf("Test -- Initialized\n");
                ans = searchkey(hP, placeKey);
                if (ans == 1)
                {
                    printf("Place exists\n");
                    printf("Test -- Success\n");
                    addHotel(h, placeKey, hotelName, hotelKey, rating, totalRooms, occupiedRooms);
                }
                else
                {
                    printf("Test -- Failed, because place with place-key is not matching. So the hotel can't be added\n");
                }
            }

            fclose(file);
            printf("Add Hotels -- Successful\n");
            printf("\n");
            break;

        case 2:
            printf("Enter the place-key of hotel\n");
            scanf("%d", &key);
            int hkey;
            printf("Enter the hotel key\n");
            scanf("%d", &hkey);
            ans = deleteHotel(h, key, hkey);
            if (ans == 1)
            {
                printf("Place-key found and hotel deleated\n");
            }
            else
            {
                printf("Place-key or hotel key not found hotel not deleated\n");
            }
            printf("\n");
            break;

        case 3:
            printf("Enter place key\n");
            int tix, ans, tiy;
            scanf("%d", &tix);
            printf("Enter hotel key\n");
            scanf("%d", &tiy);

            ans = searchHotel(h, tix, tiy);
            if (ans == 1)
            {
                printf("The hospital-key found\n");
            }
            else
            {
                printf("The hospital-key not found\n");
            }
            printf("\n");
            break;

        case 4:
            deleteTotHotel(h);
            printf("Deleated\n");
            printf("\n");
            break;

        case 5:
            displayHotel(h);
            printf("\n");
            break;

        case 6:
            deleteTotHotel(h);
            exit(0);
            printf("\n");
            break;
        }

    } while (ch != 0);
}
//***********************************************************************Rahuls Code**********************************************************************************************************

//------------------------main function---------------------------------
//*Hotel Structure for details*************

typedef struct HotelInfo
{
    int key;
    char HotelName[40];
    char Address[50];
    int RoomPrice[2]; // Single and double room prices
    float Rating;
    char Description[150]; // Short description about the hotel
} Hotel;

typedef struct customerinfo
{
    char Name[40];
    int RoomPrice[2]; // Single and double room prices
    long long int mobile;
    char Description[150]; // Short description about the hotel
} customer;

typedef struct Graph
{
    int matrix2[totalhotels][totalhotels];

}Graph;

Graph *CreateMatrix2Graph1()
{
    Graph *Temp3;
    Temp3 = (Graph *)malloc(sizeof(Graph));
    for (int i = 0; i < totalhotels; i++)
    {
        for (int j = 0; j < totalhotels; j++)
        {
            Temp3->matrix2[i][j] = -1;
        }
    }
    return Temp3;
}
//-------------------------BFS-----------------------------
typedef struct queue1
{
    int array[totalhotels];
    int front;
    int rear;
} queue1;

int isFull1(queue1 *q)
{
    if (q->front == totalhotels - 1)
    return 1;
    return 0;
}

int isEmpty1(queue1 *q)
{
    if (q->rear > q->front)
        return 1;
    return 0;
}

void enqueue1(queue1 *q, int data)
{
    if (isFull1(q))
    {
        printf("Queue is full.\n");
        return;
    }
    q->front++;
    q->array[q->front] = data;
    return;
}

int dequeue1(queue1 *q)
{
    if (isEmpty1(q))
    {
        printf("Queue is Empty.\n");
        return -1;
    }
    int n;
    n = q->array[q->rear];
    q->rear++;
    return n;
}
void DisplayPlaces1(Hotel *hotels)
{
        printf("-----------------------------------------------------------------------------------------\n");
        printf("Name :%s \nAdress : %s \nroom price : %d \nRating : %0.1f\nDiscription : %s\n", hotels->HotelName, hotels->Address, hotels->RoomPrice[0], hotels->Rating, hotels->Description);
        printf("-----------------------------------------------------------------------------------------\n");
    
    return;
}

void BFS1(Graph *Map1, Hotel array[],int SourceIndex)
{
    queue1 q;
    q.front = -1;
    q.rear = 0;
    int currentNode;
    int Visited[totalhotels];

    for (int i = 0; i < totalhotels; i++)
        Visited[i] = 0;

    Visited[SourceIndex] = 1;

    enqueue1(&q, SourceIndex);
    while (!isEmpty1(&q))
    {

        currentNode = dequeue1(&q);

       DisplayPlaces1(&array[currentNode]);

        for (int i = 0; i < totalhotels; i++)
        {   
            if (Map1->matrix2[currentNode][i] != -1 && !Visited[i])
            {
                enqueue1(&q, i);
                Visited[i] = 1;
            }
        }
       
        printf("\n");
    }
    return;
}

void display1(Hotel hotels[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("-----------------------------------------------------------------------------------------\n");
        printf("hotel No :%d\n",i+1);
        printf("Name :%s \nAdress : %s \nroom price : %d \nRating : %0.1f\nDiscription : %s\n", hotels[i].HotelName, hotels[i].Address, hotels[i].RoomPrice[0], hotels[i].Rating, hotels[i].Description);
        printf("-----------------------------------------------------------------------------------------\n");
    }
    return;
}

void display2(Hotel hotels[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("---------------------------------------------------------------------------\n");
        printf("hotel No :%d\n",i+1);
        printf("Name : %s \nRating : %0.1f \n", hotels[i].HotelName,hotels[i].Rating);
        printf("-----------------------------------------------------------------------------\n");
    }
    return;
}
//------------------------------------------------------------------------------
//*Read Hotel details********************************
void readHotelInfo1(Hotel *hotel)
{
    printf("Enter details for the Hotel:\n");

    printf("Hotel Name: ");
    fflush(stdin);
    gets(hotel->HotelName);
    int i = 0;
    while (hotel->HotelName[i] != '\0')
    {
        hotel->HotelName[i] = tolower(hotel->HotelName[i]);
        i++;
    }

    printf("Address: ");
    fflush(stdin);

    gets(hotel->Address);

    printf("Room Prices (for Single and Double rooms, separated by space): ");
    scanf("%d %d", &hotel->RoomPrice[0], &hotel->RoomPrice[1]);

    printf("Rating: ");
    scanf("%f", &hotel->Rating);

    printf("Description: ");
    fflush(stdin);

    gets(hotel->Description);

    return;

}



void insertionSort1(Hotel hotels[], int n)
{


    int i, j;
    Hotel key;
    for (i = 1; i < n; i++)
    {

        key = hotels[i];
        j = i - 1;

        // Move hotels that have higher rating than key to one position ahead

        while (j >= 0 && hotels[j].Rating < key.Rating)
        {

            hotels[j + 1] = hotels[j];
            j = j - 1;
            
        }

        hotels[j + 1] = key;
    }
}

void selectionSort1(Hotel hotels[], int n)
{

    int i, j, minIndex;

    Hotel temp3;

    for (i = 0; i < n - 1; i++)
    {

        minIndex = i;

        for (j = i + 1; j < n; j++)
        {

            // Compare based on the price of a single bed room

            if (hotels[j].RoomPrice[0] < hotels[minIndex].RoomPrice[0])
                minIndex = j;
                
        }
        // Swap hotels[i] with the minimum element

        temp3 = hotels[i];
        hotels[i] = hotels[minIndex];
        hotels[minIndex] = temp3;

    }
}

int leastweightind1(int distance[totalhotels], int visited[totalhotels])
{
    int min = _INT_MAX_;
    int min_index;
    for (int i = 0; i < totalhotels; i++)
    {
        if (distance[i] <= min && visited[i] == 0)
        {
            min = distance[i], min_index = i;
        }
    }
    return min_index;
}


void Dijkstra1(Graph *Map1, Hotel array[], int sourceIndex,int p)
{

    // arrays needed to stored while travelling from one hotel to other

    int distance[totalhotels];
    int visited[totalhotels];

    for (int i = 0; i < totalhotels; i++)
    {
        distance[i] = _INT_MAX_;

        visited[i] = 0;
    }
    
    //making the distance of the input hotel as zero

    distance[sourceIndex] = 0;

    for (int count = 0; count < totalhotels - 1; count++)
    {
        int u = leastweightind1(distance, visited);
        visited[u] = 1;

        for (int v = 0; v < totalhotels; v++)
        {
            if (!visited[v] && Map1->matrix2[u][v] != -1 && distance[u] != _INT_MAX_ &&
                distance[u] + Map1->matrix2[u][v] < distance[v])
            {

                distance[v] = distance[u] + Map1->matrix2[u][v];
            }
        }
    }

    // Print the distances or process the results as needed

    printf("\n\nDistances from hotel %s to other hotels:\n", array[sourceIndex].HotelName);

    for (int i = 0; i < 5; i++)
    {
        if(distance[i]!=0)
        {
           printf("To hotel %s: %d mtrs \n", array[i].HotelName, distance[i]);
        }
        

    }
}

// //**********************************************************************Main Code*************************************************************************************************************

int main()
{ // EDIT YOUR CODE//
    int FirstChoice;

    //-------------------------------Manoj Railway--------------------------------------------------------
    int i;
    char ch; // Temparory charectors
    int Choice;
    TrainDetailsForSystem *TrainList = NULL;
    Ticket *PassengersList = NULL;
    Ticket *NewPassenger;
    char Source[20];
    char Destination[20];
    int TicketNoForDeletion;
    TrainDetailsForSystem *temp2 = NULL;
    Queue WaitingList[MaxQueue];
    SkipList *Sklist;
    int AvailableTrains = 10;
    char classstr[5];
    int TrainNumberforChecking;
    int inter_result;
    int Result;
    int resultofseatchecking;
    Ticket *tic;
    int Choice_for_Booking;
    int result3;

    struct hashTable hP;
    init(&hP);
    struct hashHospital hH;
    init_hashHospital(&hH);
    struct hashHotel hHot;
    init_HashHotel(&hHot);

    //-----------------------------Manoj  Railway End------------------------------------------------------

    //------------------------File Railway handling Manoj-------------------------------------------------------
    FILE *fptr;
    fptr = fopen("Trains.txt", "rb");

    //------------------------Always the file ptr comes at start------------------------------------------------
    rewind(fptr);
    TrainDetailsForSystem r;

    rewind(fptr);
    for (int i = 0; i < AvailableTrains; i++)
    {
        fread(&r, sizeof(r), 1, fptr);
        temp2 = CreatingTrainNode();
        //-------------------------Temperory copying of Data from extracted structure to temperory structure---------
        strcpy(temp2->TrainName, r.TrainName);
        temp2->TrainNo = r.TrainNo;
        temp2->Time.Hour = r.Time.Hour;
        temp2->Time.Minutes = r.Time.Minutes;
        strcpy(temp2->Source, r.Source);
        strcpy(temp2->Destination, r.Destination);
        for (int i = 0; i < 5; i++)
        {
            temp2->price[i] = r.price[i];
            temp2->seats[i] = r.seats[i];
        }
        for (int i = 0; i < 4; i++)
        {
            temp2->seats[i] = r.seats[i];
            temp2->seatsLeft[i] = temp2->seats[i];
        }
        //-----------------------------------------End of temperory copy operation ------------------------------------------------------------------------
        TrainList = InsertionNewTrain(TrainList, temp2);
        // Invoking fuction to create List
    }
    fclose(fptr);

    assigningstructurequeue(TrainList, WaitingList);
    Sklist = Linking(TrainList);
    //---------------------------------------------End File railay Handling Manoj------------------------------

    //-----------------------------------------------Manoj Tourist Spot------------------------------------------

    int availablePlaces = 10;
    TouristPlace Place[availablePlaces];
    TouristPlace t;
    MatrixGraph *Map;
    int choice;
    int LocationKeyDickstras;
    FILE *fptr2;
    fptr2 = fopen("touristPlaces.txt", "rb");

    rewind(fptr2);
    for (int i = 0; i < availablePlaces; i++)
    {
        fread(&t, sizeof(t), 1, fptr2);
        Place[i].key = t.key;
        strcpy(Place[i].PlaceName, t.PlaceName);
        strcpy(Place[i].Address, t.Address);
        strcpy(Place[i].Description, t.Description);
        Place[i].EntryPrice[0] = t.EntryPrice[0];
        Place[i].EntryPrice[1] = t.EntryPrice[1];
        Place[i].Rating = t.Rating;
    }
    fclose(fptr);

    Map = CreateMatrixGraph();

    int matrix[MaxPlace][MaxPlace] = {{0, 150, 0, 200, 0, 0, 200, 0, 0, 200},
                                      {150, 0, 200, 0, 0, 300, 0, 0, 0, 0},
                                      {0, 200, 0, 200, 0, 0, 0, 0, 0, 0},
                                      {0, 0, 200, 0, 600, 0, 0, 0, 0, 0},
                                      {0, 0, 0, 600, 0, 250, 0, 800, 0, 0},
                                      {0, 300, 0, 0, 250, 0, 200, 170, 0, 0},
                                      {200, 0, 0, 0, 0, 200, 0, 0, 300, 0},
                                      {0, 0, 0, 0, 0, 300, 0, 0, 400, 0},
                                      {0, 0, 0, 0, 0, 0, 300, 400, 0, 300},
                                      {200, 0, 700, 0, 0, 0, 0, 0, 0, 300, 0}};

    for (int i = 0; i < availablePlaces; i++)
    {
        for (int j = 0; j < availablePlaces; j++)
        {
            if (matrix[i][j] != 0)
                Map->matrix[i][j] = matrix[i][j];
        }
    }

//*************************************Rahuls Basic******************************************************************************
Hotel temp3, read;
    int p = 5;
    Hotel hotels[p];
    FILE *fptr3;

    fptr3 = fopen("file.txt", "rb");

    for (int i = 0; i < p; i++)
    {

        fread(&temp3, sizeof(temp3), 1, fptr3);
        strcpy(hotels[i].HotelName, temp3.HotelName);
        strcpy(hotels[i].Address, temp3.Address);
        strcpy(hotels[i].Description, temp3.Description);
        hotels[i].RoomPrice[0] = temp3.RoomPrice[0];
        hotels[i].RoomPrice[1] = temp3.RoomPrice[1];
        hotels[i].Rating = temp3.Rating;
    }

    fclose(fptr2);
    Graph *Map1;
    Map1 = CreateMatrix2Graph1();

 int   matrix2[totalhotels][totalhotels] = 
                                   {{0, 80,0,0,70},
                                    {80,0,40, 90,110},
                                    {0, 40,0,45,0},
                                    {0,90,45, 0,60},
                                    {70, 110,0,45,0}};


    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < p; j++)
        {   if(matrix2[i][j]!=0)
                 Map1->matrix2[i][j] = matrix2[i][j];
        }
    }


    int k, sourceIndex;
    //*******************************************************End of Rahuls************************************
    //---------------------------------------------------Manoj Tourist Spot Ends---------------------------------
    while (1)
    {
        printf("========================================================================================================\n");
        printf("Enter:\n");
        printf("1)Search and Book Train                                              2)Nearby Tourist Places   \n");
        printf("3)Hospitals                                                          4)Search about hotels     \n");
        printf("5)Exit  from Program                                                                           \n");
        printf("========================================================================================================\n");
        printf("Enter Here...:");
        scanf("%d", &FirstChoice);

        switch (FirstChoice)
        {
        case 1:
        {
            //*********************************Main Services for a customers*********************************

            while (1)
            {
                printf("1-For Searching Train,2-Ticket Cancellation , others for Exit:");
                scanf("%d", &Choice);
                switch (Choice)
                {
                case 1: // For Searching Train
                {
                    printf("Enter Source:");
                    fflush(stdin);
                    fgets(Source, sizeof(Source), stdin);
                    i = 0;
                    while (Source[i] != '\0')
                    {
                        ch = Source[i];
                        ch = toupper(ch);
                        Source[i] = ch;
                        i++;
                    }

                    printf("Enter Destination:");
                    fflush(stdin);

                    fgets(Destination, sizeof(Destination), stdin);
                    i = 0;
                    while (Destination[i] != '\0')
                    {
                        ch = Destination[i];
                        ch = toupper(ch);
                        Destination[i] = ch;
                        i++;
                    }

                    Result = SearchTrain(TrainList, Source, Destination);
                    if (Result)
                    {
                        printf("1 to availability of seats,2 for back:\n");
                        scanf("%d", &inter_result);
                        if (inter_result == 1)
                        {
                            printf("Enter the Train number of Selcted train:");
                            scanf("%d", &TrainNumberforChecking);
                            printf("The class of choice:");
                            scanf("%s", classstr);
                            i = 0;
                            while (classstr[i] != '\0')
                            {
                                ch = classstr[i];
                                ch = toupper(ch);
                                classstr[i] = ch;
                                i++;
                            }

                            resultofseatchecking = CheckAvailabilityoofTicket(TrainList, TrainNumberforChecking, classstr, Sklist);
                            // to book,or waiting list or exit
                            if (resultofseatchecking == 2)
                            {
                                printf("Seats are available.\n");

                                printf("Enter 1 for Booking,2-for exit");
                                scanf("%d", &Choice_for_Booking);
                                if (Choice_for_Booking == 1)
                                {
                                    NewPassenger = GetDetails(TrainList, TrainNumberforChecking, classstr, Sklist);
                                    PassengersList = PassengerDetailInsertion(PassengersList, NewPassenger);
                                    printf("THANK YOU\n");
                                    printf("\tTICKET BOOKED\n");
                                    PrintTrainTicket(NewPassenger);
                                }
                                else
                                {
                                    printf("Thank YOU.\n");
                                }
                            }
                            else if (resultofseatchecking == 1)
                            {
                                // waiting list
                                tic = GetDetailsforWaitingList(TrainList, TrainNumberforChecking, classstr, Sklist);
                                result3 = enqueuePassenger(WaitingList, tic);
                                if (result3 == 1)
                                {
                                    printf("You are added in Waiting List.\n");
                                    printf("Thank You");
                                }
                                else
                                {
                                    printf("Waiting List is FULL.\n");
                                    printf("Thank you.\n");
                                }
                            }
                            else
                            {
                                printf("Thank You.\n");
                            }
                        }
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        printf("\tSorry! Currently No Routes are Available on this Route.\n");
                    }
                    break;
                }

                case 2: // Ticket Cancellation
                {
                    printf("Enter Ticket No:");
                    scanf("%d", &TicketNoForDeletion, WaitingList);
                    PassengersList = BookedTicketDeletion(PassengersList, TicketNoForDeletion, WaitingList);
                    break;
                }
                case 3:
                    break;
                default:
                    break;
                }
                if (Choice == 3)
                    break;
            }
            break;
        }
        case 2:
        {

            while (1)
            {
                printf("========================================================================================================\n");
                printf("Enter:\n");
                printf("1)to view All tourist Places              2)to Search Nearest Tourist Places From Your Location\n");
                printf("3)Arranging Based on Price                4)Sorting Based on Rating                            \n");
                printf("5)Exit                                                                                         \n");
                printf("========================================================================================================\n");
                printf("Enter  here..:");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    BFS(Map, Place, 0);

                    break;
                case 2:
                    printf("Enter your Location:");
                    scanf("%d", &LocationKeyDickstras);
                    DikstrasAlgorithm(Map, Place, availablePlaces, LocationKeyDickstras);
                    break;
                case 3:
                    // Sorting Based Price
                    InsertionSorting(Place, availablePlaces);
                    break;
                case 4:
                    // Sorting Based Rating
                    SelectionSorting(Place, availablePlaces);
                    break;
                default:
                    break;
                }

                if (choice != 1 || choice != 2 || choice != 3 || choice != 4)
                    break;
            }
            break;
        }
        break;

        case 3:
        {
            printf("\n");
            int tich;
            do
            {
                printf("Enter the choise\n");
                printf("0--Back to main menu\n");
                printf("1--Edit places\n");
                printf("2--Edit hospitals\n");
                printf("3--Details about hospitals\n");
                printf("4--Details on hotels\n");
                printf("Enter the choise\n");
                scanf("%d", &tich);

                switch (tich)
                {
                case 1:
                    editplaces(&hP);
                    break;

                case 2:
                    edithospital(&hH, &hP);
                    break;

                case 3:
                    detailsabouthospital(&hH, &hP);
                    break;

                case 4:
                    editHotel(&hHot, &hP);
                    break;
                }
            } while (tich != 0);

            break;
        }
        case 4:
        {
 while (1)
    {
        printf("\n\nSelect any one value from given below :\n\n1 :To display hotels        2 :To sort by ratings  \n3 :To sort hotels by price  4 :To find nearest one \n5 :To Exit\n");
        scanf("%d", &k);
        switch (k)
        {
        case 1:
            BFS1(Map1,hotels,0);
            break;
        
        case 2:
                  insertionSort1(hotels, p);
                 printf("Hotels sorted based on rating:\n");
                 display2(hotels, p);

                 int m, n,f,age;
                 long long int adhar, mobile;
                 char name[20];

                  printf("Enter 1 to book a room and 0 to exit: ");
                  scanf("%d", &m);

                  if (m == 1)
                  {
                      printf("Enter the hotel number to book the room: ");
                      scanf("%d", &n);

                      if(n>p)
                     {
                        printf("\n\nInvalid hotel no ");
                        break;
                     }
                     
                        f=n-1;
                      printf("\nEnter your name to book a room: ");
                      scanf("%s", name);

                       printf("\nEnter your age :");
                      scanf("%d",&age);

                      printf("\nEnter your mobile no: ");
                      scanf("%lld", &mobile);

                      printf("\nEnter your Aadhar no: ");
                      scanf("%lld", &adhar);

                      printf("\n\nTHANK YOU! YOUR ROOM BOOKING IS SUCCESSFUL IN: %s\n\n ", hotels[f].HotelName);
                  }
                 else
                  {
                    break;
                  }
               break;

        case 3:
             selectionSort1(hotels, p);
             printf("Hotels sorted based on the price  room:\n");
             display1(hotels, p);
             printf("Enter 1 to book a room and 0 to exit: ");
                  scanf("%d", &m);

                  if (m == 1)
                  {
                      printf("Enter the hotel number to book the room: ");
                      scanf("%d", &n);

                     if(n>p)
                     {
                        printf("\n\nInvalid hotel NO ");
                        break;
                     }
                      
                      f=n-1;

                      printf("\nEnter your name to book a room: ");
                      scanf("%s", name);
                      
                      printf("\nEnter your age :");
                      scanf("%d",&age);

                      printf("\nEnter your mobile no: ");
                      scanf("%lld", &mobile);

                      printf("\nEnter your Aadhar no: ");
                      scanf("%lld", &adhar);

                      printf("\n\nTHANK YOU! YOUR ROOM BOOKING IS SUCCESSFUL IN: %s hotel \n\n ", hotels[f].HotelName);
                  }
                 else
                  {
                    break;
                  }
             break;

        case 4: // Add this case in your main loop
                printf("Enter the index of the source hotel to find the nearest hotels: ");
                scanf("%d", &sourceIndex);
                Dijkstra1(Map1, hotels, sourceIndex,p);
                // int m, n;
                //  long long int adhar, mobile;
                //  char name[20];

                  printf("Enter 1 to book a room and 0 to exit: ");

                  scanf("%d", &m);

                  if (m == 1)
                  {
                      printf("Enter the hotel number to book the room: ");
                      scanf("%d", &n);
                       {

                      printf("\nEnter your name to book a room: ");
                      scanf("%s", name);

                       printf("\nEnter your age :");
                      scanf("%d",&age);

                      printf("\nEnter your mobile no: ");
                      scanf("%lld", &mobile);

                      printf("\nEnter your Aadhar no: ");
                      scanf("%lld", &adhar);

                      printf("\n\nTHANK YOU! YOUR ROOM BOOKING IS SUCCESSFUL IN: %s\n\n ", hotels[n].HotelName);
                       }
                  }
                 else
                  {

                    break;

                  }

                break;


        case 5: default:
               break;

            break;
        }
        if(k==5)
        {
            break;
        }
    }            
        }
        break;
        default:
            exit(0);
        }
    }
    return 0;
}
// End of Program1