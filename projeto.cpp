#include <iostream>
#include <array>
#include <cmath>

using namespace std;
const int tamanho = 30;
void LeituraQrCode(int lb[], int cb[], int lt[], int ct[], int qb[], int db[], int size)
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

void ImprimirTeste(int lb[], int cb[], int lt[], int ct[], int qb[], int db[], int size)
{
  int valor, i;
  cout << endl
       << "ARRAY LB: ";
  for (i = 0; i < size; i++)
  {
    cout << lb[i] << " ";
  }
  cout << endl
       << "ARRAY CB: ";
  for (i = 0; i < size; i++)
  {
    cout << cb[i] << " ";
  }
  cout << endl
       << "ARRAY LT: ";
  for (i = 0; i < size; i++)
  {
    cout << lt[i] << " ";
  }
  cout << endl
       << "ARRAY CT: ";
  for (i = 0; i < size; i++)
  {
    cout << ct[i] << " ";
  }
  cout << endl
       << "ARRAY QB: ";
  for (i = 0; i < 4; i++)
  {
    cout << qb[i] << " ";
  }
  cout << endl
       << "ARRAY DB: ";
  for (i = 0; i < 2; i++)
  {

    cout << db[i] << " ";
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

int retornaQuadrante(int linha, int coluna, int N)
{
  if (linha <= floor(N / 2) && coluna > floor(N / 2))
  {
    return 1;
  }
  if (linha <= floor(N / 2) && coluna <= floor(N / 2))
  {
    return 2;
  }
  if (linha > floor(N / 2) && coluna <= floor(N / 2))
  {
    return 3;
  }
  if (linha > floor(N / 2) && coluna > floor(N / 2))
  {
    return 4;
  }
  return 0;
}

int verificaDefeito(int lb[], int cb[], int lt[], int ct[], int qb[], int db[], int N)
{
  int soma = 0;
  int fl = floor(N / 2 + 1);
  int result = pow(fl, 2.0);
  // Verifica linha e colunas (colors e transitions)
  for (int i = 0; i < N; i++)
  {
    if (lb[i] < 0 || lb[i] > N || cb[i] < 0 || cb[i] > N)
    {
      return 0;
    }
    if (lt[i] < 0 || lt[i] > N - 1 || ct[i] < 0 || ct[i] > N - 1)
    {
      return 0;
    }
  }
  // Verifica diagonais
  for (int i = 0; i < 2; i++)
  {
    if (db[i] < 0 || db[i] > N)
    {
      return 0;
    }
  }
  // Verifica quadrantes
  for (int i = 0; i < 4; i++)
  {
    soma += qb[i];
  }

  if (soma > result)
  {
    return 0;
  }

  return 1;
}

/*
Verifica se é possivel gerar um codigo
*/
int VerificaInvalido(int lb[], int cb[], int lt[], int ct[], int qb[], int db[], int N)
{
  int verificalb = 0, verificacb = 0, verificact = 0, verificalt = 0, verificaqb = 0;
  for (int i = 1; i < N; i++)
  {
    if (lb[0] == lb[i])
    {
      verificalb++;
    }
    if (cb[0] == cb[i])
    {
      verificacb++;
    }
    if (lt[0] == lt[i])
    {
      verificalt++;
    }
    if (ct[0] == ct[i])
    {
      verificact++;
    }
  }
  for (int i = 1; i < 4; i++)
  {
    if (qb[0] == qb[i])
    {
      verificaqb++;
    }
  }
  if (verificalb != N - 1 || verificacb != N - 1 || verificact != N - 1 || verificalt != N - 1 || verificaqb != 3)
  {
    return 0;
  }
  return 1;
}

/*
Verifica se o nº de pretos em todas as linhas dá o mesmo que os quadrantes todos juntos.
Verifica se o nº de pretos em todas as colunas dá o mesmo que os quadrantes todos juntos.
*/
bool verificaLinhasColunasQuadrante(int lb[], int cb[], int qb[], int num)
{
  int somalb = 0, somacb = 0, somaqb = 0;
  for (int i = 0; i < num; i++)
  {
    somalb += lb[i];
    somacb += cb[i];
  }
  for (int i = 0; i < 4; i++)
  {
    somaqb += qb[i];
  }

  return (somalb == somaqb && somacb == somaqb);
}

void preenche(int array[tamanho][tamanho], int tam)
{
  for (int i = 0; i < tam; i++)
  {
    for (int k = 0; k < tam; k++)
    {
      array[i][k] = 0;
    }
  }
}

void imprimeQRcode(int array[tamanho][tamanho], int tam)
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
      else
      {
        cout << "#";
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

  int numeroQR;
  cin >> numeroQR;

  for (int i = 0; i < numeroQR; i++)
  {
    int numero;
    cin >> numero;
    int array[tamanho][tamanho];
    int tamanho = numero;
    preenche(array, numero);
    int lb[numero];
    int cb[numero];
    int lt[numero];
    int ct[numero];
    int qb[numero];

    int db[2];
    LeituraQrCode(lb, cb, lt, ct, qb, db, numero);

    if (!verificaDefeito(lb, cb, lt, ct, qb, db, numero))
    {
      cout << "DEFECT: No QR Code generated!" << endl;
    }
    else
    {
      if (!verificaLinhasColunasQuadrante(lb, cb, qb, numero))
      {
        cout << "DEFECT: No QR Code generated!" << endl;
      }
      else if (VerificaInvalido(lb, cb, lt, ct, qb, db, numero))
      {
        cout << "INVALID: " << numero / qb[0] << " QR Codes generated!" << endl;
      }
      else
      {
        // chamar aqui a função que mete os 0's e 1's
        imprimeQRcode(array, numero);
      }
    }
  }

  return 0;
}
