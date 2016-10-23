#ifndef SOLTADOR_H_INCLUDED
#define SOLTADOR_H_INCLUDED

typedef struct _OBJETO_SOLTADOR
{
   int x;
   int y;
   int velocidade;

}OBJETO_SOLTADOR;

OBJETO_SOLTADOR soltaObjetos[5];
int continua[5];
void iniciar()
{
   int i;
   soltaObjetos[0].y = 40;
   soltaObjetos[1].y = 200;
   soltaObjetos[2].y = 560;
   soltaObjetos[3].y = 400;
   soltaObjetos[4].y = 700;

   for(i=0;i<5;i++)
   {
     continua[i]=0;
     soltaObjetos[i].velocidade = 2;//velocidade do creu
     soltaObjetos[i].x=1400;
   }
}



void MEXESOLTA(int x)
{
    if(x==0)
    {
        soltaObjetos[x].y+=soltaObjetos[x].velocidade;
        if(soltaObjetos[x].y<5||soltaObjetos[x].y>100)
        {
            soltaObjetos[x].velocidade*=(-1);
        }
        return;
    }
    else if(x==1||x==3)
    {
        soltaObjetos[x].y+=soltaObjetos[x].velocidade;
        if(soltaObjetos[x].y<200 || soltaObjetos[x].y>380)
        {
           if(soltaObjetos[x].y<195)
           {
              soltaObjetos[x].y = 202;
           }
           else if(soltaObjetos[x].y>385)
           {
              soltaObjetos[x].y = 378;
           }
           if(soltaObjetos[x].velocidade!=2 && soltaObjetos[x].velocidade!=-2)
           {
              soltaObjetos[x].velocidade=2;
           }
           else
           {
              soltaObjetos[x].velocidade*=(-1);
           }
        }
        return;
    }
    else if(x==2||x==4)
    {
        soltaObjetos[x].y+=soltaObjetos[x].velocidade;
        if(soltaObjetos[x].y<475||soltaObjetos[x].y>695)
        {
            soltaObjetos[x].velocidade*=(-1);
        }
        return;
    }


}

#endif // SOLTADOR_H_INCLUDED
