// Virtual Machine MM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>
using namespace std;
class VM
{
public:

    unsigned char regs[16];
    char prog_mem[256];
    int Rx;
    int Ry;
    int tmp;
    char hex2, raid;
    int x = 0;
    int n;
    int flag = 1;
    VM()
    {
       
    }
    void ACT(const char * file, string msg, string ats)
    {
        flag = 1;
        x =0;
        int zz = 0;
        int tmp = 0;
        FILE* pFile;
        ifstream in(msg);
        ofstream out(ats);
        pFile = fopen(file, "rb");
        if (pFile)
        {
            while ((hex2 = getc(pFile)) != EOF)
            {
                prog_mem[x] = hex2;
                x++;
            }
        }
        for (int i = 0; i < x; i++)
        {
            if (i % 2 == 0)
            {
                Rx = prog_mem[i+1] & 0x0F;
                Ry = prog_mem[i+1] >> 4;
                if (prog_mem[i] == 1)
                {
                    flag = 1;
                    regs[Rx]=INC(regs, Rx);

                }
                else if (prog_mem[i] == 2)
                {
                    flag = 1;
                    regs[Rx] = DEC(regs,Rx);
                }
                else if (prog_mem[i] == 3)
                {
                    flag = 1;
;                    regs[Rx] = MOV(regs,Rx,Ry);
                }
                else if (prog_mem[i] == 4)
                {
                    flag = 1;
                    regs[0] = MOVC(regs,prog_mem[i + 1]);
                }
                else if (prog_mem[i] == 5)
                {
                    flag = 1;
                    regs[Rx] = LSL(regs[Rx]);
                }
                else if (prog_mem[i] == 6)
                {
                    flag = 1;
                    regs[Rx] = LSR(regs[Rx]);
                    
                }
                else if (prog_mem[i] == 7)
                { 
                    i = JMP((int)prog_mem[i + 1], i)-2;
                }
                else if (prog_mem[i] == 8)
                {
                    i = JZ((int)prog_mem[i + 1], i, flag)-2;
                }
                else if (prog_mem[i] == 9)
                {
                    i = JNZ((int)prog_mem[i + 1], i, flag)-2;
                }
                else if (prog_mem[i] == 10)
                {
                    if (in.eof())
                    {
                        i = JFE((int)prog_mem[i + 1], i)-2;
                    }
                }
                else if (prog_mem[i] == 11)
                {
                    break;
                }
                else if (prog_mem[i] == 12)
                {
                    flag = 1;
                    regs[Rx] = ADD(regs, Rx, Ry);
                }
                else if (prog_mem[i] == 13)
                {
                    flag = 1;
                    regs[Rx] = SUB(regs, Rx, Ry);
                }
                else if (prog_mem[i] == 14)
                {
                    flag = 1;
                    regs[Rx] = XOR(regs, Rx, Ry);
                }
                else if (prog_mem[i] == 15)
                {
                    flag = 1;
                    regs[Rx] = OR(regs, Rx, Ry);
                }
                else if (prog_mem[i] == 16)
                {
                    if (!in.eof())
                    {
                        flag = 1;
                        in >> noskipws >> raid;
                        regs[Rx] = raid;
                    }
                    else if(in.eof())
                    {
                        flag = 0;
                        in.close();
                    }
                }
                else if (prog_mem[i] == 17)
                {
                  out << regs[Rx];
                }
            }
        }
        cout << "ATLIKTA!!!" << endl;
    }
    unsigned char INC(unsigned char regs[],int x)
    { 
        regs[x] = regs[x] + 1;
        return regs[x];
    }
    unsigned char DEC(unsigned char regs[],int x)
    {
        regs[x] = regs[x] - 1;
        return regs[x];
    }
    unsigned char MOV(unsigned char regs[], int x, int y)
    {
        regs[x] = regs[y];
        return regs[x];
    }
    unsigned char MOVC(unsigned char regs[],int x)
    {
        regs[0] = x;
        return regs[0];
    }
    int LSL(int Rx)
    {
        Rx = Rx << 1;
        return Rx;
    }
    int LSR(int Rx)
    {
        Rx = Rx >> 1;
        return Rx;
    }
    int JMP(int jmp, int h)
    {
        //h= 28 ir jmp = 230
        return jmp + h;
        return h;
    }
    int JZ(char jmp, int h, int flag)
    {
        
        if (flag == 0)
        {
            return jmp + h;
        }
        else
        {
            return h;
        }
    }
    int JNZ(char jmp, int h, int flag)
    {
        if (flag == 1)
        {
            return jmp + h;
        }
        else
        {
            return h;
        }
    }
    int JFE(char jmp, int h)
    {
        return jmp + h;
    }
    unsigned char ADD(unsigned char regs[], int Rx, int Ry)
    {
        regs[Rx] = regs[Rx] + regs[Ry];
        return regs[Rx];
    }
    unsigned char SUB(unsigned char regs[], int Rx, int Ry)
    {
        regs[Rx] = regs[Rx] - regs[Ry];
        return regs[Rx];
    }
    unsigned char XOR(unsigned char regs[], int Rx, int Ry)
    {
        regs[Rx] = regs[Rx] ^ regs[Ry];
        return regs[Rx];
    }
    unsigned char OR(unsigned char regs[], int Rx, int Ry)
    {
        regs[Rx] = regs[Rx] | regs[Ry];
        return regs[Rx];
    }
    bool MainMenu()
    {
        int choice;
        system("cls");
        cout << "Pasirinkite:" << endl;
        cout << "1) Atkoduoti pirma dali" << endl;
        cout << "2) Uzkoduoti antra dali" << endl;
        cout << "3) Atkoduoti antra dali" << endl;
        cout << "4) Exit" << endl;
        cin >> choice;
        switch (choice)
        {
            
        case 1:
            ACT("VM-Reiskinys.bin", "TekstinisFailas.txt", "ATS.txt");
            return true;
        case 2:
            ACT("encr2.bin", "zinute.txt", "zinute_encrypted.txt");
            return true;
        case 3:
            ACT("decr2.bin", "zinute_encrypted.txt", "zinute_decrypted.txt");
            return true;
        case 4:
            return false;
        default:
            return true;
        }
    }
    ~VM()
    {

    }
};
int main()
{
    VM obj;
    bool showMenu = true;
    while (showMenu)
    {
        showMenu = obj.MainMenu();
    }
    
    //obj.ACT("decryptor.bin", "q1_encr.txt","q1_encr_ats.txt");
    //obj.ACT("encryptor_2.txt", "zinute.txt", "zinute_ats.txt");
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
