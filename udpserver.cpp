#include <string>
#include <iostream>
#include "UDP.h"

UDP empfangen;
UDP senden;

long WINAPI empfangen1(void);
long WINAPI senden1(void);
using namespace std;

int main(void)
{
    /*UDP server = UDP();

    server.socketErzeugen();
    server.sockDef(50000);

    string antwort;

    server.empfangen(antwort);

    cout << antwort<<"\n";

    system("PAUSE");

    server.socketSchliesen();
    server.winsockfreigeben();*/




    empfangen.socketErzeugen();
    empfangen.sockDef(50000);

    senden.socketErzeugen();


    HANDLE hEmpfangen = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)empfangen1,0, 0, 0);
    HANDLE hSenden    = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)senden1,0, 0, 0);

    WaitForSingleObject(hEmpfangen, INFINITE);
    WaitForSingleObject(hSenden, INFINITE);

    CloseHandle(hSenden);
    CloseHandle(hEmpfangen);

    senden.socketSchliesen();
    senden.winsockfreigeben();
    empfangen.socketSchliesen();
    empfangen.winsockfreigeben();
    return 0;
}

long WINAPI empfangen1(void)
{
    string antwort;

    while(true)
    {
        empfangen.empfangen(antwort);
        cout << antwort;
    }
    return 0;
}
long WINAPI senden1(void)
{
    string nachricht = "gesendete nachricht \n";

    while(true)
    {
        senden.senden("localhost",nachricht,50001);
    }
    return 0;
}

