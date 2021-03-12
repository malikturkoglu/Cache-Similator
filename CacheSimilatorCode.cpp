
#include<stdio.h>
#include<math.h>
#include<getopt.h>               //MALÝK TÜRKOÐLU,150116044,     -CSE 238/2038/2138 Systems Programming Project 3-                     
#include<stdlib.h>
#include<unistd.h>              //  whole operation (I,L,S,M) is done. 
#include<string.h>
void HexConvertBin(char* hexdec,char* s)        // This help us for the convert hex to binary form.
{                                               // Bize verilen hexadecimal deðerleri,binary dönüþtürmek için kullanacaðýz.
int len = strlen(s);
	long int i = 0; 

	while (hexdec[i]) { 

		switch (hexdec[i]) { 
		case '0': 
		strcat( s, "0000" );
		
			break; 
		case '1': 
		
			strcat( s, "0001" );
			break; 
		case '2': 
		
			strcat( s, "0010" );
			break; 
		case '3': 
		
			strcat( s, "0011" ); 
			break; 
		case '4': 
		
			strcat( s, "0100" );
			break; 
		case '5': 
		
			strcat( s, "0101" ); 
			break; 
		case '6': 
		
			strcat( s, "0110" );
			break; 
		case '7': 
		 
			strcat( s, "0111" );
			break; 
		case '8': 
		
			strcat( s, "1000" );
			break; 
		case '9': 
		
			strcat( s, "1001" );
			break; 
		case 'A': 
		case 'a': 
		
			strcat( s, "1010" );
			break; 
		case 'B': 
		case 'b': 
		
			strcat( s, "1011" );
			break; 
		case 'C': 
		case 'c': 
		
			strcat( s, "1100" );
			break; 
		case 'D': 
		case 'd': 
		
			strcat( s, "1101" );
			break; 
		case 'E': 
		case 'e': 
			
			strcat( s, "1110" );
			break; 
		case 'F': 
		case 'f': 
			strcat( s, "1111" );
		
			break; 
		default: 
			printf("\nInvalid hexadecimal digit %c", 
				hexdec[i]); 
		} 
		i++; 
	} 
} 






struct CacheL1I {                                    // we will make struct array
    int valid[5];
    int time[5];
    int tag[5];                      
   int blockBit;                        
   int line;
   
};

struct CacheL1D {                                    
   int valid[5];
    int time[5];
    int tag[5];                      
   int blockBit;                       
   int line;
   

};
struct CacheL2 {                                    
    int valid[5];
    int time[5];
    int tag[5];                     
   int blockBit;                        
   int line;
};





int main()
{
	 FILE *traceFiles;
  int tagsizeL2;
  int tagsizeL1;
   int set1Number;
   int set2Number;
char trace[20]={'\0'};

int L1Ihit=0;
int L1Imiss=0;
int timerL1I=0;
int L1Ieviction=0;

int L1Dhit=0;
int L1Dmiss=0;
int timerL1D=0;
int L1Deviction=0;

int L2hit=0;
int L2miss=0;
int timerL2=0;
int L2eviction=0;




    // -L1s 0 -L1E 2 -L1b 3 -L2s 1 -L2E 2 -L2b 3 -t test1.trace 
 
    int l1s;
    int l1E;
    int l1b;          //bunlarý kullanýcýdan input almak için kullandýðýmda hata ile karþýlaþtým, mecburen alttaki variable larý (av,bv,cv....)tanýmlayýp onlarý bunlara atamak zorunda kaldým.
    
    int l2s;
    int l2E;
    int l2b;
    
int av;                                 // bunlarý kullanýcýdan input almak için kullanacaðýz.
int bv;
int cv;
int dv;
int ev;
int fv;
  printf("Enter l1s: ");
    scanf("%d",&av);
     printf("Enter l1E :");
    scanf("%d",&bv);
     printf("Enter l1b: ");
    scanf("%d",&cv);
     printf("Enter l2s :");
    scanf("%d",&dv);  
      printf("Enter l2E: ");
    scanf("%d",&ev);
     printf("Enter l2b :");
    scanf("%d",&fv); 
 /*  */ 
 
    l1s=av;
    l1E=bv;
    l1b=cv;
    
    l2s=dv;
    l2E=ev;
    l2b=fv;
 
 
 
     printf("what is your folder name:");
    scanf("%s",&trace); 

    
     tagsizeL1 = 64-(l1s+l1b);       // BURDA TAGSÝZE ÝÇÝN BUNLARI ÇIKARMAMIZ LAZIM
    tagsizeL1 = 64-(l2s+l2b);
    set1Number = pow(2, l1s);      // BURDA SET SAYISI
    set2Number = pow(2, l2s);
    
     struct CacheL1I LI1cache[set1Number];	// BURDA HER BÝR CACHE ÝÇÝN BÝR STRUCT ARRAY I OLUÞTURUYORUZ , BURDA ÝNFO BÝLGÝLERÝ TUTULACAKTIR
     struct CacheL1D L1Dcache[set1Number];
     struct CacheL2 L2cache[set2Number];
     
     
     char *CacheL1IData[set1Number][l1E]={'\0'};   //buda store kýsmýdýr,set kýsmý hangi sette olduðunu söyler,line kýsmýda hangi lineda olduðu(three dimensional array)
     char *CacheL1DData[set1Number][l1E]={'\0'};
     char *CacheL2Data[set2Number][l2E]={'\0'};
     
    int i,k,j;                                     
        for (i = 0; i < set1Number; i++) {          // we put beginning values ,null
	for (k = 0; k <l1E ; k++)
CacheL1IData[i][k]='\0';	  	
    }
         for (i = 0; i < set1Number; i++) {          // we put beginning values ,null
	for (k = 0; k <l1E ; k++)
CacheL1DData[i][k]='\0';	  	
    }   
          for (i = 0; i < set2Number; i++) {          // we put beginning values ,null
	for (k = 0; k <l2E ; k++)
CacheL2Data[i][k]='\0';	  	
    }  
	                              // we finished part1,we took input, we built caches, gave beginning values
                                  // we are going to read trace file  
								  
	
	char hexdec[100]={'\0'};						  
	char operation;		//Stores the operation mode- Modify or Load or Store
    char centik;
    char data[64]={'\0'};
	int address;
    int size;							  
	FILE *fp,*outp;; 
	
	fp = fopen("ram.txt", "r"); 		   

    traceFiles = fopen(trace, "r");                                                                    // burda , traceFiles = fopen(trace, "r"); 
    if (traceFiles == NULL) {
	fprintf(stderr, "Error");
	return -1;
    }
 
int x=0;  

  for (i = 0; i < set1Number; i++) {          // we put beginning values 0. (sýfýr atadýðýmda bazý indexlerde yinede garip sayýlar kaldý,ayný þeyi yapýp tekrar atadým,düzeldi.)
	for (k = 0; k < 5 ; k++) {
		LI1cache[i].tag[k] = 0;
		 LI1cache[i].valid[k]=0;
	  LI1cache[i].time[k]=0;	  
	}
    }

  for (i = 0; i < set1Number; i++) {          // we put beginning values 0.
	for (k = 0; k < 5 ; k++) {
		L1Dcache[i].tag[k] = 0;
		 L1Dcache[i].valid[k]=0;
	  L1Dcache[i].time[k]=0;	  
	}
    }
for (i = 0; i < set2Number; i++) {          // we put beginning values 0.
	for (k = 0; k < 5 ; k++) {
		L2cache[i].tag[k] = 0;
		 L2cache[i].valid[k]=0;
	  L2cache[i].time[k]=0;	  
	}
    }

                                                                                      // Buraya kadar struct , struct array, double char arrayler oluþturuldu,
																					  // deðerlere nul ve 0 atandý
    while (1) {                                                                         //Read every line  WE ARE READING TRACE FILE HERE 
 char s[24]={'\0'}; 
 char tagBinary[24]={'\0'};
 char adressBinary[24]={'\0'};
int long long adressDecimal=0;
char input[38]={'\0'}; 	
	fscanf(traceFiles, " %c %x,%d", &operation, &address, &size);
	
	if (operation == 'M')	//ignore all instruction cache accesses (lines starting with “I”).
	    fscanf(traceFiles, " %c %s", &centik, &data);
	    	if (operation == 'S')	//ignore all instruction cache accesses (lines starting with “I”).
	    fscanf(traceFiles, " %c %s", &centik, &data);
	if (feof( traceFiles))
	    break;
	    
	    
	 // I WILL FIND ADRESS' DECIMAL VALUE    
	   
	    sprintf(hexdec, "%x", address);
		HexConvertBin(hexdec,s);
		int power1=0;

int counterBin=0;
for(int a=0;a<24;a++){
	adressBinary[a]=s[a];
	if(s[a]!=0){
		counterBin++;
	}
}	

for (j = counterBin-1 ; j >= 0; j-- ) {                            //BURDA BINARY DEN DECIMAL E ÇEVÝRÝYORUZ

	 	adressDecimal +=  (adressBinary[j] - 48) * (int)pow((double)2, power1);
	 power1++;	 	 
 }


if(operation =='I'){
	int missPart=1;
	timerL1I++;
	sprintf(hexdec, "%x", address);
		HexConvertBin(hexdec,s);
int a;
int k=l1s+l1b;	
for(int a=0;a<24-k;a++){
	tagBinary[a]=s[a];
}
int long long tagDecimal=0;
int power=0;
for (j = 24-1-k ; j >= 0; j-- ) {
	 tagDecimal +=  (tagBinary[j] - 48) * (int)pow((double)2, power);
	// 	 printf("  (tagBinary[j] - 48)=%d ve decimal deðeri %d\n",  (tagBinary[j] - 48) ,decimal); 
	 power++;
//	 printf("j %d ve power %d \n",j,power); 
 }

 for (i = 0; i < set1Number; i++) {          // we are searhing hit.
	for (k = 0; k <l1E ; k++) {
		if(LI1cache[i].tag[k]==tagDecimal){
			L1Ihit++; 
			i=set1Number;
			missPart=0;
			break;}	 
	}
    }

if(missPart){  
fseek(fp,adressDecimal, SEEK_SET); 
fgets( input, size*4, fp );


                                                 // BU BÖLÜM MÝSS PART BÖLÜMÜDÜR BURDA HÝT OLMAYANLARI YERLEÞTÝRÝYORUZ
	L1Imiss++;
	int spaceEmpty=1;
	for (i = 0; i < set1Number; i++) {          // we are putting empty space , ÝLK ÖNCE BOÞLUKLARI DOLDURUYORUZ
	for (k = 0; k <l1E ; k++) {

		if(LI1cache[i].valid[k]==0){
		LI1cache[i].valid[k]=1;
		LI1cache[i].time[k]=timerL1I;
		LI1cache[i].tag[k]==tagDecimal;
	CacheL1IData[i][k]=input;	
			i=set1Number;
			spaceEmpty=0;
			break;}	 
	}
    }

if(spaceEmpty){
	L1Ieviction++;
int templerTime=LI1cache[0].time[0];
int templerI=0;
int templerK=0;

for (i = 0; i < set1Number; i++) {          // first in first out  // EÐER BOÞLUKLAR DOLDU ÝLE FIRST IN FIRST OUT YAPIYORUZ
	for (k = 0; k <l1E ; k++) {
		if(LI1cache[i].time[k]<templerTime){
			
templerTime=LI1cache[i].time[k];
templerI=i;
templerK=k;
	}
    }
}
LI1cache[templerI].tag[templerK]=tagDecimal;
LI1cache[templerI].time[templerK]=timerL1I;
	CacheL1IData[templerI][templerK]=input;	
}

}


// L2 PLACE

int L2=1;
if(L2){
int missPart=1;	
	timerL1D++;                   //check condition , ödevi kontrol etme mekanizmasý
	sprintf(hexdec, "%x", address);
		HexConvertBin(hexdec,s);
	int a;
	int k=l2s+l2b;
	for(int a=0;a<24-k;a++){
	tagBinary[a]=s[a];
}
	
	int long long tagDecimal=0;
int power=0;
for (j = 24-1-k ; j >= 0; j-- ) {
	 tagDecimal +=  (tagBinary[j] - 48) * (int)pow((double)2, power);
	 power++;
 }
	
	for (i = 0; i < set2Number; i++) {          // we are searhing hit.
	for (k = 0; k <l2E ; k++) {
		if(L2cache[i].tag[k]==tagDecimal){
			L2hit++; 
			i=set2Number;
			missPart=0;
			break;}	 
	}
    }
	
	if(missPart){                                                   // BU BÖLÜM MÝSS PART BÖLÜMÜDÜR BURDA HÝT OLMAYANLARI YERLEÞTÝRÝYORUZ
	L2miss++;
fseek(fp,adressDecimal, SEEK_SET); 
fgets( input, size*4, fp );

	int spaceEmpty=1;
	for (i = 0; i < set2Number; i++) {          // we are putting empty space , ÝLK ÖNCE BOÞLUKLARI DOLDURUYORUZ
	for (k = 0; k <l2E ; k++) {
		if(L2cache[i].valid[k]==0){
		L2cache[i].valid[k]=1;
		L2cache[i].time[k]=timerL2;
		L2cache[i].tag[k]==tagDecimal;
		CacheL1IData[i][k]=input;	
			i=set2Number;
			spaceEmpty=0;
			break;}	 
	}
    }

if(spaceEmpty){
	L2eviction++;
int templerTime=L2cache[0].time[0];
int templerI=0;
int templerK=0;

for (i = 0; i < set2Number; i++) {          // first in first out  // EÐER BOÞLUKLAR DOLDU ÝLE FIRST IN FIRST OUT YAPIYORUZ
	for (k = 0; k <l2E ; k++) {
		if(L2cache[i].time[k]<templerTime){
			
templerTime=L2cache[i].time[k];
templerI=i;
templerK=k;
	}
    }
}
L2cache[templerI].tag[templerK]=tagDecimal;
L2cache[templerI].time[templerK]=timerL2;
CacheL1IData[templerI][templerK]=input;	

}

}
	
	
	
}



	
	
}


if(operation =='L'){
	
	
	int missPart=1;
	timerL1D++;
	sprintf(hexdec, "%x", address);
		HexConvertBin(hexdec,s);
int a;
int k=l1s+l1b;	
for(int a=0;a<24-k;a++){
	tagBinary[a]=s[a];
}
int long long tagDecimal=0;
int power=0;
for (j = 24-1-k ; j >= 0; j-- ) {
	 tagDecimal +=  (tagBinary[j] - 48) * (int)pow((double)2, power);
	// 	 printf("  (tagBinary[j] - 48)=%d ve decimal deðeri %d\n",  (tagBinary[j] - 48) ,decimal); 
	 power++;
//	 printf("j %d ve power %d \n",j,power); 
 }

 for (i = 0; i < set1Number; i++) {          // we are searhing hit.
	for (k = 0; k <l1E ; k++) {
		if(L1Dcache[i].tag[k]==tagDecimal){
			L1Dhit++; 
			i=set1Number;
			missPart=0;
				CacheL1DData[i][k]=input;	
			break;}	 
	}
    }

if(missPart){                                                   // BU BÖLÜM MÝSS PART BÖLÜMÜDÜR BURDA HÝT OLMAYANLARI YERLEÞTÝRÝYORUZ
	L1Dmiss++;
fseek(fp,adressDecimal, SEEK_SET); 
fgets( input, size*4, fp );
	int spaceEmpty=1;
	for (i = 0; i < set1Number; i++) {          // we are putting empty space , ÝLK ÖNCE BOÞLUKLARI DOLDURUYORUZ
	for (k = 0; k <l1E ; k++) {
		if(L1Dcache[i].valid[k]==0){
		L1Dcache[i].valid[k]=1;
		L1Dcache[i].time[k]=timerL1D;
		L1Dcache[i].tag[k]==tagDecimal;
		
			i=set1Number;
			spaceEmpty=0;
			break;}	 
	}
    }

if(spaceEmpty){
	L1Deviction++;
int templerTime=L1Dcache[0].time[0];
int templerI=0;
int templerK=0;

for (i = 0; i < set1Number; i++) {          // first in first out  // EÐER BOÞLUKLAR DOLDU ÝLE FIRST IN FIRST OUT YAPIYORUZ
	for (k = 0; k <l1E ; k++) {
		if(L1Dcache[i].time[k]<templerTime){		
templerTime=L1Dcache[i].time[k];
templerI=i;
templerK=k;
	}
    }
}
L1Dcache[templerI].tag[templerK]=tagDecimal;
L1Dcache[templerI].time[templerK]=timerL1D;
CacheL1DData[templerI][templerK]=input;	
}

}	
                                           // L2 PLACE
int L2=1;
if(L2){
int missPart=1;	
	timerL1D++;
	sprintf(hexdec, "%x", address);
		HexConvertBin(hexdec,s);
	int a;
	int k=l2s+l2b;
	for(int a=0;a<24-k;a++){
	tagBinary[a]=s[a];
}
	
	int long long tagDecimal=0;
int power=0;
for (j = 24-1-k ; j >= 0; j-- ) {
	 tagDecimal +=  (tagBinary[j] - 48) * (int)pow((double)2, power);
	 power++;
 }
	
	for (i = 0; i < set2Number; i++) {          // we are searhing hit.
	for (k = 0; k <l2E ; k++) {
		if(L2cache[i].tag[k]==tagDecimal){
			L2hit++; 
			i=set2Number;
			missPart=0;
			break;}	 
	}
    }
	
	if(missPart){                                                   // BU BÖLÜM MÝSS PART BÖLÜMÜDÜR BURDA HÝT OLMAYANLARI YERLEÞTÝRÝYORUZ
	L2miss++;
fseek(fp,adressDecimal, SEEK_SET); 
fgets( input, size*4, fp );
	int spaceEmpty=1;
	for (i = 0; i < set2Number; i++) {          // we are putting empty space , ÝLK ÖNCE BOÞLUKLARI DOLDURUYORUZ
	for (k = 0; k <l2E ; k++) {
		if(L2cache[i].valid[k]==0){
		L2cache[i].valid[k]=1;
		L2cache[i].time[k]=timerL2;
		L2cache[i].tag[k]==tagDecimal;
		CacheL2Data[i][k]=input;	

			i=set2Number;
			spaceEmpty=0;
			break;}	 
	}
    }

if(spaceEmpty){
	L2eviction++;
int templerTime=L2cache[0].time[0];
int templerI=0;
int templerK=0;

for (i = 0; i < set2Number; i++) {          // first in first out  // EÐER BOÞLUKLAR DOLDU ÝLE FIRST IN FIRST OUT YAPIYORUZ
	for (k = 0; k <l2E ; k++) {
		if(L2cache[i].time[k]<templerTime){
			
templerTime=L2cache[i].time[k];
templerI=i;
templerK=k;
	}
    }
}
L2cache[templerI].tag[templerK]=tagDecimal;
L2cache[templerI].time[templerK]=timerL2;
CacheL2Data[templerI][templerK]=input;	

}

}
	
	
	
}
	
}
if(operation =='S'){                                      // BURDA VERILEN ADRES EGER CACHE(L1D VE L2 DA) VAR ISE ORAYA DATA GUNCELLENECEK,VE RAMDE GUNCELLENECEK, YOK ÝSE SADECE RAMDE GÜNCELLENECEK
	                                                      // BEN RAMDE GUNCELLEYEMEDIM
	
	int missPart=1;
	timerL1D++;
	sprintf(hexdec, "%x", address);
		HexConvertBin(hexdec,s);
int a;
int k=l1s+l1b;	
for(int a=0;a<24-k;a++){
	tagBinary[a]=s[a];
}
int long long tagDecimal=0;
int power=0;
for (j = 24-1-k ; j >= 0; j-- ) {
	 tagDecimal +=  (tagBinary[j] - 48) * (int)pow((double)2, power);
	// 	 printf("  (tagBinary[j] - 48)=%d ve decimal deðeri %d\n",  (tagBinary[j] - 48) ,decimal); 
	 power++;
//	 printf("j %d ve power %d \n",j,power); 
 }

 for (i = 0; i < set1Number; i++) {          // we are searhing hit.
	for (k = 0; k <l1E ; k++) {
		if(L1Dcache[i].tag[k]==tagDecimal){
			L1Dhit++; 
			i=set1Number;
			missPart=0;
				CacheL1DData[i][k]=data;	
			break;}	 
	}
    }

if(missPart){                                                   // BU BÖLÜM MÝSS PART BÖLÜMÜDÜR BURDA HÝT OLMAYANLARI YERLEÞTÝRÝYORUZ
	L1Dmiss++;
	
/*	
	
fseek(fp,adressDecimal, SEEK_SET); 
fgets( input, size*4, fp );
	int spaceEmpty=1;
	for (i = 0; i < set1Number; i++) {          // we are putting empty space , ÝLK ÖNCE BOÞLUKLARI DOLDURUYORUZ
	for (k = 0; k <l1E ; k++) {
		if(L1Dcache[i].valid[k]==0){
		L1Dcache[i].valid[k]=1;
		L1Dcache[i].time[k]=timerL1D;
		L1Dcache[i].tag[k]==tagDecimal;
		
			i=set1Number;
			spaceEmpty=0;
			break;}	 
	}
    }

if(spaceEmpty){
	L1Deviction++;
int templerTime=L1Dcache[0].time[0];
int templerI=0;
int templerK=0;

for (i = 0; i < set1Number; i++) {          // first in first out  // EÐER BOÞLUKLAR DOLDU ÝLE FIRST IN FIRST OUT YAPIYORUZ
	for (k = 0; k <l1E ; k++) {
		if(L1Dcache[i].time[k]<templerTime){		
templerTime=L1Dcache[i].time[k];
templerI=i;
templerK=k;
	}
    }
}
L1Dcache[templerI].tag[templerK]=tagDecimal;
L1Dcache[templerI].time[templerK]=timerL1D;
CacheL1DData[templerI][templerK]=input;	
}


*/
}	
                                           // L2 PLACE
int L2=1;
if(L2){
int missPart=1;	
	timerL1D++;
	sprintf(hexdec, "%x", address);
		HexConvertBin(hexdec,s);
	int a;
	int k=l2s+l2b;
	for(int a=0;a<24-k;a++){
	tagBinary[a]=s[a];
}
	
	int long long tagDecimal=0;
int power=0;
for (j = 24-1-k ; j >= 0; j-- ) {
	 tagDecimal +=  (tagBinary[j] - 48) * (int)pow((double)2, power);
	 power++;
 }
	
	for (i = 0; i < set2Number; i++) {          // we are searhing hit.
	for (k = 0; k <l2E ; k++) {
		if(L2cache[i].tag[k]==tagDecimal){
			L2hit++; 
			i=set2Number;
			missPart=0;
			break;}	 
	}
    }
	
	if(missPart){                                                   // BU BÖLÜM MÝSS PART BÖLÜMÜDÜR BURDA HÝT OLMAYANLARI YERLEÞTÝRÝYORUZ
	L2miss++;
	
/*	
fseek(fp,adressDecimal, SEEK_SET); 
fgets( input, size*4, fp );
	int spaceEmpty=1;
	for (i = 0; i < set2Number; i++) {          // we are putting empty space , ÝLK ÖNCE BOÞLUKLARI DOLDURUYORUZ
	for (k = 0; k <l2E ; k++) {
		if(L2cache[i].valid[k]==0){
		L2cache[i].valid[k]=1;
		L2cache[i].time[k]=timerL2;
		L2cache[i].tag[k]==tagDecimal;
		CacheL2Data[i][k]=input;	

			i=set2Number;
			spaceEmpty=0;
			break;}	 
	}
    }

if(spaceEmpty){
	L2eviction++;
int templerTime=L2cache[0].time[0];
int templerI=0;
int templerK=0;

for (i = 0; i < set2Number; i++) {          // first in first out  // EÐER BOÞLUKLAR DOLDU ÝLE FIRST IN FIRST OUT YAPIYORUZ
	for (k = 0; k <l2E ; k++) {
		if(L2cache[i].time[k]<templerTime){
			
templerTime=L2cache[i].time[k];
templerI=i;
templerK=k;
	}
    }
}
L2cache[templerI].tag[templerK]=tagDecimal;
L2cache[templerI].time[templerK]=timerL2;
CacheL2Data[templerI][templerK]=input;	

}


 */
}
	
	
	
}

}  
if(operation =='M'){               // BURDA ÝLK ONCE CACHE DE VAR MI YOK MU ONA BAKIYORUZ,cache'lerde yoksa cache'e taþýyoruz,daha sonra store iþlemi yapýyoruz.
	
	
	int missPart=1;
	timerL1D++;
	sprintf(hexdec, "%x", address);
		HexConvertBin(hexdec,s);
int a;
int k=l1s+l1b;	
for(int a=0;a<24-k;a++){
	tagBinary[a]=s[a];
}
int long long tagDecimal=0;
int power=0;
for (j = 24-1-k ; j >= 0; j-- ) {
	 tagDecimal +=  (tagBinary[j] - 48) * (int)pow((double)2, power);
	 power++;
 }

 for (i = 0; i < set1Number; i++) {          // we are searhing hit.
	for (k = 0; k <l1E ; k++) {
		if(L1Dcache[i].tag[k]==tagDecimal){
			L1Dhit++; 
			i=set1Number;
			missPart=0;
				CacheL1DData[i][k]=data;	
			break;}	 
	}
    }

if(missPart){                                                   // BU BÖLÜM MÝSS PART BÖLÜMÜDÜR BURDA HÝT OLMAYANLARI YERLEÞTÝRÝYORUZ
	L1Dmiss++;
	L1Dhit++;
fseek(fp,adressDecimal, SEEK_SET); 
fgets( input, size*4, fp );
	int spaceEmpty=1;
	for (i = 0; i < set1Number; i++) {          // we are putting empty space , ÝLK ÖNCE BOÞLUKLARI DOLDURUYORUZ
	for (k = 0; k <l1E ; k++) {
		if(L1Dcache[i].valid[k]==0){
		L1Dcache[i].valid[k]=1;
		L1Dcache[i].time[k]=timerL1D;
		L1Dcache[i].tag[k]==tagDecimal;
			CacheL1DData[i][k]=data;
			i=set1Number;
			spaceEmpty=0;
			break;}	 
	}
    }

if(spaceEmpty){
	L1Deviction++;
int templerTime=L1Dcache[0].time[0];
int templerI=0;
int templerK=0;

for (i = 0; i < set1Number; i++) {          // first in first out  // EÐER BOÞLUKLAR DOLDU ÝLE FIRST IN FIRST OUT YAPIYORUZ
	for (k = 0; k <l1E ; k++) {
		if(L1Dcache[i].time[k]<templerTime){		
templerTime=L1Dcache[i].time[k];
templerI=i;
templerK=k;
	}
    }
}
L1Dcache[templerI].tag[templerK]=tagDecimal;
L1Dcache[templerI].time[templerK]=timerL1D;
CacheL1DData[templerI][templerK]=data;	
}

}	
                                           // L2 PLACE
int L2=1;
if(L2){
int missPart=1;	
	timerL1D++;
	
	sprintf(hexdec, "%x", address);
		HexConvertBin(hexdec,s);
	int a;
	int k=l2s+l2b;
	for(int a=0;a<24-k;a++){
	tagBinary[a]=s[a];
}
	
	int long long tagDecimal=0;
int power=0;
for (j = 24-1-k ; j >= 0; j-- ) {
	 tagDecimal +=  (tagBinary[j] - 48) * (int)pow((double)2, power);
	 power++;
 }
	
	for (i = 0; i < set2Number; i++) {          // we are searhing hit.
	for (k = 0; k <l2E ; k++) {
		if(L2cache[i].tag[k]==tagDecimal){
			L2hit++; 
			i=set2Number;
	CacheL2Data[i][k]=data;	

			missPart=0;
			break;}	 
	}
    }
	
	if(missPart){                                                   // BU BÖLÜM MÝSS PART BÖLÜMÜDÜR BURDA HÝT OLMAYANLARI YERLEÞTÝRÝYORUZ
	L2miss++;
	L2hit++;
fseek(fp,adressDecimal, SEEK_SET); 
fgets( input, size*4, fp );
	int spaceEmpty=1;
	for (i = 0; i < set2Number; i++) {          
	for (k = 0; k <l2E ; k++) {
		if(L2cache[i].valid[k]==0){
		L2cache[i].valid[k]=1;
		L2cache[i].time[k]=timerL2;
		L2cache[i].tag[k]==tagDecimal;
		CacheL2Data[i][k]=data;	

			i=set2Number;
			spaceEmpty=0;
			break;}	 
	}
    }

if(spaceEmpty){
	L2eviction++;
int templerTime=L2cache[0].time[0];
int templerI=0;
int templerK=0;

for (i = 0; i < set2Number; i++) {          // first in first out  // EÐER BOÞLUKLAR DOLDU ÝLE FIRST IN FIRST OUT YAPIYORUZ
	for (k = 0; k <l2E ; k++) {
		if(L2cache[i].time[k]<templerTime){
			
templerTime=L2cache[i].time[k];
templerI=i;
templerK=k;
	}
    }
}
L2cache[templerI].tag[templerK]=tagDecimal;
L2cache[templerI].time[templerK]=timerL2;
CacheL2Data[templerI][templerK]=data;	

}

}
	
	
	
}
	
}	
	
	
	
}                                                                                                                           // while ýn sonu
	printf("----L1I-INSTRUCTION.CACHE---- \nTotal Misses : %d \nTotal Hit: %d \nTotal Eviction : %d \n",L1Imiss,L1Ihit,L1Ieviction);
		printf("----L1D-DATA.CACHE---- \nTotal Misses : %d \nTotal Hit: %d \nTotal Eviction : %d \n",L1Dmiss,L1Dhit,L1Deviction);
      	printf("----L2-L2.CACHE---- \nTotal Misses : %d \nTotal Hit: %d \nTotal Eviction : %d \n",L2miss,L2hit,L2eviction);

fclose(fp);
fclose(traceFiles);



 outp=fopen("output.txt", "w");//printing output.txt
 	fprintf(outp,"----L1I-INSTRUCTION.CACHE---- \nTotal Misses : %d \nTotal Hit: %d \nTotal Eviction : %d \n",L1Imiss,L1Ihit,L1Ieviction);
		fprintf(outp,"----L1D-DATA.CACHE---- \nTotal Misses : %d \nTotal Hit: %d \nTotal Eviction : %d \n",L1Dmiss,L1Dhit,L1Deviction);
      	fprintf(outp,"----L2-L2.CACHE---- \nTotal Misses : %d \nTotal Hit: %d \nTotal Eviction : %d \n",L2miss,L2hit,L2eviction);
fclose(outp);

return 0;
}




