
 int festaEnA(int A[], int y) {
 int i=0;

while ((i< 5)&& (A[i] != y)) i=i + 1;

  if (i >= 5) return 0;
 else return 1;
 }

 int arreglo[6]= {10, 14, 21, 45, 5, 0};
int y;

 void main (){

 cout << "ingrese un numero: ";
 cin >> y;
cout << "\n";

 if (festaEnA(arreglo, y)) cout << "el numero esta en el arreglo \n";
 else cout <<" el numero esta No esta en el arreglo \n";

}