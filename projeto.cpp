#include <iostream>
#include <array>
#include <cmath>

using namespace std;



void LeituraQrCode(int lb[],int cb[],int lt[],int ct[],int qb[],int db[],int size){
  int valor,i;
  for(i = 0; i < size; i++){
    cin >> valor;
    lb[i] = valor;
  }
  for(i = 0; i < size; i++){
     cin >> valor;
    cb[i] = valor;
  }
   for(i = 0; i < size; i++){
    cin >> valor;
    lt[i] = valor;
  }
   for(i = 0; i < size; i++){
     cin >> valor;
    ct[i] = valor;
  }
   for(i = 0; i < 4; i++){
    cin >> valor;
    qb[i] = valor;
  }
  for(i = 0; i < 2;i++){
    cin >> valor;
    db[i] = valor;
  }
}

void ImprimirTeste(int lb[],int cb[],int lt[],int ct[],int qb[],int db[],int size){
  int valor,i;
  cout << endl << "ARRAY LB: ";
  for(i = 0; i < size; i++){
    cout << lb[i] << " ";
  }
  cout << endl << "ARRAY CB: ";
  for(i = 0; i < size; i++){
   cout << cb[i] << " ";
  }
  cout << endl << "ARRAY LT: ";
   for(i = 0; i < size; i++){
   cout << lt[i] << " ";
  }
  cout << endl << "ARRAY CT: ";
   for(i = 0; i < size; i++){
    cout << ct[i] << " ";
  }
  cout << endl << "ARRAY QB: ";
   for(i = 0; i < 4; i++){
    cout << qb[i] << " ";
  }
  cout << endl << "ARRAY DB: ";
  for(i = 0; i < 2;i++){
    
    cout << db[i] << " ";
  }
}
int retornaQuadrante(int linha, int coluna, int N){
  if(linha <= floor(N/2) && coluna > floor(N/2)){
    return 1;
  }
  if(linha <= floor(N/2) && coluna <= floor(N/2)){
    return 2;
  }
  if(linha > floor(N/2) && coluna <= floor(N/2)){
    return 3;
  }
  if(linha > floor(N/2) && coluna > floor(N/2)){
    return 4;
  }
  return 0;
}

int verificaDefeito(int lb[],int cb[],int lt[],int ct[],int qb[],int db[],int N){
  int soma = 0;
  int fl = floor(N/2+1);
  int result = pow(fl,2.0);
  // Verifica linha e colunas (colors e transitions)
  for(int i = 0; i < N; i++){
    if(lb[i] < 0 || lb[i] > N || cb[i] < 0 || cb[i] > N){
      return 0;
    }
    if(lt[i] < 0 || lt[i] > N - 1 || ct[i] < 0 || ct[i] > N - 1){
      return 0;
    }
  }
  // Verifica diagonais 
  for(int i = 0; i < 2; i++){
    if(db[i] < 0 || db[i] > N){
      return 0;
    }
  }
  // Verifica quadrantes
  for (int i = 0; i < 4; i++)
  {
    soma += qb[i];
  }
  if(soma > result){
    return 0;
  }
  return 1;
}



int Diagonal(int linha, int coluna){
  if(linha == coluna){
    return 1;
  }
  //if L-l+1 = c
  //Necessario fazer isto, mas não sei de onde vem o L 
  return -1;
}


int main() {
  
  int numeroQR;
  cin >> numeroQR;

  for(int i = 0; i < numeroQR; i++){
    int numero;
    cin >> numero;
    int lb[numero];
    int cb[numero];
    int lt[numero];
    int ct[numero];
    int qb[numero];
    int db[2];
    LeituraQrCode(lb,cb,lt,ct,qb,db,numero);
    if(!verificaDefeito(lb,cb,lt,ct,qb,db,numero)){
      cout << "DEFECT: No QR Code generated!" << endl;
    }else{
      cout << endl;
    }
     // cout << is_valid(lb,cb,lt,ct,qb,db,numero) << endl;
     // ImprimirTeste(lb,cb,lt,ct,qb,db,numero);
      
  }
  
 
  return 0;
}

