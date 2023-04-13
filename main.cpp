//Aluno: Enzo Rocha Portela		190027282
//Aluno: Gabriela de Sousa Peres	200037684

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <typeinfo>

using namespace std;

#define TRUE 1

void leitor(char ler[]){
	cout<<"$: ";
	cin.getline(ler, 50);
}

int main(int argc, char* argv[], char* envp[]){
	pid_t pid;
	
	while(TRUE){
		char cmd[50];
		leitor(cmd);
		
		int tamanho = strlen(cmd);
		
		char* token = strtok(cmd, " ");
		char* p[10];
		string arg;
		int x=0;
		
		while(token != NULL) {
        	p[x] = token;
        	token = strtok(NULL, " ");
        	x++;
    	}
    	
    	for(int i=1; i<x; i++){
        	arg+=p[i];
        	arg+=" ";
    	} 
    	
    	pid = fork();
		
		if(pid < 0){
			cout<<"Unable to fork\n";
			system("pause");
		}
		
		if(pid != 0){
			waitpid(-1, NULL, 0);
		}
		else{
		
			execve(cmd, NULL, envp);
			
			string palavra = cmd;
			palavra = "/bin/"+palavra;		//argumentos e comandos de /bin/
			execve(palavra.c_str(), p, envp);
			
			string t=arg;
			int t2 = arg.length();
			t[t2-1]='/';
			
			if(chdir(t.c_str())!=0){	//Logica do cd
				cout<<"ERROU\n";
			}
		}
		
		for(int i=0; i<x; i++){
			p[i] = NULL;
		}
	}
	
	return 0;
}
