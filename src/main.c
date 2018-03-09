/**
 * NOME: GUILHERME DE BRITO ABREU
 * RA: 173691
 * DISCIPLINA: EA876
 * 
 * OBJETIVO: Nesta tarefa, o programa recebera como entrada um texto contendo diversas palavras e numeros.
 * Devera retornar, na saida, a soma de todos os numeros encontrados.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

int fatorial(int x);/*Funcao que calcula recursivamente o fatorial de um numero*/
float add_numbers(char *);/*Funcao que soma os numeros encontrados na string passada como parametro*/
int char_converter(char *str, int beg, int last);/*Funcao que converte os caracteres de uma string em numeros*/

int main(){
    char str[50];
    float sum = 0.0;

    scanf("%[^\n]s", str);
    getchar();
    sum += add_numbers(str);
    
    printf("%.2f\n", sum);

    return 0;
}

int char_converter(char *str, int beg, int last){
    int i = last, num = 0;

    while (i >= beg){
        num += pow(10, last -i)*(str[i]- 48);
        i--;
    }

    return num;
}

int fatorial(int x){
    if (x < 2)
        return 1;
    else
        return x*fatorial(x-1);
}

int is_number(char c){
    if(c < 58 && c > 47)
        return 1;
    else
        return 0;
}

float add_numbers(char *str){
    int i = 0, ende = strlen(str);
    int beg;
    char last_char = ' ';
    float sum = 0.0, num, last_sum = 0.0;

    while(i < ende){
        if(is_number(str[i]) && last_char == ' '){
            /*Se encontrar um algarismo precedido de espaco, procurar o ultimo algarismo*/
            beg = i;
            while(i < ende && is_number(str[i]))
                i++;
            
            num = char_converter(str, beg, i-1);

            if(str[i] == '!'){
                num = fatorial((int)num);
                i++;
            }

            /*Caso ele seja potencialmente valido havera a soma*/
            if(i == ende || str[i] == ' ' || str[i] == '.'){
                sum += num;
                last_sum = num;
            }
        }
        else if(i != ende -1 && is_number(str[i+1]) && str[i] == '.' && last_char == ' '){
            /*Se encontrar um algarismo precedido de um ponto, procurar o ultimo algarismo*/
            int j = 0;
            beg = ++i;
            while(i < ende && is_number(str[i])){
                i++;
                j++;
            }
            num = (float)char_converter(str, beg, i-1);

            /*Transforma num na parte fracionaria do numero encontrado anteriormente*/
            while(j > 0){
                num /= 10;
                j--;
            }
            
            /*Caso ele seja valido havera a soma, caso contrário todo o numero em ponto flutuante sera descartado*/
            if(i == ende || str[i] == ' ')
                sum += num;
            else
                sum -= last_sum;
        }
        else{
            last_char = str[i];
            i++;
        }
    }
    
    return sum;
}