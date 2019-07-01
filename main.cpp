/// Alencar Antônio Moreira
/// 2016013836
///
/// NICHOLAS DE CARVALHO GOMES
/// 2019000582


#include <iostream>
#include <list>

//using namespace std;


struct dados {
    int chave;
    //outros dados
};

union celula {
    struct {
        int quant, first, last, free;
    } cabecalho;
    struct {
        int next, prev;
        dados reg;
    } lista;
};

bool insereRegistro(celula listaDados[]);

void mostraList(celula listaDados[]);

void iniciaEstrutura(celula listaDados[], int tamanho);

bool removeRegistro(celula listaDados[]);

bool organizaCabecalhoRemove(celula listaDados[], int aux1);

bool mostrarRegistrosLivres(celula listaDados[]);

bool mostrarCabecalho(celula listaDados[]);

bool mostraNaoOrdernado(celula listaDados, int tamanho);


bool insereRegistro(celula listaDados[]) {

    dados dado;

    std::cout << "Digite o dado a ser inserido: " << std::endl;
    std::cin >> dado.chave;

    listaDados[0].cabecalho.quant++;

    int freePosition = listaDados[0].cabecalho.free;
    listaDados[0].cabecalho.free = listaDados[freePosition].lista.next;
    listaDados[freePosition].lista.reg = dado;
    listaDados[freePosition].lista.next = -1;

    if (listaDados[0].cabecalho.first == -1) {
        listaDados[0].cabecalho.first = freePosition;
        listaDados[0].cabecalho.last = freePosition;
    }

    if (listaDados[freePosition].lista.reg.chave < listaDados[listaDados[0].cabecalho.first].lista.reg.chave) {
        int indiceAux = listaDados[0].cabecalho.first;
        listaDados[indiceAux].lista.prev = freePosition;
        listaDados[freePosition].lista.prev = -1;
        listaDados[freePosition].lista.next = listaDados[0].cabecalho.first;
        listaDados[0].cabecalho.first = freePosition;
        return true;
    }
    if (listaDados[freePosition].lista.reg.chave > listaDados[listaDados[0].cabecalho.last].lista.reg.chave) {
        int indiceAux = listaDados[0].cabecalho.last;
        listaDados[freePosition].lista.prev = indiceAux;
        listaDados[freePosition].lista.next = -1;
        listaDados[indiceAux].lista.next = freePosition;
        listaDados[0].cabecalho.last = freePosition;
        return true;
    }


    int indice = listaDados[0].cabecalho.first;
    ////OBSERVAR PREV E NEXT ELES QUE ESTÃO FODENDO O ROLE

    while (indice != -1) {
        ///Acha o exatamente maior que a chave que esta sendo inserida
        if (listaDados[indice].lista.reg.chave > listaDados[freePosition].lista.reg.chave) {
            listaDados[freePosition].lista.prev = listaDados[indice].lista.prev;
            listaDados[freePosition].lista.next = indice;
            listaDados[listaDados[indice].lista.prev].lista.next = freePosition;
            listaDados[indice].lista.prev = freePosition;
            return true;
        }
        indice = listaDados[indice].lista.next;
    }
    return false;
}


void mostraList(celula listaDados[]) {

    mostrarCabecalho(listaDados);
    int index = listaDados[0].cabecalho.first;
    while (index != -1) {
        std::cout << "Posição: " << index << std::endl;
        std::cout << "Dado: " << listaDados[index].lista.reg.chave << std::endl;
        std::cout << "Next: " << listaDados[index].lista.next << std::endl;
        std::cout << "Prev: " << listaDados[index].lista.prev << std::endl;
        index = listaDados[index].lista.next;
    }
}

void iniciaEstrutura(celula listaDados[], int tamanho) {
    listaDados[0].cabecalho.first = -1;
    listaDados[0].cabecalho.last = -1;
    listaDados[0].cabecalho.free = 1;
    listaDados[0].cabecalho.quant = 0;

    for (int i = 1; i < tamanho; ++i) {
        listaDados[i].lista.next = i + 1;
        listaDados[i].lista.prev = -1;
        listaDados[i].lista.reg.chave = -1;
        if (i == tamanho - 1)
            listaDados[i].lista.next = -1;
    }

}

bool organizaCabecalhoRemove(celula listaDados[], int aux1) {
    if (listaDados[0].cabecalho.free == -1) {
        listaDados[aux1].lista.next = -1;
        listaDados[0].cabecalho.free = aux1;

        return true;
    } else if (aux1 < listaDados[0].cabecalho.free) {
        listaDados[aux1].lista.next = listaDados[0].cabecalho.free;
        listaDados[0].cabecalho.free = aux1;

        return true;
    } else {
        int index = listaDados[0].cabecalho.free;
        if (listaDados[index].lista.next == -1) {
            listaDados[index].lista.next = aux1;
            listaDados[aux1].lista.next = -1;
            return true;
        }
        while (aux1 != index) {

            if (listaDados[index].lista.next == -1) {
                listaDados[index].lista.next = aux1;
                listaDados[aux1].lista.next = -1;
                return true;
            }
            if (listaDados[index].lista.next > aux1) {
                listaDados[aux1].lista.next = listaDados[index].lista.next;
                listaDados[index].lista.next = aux1;
                return true;
            }

            index = listaDados[index].lista.next;
        }
    }
    return false;
}

bool removeRegistro(celula listaDados[]) {
    ////ARRUMA ESSE CARALHO IRMÃO
    if (listaDados[0].cabecalho.quant == 0) {
        std::cout << "Não há dados para serem removidos" << std::endl;
        return false;
    } else {
        int chave;
        int indice;
        std::cout << "Digite o dado a ser removido: " << std::endl;
        std::cin >> chave;
        indice = listaDados[0].cabecalho.first;

        if ((listaDados[0].cabecalho.quant == 1) &&
            (listaDados[listaDados[0].cabecalho.first].lista.reg.chave == chave)) {
            listaDados[0].cabecalho.quant--;
            int aux = listaDados[0].cabecalho.first;
            listaDados[aux].lista.prev = -1;
            listaDados[aux].lista.reg.chave = -1;
            listaDados[aux].lista.next = -1;
            listaDados[0].cabecalho.first = -1;
            listaDados[0].cabecalho.last = -1;
            organizaCabecalhoRemove(listaDados, aux);
            return true;
        }

        if (listaDados[listaDados[0].cabecalho.first].lista.reg.chave == chave) {
            listaDados[0].cabecalho.quant--;
            int aux1 = listaDados[0].cabecalho.first;
            listaDados[0].cabecalho.first = listaDados[listaDados[0].cabecalho.first].lista.next;
            listaDados[aux1].lista.prev = -1;
            listaDados[aux1].lista.reg.chave = -1;
            listaDados[listaDados[0].cabecalho.first].lista.prev = -1;
            ///fazer atualização de indices
            listaDados[aux1].lista.next = -1;
            organizaCabecalhoRemove(listaDados, aux1);
            return true;

        }

        if (listaDados[listaDados[0].cabecalho.last].lista.reg.chave == chave) {
            listaDados[0].cabecalho.quant--;
            int aux1 = listaDados[0].cabecalho.last;
            listaDados[0].cabecalho.last = listaDados[aux1].lista.prev;
            listaDados[listaDados[aux1].lista.prev].lista.next = -1;
            listaDados[aux1].lista.prev = -1;
            listaDados[aux1].lista.reg.chave = -1;
            listaDados[aux1].lista.next = -1;
            if (organizaCabecalhoRemove(listaDados, aux1)) {
                return true;
            }

            return false;
        } else {
            while (indice != -1) {
                ///Se o atual é o procurado entra
                if (listaDados[indice].lista.reg.chave == chave) {
                    listaDados[0].cabecalho.quant--;

                    listaDados[indice].lista.reg.chave = -1;
                    listaDados[listaDados[indice].lista.prev].lista.next = listaDados[indice].lista.next;
                    listaDados[listaDados[indice].lista.next].lista.prev = listaDados[indice].lista.prev;
                    listaDados[indice].lista.prev = -1;

                    if (organizaCabecalhoRemove(listaDados, indice)) {
                        return true;
                    } else {
                        return false;
                    }
                }
                indice = listaDados[indice].lista.next;
            }
        }
        std::cout << "Item não está na lista" << std::endl;
        return false;
    }
}


bool mostrarCabecalho(celula listaDados[]) {
    std::cout << "Mostrar cabeçalho" << std::endl;
    std::cout << "Cabeçalho" << std::endl;
    std::cout << "Primeiro: " << listaDados[0].cabecalho.first << std::endl;
    std::cout << "Ultimo: " << listaDados[0].cabecalho.last << std::endl;
    std::cout << "Primeiro livre: " << listaDados[0].cabecalho.free << std::endl;
    std::cout << "Quantidade: " << listaDados[0].cabecalho.quant << std::endl;
    std::cin.ignore();
    return true;
}

bool mostrarRegistrosLivres(celula listaDados[]) {
    if (listaDados[0].cabecalho.free == -1) {
        std::cout << "Não há registros livres!" << std::endl;
    } else {
        int index = listaDados[0].cabecalho.free;
        std::cout << "Os registros livre são " << index;
        if (listaDados[index].lista.next != -1) {
            do {
                std::cout << ", ";
                std::cout << listaDados[index].lista.next;
                index = listaDados[index].lista.next;
            } while (listaDados[index].lista.next != -1);
        }
        std::cout << "!" << std::endl;
    }
    return true;
}

bool mostraNaoOrdernado(celula listaDados[], int tamanho) {
    mostrarCabecalho(listaDados);

    for (int i = 1; i < tamanho; ++i) {

        std::cout << "Posição: " << i << std::endl;
        if (listaDados[i].lista.reg.chave == -1) {
            std::cout << "Dado: Vazio" << std::endl;
        } else {
            std::cout << "Dado: " << listaDados[i].lista.reg.chave << std::endl;
        }
        std::cout << "Next: " << listaDados[i].lista.next << std::endl;
        std::cout << "Prev: " << listaDados[i].lista.prev << std::endl;
    }
    return true;
}

int main() {
    int nRegistros;

    char op = 'j';

    std::cout << "Digite o número de registros :" << std::endl;
    std::cin >> nRegistros;
    nRegistros++;
    celula listaDados[nRegistros];

    iniciaEstrutura(listaDados, nRegistros);

    while (true) {
        std::cout << "MENU" << std::endl;
        std::cout << "1)Inserir" << std::endl;
        std::cout << "2)Remover" << std::endl;
        std::cout << "3)Mostrar dados ordernados" << std::endl;
        std::cout << "4)Mostrar dados não ordernados" << std::endl;
        std::cout << "5)Mostrar cabeçalho" << std::endl;
        std::cout << "6)Mostrar registros livres" << std::endl;
        std::cout << "0)Sair" << std::endl;
        std::cin >> op;

        switch (op) {
            case '1':
                if (listaDados[0].cabecalho.quant + 1 == nRegistros) {
                    std::cout << "A lista está cheia" << std::endl;
                } else {
                    insereRegistro(listaDados);
                }
                break;
            case '2':
                if (listaDados[0].cabecalho.quant == 0) {
                    std::cout << "Não há registros a serem removidos" << std::endl;
                } else {
                    if (removeRegistro(listaDados)) {
                        std::cout << "Dado removido com sucesso!" << std::endl;
                    } else {
                        std::cout << "Algo deu errado na remoção!" << std::endl << std::endl;
                    }
                }
                break;
            case '3':
                std::cout << "Mostrar os dados armazenados" << std::endl;
                mostraList(listaDados);
                break;
            case '4':
                mostraNaoOrdernado(listaDados, nRegistros);
                break;
            case '5':
                mostrarCabecalho(listaDados);
                break;
            case '6':
                mostrarRegistrosLivres(listaDados);
                break;
            case '0':
                return 0;
            default:
                std::cout << "Opção inválida\a" << std::endl;
                break;
        }
    }
}