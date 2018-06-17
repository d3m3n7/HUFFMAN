#include <iostream>
using namespace std;
int main(){
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i){
		char caracter;
		string aux;
		cin >> caracter >> aux;
		cout << caracter <<" "<< aux << endl; 
	}
}