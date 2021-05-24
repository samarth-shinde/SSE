#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#define sizea 10
    using namespace std;
void drawline();
char *file_name[50];
int file_no, i;
void creation()
{
    printf("How many file do u want to create ?");
    scanf("%d", &file_no);
    for (i = 0; i < file_no; i++)
    {
        char temp_input[50];
        file_name[i] = (char *)malloc(10 * sizeof(int));
        printf("File %d:", i);
        scanf("%s", &temp_input);
        ofstream file(temp_input);
        strcpy(file_name[i], temp_input);
        if (file == NULL)
            printf("Oops! File is unable to create");
        else
            printf("File is successfully created");
        file.close();
    }
}
void inserting()
{
    char sentence[1000];
    // creating file pointer to work with files
    FILE *fptr;
    char fname[10];
    // opening file in writing mode
    printf("Input file name do u want to insert it in?:");
    scanf("%s", &fname);
    fptr = fopen(fname, "w");

    // exiting program
    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    printf("Enter a sentence:\n");
    scanf("%s", sentence);
    fgets(sentence, sizeof(sentence), stdin);
    fprintf(fptr, "%s", sentence);
    fclose(fptr);
}
void search_data(int argc, char *argv[])
{
    FILE *fp;
    char temp[255];
    int line = 1, flag = 0, i;
    for (i = 1; i <= argc; i++)
    {
        fp = fopen(argv[i], "r");
        if (fp != NULL)
        {
            printf("\n\t File Scanned : '%s'", argv[i]);
            while (fgets(temp, 50, fp) != NULL)
            {
                if ((strstr(temp, argv[0])) != NULL)
                {
                    printf("\nSearch Result :\n");
                    printf(" \t'%s' found in %s\n", argv[0], argv[i]);
                    printf(" \t A match found on line:%d\n", line);
                    flag++;
                }
                line++;
                if (flag == 0)
                    printf("\nOops Your Word is Not found in '%s'\n", argv[i]);
            }
            fclose(fp);
        }
        else
        {
            printf("\n>> Failed to open file '%s'\n", argv[i]);
        }
    }
    printf("\nFinal Result :");
    if (flag == 0)
        printf("\n :( Could not find occurrence of '%s' in any files !\n", argv[0]);
    else
    {
        printf("\nThe word '%s' occurred %d Times \n", argv[0], flag);
    }
}

void data_searching()
{
    char *argv[10];
    int i, a, j;
    int argc = file_no;
    argv[0] = (char *)malloc(10 * sizeof(char));
    printf("Input word you want to search ?:");
    scanf("%s", argv[0]);
    for (i = 1; i <= file_no; i++)
    {
        argv[i] = (char *)malloc(10 * sizeof(char));
        argv[i] = file_name[i - 1];
    }
    search_data(argc, argv);
}
void list_dir(const char *path)
{
    struct dirent *entry;
    char file_list[50];

    DIR *dir = opendir(path);
    printf("Input the word u want to search ?:");
    scanf("%s", &file_list);
    FILE *fp;
    char temp[255];
    int line = 1, flag = 0, i;
    if (dir == NULL)
    {
        return;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        fp = fopen(entry->d_name, "r");
        if (fp != NULL)
        {
            printf("\n File Scanned :%s", entry->d_name);
            while (fgets(temp, 50, fp) != NULL)
            {
                if (strstr(temp, file_list) != NULL)
                {
                    printf("\n\t Search Result :\n");
                    printf(" \t'%s' found in %s\n", file_list, entry->d_name);
                    printf(" \t A match found on line:%d\n", line);
                    flag++;
                }
                line++;
            }
            fclose(fp);
        }
        else
        {
            printf("\n>> Failed to open file '%s'\n", entry->d_name);
        }
    }
    closedir(dir);
    printf("\nFinal Result :");
    if (flag == 0)
        printf("\n :( Could not find occurrence of '%s' in any files !\n", file_list);
    else
    {
        printf("\nThe word '%s' occurred %d Times n", file_list, flag);
    }
}
void serach_face()
{
    list_dir("C:\\TURBOC3\\BIN\\Data Structure\\File Handling\\Textfile");
}
void scan_dir(const char *path)
{
    struct dirent *entry;
    char file_list[50];
    char temp[100];
    int loc = 0;
    DIR *dir = opendir(path);
    FILE *fp;
    printf("Input the file do u want to scan ?:");
    scanf("%s", &file_list);
    if (dir == NULL)
    {
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(file_list, entry->d_name) == 0)
        {
            fp = fopen(entry->d_name, "r");
            while (fscanf(fp, "%s", temp) != EOF)
            {
                printf(" %s", temp);
            }
            fclose(fp);
        }
    }
    closedir(dir);
}
void file_scanning()
{
    scan_dir("C:\\TURBOC3\\BIN\\Data Structure\\File Handling\\Textfile");
}
int main_menu()
{
    char choice;
    int choice_main;
    do
    {
        cout << "Select Appropriate Option " << endl;
        cout << "\n\t [1] File Creation \n\t [2] Data Searching \n\t [3] File Scanning \n\t [4] File Editing \n\t [5] Search \n " << endl;
        cout << "Insert Choice:";
        cin >> choice_main;
        switch (choice_main)
        {
        case 1:
            creation();
            break;
        case 2:
            data_searching();
            break;
        case 3:
            file_scanning();
            break;
        case 4:
            inserting();
            break;
        case 5:
            serach_face();
            break;
        default:
            cout << "Please! Choose Appropriate Option";
            break;
        }
        fflush(stdin);
        cout << "\nDo you want to continue ?(y/n) :";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}
int main()
{
    system("COLOR 06");
    drawline();
    cout << "\n\n\n\n\t\t\t\t\t\tFile Handling" << endl;
    drawline();
    cout << "\n\n\n\t\t\t\t\t(Press any key to continue)";
    cin.get();
    system("cls");
    main_menu();
}
void drawline()
{
    int i;
    printf("\n\n\n\n\t\t\t\t");
    for (i = 0; i < 45; i++)
        printf("=");
}