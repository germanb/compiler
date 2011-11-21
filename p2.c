int v1[10], v2[10];

int k, e, sum; int b;

int ffact ( int x ) {
 
if (x == 0) return 1;
 else return( ffact(x-1) * x );

}

void fcalc (int vec[], int lim) {
 
int i=1;
while (i <= lim ) {
vec[i-1] = ffact(vec[i-1]);
sum = sum + vec[i-1];
i = i+1;
 }

}

void main(){
  k=0; b=1;

while (b) {
cout << valor de v1[ << k << ]=;
 cin >> e;
v1[k]=e;
  v2[k]=v1[k];
 k=k+1;
 if (k>4) b=0;
 } 

sum=0;
calc (v1,5);
 cout << sum : ;
  cin >> sum;
 
 sum=0;
 fcalc (v2,5);
cout << sum : ;
  cin >> sum;

  k=0;
 cout << **************;
 while (k <= 4) {
 cout << ffact(v1[k] - v2[k]);
 k=k+1;
  }
 cout << **************; 
 }
