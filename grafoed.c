#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


/**            PERGUNTAS PRA FAZER PRA TIA BEBEL <3
+Perguntar se podem existir nos com valores repetidos em um grafo R: Não
+Perguntar se eu posso usar estruturas auxiliares para guardar pontes
+Perguntar se grafos unicos com autoloop existem      R: Não
+Perguntar se grafos unicos sao conexos os desconexos R: Desconexos
*/

/**
            Checando orientacao em um grafo
Para cada no do grafo
    Para cada vizinho desse no
        Se o no original nao e alcancado pelo vizinho, retorna 1
    Repete para todos os vizinhos
Repete para todos os nos

A logica:
      Dado um grafo com M nos:
      Se todos os nos sao alcancaveis a partir dos outros nos, ele nao e orientado.
      Lgo, se existe um no para qual essa sentenca e falsa, o grafo e orientado.



Implementado mais facilmente usando buscaAresta

*/

int checaOrientacao(TG * g){
  if((!g)||(!g->prim->prim_viz)) return 0;
  TNO * p = g->prim;

  while(p){
    TViz * v = p->prim_viz;
    while(v){

      TNO * vizinho = buscaNo(g,v->id_viz);
      TViz * vizinhosBusca = vizinho->prim_viz;

      while((vizinhosBusca->id_viz != p->id_no)&&(vizinhosBusca)){
        if(!vizinhosBusca) return 1;
        vizinhosBusca = vizinhosBusca->prox_viz;
      }
      v=v->prox_viz;
    }
    p=p->prox_no;
  }
  return 0;
}
/**
            Verificando se V alcanca W(procurando W a partir de V)

Para todos os vizinhos de V
    Se W e vizinho de V, retorna 1
    Se nao, procura W a partir do vizinho de V

*/
int procuraCaminho(TG * g, int id1, int id2){
  if(!g) return 0;
  TNO * no1 = buscaNo(g, id1);
  if(!no1) return 0;
  TNO * no2 = buscaNo(g, id2);
  if(!no2) return 0;

  if(!no1->prim_viz) return 0;

  TViz * v = no1->prim_viz;
  int resp = 0;

  while(v && (!resp)){
    if(v->id_viz == id2) return 1;

    if(!v->passou){
      v->passou = 1;
      resp = procuraCaminho(g,v->id_viz,id2);
      v->passou = 0;
    }
    v=v->prox_viz;
  }
  return resp;
}

/**TODO
                        Checando conectividade

Para todos os nos do grafo
    vejo se ele alcanca outros nos(procuraCaminho)
        se ele alcanca, pinta da mesma cor
        se nao alcanca, pinta o subgrafo da proxima cor

No pior caso, o numero de cores sera o numero de nos informado no arquivo(ou seja,
grafo totalmente desconexo).
No melhor caso, o numero de cores sera igual a 1(ou seja, grafo totalmente conexo)

*/
void pintaSub(TG * g, int no){//pinta toda a componente conexa
  if(!g) return;
  int cor = g->numCores;
  TNO * no1 = buscaNo(g, no);
  if(!no1) return;
  if(!no1->cor) no1->cor = cor;
  TViz * a = no1->prim_viz;
  while(a){
    TNO * viz = buscaNo(g,a->id_viz);
    if(!viz->cor) viz->cor = cor;
    pintaSub(g,a->id_viz);
    a=a->prox_viz;
  }
  return;
}

int verificaCor(TG * g,int id){//verifica se existe algum NO na componente conexa que possua cor
  if(!g) return 0;

  TNO * no1 = buscaNo(g, id);
  if(!no1) return 0;

  TNO * no2 = g->prim;
  while(no2){
    if(procuraCaminho(g,no1->id_no,no2->id_no) && no2->cor) return no2->cor;
    no2=no2->prox_no;
  }
  return 0;
}

int conexo(TG * g){
  if(!g) return 0;
  TNO * p = g->prim;
  if(!p->prox_no) return 1;
  int cor = g->numCores;
  p->cor = cor;
  int resp = 1;
  while(p){
    TNO * q = g->prim;

    while(q){
      if(q->id_no!=p->id_no){

        if(procuraCaminho(g,p->id_no,q->id_no)){
          if(q->cor != p->cor) g->numCores--;
          q->cor = p->cor;
        }

        else if (!procuraCaminho(g,p->id_no,q->id_no)){
          if(!q->cor){
            int pintar = verificaCor(g,q->id_no);
            if(!pintar){
              g->numCores++;
              cor=g->numCores;
              q->cor = cor;
            }
            else pintaSub(g,q->id_no);

          }
          resp = 0;
        }
      }
      q=q->prox_no;
    }
  }
  return resp;
}




/**TODO

Remove uma aresta do grafo
Procura um caminho do no V ate o no W
                      Encontrando pontes
    se existe caminho, nao e uma ponte
    se nao, e uma ponte
Insere a aresta novamente
*/

void achaPontes(TG * g){
  if(!g) return;
  TNO * p = g->prim;
  while(p){
    while(p && (!p->prim_viz)) p = p->prox_no;
    if(!p) return;
    TViz * v = p->prim_viz;

    int primAresta = v->id_viz;
    int aux;
    do{
      aux = v->id_viz;
      removeAresta(g,p->id_no,aux);
      int caminho = procuraCaminho(g,p->id_no,aux);
      if(!caminho){
        printf("%d faz ponte com %d",p->id_no,aux);
      }
      insereAresta(g,p->id_no,aux,0);
    }while(aux!=primAresta);

    p=p->prox_no;
  }
}

/**TODO
                      Checando componente fortemente conexa

*/
/*Vou alterar um pouco a logica

Se elas forem fortemente conexas, eu so pinto elas da mesma cor,
ai eu crio uma função imprime que imprime todos os nos que tiverem a mesma cor.

*/
void fortementeConexa(TG * g){
  TNO * no1 = g->prim;
  int corNo1 = no1->cor;
  int totalCores = g->numCores;
  while(no1){
    TNO * no2 = g->prim;
    if(no1!= no2){
      while(no2){
        int vTow = procuraCaminho(g, no1->id_no, no2->id_no);
        int wTov = procuraCaminho(g, no2->id_no, no1->id_no);
        if(vTow && wTov){
          no2->cor = corNo1;
        }
        else
        no2 = no2->prox_no;
      }
    }
  no1 = no1->prox_no;
  }
}
TG * criaGrafo(char * nomeArq){
    printf("Criando grafo");
    FILE * fp;
    fp = fopen("grafo.txt","rt");

    if(!fp) {printf("EXIT\n");exit(1);}
	printf("Abriu\n");
    int numNos,no1,no2,n=0,read;
    fscanf(fp,"%d",&numNos);
    printf("Inicializando grafo\n");
    TG* g = inicializa();

    read = fscanf(fp,"%d %d",&no1,&no2);
	printf("%d %d\n", no1, no2);
	printf("%d cores\n",g->numCores);
    
	while(read!=EOF){
      insereNo(g,no1);
	  printf("Inserindo Aresta");
	  if(!buscaNo(g,no2)) insereNo(g,no2);
      insereAresta(g,no1,no2,0);
      read = fscanf(fp,"%d %d",&no1,&no2);
    }

    fclose(fp);
    return g;
}

int main(void){
  char * nomeArq = (char*)malloc(100);
  printf("Digite o nome do arquivo: ");
  scanf("%s", nomeArq);
  
  TG * l = NULL;
  printf("Entrando em cria grafo");
  l = criaGrafo(nomeArq);
  printf("Grafo criado!\n");
  imprime(l);

  return 0;






}
