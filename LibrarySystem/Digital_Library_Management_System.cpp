#include <iostream>
#include <vector>
using namespace std;

class LibraryBook
{
    public:
        string title;
        string author;      // Attributes for LibraryBook class.
        string ISBN;
        bool available;

        static int totalBooks;

        LibraryBook(string bookTitle, string bookAuthor, string bookISBN)   // Constructor.
        {
            title = bookTitle;
            author = bookAuthor;
            ISBN = bookISBN;
            available = true;
        }

        void setAvailability(bool bookAvailability) // Setter method for change the availability.
        {
            available = bookAvailability;
        }

        bool isAvailable()  // Check wheter book is available or not.
        {
            return available;
        }

        static int getTotalBooks()  // Static method to get total number of books. I define it static since return tpe is static.
        {
            return totalBooks;
        }

        void displayInfo()  // Display all attribute's of book.
        {
            cout << "Title: " << title << ", Author: " << author <<  ", ISBN: " << ISBN << ", Availavle: " << (available ? "Yes" : "No")  << endl;
        }

        ~LibraryBook()  // Destructors.
        {
            totalBooks--;
        }
};

int LibraryBook::totalBooks = 0;    // Initializing the static attribute outside the class.

//---------------------------------------------------------------------------------------------------------------

class LibraryUser
{
    public:
        string name;    // Attributes for LibraryUser abstract class.
        int userID;

    public:
        LibraryUser(string name_User, int UserID_User) : name(name_User), userID(UserID_User) {}    // Constructor.

        virtual void displayUserInfo() = 0; // Virtual function for display the user informaion.
};

//---------------------------------------------------------------------------------------------------------------

class Member : public LibraryUser
{
    private:
        vector <LibraryBook*> borrowedBooks;    // Define a variable that object of vector.

    public:

        Member(string memberName, int memberUserID) : LibraryUser(memberName, memberUserID) {} // Constructor.

        void borrowBook(LibraryBook* book)
        {
            try
            {
                if (book->isAvailable())    // Check whether book is available or not. If it is available then push it on borrowed books vector and change availability to false.
                {
                    borrowedBooks.push_back(book);
                    book->setAvailability(false);

                    cout << "Member " << name << " is borrowing \"" << book->title << "\"." << endl;
                }
                else
                {
                    throw string ("The requested book is not available");
                }
            }
            catch (const string& e)
            {
                cout << "Warning: " << e << endl;
            }
        }

        void returnBook(LibraryBook* book)
        {   
            for (int i = 0; i < borrowedBooks.size(); i++)
            {
                if (borrowedBooks[i] == book)
                {                                   // Traverse in the borrowed books vector and if given input matches with the elemen of borrowed books do it available and delete from borrowed books.      
                    book->setAvailability(true);
                    borrowedBooks.erase(borrowedBooks.begin() + i);

                    cout << "Member " << name << " returned \"" << book->title << "\"." << endl;
                    break;
                }
            }       
        }

        void displayUserInfo() override
        {
            cout << "Member: " << LibraryUser::name << ", ID: " << LibraryUser::userID << endl; // Display the member's information method that inherited from LibraryUser class.
        }   
};

//---------------------------------------------------------------------------------------------------------------

class Librarian : public LibraryUser
{
 
    public:
        Librarian(string librarianName, int librarianID) : LibraryUser(librarianName, librarianID) {}  // Constructor.

        void addBook(LibraryBook* book, vector<LibraryBook*>& books)    // Adding a given book o books vetor which is defined in LibrarySystem class. I reference book to books since add the given book without copying.
        {
            books.push_back(book);
            LibraryBook::totalBooks++;

            cout << "Adding book: " << "\"" << book->title << "\" " << "by " << book->author << ", " << "ISBN: " << book->ISBN << endl;
            cout << "Total books: " << LibraryBook::totalBooks << endl;
        }

        void removeBook(string ISBN, vector<LibraryBook*>& books)
        {
            try                                              // Traverse int he books vector and if matches the wanted ISBN remove the book from books vvector.
            {
                for (int i = 0; i < books.size(); i++)
                {
                    if (books[i]->ISBN == ISBN)
                    {
                        delete books[i];                    // Release the object from memory
                        books.erase(books.begin() + i);
                        break;
                    }
                    else
                    {
                        throw string ("There are no books matching the searched ISBN.");
                    }
                }
            }
            catch (const string& e)
            {
                cout << "Warning: " << e << endl;
            }
        }

        void displayUserInfo() override
        {
            cout << "Librarian: " << LibraryUser::name << ", ID: " << LibraryUser::userID << endl;  // Display the librarian's information method that inherited from LibraryUser class.
        }
};

//---------------------------------------------------------------------------------------------------------------

class LibrarySystem
{
    public:
        vector<LibraryBook*> books;     // Define a variables that object of vector.
        vector<LibraryUser*> users;

        LibrarySystem()
        {
            cout << "Library System Initialized." << endl;  // Constructor.
        }

        void addUser(LibraryUser* user)  // Add given user to users vector.
        {
             if (user)
            {
                users.push_back(user);  

                if (typeid(*user) == typeid(Member)) // Give output respect to user tpye.
                {
                    cout << "Adding new member: " << user->name << " (ID: " << user->userID << ")" << endl;
                }
                 else if (typeid(*user) == typeid(Librarian))
                {
                    cout << "Adding new librarian: " << user->name << " (ID: " << user->userID << ")" << endl;
                }
            }
            
        }

        LibraryBook* searchBook(string title)
        {
            int index = 0;

            if (index >= books.size())
            {   
                return NULL;                // Recursive function that search book from their name.
            }
            if (books[index]->title == title)
            {
                return books[index];
                index++;
            }
            return searchBook(title);
        }

        void displayAllBooks()
        {
            cout << "Displaying all books:" << endl;

            for (int i = 0; i < books.size(); i++)      // Display all books in books vector and their attributes.
            {
                cout << "- ";
                books[i]->displayInfo();
            }

            cout << "Total books: " << LibraryBook::getTotalBooks() << endl;
        }

        void displayAllUsers()
        {
            cout << "Displaying all users:" << endl;

            for (int i = 0; i < users.size(); i++)      // Display all users in users vector and their attributes.
            {
                cout << "- ";
                users[i]->displayUserInfo();
            }
        }

        ~LibrarySystem()    // Destructor.
        {
            for (int i = 0; i < books.size(); i++)      
            {
                delete books[i];
            }

            for (int i = 0; i < users.size(); i++)
            {
                delete users[i];
            }
        }


};

//---------------------------------------------------------------------------------------------------------------

int main()
{
    LibrarySystem library;  // Creating a object from LibrarySystem class.

    Member* member = new Member("John Doe", 101);   // Creating a object from Member class.
    Librarian* librarian = new Librarian("Sarah Smith", 102);   // Creating a object from Librarian class.

    library.addUser(member);
    library.addUser(librarian);

    LibraryBook* b1 = new LibraryBook("1984", "George Orwell", "9780451524935");    // Creating a object from LibraryBook class.
    LibraryBook* b2 = new LibraryBook("To Kill a Mockingbird", "Harper Lee", "9780060935467");

    cout << endl;

    librarian->addBook(b1, library.books);
    librarian->addBook(b2, library.books);

    cout << endl;

    member->borrowBook(b1);
    member->returnBook(b1);

    cout << endl;

    library.displayAllBooks();

    cout << endl;

    library.displayAllUsers();

    delete member;
    delete librarian;   // Delete the created objects from memory.
    delete b1;
    delete b2;

    return 0;
}