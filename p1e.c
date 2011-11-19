

void main() {

int leido;


  cout << "ingrese un numero entre 0 y 10";
  cin >> leido;

  if ((leido < 0) || (leido > 10))
     cout << "numero fuera de rango";
  else {
       float f;
       cout << "su numero sera multiplicado por 1.5";
       f = leido* 1.5;
       cout << "el resultado es: " << f;
  }

}
