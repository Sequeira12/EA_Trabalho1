#include <iostream>
#include <array>

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
    ImprimirTeste(lb,cb,lt,ct,qb,db,numero);
    cout << endl;
  }
 

  return 0;


}

