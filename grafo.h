typedef struct grafo{TG;
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
