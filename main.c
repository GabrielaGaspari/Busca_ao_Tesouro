#include <stdio.h>
#include <stdlib.h>
#include <time.h> // para a randomização
#include <unistd.h> //para a função sleep

//para o clear funcionar tanto no linux quanto no windows
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

int main (){

    //variáveis
    int tabuleiro [11][11];
    int l, c, i;
    char movimento;
    int tesouro = 0;

    srand(time(NULL)); //inicia o gerador de números aleatórios

    //limpando o tabuleiro
    for(l = 0; l < 11; l++){
        for(c = 0; c < 11; c++){
            tabuleiro[l][c] = 0;
        }
    }

    //colocando as bombas e os tesouros de forma aleatoria

    for(i = 0; i < 3; i++)
        tabuleiro[rand()%11][rand()%11] = 2; //valor da bomba
    for(i = 0; i < 6; i++)
        tabuleiro[rand()%11][rand()%11] = 1; //valor do tesouro

    
    //definindo a posição inicial aleatoria
    int playerX = (rand()%11);
    int playerY = (rand()%11);
    tabuleiro[playerX][playerY] = 5;
   

    //sistema de "spoiler" do tabuleiro antes do game começar
    system(CLEAR);
    printf("Prepare-se! Memorize o mapa!\n");

    for(l = 0; l < 11; l++){
        for(c = 0; c < 11; c++){
            if(tabuleiro[l][c] == 5) printf(" P ");
            else if(tabuleiro[l][c] == 1) printf(" T ");
            else if(tabuleiro[l][c] == 2) printf(" B ");
            else printf(" . ");
        }
        printf("\n");
    }
    sleep(8); //sleep de 8 segundos para ver todos os elementos do game
    system(CLEAR);
    
    
    //loop da movimentação
    do{
        
        system(CLEAR); //limpa o terminal
        
        //imprime o tabuleiro
        printf("--- Busca ao tesouro (colete 5 tesouros) ---\n");
            for(l = 0; l < 11; l++){
                for(c = 0; c < 11; c++){
                    if (tabuleiro[l][c] == 5) printf(" P ");
                    else printf(" . ");
                }
                printf("\n");
            }
        
        //entada de dados
        printf("Tesouros: %d | (W,A,S,D) para mover | (Q) para desistir: \n", tesouro);
        scanf(" %c", &movimento);
        if(movimento == 'q' || movimento == 'Q') break;

        tabuleiro[playerX][playerY] = 0; //limpa a posição antiga do player

        //switch da movimentação com limite do tabuleiro
        switch(movimento){
            case 'w': case 'W': if(playerX > 0) playerX--; break;
            case 's': case 'S': if(playerX < 10) playerX++; break;
            case 'a': case 'A': if(playerY > 0) playerY--; break;
            case 'd': case 'D': if(playerY < 10) playerY++; break;
        }

        //verificação de colisão, 1 para tesouro e 2  para bomba
        if(tabuleiro[playerX][playerY] == 1){
            tesouro++;
            tabuleiro[playerX][playerY] = 0;
        }
        else if(tabuleiro[playerX][playerY] == 2){
            system(CLEAR);
            printf("BOOOMM!! Voce pisou em uma bomba | Fim de jogo!\n");
            break;
        }

        tabuleiro[playerX][playerY] = 5; //define a nova posição do player 

        system(CLEAR);
    } while(tesouro < 5); //while achar tesouros suficientes


    if(tesouro == 5) printf("Voce Venceu! Coletou 5 tesouros!\n");

    printf("Obrigada por jogar!\n");
    printf("Pressione Enter para sair...");
    
    getchar(); getchar(); // O primeiro getchar() captura o Enter da pergunta anterior, o segundo espera o usuário apertar Enter

    return 0;
}