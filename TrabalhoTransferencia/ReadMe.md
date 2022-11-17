Arquivo enviado e testado no ambiente virtual da aws.

Para compilar o arquivo foi utilizado o comando:
	gcc -g -Wall -o projeto projeto_so.c -lpthreads

Para fazer esse codigo, utilizamos o codigo disponibilizado pelo professor para o trabalho e outro codigo, também disponibilizado pelo professor, para o Lab 3 de pthreads

Para executar o programa utilizamos o comando:
./projeto


OBS: A primeira versão do programa dava erro quando, por exemplo, a conta2 foi zerada e não existem mais transaçoes da conta1 para a conta2, mas existem transações aguardando ter dinheiro o suficiente na conta2 para finalizar, assim nunca finalizando. Inicialmente nós tinhamos deixado o erro e notificavamos o usuário. Agora, para mitigar este problema, ao faltar dinheiro em uma conta, e não existirem mais transações da outra, é gerado uma transação para a conta que precisa de dinheiro. É possível observar quantas vezes isso aconteceu no print no final da execução.
