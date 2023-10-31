#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>

using namespace std;

int main() {
        int choice;
        // MENU
        cout << "------------------\n";
        cout << "Executar o arquivo\n 1- Arquivo 16b\n 2- Arquivo 32b\n";
        cout << "------------------\n";
        cin >> choice;

        // EXECUTA ARQUIVO 16b
    if (choice == 1) {
        string line;
        ifstream addressFile("addresses_16b.txt");
        ifstream dataFile("data_memory.txt");

        if (addressFile.is_open() && dataFile.is_open()) {
            while (getline(addressFile, line)) {
                unsigned int address;

                if (istringstream(line) >> address) {
                    cout << "Endereço: " << address << endl;

                    bitset<16> bs2(address);
                    cout << "Binario:  " << bs2 << endl;

                    unsigned int pageNumber = (address >> 12); // Obtem os 4 primeiros bits
                    cout << "Numero da pagina: " << pageNumber << endl;

                    unsigned int offset = (address & 0x0FFF); // Máscara para manter 12 bits do deslocamento
                    cout << "Deslocamento: " << offset << endl;

                    // Busca na posição do arquivo de dados
                    dataFile.seekg(offset * sizeof(int));

                    unsigned int value;
                    dataFile >> value;
                    cout << "Valor lido: " << value << endl;

                    cout << endl;
                } else {
                    cout << "Endereco invalido: " << line << endl;
                }
            }
            addressFile.close();
            dataFile.close();
        } else {
            cout << "Não foi possivel abrir nenhum arquivo." << endl;
        }

        // EXECUTA ARQUIVO 32b
    } else if (choice == 2) {
        string line;
        ifstream addressFile("addresses_32b.txt");
        ifstream dataFile("data_memory.txt");

        if (addressFile.is_open() && dataFile.is_open()) {
            while (getline(addressFile, line)) {
                unsigned int address;

                if (istringstream(line) >> address) {
                    cout << "Endereço: " << address << endl;

                    bitset<32> bs2(address);
                    cout << "Binario:  " << bs2 << endl;

                    unsigned int firstLevelMask = 0xFFC00000; // Máscara para os primeiros 10 bits
                    unsigned int secondLevelMask = 0x003FF000; // Máscara para os próximos 10 bits

                    // Cálculo do índice de cada nível
                    unsigned int firstLevelIndex = (address & firstLevelMask) >> 12;
                    unsigned int secondLevelIndex = (address & secondLevelMask) >> 12;

                    cout << "Primeiro nivel: " << firstLevelIndex << endl;
                    cout << "Segundo nivel: " << secondLevelIndex << endl;

                    unsigned int offset = (address & 0xFFF); // Máscara para os últimos 12 bits
                    cout << "Deslocamento: " << offset << endl;

                    unsigned int value = 0;

                    // Busca do valor no arquivo de dados
                    dataFile.seekg((firstLevelIndex * 1024 + secondLevelIndex) * sizeof(int)); // Cada nível com 10 bits representa 1024 páginas de 4KB

                    dataFile >> value;
                    cout << "Valor lido: " << value << endl;

                    cout << endl;
                } else {
                    cout << "Endereço invalido: " << line << endl;
                }
            }
            addressFile.close();
            dataFile.close();
        } else {
            cout << "Não foi possivel abrir nenhum arquivo." << endl;
        }

    } else {
        cout << endl << "Numero invalido! Digite entre 1 e 2.";
    }


    return 0;
}
