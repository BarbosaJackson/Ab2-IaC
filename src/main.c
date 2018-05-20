#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

void cpu() { // função que testa o processador
	for(;;){ // loop infinito para o teste de processador
	}
}

void cpu_mem() { // função que testa a memória e o processador
	for(;;){ // loop infinito para o teste de processador
		malloc(sizeof(int)); // aloca um inteiro a cada loop para o teste de memória
	}
}
// função que verifica se duas strings são iguais
int string_equals(char *string1, char *string2) {
	return *string1 != *string2 ? 0 : (*string1 == '\0' && *string2 == '\0') ? 1 : string_equals(string1 + 1, string2 + 1);
}

int main(int argc, char *argv[], char *envp[]) {
	int pid = fork(); // identificador do processo
	int i = 0; // i -> conta os segundos de execução do processo filho dentro do processo pai para interromper aos 10 segundos
	// sys -> armazena o comando do sistema que mostra o pid, porcentagem da CPU e/ou a quantidade de bytes alocados
	// aux -> armazena o valor do pid do filho convertido para string 
	char sys[100], aux[100]; 
	if(pid < 0) { /* se o fork não funcionou */
		perror ("Erro: ") ;
		exit (-1) ; /* encerra o processo com código de erro -1 */ 		
	} else if(pid == 0){ // se sou o processo filho
		if(string_equals(argv[1], "ucp") == 1) { // se o paramêtro de argv[1] indicar que o programa deve testar apenas a cpu entra nesse if
			cpu(); // chama a função cpu() que tem um loop infinito para forçar o processador
		} else if(string_equals(argv[1], "ucp_mem") == 1) { // senão se o paramêtro indicar que o programar deve testar a cpu e a memória entra aqui
			cpu_mem(); // chama a função cpu_mem que tem um loop infinito para forçar o processador e, em cada loop, uma chamada a função malloc allocando a quantidade de bytes de um inteiro para forçar a memória
		}
	} else { // se sou o pai
		sprintf(aux, "%d", pid); // converte o pid do filho para string e passa esse valor pra variavel aux
		if(string_equals(argv[1], "ucp") == 1) { // se for só o teste de processador
			printf(" PID - CPU%%\n"); // printa na tela um header para melhor identificação visual dos valores
			strcpy(sys, "ps -e -o pid,pcpu | grep "); // salva na variável 'sys' o comando que traz a tela os valores do pid e a porcentagem de cpu usada por um processo com o 'grep' para filtrar a partir do pid
			strcat(sys, aux); // concatena a string sys o valor do pid a ser analisado
		} else if(string_equals(argv[1], "ucp_mem") == 1) { // se o teste for de processador e de memória
			printf(" PID - CPU%%\n"); // printa na tela um header para melhor identificação visual dos valores
			strcpy(sys, "ps -e -o pid,pcpu | grep ");// salva na variável 'sys' o comando que traz a tela os valores do pid e a porcentagem de cpu usada por um processo com o 'grep' para filtrar a partir do pid
			strcat(sys, aux);// concatena a string sys o valor do pid a ser analisado
			strcat(sys, ";pmap ");// concatena a ela tbm um ';' para indicar fim de comando e 'pmap' para identificar quantos Kb de memoria estão sendo usadas pelo processo
			strcat(sys, aux); // com o pid do processo o programa filtra qual processo deve ter a memoria monitorada
			strcat(sys, " | grep -i total"); // com o uso do grep aqui, mostra apenas o total de memória usada
		}
		while(i < 10) {// enquanto não se passarem 10 segundos, faça
			system(sys); // chama o sistema e executa o comando determinado pelos if-else-if acima e executa-o
			sleep(1); // espera um segundo
			i++;//incrementa o i para chegar a condição de parada em 10 seg.
		}
		strcpy(sys, "kill ");// envia para sys um novo valor para o comando 'kill'
		strcat(sys, aux); // com o pid do processo filho salvo em 'aux'
		system(sys); // executa o comando 'kill *pid*' matando o processo filho após 10 segundos de execução
	}
	
	perror ("Erro: ") ; /* execve nãoo funcionou */
	exit(0) ; /* encerra o processo com sucesso (código 0) */ 
	return 0;
}
