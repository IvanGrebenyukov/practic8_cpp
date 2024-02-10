// practica8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <algorithm>
#include<vector>
using namespace std;
struct Publication {
    char author[100];
    char title[100];
    char type[100];
    union
    {
        int bookYear;
        struct {
            char journalName[100];
            int journalYear;
            int journalNumber;
        } journal;

    };
    Publication(const char* aut, const char* tit, const char* tp, int ye) {
        strncpy_s(author, aut, sizeof(author));
        strncpy_s(title , tit, sizeof(title));
        strncpy_s(type, tp, sizeof(type));
        bookYear = ye;
    }
       

     Publication(const char* aut, const char* tit, const char* tp, const char* jourName, int ye, int num)
     {
         strncpy_s(author, aut, sizeof(author));
         strncpy_s(title, tit, sizeof(title));
         strncpy_s(type, tp, sizeof(type));
         strncpy_s(journal.journalName, jourName, sizeof(type));
         journal.journalYear = ye;
         journal.journalNumber = num;
     }
     Publication() {};
    
};

bool isJournal(const Publication& pub) {
    return pub.type == "журнал";
}

bool publishedYear(const Publication& pub, int year) {
    return pub.journal.journalYear == year;
}

int main()
{
    setlocale(LC_ALL, "ru");
    Publication publications[] = {
       Publication("Автор1", "Название1", "книга", 2000),
       Publication{"Автор2", "Название2", "журнал", "Журнал1", 2001, 1},
       Publication{"Автор3", "Название3", "журнал", "Журнал2", 2001, 2},
       Publication{"Автор4", "Название4", "журнал", "Журнал3", 2002, 3},
       Publication{"Автор3", "Название3", "книга", 2005},
       Publication{"Автор3", "Название4", "журнал", "Журнал4", 2001, 4},
    };
   
    int yearToSearch = 2001;
    //Publication journalPublications[10];
    //int count = 0;
    vector<Publication> journalPublications;
    for ( const auto& publication: publications )
    {
        if (publishedYear(publication, yearToSearch)) {
            journalPublications.push_back(publication);
        }
    }
    
    for (int i = 0; i < journalPublications.size() - 1; ++i) 
    {
        for (int j = 0; j < journalPublications.size() - i - 1; ++j) 
        {
            if (journalPublications[j].title > journalPublications[j + 1].title) {
                swap(journalPublications[j], journalPublications[j + 1]);
            }
        }
    }
   /* sort(journalPublications, yearToSearch, publishedYear);*/
    cout << "Журнальные произведения за " << yearToSearch << ": " << endl;
    for (const auto& publication : journalPublications)
    {
        cout << publication.title << " (" << publication.journal.journalName << ", " << publication.journal.journalNumber << ")" << endl;
    }
    return 0;
}

