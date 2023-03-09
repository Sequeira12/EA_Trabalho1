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
vector<bool> QuadrantesCheios;
vector<bool> QuadrantesVazios;
vector<bool> colunasCheias;
int colunas_cheias = 0;

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

vector<int> colunasP;
vector<int> diagonaisP;
vector<int> QuadranteP;
vector<int> colunasT;
vector<int> linhasFaltam;

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

bool pre_proc(int size)
{

    int contadorpretosLine = 0, contadorpretosCol = 0, contadorQuadrantes = 0;
    // numero de pretos em todas as linhas e colunas
    int contadorpretoLine2 = 0, contadorpretoCol2 = 0;
    for (int i = 0; i < size; i++)
    {
        int meio = ceil(size / 2);

        if (i >= meio)
        {

            contadorpretoLine2 += lb[i];
            contadorpretoCol2 += cb[i];
        }

        if (i == meio)
        {
            if (contadorpretosCol != qb[2] + qb[1])
            {
                return false;
            }
            if (contadorpretosLine != qb[0] + qb[1])
            {
                return false;
            }
        }
        if (i == size - 1)
        {
            if (contadorpretoLine2 != qb[2] + qb[3])
            {
                return false;
            }
            if (contadorpretoCol2 != qb[0] + qb[3])
            {
                return false;
            }
        }
        contadorpretosLine += lb[i];
        contadorpretosCol += cb[i];

        if (cb[i] == N)
        {
            colunasCheias[i] = true;
            colunas_cheias += 1;
        }

        if (lb[i] > size || lb[i] < 0)
        {

            return false;
        }
        if (lt[i] > size - 1 || lt[i] < 0 || lt[i] > lb[i] * 2)
        {

            return false;
        }
        if (lb[i] > 1 && lb[i] != N)
        {
            if (lt[i] < 1 || lt[i] > lb[i] * 2)
            {
                return false;
            }
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
    int max;

    int valor = N;
    int maxq0 = floor(N / 2) * floor(N / 2 + 1);
    int maxq1 = floor(N / 2) * floor(N / 2);
    int maxq2 = floor(N / 2 + 1) * floor(N / 2 + 1);

    int array[4] = {maxq0, maxq1, maxq0, maxq2};

    // numero de pretos em todos os quadrantes
    for (int i = 0; i < 4; i++)
    {
        if (qb[i] == 0)
        {
            QuadrantesVazios[i] = true;
        }

        if (qb[i] == array[i])
        {
            QuadrantesCheios[i] = true;
        }
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
            if (qb[1] + qb[3] < db[0] || qb[0] + qb[2] < db[1])
            {
                return false;
            }
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
    for (int i = 0; i < N; i++)
    {
        if (colunasP[i] != cb[i])
            return false;
        if (colunasT[i] != ct[i])
            return false;
    }
    return (QuadranteP[0] == qb[0] && QuadranteP[1] == qb[1] && QuadranteP[2] == qb[2] && QuadranteP[3] == qb[3] && diagonaisP[0] == db[0] && diagonaisP[1] == db[1]);
}

bool verificacaoCombinacao(vector<int> &array, int num, int linha)
{

    int linha2 = ceil(N / 2);
    int falta = linha2 - linha - 1;

    // quando chegamos a linha anterior ao limite do quad
    if (linha == linha2 - 1)
    {
        if (qb[0] != QuadranteP[0] || qb[1] != QuadranteP[1])
        {
            return false;
        }
    }

    if (linha < linha2)
    {
        if (falta * ceil(N / 2) < qb[1] - QuadranteP[1] || falta * (N - ceil(N / 2)) < qb[0] - QuadranteP[0])
        {

            return false;
        }
    }
    else
    {
        int f = N - linha - 1;
        if (f * ceil(N / 2) < qb[2] - QuadranteP[2] || f * (N - ceil(N / 2)) < qb[3] - QuadranteP[3])
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
        if (array[i] == 0 && colunasCheias[i])
            return false;

        if (colunasT[i] > ct[i])
        {
            return false;
        }

        if (colunasT[i] + N - linha - 1 < ct[i])
            return false;

        if (colunasP[i] > cb[i])
        {
            return false;
        }

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

void gerador(int preto, int linha, int inicio, int fim, vector<int> &combination, vector<vector<int>> &vec)
{

    vector<int> comb;
    vector<vector<int>> combs;
    int quad = retornaQuadrante(linha + 1, 1);
    int quad2 = retornaQuadrante(linha + 1, N - 1);
    int valor_es = quad - 1, valor_dir = quad2 - 1;

    if ((N == preto && inicio == 0) || (QuadrantesCheios[valor_es] && QuadrantesCheios[valor_dir]))
    {

        comb = vector<int>(N, 1);
        ConstroiMatriz(linha, comb, vec);
    }
    else if (QuadrantesCheios[valor_es] || QuadrantesCheios[valor_dir])
    {

        comb = vector<int>(N, 0);
        if (QuadrantesCheios[valor_es])
        {

            for (int i = 0; i < N / 2; i++)
            {
                comb[i] = 1;
            }

            vector<int> comb2(N - N / 2, 0);

            if (preto > N / 2)
            {
                if(lt[linha]==1 && preto-N/2==N-N/2-1){
                    if(preto-N/2==N-N/2-1){
                        for(int i=N/2;i<N-1;i++){
                            comb[i]=1;
                        }
                        ConstroiMatriz(linha,comb,vec);
                    }
                }

                else if(lt[linha]%2!=0 && preto - N/2==(N-N/2)/2){
                    for (int i=1;i<N+1;i+=2){
                        comb[i]=1;
                    }

                    ConstroiMatriz(linha,comb,vec);
                }

                else if (lt[linha]%2==0 && preto - N/2 == (N-N/2)/2){
                     for (int i=0;i<N+1;i+=2){
                        comb[i]=1;
                    }

                    ConstroiMatriz(linha,comb,vec);
                }

                else{
              
                    for (int k = 0; k < preto - N / 2; k++)
                    {
                        comb2[k] = 1;
                    }

                    do
                    {
                        for (int i = 0; i < N - N / 2; i++)
                        {

                            comb[i + N / 2] = comb2[i];
                        }
                        ConstroiMatriz(linha, comb, vec);
                    } while (prev_permutation(comb2.begin(), comb2.end()));
                }
            }
            else
                ConstroiMatriz(linha, comb, vec);
        }
        else if (QuadrantesCheios[valor_dir])
        {
                for (int i = N / 2; i < N; i++)
                {
                    comb[i] = 1;
                }

                vector<int> comb2(N / 2, 0);

                if (preto > N - N / 2)
                {
                    if(lt[linha==1] && preto-N-N/2==1){
                        if(preto-N-N/2==1){
                            comb[N/2-1]=1;
                            ConstroiMatriz(linha,comb,vec);
                        }
                    }

                    else if(lt[linha]%2==0 && preto-N-N/2==N/4){
                        for (int i=0;i<N/2+1;i+=2){
                            comb[i]=1;
                        }

                        ConstroiMatriz(linha,comb,vec);
                    }

                    else if(lt[linha]%2!=0 && preto-N-N/2==N/4){
                          for (int i=1;i<N/2+1;i+=2){
                            comb[i]=1;
                        }

                        ConstroiMatriz(linha,comb,vec);
                    }
                    
                    else{
                        for (int k = 0; k < preto - (N - N / 2); k++)
                        {
                            comb2[k] = 1;
                        }
                        do
                        {
                            for (int i = 0; i < N / 2; i++)
                            {
                                comb[i] = comb2[i];
                            }
                            ConstroiMatriz(linha, comb, vec);
                        } while (prev_permutation(comb2.begin(), comb2.end()));
                    }
            }
            else
                ConstroiMatriz(linha, comb, vec);
        }
    }
    else if (qb[valor_es] == 0 || qb[valor_dir] == 0)
    {

        comb = vector<int>(N, 0);
        if (qb[valor_es] == 0)
        {
            if(lt[linha]==1 && (preto==1)){
                if(preto==1){
                    comb[N-1]=1;
                    ConstroiMatriz(linha,comb,vec);
                }
            }
            else{
                vector<int> comb2(N - N / 2, 0);
                for (int k = 0; k < preto; k++)
                {
                    comb2[k] = 1;
                }

                do
                {
                    for (int i = 0; i < N - N / 2; i++)
                    {

                        comb[i + N / 2] = comb2[i];
                    }
                    ConstroiMatriz(linha, comb, vec);
                } while (prev_permutation(comb2.begin(), comb2.end()));

            }
        }

        else if (qb[valor_dir] == 0)
        {

            vector<int> comb2(N / 2, 0);

            for (int k = 0; k < preto; k++)
            {
                comb2[k] = 1;
            }
            do
            {
                for (int i = 0; i < N / 2; i++)
                {
                    comb[i] = comb2[i];
                }
                ConstroiMatriz(linha, comb, vec);
            } while (prev_permutation(comb2.begin(), comb2.end()));
        }
    }
    else if (preto == colunas_cheias && inicio == 0)
    {
        comb = vector<int>(N, 0);

        for (int i = 0; i < N; i++)
        {
            if (colunasCheias[i])
                comb[i] = 1;
        }
        ConstroiMatriz(linha, comb, vec);
    }

    else if (preto == colunas_cheias + 1 && inicio == 0)
    {
        // so testar uma posicao
        comb = vector<int>(N, 0);
        for (int i = 0; i < N; i++)
        {
            if (colunasCheias[i])
                comb[i] = 1;
        }
        for (int i = 0; i < N; i++)
        {
            if (comb[i] == 0)
            {
                comb[i] = 1;
                ConstroiMatriz(linha, comb, vec);
                comb[i] = 0;
            }
        }
    }

    else if (preto == 0 && inicio == 0)
    {
        comb = vector<int>(N, 0);
        ConstroiMatriz(linha, comb, vec);
    }

    // caso 1 preto com duas transicoes(01000)
    else if (preto == 1 && lt[linha] == 2 && inicio == 0)
    {
        comb = vector<int>(N, 0);
        for (int i = 1; i < N; i++)
        {
            comb[i] = 1;

            ConstroiMatriz(linha, comb, vec);

            comb[i] = 0;
        }
        return;
    }
    else if (lt[linha] == N - 1)
    {
        if (N % 2 == 0)
        {
            comb = vector<int>(N, 0);
            for (int i = 0; i < N; i += 2)
            {
                comb[i] = 1;
            }
            ConstroiMatriz(linha, comb, vec);

            comb = vector<int>(N, 0);
            for (int i = 1; i < N; i += 2)
            {
                comb[i] = 1;
            }
            ConstroiMatriz(linha, comb, vec);
        }
        else
        {
            int valor = N / 2 + 1;
            if (lb[linha] == valor)
            {
                comb = vector<int>(N, 0);
                for (int i = 0; i < N; i += 2)
                {
                    comb[i] = 1;
                }
                ConstroiMatriz(linha, comb, vec);
            }
            else
            {
                comb = vector<int>(N, 0);
                for (int i = 1; i < N; i += 2)
                {
                    comb[i] = 1;
                }
                ConstroiMatriz(linha, comb, vec);
            }
        }
    }

    else if (lt[linha] % 2 == preto && lt[linha] / preto == 2 && inicio == 0)
    {
        comb = vector<int>(N, 0);
        for (int i = 1; i < N - preto; i++)
        {
            comb = vector<int>(N, 0);
            for (int j = i + preto; j < N; j++)
            {
                comb[i] = 1;
                comb[j] = 1;
                ConstroiMatriz(linha, comb, vec);
                comb[i] = 0;
                comb[j] = 0;
            }
        }
    }

    else if (lt[linha] == 1 && inicio == 0)
    {
        comb = vector<int>(N, 0);
        for (int i = 0; i < preto; i++)
        {
            comb[i] = 1;
        }
        ConstroiMatriz(linha, comb, vec);

        comb = vector<int>(N, 0);
        for (int i = N - preto; i < N; i++)
        {
            comb[i] = 1;
        }
        ConstroiMatriz(linha, comb, vec);
    }

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
                ConstroiMatriz(linha, comb, vec);
            }
        }

        else if (lt[linha] == 1)
        {
            comb = vector<int>(N, 1);

            comb[N - 1] = 0;
            ConstroiMatriz(linha, comb, vec);

            comb[0] = 0;

            for (int i = 1; i < N; i++)
            {
                comb[i] = 1;
            }

            ConstroiMatriz(linha, comb, vec);
        }
    }

    else if (lt[linha] == 2 && preto == 2)
    {
        comb = vector<int>(N, 0);
        comb[0] = 1;
        comb[N - 1] = 1;
        ConstroiMatriz(linha, comb, vec);
        comb = vector<int>(N, 0);
        for (int i = 0; i < N - 1; i++)
        {
            comb[i] = 1;
            comb[i + 1] = 1;
            ConstroiMatriz(linha, comb, vec);
            comb[i] = 0;
            comb[i + 1] = 0;
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

            ConstroiMatriz(linha, comb, vec);
        } while (prev_permutation(comb.begin(), comb.end()));
    }
}

void ConstroiMatriz(int linha, vector<int> &combination, vector<vector<int>> &vec)
{

    if (combination[linha] == 0 && db[0] == N)
        return;
    if (combination[N - linha - 1] == 0 && db[1] == N)
        return;
    if (combination[linha] == 1 && db[0] == 0)
        return;
    if (combination[N - linha - 1] == 1 && db[1] == 0)
        return;

    int count_transicoes = 0;
    int i = 0;
    for (i = 0; i < N - 1; i++)
    {

        if (combination[i] != combination[i + 1])
            count_transicoes += 1;
        if (combination[i] == 1 && cb[i] == 0)
            return;
        if (combination[i] == 0 && cb[i] == N)
            return;

        if (count_transicoes > lt[linha])
            return;
    }

    if (combination[i + 1] == 1 && cb[i + 1] == 0)
        return;
    if (combination[i + 1] == 0 && cb[i + 1] == N)
        return;
    if (count_transicoes != lt[linha])
        return;

    if (combination[linha] == 1)
        diagonaisP[0]++;
    if (combination[N - linha - 1] == 1)
        diagonaisP[1]++;

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

            if (linha != 0)
            {
                if (vec[linha - 1][i] == 0)
                    colunasT[i] += 1;
            }

            QuadranteP[retornaQuadrante(linha + 1, i + 1) - 1]++;
            colunasP[i]++;
        }
    }

    if (!verificacaoCombinacao(combination, N, linha))
    {
        if (combination[linha] == 1)
            diagonaisP[0]--;
        if (combination[N - linha - 1] == 1)
            diagonaisP[1]--;
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

            if (verificacaoFinal(vec, N, 1))
            {
                if (contadorQRcode == 0)
                {
                    ArrayFinal = vec;
                }

                contadorQRcode++;
            }

            if (combination[linha] == 1)
                diagonaisP[0]--;
            if (combination[N - linha - 1] == 1)
                diagonaisP[1]--;
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

        gerador(lb[linha + 1], linha + 1, 0, N - 1, combination, vec);

        if (combination[linha] == 1)
            diagonaisP[0]--;
        if (combination[N - linha - 1] == 1)
            diagonaisP[1]--;
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

    int numeroQR;
    cin >> numeroQR;

    for (int i = 0; i < numeroQR; i++)
    {
        contadorQRcode = 0;
        int numero;
        cin >> numero;

        N = numero;
        colunas_cheias = 0;
        arrayNovo = vector<vector<int>>(numero, vector<int>(numero, 0));
        ArrayFinal = vector<vector<int>>(numero, vector<int>(numero, 0));
        colunasCheias = vector<bool>(numero, false);
        QuadrantesCheios = vector<bool>(4, false);
        QuadrantesVazios = vector<bool>(4, false);

        int linha = 0;

        vector<int> combinacao(N, 0);
        LeituraQrCode(N);

        if (!pre_proc(N))
        {
            printf("DEFECT: No QR Code generated!\n");
        }
        else
        {
            colunasT = vector<int>(N, 0);
            colunasP = vector<int>(N, 0);
            QuadranteP = vector<int>(4, 0);
            diagonaisP = vector<int>(2, 0);
            linhasFaltam = vector<int>(N, -1);

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
                printf("DEFECT: No QR Code generated!\n");
            }
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
