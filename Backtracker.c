#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int flag=0;//Sonuca ulaþýlýp ulaþýlmadýðýný kontrol eden flag. Eðer 0 ise sonuca ulaþýlmýþtýr ve son satýr prompt'a basýlýr
int count=0;//Satýrlarýn toplam kaç kere shift edildiðini tutar.

void matrixoku(int **matrix,int n){
	char renkler[8][10]={"mavi","yesil","kirmizi","sari","mor","siyah","beyaz","turuncu"};	
	int Kullanilan_renkler[n];//Daha sonra girilecek  renklerin en üst satýrdaki renklerle ayný olup olmadýðýný kontrol eder
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
				Kullanilan_renkler[k++]=z;//ilk satýrda alýnan deðerler kullanýlan renkler arrayine eklenþr
				flag=0;				
				}
			else z++;
		}
	}	
	k=0;
	int break_flag=0;// ilk satýrda kullanýlmayýp sonraki satýrlarda kullanýlan bir renk varsa programý kapatmak için kullanýlýyor 
	for(i=1;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%s",temp);
			flag=1;
			z=0;
			while(flag==1){ //while kullanma nedenim: girilen renk bulununca array içinde gezinmeye devam etmeden sonraki alýma geçmektir
				if(strcmp(temp,renkler[z])==0){
					break_flag=0;
					k=0;
					matrix[i][j]=z;
					flag=0;
					while(break_flag==0 && k<n){//while kullanma nedenim: girilen renk bulununca array içinde gezinmeye devam etmeden sonraki alýma geçmektir
						if(Kullanilan_renkler[k]==z){
							break_flag=1;
						}
						else k++;
					}
					if(k>=n){//yanlýþ girilmiþ renk varsa program kapanýr
						printf("Girilen Rengin Ust Satirdaki renklerden biri olmasi gerekiyor!");
						exit(0);		
					}				
				}
				else z++;
			}
		}
	}
}
void print_matrix(int **matrix,int n){//girilen rowno parametresine göre o satýra kadar bastýrma yapar
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
int N_gir(){//N sayýsýnýn alýmý... (Recursive biçimde yapýlabilir mi diye merak etmiþtim... yapýlýyormuþ :D)
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

void Slide_right(int **matrix,int rowno,int n){//Seçilen satýrý saða kaydýran fonksiyon
	int i;
	int temp=matrix[rowno][n-1];
	for(i=n-1;i>0;i--){
		matrix[rowno][i]=matrix[rowno][i-1];
	}
	matrix[rowno][0]=temp;
}
int us_kontrol(int **matrix,int rowno,int column){//bir sütunda ayný renkten 1'den fazla var mý diye kontrol eden fonksiyon. Sadece üst satýrlara bakar
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
	while(i<n && i!=-1){//i=-1 ise shift sayýsý n sayýsýný geçmiþtir(n'den fazla shift yapýlmýþtýr) i=1 ise ayný sütunda ayný renkten var demektir
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
		}//us kontrolden 0 dönerse ayný sutunda o renkten yoktur ve diðer sutuna geçer
		else{
			i++;
		}
	}
	if(i==-1){
		if(array[rowno]>=pow(n,rowno) || rowno==1){// rowno 1 iken sonuç bulunamadýysa aþaðýdaki her kombinasyon denenmiþtir böylece üstü kaydýrmak bir þey deðiþtirmeyecektir
			printf("\nSonuc bulunamadi\n");			//diðer case için ise eðer bir satýr en kötü ihtimalle dönmesi gereken kadar döndüyse ve sonuç çýkmadýysa sonuç bulunamaz 
			flag=1;
			return;
		}
		Slide_right(matrix,rowno-1,n);//üst satýra çýkmadan önce önce üst satýrýn en az 1 kere kaydýrýlmasý gerekir ki yukarýdaki satýr, kaydýrma yapmadan aþaðý satýra dönüþ yapmasýn
		array[rowno-1]++;
		count++;
		return recursion(matrix,rowno-1,n,1,array,mod);//i=-1 ve rowno !=1 ise bir üst satýra çýkýlýp iþlemler yapýlýr
	}
	else{
		if(rowno!=n-1){//eðer son satýrda deðilsek
			if(mod==2)//Programýn çalýþma þekli 2 (adým adým) ise bu satýra kadarki satýrlar bastýrýlýr
			print_matrix(matrix,n);
			
			return recursion(matrix,rowno+1,n,0,array,mod);//ve bir alt satýra geçilip iþlemler yapýlýr
			}
		else return;//eðer son satýrdaysak
	}
}

int main(){
	int mod;
	printf("Mod Secimi yapiniz:\n'1'-->Sadece sonuc matrisini gosterir\n'2'-->Adim adim matris durumunu gosterir\n");
	scanf("%d",&mod);//programýn çalýþma þekli 1->sadece sonuç bastýrýlýr 2->düzgün oturmuþ satýrlar bastýrýlýr
	int *array;
	int n=N_gir();
	array=(int*)malloc(sizeof(int)*n);
	int **matrix;
	int i;
	matrix=(int**)malloc(sizeof(int*)*n);//matrisin açýmý
	for(i=0;i<n;i++){
		matrix[i]=(int*)malloc(sizeof(int)*n);
		array[i]=0;//satýr baþýna kaç kere dönüldüðünü tutan matris
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
