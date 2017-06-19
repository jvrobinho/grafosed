#include <stdio.h>
#include <stdlib.h>
  typedef struct  viz{
  int id_viz;
  int custo;
  int passou;
  struct viz * prox_viz;
}TViz;

typedef struct no{
  int id_no;
  int cor;
  int ponte;
  TViz * prim_viz;
  struct no * prox_no;
}TNO;

typedef struct grafo{
  TNO * prim;
  int numCores;
}TG;



TG * inicializa(void){
  TG * g = (TG*)malloc(sizeof(TG));
  g->prim = NULL;
  g->numCores = 1;
  return g;
}

void imprime(TG * g){
    TNO * p = g->prim;
    while(p){
        printf("%d \n", p->id_no);
        TViz * v = p->prim_viz;
        while(v){
            printf("viz: %d \t custo: %d\n", v->id_viz, v->custo);
            v=v->prox_viz;
        }
        p=p->prox_no;
    }
}

TNO * buscaNo(TG * g, int no){
  TNO * p = g->prim;
  while((p)&&(p->id_no!=no))p=p->prox_no;
  return p;
}
TViz * buscaAresta(TG * g, int no1, int no2){
    if(!g) return NULL;
    TNO * n1 = buscaNo(g,no1);
    if(!n1) return NULL;
    TNO * n2 = buscaNo(g,no2);
    if(!n2) return NULL;

    TViz * p = n1->prim_viz;
    while(p && (p->id_viz != no2))
      p=p->prox_viz;
    return p;
}
void insereNo(TG * g, int elem){
    if(!g) return;
    TNO * aux = buscaNo(g,elem);
    if(aux) return;

    TNO * no = (TNO*)malloc(sizeof(TNO));
    no->id_no = elem;
    no->cor = 0;

    no->prim_viz = NULL;
    if(!g->prim){
      g->prim = no;
      return;
    }
	  aux = g->prim;
    while(aux->prox_no){
      aux = aux->prox_no;
    }
    aux->prox_no = no;
    no->prox_no = NULL;

    return;
}

void insereAresta(TG * g, int no1, int no2, int custo){
    TNO * n1 = buscaNo(g,no1);
    if(!n1) return;
    TNO * n2 = buscaNo(g,no2);
    if(!n2) return;
    TViz * viz = buscaAresta(g,no1,no2);
    if(viz){
      viz->custo = custo;
      return;
    }



    viz = (TViz*) malloc (sizeof(TViz));
    viz->custo = custo;
    viz->id_viz = n2->id_no;
    viz->passou = 0;
    if(n1->prim_viz){
      TViz * aux = n1->prim_viz;
      while(aux->prox_viz) aux = aux->prox_viz;
      viz->prox_viz = aux->prox_viz;
      aux->prox_viz = viz;
      return;
    }
    viz->prox_viz = n1->prim_viz;
    n1->prim_viz = viz;
    return;
}
void removeAresta(TG * g, int no1, int no2){
  TNO * n1 = buscaNo(g,no1);
  if(!no1) return;
  TNO * n2 = buscaNo(g,no2);
  if(!no2) return;
  TViz * v = n1->prim_viz, *ant = NULL;
  while(v && (v->id_viz != no2)){
    ant = v;
    v=v->prox_viz;
  }
  if(!v) return;
  if(!ant) n1->prim_viz = v->prox_viz;
  else ant->prox_viz = v->prox_viz;
  free(v);
}
void removeNo(TG * g, int id){
  TNO * p= g->prim, *ant = NULL;
  while((p) && (p->id_no!= id)){
    ant = p;
    p=p->prox_no;
  }
  if(!p) return;
  TViz * v = p->prim_viz;
  while(v){
    removeAresta(g,id,v->id_viz);
    v=p->prim_viz;
  }
  if(!ant) g->prim = p->prox_no;
  else ant->prox_no = p->prox_no;
  free(p);
  return;
}


void libera (TG * g){
    TNO * no = g->prim;
    while(no){
        TViz * aresta = no->prim_viz;
        while(aresta){
            TViz * aux = aresta;
            aresta = aresta->prox_viz;
            free(aux);
        }
        g->prim = no->prox_no;
        TNO * aux_no = no;
        no = no->prox_no;
        free(aux_no);
    }
}

void imprimeNo(TG * g, int id){
  if(!g)return;
  TNO * p = buscaNo(g,id);
  if(!p) return;
  printf("No %d \n Cor: %d \n", p->id_no, p->cor);
  TViz * v = p->prim_viz;
  while(v){
      printf("viz: %d \t custo: %d\n", v->id_viz, v->custo);
      v=v->prox_viz;
  }
}
