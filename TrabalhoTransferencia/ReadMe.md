Arquivo enviado e testado no ambiente virtual da aws.

Para compilar o arquivo foi utilizado o comando:
	gcc -g -Wall -o Trabalho trabalho.c -lpthreads

Para fazer esse codigo, utilizamos o codigo disponibilizado pelo professor para o trabalho e outro codigo, também disponibilizado pelo professor, para o Lab 3 de pthreads

Para executar o programa utilizamos o comando:
./Trabalho


OBS: A primeira versão do programa dava erro quando, por exemplo, a conta2 foi zerada e não existem mais transaçoes da conta 1 para a conta 2. Inicialmente nós tinhamos deixado o erro e notificavamos o usuário. Agora, para mitigar este problema, ao faltar dinheiro em uma conta ele gera uma transação da conta não zerada para a zerada. É possível observar quantas vezes isso foi necessário no print no final da execução.
