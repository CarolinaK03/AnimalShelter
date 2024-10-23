#include "Animal.h"
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

/*****************************************************************/
// Animal Methods
Animal::Animal(int id1, const char* name1, string species1, int age1, int weight1) {
    id = id1;
    name = new char[strlen(name1) + 1];
    strcpy(name, name1);
    species = species1;
    age = age1;
    weight = weight1;
    next = nullptr;
}
Animal::~Animal() {
    delete[] name;
}
/*****************************************************************/
// HealthRecord Methods
HealthRecord::HealthRecord() : vaccinated(false), medication("None"), diet("Standard") {}
HealthRecord::~HealthRecord() {}

void HealthRecord::editInfo() {
    char choice;
    do {
        cout << "Edit Health Record Menu: " << endl;
        cout << "1. Vaccination Status" << endl;
        cout << "2. Medications " << endl;
        cout << "3. Diet" << endl;
        cout << "4. Done" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                char vacc;
                cout << "Is the animal vaccinated? (y/n): ";
                cin >> vacc;
                vaccinated= (vacc == 'y' || vacc == 'Y');
                break;
            }
            case '2': {
                cout << "Medications the animal is taking: ";
                cin.ignore(); 
                getline(cin, medication);
                break;
            }
            case '3': {
                cout << "Dietary Restrictions: ";
                cin.ignore(); 
                getline(cin, diet);
                break;
            }
            case '4':
                cout << "Health Record Updates finished..." << endl;
                break;
            default:
                cout << "Invalid choice, please choose a digit from 1-4." << endl;
        }
    } while (choice != '4');
}

void HealthRecord::displayInfo() const {
    cout << "Vaccinated: " << (vaccinated ? "Yes" : "No") << endl;
    cout << "Medication: " << medication << endl;
    cout << "Diet: " << diet << endl;
}

/*****************************************************************/
// AnimalShelter Methods
AnimalShelter::AnimalShelter() : head(nullptr), animalCount(0) {}
AnimalShelter::~AnimalShelter() {
    while (head) {
        Animal* temp = head;
        head = head->next;
        delete temp;
    }
}

void AnimalShelter::addAnimal() {
    char name[50];
    string species;
    int age, weight;
    cout << "Enter Animal Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Enter Species: ";
    cin.ignore();
    getline(cin, species);
    cout << "Enter Age (in years): ";
    cin >> age;
    cout << "Enter Weight (in kg): ";
    cin >> weight;

    int id = 1 + ++animalCount; // issue with id generation, added 1
    Animal* newAnimal = new Animal(id, name, species, age, weight);
    newAnimal->next = head;
    head = newAnimal;
    cout << "Animal added successfully. ID: " << id << endl;
    cout << '\n' << endl;

}

void AnimalShelter::removeAnimal(int id) {
    Animal* current = head;
    Animal* previous = nullptr;

    while (current!=nullptr && (current->getID()!=id)) {
        previous = current;
        current = current->next;
    }
    if (current == nullptr) {
        cout << "Animal not found..." << endl;
        return;
    }
    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;
    cout << "Animal removed successfully..." << endl;
    cout << '\n' << endl;
}

void AnimalShelter::editAnimal(int id) {
    Animal* current = head;

    while (current != nullptr && current->getID() != id) {
        current = current->next;
    }
    if (current == nullptr) {
        cout << "Animal not found..." << endl;
        return;
    }

    char choice;
    do {
        cout << '\n' << endl;
        cout << "********************************" << endl;
        cout << "Edit Menu: " << endl;
        cout << "1. Name" << endl;
        cout << "2. Species" << endl;
        cout << "3. Age" << endl;
        cout << "4. Weight" << endl;
        cout << "5. Done" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cout << "................................" << endl;

        switch (choice) {
            case '1': {
                char newName[50];
                cout << "Enter new name: ";
                cin >> newName;
                delete[] current->name;
                current->name = new char[strlen(newName) + 1];
                strcpy(current->name, newName);
                break;
            }
            case '2': {
                string newSpecies;
                cout << "Enter new species: ";
                cin.ignore();
                getline(cin, newSpecies);
                current->species = newSpecies;
                break;
            }
            case '3': {
                int newAge;
                cout << "Enter new age: ";
                cin >> newAge;
                current->age = newAge;
                break;
            }
            case '4': {
                int newWeight;
                cout << "Enter new weight: ";
                cin >> newWeight;
                current->weight = newWeight;
                break;
            }
            case '5':
                cout << "Finished editing." << endl;
                break;
            default:
                cout << "Invalid choice, please select a valid number." << endl;
        }
    } while (choice != '5');
}

void AnimalShelter::editAnimalShelterList() {
    char choice;
    static int totalAnimals = 0;
    
    do {
        cout << '\n' << endl;
        cout << "********************************" << endl;
        cout << "Edit Animal Shelter List Menu: " << endl;
        cout << "1. Add Animal" << endl;
        cout << "2. Remove Animal" << endl;
        cout << "3. Edit Animal Details" << endl;
        cout << "4. Done" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                int id = totalAnimals + 1;
                totalAnimals++; 
                addAnimal();
                break;
            }
            case '2': {
                int id;
                cout << "Enter ID of the animal to remove: ";
                cin >> id;
                removeAnimal(id);
                break;
            }
            case '3': {
                int id;
                cout << "Enter ID of the animal to edit: ";
                cin >> id;
                editAnimal(id);
                break;
            }
            case '4':
                cout << "Finished editing animal shelter list..." << endl;
                break;
            default:
                cout << "Invalid choice, please choose a valid number." << endl;
        }
    } while (choice != '4');
}

void AnimalShelter::printList() {
    Animal* current = head;
    cout << '\n';
    cout << "********************************" << endl;
    cout << "Animal Shelter List:" << endl;
    cout << '\n';
    while (current) {
        cout << "ID: " << current->getID() << endl;
        cout << "Name: " << current->getName() << endl;
        cout << "Species: " << current->species << endl;
        cout<< "Age (years): " << current->age << endl;
        cout<< "Weight (kg): " << current->weight << endl;
        cout << '\n';
        current = current->next;
    }
    cout << "********************************" << endl;
}

void AnimalShelter::editAnimalRecord(int id) {
    Animal* current = head;

    while (current != nullptr && current->getID() != id) {
        current = current->next;
    }
    if (current == nullptr) {
        cout << "Animal not found." << endl;
        return;
    }
    current->getHealthRecord().editInfo();
}

void AnimalShelter::saveToFile(const string& filename) {

    ofstream outFile(filename, ios::binary);

    if (!outFile) {
        cout << "No file to open..." << endl;
        return;
    }

    Animal* current = head;

    while (current) {
        int id = current->id;
        size_t nameLength = strlen(current->name) + 1;
        string species = current->species;
        int age = current->age;
        int weight = current->weight;

        outFile.write(reinterpret_cast<char*>(&id), sizeof(id));
        outFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

        outFile.write(current->name, nameLength);
        size_t speciesLength = species.size() + 1;
        outFile.write(reinterpret_cast<char*>(&speciesLength), sizeof(speciesLength));
        outFile.write(species.c_str(), speciesLength);
        outFile.write(reinterpret_cast<char*>(&age), sizeof(age));
        outFile.write(reinterpret_cast<char*>(&weight), sizeof(weight));

        current = current->next;
    }
    outFile.close();
    //cout << "Animal list saved successfully..." << endl;
}

void AnimalShelter::loadFromFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cout << "No file to read..." << endl;
        return;
    }

    while (inFile.peek() != EOF) {
        int id;
        size_t nameLength;
        char name[50];
        size_t speciesLength;
        char species[50];
        int age;
        int weight;

        inFile.read(reinterpret_cast<char*>(&id), sizeof(id));
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        inFile.read(name, nameLength);
        inFile.read(reinterpret_cast<char*>(&speciesLength), sizeof(speciesLength));
        inFile.read(species, speciesLength);
        inFile.read(reinterpret_cast<char*>(&age), sizeof(age));
        inFile.read(reinterpret_cast<char*>(&weight), sizeof(weight));

        Animal* newAnimal = new Animal(id, name, species, age, weight);
        newAnimal->next = head;
        head = newAnimal;
        animalCount = id; 
    }

    inFile.close();
    //cout << "Animal list loaded successfully." << endl;
}

/*****************************************************************/
// Inventory Methods
Inventory::Inventory(): food_head(nullptr), meds_head(nullptr), kennels(0){}
Inventory::~Inventory() {
    while (food_head) {
        Food* temp = food_head;
        food_head = food_head->next;
        delete temp;
    }
    while (meds_head) {
        Meds* temp = meds_head;
        meds_head = meds_head->next;
        delete temp;
    }
}

void Inventory::addFood(const string& name, float amount) {
    Food* newFood = new Food(name, amount);
    newFood->next = food_head;
    food_head = newFood;
}
void Inventory::addMeds(const string& name, float amount) {
    Meds* newMeds = new Meds(name, amount);
    newMeds->next = meds_head;
    meds_head = newMeds;
}
//merge 

void Inventory::checkInventory() {
    cout << '\n';
    cout << "********************************" << endl;
    cout << "Food Inventory:" << endl;
    Food* currentFood = food_head;
    
    while (currentFood) {
        cout << "Food Name: " << currentFood->food_name << ", Amount: " << currentFood->amount_food << " kgs" << endl;
        currentFood = currentFood->next;
    }

    cout << "\nMedication Inventory:" << endl;
    Meds* currentMeds = meds_head;
    while (currentMeds) {
        cout << "Medication Name: " << currentMeds->med_name << ", Amount: " << currentMeds->amount_meds << " bottles" << endl;
        currentMeds = currentMeds->next;
    }
    cout << "\nKennels: " << kennels << endl;
    cout << "********************************" << endl;

}

void Inventory::editInventory() {
    char choice;
    do {
        cout << '\n';
        cout << "********************************" << endl;
        cout << "Edit Inventory Menu: " << endl;
        cout << "1. Add Food" << endl;
        cout << "2. Add Medication" << endl;
        cout << "3. Update Food Amount" << endl;
        cout << "4. Update Medication Amount" << endl;
        cout << "5. Update Kennels" << endl;
        cout << "6. Done" << endl;
        cout << "Enter choice: "  << endl;
        cin >> choice;

        switch (choice) {
            case '1': {
                string name;
                float amount;
                cout << "Enter food name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter amount (in kgs): ";
                cin >> amount;
                addFood(name, amount);
                break;
            }
            case '2': {
                string name;
                float amount;
                cout << "Enter medication name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter amount (in bottles): ";
                cin >> amount;
                addMeds(name, amount);
                break;
            }
            case '3': {
                string name;
                float amount;
                cout << "Enter food name to update: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter new amount (in kgs): ";
                cin >> amount;
                Food* currentFood = food_head;
                while (currentFood) {
                    if (currentFood->food_name == name) {
                        currentFood->amount_food = amount;
                        break;
                    }
                    currentFood = currentFood->next;
                }
                if (!currentFood) {
                    cout << "Food item not availible, maybe try adding it to the list." << endl;
                }
                break;
            }
            case '4': {
                string name;
                float amount;
                cout << "Enter medication name to update: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter new amount (in bottles): ";
                cin >> amount;
                Meds* currentMeds = meds_head;
                while (currentMeds) {
                    if (currentMeds->med_name == name) {
                        currentMeds->amount_meds = amount;
                        break;
                    }
                    currentMeds = currentMeds->next;
                }
                if (!currentMeds) {
                    cout << "Medication not availble, maybe try adding it to the list." << endl;
                }
                break;
            }
            case '5': {
                int newKennels;
                cout << "Enter new number of kennels: ";
                cin >> newKennels;
                kennels = newKennels;
                break;
            }
            case '6':
                cout << "Finished editing inventory..." << endl;
                break;
            default:
                cout << "Invalid choice, please pick a valid number." << endl;
        }
    } while (choice != '6');
}