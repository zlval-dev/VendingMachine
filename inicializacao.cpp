#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "inicializacao.h"
#include "cores.h"

using namespace std;

// Tamanho da maquina (entre 9 e 12)
int* tamanho(){
    int* aux = new int[1];
    aux[0] = rand() % 4 + 9;
    return aux;
}

// Capacidade de cada slot (entre 5 e 10)
int* capacidade(int tamanhoMaquina){
    int* aux;
    aux = new int[tamanhoMaquina];
    for(int i = 0; i < tamanhoMaquina; i++){
        aux[i] = rand() % 6 + 5;
    }
    return aux;
}

// Valor da Caixa (cada moeda entre 10 e 20)
int* valor(){
    int* aux = new int[6];
    for(int i = 0; i < 6; i++){
        aux[i] = rand() % 11 + 10;
    }
    return aux;
}

// Numero de linhas do ficheiro de produtos
int numeroLinhas(){
    ifstream myFile("produtos.txt");
    string line;
    if(myFile.is_open()){
        int numeroLinha = 0;
        while(!myFile.eof()){
            getline(myFile, line);
            numeroLinha++;
        }
        myFile.close();
        return numeroLinha;
    }
}

int numeroLinhasProdutos = numeroLinhas();
// Função para obter todos os produtos num array
string* todosProdutos(){
    string* aux;
    aux = new string[numeroLinhasProdutos];
    ifstream myFile("produtos.txt");
    string line;
    if(myFile.is_open()){
        int numeroLinha = 0;
        while(!myFile.eof()){
            getline(myFile, line);
            aux[numeroLinha] = line;
            numeroLinha++;
        }
        myFile.close();
    }
    return aux;
}

// Função para não obter produtos repetidos
int obterNovoProduto(int* numeroArrayProdutos, int tamanhoMaquina){
    int novoProduto = rand() % numeroLinhasProdutos;
    bool existe = false;
    for(int i = 0; i < tamanhoMaquina; i++){
        if(novoProduto == numeroArrayProdutos[i]){
            existe = true;
            break;
        }
    }
    if(existe){
        obterNovoProduto(numeroArrayProdutos, tamanhoMaquina);
    }else{
        return novoProduto;
    }
}

// Numero de linhas do ficheiro de preços
int numeroPrecos(){
    ifstream myFile("precos.txt");
    string line;
    if(myFile.is_open()){
        int numeroLinha = 0;
        while(!myFile.eof()){
            getline(myFile, line);
            numeroLinha++;
        }
        myFile.close();
        return numeroLinha;
    }
}

int numeroLinhasPrecos = numeroPrecos();
// Função para obter todos os precos num array
string* todosPrecos(){
    string* aux;
    aux = new string[numeroLinhasPrecos];
    ifstream myFile("precos.txt");
    string line;
    if(myFile.is_open()){
        int numeroLinha = 0;
        while(!myFile.eof()){
            getline(myFile, line);
            aux[numeroLinha] = line;
            numeroLinha++;
        }
        myFile.close();
    }
    return aux;
}

string* precos = todosPrecos();
// Funcao para obter valor do produto
string obtemValor(){
    return precos[rand() % numeroLinhasPrecos];
}

// Função para obter os produtos iniciais da maquina (sem haver repetidos)
string** obterProdutos(int tamanhoMaquina){
    string** aux;
    aux = new string*[tamanhoMaquina];
    for(int i = 0; i < tamanhoMaquina; i++){
        aux[i] = new string[2];
    }
    string* produtos = todosProdutos();
    int* numeroArrayProdutos;
    numeroArrayProdutos = new int[tamanhoMaquina];
    for(int i = 0; i < tamanhoMaquina; i++){
        numeroArrayProdutos[i] = obterNovoProduto(numeroArrayProdutos, tamanhoMaquina);
        aux[i][0] = produtos[numeroArrayProdutos[i]];
        aux[i][1] = obtemValor();
    }
    delete[] produtos;
    delete[] numeroArrayProdutos;
    return aux;
}

// Função para criar um novo array de quantidades de produtos com os mesmos valores da capacidade
int* quantidade(int* capacidadeProduto, int tamanhoMaquina){
    int* aux = new int[tamanhoMaquina];
    for(int i = 0; i < tamanhoMaquina; i++){
        aux[i] = capacidadeProduto[i];
    }
    return aux;
}

// Função para imprimir seguindo o modelo e devolve a tecla escolhida pelo utilizador
string imprimirInformacoes(int tamanhoMaquina, int* capacidadeSlots, string** produtos, int* quantidadeProduto, int* valorCaixa){
    char slot = 'A';
    string tecla;
    for(int i = 0; i < tamanhoMaquina; i++){
        cout << ANSI_COLOR_BOLD << "Slot: " << ANSI_COLOR_RESET << slot++ << endl;
        if(quantidadeProduto[i] > 0){
            cout << ANSI_COLOR_BOLD << "Produto: " << ANSI_COLOR_RESET << produtos[i][0] << endl;
            cout << ANSI_COLOR_BOLD << "Preço: " << ANSI_COLOR_RESET << produtos[i][1] << "€" << endl;
        }else{
            cout << ANSI_COLOR_BOLD << "Produto: " << ANSI_COLOR_RESET << "Vazio" << endl;
            cout << ANSI_COLOR_BOLD << "Preço: " << ANSI_COLOR_RESET << "0" << endl;
        }
        cout << ANSI_COLOR_BOLD << "Quantidade: " << ANSI_COLOR_RESET << quantidadeProduto[i] << ANSI_COLOR_BOLD << "\t| Capacidade: " << ANSI_COLOR_RESET << capacidadeSlots[i] << endl;
        cout << ANSI_COLOR_BLUE << "-------------------------------" << ANSI_COLOR_RESET << endl;
    }
    // Imprimir informação de quando tem poucas moedas na máquina
    if(valorCaixa[5] <= 3){
        cout << ANSI_COLOR_RED << "*** Atenção existem apenas " << valorCaixa[5] << " moedas de 2 euros ***" << ANSI_COLOR_RESET << endl;
    }if(valorCaixa[4] <= 3){
        cout << ANSI_COLOR_RED << "*** Atenção existem apenas " << valorCaixa[4] << " moedas de 1 euro ***" << ANSI_COLOR_RESET << endl;
    }if(valorCaixa[3] <= 3){
        cout << ANSI_COLOR_RED << "*** Atenção existem apenas " << valorCaixa[3] << " moedas de 50 cêntimos ***" << ANSI_COLOR_RESET << endl;
    }if(valorCaixa[2] <= 3){
        cout << ANSI_COLOR_RED << "*** Atenção existem apenas " << valorCaixa[2] << " moedas de 20 cêntimos ***" << ANSI_COLOR_RESET << endl;
    }if(valorCaixa[1] <= 3){
        cout << ANSI_COLOR_RED << "*** Atenção existem apenas " << valorCaixa[1] << " moedas de 10 cêntimos ***" << ANSI_COLOR_RESET << endl;
    }if(valorCaixa[0] <= 3){
        cout << ANSI_COLOR_RED << "*** Atenção existem apenas " << valorCaixa[0] << " moedas de 5 cêntimos ***" << ANSI_COLOR_RESET << endl;
    }
    cout << ANSI_COLOR_YELLOW << "(c)" << ANSI_COLOR_RESET << "liente\t**********\t" << ANSI_COLOR_YELLOW << "(f)" << ANSI_COLOR_RESET << "uncionário\n";
    cout << ANSI_COLOR_BOLD << "Selecione a sua opção: " << ANSI_COLOR_RESET;
    getline(cin, tecla);
    while(!(tecla == "f" || tecla == "c")){
        cout << ANSI_COLOR_BLUE << "-------------------------------" << ANSI_COLOR_RESET << endl;
        cout << ANSI_COLOR_RED << "Opção inserida incorreta!\n" << ANSI_COLOR_RESET;
        cout << ANSI_COLOR_YELLOW << "(c)" << ANSI_COLOR_RESET << "liente\t**********\t" << ANSI_COLOR_YELLOW << "(f)" << ANSI_COLOR_RESET << "uncionário\n";
        cout << ANSI_COLOR_BOLD << "Selecione a sua opção: " << ANSI_COLOR_RESET;
        getline(cin, tecla);
    }
    return tecla;
}