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


void visitado(TG * g, int elem){
  if(!g) return;
  TNO * no = g->prim;
  while(no){
    TViz * ar = no->prim_viz;
    while(ar){
      if (elem == ar->id_viz) {
        ar->passou = 1;
      }
      ar = ar->prox_viz;
    }
    no = no->prox_no;
  }
}


void col (TG *g,int elem,int cor){
    if (!g) return;
    TNO * no = buscaNo(g,elem);
    while(no){
      if (no->cor != cor && no->cor !=-1){
        no->cor = cor;
        //visitado(g,no->id_no);
        TViz * v = no->prim_viz;
        while(v){
          col(g,v->id_viz,cor);
          v = v->prox_viz;
        }
      }/* condition */
      no = no->prox_no;
    }
}

void limpaCor(TG*g){
  if (!g) return;
  TNO * no = g->prim;
  while(no){
    no->cor = 0;
    no = no->prox_no;
  }
}

TG * copiar (TG *g){
    if (!g) return NULL;
    TG * novo = inicializa();
    TNO * no = g->prim;
    while(no){
      insereNo(novo,no->id_no);
      no = no->prox_no;
    }
    no = g->prim;
    while(no){
      TViz *viz = no->prim_viz;
      while(viz){
        insereAresta(novo,no->id_no,viz->id_viz,0);
        viz = viz->prox_viz;
      }
      no = no->prox_no;
    }
    return novo;
}
int checaOrientacao(TG * g){
  if(!g) return 0;
  TNO * p = g->prim;

  while(p){
    TViz * v = p->prim_viz;
    while(v){
      TNO * vizinho = buscaNo(g,v->id_viz);
      TViz * vizinhosBusca = vizinho->prim_viz;
      while((vizinhosBusca)&&(vizinhosBusca->id_viz != p->id_no)){
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
    }
      v->passou = 0;
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
    if(viz->cor!=cor){
			viz->cor = cor;
			pintaSub(g,a->id_viz);
		}	
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
    if(procuraCaminho(g,no1->id_no,no2->id_no) && (no2->cor)) return no2->cor;
    no2=no2->prox_no;
  }
  return 0;
}

int conexo(TG * g){
  if(!g) return 0;
  TNO * p = g->prim;
  if(!p->prox_no){p->cor = g->numCores; return 1;}
  int cor;
  if(p->cor) cor = p->cor;
  else cor = g->numCores;
  p->cor = cor;
  int resp = 1;
  TNO * q = g->prim;
	int corAnt;
  while(q){
    if(q->id_no!=p->id_no){
      if(procuraCaminho(g,p->id_no,q->id_no)){
        if((q->cor)&&(q->cor!=cor)&&(q->cor!=corAnt)){
          g->numCores--;
					corAnt = q->cor;
        }
        q->cor = cor;
			}


        else{
          if(!q->cor){
            int pintar = verificaCor(g,q->id_no);
            if(!pintar){
              g->numCores++;
              cor=g->numCores;
              q->cor = cor;
							pintaSub(g,q->id_no);
            }
          }
					else if (q->cor){
						int pintar = verificaCor(g,q->id_no);
						if(!pintar){
						cor++;
						g->numCores = cor;
						q->cor = cor;
						pintaSub(g,q->id_no);
						}
					}
          resp = 0;
        }
      }
      q=q->prox_no;
    }
    return resp;
  }


void imprimeConexo(TG * g){
  int total = g->numCores;
  int i = 1;
  printf("Total de componentes conexas: %d\n",g->numCores);
  while(i<total+1){
    TNO * p = g->prim;
    while(p){
      if(p->cor == i) printf("Componente %d: %d\n", i, p->id_no);
      p=p->prox_no;
    }
    i++;
  }
}

int verificaPonto(TG *g, int elem){
  if (!g) return 0;
	if(!g->prim->prox_no) return 0;
  TG * cop = copiar(g);
  limpaCor(cop);
  removeNo(cop,elem);
  conexo(cop);
  int cores = g->numCores;
	int cores2 = cop->numCores;
	free(cop);
  if(cores < cores2)return 1;
  return 0;
}

void pontoDeArticulacao(TG * g){
  if(!g) return;
  TNO * no = g->prim;

  while(no){
    int id = no->id_no;
    int art = verificaPonto(g, no->id_no);
    if(art) printf("O no %d e ponto de articulacao\n",id);
    no=no->prox_no;
  }
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
    TNO * noAux = buscaNo(g,v->id_viz);
    int primAresta = v->id_viz;
    int aux;
    do{
      aux = v->id_viz;
      removeAresta(g,p->id_no,aux);
	  removeAresta(g,aux,p->id_no);
      int caminho = procuraCaminho(g,p->id_no,aux);
      if(!caminho && ((!p->ponte)||(!noAux->ponte))){
        printf("%d faz ponte com %d\n",p->id_no,aux);
        p->ponte =1;
        noAux->ponte = 1;
      }
      insereAresta(g,p->id_no,aux,0);
	  insereAresta(g,aux,p->id_no,0);
    }while(aux!=primAresta);
    p=p->prox_no;

  }
  p = g->prim;
  while(p){ p->ponte = 0; p=p->prox_no;}
}

/**TODO
                      Checando componente fortemente conexa

*/
/*Vou alterar um pouco a logica

Se elas forem fortemente conexas, eu so pinto elas da mesma cor,
ai eu crio uma função imprime que imprime todos os nos que tiverem a mesma cor.

*/

void pintaSubForte(TG * g,int id_no){
  if(!g) return;
  int cor = g->numCores;
  TNO * no1 = buscaNo(g, id_no);
  if(!no1) return;
  if(!no1->cor) no1->cor = cor;
  TViz * a = no1->prim_viz;
	while(a){
    TNO * viz = buscaNo(g,a->id_viz);
		if(procuraCaminho(g,no1->id_no,viz->id_no) && procuraCaminho(g,viz->id_no,no1->id_no) )
			if(viz->cor!=cor){
				viz->cor = cor;
				pintaSubForte(g,a->id_viz);
			}
    a=a->prox_viz;
  }
  return;
}

int verificaCorForte(TG * g,int id){
  if(!g) return 0;

  TNO * no1 = buscaNo(g, id);
  if(!no1) return 0;

  TNO * no2 = g->prim;
  while(no2){
    if((procuraCaminho(g,no1->id_no,no2->id_no) && procuraCaminho(g,no2->id_no,no1->id_no))) return no2->cor;
    no2=no2->prox_no;
  }
  return 0;
}

void fortementeConexa(TG * g){
	if(!g) return;
	TNO * no1 = g->prim;
	if(!no1->prox_no){no1->cor = g->numCores; return;}
  int cor;
  if(no1->cor) cor = no1->cor;
  else cor = g->numCores;
	no1->cor = cor;
	int corAnt;
 
    TNO * no2 = g->prim;	
      while(no2){
				if(no1->id_no != no2->id_no){ 
        int vTow = procuraCaminho(g, no1->id_no, no2->id_no);
        int wTov = procuraCaminho(g, no2->id_no, no1->id_no);
				if(vTow && wTov){
						if(no2->cor && (no2->cor != no1->cor)&&no2->cor!=corAnt){
							g->numCores--;
							corAnt=no2->cor;
						}
						no2->cor = no1->cor;
				}
				else{
					
					if(!no2->cor){
						int pintar = verificaCorForte(g,no2->id_no);
						if(!pintar){
							g->numCores++;
							cor=g->numCores;
							no2->cor = cor;
							pintaSubForte(g,no2->id_no);
						}	
					}
					
					else if(no2->cor){
						int pintar = verificaCorForte(g,no2->id_no);
						if(!pintar){
							cor++;
							g->numCores=cor;
							no2->cor = cor;
							pintaSubForte(g,no2->id_no);
						}	
					}	
				}
				}
				no2 = no2->prox_no;
			}

}	
		
	



void imprimeForte(TG *g){
  if(!g) return;
  int total = g->numCores;
  int i = 0;
  while(i<total+1){
    TNO * p = g->prim;
    while(p){
      if(p->cor == i) printf("Componente fortemente conexa %d: %d\n", i, p->id_no);
      p=p->prox_no;
    }
    i++;
  }
}


void imprimeArticulacao(TG * g){
  if(!g) return;
  TNO * p = g->prim;
  while(p){
    if(verificaPonto(g,p->id_no)) printf("%d e ponto de articulacao\n", p->id_no);
    p=p->prox_no;
  }
}

TG * criaGrafo(char * nomeArq){
    FILE * fp;
    fp = fopen(nomeArq,"rt");
		if(!fp) exit(1);
    int numNos,no1,no2,n=0,read;
    fscanf(fp,"%d",&numNos);
    TG* g = inicializa();
		while(n<numNos){
      insereNo(g,n+1);
      n++;
    }
    read = fscanf(fp,"%d %d",&no1,&no2);

	  while(read!=EOF){
      insereAresta(g,no1,no2,0);
      read = fscanf(fp,"%d %d",&no1,&no2);
    }

    fclose(fp);
    return g;
}

int main(int argc, char*argv[]){
	TG * g = NULL;
  g = criaGrafo(argv[1]);
  printf("Grafo criado!\n");
  imprime(g);
  int or = checaOrientacao(g);
  int opcao;
  while(opcao!=-1){
		if(!g->prim) printf("SEU GRAFO ESTA VAZIO!! POR FAVOR, SELECIONE A OPCAO 1  E INSIRA UM NOVO NO!\n");
		printf("\nDIGITE O NUMERO DA ACAO DESEJADA:\n 1.Adicionar um no.\n 2.Adicionar uma aresta/Alterar custo.\n 3.Ver informacao de um no ou aresta.\n 4.Imprimir o grafo.\n 5.Imprimir componentes conexas.\n 6.Imprimir pontes.\n 7.Imprimir pontos de articulacao.\n 8.Imprimir componentes fortemente conexas.\n 9.Remover um no.\n 10.Remover uma aresta\n -1. Sair\n");
		scanf("%d",&opcao);
    if(opcao == 1){
      printf("Digite o numero do no: ");
      int addNo;
      scanf(" %d", &addNo);
      insereNo(g,addNo);
      or = checaOrientacao(g);
    }
    else if(opcao == 2){
			if(!g->prim) printf("SEU GRAFO ESTA VAZIO!! POR FAVOR, SELECIONE A OPCAO 1  E INSIRA UM NOVO NO!\n");
			else{
      int origem, destino,custo;
      printf("\nDigite o no origem: ");
      scanf(" %d", &origem);
      printf("\nDigite o no destino: ");
      scanf(" %d", &destino);
      printf("\nDigite o custo(caso nao haja, digite 0): ");
      scanf(" %d",&custo);
      insereAresta(g,origem,destino,custo);
      or = checaOrientacao(g);
			}
    }
    else if(opcao == 3){
			if(!g->prim) printf("SEU GRAFO ESTA VAZIO!! POR FAVOR, SELECIONE A OPCAO 1  E INSIRA UM NOVO NO!\n");
			else{
			int opt;
			printf("Digite 1 para ver o no ou digite 2 para ver a aresta: ");
			scanf(" %d", &opt);
			if(opt == 1){
				printf("\nDigite o no desejado: ");
				int infoNo;
				scanf(" %d", &infoNo);
				imprimeNo(g,infoNo);
			}
			else if(opt == 2){
				printf("\nDigite os nos desejados: ");
				int no1, no2;
				scanf("%d%d", &no1, &no2);
				imprimeAresta(g,no1,no2);
			}
			}
    }
    else if(opcao == 4){
			if(!g->prim) printf("SEU GRAFO ESTA VAZIO!! POR FAVOR, SELECIONE A OPCAO 1  E INSIRA UM NOVO NO!\n");
			else{
			imprime(g);
			or = checaOrientacao(g);
      if(!or) printf("GRAFO NAO-ORIENTADO\n");
      else printf("GRAFO ORIENTADO\n");
			}
    }
    else if(opcao == 5){
			if(!g->prim) printf("SEU GRAFO ESTA VAZIO!! POR FAVOR, SELECIONE A OPCAO 1  E INSIRA UM NOVO NO!\n");
			else{
			or = checaOrientacao(g);
			if(!or){
				int cox = conexo(g);
				if(!cox) printf("\nGRAFO NAO CONEXO\n");
				else printf("\nGRAFO CONEXO\n");
				imprimeConexo(g);
			}
			else printf("ESSA OPERACAO SO E VALIDA PARA GRAFOS NAO ORIENTADOS!!");
			}
		}
    else if(opcao == 6){
			if(!g->prim) printf("SEU GRAFO ESTA VAZIO!! POR FAVOR, SELECIONE A OPCAO 1  E INSIRA UM NOVO NO!\n");
			else{
      or = checaOrientacao(g);
			if(!or) achaPontes(g);
      else printf("ESSA OPERACAO SO E VALIDA PARA GRAFOS NAO ORIENTADOS!!");
			}
    }
    else if(opcao == 7){
		if(!g->prim) printf("SEU GRAFO ESTA VAZIO!! POR FAVOR, SELECIONE A OPCAO 1  E INSIRA UM NOVO NO!\n");
		else{	
    or = checaOrientacao(g);
		if(!or) pontoDeArticulacao(g);
	  else printf("ESSA OPERACAO SO E VALIDA PARA GRAFOS NAO ORIENTADOS!!");
		}
		}
    else if(opcao == 8){
			if(!g->prim) printf("SEU GRAFO ESTA VAZIO!! POR FAVOR, SELECIONE A OPCAO 1  E INSIRA UM NOVO NO!\n");
			else{
			or = checaOrientacao(g);
			if(or){
				fortementeConexa(g);
				imprimeForte(g);
			}
			
			else printf("ESSA OPERACAO SO E VALIDA PARA GRAFOS ORIENTADOS!!");
		}
		}
    else if(opcao == 9){
			if(!g->prim) printf("SEU GRAFO ESTA VAZIO!! POR FAVOR, SELECIONE A OPCAO 1  E INSIRA UM NOVO NO!\n");
			else{
      int delNo;
      printf("\nDigite o no a ser removido: ");
      scanf(" %d", &delNo);
			if(!g->prim->prox_no)
				removeNo(g,delNo);
			else{
				removeNo(g,delNo);
				or = checaOrientacao(g);
			}
			}
    }
    else if(opcao == 10){
			if(!g->prim) printf("SEU GRAFO ESTA VAZIO!! POR FAVOR, SELECIONE A OPCAO 1  E INSIRA UM NOVO NO!\n");
			else{
      int delArestaOrg, delArestaDest;
      printf("\nDigite o no origem: ");
      scanf(" %d", &delArestaOrg);
      printf("\nDigite o destino: ");
      scanf(" %d", &delArestaDest);
      removeAresta(g,delArestaOrg,delArestaDest);
      or = checaOrientacao(g);
			}
		}	
    else if(opcao == -1){exit(1);}
    else{
			printf("Voce digitou um numero invalido! Tente novamente.\n");
		}

    printf("\n");
  }
  return 0;
}
