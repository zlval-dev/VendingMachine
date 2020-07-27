#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <algorithm>
#include "cliente.h"
#include "cores.h"

using namespace std;

// Função para obter a quantidade de moedas e verificação se o utilizador introduziu inteiro
int obterQuantidadeMoedas(int caso){
    string moeda;
    switch(caso){
        case 1:
            moeda = "2 euros: ";
            break;
        case 2:
            moeda = "1 euros: ";
            break;
        case 3:
            moeda = "50 cêntimos: ";
            break;
        case 4:
            moeda = "20 cêntimos: ";
            break;
        case 5:
            moeda = "10 cêntimos: ";
            break;
        case 6:
            moeda = "5 cêntimos: ";
            break;
    }
    cout << ANSI_COLOR_BOLD << "Introduza a quantidade de moedas de " << moeda << ANSI_COLOR_RESET;
    string quantidade;
    getline(cin, quantidade);
    if(!quantidade.find_first_not_of("0123456789")){
        cout << ANSI_COLOR_RED << "Não foi introduzido um inteiro!" << ANSI_COLOR_RESET << endl;
        obterQuantidadeMoedas(caso);
    }else{
        return stoi(quantidade);
    }
}

// Função para verificar se o valor introduzido pelo utilizador é sufeciente para comprar o produto
bool verificaValor(float valorUtilizador, float valorProduto){
    return valorProduto <= valorUtilizador;
}

// Função para registar todos os trocos que sairam da máquina num documento
int numeroRegistos = 1;
void registarTrocos(int doisEuros, int umEuro, int cinquentaCentimos, int vinteCentimos, int dezCentimos, int cincoCentimos){
    ofstream documento;
    if(numeroRegistos == 1){
        // Caso seja primeiro registo, apagar ficheiro existente e criar um novo
        remove("registoTrocos.txt");
        documento.open("registoTrocos.txt");
    }else{
        // Começar a escrever no ficheiro na última linha
        documento.open("registoTrocos.txt", std::ios::app);
    }
    if(documento){
        documento << numeroRegistos << " Registo" << endl;
        documento << "Moedas de 2 euros: " << doisEuros << endl;
        documento << "Moedas de 1 euros: " << umEuro << endl;
        documento << "Moedas de 50 cêntimos: " << cinquentaCentimos << endl;
        documento << "Moedas de 20 cêntimos: " << vinteCentimos << endl;
        documento << "Moedas de 10 cêntimos: " << dezCentimos << endl;
        documento << "Moedas de 5 cêntimos: " << cincoCentimos << endl;
        numeroRegistos++;
    }
    documento.close();
}

// Função para verificar se tem troco disponível
bool verificaTroco(int* valorCaixa, float valorUtilizador, float precoProduto){
    float troco = valorUtilizador - precoProduto;
    int moedasDois = 0;
    int moedasUm = 0;
    int moedasCinquenta = 0;
    int moedasVinte = 0;
    int moedasDez = 0;
    int moedasCinco = 0;
    while(troco > 0){
        if(troco >= 2 && valorCaixa[5] > 0){
            troco -= 2;
            moedasDois++;
        }else if(troco >= 1 && valorCaixa[4] > 0){
            troco -= 1;
            moedasUm++;
        }else if(troco >= 0.5 && valorCaixa[3] > 0){
            troco -= 0.5;
            moedasCinquenta++;
        }else if(troco >= 0.2 && valorCaixa[2] > 0){
            troco -= 0.2;
            moedasVinte++;
        }else if(troco >= 0.1 && valorCaixa[1] > 0){
            troco -= 0.1;
            moedasDez++;
        }else if(troco >= 0.05 && valorCaixa[0] > 0){
            troco -= 0.05;
            moedasCinco++;
        }else{
            break;
        }
    }
    if(troco == 0){
        valorCaixa[0] -= moedasCinco;
        valorCaixa[1] -= moedasDez;
        valorCaixa[2] -= moedasVinte;
        valorCaixa[3] -= moedasCinquenta;
        valorCaixa[4] -= moedasUm;
        valorCaixa[5] -= moedasDois;
    }
    return troco == 0;
}

// Função para efetuar compra
void efetuaCompra(string tecla, int tamanhoMaquina, string** produtos, int* quantidadeProduto, int* valorCaixa){
    char ultimoSlot = 'a' + (tamanhoMaquina - 1);
    // Converter a string inserida pelo cliente tudo para minusculas
    transform(tecla.begin(), tecla.end(), tecla.begin(), tolower);
    // Verifica se o slot inserido pelo utilizador existe
    if((tecla[0] >= 'a' && tecla[0] <= ultimoSlot) && tecla.length() == 1){
        // Converte o codigo do produto para o indice do array
        int indice = 0;
        char primeiroSlot = 'a';
        for(int i = 0; i < tamanhoMaquina; i++){
            if(tecla[0] != primeiroSlot){
                primeiroSlot++;
                indice++;
            }else{
                break;
            }
        }
        if(quantidadeProduto[indice] > 0){
            cout << ANSI_COLOR_BOLD << "Escolheu: " << ANSI_COLOR_RESET << produtos[indice][0] << endl;
            int doisEuros = obterQuantidadeMoedas(1);
            int umEuro = obterQuantidadeMoedas(2);
            int cinquentaCentimos = obterQuantidadeMoedas(3);
            int vinteCentimos = obterQuantidadeMoedas(4);
            int dezCentimos = obterQuantidadeMoedas(5);
            int cincoCentimos = obterQuantidadeMoedas(6);
            float valorUtilizador = (doisEuros * 2) + (umEuro * 1) + (cinquentaCentimos * 0.50) + (vinteCentimos * 0.20) + (dezCentimos * 0.10) + (cincoCentimos * 0.05);
            if(verificaValor(valorUtilizador, stof(produtos[indice][1]))){
                valorCaixa[0] += cincoCentimos;
                valorCaixa[1] += dezCentimos;
                valorCaixa[2] += vinteCentimos;
                valorCaixa[3] += cinquentaCentimos;
                valorCaixa[4] += umEuro;
                valorCaixa[5] += doisEuros;
                // Verifica se tem troco disponivel
                if(verificaTroco(valorCaixa, valorUtilizador, stof(produtos[indice][1]))){
                    // Produto comprado com sucesso
                    quantidadeProduto[indice] -= 1;
                    cout << ANSI_COLOR_GREEN << "*** Produto devolvido obrigado ***" << endl;
                    cout << ANSI_COLOR_BLUE << "*** Caixa - moedas***" << endl;
                    cout << ANSI_COLOR_BOLD << "2 euros: " << ANSI_COLOR_RESET << valorCaixa[5] << ANSI_COLOR_BLUE << " | " << ANSI_COLOR_RESET;
                    cout << ANSI_COLOR_BOLD << "1 euros: " << ANSI_COLOR_RESET << valorCaixa[4] << ANSI_COLOR_BLUE << " | " << ANSI_COLOR_RESET;
                    cout << ANSI_COLOR_BOLD << "0.5 euros: " << ANSI_COLOR_RESET << valorCaixa[3] << ANSI_COLOR_BLUE << " | " << ANSI_COLOR_RESET;
                    cout << ANSI_COLOR_BOLD << "0.2 euros: " << ANSI_COLOR_RESET << valorCaixa[2] << ANSI_COLOR_BLUE << " | " << ANSI_COLOR_RESET;
                    cout << ANSI_COLOR_BOLD << "0.1 euros: " << ANSI_COLOR_RESET << valorCaixa[1] << ANSI_COLOR_BLUE << " | " << ANSI_COLOR_RESET;
                    cout << ANSI_COLOR_BOLD << "0.05 euros: " << ANSI_COLOR_RESET << valorCaixa[0] << endl;
                    cout << ANSI_COLOR_BLUE << "*****************************" << ANSI_COLOR_RESET << endl;
                    registarTrocos(doisEuros, umEuro, cinquentaCentimos, vinteCentimos, dezCentimos, cincoCentimos);
                    system("pause");
                    system("cls");
                }else{
                    // Erro sem troco disponível
                    valorCaixa[0] -= cincoCentimos;
                    valorCaixa[1] -= dezCentimos;
                    valorCaixa[2] -= vinteCentimos;
                    valorCaixa[3] -= cinquentaCentimos;
                    valorCaixa[4] -= umEuro;
                    valorCaixa[5] -= doisEuros;
                    cout << ANSI_COLOR_RED << "Máquina sem troco para prosseguir esta operação!" << ANSI_COLOR_RESET << endl;
                    system("pause");
                    system("cls");
                }
            }else{
                // Erro dinheiro insufeciente
                cout << ANSI_COLOR_RED << "Dinheiro insufeciente para comprar este produto!" << endl;
                cout << "*** Troco Devolvido ***" << ANSI_COLOR_RESET << endl;
                system("pause");
                system("cls");
            }
        }else{
            // Erro nao tem produto para venda
            cout << ANSI_COLOR_RED << "Não tem produto disponível para venda neste slot!" << ANSI_COLOR_RESET << endl;
            system("pause");
            system("cls");
        }
    }else{
        // Código do produto inválido
        cout << ANSI_COLOR_RED << "Código do Produto não válido!" << ANSI_COLOR_RESET << endl;
        cout << ANSI_COLOR_BOLD << "Introduza o código do produto: " << ANSI_COLOR_RESET;
        getline(cin, tecla);
        efetuaCompra(tecla, tamanhoMaquina, produtos, quantidadeProduto, valorCaixa);
    }
}

// Função com todas as funcionalidades para o cliente efetuar a compra
void clienteCompra(int tamanhoMaquina, string** produtos, int* quantidadeProduto, int* valorCaixa){
    string tecla;
    cout << ANSI_COLOR_BLUE << "\n\n*** Bem vindo Cliente ***" << ANSI_COLOR_RESET << endl;
    cout << ANSI_COLOR_BOLD << "Introduza o código do produto: " << ANSI_COLOR_RESET;
    getline(cin, tecla);
    efetuaCompra(tecla, tamanhoMaquina, produtos, quantidadeProduto, valorCaixa);
}