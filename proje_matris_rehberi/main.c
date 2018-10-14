#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#define DOSYA_YOLU "matris.txt"
#define DOSYA_YOLU1 "hadamard.txt"
#define DOSYA_YOLU2 "dairesel.txt"
#define DOSYA_YOLU3 "simetrik.txt"
int hadamard(int matris[][16], int d);
int dairesel(int x[][16], int d);
int simetrik(int matris[][16],int d);
int main()
{

    int satir,sutun;
    while(1){
       printf("boyut gir:");
       scanf("%d",&satir);
       if(satir<4 || satir>16)
          continue;


        else{
           sutun=satir;
           printf("satir:%d  sutun:%d\n\n",satir,sutun);
           break;
    }
 }

    int **matris;
    int i,j,k;

    matris = (int **) calloc(satir, sizeof(int));       //[3]


    for(k = 0; k < satir; k++)                         //[3]
	matris[k] = (int *) calloc(sutun, sizeof(int));

	FILE *dosya;
    if((dosya=fopen(DOSYA_YOLU,"w"))==NULL){
        printf("dosya acilamadi");
        exit(1);
    }

	for(i=0;i<satir;i++){
        for(j=0;j<sutun  ;j++){
           scanf("%d",&matris[i][j]);
           fprintf(dosya,"  %d",matris[i][j]);
        }
        printf("\n");
        fputs("\n",dosya);
    }
    fclose(dosya);

    FILE *dosya1;
    if((dosya1=fopen(DOSYA_YOLU,"r"))==NULL){
        printf("dosya acilamadi");
        exit(1);
    }
    int buf[16][16],a=0,b=0;
    for(a=0;a<satir;a++){
        for(b=0;b<sutun;b++){
            fscanf (dosya1,"%d",&buf[a][b]);
            printf(" %d",buf[a][b]);
        }
        printf("\n");
    }
    fclose(dosya1);
    allegro_init();      //[1]
    install_keyboard();     //[1]
    set_gfx_mode(GFX_AUTODETECT, 640,480,0,0);   //[1]
    int val, scancode;                             //[1]

    textout_ex(screen,font,"1=hadamard matris", 10, 10, makecol(255,255,255), -1);
    textout_ex(screen,font,"2=dairesel matris", 10, 20, makecol(255,255,255), -1);
    textout_ex(screen,font,"3=simetrik matris", 10, 30, makecol(255,255,255), -1);
    textout_ex(screen,font,"seciminizi yapiniz:", 10, 40, makecol(0,255,0), -1);
    while(1){
    val=ureadkey(&scancode);
    if(key[KEY_1]){
        if(satir==4 || satir==8 || satir==16)
            break;
        else{
            textout_ex(screen,font,"tekrar secim yapiniz:", 10, 50, makecol(255,0,0), -1);
            continue;
        }

    }
    else if(key[KEY_2] || key[KEY_3])
            break;
    else
        textout_ex(screen,font,"yanlis secim yaptiniz tekrar secim yapiniz:", 10, 60, makecol(255,0,0), -1);
    }

    switch(scancode){
    case KEY_1:{
        int x=hadamard(buf,satir);
        FILE *dosya2;
        if((dosya2=fopen(DOSYA_YOLU1,"w"))==NULL){
           printf("dosya acilamadi");
           exit(1);
        }

        if(x==1){
           fputs("girilen matris hadamardtir\n",dosya2);
           for(i=0;i<satir;i++){
              for(j=0;j<sutun;j++){
                  fprintf(dosya2," %d",buf[i][j]);
              }
              fputs("\n",dosya2);
           }
        }
        else
            fputs("girilen matris hadamard degildir\n",dosya2);
       fclose(dosya2);
        break;
    }

    case KEY_2:{
       int y=dairesel(buf,satir);
       FILE *dosya3;
       if((dosya3=fopen(DOSYA_YOLU2,"w"))==NULL){
          printf("dosya acilamadi");
          exit(1);
       }
        if(y==1){
           fputs("girilen matris daireseldir\n",dosya3);
           for(i=0;i<satir;i++){
              for(j=0;j<sutun;j++){
                  fprintf(dosya3,"  %d",buf[i][j]);
              }
              fputs("\n",dosya3);
          }

        }
        else
            fputs("girilen matris daireseldir\n",dosya3);
        fclose(dosya3);

        break;
    }

    case KEY_3:{
       int z=simetrik(buf,satir);
       FILE *dosya4;
        if((dosya4=fopen(DOSYA_YOLU3,"w"))==NULL){
           printf("dosya acilamadi");
           exit(1);
        }

        if(z==1){
           fputs("girilen matris simetriktir\n",dosya4);
           for(i=0;i<satir;i++){
              for(j=0;j<sutun;j++){
                  fprintf(dosya4,"  %d",buf[i][j]);
              }
              fputs("\n",dosya4);
          }

        }
        else
            fputs("girilen matris simetrik deigildir\n",dosya4);
        fclose(dosya4);
       break;
    }

    default:
        textout_ex(screen,font,"Yanlis secim yaptiniz:", 10, 70, makecol(255,0,0), -1);
        break;
}
    return 0;
}
END_OF_MAIN()

int hadamard(int matris[][16], int d)
{
    int i,j,N=d-1;
    for(i=0;i<d;i++){
        for(j=0;j<d;j++){
            if(matris[i][j]!=matris[N-i][N-j])
               return 0;
            }
        }

    return 1;
}

int dairesel(int x[][16], int d)
{
   int i,j,m,n;
   int k=1;
   for(i=0;i<d-1;i++){
        if(x[i][i]!=x[i+1][i+1])
        return 0;
   }

    for(i=0;i<d-1;i++){
        for(j=i+k;j<=d;j++){
            m=j+1;
            n=j;
            if(j+1==d)
                m=0;
            else if(j+1>d)
            {
                m=1;
                n=0;
            }

            if(x[i][n]!=x[i+1][m])
                return 0;
        }
    }
   return 1;
}

int simetrik(int matris[][16],int d)
{
    int y[d][d];
    int i,j;
    for(i=0;i<d;i++){
        for(j=0;j<d;j++){
            y[j][i]=matris[i][j];
        }
    }
    for(i=0;i<d;i++){
        for(j=0;j<d;j++){
            if(matris[i][j]!=y[i][j])
                return 0;
        }
    }
    return 1;
}
