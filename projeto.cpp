#include <iostream>
#include <array>
#include <cmath>
#include <unordered_set>

using namespace std;
const int tamanho = 30;
unordered_set<int> P;
int contador = 0;
void imprimeQRcode(int array[tamanho][tamanho], int tam);
int Same = 0;
void retira(int lb[], int cb[], int lt[], int ct[], int qb[], int db[], int x, int y)
{
	if (lb[x] > 0)
	{
		lb[x]--;
	}
	if (lt[x] > 0)
	{
		lt[x]--;
	}
	if (cb[y] > 0)
	{
		cb[y]--;
	}
	if (ct[y] > 0)
	{
		ct[y]--;
	}
}

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
	int a = floor(N / 2);
	// printf("Linha %d, coluna %d  e floor %d\n", linha, coluna, a);
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
bool verificacaoFinal(int cb[], int ct[], int array[tamanho][tamanho], int num)
{

	for (int col = 0; col < num; col++)
	{
		int somaCB = 0, somaCT = 0;
		for (int i = 0; i < num; i++)
		{

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

	return true;
}

bool verificacaoAMEIO(int cb[], int ct[], int array[tamanho][tamanho], int num, int linha)
{

	for (int col = 0; col < num; col++)
	{
		int somaCB = 0, somaCT = 0;
		for (int i = 0; i < num; i++)
		{

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
		printf("%d:CB  %d --> %d  CT %d ---->%d\n", col, somaCB, cb[col], somaCT, ct[col]);

		if (somaCB > cb[col])
		{
			printf("FODEU-se\n\n");
			return false;
		}
	}

	return true;
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
int array2[tamanho][tamanho];
void teste(int lb[], int cb[], int lt[], int ct[], int qb[], int db[], int N, int x, int y, int array[][tamanho])
{

	contador++;
	int next = x + 1;
	// imprimeQRcode(array, N);
	/*if (verificacaoAMEIO(cb, ct, array, N, x) == false)
	{
		return;
	};
	 if (verificacaoAMEIO(cb, ct, array, N, x) == 0)
	{
		// printf("ENTROU\n");
		return;
	}
	*/
	if (x == N)
	{
		// imprimeQRcode(array, N);
		int conta = 0, conta2 = 0;
		for (int i = 0; i < N; i++)
		{
			if (array[i][i] == 1)
			{
				conta++;
			}

			if (array[N - 1 - i][i] == 1)
			{
				conta2++;
			}
		}
		// true (conta == db[0] && conta2 == db[1])
		if (conta == db[0] && conta2 == db[1] && verificacaoFinal(cb, ct, array, N))
		{
			Same++;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					array2[i][j] = array[i][j];
				}
			}
		}
		return;
	}

	// existem N-1 pretos e verifico se tem duas ou uma transição
	if (lb[x] == N - 1)
	{
		if (lt[x] == 2)
		{
			int contador = 1;
			for (int i = 1; i < N - 1; i++)
			{
				array[x][0] = 1;
				array[x][N - 1] = 1;
				for (int j = 0; j < N - 1; j++)
				{
					if (j != i)
					{
						array[x][j] = 1;
					}
					else
					{
						array[x][j] = 0;
					}
				}
				teste(lb, cb, lt, ct, qb, db, N, next, y, array);
			}
		}
		if (lt[x] == 1)
		{
			for (int i = 0; i < N - 1; i++)
			{
				array[x][i] = 1;
			}
			array[x][N - 1] = 0;
			teste(lb, cb, lt, ct, qb, db, N, next, y, array);

			array[x][0] = 0;
			for (int i = 1; i < N; i++)
			{
				array[x][i] = 1;
			}

			teste(lb, cb, lt, ct, qb, db, N, next, y, array);
		}
	}

	// no caso de existir apenas um preto ATENCAO JUNTAR COM O DE BAIXO
	if (lb[x] == 1 && lt[x] == 2)
	{
		for (int i = 1; i < N - 1; i++)
		{
			array[x][0] = 0;
			array[x][N - 1] = 0;
			for (int j = 0; j < N - 1; j++)
			{
				if (j == i)
				{
					array[x][j] = 1;
				}
				else
				{
					array[x][j] = 0;
				}
			}
			teste(lb, cb, lt, ct, qb, db, N, next, y, array);
		}
	}
	if (lt[x] == 2)
	{
		if (lb[x] > lt[x])
		{
			array[x][0] = 1;
			array[x][N - 1] = 1;
			int valorFalta = lb[x] - 2;
			if (valorFalta == 1)
			{
				array[x][N - 2] = 1;
				for (int i = 1; i < N - 2; i++)
				{
					array[x][i] = 0;
				}
				teste(lb, cb, lt, ct, qb, db, N, next, y, array);
				array[x][1] = 1;
				for (int i = 2; i < N - 1; i++)
				{
					array[x][i] = 0;
				}
				teste(lb, cb, lt, ct, qb, db, N, next, y, array);
			}
		}
	}

	// no caso de apenas existir um preto e uma transição
	if (lb[x] == 1 && lt[x] == 1)
	{
		array[x][0] = 1;
		for (int i = 1; i < N; i++)
		{
			array[x][i] = 0;
		}
		teste(lb, cb, lt, ct, qb, db, N, next, y, array);
		for (int i = 0; i < N - 1; i++)
		{
			array[x][i] = 0;
		}
		array[x][N - 1] = 1;
		teste(lb, cb, lt, ct, qb, db, N, next, y, array);
	}
	// TEM METADE DE PRETOS:

	if (lb[x] == N / 2 && N % 2 == 0)
	{
		for (int i = 0; i < N - 1; i += 2)
		{
			array[x][i] = 0;
			array[x][i + 1] = 1;
		}

		teste(lb, cb, lt, ct, qb, db, N, next, y, array);
		for (int i = 0; i < N - 1; i += 2)
		{
			array[x][i] = 1;
			array[x][i + 1] = 0;
		}
		teste(lb, cb, lt, ct, qb, db, N, next, y, array);
	}

	// LINHA TODA PRETA
	if (lb[x] == N)
	{
		for (int i = 0; i < N; i++)
		{
			array[x][i] = 1;
		}

		teste(lb, cb, lt, ct, qb, db, N, next, y, array);
	}
	if (lt[x] == N - 1)
	{
		if ((float)N / 2 < (float)lb[x])
		{

			for (int i = 0; i < N; i += 2)
			{
				array[x][i + 1] = 0;
				array[x][i] = 1;
			}

			teste(lb, cb, lt, ct, qb, db, N, next, y, array);
		}
	}

	// no caso de apenas existir nenhum preto
	if (lb[x] == 0)
	{
		for (int i = 0; i < N; i++)
		{
			array[x][i] = 0;
		}
		teste(lb, cb, lt, ct, qb, db, N, next, y, array);
	}

	// teste(lb, cb, lt, ct, qb, db, N, x + 1, y + 0, array);
}

int main()
{

	int numeroQR;
	cin >> numeroQR;

	for (int i = 0; i < numeroQR; i++)
	{
		Same = 0;
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

		// chamar aqui a função que mete os 0's e 1's
		teste(lb, cb, lt, ct, qb, db, numero, 0, 0, array);
		if (Same == 1)
		{
			imprimeQRcode(array2, numero);
		}
		else if (Same > 1)
		{
			printf("INVALID: %d QR Codes generated!\n", Same);
		}
		else
		{
			printf("DEFECT: No QR code generated!\n");
		}
		}

	return 0;
}
