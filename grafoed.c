typedef struct grafo{
  TNO * prim;
}TG;

typedef struct no{
  int id;
  TViz * prim_viz;
  struc no * prox_no;
}TNO;

typedef struct viz{
  int id_viz;
  int custo;
  struct viz * prox_viz;
}TViz;

TNO * buscaNo(TG * g, int elem){};
/**            PERGUNTAS PRA FAZER PRA TIA BEBEL <3
+Perguntar se grafos com somente um no devem ser tratados
+Perguntar se podem existir nos com valores repetidos em um grafo
+Perguntar se eu posso usar estruturas auxiliares para guardar pontes
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
      Logo, se existe um no para qual essa sentenca e falsa, o grafo e orientado.

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

      while((vizinhoBusca->id_viz != p->id)&&(vizinnhosBusca)){
        vizinhosBusca = vizinhosBusca->prox_viz;
      }
      if(!vizinhosBusca) return 1;
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
    resp = procuraCaminho(g,v->id_viz,id2);
    v=v->prox_viz;
  }
  return resp;
}

/**TODO
                        Checando conectividade

Para todos os nos do grafo
    vejo se ele alcanca outros nos(procuraCaminho)
        se ele alcanca, pinta da mesma cor
        se nao alcanca, pinta da proxima cor


No pior caso, o numero de cores sera o numero de nos informado no arquivo(ou seja,
grafo totalmente desconexo).
No melhor caso, o numero de cores sera igual a 1(ou seja, grafo totalmente conexo)
*/


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
