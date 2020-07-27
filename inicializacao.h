#ifndef INICIALIZACAO_H
#define INICIALIZACAO_H
#include <string>
using namespace std;

int* tamanho();
int* capacidade(int tamanhoMaquina);
int* quantidade(int* capacidadeProduto, int tamanhoMaquina);
int* valor();
string** obterProdutos(int tamanhoMaquina);
string imprimirInformacoes(int tamanhoMaquina, int* capacidadeSlots, string** produtos, int* quantidadeProduto, int* valorCaixa);
string obtemValor();

#endif