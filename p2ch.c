int v1[10.1];   #error#
int v2[3]={2,1 } #error#

int v3[3]={2,3,'2'} 

int v4[5];

void main(){

v4=v2; #error#

v4=v2[0]; #error#

v4[2]= '7'; #no error#

v4[2]= 7.0; #error#


}
