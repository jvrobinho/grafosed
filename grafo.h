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
