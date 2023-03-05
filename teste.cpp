#include <iostream>
#include <cstdlib> // necessário para gerar números aleatórios
#include <ctime>   // necessário para inicializar a semente dos números aleatórios
#include <cmath>
using namespace std;
const int tamF = 15;
void criarMatriz(int matriz[][tamF])
{
    // inicializa a semente dos números aleatórios
    srand(time(NULL));

    // preenche a matriz com números aleatórios entre 0 e 1
    for (int i = 0; i < tamF; i++)
    {
        for (int j = 0; j < tamF; j++)
        {
            matriz[i][j] = rand() % 2;
        }
    }
}
int retornaQuadrante(int linha, int coluna)
{
    int a = floor(tamF / 2);

    if (linha <= a && coluna > a)
    {

        return 1;
    }
    if (linha <= a && coluna <= a)
    {
        return 2;
    }
    if (linha > a && coluna <= a)
    {

        return 3;
    }
    if (linha > a && coluna > a)
    {

        return 4;
    }
    return 0;
}
void imprimeQRcode(int matriz[][tamF])
{
    int tam = tamF;
    cout << "VALID: 1 QR Code generated!\n";
    cout << "+";
    for (int i = 0; i < tam; i++)
    {
        cout << "-";
    }
    cout << "+\n";
    for (int i = 0; i < tam; i++)
    {
        cout << "|";
        for (int k = 0; k < tam; k++)
        {
            if (matriz[i][k] == 0)
            {
                cout << " ";
            }
            if (matriz[i][k] == 1)
            {
                // if(i==k){
                //     cout << "(";
                // }
                cout << "#";
            }
            if (matriz[i][k] == 2)
            {
                cout << "_";
            }
        }

        cout << "|\n";
    }
    cout << "+";
    for (int i = 0; i < tam; i++)
    {
        cout << "-";
    }
    cout << "+\n";
}

int main()
{
    int matriz[tamF][tamF];

    criarMatriz(matriz);
    int lb[tamF] = {0};
    int lt[tamF] = {0};
    int cb[tamF] = {0};
    int ct[tamF] = {0};
    int qb[4] = {0, 0, 0, 0};
    int db[2] = {0, 0};

    int contadorL = 0, contadorC = 0;
    for (int i = 0; i < tamF; i++)
    {
        for (int j = 0; j < tamF; j++)
        {
            int quanto = retornaQuadrante(i + 1, j + 1);

            if (matriz[i][j] == 1)
            {
                lb[i]++;
                cb[j]++;
                qb[quanto - 1]++;
            }
        }
    }

    for (int i = 0; i < tamF; i++)
    {
        for (int j = 1; j < tamF; j++)
        {
            if (matriz[i][j] != matriz[i][j - 1])
            {
                lt[i]++;
            }
        }
    }

    for (int i = 0; i < tamF; i++)
    {
        for (int j = 1; j < tamF; j++)
        {

            if (matriz[j][i] != matriz[j - 1][i])
            {
                ct[i]++;
            }
        }
    }

    for (int i = 0; i < tamF; i++)
    {
        if (matriz[i][i] == 1)
        {
            db[0]++;
        }
        printf("%d -- %d\n", (tamF - i - 1), i);
        if (matriz[tamF - i - 1][i] == 1)
        {
            db[1]++;
        }
    }

    // imprime a matriz

    imprimeQRcode(matriz);

    for (int i = 0; i < tamF; i++)
    {
        printf("%d ", lb[i]);
    }
    printf("\n");

    for (int i = 0; i < tamF; i++)
    {
        printf("%d ", cb[i]);
    }
    printf("\n");
    for (int i = 0; i < tamF; i++)
    {
        printf("%d ", lt[i]);
    }
    printf("\n");
    for (int i = 0; i < tamF; i++)
    {
        printf("%d ", ct[i]);
    }
    printf("\n");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", qb[i]);
    }
    printf("\n");
    for (int i = 0; i < 2; i++)
    {
        printf("%d ", db[i]);
    }
    printf("\n");
    return 0;
}