
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

void printMenu() {
    std::cout << "\nLASD Libraries 2025 - Menu dei Test" << std::endl;
    std::cout << "1. Esercizi 1 & 2 - Test del Professore" << std::endl;
    std::cout << "2. Esercizio 1 - Miei Test Personali" << std::endl;
    std::cout << "3. Esercizio 2 - Miei Test Personali (Non ancora implementati)" << std::endl;
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
                std::cout << "\nEsecuzione Test del Professore per Esercizi 1 & 2..." << std::endl;
                lasdtest(); // Esegue i test di entrambi gli esercizi
                break;
            case 2:
                std::cout << "\nEsecuzione Test Personali - Esercizio 1..." << std::endl;
                mytest(); // Test personali per l'Esercizio 1
                break;
            case 3:
                std::cout << "\nEsecuzione Test Personali - Esercizio 2..." << std::endl;
                std::cout << "Non ancora implementati" << std::endl;
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