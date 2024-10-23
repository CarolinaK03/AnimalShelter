#ifndef ANIMAL_H
#define ANIMAL_H
#include <string>
using namespace std;

/*****************************************************************/
// HealthRecord Class
class HealthRecord {
    bool vaccinated;
    string medication;
    string diet;
public:
    HealthRecord();
    ~HealthRecord();
    void editInfo();
    void displayInfo() const;
    friend class Animal;
};
/*****************************************************************/
// Animal Class
class Animal {
    int id;
    char* name;
    string species;
    int age;
    int weight;
    HealthRecord healthRecord;
    Animal* next;
public:
    Animal(int id1, const char* name1, string species1, int age1, int weight1);
    ~Animal();
    int getID() const { return id; }
    const char* getName() const { return name; }
    //void setName(const char* newName);
    HealthRecord& getHealthRecord() { return healthRecord; }
    friend class AnimalShelter;
};
/*****************************************************************/
// AnimalShelter Class
class AnimalShelter {
    Animal* head;
    int animalCount;
public:
    AnimalShelter();
    ~AnimalShelter();
    void addAnimal();
    void removeAnimal(int id);
    void editAnimal(int animal_id);
    void editAnimalShelterList();
    void printList();
    int AnimalCount() const { return animalCount; }
    int& AnimalCountRef() { return animalCount; }
    void incrementAnimals() { animalCount++; }
    void editAnimalRecord(int id);
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
};
/*****************************************************************/
// Inventory Class
class Inventory {
    struct Food {
        string food_name;
        float amount_food;
        Food* next;
        Food(const string& name, float amount) : food_name(name), amount_food(amount), next(nullptr) {}
    };
    struct Meds {
        string med_name;
        float amount_meds;
        Meds* next;
        Meds(const std::string& name, float amount) : med_name(name), amount_meds(amount), next(nullptr) {}
    };

    Food* food_head;
    Meds* meds_head;
    int kennels;
public:
    Inventory();
    ~Inventory();
    void addFood(const string& name, float amount);
    void addMeds(const string& name, float amount);
    void checkInventory();
    void editInventory();
};
/*****************************************************************/

#endif // ANIMAL_H
