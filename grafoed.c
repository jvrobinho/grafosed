#include <stdio.h>
#include <stdlib.h>
#include <grafo.h>
typedef struct grafo{
  TNO * prim;
  int numCores;
}TG;

typedef struct no{
  int id_no;
  int cor;
  TViz * prim_viz;
  struc no * prox_no;
}TNO;

typedef struct viz{
  int id_viz;
  int custo;
  struct viz * prox_viz;
}TViz;


void imprime (TG * g ){
    TNO * p = g->prim;
    while(p){
        printf("%d \n", p->id_no);
        TViz * v = p->prim_viz;
        while(v){
            printf("viz: %d \t custo: %d", v->id_viz, v->custo);
            v=v->prox_viz;
        }
        p=p->prox_no;
    }
}
void insereNo(TG * g, int elem){
    TNO * aux = g->prim;
    TNO * no = (TNO*)malloc(sizeof(TNO));
    while(aux->prox_no){
        aux = aux->prox_no;
    } 
    aux->prox_no = no;
    no->id_no = elem;
} 
TNO * buscaNo(TG * g, int elem){
    TNO * no = g->prim;
    while(no){
        if(elem== no->id_no){
            return no;
        }  
        no = no->prox_no;
    }
    return null; 
}
void removeNO(TG * g, int elem){
    TNO no = buscaNO(g, elem);
    if(!no)
        return;  
    }  
    while(no->prim_viz){
        TNO * viz = no->prim_viz;
        no->prim_viz = viz->prox_viz;
        free(viz); 
    }
    free(no); 
    TNO * aux = g->prim;

    while(aux){
        TViz * aux_viz = aux->prim_viz;
        while(aux_viz){
            if(aux_viz->id_viz == elem){
                TViz * c = aux_viz;
                aux_viz = aux_viz->prox_viz;
                free(c); 
            }  
            aux = aux->prox_no;
        }            
    }
     
}


TViz * buscaAresta(TG * g, int no1, int no2){
    TNO * no = g->prim;
    while(no){
        if(no->id_no == no1){
            TViz aresta = no->prim_viz;
            while(aresta){
                if(aresta->id_viz == no2){
                    return aresta;   
                }
            }
            return; 
        }
    }
    return; 
}
void insereAresta(TG * g, int no1, int no2, int custo){
    TViz aresta = buscaAresta(g,no1,no2);
    if(aresta){
    return;
    }
    TNO * n1 = buscaNo(g,no1);
    TNO * n2 = buscaNo(g,no2);
    if(n1 && n2){
        TViz viz = n1->prim_viz;
        while(viz->prox_viz){
        viz= viz->prox_viz;
        }
        viz->prox_viz = (TViz*) malloc (sizeof(TViz));
        viz = viz->prox_viz;
        viz->custo = custo;
        viz->id_viz = no2->id_no;
    }
}
void removeAresta(TG * g, int no1, int no2){
    TViz aresta = buscaAresta(g,no1,no2);
    if(aresta){
    TViz * r = aresta; 
    aresta = aresta->prox_viz;
    free(r);
    }
}
void imprime (TG* g){
    TNO * p = g-> prim;
    while(p){
        printf("%d \n", p->id_no);
        TViz * v = p->prim_viz;
        while(v){
        printf("viz: %d \t custo %d",v->id_viz, v->custo);
        v=v->prox_viz;"
        }
    }
    p=p->prox_no;
        
}
void libera (TG * g){
    TNO * no = g->prim;
    while(no){
        TViz aresta = no->prim_viz;
        while(aresta){
            TViz aux = aresta; 
            aresta = aresta->prox_viz;
            free(aux); 
        }
        g->prim = no->prox_no;
        TNO aux_no = no;
        no = no->prox_no;
        free(aux_no);
    }
}



void fortementeConexa(TG * g){
    TNO * no1 = g->prim;
    while(no1){
        TNO * no2 = g->prim;
        if(no1!= no2){
            while(no2){
                TViz a1 = buscaAresta(g,no1->id_no,no2->id_no);
                TViz a2 = buscaAresta(g,no2->id_no,no1->id_no);
                if(a1 && a2){
                    //Printa que o nome das duas sendo conexas;
                }
            no2 = no2->prox_no;
            }
        }
        no1 = no1->prox_no;
    }


}
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

Remove uma aresta do grafo
Procura um caminho do no V ate o no W
                      Encontrando pontes
    se existe caminho, nao e uma ponte
    se nao, e uma ponte
Insere a aresta novamente
*/
int verificaPonte(TG * g, int id1, int id2){
  if(!g) return;

  TNO * no1 = buscaNo(g, id1);
  if(!no1) return 0;
  TNO * no2 = buscaNo(g, id2);
  if(!no2) return 0;
  TViz * aresta = buscaAresta(g, id1, id2);
  if(!aresta) return 0;

  removeAresta(g,id1,id2);
  removeAresta(g,id2,id1);

  int caminho = procuraCaminho(g,id1,id2);

  if(!caminho) return 0;
  return 1;
}

void achaPontes(TG * g){
  if(!g) return 0;
  TNO * p = g->prim;
  while(p && !p->prim_viz){
    p=p->prox_no;
  }
  if(!p) return;
  TViz * a = p->prim_viz;
  while(a){
    TNO * v = buscaNo(g,v->id_viz);
    
  }

}

/**TODO
                      Checando componente conexa

*/
