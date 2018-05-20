# Instalação

Para a instalação do monitor de processos inicialmente deve-se abrir o terminal, para isto use o buscador ou o atalho *CONTROL + ALT + T*, feito isso, vá a pasta onde gostaria de clonar o repositório utilizando o comando cd(_change disk_) caminho, veja um exemplo:

```bash
$ cd Desktop/
```

Agora que estamos no local onde gostariamos de clonar o repositório podemos de fato clona-lo, para isso, faremos uso do comando a seguir:

```bash
$ git clone https://github.com/BarbosaJackson/Monitor_de_processo.git
```

Quando o projeto for clonado, utilize o seguinte comando:

```bash
cd Monitor_de_processo/
```

# Compilação

Agora estamos com o projeto na máquina só falta compilar e executar, para a compilação será usado o compilador *gcc*, mas antes, já dentro da pasta do projeto (*Monitor_de_processo*), vamos para a pasta onde se encontra o arquivo à ser compilado, para isso, execute o seguinte comando:

```bash
cd src/
```

Agora estamos na pasta com o arquivo que vai ser compilado o *main.c*, para compila-lo execute o comando a seguir
```bash
gcc -o bin main.c
```

# Execução

Agora que já temos o arquivo binário que será executado temos de optar pelo programa que executa os teste com o processador, ou com o processador e a memória, para isso opte entre os comando de execução abaixo:

  - Para o teste com o processador apenas execute o programa com o seguinte comando
  ```bash
$ ./bin ucp
  ```
  - Para o teste com o processador e a memória execute o programa com o seguinte comando
  ```bash
$ ./bin ucp_mem
  ```