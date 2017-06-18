typedef struct grafo TG;
typedef struct no TNO;
typedef struct viz TViz;

void imprime (TG * g );
TNO * buscaNo(TG * g, int elem);
void removeNO(TG * g, int elem);
TViz * buscaAresta(TG *g, int no1, int no2);
void checaOrientação(TG * g);
int conexo (TG * g);
void pintaSub(TG *g);
int verificaPonte(TG * g, int id1, int id2);
void achaPontes(TG * g);

typedef struct grafo{
  TNO * prim;
  int numCores = 1;
}TG;

typedef struct no{
  int id_no;
  int cor = 0;
  TViz * prim_viz;
  struc no * prox_no;
}TNO;

typedef struct viz{
  int id_viz;
  int custo;
  int passou = 0;
  struct viz * prox_viz;
}TViz;

TG * inicializa(void){
  return NULL;
}
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
    if(!g) return;
    TNO * aux = buscaNo(g,elem);
    if(aux) return;

    TNO * no = (TNO*)malloc(sizeof(TNO));
    no->id_no = elem;
    no->cor = 0;
    no->prox_no = NULL;
    no->prim_viz = NULL;
    if(!g->prim){
      g->prim = no;
      return;
    }

    while(aux->prox_no){
        aux = aux->prox_no;
    }
    aux->prox_no = no;

    return;
}
TNO * buscaNo(TG * g, int elem){
    TNO * no = g->prim;
    while(no){
        if(elem== no->id_no){
            return no;
        }
        no = no->prox_no;
    }
    return NULL;
}
void removeNo(TG * g, int elem){
    TNO * no = buscaNo(g, elem);
    if(!no)
        return;
    }
    while(no->prim_viz){
        TNO * viz = no->prim_viz;
        no->prim_viz = viz->prox_viz;
        free(viz);
    }
    if(g->prim->id_no == elem) g->prim = no->prox_no;
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
    if(!g) return NULL;
    TNO * no1 = buscaNo(g,no1);
    if(!no1) return NULL;
    TNO * no2 = buscaNo(g,no2);
    if(!no2) return NULL;

    TViz * p = no1->prim_viz;
    while(p && (p->id_viz != no2))
      p=p->prox_viz;
    return p;
}
void insereAresta(TG * g, int no1, int no2, int custo){
    TNO * n1 = buscaNo(g,no1);
    if(!no1) return;
    TNO * n2 = buscaNo(g,no2);
    if(!no2) return;
    TViz * aresta = buscaAresta(g,no1,no2);
    if(aresta){
      aresta->custo = custo;
      return;
    }
    TViz * viz = n1->prim_viz;
    while(viz->prox_viz){
      viz= viz->prox_viz;
    }
    viz->prox_viz = (TViz*) malloc (sizeof(TViz));
    viz = viz->prox_viz;
    viz->custo = custo;
    viz->id_viz = no2->id_no;
    viz->passou = 0;
    }
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

void imprime (TG* g){
    TNO * p = g-> prim;
    while(p){
        printf("%d \n", p->id_no);
        TViz * v = p->prim_viz;
        while(v){
        printf("viz: %d \t custo %d",v->id_viz, v->custo);
        v=v->prox_viz;
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
