#include <iostream>
#include <vector>
#include<string>

class book {

    public:
        std::string title;
        std::string author;
        int isbn;
        int quantity;

        bool operator==(const book& other) const {
            return this->isbn == other.isbn;
        }

        book(const std::string& title, const std::string& author, int isbn, int quantity)
            : title(title), author(author), isbn(isbn), quantity(quantity) {

            std::cout << "Book " << this->title << " inserted!";
        }

        void showBook() const{
            std::cout << this->title << " --- " << this->author << " --- " << this->isbn << " --- " << this->quantity << "\n";
        };

        void returnBook() {
            this->quantity += 1;
        };

        void borrowBook() {
            this->quantity -= 1;
        };
};

book* locate(std::vector<book>& catalogue) {
    int selected;
    std::cout << "Type in the ISBN of the book you wish to select: ";
    std::cin >> selected;

    auto i = std::find_if(catalogue.begin(), catalogue.end(), [selected](const book& b) {
        return b.isbn == selected;
        });

    if (i != catalogue.end()) {
        return &(*i);
    }

    std::cout << "Book not found, please check its ISBN again.\n";
    return nullptr;
}


std::string getString() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void deleteBook(std::vector<book>& catalogue) {

    book* bookSelected = locate(catalogue);
    if (bookSelected) {
        auto b = std::find(catalogue.begin(), catalogue.end(), *bookSelected);
        if (b != catalogue.end()) {
            catalogue.erase(b);
            std::cout << "Book " << bookSelected->title << " deleted from the catalogue.\n";
        }
        else {
            std::cout << "Book not found in the catalogue.\n";
        }
    }
};

class user {

private:
    std::string username;
    std::string password;
    std::vector<int>booksRented;

public:
    user(const std::string& username, const std::string& password)
        : username(username), password(password) {

        std::cout << "User " << this->username << " created!\n";
    }

    void userRentBook(book* bookSelected) {

        if (bookSelected && bookSelected->quantity > 0) {
            this->booksRented.push_back(bookSelected->isbn);
            bookSelected->borrowBook();
            std::cout << "Book " << bookSelected->title << " borrowed by " << this->username << "\n";
        }
        else {
            std::cout << "Book not available or not found.\n";
        }
    }

    void userReturnBook(book* bookSelected) {

        if (bookSelected) {

            auto isbn = std::find(booksRented.begin(), booksRented.end(), bookSelected->isbn);

            if (isbn != booksRented.end()) {

                booksRented.erase(isbn);
                std::cout << "Book " << bookSelected->title << " returned by " << this->username << "\n";
                bookSelected->returnBook();
            }
            else {
                std::cout << "You haven't borrowed " << bookSelected->title << ".\n";
            }
        }
    }
};

void show(const std::vector<book>& catalogue) {

    for (const book& b : catalogue) {
        b.showBook();
    }
};

int main(){

    int option;
    bool exit = false;
    std::vector<book> catalogue;

    std::cout << "[ Library managment services ]\n";
    std::cout << "Type in your username: ";
    std::string newName = getString();
    std::cout << "Type in your password: ";
    std::string newPassword = getString();

    user newUser(newName, newPassword); 

    while (!exit) {

        std::cout << "1.Add a Book\n" << "2.Remove a Book\n" << "3.Display Books\n" << "4.Search for a Book\n" << "5.Borrow Book\n" <<
            "6.Return a Book\n" << "[ANY OTHER KEY].Exit\nPlease Select an option:";

        std::cin >> option;

        switch (option) {
            
        case 1: {
            int bookIsbn;
            int bookQuantity;
            std::cin.ignore();
            std::cout << "Type in the book's title: ";
            std::string bookTitle = getString();
            std::cout << "Type in the book's author: ";
            std::string bookAuthor = getString();
            std::cout << "Type in the book's isbn: ";
            std::cin >> bookIsbn;
            std::cout << "Type in the book's quantity: ";
            std::cin >> bookQuantity;

            //catalogue.push_back(newBook); 
            // DIRECLTY CREATES OBJECT IN VECTOR USING THE CONSTRUCTOR
            catalogue.emplace_back(bookTitle, bookAuthor, bookIsbn, bookQuantity);
            //braces in switch case for proper variable initializations
        }
            break;

        case 2:
            deleteBook(catalogue);
            break;

        case 3:
            show(catalogue);
            break;

        case 4:
            locate(catalogue);
            break;

        case 5:
            newUser.userRentBook(locate(catalogue));
            break;

        case 6:
            newUser.userReturnBook(locate(catalogue));
            break;

        default:
            std::cout << "Finishing program.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            exit = true;
            break;
        };
    };
    return 0;
}