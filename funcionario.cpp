#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <algorithm>
#include "funcionario.h"
#include "inicializacao.h"
#include "cores.h"

using namespace std;

// Função para obter tarefa escolhida pelo utilizador
int escolhaUtilizador(){
    cout << ANSI_COLOR_RESET << ANSI_COLOR_BOLD << "Introduza a sua opção: " << ANSI_COLOR_RESET;
    string opcao;
    getline(cin, opcao);
    bool erro = false;
    if(opcao.find_first_not_of("0123456789")){  
        if(stoi(opcao) < 0 || stoi(opcao) > 10){
            erro = true;
        }
    }else{
        erro = true;
    }
    if(erro){
        cout << ANSI_COLOR_RED << "Tarefa escolhida não é válida!" << endl;
        escolhaUtilizador();
    }else{
        return stoi(opcao);
    }
}

// Função para imprimir as tarefas do funcionario e o mesmo escolher a opção
int tarefasUtilizador(){
    cout << ANSI_COLOR_BLUE << "*** Bem vindo funcionário ***" << endl;
    cout << ANSI_COLOR_YELLOW << "1. " << ANSI_COLOR_RESET << "Limpar slots" << endl;
    cout << ANSI_COLOR_YELLOW << "2. " << ANSI_COLOR_RESET << "Limpar máquina" << endl;
    cout << ANSI_COLOR_YELLOW << "3. " << ANSI_COLOR_RESET << "Adicionar produto" << endl;
    cout << ANSI_COLOR_YELLOW << "4. " << ANSI_COLOR_RESET << "Alterar preço" << endl;
    cout << ANSI_COLOR_YELLOW << "5. " << ANSI_COLOR_RESET << "Adicionar slot" << endl;
    cout << ANSI_COLOR_YELLOW << "6. " << ANSI_COLOR_RESET << "Carregar moedas" << endl;
    cout << ANSI_COLOR_YELLOW << "7. " << ANSI_COLOR_RESET << "Imprimir produtos" << endl;
    cout << ANSI_COLOR_YELLOW << "8. " << ANSI_COLOR_RESET << "Gravar máquina" << endl;
    cout << ANSI_COLOR_YELLOW << "9. " << ANSI_COLOR_RESET << "Carregar máquina" << endl;
    cout << ANSI_COLOR_YELLOW << "10. " << ANSI_COLOR_RESET << "Remover trocos" << endl;
    cout << ANSI_COLOR_YELLOW << "0. " << ANSI_COLOR_RESET << "Voltar" << endl;
    return escolhaUtilizador();
}

// Função para obter resposta do funcionario e verificar se slot existe
int verificaRespostaSlot(int tamanhoMaquina){
    string opcao;
    getline(cin, opcao);
    char ultimoSlot = 'a' + (tamanhoMaquina - 1);
    // Converter a string inserida pelo cliente tudo para minusculas
    transform(opcao.begin(), opcao.end(), opcao.begin(), tolower);
    if((opcao[0] >= 'a' && opcao[0] <= ultimoSlot) && opcao.length() == 1){
        // Converte o codigo do produto para o indice do array
        int indice = 0;
        char primeiroSlot = 'a';
        for(int i = 0; i < tamanhoMaquina; i++){
            if(opcao[0] != primeiroSlot){
                primeiroSlot++;
                indice++;
            }else{
                break;
            }
        }
        return indice;
    }else{
        return -1;
    }
}

// Função para limpar o slot
void limpaSlot(int tamanhoMaquina, int* quantidadeProduto, string** produtos, bool erro){
    if(erro){
        cout << ANSI_COLOR_RED << "Slot inserido não existe!" << ANSI_COLOR_RESET << endl;
    }else{
        cout << ANSI_COLOR_BLUE << "*** Limpar um slot ***" << ANSI_COLOR_RESET << endl;
    }
    cout << ANSI_COLOR_BOLD << "Qual o slot que pretende limpar: " << ANSI_COLOR_RESET;
    // Verifica se o slot inserido pelo utilizador existe
    int indice = verificaRespostaSlot(tamanhoMaquina);
    if(indice != -1){
        // Verifica se o slot ja nao esta vazio
        if(quantidadeProduto[indice] > 0){
            quantidadeProduto[indice] = 0;
            produtos[indice][0] = "Vazio";
            produtos[indice][1] = "0";
            cout << ANSI_COLOR_GREEN << "*** Slot limpo com sucesso ***" << ANSI_COLOR_RESET << endl;
            system("pause");
            system("cls");
        }else{
            cout << ANSI_COLOR_RED << "Este slot já se encontra vazio" << ANSI_COLOR_RESET << endl;
            system("pause");
            system("cls");
        }
    }else{
        limpaSlot(tamanhoMaquina, quantidadeProduto, produtos, true);
    }
}

// Função para limpar completamente a maquina, deixando apenas a capacidade do slot e numero de slots
void limparMaquina(int tamanhoMaquina, int* quantidadeProduto, string** produtos){
    for(int i = 0; i < tamanhoMaquina; i++){
        quantidadeProduto[i] = 0;
        produtos[i][0] = "Vazio";
        produtos[i][1] = "0";
    }
    cout << ANSI_COLOR_GREEN << "*** Máquina limpa com sucesso ***" << ANSI_COLOR_RESET << endl;
    system("pause");
    system("cls");
}

// Função para imprimir sucesso no adicionar produtos
void imprimeAdicionarProduto(){
    cout << ANSI_COLOR_GREEN << "*** Produtos adicionados com sucesso ***" << ANSI_COLOR_RESET << endl;
    system("pause");
    system("cls");
}

// Função que verifica se tem algum slot Vazio
int verificaSlotVazio(int tamanhoMaquina, int* quantidadeProduto){
    int slot = -1;
    for(int i = 0; i< tamanhoMaquina; i++){
        if(quantidadeProduto[i] == 0){
            slot = i;
            break;
        }
    }
    return slot;
}

// Função para adicionar produto
void adicionarProduto(int tamanhoMaquina, int* quantidadeProduto, string** produtos, int* capacidadeSlots, bool erroEscolha){
    if(erroEscolha){
        cout << ANSI_COLOR_RED << "Slot inserido não existe!" << ANSI_COLOR_RESET << endl;
    }else{
        cout << ANSI_COLOR_BLUE << "*** Adicionar produto ***" << ANSI_COLOR_RESET << endl;
    }
    cout << ANSI_COLOR_BOLD << "Qual o slot que pretende adicionar produto: " << ANSI_COLOR_RESET;
    // Verifica se o slot inserido pelo utilizador existe
    int indice = verificaRespostaSlot(tamanhoMaquina);
    if(indice != -1){
        int numeroProdutos = 0;
        int erroNumeroProdutos = false;
        // Obter a quantidade de produtos a adicionar
        while(numeroProdutos == 0){
            if(erroNumeroProdutos){
                cout << ANSI_COLOR_RED << "Quantidade de produtos não válida!" << ANSI_COLOR_RESET << endl;
            }
            cout << ANSI_COLOR_BOLD << "Introduza a quantidade de produtos a adicionar: " << ANSI_COLOR_RESET;
            string quantidadeAdicionar;
            getline(cin, quantidadeAdicionar);
            if(quantidadeAdicionar.find_first_not_of("0123456789")){
                numeroProdutos = stoi(quantidadeAdicionar);
            }else{
                erroNumeroProdutos = true;
            }
        }
        // Obter o nome do produto a adicionar
        cout << ANSI_COLOR_BOLD << "Introduza o nome do produto a adicionar: " << ANSI_COLOR_RESET;
        string nomeProduto;
        getline(cin, nomeProduto);
        // Verificar se o nome do produto a adicionar e o que esta no slot é o mesmo
        if(produtos[indice][0] == nomeProduto || produtos[indice][0] == "Vazio"){
            if(produtos[indice][0] == "Vazio"){
                produtos[indice][0] = nomeProduto;
                produtos[indice][1] = obtemValor();
            }
            // Caso tenho produtos no slot
            if(quantidadeProduto[indice] + numeroProdutos <= capacidadeSlots[indice]){
                // Apenas adiciona os produtos
                quantidadeProduto[indice] += numeroProdutos;
                imprimeAdicionarProduto();
            }else{
                // Verifica se tem algum slot vazio e se tiver introduz os que faltam ai
                int slotVazio = verificaSlotVazio(tamanhoMaquina, quantidadeProduto);
                if(slotVazio != -1){
                    // Existe slot vazio
                    int restante = numeroProdutos - (capacidadeSlots[indice] - quantidadeProduto[indice]);
                    quantidadeProduto[indice] = capacidadeSlots[indice];
                    produtos[slotVazio][0] = produtos[indice][0];
                    produtos[slotVazio][1] = produtos[indice][1];
                    if(capacidadeSlots[slotVazio] < restante){
                        capacidadeSlots[slotVazio] = restante;
                    }
                    quantidadeProduto[slotVazio] = restante;
                    imprimeAdicionarProduto();
                }else{
                    // Nao existe slot vazio
                    cout << "*** Erro ao introduzir produto ***" << ANSI_COLOR_RESET << endl;
                    cout << "A quantidade que está a tentar adicionar é maior do que as vagas suficientes no slot e não tem nenhum slot vazio na máquina" << endl;
                    cout << "Que pretende fazer?" << endl;
                    cout << "1- Alterar tamanho do slot para acomodar todos os produtos inseridos" << endl;
                    cout << "2- Adicionar apenas os produtos que conseguem ser inseridos" << endl;
                    cout << ANSI_COLOR_BOLD << "Opção: " << ANSI_COLOR_RESET;
                    bool erro = false;
                    string opcao;
                    getline(cin, opcao);
                    if(opcao.find_first_not_of("0123456789") && opcao.length() == 1){
                        if(!(opcao[0] == '1' || opcao[0] == '2')){
                            erro = true;
                        }
                    }else{
                        erro = true;
                    }
                    while(erro){
                        cout << ANSI_COLOR_RED << "Opção introduzida incorreta!" << ANSI_COLOR_RESET << endl;
                        cout << ANSI_COLOR_BOLD << "Opção: " << ANSI_COLOR_RESET;
                        erro = false;
                        getline(cin, opcao);
                        if(opcao.find_first_not_of("0123456789") && opcao.length() == 1){
                            if(!(opcao[0] == '1' || opcao[0] == '2')){
                                erro = true;
                            }
                        }else{
                            erro = true;
                        }
                    }
                    if(opcao[0] == '1'){
                        // Alterar tamanho do slot para acomodar todos os produtos inseridos
                        capacidadeSlots[indice] += numeroProdutos;
                        quantidadeProduto[indice] += numeroProdutos;
                        imprimeAdicionarProduto();
                    }else if(opcao[0] == '2'){
                        // Adicionar apenas os produtos que conseguem ser inseridos
                        quantidadeProduto[indice] = capacidadeSlots[indice];
                        imprimeAdicionarProduto();
                    }
                }
            }
        }else{
            cout << ANSI_COLOR_RED << "*** Erro ao introduzir produto ***" << endl;
            cout << "Produto no slot e o produto que está a tentar introduzir são diferentes!" << ANSI_COLOR_RESET << endl;
            system("pause");
            system("cls");
        }
    }else{
        adicionarProduto(tamanhoMaquina, quantidadeProduto, produtos, capacidadeSlots, true);
    }
}

bool multiploCincoCentimos(float novoPreco){
    while(novoPreco > 0){
        novoPreco -= 0.05;
        novoPreco = roundf(novoPreco * 100) / 100;
    }
    if(novoPreco == 0){
        return true;
    }else{
        return false;
    }
}

// Função para alterar o preço de um produto
void alterarPreco(int tamanhoMaquina, string** produtos){
    cout << ANSI_COLOR_BLUE << "*** Alterar Preço ***" << ANSI_COLOR_RESET << endl;
    cout << ANSI_COLOR_BOLD << "Nome do Produto: ";
    string produto;
    transform(produto.begin(), produto.end(), produto.begin(), tolower);
    getline(cin, produto);
    cout << ANSI_COLOR_BOLD << "Novo Preço: ";
    string novoPreco;
    getline(cin, novoPreco);
    if(multiploCincoCentimos(stof(novoPreco))){ 
        bool existeProduto = false;
        for(int i = 0; i < tamanhoMaquina; i++){
            string aux = produtos[i][0];
            transform(aux.begin(), aux.end(), aux.begin(), tolower);
            if(aux == produto){
                produtos[i][1] = novoPreco;
                existeProduto = true;
            }
        }
        if(existeProduto){
            cout << ANSI_COLOR_GREEN << "*** Preço alterado com sucesso ***" << ANSI_COLOR_RESET << endl;
            system("pause");
            system("cls");
        }else{
            cout << ANSI_COLOR_RED << "*** Erro ao alterar preço ***" << ANSI_COLOR_RESET << endl;
            cout << "Nome do produto não se encontra na máquina" << endl;
            system("pause");
            system("cls");
        }
    }else{
        cout << ANSI_COLOR_RED << "*** Erro ao alterar preço ***" << ANSI_COLOR_RESET << endl;
        cout << "Preço não é múltiplo de 0.05€" << endl;
        system("pause");
        system("cls");
    }
}

// Função para verificar se é inteiro
bool verificaMoeda(string moeda){
    if(moeda.find_first_not_of("0123456789")){  
        return false;
    }else{
        return true;
    }
}

// Função para obter o valor das moedas introduzidas pelo utilizador
int* obterQuantidadeMoedas(){
    string moedaDois = "zero";
    bool erroDois = false;
    while(verificaMoeda(moedaDois)){
        if(erroDois){
            cout << ANSI_COLOR_RED << "Valor introduido não é um inteiro!" << ANSI_COLOR_RESET << endl;
        }
        erroDois = true;
        cout << ANSI_COLOR_BOLD << "Introduza a quantidade de moedas de 2 euros: " << ANSI_COLOR_RESET;
        getline(cin, moedaDois);
    }
    string moedaUm = "zero";
    bool erroUm = false;
    while(verificaMoeda(moedaUm)){
        if(erroUm){
            cout << ANSI_COLOR_RED << "Valor introduido não é um inteiro!" << ANSI_COLOR_RESET << endl;
        }
        erroUm = true;
        cout << ANSI_COLOR_BOLD << "Introduza a quantidade de moedas de 1 euros: " << ANSI_COLOR_RESET;
        getline(cin, moedaUm);
    }
    string moedaCinquenta = "zero";
    bool erroCinquenta = false;
    while(verificaMoeda(moedaCinquenta)){
        if(erroCinquenta){
            cout << ANSI_COLOR_RED << "Valor introduido não é um inteiro!" << ANSI_COLOR_RESET << endl;
        }
        erroCinquenta = true;
        cout << ANSI_COLOR_BOLD << "Introduza a quantidade de moedas de 50 cêntimos: " << ANSI_COLOR_RESET;
        getline(cin, moedaCinquenta);
    }
    string moedaVinte = "zero";
    bool erroVinte = false;
    while(verificaMoeda(moedaVinte)){
        if(erroVinte){
            cout << ANSI_COLOR_RED << "Valor introduido não é um inteiro!" << ANSI_COLOR_RESET << endl;
        }
        erroVinte = true;
        cout << ANSI_COLOR_BOLD << "Introduza a quantidade de moedas de 20 cêntimos: " << ANSI_COLOR_RESET;
        getline(cin, moedaVinte);
    }
    string moedaDez = "zero";
    bool erroDez = false;
    while(verificaMoeda(moedaDez)){
        if(erroDez){
            cout << ANSI_COLOR_RED << "Valor introduido não é um inteiro!" << ANSI_COLOR_RESET << endl;
        }
        erroDez = true;
        cout << ANSI_COLOR_BOLD << "Introduza a quantidade de moedas de 10 cêntimos: " << ANSI_COLOR_RESET;
        getline(cin, moedaDez);
    }
    string moedaCinco = "zero";
    bool erroCinco = false;
    while(verificaMoeda(moedaCinco)){
        if(erroCinco){
            cout << ANSI_COLOR_RED << "Valor introduido não é um inteiro!" << ANSI_COLOR_RESET << endl;
        }
        erroCinquenta = true;
        cout << ANSI_COLOR_BOLD << "Introduza a quantidade de moedas de 5 cêntimos: " << ANSI_COLOR_RESET;
        getline(cin, moedaCinco);
    }
    int * quantidadeMoedas = new int[6];
    quantidadeMoedas[0] = stoi(moedaCinco);
    quantidadeMoedas[1] = stoi(moedaDez);
    quantidadeMoedas[2] = stoi(moedaVinte);
    quantidadeMoedas[3] = stoi(moedaCinquenta);
    quantidadeMoedas[4] = stoi(moedaUm);
    quantidadeMoedas[5] = stoi(moedaDois);
    return quantidadeMoedas;
}

// Função que permite carregar moedas da máquina
void carregarMoedas(int* valorCaixa){
    cout << ANSI_COLOR_BLUE << "*** Carregar moedas ***" << ANSI_COLOR_RESET << endl;
    int * moedas = new int[6];
    moedas = obterQuantidadeMoedas();
    valorCaixa[5] += moedas[5];
    valorCaixa[4] += moedas[4];
    valorCaixa[3] += moedas[3];
    valorCaixa[2] += moedas[2];
    valorCaixa[1] += moedas[1];
    valorCaixa[0] += moedas[0];
    cout << ANSI_COLOR_GREEN << "*** Moedas carregadas com sucesso ***" << ANSI_COLOR_RESET << endl;
    system("pause");
    system("cls");
}

// Função para remover moedas da máquina
void removerFundos(int* valorCaixa){
    cout << ANSI_COLOR_BLUE << "*** Remover fundos ***" << ANSI_COLOR_RESET << endl;
    cout << ANSI_COLOR_BOLD << "Moedas de 2 euros: " << ANSI_COLOR_RESET << valorCaixa[5] << endl;
    cout << ANSI_COLOR_BOLD << "Moedas de 1 euros: " << ANSI_COLOR_RESET << valorCaixa[4] << endl;
    cout << ANSI_COLOR_BOLD << "Moedas de 50 cêntimos: " << ANSI_COLOR_RESET << valorCaixa[3] << endl;
    cout << ANSI_COLOR_BOLD << "Moedas de 20 cêntimos: " << ANSI_COLOR_RESET << valorCaixa[2] << endl;
    cout << ANSI_COLOR_BOLD << "Moedas de 10 cêntimos: " << ANSI_COLOR_RESET << valorCaixa[1] << endl;
    cout << ANSI_COLOR_BOLD << "Moedas de 5 cêntimos: " << ANSI_COLOR_RESET << valorCaixa[0] << endl;
    int* moedas = obterQuantidadeMoedas();
    bool erro = false;
    for(int i = 0; i < 6; i++){
        if(valorCaixa[i] - moedas[i] < 0){
            erro = true;
        }
    }
    if(erro){
        cout << ANSI_COLOR_RED << "*** Erro, tentou retirar mais moedas do que aquelas que já existiam na máquina ***" << ANSI_COLOR_RESET << endl;
        system("pause");
        system("cls");
    }else{
        valorCaixa[5] -= moedas[5];
        valorCaixa[4] -= moedas[4];
        valorCaixa[3] -= moedas[3];
        valorCaixa[2] -= moedas[2];
        valorCaixa[1] -= moedas[1];
        valorCaixa[0] -= moedas[0];
        cout << ANSI_COLOR_GREEN << "*** Moedas retiradas com sucesso ***" << ANSI_COLOR_RESET << endl;
        system("pause");
        system("cls");
    }
}

// Função para imprimir produtos por ordem Alfabética
void ordemAlfabetica(int tamanhoMaquina, string* auxNomeProduto){
    cout << ANSI_COLOR_BLUE << "*** Alfabeticamente ***" << ANSI_COLOR_RESET << endl;
    string aux;
    for(int i = 0; i < tamanhoMaquina; i++){
        for(int j = 0; j < tamanhoMaquina; j++){
            if(auxNomeProduto[i] < auxNomeProduto[j]){
                aux = auxNomeProduto[i];
                auxNomeProduto[i] = auxNomeProduto[j];
                auxNomeProduto[j] = aux;
            }
        }
    }
    for(int i = 0; i < tamanhoMaquina; i++){
        cout << auxNomeProduto[i] << endl;
    }
}

// Função para imprimir produtos por preço
void porPreco(int tamanhoMaquina, string** auxProdutos){
    cout << ANSI_COLOR_BLUE << "*** Por preço ***" << ANSI_COLOR_RESET << endl;
    string aux, aux2;
    for(int i = 0; i < tamanhoMaquina; i++){
        for(int j = 0; j < tamanhoMaquina; j++){
            if(auxProdutos[i][1] < auxProdutos[j][1]){
                aux = auxProdutos[i][0];
                aux2 = auxProdutos[i][1];
                auxProdutos[i][0] = auxProdutos[j][0];
                auxProdutos[j][0] = aux;
                auxProdutos[i][1] = auxProdutos[j][1];
                auxProdutos[j][1] = aux2;
            }
        }
    }
    for(int i = 0; i < tamanhoMaquina; i++){
        cout << auxProdutos[i][0] << endl;
    }
}

// Função para imprimir produtos por quantidade disponível
void quantidadeDisponivel(int tamanhoMaquina, int* auxQuantidadeProduto, string* auxNomeProduto){
    cout << ANSI_COLOR_BLUE << "*** Por quantidade ***" << ANSI_COLOR_RESET << endl;
    int aux;
    string aux2;
    for(int i = 0; i < tamanhoMaquina; i++){
        for(int j = 0; j < tamanhoMaquina; j++){
            if(auxQuantidadeProduto[i] < auxQuantidadeProduto[j]){
                aux = auxQuantidadeProduto[i];
                aux2 = auxNomeProduto[i];
                auxQuantidadeProduto[i] = auxQuantidadeProduto[j];
                auxQuantidadeProduto[j] = aux;
                auxNomeProduto[i] = auxNomeProduto[j];
                auxNomeProduto[j] = aux2;
            }
        }
    }
    for(int i = 0; i < tamanhoMaquina; i++){
        cout << auxNomeProduto[i] << endl;
    }
}

// Função para imprimir produtos
void imprimirProdutos(int tamanhoMaquina, string** produtos, int* quantidadeProduto){
    cout << ANSI_COLOR_BLUE << "*** Imprimir produto ***" << ANSI_COLOR_RESET << endl;
    cout << ANSI_COLOR_BOLD << "1. " << ANSI_COLOR_RESET << "Por ordem alfabética" << endl;
    cout << ANSI_COLOR_BOLD << "2. " << ANSI_COLOR_RESET << "Por preço" << endl;
    cout << ANSI_COLOR_BOLD << "3. " << ANSI_COLOR_RESET << "Por quantidade disponível" << endl;
    cout << ANSI_COLOR_BOLD << "Escolha a sua opção: " << ANSI_COLOR_RESET;
    string opcao;
    getline(cin, opcao);
    while(!opcao.find_first_not_of("123") || opcao.length() > 1){
        cout << ANSI_COLOR_RED << "Opção escolhida não existe!" << ANSI_COLOR_RESET << endl;
        cout << ANSI_COLOR_BOLD << "Escolha a sua opção: " << ANSI_COLOR_RESET;
        getline(cin, opcao);
    }
    if(opcao[0] == '1'){
        string* auxNomeProduto = new string[tamanhoMaquina];
        for(int i = 0; i < tamanhoMaquina; i++){
            auxNomeProduto[i] = produtos[i][0];
        }
        ordemAlfabetica(tamanhoMaquina, auxNomeProduto);
        delete[] auxNomeProduto;
    }else if(opcao[0] == '2'){
        string** auxProdutos = new string*[tamanhoMaquina];
        for(int i = 0; i < tamanhoMaquina; i++){
            auxProdutos[i] = new string[2];
        }
        for(int i = 0; i < tamanhoMaquina; i++){
            auxProdutos[i][0] = produtos[i][0];
            auxProdutos[i][1] = produtos[i][1];
        }
        porPreco(tamanhoMaquina, auxProdutos);
        for(int i = 0; i < tamanhoMaquina; i++){
            delete[] auxProdutos[i];
        }
        delete[] auxProdutos;
    }else{
        string* auxNomeProduto = new string[tamanhoMaquina];
        int* auxQuantidadeProduto = new int[tamanhoMaquina];
        for(int i = 0; i < tamanhoMaquina; i++){
            auxNomeProduto[i] = produtos[i][0];
            auxQuantidadeProduto[i] = quantidadeProduto[i];
        }
        quantidadeDisponivel(tamanhoMaquina, auxQuantidadeProduto, auxNomeProduto);
        delete[] auxNomeProduto;
        delete[] auxQuantidadeProduto;
    }
    system("pause");
    system("cls");
}

// Função para gravar dados da máquina num ficheiro
void gravarMaquina(int tamanhoMaquina, int* quantidadeProduto, int* capacidadeSlots, string** produtos, int* valorCaixa){
    ofstream ficheiro;
    cout << ANSI_COLOR_BLUE << "*** Gravar máquina ***" << ANSI_COLOR_RESET << endl;
    cout << ANSI_COLOR_BOLD << "Introduza o nome para o ficheiro: ";
    string nomeFicheiro;
    getline(cin, nomeFicheiro);
    ficheiro.open(nomeFicheiro + ".txt");
    ficheiro << "Tamanho da máquina: " << tamanhoMaquina << endl << endl;
    for(int i = 0; i < tamanhoMaquina; i++){
        ficheiro << "Nome: " << produtos[i][0] << endl;
        ficheiro << "Preço: " << produtos[i][1] << endl;
        ficheiro << "Quantidade: " << quantidadeProduto[i] << endl;
        ficheiro << "Capacidade: " << capacidadeSlots[i] << endl << endl;
    }
    ficheiro << "Moedas na caixa" << endl;
    ficheiro << "2 euros: " << valorCaixa[5] << endl;
    ficheiro << "1 euro: " << valorCaixa[4] << endl;
    ficheiro << "50 cêntimos: " << valorCaixa[3] << endl;
    ficheiro << "20 cêntimos: " << valorCaixa[2] << endl;
    ficheiro << "10 cêntimos: " << valorCaixa[1] << endl;
    ficheiro << "5 cêntimos: " << valorCaixa[0] << endl;
    ficheiro.close();
    cout << ANSI_COLOR_GREEN << "Máquina gravada com sucesso!" << ANSI_COLOR_RESET << endl;
    system("pause");
    system("cls");
}

int* auxCapacidadeSlots = new int;
int* auxQuantidadeProduto = new int;
string** auxProdutos = new string*;
bool atualiza = false;
// Função para verificar se é preciso atualizar
bool verificaAtualizacao(){
    return atualiza;
}

// Atualizacao feita
void atualizacaoConcluida(){
    atualiza = false;
}

// Atualiza Quantidades
int* atualizaQuantidades(){
    return auxQuantidadeProduto;
}

// Atualiza Capacidades
int* atualizaCapacidades(){
    return auxCapacidadeSlots;
}

// Atualiza Produtos
string** atualizaProdutos(){
    return auxProdutos;
}

// Função para carregar máquina de um ficheiro
void carregarMaquina(int* tamanhoMaquina, int* capacidadeSlots, int* quantidadeProduto, int* valorCaixa, string** produtos){
    cout << ANSI_COLOR_BLUE << "*** Carregar maquina ***" << ANSI_COLOR_RESET << endl;
    cout << ANSI_COLOR_BOLD << "Introduza o nome do ficheiro: " << ANSI_COLOR_RESET;
    string nomeFicheiro;
    getline(cin, nomeFicheiro);
    ifstream ficheiro;
    // Abrir ficheiro
    ficheiro.open(nomeFicheiro + ".txt");
    if(ficheiro.fail()){
        cout << ANSI_COLOR_RED << "Esse ficheiro não existe!" << ANSI_COLOR_RESET << endl;
    }else{
        atualiza = true;
        string line, retirar, resultado;
        bool tamanho = false;
        bool moedas = false;
        int caso = 0;
        int indice = 0;
        // Enquanto nao terminar
        while(!ficheiro.eof()){
            getline(ficheiro, line);
            if(!tamanho){
                retirar = "Tamanho da máquina: ";
                resultado = line.erase(line.find(retirar), retirar.length());
                tamanhoMaquina[0] = stoi(resultado);
                auxCapacidadeSlots = new int[stoi(resultado)];
                auxQuantidadeProduto = new int[stoi(resultado)];
                auxProdutos = new string*[stoi(resultado)];
                for(int i = 0; i < stoi(resultado); i++){
                    auxProdutos[i] = new string[2];
                }
                tamanho = true;
                getline(ficheiro, line);
            }else if(!moedas){
                if(line == "Moedas na caixa"){
                    moedas = true;
                }else{
                    switch(caso){
                        case 0:
                            retirar = "Nome: ";
                            resultado = line.erase(line.find(retirar), retirar.length());
                            auxProdutos[indice][0] = resultado;
                            caso = 1;
                            break;
                        case 1:
                            retirar ="Preço: ";
                            resultado = line.erase(line.find(retirar), retirar.length());
                            auxProdutos[indice][1] = resultado;
                            caso = 2;
                            break;
                        case 2:
                            retirar = "Quantidade: ";
                            resultado = line.erase(line.find(retirar), retirar.length());
                            auxQuantidadeProduto[indice] = stoi(resultado);
                            caso = 3;
                            break;
                        case 3:
                            retirar = "Capacidade: ";
                            resultado = line.erase(line.find(retirar), retirar.length());
                            auxCapacidadeSlots[indice] = stoi(resultado);
                            caso = 0;
                            indice++;
                            getline(ficheiro, line);
                            break;
                    }
                }
            }else{
                switch(caso){
                    case 0:
                        indice = 5;
                        retirar = "2 euros: ";
                        resultado = line.erase(line.find(retirar), retirar.length());
                        valorCaixa[indice] = stoi(resultado);
                        caso = 1;
                        break;
                    case 1:
                        indice = 4;
                        retirar = "1 euro: ";
                        resultado = line.erase(line.find(retirar), retirar.length());
                        valorCaixa[indice] = stoi(resultado);
                        caso = 2;
                        break;
                    case 2:
                        indice = 3;
                        retirar = "50 cêntimos: ";
                        resultado = line.erase(line.find(retirar), retirar.length());
                        valorCaixa[indice] = stoi(resultado);
                        caso = 3;
                        break;
                    case 3:
                        indice = 2;
                        retirar = "20 cêntimos: ";
                        resultado = line.erase(line.find(retirar), retirar.length());
                        valorCaixa[indice] = stoi(resultado);
                        caso = 4;
                        break;
                    case 4:
                        indice = 1;
                        retirar = "10 cêntimos: ";
                        resultado = line.erase(line.find(retirar), retirar.length());
                        valorCaixa[indice] = stoi(resultado);
                        caso = 5;
                        break;
                    case 5:
                        indice = 0;
                        retirar = "5 cêntimos: ";
                        resultado = line.erase(line.find(retirar), retirar.length());
                        valorCaixa[indice] = stoi(resultado);
                        caso ++;
                        break;
                }
            }
        }
    }
    cout << ANSI_COLOR_GREEN << "Máquina carregada com sucesso!" << ANSI_COLOR_RESET << endl;
    system("pause");
    system("cls");
}

// Função para adicionar slot
void adicionarSlot(int* tamanhoMaquina, int* capacidadeSlots, int* quantidadeProduto, string** produtos){
    cout << ANSI_COLOR_BLUE << "*** Adicionar slot ***" << ANSI_COLOR_RESET << endl;
    cout << ANSI_COLOR_BOLD << "Pretende adicionar um slot com quanto de capacidade? " << ANSI_COLOR_RESET;
    int numero;
    cin >> numero;
    while(!cin.good()){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << ANSI_COLOR_RED << "*** Não introduziu um número válido! ***" << ANSI_COLOR_RESET << endl;
        cout << ANSI_COLOR_BOLD << "Pretende adicionar um slot com quanto de capacidade? " << ANSI_COLOR_RESET;
        cin >> numero;
    }
    tamanhoMaquina[0] += 1;
    auxCapacidadeSlots = new int[tamanhoMaquina[0]];
    auxQuantidadeProduto = new int[tamanhoMaquina[0]];
    auxProdutos = new string*[tamanhoMaquina[0]];
    for(int i = 0; i < tamanhoMaquina[0]; i++){
        auxProdutos[i] = new string[2];
    }
    for(int i = 0; i < (tamanhoMaquina[0]-1); i++){
        auxCapacidadeSlots[i] = capacidadeSlots[i];
        auxQuantidadeProduto[i] = quantidadeProduto[i];
        auxProdutos[i][0] = produtos[i][0];
        auxProdutos[i][1] = produtos[i][1];
    }
    auxCapacidadeSlots[tamanhoMaquina[0]-1] = numero;
    auxQuantidadeProduto[tamanhoMaquina[0]-1] = 0;
    auxProdutos[tamanhoMaquina[0]-1][0] = "Vazio";
    auxProdutos[tamanhoMaquina[0]-1][1] = "0";
    atualiza = true;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cout << ANSI_COLOR_GREEN << "Slot adicionado com sucesso!" << ANSI_COLOR_RESET << endl;
    system("pause");
    system("cls");
}

// Função para realizar a tarefa escolhida pelo utilizador
void realizacaoTarefa(int tarefaUtilizador, int* tamanhoMaquina, int* quantidadeProduto, string** produtos, int* capacidadeSlots, int* valorCaixa){
    switch(tarefaUtilizador){
        case 0:
            system("pause");
            system("cls");
            break;
        case 1:
            limpaSlot(tamanhoMaquina[0], quantidadeProduto, produtos, false);
            break;
        case 2:
            limparMaquina(tamanhoMaquina[0], quantidadeProduto, produtos);
            break;
        case 3:
            adicionarProduto(tamanhoMaquina[0], quantidadeProduto, produtos, capacidadeSlots, false);
            break;
        case 4:
            alterarPreco(tamanhoMaquina[0], produtos);
            break;
        case 5:
            adicionarSlot(tamanhoMaquina, capacidadeSlots, quantidadeProduto, produtos);
            break;
        case 6:
            carregarMoedas(valorCaixa);
            break;
        case 7:
            imprimirProdutos(tamanhoMaquina[0], produtos, quantidadeProduto);
            break;
        case 8:
            gravarMaquina(tamanhoMaquina[0], quantidadeProduto, capacidadeSlots, produtos, valorCaixa);
            break;
        case 9:
            carregarMaquina(tamanhoMaquina, capacidadeSlots, quantidadeProduto, valorCaixa, produtos);
            break;
        case 10:
            removerFundos(valorCaixa);
            break;
    }
}