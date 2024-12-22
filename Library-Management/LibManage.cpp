#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

class Book {
protected:
    int id;
    string title;
    string author;
    string publisher;
    string type;
    int quantity;
    int borrowed;

public:
    virtual void InformationBook() = 0;
    virtual void AddBookType() = 0;

    int GetID() {
        return id;
    }

    string GetType() {
        return type;
    }

    string GetTitle() {
        return title;
    }

    int GetQuantity() {
        return quantity;
    }

    string GetPublisher() {
        return publisher;
    }
    
    string GetAuthor() {
        return author;
    }

    int GetBorrowed() {
        return borrowed;
    }

    void SetID(int id) {
        this->id = id;
    }

    void SetTitle(string title) {
        this->title = title;
    }

    void SetQuantity(int quantity) {
        this->quantity = quantity;
    }

    void SetPublisher(string publisher) {
        this->publisher = publisher;
    }

    void SetAuthor (string author) {
        this->author = author;
    }

    void SetType (string type) {
        this->type = type;
    }

    void SetBorrowed (int borrowed) {
        this->borrowed = borrowed;
    }

    void PrintBooks() {
        cout << setw(21) << "";
        cout << left << setw(10) << id;
        cout << left << setw(56) << title;
        cout << left << setw(38) << author;
        cout << left << setw(26) << publisher;
        cout << left << setw(15) << quantity;
        cout << left << setw(10) << borrowed << endl;
    }

    void LoadFromFile(ifstream &file) {
        file >> id;
        file.ignore();
        getline(file, type, ',');
        file >> quantity;
        file.ignore();      
        getline(file, title, ',');
        getline(file, author, ',');
        getline(file, publisher, ',');
        file >> borrowed;
        file.ignore();
    }

    void Add() {
        borrowed = 0;
        cin.ignore();
        cout << "Title: ";
        getline(cin, title);
        cout << "Author: ";
        getline(cin, author);
        cout << "Publisher: ";
        getline(cin, publisher);
        cout << "Quantity: ";
        cin >> quantity;
    }
};

bool flagN = 0;
bool flagA = 0;
bool flagH = 0;
bool flagS = 0;

class Novel : public Book {
public:
    void InformationBook () {
        if(flagN == 0) {
            cout << "\nNovel" << endl;
            flagN = !flagN;
        }
        PrintBooks();
    }

    void AddBookType () {
        Add();
        type = "Novel";
    }
};

class Academic : public Book {
public:
    void InformationBook () {
        if(flagA == 0) {
            cout << "\nAcademic Book" << endl;
            flagA = !flagA;
        }
        PrintBooks();
    }

    void AddBookType () {
        Add();
        type = "Academic";
    }
};
class History : public Book {
public:
    void InformationBook () {
        if(flagH == 0) {
            cout << "\nHistory Book" << endl;
            flagH = !flagH;
        }
        PrintBooks();
    }

    void AddBookType () {
        Add();
        type = "History";
    }
};
class Science : public Book {
public:
    void InformationBook () {
        if(flagS == 0) {
            cout << "\nScience Book" << endl;
            flagS = !flagS;
        }
        PrintBooks();
    }

    void AddBookType () {
        Add();
        type = "Science";
    }
};

class Member {
private:
    string name;
    int memberID;
    string mail;
    int tel;
    int borrow;
    int bookIDborrow1;
    int bookIDborrow2;
    int bookIDborrow3;
public:
    Member() {
        name = "";
        memberID = 0;
        mail = "";
        tel = 0;
        borrow = 0;
        bookIDborrow1 = 0;
        bookIDborrow2 = 0;
        bookIDborrow3 = 0;
    }

    void PrintInfo() {
        cout << "\n";
        cout << left << setw(20) << memberID;
        cout << left << setw(33) << name;
        cout << left << setw(27) << tel;
        cout << left << setw(42) << mail;
        cout << left << setw(19) << borrow;
        cout << left << setw(10) << bookIDborrow1;
        cout << left << setw(10) << bookIDborrow2;
        cout << left << setw(10) << bookIDborrow3;
    }

    void LoadFromFile(ifstream &file) {
        file >> memberID;
        file.ignore();
        getline(file, name, ',');
        file >> tel;
        file.ignore();
        getline(file, mail, ',');
        file >> borrow;
        file.ignore();
    }

    void Add(int Member_ID) {
        memberID = Member_ID;
        borrow = 0;
        cin.ignore();
        cout << "Full name: ";
        getline(cin, name);
        cout << "Phone number: ";
        cin >> tel;
        cin.ignore();
        cout << "Mail: ";
        getline(cin, mail);
    }

    int GetMemberID() {
        return memberID;
    }

    string GetName() {
        return name;
    }

    string GetMail() {
        return mail;
    }

    int GetTel() {
        return tel;
    }

    int GetBorrow() {
        return borrow;
    }

    int GetBookIDborrow1() {
        return bookIDborrow1;
    }

    int GetBookIDborrow2() {
        return bookIDborrow2;
    }

    int GetBookIDborrow3() {
        return bookIDborrow3;
    }

    void SetBorrow (int borrow) {
        this->borrow = borrow;
    }

    void SetBookIDborrow1 (int bookIDborrow1) {
        this->bookIDborrow1 = bookIDborrow1;
    }

    void SetBookIDborrow2 (int bookIDborrow2) {
        this->bookIDborrow2 = bookIDborrow2;
    }

    void SetBookIDborrow3 (int bookIDborrow3) {
        this->bookIDborrow3 = bookIDborrow3;
    }
};

class Library {
private:
    vector<Book*> books;
    vector<Member*> members;
public:
    void LoadBooks() {
        ifstream file;
        file.open("books.csv");

        if (file.is_open()) {
            int total, n,a,h,s;
            file >> total;
            books.resize(total);
            file >> n;
            file >> a;
            file >> h;
            file >> s;
            file.ignore();

            for (int i = 0; i < n; i++) {
                books[i] = new Novel();
            }
            for (int i = n; i < n+a; i++) {
                books[i] = new Academic();
            }
            for (int i = n+a; i < n+a+h; i++) {
                books[i] = new History();
            }
            for (int i = n+a+h; i < n+a+h+s; i++) {
                books[i] = new Science();
            }

            for(int i = 0 ; i < total; i++) {
                    books[i]->LoadFromFile(file);
            }
            
            file.close();
            cout << "Books loaded successfully!" << endl;
        } else {
            cout << "\nFailed to open books file.";
        }
    }

    void LoadMembers() {
        ifstream file;
        file.open("members.csv");

        if (file.is_open()) {
            int total;
            file >> total;
            file.ignore();
            members.resize(total);

            for (int i = 0; i < total; i++) {
                members[i] = new Member();
                members[i]->LoadFromFile(file);
            }

            file.close();
            cout << "Members loaded successfully!" << endl;
        } else {
            cout << "\nFailed to open members file.";
        }
    }

    void DisplayBooks() {
        cout << "\n=============================================================================================================================================================================" << endl;
        cout << "******************************************************************************** BOOK LIST **********************************************************************************" << endl;
        cout << "=============================================================================================================================================================================" << endl;
        cout << setw(21) << "";
        cout << left << setw(10) << "ID";
        cout << left << setw(56) << "Title";
        cout << left << setw(36) << "Author";
        cout << left << setw(25) << "Publisher";
        cout << left << setw(15) << "Quantity";
        cout << left << setw(10) << "Borrowed" << endl;

        for (int i = 0; i < books.size(); i++) {
            books[i]->InformationBook();
        }

        flagN = !flagN;
        flagA = !flagA;
        flagH = !flagH;
        flagS = !flagS;

        cout << "\n*****************************************************************************************************************************************************************************" << endl;
    }

    void DisplayMembers() {
        cout << "\n=========================================================================================================================================================================" << endl;
        cout << "***************************************************************************** MEMBER LIST *******************************************************************************" << endl;
        cout << "=========================================================================================================================================================================" << endl;
        cout << left << setw(20) << "Member ID";
        cout << left << setw(30) << "Name";
        cout << left << setw(30) << "Telephone Number";
        cout << left << setw(40) << "Mail";
        cout << left << setw(15) << "Borrow";
        cout << left << setw(10) << "Book IDs borrowing (Maximum is 3)";

        for (int i = 0; i < members.size(); i++) {
            members[i]->PrintInfo();
        }
        cout << "\n\n*************************************************************************************************************************************************************************" << endl;
    }

    void BorrowBook() {
        int bookID;
        int memberID;
        cout << "Enter Book ID to borrow: ";
        cin >> bookID;
        cout << "Enter Member ID to borrow: ";
        cin >> memberID;
        for (Book* book : books) {
            if (book->GetID() == bookID && book->GetQuantity() > 1) {
                for(Member* member : members) {
                    if(memberID == member->GetMemberID()) {
                        if(member->GetBookIDborrow1() == 0) member->SetBookIDborrow1(bookID);
                        else if(member->GetBookIDborrow2() == 0) member->SetBookIDborrow2(bookID);
                        else if(member->GetBookIDborrow3() == 0) member->SetBookIDborrow3(bookID);
                        else {
                            cout << "Cant borrow more than 3 books.";
                            return;
                        }
                        book->SetQuantity(book->GetQuantity() - 1);
                        book->SetBorrowed(book->GetBorrowed() + 1);
                        member->SetBorrow(member->GetBorrow() + 1);
                        cout << "Book borrowed successfully!" << endl;
                        return;
                    }
                }
                cout << "Member " << memberID << " does not exist." << endl;
                cout << "Please register to be a member." << endl;
                return;
            }
        }
        cout << "Book is not available or does not exist." << endl;
    }

    void ReturnBook() {
        int bookID;
        int memberID;
        cout << "Enter Book ID to return: ";
        cin >> bookID;
        cout << "Enter Member ID to return: ";
        cin >> memberID;
        for (Book* book : books) {
            if (book->GetID() == bookID && book->GetBorrowed() > 0) {
                for(Member* member : members) {
                    if(memberID == member->GetMemberID() && bookID == member->GetBookIDborrow1()) {
                        book->SetQuantity(book->GetQuantity() + 1);
                        book->SetBorrowed(book->GetBorrowed() - 1);
                        member->SetBorrow(member->GetBorrow() - 1);
                        member->SetBookIDborrow1(0);
                        cout << "Book returned successfully!" << endl;
                        return;
                    }
                    if(memberID == member->GetMemberID() && bookID == member->GetBookIDborrow2()) {
                        book->SetQuantity(book->GetQuantity() + 1);
                        book->SetBorrowed(book->GetBorrowed() - 1);
                        member->SetBorrow(member->GetBorrow() - 1);
                        member->SetBookIDborrow2(0);
                        cout << "Book returned successfully!" << endl;
                        return;
                    }
                    if(memberID == member->GetMemberID() && bookID == member->GetBookIDborrow3()) {
                        book->SetQuantity(book->GetQuantity() + 1);
                        book->SetBorrowed(book->GetBorrowed() - 1);
                        member->SetBorrow(member->GetBorrow() - 1);
                        member->SetBookIDborrow3(0);
                        cout << "Book returned successfully!" << endl;
                        return;
                    }
                }
                cout << "Member " << memberID << " does not exist or does not borrow any book." << endl;
                return;
            }
        }
        cout << "Book is not borrowed or does not exist." << endl;
    }

    void AddMember() {
        int member_ID;
        bool check = 0;
        do {
            cout << "Member ID: ";
            cin >> member_ID;
            for(Member* member : members) {
                if(member_ID == member->GetMemberID()) {
                    check = 1;
                    cout << "Member " << member_ID << " has already existed." << endl;
                    cout << "Please choose another ID." << endl;
                    break;
                }
                check = 0;
            }
        } while (check == 1);
        Member* member;
        member = new Member();
        member->Add(member_ID);
        members.insert(members.end(), member);
        cout << "Add member successfully!" << endl;
    }

    void DeleteMember() {
        int member_ID;
        cout << "Member ID need to be deleted: ";
        cin >> member_ID;
        int index;
        bool check = 0;
        for (int i=0; i < members.size(); i++) {
            if(member_ID == members[i]->GetMemberID()) {
                index = i;
                check = 1;
                break;
            }
        }
        if(check == 1) {
            delete members[index];
            members.erase(members.begin() + index);
            cout << "Delete member successfully!" << endl;
            return;
        } else {
            cout << "Member " << member_ID << " does not exist to be deleted." << endl;
            return;
        }
    }

    int CountBookType(string booktype) {
        int count = 0;
        for(Book* book : books) {
            if(book->GetType() == booktype) count++;
        }
        return count;
    }

    void AddBook() {
        int book_Type;
        int n, a, h, s;
        n = CountBookType("Novel");
        a = CountBookType("Academic");
        h = CountBookType("History");
        s = CountBookType("Science");
        
        do {
            cout << "0. Exit" << endl;
            cout << "1. Novel" << endl;
            cout << "2. Academic" << endl;
            cout << "3. History" << endl;
            cout << "4. Science" << endl;
            cout << "Type of book (1-4): ";
            cin >> book_Type;

            switch (book_Type) {
                case 1: {
                    for(Book* b : books) {
                        if(b->GetID() >= n + 1) {
                            b->SetID(b->GetID() + 1);
                        }
                    }
                    Book* book;
                    book = new Novel();
                    book->AddBookType();
                    book->SetID(n + 1);
                    books.insert(books.begin() + n, book);
                    cout << "Add Novel successfully!" << endl;
                    break;
                }
                case 2: {
                    for(Book* b : books) {
                        if(b->GetID() >= n + a + 1) {
                            b->SetID(b->GetID() + 1);
                        }
                    }
                    Book* book;
                    book = new Academic();
                    book->AddBookType();
                    book->SetID(n + a + 1);
                    books.insert(books.begin() + n + a, book);
                    cout << "Add Academic Book successfully!" << endl;
                    break;
                }
                case 3: {
                    for(Book* b : books) {
                        if(b->GetID() >= n + a + h + 1) {
                            b->SetID(b->GetID() + 1);
                        }
                    }
                    Book* book;
                    book = new History();
                    book->AddBookType();
                    book->SetID(n + a + h + 1);
                    books.insert(books.begin() + n + a + h, book);
                    cout << "Add History Book successfully!" << endl;
                    break;
                }
                case 4: {
                    for(Book* b : books) {
                        if(b->GetID() >= n + a + h + s + 1) {
                            b->SetID(b->GetID() + 1);
                        }
                    }
                    Book* book;
                    book = new Science();
                    book->AddBookType();
                    book->SetID(n + a + h + s + 1);
                    books.insert(books.begin() + n + a + h + s, book);
                    cout << "Add Science Book successfully!" << endl;
                    break;
                }
                case 0:
                    cout << "Exiting!" << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
            }
            cout << endl;
        } while (book_Type > 4);
    }

    void DeleteBook() {
        int book_ID;
        cout << "Book ID need to be deleted: ";
        cin >> book_ID;
        int index;
        bool check = 0;
        for (int i=0; i < books.size(); i++) {
            if(book_ID == books[i]->GetID()) {
                index = i;
                check = 1;
                break;
            }
        }
        if(check == 1) {
            delete books[index];
            books.erase(books.begin() + index);
            for(Book* b : books) {
                if(b->GetID() > index) {
                    b->SetID(b->GetID() - 1);
                }
            }
            cout << "Delete book successfully!" << endl;
            return;
        } else {
            cout << "Book " <<book_ID << " does not exist to be deleted." << endl;
            return;
        }
    }

    ~Library() {
        for (Book* book : books) {
            delete book;
        }
        for (Member* member : members) {
            delete member;
        }
    }
};

class LibraryManagement {
private:
    Library library;

public:
    void DisplayLibraryManagement() {
        int choice;
        do {
            cout << "**********************************************" << endl;
            cout << "============= Library Management =============" << endl;
            cout << " 1. Load Books" << endl;
            cout << " 2. Display Books" << endl;
            cout << " 3. Load Members" << endl;
            cout << " 4. Display Members" << endl;
            cout << " 5. Borrow Book" << endl;
            cout << " 6. Return Book" << endl;
            cout << " 7. Add member" << endl;
            cout << " 8. Delete member" << endl;
            cout << " 9. Add book" << endl;
            cout << "10. Delete book" << endl;
            cout << " 0. Exit" << endl;
            cout << "==============================================" << endl;
            cout << "**********************************************" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    library.LoadBooks();
                    break;
                case 2:
                    library.DisplayBooks();
                    break;
                case 3:
                    library.LoadMembers();
                    break;
                case 4:
                    library.DisplayMembers();
                    break;
                case 5: 
                    library.BorrowBook();
                    break;
                case 6: 
                    library.ReturnBook();
                    break;
                case 7: 
                    library.AddMember();
                    break;
                case 8: 
                    library.DeleteMember();
                    break;
                case 9:
                    library.AddBook();
                    break;
                case 10:
                    library.DeleteBook();
                    break;
                case 0:
                    cout << "Exiting program!" << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
            }
            cout << endl;
        } while (choice != 0);
    }
};

int main() {
    LibraryManagement LibManage;
    LibManage.DisplayLibraryManagement();
    return 0;
}