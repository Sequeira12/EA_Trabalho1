#include <iostream>
#include <array>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<int>> arrayNovo;
vector<vector<int>> ArrayFinal;
vector<int> combinacao;
int N;
// pretos por linha
vector<int> lb;
// pretos por coluna
vector<int> cb;
// transicoes por linha
vector<int> lt;
// transicoes por coluna
vector<int> ct;
// pretos por quadrante
vector<int> qb;
// pretos por diagonal
vector<int> db;

int contadorQRcode = 0;

int retornaQuadrante(int linha, int coluna)
{
    int a = floor(N / 2);

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
void LeituraQrCode(int size)
{
    int valor, i;
    for (i = 0; i < size; i++)
    {
        cin >> valor;
        lb.push_back(valor);
    }
    for (i = 0; i < size; i++)
    {
        cin >> valor;
        cb.push_back(valor);
    }
    for (i = 0; i < size; i++)
    {
        cin >> valor;
        lt.push_back(valor);
    }
    for (i = 0; i < size; i++)
    {
        cin >> valor;
        ct.push_back(valor);
    }
    for (i = 0; i < 4; i++)
    {
        cin >> valor;
        qb.push_back(valor);
    }
    for (i = 0; i < 2; i++)
    {
        cin >> valor;
        db.push_back(valor);
    }
}

int somador(int array[], int tam)
{
    int soma = 0;
    for (int i = 0; i < tam; i++)
    {
        soma += array[tam];
    }
    cout << soma << endl;
    return soma;
}

/*
Verifica se o nº de pretos em todas as linhas dá o mesmo que os quadrantes todos juntos.
Verifica se o nº de pretos em todas as colunas dá o mesmo que os quadrantes todos juntos.
*/
bool verificacaoFinal(vector<vector<int>> &array, int num)
{
    int arrayqb[4] = {0, 0, 0, 0};
    for (int col = 0; col < num; col++)
    {
        int somaCB = 0, somaCT = 0;
        for (int i = 0; i < num; i++)
        {
            int quadrante = retornaQuadrante(col + 1, i + 1);

            if (array[col][i] == 1)
            {
                arrayqb[quadrante - 1]++;
            }
            if (array[i][col] == 1)
            {
                somaCB += 1;
            }
            if (i != num - 1)
            {
                if (array[i][col] != array[i + 1][col])
                {
                    somaCT += 1;
                }
            }
        }

        if (somaCB != cb[col] || somaCT != ct[col])
        {

            return false;
        }
    }

    return (arrayqb[0] == qb[0] && arrayqb[1] == qb[1] && arrayqb[2] == qb[2] && arrayqb[3] == qb[3]);
}

bool verificacaoTransicoes(vector<int> &array, int num, int linha)
{
    int somaCB = 0, somaCT = 0;
    for (int i = 0; i < num; i++)
    {

        if (array[i] == 1)
        {
            somaCB += 1;
        }
        if (i != num - 1)
        {
            if (array[i] != array[i + 1])
            {
                somaCT += 1;
            }
        }
    }
    if (somaCB != lb[linha] || somaCT != lt[linha])
    {

        return false;
    }
    return true;
}

bool verificacaoAMEIO(vector<vector<int>> &array, int num, int col)
{
    int soma = 0;
    for (int i = 0; i < num; i++)
    {
        soma += array[i][col];
    }

    if (soma < cb[col])
    {
        return true;
    }
    return false;
}

void preenche(int array[30][30], int tam)
{
    for (int i = 0; i < tam; i++)
    {
        for (int k = 0; k < tam; k++)
        {
            array[i][k] = 0;
        }
    }
}

void imprimeQRcode(vector<vector<int>> &array, int tam)
{
    cout << "VALID: 1 QR code generated!\n";
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
            if (array[i][k] == 0)
            {
                cout << " ";
            }
            if (array[i][k] == 1)
            {
                cout << "#";
            }
            if (array[i][k] == 2)
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

bool contarPretosDiagonal(vector<vector<int>> &mat, int k)
{
    int count = 0;
    int count2 = 0;

    for (int i = 0; i < k; i++)
    {
        if (mat[i][i] == 1)
        {
            count++;
        }
        if (mat[N - i - 1][i] == 1)
        {
            count2++;
        }
    }

    return count == db[0] && count2 == db[1];
}
void ConstroiMatriz(int linha, vector<int> &combination, vector<vector<int>> &vec);
void gerar_combinacoes(int linha, int posicao, int num_pretos, int num_quadrados, vector<int>& combinacao, vector<vector<int>>&vec) {
    if (posicao == num_quadrados) {
        if (combinacao.size() == num_pretos) {
            vector <int> new_combinacao;
            for (int i = 0; i < num_quadrados; i++) {
                if (find(combinacao.begin(), combinacao.end(), i) != combinacao.end()) {
                    new_combinacao.push_back(1);
                } else {
                    new_combinacao.push_back(0);
                }
            }
            ConstroiMatriz(linha,new_combinacao,vec);
            return;

        }
        return;
    }
    combinacao.push_back(posicao);
    gerar_combinacoes(linha,posicao+1, num_pretos, num_quadrados, combinacao,vec);
    combinacao.pop_back();
    gerar_combinacoes(linha,posicao+1, num_pretos, num_quadrados, combinacao,vec);
}
void gerador(int preto, int linha, int inicio, int fim, vector<int> &combination, vector<vector<int>> &vec)
{
	vector<int> comb;
    vector <vector<int>> combs;

	gerar_combinacoes(linha,0,lb[linha],N,comb,vec);
}

void ConstroiMatriz(int linha, vector<int> &combination, vector<vector<int>> &vec)
{

    if (!verificacaoTransicoes(combination, N, linha))
    {

        return;
    }
    else
    {
        vec[linha] = combination;
        if (linha == N - 1)
        {

            if (verificacaoFinal(vec, N) && contarPretosDiagonal(vec, N))
            {
                ArrayFinal = vec;

                contadorQRcode++;
            }

            return;
        }
        gerador(lb[linha + 1], linha + 1, 0, N - 1, combination, vec);
    }
}

int main()
{
    int numeroQR;
    cin >> numeroQR;

    for (int i = 0; i < numeroQR; i++)
    {
        contadorQRcode = 0;
        int numero;
        cin >> numero;

        arrayNovo = vector<vector<int>>(numero, vector<int>(numero, 0));
        ArrayFinal = vector<vector<int>>(numero, vector<int>(numero, 0));

        N = numero;

        int linha = 0;

        vector<int> combinacao(N, 0);
        LeituraQrCode(N);

        // printf("LINHA: %d and N %d\n", lb[N - 1], N);
        gerador(lb[linha], linha, 0, N - 1, combinacao, arrayNovo);
        if (contadorQRcode == 1)
        {
            imprimeQRcode(ArrayFinal, numero);
        }
        else if (contadorQRcode > 1)
        {
            printf("INVALID: %d QR Codes generated!\n", contadorQRcode);
        }
        else
        {
            printf("DEFECT: No QR code generated!\n");
        }
        lb.clear();
        lt.clear();
        cb.clear();
        ct.clear();
        qb.clear();
        db.clear();
    }

    return 0;
}