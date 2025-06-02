
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

void printMenu() {
    std::cout << "\n~*~#~*~ LASD Libraries 2025 - Menu dei Test ~*~#~*" << std::endl;
    std::cout << "1. Esercizi 1 & 2 - Test di default" << std::endl;
    std::cout << "2. Test Personali" << std::endl;
    std::cout << "0. Esci" << std::endl;
    std::cout << "Seleziona un'opzione: ";
}

int main() {
    int choice;
    
    do {
        printMenu();
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                std::cout << "\nEsecuzione Test di default per Esercizi 1 & 2..." << std::endl;
                lasdtest(); // Esegue i test di entrambi gli esercizi
                break;
            case 2:
                std::cout << "\nEsecuzione Test Personali..." << std::endl;
                mytest(); // Test personali unificati
                break;
            case 0:
                std::cout << "\nUscita dal programma..." << std::endl;
                break;
            default:
                std::cout << "\nOpzione non valida! Riprova." << std::endl;
        }
    } while (choice != 0);

    return 0;
}