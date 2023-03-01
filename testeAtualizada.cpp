#include <iostream>
#include <array>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>

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
/*
vector<int> colunasP;
vector<int> diagonaisP;
vector<int> QuadrantesP; */

int conta = 0;
int contadorQRcode = 0;
int gera = 0;
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

/*
Verifica se o nº de pretos em todas as linhas dá o mesmo que os quadrantes todos juntos.
Verifica se o nº de pretos em todas as colunas dá o mesmo que os quadrantes todos juntos.
*/
bool verificacaoFinal(vector<vector<int>> &array, int num, int valor)
{
    int arrayqb[4] = {0, 0, 0, 0};
    int count = 0, count2 = 0;
    for (int col = 0; col < num; col++)
    {
        if (array[col][col] == 1)
        {
            count++;
        }
        if (array[N - col - 1][col] == 1)
        {
            count2++;
        }
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
    // printf("%d %d\n", count, count2);
    return (arrayqb[0] == qb[0] && arrayqb[1] == qb[1] && arrayqb[2] == qb[2] && arrayqb[3] == qb[3] && count == db[0] && count2 == db[1]);
}

bool verificacaoTransicoes(vector<int> diagonaisP, vector<int> colunaP, vector<int> QuadranteP, vector<int> colunasT, vector<int> &array, int num, int linha)
{
    // n - linha - 1 - (db[0] - diagonaisP[0]) >= 0
    int numero_total0 = N - linha - 1 - db[0] - diagonaisP[0];
    int numero_total1 = N - linha - 1;  // numero total possiveis
    int falta0 = db[0] - diagonaisP[0]; // numero que faltam pintar

    int falta1 = db[1] - diagonaisP[1]; // numero que faltam pintar
                                        // printf("Linha %d, %d %d\n", linha, numero_total1, falta0);

    // COMPO ESTA CONDICAO
    /*    if (diagonaisP[0] + N - linha - 1 < db[0] || diagonaisP[1] + N - linha - 1 < db[1])
       {
           if (db[1] != 0 && db[0] != 0 && diagonaisP[0] + N - linha - 1 != db[0] && diagonaisP[1] + N - linha - 1 != db[1])
           {
               return false;
           }
       }
    */
    if (diagonaisP[0] > db[0] || diagonaisP[1] > db[1])
    {

        // printf("Line %d , diagonais %d  --> final%d \n", linha, diagonaisP[1], db[1]);
        if (db[1] != 0 && db[0] != 0)
        {
            return false;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (qb[i] < QuadranteP[i])
        {

            return false;
        }
    }

    int somaLB = 0, somaLT = 0, somaCP = 0, somaCT = 0;
    for (int i = 0; i < num; i++)
    {
        int quadradosPossiveis = N - linha - 1;

        //  printf("Linha: (%d) - > %d --t [%d] e total %d\n", linha, quadradosPossiveis, colunasT[i], ct[i]);
        //  printf(" A DIFERENCA é: %d  e as possbilidade %d\n", (ct[i] - colunasT[i]), quadradosPossiveis);
        if (colunasT[i] > ct[i])
        {
            return false;
        }

        if ((ct[i] - colunasT[i]) > quadradosPossiveis)
        {
            return false;
        }
        if (colunaP[i] > cb[i])
        {
            return false;
        }
        //(1-0 == 1 < 5 - 1)
        if (colunaP[i] + N - linha - 1 < cb[i])
        {
            return false;
        }

        if (array[i] == 1)
        {

            somaLB += 1;
        }
        if (i != num - 1)
        {
            if (array[i] != array[i + 1])
            {
                somaLT += 1;
            }
        }
    }
    if (somaLB != lb[linha] || somaLT != lt[linha])
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

void imprimeQRcode(vector<vector<int>> &array, int tam)
{
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

bool verificaAmeioCombinacoes(int linha, vector<int> &combinacao)
{
    if (combinacao.size() == 0)
    {
        return true;
    }
    // N - linha - 1
    int falta = N - combinacao.size();
    int contaP = 0, contaT = 0;
    for (int i = 0; i < combinacao.size() - 1; i++)
    {

        if (combinacao[i] == 1)
        {
            contaP += 1;
        }
        if (i != combinacao.size() - 1)
        {
            if (combinacao[i] != combinacao[i + 1])
            {
                contaT += 1;
            }
        }
    }
    // n - linha - 1 - (db[0] - diagonaisP[0]) >= 0
    return (falta - (lb[linha] - contaP) >= 0 || ((falta - 1) - (lt[linha] - contaT) >= 0));
}

void ConstroiMatriz(vector<int> diagonaisP, vector<int> colunasP, vector<int> QuadrantesP, vector<int> colunasT, int linha, vector<int> &combination, vector<vector<int>> &vec);

void gerador(vector<int> diagonaisP, vector<int> colunaP, vector<int> QuadranteP, vector<int> colunasT, int preto, int linha, int inicio, int fim, vector<int> &combination, vector<vector<int>> &vec)
{
    if (linha == N)
    {
        return;
    }
    vector<int> comb;
    vector<vector<int>> combs;

    if (N == preto && inicio == 0)
    {

        comb = vector<int>(N, 1);
        ConstroiMatriz(diagonaisP, colunaP, QuadranteP, colunasT, linha, comb, vec);
    }
    else if (preto == 0 && inicio == 0)
    {
        comb = vector<int>(N, 0);
        ConstroiMatriz(diagonaisP, colunaP, QuadranteP, colunasT, linha, comb, vec);
    }
    // caso 1 preto com duas transicoes(01000)
    else if (preto == 1 && lt[linha] == 2 && inicio == 0)
    {
        comb = vector<int>(N, 0);
        for (int i = 1; i < N; i++)
        {
            comb[i] = 1;

            ConstroiMatriz(diagonaisP, colunaP, QuadranteP, colunasT, linha, comb, vec);

            comb[i] = 0;
        }
        return;
    }
    else if (preto == 2 && lt[linha] == 4 && inicio == 0)
    {
        comb = vector<int>(N, 0);
        for (int i = 1; i < N - 2; i++)
        {
            comb = vector<int>(N, 0);
            for (int j = i + 2; j < N; j++)
            {
                comb[i] = 1;
                comb[j] = 1;
                ConstroiMatriz(diagonaisP, colunaP, QuadranteP, colunasT, linha, comb, vec);
                comb[i] = 0;
                comb[j] = 0;
            }
        }
    }

    else if (lt[linha] == 1 && preto == N - 1 && inicio == 0)
    {
        comb = vector<int>(N, 1);

        // 0 fim
        comb[N - 1] = 0;
        ConstroiMatriz(diagonaisP, colunaP, QuadranteP, colunasT, linha, comb, vec);

        comb = vector<int>(N, 1);
        // 0 inicio
        comb[0] = 0;
        ConstroiMatriz(diagonaisP, colunaP, QuadranteP, colunasT, linha, comb, vec);
    }
    /* else if (preto == N - 2 && lt[linha] == 4 && inicio == 0)
    {

        for (int i = 1; i < N - 3; i++)
        {
            comb = vector<int>(N, 1);
            for (int j = i + 2; j < N - 1; j++)
            {
                comb[i] = 0;
                comb[j] = 0;

                ConstroiMatriz(linha, comb, vec);
                comb = vector<int>(N, 1);
            }
        }
    }
    */

    else if (preto == N - 1 && inicio == 0)
    {

        if (lt[linha] == 2)
        {
            int contador = 1;
            comb = vector<int>(N, 1);

            for (int i = 1; i < N - 1; i++)
            {
                comb = vector<int>(N, 1);
                comb[i] = 0;
                ConstroiMatriz(diagonaisP, colunaP, QuadranteP, colunasT, linha, comb, vec);
            }
        }

        else if (lt[linha] == 1)
        {
            comb = vector<int>(N, 1);

            comb[N - 1] = 0;
            ConstroiMatriz(diagonaisP, colunaP, QuadranteP, colunasT, linha, comb, vec);

            comb[0] = 0;

            for (int i = 1; i < N; i++)
            {
                comb[i] = 1;
            }

            ConstroiMatriz(diagonaisP, colunaP, QuadranteP, colunasT, linha, comb, vec);
        }
    }
    else
    {

        comb = vector<int>(N, 0);
        for (int i = 0; i < preto; i++)
        {
            comb[i] = 1;
        }
        do
        {
            ConstroiMatriz(diagonaisP, colunaP, QuadranteP, colunasT, linha, comb, vec);
        } while (prev_permutation(comb.begin(), comb.end()));
    }
}

void ConstroiMatriz(vector<int> diagonaisP, vector<int> colunasP, vector<int> QuadrantesP, vector<int> colunasT, int linha, vector<int> &combination, vector<vector<int>> &vec)
{

    for (int i = 0; i < combination.size(); i++)
    {
        if (combination[i] == 0)
        {
            if (linha != 0)
            {
                if (vec[linha - 1][i] == 1)
                    colunasT[i] += 1;
            }
        }
        if (combination[i] == 1)
        {

            if (linha == i)
            {
                diagonaisP[0]++;
            }
            if (N - linha + 1 == i)
            {
                diagonaisP[1]++;
            }

            if (linha != 0)
            {
                if (vec[linha - 1][i] == 0)
                    colunasT[i] += 1;
            }

            QuadrantesP[retornaQuadrante(linha + 1, i + 1) - 1]++;
            colunasP[i]++;
        }
    }

    if (!verificacaoTransicoes(diagonaisP, colunasP, QuadrantesP, colunasT, combination, N, linha))
    {
        for (int i = 0; i < combination.size(); i++)
        {
            if (combination[i] == 0)
            {
                if (linha != 0)
                {
                    if (vec[linha - 1][i] == 1)
                        colunasT[i] -= 1;
                }
            }
            if (combination[i] == 1)
            {

                if (linha == i)
                {
                    diagonaisP[0]--;
                }
                if (N - linha + 1 == i)
                {
                    diagonaisP[1]--;
                }

                if (linha != 0)
                {
                    if (vec[linha - 1][i] == 0)
                        colunasT[i] -= 1;
                }

                QuadrantesP[retornaQuadrante(linha + 1, i + 1) - 1]--;
                colunasP[i]--;
            }
        }
    }
    else
    {
        vec[linha] = combination;
        // printf("LINHA: %d ,%d %d %d %d\n", linha, diagonaisP[0], db[0], diagonaisP[1], db[1]);

        if (linha == N - 1)
        {
            // imprimeQRcode(vec, N);
            if (verificacaoFinal(vec, N, 1))
            {

                ArrayFinal = vec;

                contadorQRcode++;
            }

            colunasP = vector<int>(N, 0);
            QuadrantesP = vector<int>(4, 0);
            diagonaisP = vector<int>(2, 0);

            return;
        }

        gerador(diagonaisP, colunasP, QuadrantesP, colunasT, lb[linha + 1], linha + 1, 0, N - 1, combination, vec);

        QuadrantesP = vector<int>(4, 0);
        colunasP = vector<int>(N, 0);
        diagonaisP = vector<int>(2, 0);
    }
    return;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
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
        vector<int> colunasT;
        vector<int> colunasP;
        vector<int> diagonaisP;
        vector<int> QuadrantesP;
        colunasT = vector<int>(N, 0);
        colunasP = vector<int>(N, 0);
        QuadrantesP = vector<int>(4, 0);
        diagonaisP = vector<int>(2, 0);
        // printf("LINHA: %d and N %d\n", lb[N - 1], N);
        // vector<int> diagonaisP, vector<int> colunaP, vector<int> QuadranteP,
        gerador(diagonaisP, colunasP, QuadrantesP, colunasT, lb[linha], linha, 0, N - 1, combinacao, arrayNovo);
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
            printf("DEFECT: No QR Code generated!\n");
        }

        /*         auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
                cout << duration.count() << endl;
         */
        lb.clear();
        lt.clear();
        cb.clear();
        ct.clear();
        qb.clear();
        db.clear();
    }
    return 0;
}
