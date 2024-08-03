#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Define the Contact structure
struct Contact {
    string name;
    string phoneNumber;
    string email;
};

// Function to load contacts from a file
void loadContacts(vector<Contact>& contacts, const string& filename) {
    ifstream file(filename.c_str()); // Convert string to const char*
    if (!file.is_open()) {
        cout << "Warning: Unable to open file " << filename << ". Starting with an empty list." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Contact contact;
        contact.name = line;
        if (getline(file, contact.phoneNumber) && getline(file, contact.email)) {
            contacts.push_back(contact);
        }
    }
    file.close();
}

// Function to save contacts to a file
void saveContacts(const vector<Contact>& contacts, const string& filename) {
    ofstream file(filename.c_str()); // Convert string to const char*
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing." << endl;
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        file << contacts[i].name << endl;
        file << contacts[i].phoneNumber << endl;
        file << contacts[i].email << endl;
    }
    
    file.close();
}


// Function to add a contact
void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "Enter name: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, newContact.name);
    cout << "Enter phone number: ";
    getline(cin, newContact.phoneNumber);
    cout << "Enter email: ";
    getline(cin, newContact.email);

    contacts.push_back(newContact);
    cout << "Contact added successfully!" << endl;
}

// Function to display all contacts
void displayContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts available." << endl;
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << "Contact #" << (i + 1) << endl;
        cout << "Name: " << contacts[i].name << endl;
        cout << "Phone Number: " << contacts[i].phoneNumber << endl;
        cout << "Email: " << contacts[i].email << endl;
        cout << "-------------------------" << endl;
    }
}

// Function to delete a contact
void deleteContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts available to delete." << endl;
        return;
    }

    int index;
    cout << "Enter the contact number to delete: ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number." << endl;
        return;
    }

    contacts.erase(contacts.begin() + index - 1);
    cout << "Contact deleted successfully!" << endl;
}

// Function to edit a contact
void editContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts available to edit." << endl;
        return;
    }

    int index;
    cout << "Enter the contact number to edit: ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number." << endl;
        return;
    }

    cin.ignore(); // Ignore leftover newline characters
    --index; // Adjust index for zero-based vector indexing

    Contact& contact = contacts[index];

    cout << "Editing contact #" << (index + 1) << endl;

    cout << "Enter new name (or press Enter to keep \"" << contact.name << "\"): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty()) {
        contact.name = newName;
    }

    cout << "Enter new phone number (or press Enter to keep \"" << contact.phoneNumber << "\"): ";
    string newPhoneNumber;
    getline(cin, newPhoneNumber);
    if (!newPhoneNumber.empty()) {
        contact.phoneNumber = newPhoneNumber;
    }

    cout << "Enter new email (or press Enter to keep \"" << contact.email << "\"): ";
    string newEmail;
    getline(cin, newEmail);
    if (!newEmail.empty()) {
        contact.email = newEmail;
    }

    cout << "Contact updated successfully!" << endl;
}

// Main function with menu
int main() {
    vector<Contact> contacts;
    loadContacts(contacts, "contacts.txt"); // Load contacts from file

    int choice;

    while (true) {
        cout << "Contact Management System" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Display Contacts" << endl;
        cout << "3. Delete Contact" << endl;
        cout << "4. Edit Contact" << endl;
        cout << "5. Save and Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                displayContacts(contacts);
                break;
            case 3:
                deleteContact(contacts);
                break;
            case 4:
                editContact(contacts);
                break;
            case 5:
                saveContacts(contacts, "contacts.txt");
                cout << "Contacts saved. Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }
}

