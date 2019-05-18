#include <iostream>
#include <string.h>
#include <iomanip> // required for setwidth
#include <fstream>
using namespace std;

int details;

//global variable to hold the number of entries in the file File.txt
int studentCount = 0;

int CETCount = 0;
int COMEDKCount = 0;
int managementCount = 0;
int totalStudents = 0;

int countTotalLines(){
    int count = 0;
    char temp[500];
    ifstream in;
    in.open("File.txt");
    while(!in.eof()){
        in.getline(temp, 500);
        count++;        
    }
    in.close();
    return count-1;
}

class Student
{
  public:
    int appNumber;
    char name[50];
    int CETRank;
    int COMEDKRank;
    int managementFlag;
    int priority[3]; // CSE, ISE, ME

    Student()
    {
        for (int i = 0; i < 3; i++)
        {
            priority[i] = 0;
        }
    }

    void getDetails();

    void addStudent()
    {
        getDetails();
    }

    void printStudentDetails();
};

class MeritList : public Student
{
  public:
    void makeMeritList(Student a[])
    {
        ifstream in;
        in.open("File.txt");
        char tempname[50];
        Student s;
        int tCETRank, tapm, tcomRank, tmanFlag;
        int tpArray[3];
        for (int i = 0; i < countTotalLines(); i++)
        {
            in >> tapm >> tempname >> tpArray[0] >> tpArray[1] >> tpArray[2] >> tCETRank >> tcomRank >> tmanFlag;
            strcpy(s.name, tempname);
            s.appNumber = tapm;
            s.CETRank = tCETRank;
            s.COMEDKRank = tcomRank;
            s.managementFlag = tmanFlag;
            studentCount++;

            for (int i = 0; i < 3; i++)
            {
                s.priority[i] = tpArray[i];
            }
            a[i] = s;
        }
    }

    void printList(Student &s)
    {
        cout << "Name: ";
        cout << s.name << endl;
        cout << "Application Number: ";
        cout << s.appNumber << endl;
        cout << "CET Rank: ";
        cout << s.CETRank << endl;
        cout << "COMEDK Rank: ";
        cout << s.COMEDKRank << endl;
        cout << "Management Status: ";
        if (s.managementFlag == 1)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    void addToCETList(Student &s);
    void addToCOMEDKList(Student &s);
    void addToManagementList(Student &s);
};

void Student::getDetails()
{
    ofstream out;
    out.open("File.txt", ios::app);
    int tempInteger;

    cout << "Enter student's application number" << endl;
    cin >> appNumber;
    cout << "Enter student's name" << endl;
    cin >> name;
    cout << "Enter CET Rank (0 if not written)" << endl;
    cin >> CETRank;
    cout << "Enter COMEDK Rank (0 if not written)" << endl;
    cin >> COMEDKRank;
    cout << "Are you interested in Management option? 1 for Yes and 0 for No" << endl;
    cin >> managementFlag;
    cout << "We would now like to know your priority of subjects" << endl;
    // TODO : Make this more interactive
    cout << "1 for CSE, 2 for ISE, 3 for ME" << endl;

    out << appNumber << "\t";
    out << name << "\t";

    for (int i = 0; i < 3; i++)
    {
        cin >> tempInteger;
        // handle numbers greater than 3 (throw error)
        priority[i] = tempInteger;
        out << tempInteger << "\t";
    }

    out << CETRank << "\t";
    out << COMEDKRank << "\t";
    out << managementFlag << endl;

    out.close();

    // printStudentDetails();
}

void Student::printStudentDetails()
{
    // cout << "\nTo confirm, the new student details are:";

    cout << setw(6) << appNumber << '\t' << setw(10) << name << '\t' <<setw(8) <<  CETRank << '\t' << setw(11) << COMEDKRank << '\t' << setw(10) << managementFlag << '\t';
    // cout <<name<<'\t';
    // cout << "Name: " << name << endl;
    // cout << "CET Rank: " << CETRank << endl;
    // cout << "COMEDK Rank: " << COMEDKRank << endl;
    // cout << "Management:" << managementFlag << endl;
    for (int i = 0; i < 3; i++)
    {
        if (priority[i] == 1)
            // cout << "Priority " << i + 1 << ": "
            //      << "CSE" << endl;
            cout << "CSE\t";
        if (priority[i] == 2)
            // cout << "Priority " << i + 1 << ": "
            //      << "ISE" << endl;
            cout << "ISE\t";
        if (priority[i] == 3)
            // cout << "Priority " << i + 1 << ": "
            //      << "ME" << endl;
                 cout<<"ME\t";
    }

    cout << endl;
    // cout << "********************************************** \n";
}

Student sArray[30];
Student CETArray[15];
Student COMEDKArray[15];
Student managementArray[15];

void MeritList::addToCETList(Student &s)
{
    if (s.CETRank != 0)
        CETArray[CETCount++] = s;
}

void MeritList::addToCOMEDKList(Student &s)
{
    if (s.COMEDKRank != 0)
        COMEDKArray[COMEDKCount++] = s;
}

void MeritList::addToManagementList(Student &s)
{

    ofstream out;
    out.open("ManagementList.txt", ios::app);
    if (s.managementFlag == 1)
    {
        managementArray[managementCount++] = s;
        out << s.appNumber << "\t";
        out << s.name << "\t";

        for (int i = 0; i < 3; i++)
        {
            out << s.priority[i] << "\t";
        }
        out << endl;
    }

    out.close();
}

void appendToFile(Student &s, char fileName[])
{ // "CETList.txt"
    ofstream out;
    if (strcmp(fileName, "CETList.txt") == 0)
    {
        out.open(fileName, ios::app);
        out << s.appNumber << "\t";
        out << s.name << "\t";

        for (int i = 0; i < 3; i++)
        {
            out << s.priority[i] << "\t";
        }

        out << s.CETRank << endl;

        out.close();
    }

    else if (strcmp(fileName, "COMEDKList.txt") == 0)
    {
        out.open(fileName, ios::app);
        out << s.appNumber << "\t";
        out << s.name << "\t";

        for (int i = 0; i < 3; i++)
        {
            out << s.priority[i] << "\t";
        }

        out << s.COMEDKRank << endl;

        out.close();
    }
}

void sortCETList(Student S[])
{
    int minIndex = 0;
    Student temp;
    for (int i = 0; i < CETCount - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < CETCount; j++)
        {
            if (S[i].CETRank > S[j].CETRank)
                minIndex = j;
        }
        temp = S[i];
        S[i] = S[minIndex];
        S[minIndex] = temp;
    }

    for (int i = 0; i < CETCount; i++)
    {
        appendToFile(S[i], "CETList.txt");
    }
}

void sortCOMEDKList(Student S[])
{
    int minIndex = 0;
    Student temp;
    for (int i = 0; i < COMEDKCount - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < COMEDKCount; j++)
        {
            if (S[i].COMEDKRank > S[j].COMEDKRank)
                minIndex = j;
        }

        temp = S[i];
        S[i] = S[minIndex];
        S[minIndex] = temp;
    }

    for (int i = 0; i < COMEDKCount; i++)
    {
        appendToFile(S[i], "COMEDKList.txt");
    }
}

class Branch
{
  public:
    Student studentList[10];
    int quotaLimit[3];
    int quotaCount[3];

    Branch()
    {
        quotaLimit[0] = 4;
        quotaLimit[1] = 4;
        quotaLimit[2] = 2;
        for (int i = 0; i < 3; i++)
        {
            quotaCount[i] = 0;
        }
    }
};
Branch branches[3];

int searchArray(Student s)
{
    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j<branches[i].quotaCount[0] + branches[i].quotaCount[1] + branches[i].quotaCount[2]; j++){
            if(s.appNumber == branches[i].studentList[j].appNumber){
                return 1;
            }
        }
    }
    return -1;
}

int tryBranch(int quota, int br, Student s)
{ // KCET(0), CSE, Student object
    if (branches[br].quotaCount[quota] < branches[br].quotaLimit[quota])
    {
        if(searchArray(s) == 1){
            return -1;
        }
        branches[br].studentList[branches[br].quotaCount[0] + branches[br].quotaCount[1] + branches[br].quotaCount[2]] = s;
        
        branches[br].quotaCount[quota]++;
        return 0;
    }
    return -1;
}

void assignBranches(int quota, Student S[], int count)
{
    for (int i = 0; i < count; i++)
        for (int j = 0; j < 3; j++)
            if (tryBranch(quota, S[i].priority[j] - 1, S[i]) == 0)
                break;
}



int main()
{
    Student s;
    MeritList ML;
    int choice = 0;
    do{
            cout<<"1.Make merit list"<<endl;
            cout<<"2.Add Student"<<endl;
            cout<<"3.View merit list"<<endl;
            cout<<"4.View Student details"<<endl;
            cout<<"5.View CET list"<<endl;
            cout<<"6.View COMEDK list"<<endl;
            cout<<"7.View Management list"<<endl;
            cout<<"8.View CSE list"<<endl;
            cout<<"9.View ISE list"<<endl;
            cout<<"10.View ME list"<<endl;
            cout<<"11.Exit" << endl;

            cin>>choice;

            switch(choice)
            {
                case 1:
                 system("clear");
                    ML.makeMeritList(sArray);
                    for(int i=0;i<countTotalLines();i++){
                        ML.addToCOMEDKList(sArray[i]);
                        ML.addToCETList(sArray[i]);
                        ML.addToManagementList(sArray[i]);
                    } 
                    sortCETList(CETArray);
                    sortCOMEDKList(COMEDKArray);

                    assignBranches(0, CETArray, CETCount);
                    assignBranches(1, COMEDKArray, COMEDKCount);
                    assignBranches(2, managementArray, managementCount);
                break;

                case 2:
                 system("clear");
                    s.addStudent(); break;
                case 3:
                    system("clear");
                    cout << setw(6) <<"App No" << '\t' << setw(10) <<"Name" << '\t' <<setw(8) <<"CET Rank" << '\t' <<setw(11) << "COMEDK Rank" << '\t' << setw(10) <<"Management" << '\t' << "P1" << '\t' <<"P2" << '\t' << "P3" <<endl;
                        cout <<"-------------------------------------------------------------------------------------------" <<endl;

                    for(int i=0;i<countTotalLines();i++)
                    {
                        sArray[i].printStudentDetails();
                    }
                      cout <<"-------------------------------------------------------------------------------------------" <<endl;
                    
                    break;
                case 4:
                 system("clear");
                    cout << "Enter the application number of the student" << endl;
                    cin >> details;
                    for(int i=0;i<countTotalLines();i++){
                        if(sArray[i].appNumber == details){
                                                cout << setw(6) <<"App No" << '\t' << setw(10) <<"Name" << '\t' <<setw(8) <<"CET Rank" << '\t' <<setw(11) << "COMEDK Rank" << '\t' << setw(10) <<"Management" << '\t' << "P1" << '\t' <<"P2" << '\t' << "P3" <<endl;
                        cout <<"-------------------------------------------------------------------------------------------" <<endl;
                            sArray[i].printStudentDetails();
                             cout <<"-------------------------------------------------------------------------------------------" <<endl;
                            break;
                        }
                    }
                    break;

                case 5: 
                 system("clear");
                  cout << setw(6) <<"App No" << '\t' << setw(10) <<"Name" << '\t' <<setw(8) <<"CET Rank" << '\t' <<setw(11) << "COMEDK Rank" << '\t' << setw(10) <<"Management" << '\t' << "P1" << '\t' <<"P2" << '\t' << "P3" <<endl;
                        cout <<"-------------------------------------------------------------------------------------------" <<endl;
                    for(int i=0;i<CETCount;i++)
                        {
                            CETArray[i].printStudentDetails();
                        }
                         cout <<"-------------------------------------------------------------------------------------------" <<endl;
                    break;
                case 6: 
                 system("clear");
                cout << setw(6) <<"App No" << '\t' << setw(10) <<"Name" << '\t' <<setw(8) <<"CET Rank" << '\t' <<setw(11) << "COMEDK Rank" << '\t' << setw(10) <<"Management" << '\t' << "P1" << '\t' <<"P2" << '\t' << "P3" <<endl;
                        cout <<"-------------------------------------------------------------------------------------------" <<endl;
                    for(int i=0;i<COMEDKCount;i++){
                        COMEDKArray[i].printStudentDetails();
                    }
                     cout <<"-------------------------------------------------------------------------------------------" <<endl;
                    break;
                case 7:
                 system("clear");
                cout << setw(6) <<"App No" << '\t' << setw(10) <<"Name" << '\t' <<setw(8) <<"CET Rank" << '\t' <<setw(11) << "COMEDK Rank" << '\t' << setw(10) <<"Management" << '\t' << "P1" << '\t' <<"P2" << '\t' << "P3" <<endl;
                        cout <<"-------------------------------------------------------------------------------------------" <<endl;
                    for(int i=0;i<managementCount;i++){
                        managementArray[i].printStudentDetails();
                    }
                     cout <<"-------------------------------------------------------------------------------------------" <<endl;
                    break;
                case 8:
                 system("clear");
                cout << setw(6) <<"App No" << '\t' << setw(10) <<"Name" << '\t' <<setw(8) <<"CET Rank" << '\t' <<setw(11) << "COMEDK Rank" << '\t' << setw(10) <<"Management" << '\t' << "P1" << '\t' <<"P2" << '\t' << "P3" <<endl;
                        cout <<"-------------------------------------------------------------------------------------------" <<endl;
                 for (int i = 0; i < branches[0].quotaCount[0] + branches[0].quotaCount[1] + branches[0].quotaCount[2]; i++)
                 {
                        branches[0].studentList[i].printStudentDetails();
                 }
                 cout <<"-------------------------------------------------------------------------------------------" <<endl;
                    break;
                case 9:
                 system("clear");
                cout << setw(6) <<"App No" << '\t' << setw(10) <<"Name" << '\t' <<setw(8) <<"CET Rank" << '\t' <<setw(11) << "COMEDK Rank" << '\t' << setw(10) <<"Management" << '\t' << "P1" << '\t' <<"P2" << '\t' << "P3" <<endl;
                        cout <<"-------------------------------------------------------------------------------------------" <<endl;
                    for (int i = 0; i < branches[1].quotaCount[0] + branches[1].quotaCount[1] + branches[1].quotaCount[2]; i++)
                    {
                        branches[1].studentList[i].printStudentDetails();
                    }
                    cout <<"-------------------------------------------------------------------------------------------" <<endl;
                    break;
                case 10:
                 system("clear");
                cout << setw(6) <<"App No" << '\t' << setw(10) <<"Name" << '\t' <<setw(8) <<"CET Rank" << '\t' <<setw(11) << "COMEDK Rank" << '\t' << setw(10) <<"Management" << '\t' << "P1" << '\t' <<"P2" << '\t' << "P3" <<endl;
                        cout <<"-------------------------------------------------------------------------------------------" <<endl;
                 for (int i = 0; i < branches[2].quotaCount[0] + branches[2].quotaCount[1] + branches[2].quotaCount[2]; i++)
                {
                        branches[2].studentList[i].printStudentDetails();
                 }
                 cout <<"-------------------------------------------------------------------------------------------" <<endl;
                 break;
                case 11:
                 system("clear");
                    cout << "Shutting down..." << endl;
                    exit(1);
                
            }
    }while(choice!=11);
    
    
    return 0;
}