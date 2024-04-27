#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NOME 100
#define MAX_GENERO 200
#define MAX_LOCAL 800
#define MAX_ALBUMS 800
#define MAX_LINHA 500

typedef struct {
    char nome[MAX_NOME];
    char genero[MAX_GENERO];
    char local[MAX_LOCAL];
    char albums[MAX_ALBUMS];
} Artista;

typedef struct {
    Artista *artistas;
    int numElementos;
} ListaArtistas;

void iniciarLista(ListaArtistas *lista) {
    lista->artistas = NULL;
    lista->numElementos = 0;
}

void adicionarArtista(ListaArtistas *lista, const Artista *artista) {
    lista->numElementos++;
    lista->artistas = (Artista *)realloc(lista->artistas, lista->numElementos * sizeof(Artista));
    if (lista->artistas == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    lista->artistas[lista->numElementos - 1] = *artista;
}

void imprimirLista(ListaArtistas *lista) {
    for (int i = 0; i < lista->numElementos; i++) {
        printf("Nome: %s\n", lista->artistas[i].nome);
        printf("Gênero: %s\n", lista->artistas[i].genero);
        printf("Local: %s\n", lista->artistas[i].local);
        printf("Álbuns:\n%s\n", lista->artistas[i].albums);
        printf("==================\n");
    }
}

void limparLista(ListaArtistas *lista) {
    free(lista->artistas);
    lista->artistas = NULL;
    lista->numElementos = 0;
}

int main() {
    printf("Álbuns Musicais:\n");

    ListaArtistas lista;
    iniciarLista(&lista);

    FILE *arquivo = fopen("artistas.txt", "r");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        exit(1);
    }

    char linha[MAX_LINHA];
    Artista artista;
    int contador = 0;

    while (fgets(linha, MAX_LINHA, arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        if (strcmp(linha, "==========") == 0) {
            if (contador >= 4) {
                adicionarArtista(&lista, &artista);
            }
            contador = 0;
        } else {
            switch (contador) {
                case 0: strcpy(artista.nome, linha); break;
                case 1: strcpy(artista.genero, linha); break;
                case 2: strcpy(artista.local, linha); break;
                case 3: strcpy(artista.albums, linha); break;
                default: strcat(artista.albums, "\n"); strcat(artista.albums, linha); break;
            }
            contador++;
        }
    }
    fclose(arquivo);

    printf("---- Informações dos Artistas ----\n");
    imprimirLista(&lista);

    limparLista(&lista);

    return 0;
}