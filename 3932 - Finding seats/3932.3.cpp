#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <climits>

using namespace std;

int m[303][303], dp[303][303];

const long long infinity = 100000;

long long dist(int arr[], const int &n, const int &k){
  //retorna la longitud de la minima secuencia adyacente de arr que sume al menos k
  //arr es un arreglo de n números no negativos
  long long a = 0, b = infinity, curr = 0, aa = 0, bb = 0;
  while (bb < n){
    while (arr[aa] == 0 && aa < bb){
      ++aa;
    }
    curr += arr[bb];
    if (curr >= k && (bb - aa) < (b - a)){
      a = aa;
      b = bb;
    }
    while (curr >= k){
      curr -= arr[aa];
      aa = aa + 1;
    }
    if (curr <= 0){
      curr = 0;
      aa = bb + 1;
    }
    if (curr - arr[aa] > 0){
      curr -= arr[aa];
      aa = bb + 1;
    }
    ++bb;
  }
  cout << "La subsecuencia más corta que sume al menos " << k << " va desde " << a << " hasta " << b << endl;
  return b - a;
}

int main(){
  int r,c,seats;

  int n, k, z[100];
  cin >> n >> k;
  for (int i=0; i<n; ++i){
    cin >> z[i];
  }
  dist(z, n, k);

    /*    while(cin >> r >> c >> seats && (r | c | seats)){
    
    
      for (int i=1; i<=r; ++i){
	for (int j=1; j<=c; ++j){
	  char d;
	  cin >> d;
	  m[i][j] = (d == '.' ? 1 : 0);
	}
      } 
    
      for (int i=1; i<=r; ++i){
	for (int j=1; j<=c; ++j){
	  cout << m[i][j] << " ";
	}
	cout << endl;
    
	dist(m[i], c, seats);
      }
      }*/
    return 0;
}
