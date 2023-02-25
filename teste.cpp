#include <iostream>
#include <array>
#include <cmath>
#include <unordered_set>
#include <vector>
using namespace std;

int Same = 0;
vector <vector<vector<int>>> solutions;
vector <vector<int>> mat;

int tamanho;
//pretos por linha
vector<int> lb;
//pretos por coluna
vector<int> cb;
//transicoes por linha
vector<int> lt;
//transicoes por coluna
vector <int> ct;
//pretos por quadrante
vector<int> qb;
//pretos por diagonal
vector<int> db;

int retornaQuadrante(int linha, int coluna)
{
	int a = floor(tamanho/2);
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

void imprimeQRCode(int tam){
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
			if (mat[i][k] == 0)
			{
				cout << " ";
			}
			if (mat[i][k] == 1)
			{
				cout << "#";
			}
			if (mat[i][k] == 2)
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

int contarPretosLinha(int l){
	int count=0;
	for (int c=0;c<tamanho;c++){
		if (mat[l][c]==1) count+=1;
	}
	return count;
}

int contarPretosColuna(int c){
	int count=0;
	for (int l=0;l<tamanho;l++){
		if (mat[l][c]==1) count+=1;
	}
	return count;
}

int contarPretosTransicaoLinha(int l){
	int count=0;
	for (int c=0;c<tamanho-1;c++){
		if ((mat[l][c]==0 && mat[l][c+1]==1) ||(mat[l][c+1]==0 && mat[l][c]==1)) count++;
	}
	return count;
}

int contarPretosTransicaoColuna(int c){
	int count=0;
	for (int l=0;l<tamanho-1;l++){
		if ((mat[l][c]==0 && mat[l+1][c]==1) ||(mat[l+1][c]==0 && mat[l][c]==1)) count++;
	}
	return count;
}

bool contarPretosQuadrante(int l, int c){
	int count=0;
	int quadrante= retornaQuadrante(l,c);

	int a= floor(tamanho/2);

	for (int i=0;i<tamanho;i++){
		for (int j=0;j<tamanho;j++){
			if(quadrante==1 && i<=a && j>a && mat[i][j]==1){
				count+=1;
			}

			else if (quadrante==2 && i<=a && j<=a && mat[i][j]==1){
				count+=1;
			}

			else if (quadrante==3 && i>a && j<=a && mat[i][j]==1){
				count+=1;
			}

			else if (quadrante==4 && i>a && j>a && mat[i][j]==1){
				count+=1;
			}
		}
	}

	//quadrante 1 ocupa posicao 0
	return count<=qb[quadrante-1];

}

bool contarPretosDiagonal(int l, int c){
	int count=0;
	int count_=0;
	bool fl=false;
	if (l==c && tamanho-l+1==c){
		for (int i=0;i<tamanho;i++){
			if (mat[i][i]==1) count++;
			if(mat[tamanho-i-1][i]==1) count_++;
		}
		return (count<=db[0] && count_<=db[1]);
	}
	//pertence a diagonal principal
	else if (l==c){
		for (int i=0;i<tamanho;i++){
			if (mat[i][i]==1) count++;
		}
		return count<=db[0];
	}
	else if(tamanho-l+1==c){
			for (int i=0;i<tamanho;i++){
				if (mat[tamanho-i-1][i]==1) count++;
			}
			return count<=db[1];
	}
	else return true;
}

bool validarElemento(int l, int c){
	bool flag;
    // se todas as condições se verificarem o elemento é valido para ficar preto
	mat[l][c]=1;
    flag = contarPretosLinha(l)<=lb[l] && contarPretosTransicaoLinha(l)<=lt[l] && contarPretosColuna(c)<=cb[c] && contarPretosTransicaoColuna(c)<=ct[c]
	&& contarPretosQuadrante(l,c) && contarPretosDiagonal(l,c);
	mat[l][c]=0;
	return flag;

}

bool verificacaoFinal()
{
	int teste;
	for (int i=0;i<tamanho;i++){
		if((teste=contarPretosLinha(i))!=lb[i]) return false;
		if((teste=contarPretosColuna(i))!=cb[i]) return false;
		if((teste=contarPretosTransicaoColuna(i))!=ct[i]) return false;
		if(teste=(contarPretosTransicaoLinha(i)!=lt[i])) return false;
	}
	return true;
}


void procurar_qr_codes(int l,int c, int size_max){
	if (c==size_max-1 && l==size_max-1){
		if(mat[l][c]==0 && validarElemento(l,c)){
			//cout << "encontrou" << "\n";
			mat[l][c]=1;
			solutions.push_back(mat);
			mat[l][c]=0;
			return;
		}
		//solutions.push_back(mat);
		return;
	}
	
    for (int i=0;i<size_max;i++){
        for (int j=0;j<size_max;j++){
			if (mat[i][j]==0 && validarElemento(i,j)){
				mat[i][j]=1;

				procurar_qr_codes(i,j+1,size_max);

				mat[i][j]=0;
			}
        }
    }
}


int main()
{
	int numeroQR;
	cin >> numeroQR;

	for (int i = 0; i < numeroQR; i++)
	{

        //so para testar
		Same = 1;
		int numero;
		cin >> numero;
		// int array[tamanho][tamanho];
		tamanho = numero;

        mat=vector <vector<int>> (tamanho,(tamanho,vector<int>(tamanho,0)));
		
		

		
        LeituraQrCode(numero);

        procurar_qr_codes(0,0,tamanho);

		if(solutions.size()==1){
			mat=solutions[0];
			imprimeQRCode(tamanho);
		}
		else if (solutions.size()>1){
			for (int i=0;i<solutions.size();i++){
				mat=solutions[i];
				imprimeQRCode(tamanho);
				cout << endl<<endl;
			}
			printf("INVALID: %ld QR Codes generated!\n", solutions.size());
		}
		else{
			printf("DEFECT: No QR code generated!\n");
		}
	
	}

	return 0;
}
