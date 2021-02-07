#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int flag=0;//Sonuca ula��l�p ula��lmad���n� kontrol eden flag. E�er 0 ise sonuca ula��lm��t�r ve son sat�r prompt'a bas�l�r
int count=0;//Sat�rlar�n toplam ka� kere shift edildi�ini tutar.

void matrixoku(int **matrix,int n){
	char renkler[8][10]={"mavi","yesil","kirmizi","sari","mor","siyah","beyaz","turuncu"};	
	int Kullanilan_renkler[n];//Daha sonra girilecek  renklerin en �st sat�rdaki renklerle ayn� olup olmad���n� kontrol eder
	char temp[10];
	int i,j,z,k=0;
	int flag;
	printf("\nMatris degerlerinizi giriniz\n");
	for(i=0;i<n;i++){
		scanf("%s",temp);
		flag=1;
		z=0;
		while(flag==1){
			if(strcmp(temp,renkler[z])==0){
				matrix[0][i]=z;
				Kullanilan_renkler[k++]=z;//ilk sat�rda al�nan de�erler kullan�lan renkler arrayine eklen�r
				flag=0;				
				}
			else z++;
		}
	}	
	k=0;
	int break_flag=0;// ilk sat�rda kullan�lmay�p sonraki sat�rlarda kullan�lan bir renk varsa program� kapatmak i�in kullan�l�yor 
	for(i=1;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%s",temp);
			flag=1;
			z=0;
			while(flag==1){ //while kullanma nedenim: girilen renk bulununca array i�inde gezinmeye devam etmeden sonraki al�ma ge�mektir
				if(strcmp(temp,renkler[z])==0){
					break_flag=0;
					k=0;
					matrix[i][j]=z;
					flag=0;
					while(break_flag==0 && k<n){//while kullanma nedenim: girilen renk bulununca array i�inde gezinmeye devam etmeden sonraki al�ma ge�mektir
						if(Kullanilan_renkler[k]==z){
							break_flag=1;
						}
						else k++;
					}
					if(k>=n){//yanl�� girilmi� renk varsa program kapan�r
						printf("Girilen Rengin Ust Satirdaki renklerden biri olmasi gerekiyor!");
						exit(0);		
					}				
				}
				else z++;
			}
		}
	}
}
void print_matrix(int **matrix,int n){//girilen rowno parametresine g�re o sat�ra kadar bast�rma yapar
	char renkler[8][10]={"mavi","yesil","kirmizi","sari","mor","siyah","beyaz","turuncu",};	
	printf("\n\n");
	char temp[10];
	int i,j,z;
	int flag;
	for(i=0;i<n;i++){
		printf("\n");
		for(j=0;j<n;j++){
			printf("%s  ",renkler[matrix[i][j]]);
			}
		}
	printf("\n\n");
}
int N_gir(){//N say�s�n�n al�m�... (Recursive bi�imde yap�labilir mi diye merak etmi�tim... yap�l�yormu� :D)
	printf("N giriniz:  (3 <= N <= 8)  : ");
	int n;
	scanf("%d",&n);
	if(n<3 || n>8){
		printf("Hatali N girisi\n");
		return N_gir();
	}
	printf("\nKullanabileceginiz renkler:");
	printf("\nmavi\nyesil\nkirmizi\nsari\nmor\nsiyah\nbeyaz\nturuncu\n");
	return n;
}

void Slide_right(int **matrix,int rowno,int n){//Se�ilen sat�r� sa�a kayd�ran fonksiyon
	int i;
	int temp=matrix[rowno][n-1];
	for(i=n-1;i>0;i--){
		matrix[rowno][i]=matrix[rowno][i-1];
	}
	matrix[rowno][0]=temp;
}
int us_kontrol(int **matrix,int rowno,int column){//bir s�tunda ayn� renkten 1'den fazla var m� diye kontrol eden fonksiyon. Sadece �st sat�rlara bakar
	int i;
	for(i=0;i<rowno;i++){
		if(matrix[i][column]==matrix[rowno][column]){
			return 1;
		}
	}
	return 0;
}


void recursion(int **matrix,int rowno,int n,int shifts,int *array,int mod){//ana fonksiyon
	int i=0;
	while(i<n && i!=-1){//i=-1 ise shift say�s� n say�s�n� ge�mi�tir(n'den fazla shift yap�lm��t�r) i=1 ise ayn� s�tunda ayn� renkten var demektir
		if(us_kontrol(matrix,rowno,i)==1){
			if(shifts<n && array[rowno]<pow(n,rowno) ){
				i=0;
				shifts++;
				array[rowno]++;
				count++;
				Slide_right(matrix,rowno,n);
			}
			else{
				i=-1;
			}
		}//us kontrolden 0 d�nerse ayn� sutunda o renkten yoktur ve di�er sutuna ge�er
		else{
			i++;
		}
	}
	if(i==-1){
		if(array[rowno]>=pow(n,rowno) || rowno==1){// rowno 1 iken sonu� bulunamad�ysa a�a��daki her kombinasyon denenmi�tir b�ylece �st� kayd�rmak bir �ey de�i�tirmeyecektir
			printf("\nSonuc bulunamadi\n");			//di�er case i�in ise e�er bir sat�r en k�t� ihtimalle d�nmesi gereken kadar d�nd�yse ve sonu� ��kmad�ysa sonu� bulunamaz 
			flag=1;
			return;
		}
		Slide_right(matrix,rowno-1,n);//�st sat�ra ��kmadan �nce �nce �st sat�r�n en az 1 kere kayd�r�lmas� gerekir ki yukar�daki sat�r, kayd�rma yapmadan a�a�� sat�ra d�n�� yapmas�n
		array[rowno-1]++;
		count++;
		return recursion(matrix,rowno-1,n,1,array,mod);//i=-1 ve rowno !=1 ise bir �st sat�ra ��k�l�p i�lemler yap�l�r
	}
	else{
		if(rowno!=n-1){//e�er son sat�rda de�ilsek
			if(mod==2)//Program�n �al��ma �ekli 2 (ad�m ad�m) ise bu sat�ra kadarki sat�rlar bast�r�l�r
			print_matrix(matrix,n);
			
			return recursion(matrix,rowno+1,n,0,array,mod);//ve bir alt sat�ra ge�ilip i�lemler yap�l�r
			}
		else return;//e�er son sat�rdaysak
	}
}

int main(){
	int mod;
	printf("Mod Secimi yapiniz:\n'1'-->Sadece sonuc matrisini gosterir\n'2'-->Adim adim matris durumunu gosterir\n");
	scanf("%d",&mod);//program�n �al��ma �ekli 1->sadece sonu� bast�r�l�r 2->d�zg�n oturmu� sat�rlar bast�r�l�r
	int *array;
	int n=N_gir();
	array=(int*)malloc(sizeof(int)*n);
	int **matrix;
	int i;
	matrix=(int**)malloc(sizeof(int*)*n);//matrisin a��m�
	for(i=0;i<n;i++){
		matrix[i]=(int*)malloc(sizeof(int)*n);
		array[i]=0;//sat�r ba��na ka� kere d�n�ld���n� tutan matris
	}
	matrixoku(matrix,n);
	
	if(mod==2)
	print_matrix(matrix,n);
	
	recursion(matrix,1,n,0,array,mod);
	if(flag==0)
	print_matrix(matrix,n);
	printf("\nToplam kaydirma sayisi= %d",count);
	return 0;
}
