#include <iostream>
#include <string>
#include "archivemanager.h"
#include "exceptions.h" 

int main() {
    int optiune;
    std::string fisier;

    while (true) {
        std::cout << "        MENIU COMPRESIE DATE          \n";
        std::cout << " 1. Arhiveaza folosind Huffman\n";
        std::cout << " 2. Arhiveaza folosind LZW\n";
        std::cout << " 3. Arhiveaza folosind cea mai buna\n";
        std::cout << " 4. Dezarhiveaza un fisier (.bin)\n";
        std::cout << " 5. Afiseaza statistici si IESI\n";
        // std::cout << " Alege o optiune (1-5): ";
        std::cin >> optiune;
        if(std::cin.eof()) {
            break;
        }
        if (optiune == 5) {
            std::cout << ArchiveManager::getbytese() << '\n';
            std::cout << "Iesire din program. O zi buna!\n";
            break;
        }

        try {
            if (optiune >= 1 && optiune <= 3) {
                std::cout << " Numele fisierului pentru arhivare (ex: test.txt): ";
                std::cin >> fisier;
                
                ArchiveManager manager(optiune); 
                std::cin.get();
                std:: cout << "Parola, lasa liber daca nu vrei sa fie parolat ";
                std::string parola;
                std::getline(std::cin, parola);
                manager.compress(fisier, parola);
                
                std::cout << "\nCompresie finalizata!\n";
            } 
            else if (optiune == 4) {
                std::cout << " Numele fisierului binar (ex: arhiva.bin): ";
                std::cin >> fisier;
                
                ArchiveManager manager(0); 
                std::cin.get();
                std::cout << "Parola, lasa liber daca stii ca nu are parola: ";
                std::string parola; std::getline(std::cin, parola);
                manager.decompress(fisier, parola);
                
                std::cout << "\nDecompresie finalizata!\n";
            } 
            else {
                std::cout << "Optiune invalida!.\n";
            }
        } 
        catch (const ArchiveException& e) {
            std::cerr << "\nEROARE DE ARHIVARE: " << e.what() << "\n";
        } 
        catch (const std::exception& e) {
            std::cerr << "EROARE SISTEM: " << e.what() << "\n";
        }
    }

    return 0;
}