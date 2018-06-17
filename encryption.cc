#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
static int NOMBRE;
static bool debug = true;
static bool MODE0 = true;
	class compara
	{
	public:
	    bool operator()(pair<int,int> n1,pair<int,int> n2) {
	    	if (n1.second == n2.second) return n1.first < n2.first;
	        return n1.second>n2.second;//ORDENA PER FIRST DE MÉS PETIT A MÉS GRAN PER FIRST
	        							//SI ES EL MATEIX NOMBRE FA QUE EL MÉS NOU SIGUI L'ULTIM
	    }
	};
void pinta(vector <int> alfabet){
	char caracter = 'A';
	for (int i = 0; i < alfabet.size(); ++i){
		if (alfabet[i] > 0)cout <<"["<< caracter << "]:" << alfabet[i] << endl;
		caracter++;
		if (caracter == 'A'+26) caracter = 'a';
	}
	cout << endl;
	
}
void pintaQ(priority_queue< pair<int,int>, vector< pair<int,int> >, compara > huffman){
	while(not huffman.empty()){
		int caracter = huffman.top().first;
		if (caracter < 26 and caracter >= 0) {caracter += 65;
			if(debug)cout << "[" << char(caracter) << "]: " << huffman.top().second << endl;
			NOMBRE++;}
		else if(caracter >= 26){ caracter += 71;
		if(debug)cout << "[" << char(caracter) << "]: " << huffman.top().second << endl;
		NOMBRE++;}
		else if(debug) cout << "[" << caracter<< "]: " << huffman.top().second << endl;
		
		huffman.pop();
	}
	if(debug)cout << endl;
}
void pintaC(vector <stack <bool> > codis){
	cout <<NOMBRE <<endl;
	for (int j = 0; j < codis.size(); ++j){
		if (not codis[j].empty()){
			if (j < 26) cout << char(j+65) << " ";
			else cout << char(j+71) << " ";
			while (not codis[j].empty()){
				cout << codis[j].top();
				codis[j].pop();
			}
			cout << endl;
		}
	}
	cout << endl;
}

void recursiva(const int i,bool valor,const vector <pair <int,int> >& IDS_predecessors,
	 vector <stack <bool>>& codis){
	//cout << -(i+1) << " el vertex que estic mirant" << endl;
	int ID_primer = IDS_predecessors[i].first;
	int ID_segon = IDS_predecessors[i].second;
	//cout << "ID_primer" << ID_primer << endl;
	//cout << "ID_segon" << ID_segon << endl;
	if (ID_primer >= 0){
		codis[ID_primer].push(valor);
	}
	else{
		recursiva(abs(ID_primer+1),valor, IDS_predecessors, codis);
	}
	if (ID_segon >= 0){
		codis[ID_segon].push(valor);
	}
	else{
		recursiva(abs(ID_segon+1),valor, IDS_predecessors,codis);
	}
}

int main(){
	char inp;
	
	vector <int> frequencies(52,0);
	vector<char> missatge;
	int cont = -1;
	while(cin >> inp){
		missatge.push_back(inp);
		if (debug)cout << inp;
		if (inp >= 'A' and inp <= 'Z' ){
			frequencies[inp-65]++;
		}
		if (inp >= 'a' and inp <= 'z' ){
			frequencies[inp-97+26]++;
		}
	}
	if (debug)cout << endl << endl;
	if (debug)pinta(frequencies);
	priority_queue< pair<int,int>, vector< pair<int,int> >, compara > huffman;
	for (int i=0; i < frequencies.size(); ++i){
		if (frequencies[i] != 0) huffman.push( make_pair(i,frequencies[i]) );
	}
	
	vector <stack <bool>> codis (52);
	vector <pair <int,int> > IDS_predecessors;
	int contador = -1;
	if (debug or MODE0) pintaQ(huffman);
	while(huffman.size() > 1){
		int ID_primer = huffman.top().first;
		int frequencia_primer = huffman.top().second;
		huffman.pop();
		int ID_segon = huffman.top().first;
		int frequencia_segon = huffman.top().second;
		huffman.pop();
		//cout << "contador"<< contador << endl;
		/*
			if (ID_primer >= 0) cout <<char(ID_primer+65);
			else cout << ID_primer;
			if (ID_segon >= 0) cout <<" "<< char(ID_segon+65) << endl;
			else cout <<" "<< ID_segon << endl;
			*/
		//pintaQ(huffman);
		if (ID_primer >= 0 and ID_segon >= 0){
			codis[ID_primer].push(1);
			codis[ID_segon].push(0);
			huffman.push( make_pair(contador , frequencia_primer + frequencia_segon) );
			
			//cout << "PUSHBACK" << "(" << ID_primer << " " << ID_segon << ")" << endl;
			IDS_predecessors.push_back( make_pair(ID_primer, ID_segon) );
			
		}else{
			if (ID_primer >= 0){
				codis[ID_primer].push(0);
				huffman.push( make_pair(contador,frequencia_primer+frequencia_segon) );
				IDS_predecessors.push_back(make_pair(ID_primer, ID_segon));
				recursiva (abs(ID_segon + 1),1, IDS_predecessors, codis);
			}
			else if (ID_segon >=0){
				codis[ID_segon].push(0);
				huffman.push( make_pair(contador,frequencia_primer+frequencia_segon) );
				IDS_predecessors.push_back(make_pair(ID_primer, ID_segon));
				recursiva(abs(ID_primer+1), 1, IDS_predecessors, codis);
			}
			else{
				
				huffman.push( make_pair(contador,frequencia_primer+frequencia_segon) );
				IDS_predecessors.push_back(make_pair(ID_primer, ID_segon));
				recursiva(abs(ID_primer+1), 1, IDS_predecessors, codis);
				recursiva(abs(ID_segon+1), 0, IDS_predecessors, codis);

			}
		}
		//if (debug)pintaQ(huffman);
		contador --;
		
	}
	if (debug or MODE0)pintaC(codis);

	//CODIFICA EL MISSATGE
	vector <bool> Mcodificat;
	for (int k = 0; k < missatge.size(); ++k){
		char caracter = missatge[k];
		if (caracter >= 'A' and caracter <= 'Z') caracter -= 65;
		if (caracter >= 'a' and caracter <= 'z') caracter -= 71;
		stack <bool> copia = codis[int(caracter)];
		while(not copia.empty()){
			Mcodificat.push_back(copia.top());
			cout << copia.top();
			copia.pop();
		}
	}
	cout << endl;
//----------------------------

	//DECODIFICA EL MISSATGE
	int contadore = 0;
	for (int i = 0; i < Mcodificat.size(); ++i){
		queue<bool> patro;
		bool trobat = false;
		
		while (not trobat){
			patro.push(Mcodificat[contadore]);
			bool es_identic = true;
			if (contadore >= Mcodificat.size()) trobat = true;
			for (int k = 0; k < codis.size() and not trobat; ++k){
				//cout << "PATRO" << k << endl;
				if (codis[k].size() == patro.size()){
					//if (debug)cout <<"K: "<< k << endl;
					queue<bool> copia_patro = patro;
					stack <bool> copia = codis[k];
					
					while(not copia_patro.empty()){
						if (copia.top() != copia_patro.front()) es_identic = false;
						//if (debug)cout<< copia.top()<<" "<< copia_patro.front()<< endl;
						copia.pop(); copia_patro.pop();
					}
					if (es_identic) {
						trobat = true;
						char caracter;
						if (k < 26) caracter = (k+65);
						if (k >= 26) caracter = (k+71);
						if(debug) cout << caracter;	//RECOMPOSO EL MISSATGE
					}
					es_identic = true;
				}

			}
			//cout << endl;
			contadore++;//seguent xifra (ja he mirat tots els codis)
			
		}
	}
	if(debug) cout << endl;
}