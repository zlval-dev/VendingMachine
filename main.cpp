#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <Windows.h>
#include "inicializacao.h"
#include "cliente.h"
#include "funcionario.h"
#include "cores.h"

using namespace std;

void simulacao(){
    int* tamanhoMaquina = tamanho();
    int* capacidadeSlots = capacidade(tamanhoMaquina[0]);
    int* quantidadeProduto = quantidade(capacidadeSlots, tamanhoMaquina[0]);
    int* valorCaixa = valor();
    string** produtos = obterProdutos(tamanhoMaquina[0]);
    while(true){
        if(verificaAtualizacao()){
            capacidadeSlots = atualizaCapacidades();
            quantidadeProduto = atualizaQuantidades();
            produtos = atualizaProdutos();
            atualizacaoConcluida();
        }
        string escolhaUtilizador = imprimirInformacoes(tamanhoMaquina[0], capacidadeSlots, produtos, quantidadeProduto, valorCaixa);
        if(escolhaUtilizador == "c"){
            clienteCompra(tamanhoMaquina[0], produtos, quantidadeProduto, valorCaixa);
        }else if(escolhaUtilizador == "f"){
            realizacaoTarefa(tarefasUtilizador(), tamanhoMaquina, quantidadeProduto, produtos, capacidadeSlots, valorCaixa);
        }
    }
}


int main(){
    SetConsoleOutputCP(CP_UTF8); // Para poder imprimir os caracteres utf-8 na linha de comando
    srand(time(NULL));
    simulacao();
    return 0;
}