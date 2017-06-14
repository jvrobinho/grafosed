#include <stdio.h>
#include <stdlib.h>
#include <grafo.h>
TNO * buscaNo(TG * g, int elem){};
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

      while((vizinhoBusca->id_viz != p->id_no)&&(vizinnhosBusca)){
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

(Preciso pintar?)
*/
int procuraCaminho(TG * g, int id1, int id2){
  if(!g) return 0;
  TNO * no1 = buscaNo(g, id1);
  if(!no1) return 0;
  TNO * no2 = buscaNo(g, id2);
  if(!no2) return 0;

  if(!no1->prox_viz) return 0;

  TViz * v = no1->prox_viz;
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

int conexo(TG * g){
  if(!g) return 0;
  TNO * p = g->prim;
  if(!p->prox_no) return 1;
  int cor = g->numCores;
  p->cor = cor;
  resp = 1;
  while(p){
    TNO * q = g->prim;
    while(q){
      if(q->id!=p->id){
        if(procuraCaminho(g,p->id,q->id) && (!q->cor)){
          q->cor = p->cor;
        }
        else if (!procuraCaminho(g,p->id,q->id) && (!q->cor)){
          g->numCores++;
          cor=g->numCores;
          q->cor = cor;
          pintaSub(g,q->id);
          resp = 0;
        }
      }
      q=q->prox_no;
    }
  }
  return resp;
}

void pintaSub(TG * g, int no){//pinta toda a componente conexa
  if(!g) return;
  int cor = g->numCores
  TNO * no1 = buscaNo(g, no);
  if(!no1) return;
  if(!no1->cor) no1->cor = cor;
  TViz * a = no1->prim_viz;
  while(a){
    TNO * viz = buscaNo(g,a->id_viz);
    if(!viz->cor) viz->cor = cor;
    pintaGrafo(g,a->id_viz);
    a=a->prox_viz;
  }
  return;
}



/**TODO
                      Encontrando pontes

Remove uma aresta do grafo
Procura um caminho do no V ate o no W
    se existe caminho, nao e uma ponte
    se nao, e uma ponte
Insere a aresta novamente
*/


/**TODO
                      Checando componente conexa

*/
