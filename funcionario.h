#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H
#include <string>
using namespace std;

int tarefasUtilizador();
void realizacaoTarefa(int tarefaUtilizador, int* tamanhoMaquina, int* quantidadeProduto, string** produtos, int* capacidadeSlots, int* valorCaixa);
bool verificaAtualizacao();
int* atualizaQuantidades();
int* atualizaCapacidades();
string** atualizaProdutos();
void atualizacaoConcluida();

#endif