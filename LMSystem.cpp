#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX_NUM_BOOK = 100;
const int MAX_NUM_STUDENT = 10;

enum eBookAttribute { TITLE = 1, PUBLISHER, AUTHOR, ISBN };  
enum eStudentAttribute { STUDENT_NAME = 1, STUDENT_ID };     

// book data
struct Book {
    string book_ISBN;
    string book_title;
    string book_author;
    string book_publisher;
    string book_year;
    int book_quantity;
    bool book_isBorrowed;
};

class BookList {
public:
    BookList();
    ~BookList();
    
    void add_a_book();
    void display_a_book(string isbn);
    void display_ISBN_of_all_books();    
    int query_a_book(eBookAttribute, const string &);      
    void delete_a_book(string);     
    void modify_a_book(int);   
    void store();            
    
    string get_book_ISBN(int i) { return m_data[i].book_ISBN; }
    int get_num() { return m_num; }
    
private:
    Book   m_data[MAX_NUM_BOOK];
    int    m_num;
};

BookList::BookList() {
    m_num = 0;
}

BookList::~BookList() {
}
 

// student data
struct Student {
    string student_ID;
    string student_name;
    string student_department;
    string student_email;
};

class StudentList {
public:
    StudentList();
    ~StudentList();

    void add_a_student();
    void display_a_student(string id);
    int query_a_student(eStudentAttribute, const string *);
    void delete_a_student(string);  
    void modify_a_student(int);     
    void store();       
    
    string get_student_ID(int i) { return m_data[i].student_ID; }
    int get_num() { return m_num; }
    
private:
    Student m_data[MAX_NUM_STUDENT];
    int    m_num;
};

StudentList::StudentList() {
    m_num = 0;
}

StudentList::~StudentList() {
}

// week 17
int getRequest() {
    int request;
    
    cout << "\nEnter request" << endl
         << " 0 - Exit " << endl
         << " 1 - Add a book " << endl
         << " 2 - Add a student " << endl
         << " 3 - Display a book " << endl
         << " 4 - Display a student " << endl
         << " 5 - display_ISBN_of_all_books " << endl
         << " 6 - Query a book " << endl
         << " 7 - Query a student " << endl
         << " 8 - Delete a book " << endl
         << " 9 - Delete a student" << endl
         << " 10 - Store all the data " << endl;
         
    do {
        cout << "\n?";
        cin >> request;
    } while ( request < 1 || request > 10 );
    
    return request;
}

int main() {
    BookList myBookList;
    StudentList myStudentList;
    string queryString;
    int tmpInteger;
    string tmpString; 
    
    // week 17
    int request = getRequest();      

    while ( request != 0 ) {
        switch ( request ) {
        case 1:
            myBookList.add_a_book();
            break;
        case 2:
            myStudentList.add_a_student();
            break;
        case 3:
            myBookList.display_a_book(myBookList.get_book_ISBN(myBookList.get_num()-1));
            break;
        case 4:
            myStudentList.display_a_student(myStudentList.get_student_ID(myStudentList.get_num()-1));
            break;
        case 5:
            myBookList.display_ISBN_of_all_books();
            break;
        case 6:
            cout << "Query a book\n";
            
            eBookAttribute bookOption;
            cout << "Choose 0 for exit, 1 for title, 2 for publisher, 3 for author, and 4 for ISBN):\n";
            cin >> tmpInteger;
            bookOption = eBookAttribute ( tmpInteger );
            
            cout << "Please enter the query string:\n";
            cin >> ws;
            getline(cin, queryString);
            
            
            myBookList.modify_a_book( myBookList.query_a_book(bookOption, queryString) );
            
            break;
            
        case 7:
            cout << "Query a student\n";
            
            eStudentAttribute studentOption;
            cout << "Choose 1 for student name and 2 for student ID):\n";
            cin >> tmpInteger;
            studentOption = eStudentAttribute ( tmpInteger );
            
            cout << "Please enter the query string:\n";
            cin >> ws;
            getline(cin, queryString);
            
            
            myStudentList.modify_a_student( myStudentList.query_a_student(studentOption, &queryString) );
            
            break;
            
        case 8:                                            
            cout << "Please enter the ISBN of the book to be deleted:\n";   
            cin >> ws;                                                      
            getline(cin, tmpString);                                        
            myBookList.delete_a_book(tmpString);   
            
            break;                                    

        case 9:                                                         
            cout << "Please enter the ID of the student to be deleted:\n";   
            cin >> ws;                                                      
            getline(cin, tmpString);                                        
            myStudentList.delete_a_student(tmpString);         
            
            break;                           
            
        case 10:
            myBookList.store();
            myStudentList.store();
            
            break;
            
        default:
            break;
        }
        
        request = getRequest();
    }

    system("pause");
    return 0;
}

void BookList::add_a_book() {
    int i;
    cout << "Enter the ISBN, title, author(s), publisher, publication year, and quantity of a book\n";
    cin >> ws;     

    while ( getline(cin, m_data[m_num].book_ISBN ) ) {
         bool isExisted = false;
         
         for ( i = 0 ; i < m_num ; i++ ) {
             if ( m_data[i].book_ISBN == m_data[m_num].book_ISBN ) {
                  isExisted = true;
                  break;
             }
         }
         
         if ( !isExisted ) {
              break;
         }
         else {
              cout << "The ISBN already exists. Please re-enter the ISBN of the book\n";
         }
         cin >> ws;
    }

    getline(cin, m_data[m_num].book_title);
    getline(cin, m_data[m_num].book_author);
    getline(cin, m_data[m_num].book_publisher);
    getline(cin, m_data[m_num].book_year);
    cin >> m_data[m_num].book_quantity;
    m_data[m_num].book_isBorrowed = false;
    
    m_num++;
}

void BookList::display_a_book(string isbn) {
     int i, index;
     
     bool isFound = false;
     for ( i = 0 ; i < m_num ; i++ ) {
         if ( m_data[i].book_ISBN == isbn ) {
            index = i;
            isFound = true;
            break;
         }
     }
     
     if ( isFound ) {
        cout << "ISBN = " << m_data[index].book_ISBN << endl
             << "Title = " << m_data[index].book_title << endl
             << "Author = " << m_data[index].book_author << endl
             << "Publisher = " << m_data[index].book_publisher << endl
             << "Year = " << m_data[index].book_year << endl
             << "Quantity = " << m_data[index].book_quantity << endl;
            
          if ( m_data[index].book_isBorrowed )
             cout << "At least one copy of this book is borrowed!" << endl;
          else
             cout << "No copy of this book is not borrowed!" << endl;
     }
     else {
          cout << "Book ISBN " << isbn << " cannot be found!" << endl;
     }
     
     cout << endl;
}

void StudentList::add_a_student() {
    int i;
    
    cout << "Enter the ID, name, department, and e-mail of a student:" << endl;
    cin >> ws;
    
    while ( getline(cin, m_data[m_num].student_ID) ) {
         bool isExisted = false;
         
         for ( i = 0 ; i < m_num ; i++ ) {
             if ( m_data[i].student_ID == m_data[m_num].student_ID ) {
                  isExisted = true;
                  break;
             }
         }
         
         if ( !isExisted ) {
              break;
         }
         else {
              cout << "The ID already exists. Please re-enter the ID of the student:" << endl;
         }
         cin >> ws;
    }
    
    getline(cin, m_data[m_num].student_name);
    getline(cin, m_data[m_num].student_department);
    getline(cin, m_data[m_num].student_email);
    
    m_num++;
}

void StudentList::display_a_student(string id) {
     int i, index;
     
     bool isFound = false;
     for ( i = 0 ; i < m_num ; i++ ) {
         if ( m_data[i].student_ID == id ) {
            index = i;
            isFound = true;
            break;
         }
     }
     
     if ( isFound ) {
        cout << "ID = " << m_data[index].student_ID << endl
             << "Name = " << m_data[index].student_name << endl
             << "Department = " << m_data[index].student_department << endl
             << "E-mail = " << m_data[index].student_email << endl;
     }
     else {
          cout << "Student ID " << id << " cannot be found!" << endl;
     }
     
     cout << endl;
}

void BookList::display_ISBN_of_all_books() {    
     for ( int i = 0 ; i < m_num ; i++ ) {
         cout << "ISBN of Book " << i << " is " << m_data[i].book_ISBN << ".\n";
     }
}

int BookList::query_a_book(eBookAttribute option, const string & queryString) {  
     int i;
     int index = -1;            
     bool isFound = false;
     
     if ( option == TITLE ) {
        for ( i = 0 ; i < m_num ; i++ ) {
            if ( m_data[i].book_title == queryString ) {
                 isFound = true;
                 index = i;
                 break;
            }
        }
     }
     else if ( option == PUBLISHER) {
        for ( i = 0 ; i < m_num ; i++ ) {
            if ( m_data[i].book_publisher == queryString ) {
                 isFound = true;
                 index = i;
                 break;
            }
        }
     }
     else if ( option == AUTHOR ) {
        for ( i = 0 ; i < m_num ; i++ ) {
            if ( m_data[i].book_author == queryString ) {
                 isFound = true;
                 index = i;
                 break;
            }
        }
     }
     else {                     
        for ( i = 0 ; i < m_num ; i++ ) {
            if ( m_data[i].book_ISBN == queryString ) {
                 isFound = true;
                 index = i;
                 break;
            }
        }
     }

     if ( isFound ) {
          cout << "The data of the queried book is as follows:\n";
          display_a_book(m_data[index].book_ISBN);
     }
     else {
          cout << "This book cannot be found.\n";
     }
     
     return index;
}

int StudentList::query_a_student(eStudentAttribute option, const string * queryString) {    
     int i;
     int index = -1;            
     bool isFound = false;
     
     if ( option == STUDENT_NAME ) {
        for ( i = 0 ; i < m_num ; i++ ) {
            if ( m_data[i].student_name == *queryString ) {
                 isFound = true;
                 index = i;
                 break;
            }
        }
     }
     else {                     // i.e., option = STUDENT_ID
        for ( i = 0 ; i < m_num ; i++ ) {
            if ( m_data[i].student_ID == *queryString ) {
                 isFound = true;
                 index = i;
                 break;
            }
        }
     }

     if ( isFound ) {
          cout << "The data of the queried student is as follows:\n";
          display_a_student(m_data[index].student_ID);
     }
     else {
          cout << "This book cannot be found.\n";
     }
     
     return index;
}

void BookList::delete_a_book(string isbn) {
     int i;
     int index = -1;
     
     bool isFound = false;
     for ( i = 0 ; i < m_num ; i++ ) {
         if ( m_data[i].book_ISBN == isbn ) {
              isFound = true;
              index = i;
              break;
         }
     }
     
     if ( isFound ) {   
        for ( i = index ; i < m_num-1 ; i++ ) {
            m_data[i].book_ISBN =  m_data[i+1].book_ISBN;
            m_data[i].book_title = m_data[i+1].book_title;
            m_data[i].book_author = m_data[i+1].book_author;
            m_data[i].book_publisher = m_data[i+1].book_publisher;
            m_data[i].book_year = m_data[i+1].book_year;
            m_data[i].book_quantity = m_data[i+1].book_quantity;
            m_data[i].book_isBorrowed = m_data[i+1].book_isBorrowed;
        }
        
        m_num--;      
     }
}

void StudentList::delete_a_student(string id) {
     int i;
     int index = -1;
     
     bool isFound = false;
     for ( i = 0 ; i < m_num ; i++ ) {
         if ( m_data[i].student_ID == id ) {
              isFound = true;
              index = i;
              break;
         }
     }
     
     if ( isFound ) {   
        for ( i = index ; i < m_num-1 ; i++ ) {
            m_data[i].student_ID =  m_data[i+1].student_ID;
            m_data[i].student_name = m_data[i+1].student_name;
            m_data[i].student_department = m_data[i+1].student_department;
            m_data[i].student_email = m_data[i+1].student_email;
        }
        
        m_num--;      
     }     
}

void BookList::modify_a_book(int index) {     
    int i;
    cout << "Enter the updated ISBN, title, author(s), publisher, publication year, and quantity of book " << index << "\n";
    cin >> ws;     

    string newISBN;
    while ( getline(cin, newISBN) ) {
         bool isExisted = false;
         
         for ( i = 0 ; i < m_num ; i++ ) {
             if ( i != index && m_data[i].book_ISBN == newISBN ) {
                  isExisted = true;
                  break;
             }
         }
         
         if ( !isExisted ) {
              break;
         }
         else {
              cout << "The ISBN already exists. Please re-enter the ISBN of the book\n";
         }
         cin >> ws;
    }

    m_data[index].book_ISBN = newISBN;
    getline(cin, m_data[index].book_title);
    getline(cin, m_data[index].book_author);
    getline(cin, m_data[index].book_publisher);
    getline(cin, m_data[index].book_year);
    cin >> m_data[index].book_quantity;
    
    cout << "Enter whether this book is borrowed (0 for false; 1 for true):\n";
    cin >> m_data[index].book_isBorrowed;
}

void BookList::store() {
     int i;
     
     ofstream outFile1("book_data.txt", ios::out);
     
     for ( i = 0 ; i < m_num ; i++ ) {
         outFile1 << m_data[i].book_ISBN << endl
                  << m_data[i].book_title << endl
                  << m_data[i].book_author << endl
                  << m_data[i].book_publisher << endl
                  << m_data[i].book_year << endl
                  << m_data[i].book_quantity << endl
                  << m_data[i].book_isBorrowed << endl;
     }
}

void StudentList::store() {
     int i;

     ofstream outFile2("student_data.txt", ios::out);
     for ( i = 0 ; i < m_num ; i++ ) {
         outFile2 << m_data[i].student_ID << endl
                  << m_data[i].student_name << endl
                  << m_data[i].student_department << endl
                  << m_data[i].student_email << endl;
     }
}

void StudentList::modify_a_student(int index) {     
    int i;
    
    cout << "Enter the ID, name, department, and e-mail of a student:" << endl;
    cin >> ws;
    
    string newID;
    while ( getline(cin, newID) ) {
         bool isExisted = false;
         
         for ( i = 0 ; i < m_num ; i++ ) {
             if ( i != index && m_data[i].student_ID == newID ) {
                  isExisted = true;
                  break;
             }
         }
         
         if ( !isExisted ) {
              break;
         }
         else {
              cout << "The ID already exists. Please re-enter the ID of the student:" << endl;
         }
         cin >> ws;
    }
    
    m_data[index].student_ID = newID;
    getline(cin, m_data[index].student_name);
    getline(cin, m_data[index].student_department);
    getline(cin, m_data[index].student_email);
}
