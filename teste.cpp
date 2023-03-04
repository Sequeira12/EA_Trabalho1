#include <iostream>
#include <array>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
int N;

int conta = 0;
int contadorQRcode = 0;
int gera = 0;

void inicializaZero(int *array, int tamanho, int numero)
{
    for (int i = 0; i < tamanho; i++)
    {
        array[i] = numero;
    }
}

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

bool pre_proc(int *lb, int *cb, int *lt, int *ct, int *qb, int *db, int size)
{
    int contadorpretosLine = 0, contadorpretosCol = 0, contadorQuadrantes = 0;
    // numero de pretos em todas as linhas e colunas

    for (int i = 0; i < size; i++)
    {
        contadorpretosLine += lb[i];
        contadorpretosCol += cb[i];

        if (lb[i] > size || lb[i] < 0)
        {

            return false;
        }
        if (lt[i] > size - 1 || lt[i] < 0 || lt[i] > lb[i] * 2)
        {

            return false;
        }
        if (cb[i] > size || cb[i] < 0 || ct[i] > cb[i] * 2)
        {

            return false;
        }
        if (ct[i] == size - 1)
        {
            if (size % 2 == 0)
            {
                if (cb[i] != size / 2)
                    return false;
            }
            else
            {
                int pacima = size / 2 + 1;
                int pabaixo = size / 2;

                if (cb[i] != pacima && cb[i] != pabaixo)
                {

                    return false;
                }
            }
        }

        if ((lt[i] == 0 && (lb[i] != size && lb[i] != 0)) || (ct[i] == 0 && (cb[i] != size && cb[i] != 0)))
        {

            return false;
        }
        if (ct[i] > size - 1 || ct[i] < 0)
        {

            return false;
        }
    }

    // numero de pretos em todos os quadrantes
    for (int i = 0; i < 4; i++)
    {
        contadorQuadrantes += qb[i];
        if (qb[i] < 0)
        {

            return false;
        }
        if (size % 2 == 0)
        {
            int metade = size / 2;
            int fim = (int)pow(metade, 2);
            if (qb[i] > fim)
            {

                return false;
            }
        }
        else
        {

            int valorbaixo = size / 2;
            int valorcima = size / 2 + 1;

            int toqone = valorbaixo * valorbaixo; // q[1]
            int toqt = valorcima * valorcima;     // q[3]
            int toqzero = valorcima * valorbaixo; // q[0],q[2]

            if (qb[0] > toqzero || qb[1] > toqone || qb[2] > toqzero || qb[3] > toqt)
            {

                return false;
            }
        }
        if (i < 2)
        {

            if (db[i] < 0 || db[i] > size)
            {

                return false;
            }
        }
    }

    // valor dos pretos totais linha diferente dos da coluna ou dos quadrante.....
    if (contadorpretosLine != contadorpretosCol || contadorpretosLine != contadorQuadrantes || contadorpretosCol != contadorQuadrantes)
    {
        return false;
    }
    return true;
}

void LeituraQrCode(int *lb, int *cb, int *lt, int *ct, int *qb, int *db, int size)
{
    int valor, i;
    for (i = 0; i < size; i++)
    {
        cin >> valor;
        lb[i] = valor;
    }
    for (i = 0; i < size; i++)
    {
        cin >> valor;
        cb[i] = valor;
    }
    for (i = 0; i < size; i++)
    {
        cin >> valor;
        lt[i] = valor;
    }
    for (i = 0; i < size; i++)
    {
        cin >> valor;
        ct[i] = valor;
    }
    for (i = 0; i < 4; i++)
    {
        cin >> valor;
        qb[i] = valor;
    }
    for (i = 0; i < 2; i++)
    {
        cin >> valor;
        db[i] = valor;
    }
}

/*
Verifica se o nº de pretos em todas as linhas dá o mesmo que os quadrantes todos juntos.
Verifica se o nº de pretos em todas as colunas dá o mesmo que os quadrantes todos juntos.
*/

bool verificacaoFinal(int *lb, int *cb, int *lt, int *ct, int *qb, int *db, int *colunasT, int *colunasP, int *QuadranteP, int *diagonaisP, int *linhasFaltam, int **array, int num, int valor)
{
    for (int i = 0; i < N; i++)
    {
        if (colunasP[i] != cb[i])
            return false;
        if (colunasT[i] != ct[i])
            return false;
    }
    return (QuadranteP[0] == qb[0] && QuadranteP[1] == qb[1] && QuadranteP[2] == qb[2] && QuadranteP[3] == qb[3] && diagonaisP[0] == db[0] && diagonaisP[1] == db[1]);
}

bool verificacaoCombinacao(int *lb, int *cb, int *lt, int *ct, int *qb, int *db, int *colunasT, int *colunasP, int *QuadranteP, int *diagonaisP, int *linhasFaltam, int *array, int num, int linha)
{
    // se for true as restantes linhas estao a 0
    int linha2 = ceil(N / 2);
    if (linha == linha2)
    {
        if (qb[0] != QuadranteP[0] || qb[1] != QuadranteP[1])
        {
            return false;
        }
    }
    if (linhasFaltam[linha] == -1)
    {
        linhasFaltam[linha] = 0;
        for (int i = linha + 1; i < N; i++)
        {
            if (lb[i] != 0)
                linhasFaltam[linha]++;
        }
    }

    if (diagonaisP[0] + linhasFaltam[linha] < db[0] || diagonaisP[1] + linhasFaltam[linha] < db[1])
    {
        return false;
    }
    if (diagonaisP[0] > db[0] || diagonaisP[1] > db[1])
    {
        return false;
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
        if (colunasT[i] > ct[i])
        {
            return false;
        }

        if (colunasT[i] + N - linha - 1 < ct[i])
        {
            return false;
        }

        if (colunasP[i] > cb[i])
        {
            return false;
        }
        // (1-0 == 1 < 5 - 1)
        if (colunasP[i] + linhasFaltam[linha] < cb[i])
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

bool verificacaoAMEIO(int *lb, int *cb, int *lt, int *ct, int *qb, int *db, int **array, int num, int col)
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

void imprimeQRcode(int **array, int tam)
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
                // if(i==k){
                //     cout << "(";
                // }
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

bool contarPretosDiagonal(int *lb, int *cb, int *lt, int *ct, int *qb, int *db, vector<vector<int>> &mat, int k)
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

bool verificaAmeioCombinacoes(int *lb, int *cb, int *lt, int *ct, int *qb, int *db, int linha, vector<int> &combinacao)
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

void ConstroiMatriz(int lb[], int cb[], int lt[], int ct[], int qb[], int db[], int colunasT[], int colunasP[], int QuadranteP[], int diagonaisP[], int linhasFaltam[], int linha, int *combination, int **vec, int **final);

void gerador(int lb[], int cb[], int lt[], int ct[], int qb[], int db[], int colunasT[], int colunasP[], int QuadranteP[], int diagonaisP[], int linhasFaltam[], int preto, int linha, int inicio, int fim, int combination[], int **vec, int **final)
{

    int comb[N];
    // vector<vector<int>> combs;

    if (N == preto && inicio == 0)
    {

        inicializaZero(comb, N, 1);
        ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);
    }
    else if (preto == 0 && inicio == 0)
    {
        inicializaZero(comb, N, 0);
        ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);
    }
    // caso 1 preto com duas transicoes(01000)
    else if (preto == 1 && lt[linha] == 2 && inicio == 0)
    {
        inicializaZero(comb, N, 0);
        for (int i = 1; i < N; i++)
        {
            comb[i] = 1;

            ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);

            comb[i] = 0;
        }
        return;
    }
    else if (lt[linha] == N - 1)
    {
        if (N % 2 == 0)
        {
            inicializaZero(comb, N, 0);
            for (int i = 0; i < N; i += 2)
            {
                comb[i] = 1;
            }
            ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);

            inicializaZero(comb, N, 0);
            for (int i = 1; i < N; i += 2)
            {
                comb[i] = 1;
            }
            ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);
        }
        else
        {
            int valor = N / 2 + 1;
            if (lb[linha] == valor)
            {
                inicializaZero(comb, N, 0);
                for (int i = 0; i < N; i += 2)
                {
                    comb[i] = 1;
                }
                ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);
            }
            else
            {
                inicializaZero(comb, N, 0);
                for (int i = 1; i < N; i += 2)
                {
                    comb[i] = 1;
                }
                ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);
            }
        }
    }

    else if (lt[linha] % 2 == preto && lt[linha] / preto == 2 && inicio == 0)
    {
        inicializaZero(comb, N, 0);
        for (int i = 1; i < N - preto; i++)
        {
            inicializaZero(comb, N, 0);
            for (int j = i + preto; j < N; j++)
            {
                comb[i] = 1;
                comb[j] = 1;
                ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);
                comb[i] = 0;
                comb[j] = 0;
            }
        }
    }

    else if (lt[linha] == 1 && preto == N - 1 && inicio == 0)
    {
        inicializaZero(comb, N, 1);

        // 0 fim
        comb[N - 1] = 0;
        ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);

        inicializaZero(comb, N, 1);
        // 0 inicio
        comb[0] = 0;
        ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);
    }
    else if (lt[linha] == 1 && inicio == 0 && preto != N - 1)
    {
        inicializaZero(comb, N, 0);
        for (int i = 0; i < preto; i++)
        {
            comb[i] = 1;
        }
        ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);

        inicializaZero(comb, N, 0);
        for (int i = N - preto; i < N; i++)
        {
            comb[i] = 1;
        }
        ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);
    }

    else if (preto == N - 1 && inicio == 0)
    {

        if (lt[linha] == 2)
        {
            int contador = 1;
            inicializaZero(comb, N, 1);

            for (int i = 1; i < N - 1; i++)
            {
                inicializaZero(comb, N, 1);
                comb[i] = 0;
                ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);
            }
        }

        else if (lt[linha] == 1)
        {
            inicializaZero(comb, N, 1);

            comb[N - 1] = 0;
            ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);

            comb[0] = 0;

            for (int i = 1; i < N; i++)
            {
                comb[i] = 1;
            }

            ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);
        }
    }
    else
    {

        inicializaZero(comb, N, 0);
        for (int i = 0; i < preto; i++)
        {
            comb[i] = 1;
        }

        do
        {
            ConstroiMatriz(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, linha, comb, vec, final);
        } while (prev_permutation(comb, comb + N));
    }
}

void ConstroiMatriz(int lb[], int cb[], int lt[], int ct[], int qb[], int db[], int colunasT[], int colunasP[], int QuadranteP[], int diagonaisP[], int linhasFaltam[], int linha, int combination[], int **vec, int **final)
{
    printf("%d %d %d\n", lb[0], lb[1], lb[2]);
    if (combination[linha] == 1)
        diagonaisP[0]++;
    if (combination[N - linha - 1] == 1)
        diagonaisP[1]++;

    for (int i = 0; i < N; i++)
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

            if (linha != 0)
            {
                if (vec[linha - 1][i] == 0)
                    colunasT[i] += 1;
            }

            QuadranteP[retornaQuadrante(linha + 1, i + 1) - 1]++;
            colunasP[i]++;
        }
    }

    if (!verificacaoCombinacao(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, combination, N, linha))
    {
        if (combination[linha] == 1)
            diagonaisP[0]--;
        if (combination[N - linha - 1] == 1)
            diagonaisP[1]--;
        for (int i = 0; i < N; i++)
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

                if (linha != 0)
                {
                    if (vec[linha - 1][i] == 0)
                        colunasT[i] -= 1;
                }

                QuadranteP[retornaQuadrante(linha + 1, i + 1) - 1]--;
                colunasP[i]--;
            }
        }

        return;
    }
    else
    {
        vec[linha] = combination;
        if (linha == N - 1)
        {

            if (verificacaoFinal(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, vec, N, 1))
            {

                final = vec;

                contadorQRcode++;
            }

            if (combination[linha] == 1)
                diagonaisP[0]--;
            if (combination[N - linha - 1] == 1)
                diagonaisP[1]--;
            for (int i = 0; i < N; i++)
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

                    if (linha != 0)
                    {
                        if (vec[linha - 1][i] == 0)
                            colunasT[i] -= 1;
                    }

                    QuadranteP[retornaQuadrante(linha + 1, i + 1) - 1]--;
                    colunasP[i]--;
                }
            }

            return;
        }

        gerador(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, lb[linha + 1], linha + 1, 0, N - 1, combination, vec, final);

        if (combination[linha] == 1)
            diagonaisP[0]--;
        if (combination[N - linha - 1] == 1)
            diagonaisP[1]--;
        for (int i = 0; i < N; i++)
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

                if (linha != 0)
                {
                    if (vec[linha - 1][i] == 0)
                        colunasT[i] -= 1;
                }

                QuadranteP[retornaQuadrante(linha + 1, i + 1) - 1]--;
                colunasP[i]--;
            }
        }
    }
    return;
}

int main()
{
    // auto start = std::chrono::high_resolution_clock::now();
    int numeroQR;
    cin >> numeroQR;

    for (int i = 0; i < numeroQR; i++)
    {
        contadorQRcode = 0;
        int numero;
        cin >> numero;

        N = numero;

        int lb[numero];
        int cb[numero];
        int lt[numero];
        int ct[numero];
        int qb[4];
        int db[2];

        int linha = 0;

        LeituraQrCode(lb, cb, lt, ct, qb, db, N);

        if (!pre_proc(lb, cb, lt, ct, qb, db, N))
        {
            printf("DEFECT: No QR Code generated!\n");
        }

        else
        {
            int arrayNovo[numero][numero];
            int ArrayFinal[numero][numero];

            int colunasT[N];
            int colunasP[N];
            int QuadranteP[4];
            int diagonaisP[2];
            int linhasFaltam[N];
            for (int i = 0; i < N; i++)
            {
                linhasFaltam[i] = -1;
            }
            int combinacao[N];
            gerador(lb, cb, lt, ct, qb, db, colunasT, colunasP, QuadranteP, diagonaisP, linhasFaltam, lb[linha], linha, 0, N - 1, combinacao, reinterpret_cast<int **>(arrayNovo), reinterpret_cast<int **>(ArrayFinal));

            if (contadorQRcode == 1)
            {
                imprimeQRcode(reinterpret_cast<int **>(ArrayFinal), numero);
            }
            else if (contadorQRcode > 1)
            {
                printf("INVALID: %d QR Codes generated!\n", contadorQRcode);
            }
            else
            {
                printf("DEFECT: No QR Code generated!\n");
            }

            // auto stop = std::chrono::high_resolution_clock::now();
            // auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
            // cout << duration.count() << endl;
        }
    }
    return 0;
}