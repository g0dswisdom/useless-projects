#include <iostream>;
#include <string>;
#include <fstream>;
bool hasCar(const std::string& car) {
    std::ifstream cars("./owned.txt");
    std::string existingCar;

    while (std::getline(cars, existingCar)) {
        if (existingCar == car) {
            //std::cout << "You already have the " << existingCar << " !" << std::endl;
            cars.close();
            return true;
        }
    }

    cars.close();
    return false;
}

void dealership() {
    int car;
    std::cout << "Welcome to the car dealership. Which car would you like to buy?" << std::endl;
    std::cout << "\n--------- CARS ---------\n";
    std::cout << "\nFord F-150 (1)\nLamborghini (2)\nVolkswagen (3)" << std::endl;
    std::cout << "\n--------- PAYMENT ---------\n\nWhich car would you like to buy? Type the car's number: ";

    std::ofstream cars("./owned.txt", std::ios_base::app);
    if (cars.is_open()) {
        std::cin >> car;
        std::string carName;
        switch (car)
        {
        case 1:
            carName = "Ford F-150";
            break;
        case 2:
            carName = "Lamborghini";
        case 3:
            carName = "Volkswagen";
        default:
            break;
        }
        if (hasCar(carName)) {
            std::cout << "You already have the " << carName << "!" << std::endl;
        }
        else {
            cars << "\n" << carName << std::endl;
        }
    }
}

void inventory() {
    std::cout << "--------- INVENTORY ---------\n";
    std::ifstream cars("owned.txt");
    std::string car;

    while (std::getline(cars, car)) {
        std::cout << car << std::endl;
    }

    cars.close();
}

int main() {
    std::ifstream cars;
    cars.open("./cars.txt");

    std::string car;
    std::string check;
    std::cout << "Hello. Type 1 to enter the car dealership and type 2 to look at your inventory: ";
    std::cin >> check;
    if (check == "1") {
        system("cls");
        dealership();
    }
    else {
        inventory();
    }
}
