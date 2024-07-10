#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void checkForSourceFile();

void createSourceFile();
int lengthOf(long int passCODE);
int encKeyFun(int tempEncKey1);
int sumDigit(int);

void getSourceDetails();

void login();
void logOut();

void menu();
void viewPasswords();
void addPassword();
void removePassword();
void modifyPassword();

void encryptWebstite(char input[50]);
void encryptUsername(char input[50]);
void encryptPassword(char input[50]);
void decryptWebstite(char input[50]);
void decryptUsername(char input[50]);
void decryptPassword(char input[50]);


FILE *sourceFile;
long int sourcePassCode, sourceEncKey;
char encwebsite[50],encusername[50],encpassword[50],decwebsite[50],decusername[50],decpassword[50];

void  main()
{
    printf("Welcome to your password manager!\n");
    checkForSourceFile();
    
}

void checkForSourceFile()
{
    sourceFile=fopen("sourcefile.txt","r");
    if(sourceFile==NULL)
    {
        createSourceFile();
    }
    else
    {
        getSourceDetails();
        login();
    }
}

void createSourceFile()
{
    long int passCode, tempPassC1,tempPassC2,EncPassCode,EncEncKey;
    int  EncKey;
    printf("\nSet a local passcode: ");
    scanf("%ld",&tempPassC1);
    if(lengthOf(tempPassC1)<=9)
    {
        printf("Confirm Passcode: ");
        scanf("%ld",&tempPassC2);
        if(tempPassC1==tempPassC2)
        {
            passCode=tempPassC1;
            system("cls");
            printf("Passcode Set Sucessfully!!\n\n");

            EncKey=encKeyFun(passCode);
            EncPassCode=passCode+(EncKey*100);
            EncEncKey=EncPassCode+EncKey;
            sourceFile=fopen("sourcefile.txt","w");
            fprintf(sourceFile,"%ld\n%d",EncPassCode,EncEncKey);
            fclose(sourceFile);
            getSourceDetails();
            login();
        }
        else
        {
            system("cls");
            printf("Passcode did not matched!!\n");
            createSourceFile();
        }
    }
    else
    {
        system("cls");
        printf("Passcode must be maximum 9 digits long");
        createSourceFile();
    }
}

int lengthOf(long int passCODE)
{
    int l=0;
    while(passCODE!=0)
    {
        passCODE/=10;
        l++;
    }
    return l;
}

int encKeyFun(int tempEncKey1)
{
    int tempEncKey2,EncKey=0;

    tempEncKey2=sumDigit(tempEncKey1);
    EncKey=sumDigit(tempEncKey2*tempEncKey2);
    return EncKey;
}

int sumDigit(int num)
{
    int sum=0;
    while(num!=0)
    {
        sum+=num%10;
        num/=10;
    }
    return sum;
}

void getSourceDetails()
{
    long int encSourcePasscode, encrySourceEncKey;
    sourceFile=fopen("sourceFile.txt","r");
    fscanf(sourceFile,"%ld\n%d",&encSourcePasscode,&encrySourceEncKey);
    fclose(sourceFile);
    sourceEncKey=encrySourceEncKey-encSourcePasscode;
    sourcePassCode=encSourcePasscode-(sourceEncKey*100);
}

void login()
{
    long int usrPassCode;
    printf("\nEnter Passcode: ");
    scanf("%ld",&usrPassCode);

    if(usrPassCode==sourcePassCode)
    {
        system("cls");
        printf("You're logged in successfully!!\n\n");
        menu();
    }
    else
    {
        system("cls");
        printf("Access Denied!!\n[Wrong Passcode]");
        login();
    }
}

void logOut()
{
    system("cls");
    printf("Welcome to your password manager!\n");
    login();
}

void menu()
{
    int option;
    printf("<<-Menu->>\n\n1]View Passwords\t2]Add Password\t3]Remove Password\t4]Modify Password\t5]Log Out\nEnter Option: ");
    scanf("%d",&option);
    switch(option)
    {
    case 1:
        viewPasswords();
        break;

    case 2:
        addPassword();
        break;

    case 3:
        removePassword();
        break;

    case 4:
        modifyPassword();
        break;

    case 5:
        logOut();
        break;

    default:
        printf("Invalid Option!\n\n");
        menu();
        break;
    }
}

void viewPasswords()
{
    system("cls");
    printf("<<-View Password->>\n");
    FILE *passWordFile;
    char website[50],username[50],password[50],fileName[50];


    printf("\nEnter Website/App Name: ");
    scanf("%s",website);
    for(int i=0; website[i]!='\0'; i++)
    {
        website[i]=toupper(website[i]);
    }
    encryptWebstite(website);
    strcpy(fileName,encwebsite);
    strcat(fileName,".txt");
    passWordFile=fopen(fileName,"r");
    if(passWordFile==NULL)
    {
        int opt;
        printf("\nPassword Record Don't Exist!\n\n1]Re-enter Website/App Name\t2]Go to Main Menu\nEnter Option: ");
        scanf("%d",&opt);
        switch(opt)
        {
        case 1:
            viewPasswords();
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
    else
    {
        fscanf(passWordFile,"%s\n%s\t%s",website,username,password);
        fclose(passWordFile);
        decryptWebstite(website);
        decryptUsername(username);
        decryptPassword(password);
        printf("\nWebsite/App: %s\nUsername: %s\nPassword: %s\n\n",decwebsite,decusername,decpassword);
        menu();
    }
}

void addPassword()
{
    system("cls");
    printf("<<-Add Password->>\n");
    FILE *passWordFile;
    char website[50],username[50],password[50],fileName[50];


    printf("\nEnter Website/App Name: ");
    scanf("%s",website);
    for(int i=0; website[i]!='\0'; i++)
    {
        website[i]=toupper(website[i]);
    }
    encryptWebstite(website);

    strcpy(fileName,encwebsite);
    strcat(fileName,".txt");

    passWordFile=fopen(fileName,"r");
    if(passWordFile==NULL)
    {
        printf("Enter Username: ");
        scanf("%s",username);

        printf("Enter Password: ");
        scanf("%s",password);

        encryptUsername(username);
        encryptPassword(password);

        passWordFile=fopen(fileName,"w");
        fprintf(passWordFile,"%s\n%s\t%s",encwebsite,encusername,encpassword);
        fclose(passWordFile);
        system("cls");
        printf("\nPassword Added Successfully!!\n\n");
        menu();
    }
    else
    {
        int opt;
        printf("\nPassword Record Already Exist!\n\n1]Re-enter Website/App Name\t2]Go to Main Menu\nEnter Option: ");
        scanf("%d",&opt);
        switch(opt)
        {
        case 1:
            addPassword();
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
}

void removePassword()
{
    system("cls");
    printf("<<-Remove Password->>\n");
    FILE *passWordFile;
    char website[50],username[50],password[50],fileName[50];
    printf("\nEnter Website/App Name: ");
    scanf("%s",website);
    for(int i=0; website[i]!='\0'; i++)
    {
        website[i]=toupper(website[i]);
    }
    encryptWebstite(website);
    strcpy(fileName,encwebsite);
    strcat(fileName,".txt");
    passWordFile=fopen(fileName,"r");
    if(passWordFile==NULL)
    {
        int opt;
        printf("\nPassword Record Don't Exist!\n\n1]Re-enter Website/App Name\t2]Go to Main Menu\nEnter Option: ");
        scanf("%d",&opt);
        switch(opt)
        {
        case 1:
            removePassword();
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
    else
    {
        fscanf(passWordFile,"%s\n%s\t%s",website,username,password);
        fclose(passWordFile);
        decryptWebstite(website);

        printf("\nWebsite/App: %s\nPassword Exist!!\nDo you want to Delete That?(Y/n): ",decwebsite);
        char temp;
        scanf(" %c",&temp);
        if(temp=='y' || temp=='Y')
        {
            if (remove(fileName) == 0)
            {
                printf("Password Deleted successfully\n\n");
                menu();
            }
            else
            {
                printf("Unable to delete the password\n\n");
                int opt;
                printf("1]Re-enter Website/App Name\t2]Go to Main Menu\nEnter Option: ");
                scanf("%d",&opt);
                switch(opt)
                {
                case 1:
                    removePassword();
                    break;
                default:
                    system("cls");
                    menu();
                    break;
                }
            }
        }
        else
        {
            printf("\nPassword not deleted!\n\n");
            int opt;
            printf("1]Re-enter Website/App Name\t2]Go to Main Menu\nEnter Option: ");
            scanf("%d",&opt);
            switch(opt)
            {
            case 1:
                removePassword();
                break;
            default:
                system("cls");
                menu();
                break;
            }
        }
    }
}

void modifyPassword()
{
    system("cls");
    printf("<<-Modify Password->>\n");
    FILE *passWordFile;
    char website[50],username[50],password[50],fileName[50];


    printf("\nEnter Website/App Name: ");
    scanf("%s",website);
    for(int i=0; website[i]!='\0'; i++)
    {
        website[i]=toupper(website[i]);
    }
    encryptWebstite(website);

    strcpy(fileName,encwebsite);
    strcat(fileName,".txt");

    passWordFile=fopen(fileName,"r");
    if(passWordFile!=NULL)
    {

        printf("Enter Username: ");
        scanf("%s",username);
        encryptUsername(username);

        printf("Enter New Password: ");
        scanf("%s",password);
        encryptPassword(password);

        fclose(passWordFile);

        passWordFile=fopen(fileName,"w");
        fprintf(passWordFile,"%s\n%s\t%s",encwebsite,encusername,encpassword);
        fclose(passWordFile);
        printf("\nPassword Modified Successfully!!\n\n");
        menu();
    }
    else
    {
        int opt;
        printf("\nPassword Record Don't Exist!\n\n1]Re-enter Website/App Name\t2]Go to Main Menu\nEnter Option: ");
        scanf("%d",&opt);
        switch(opt)
        {
        case 1:
            modifyPassword();
            break;
        default:
            system("cls");
            menu();
            break;
        }
    }
}

void encryptWebstite(char input[50])
{
    for(int i=0; encwebsite[i]!='\0'; i++)
    {
        encwebsite[i]='\0';
    }
    for(int i=0; input[i]!='\0'; i++)
    {
        encwebsite[i]=input[i]+sourceEncKey;
    }
}
void encryptUsername(char input[50])
{
    for(int i=0; encusername[i]!='\0'; i++)
    {
        encusername[i]='\0';
    }
    for(int i=0; input[i]!='\0'; i++)
    {
        encusername[i]=input[i]+sourceEncKey;
    }
}
void encryptPassword(char input[50])
{
    for(int i=0; encpassword[i]!='\0'; i++)
    {
        encpassword[i]='\0';
    }
    for(int i=0; input[i]!='\0'; i++)
    {
        encpassword[i]=input[i]+sourceEncKey;
    }
}
void decryptWebstite(char input[50])
{
    for(int i=0; decwebsite[i]!='\0'; i++)
    {
        decwebsite[i]='\0';
    }
    for(int i=0; input[i]!='\0'; i++)
    {
        decwebsite[i]=input[i]-sourceEncKey;
    }
}
void decryptUsername(char input[50])
{
    for(int i=0; decusername[i]!='\0'; i++)
    {
        decusername[i]='\0';
    }
    for(int i=0; input[i]!='\0'; i++)
    {
        decusername[i]=input[i]-sourceEncKey;
    }
}
void decryptPassword(char input[50])
{
    for(int i=0; decpassword[i]!='\0'; i++)
    {
        decpassword[i]='\0';
    }
    for(int i=0; input[i]!='\0'; i++)
    {
        decpassword[i]=input[i]-sourceEncKey;
    }
}
