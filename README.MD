# WasteApp: recolha seletiva de lixo - Projeto Final CAL 2021

Aplicação para a gestão doméstica da recolha seletiva de resíduos.

## Modo de teste do programa:

- Após clicar run irá ser feito um loading do parser;
- Finalizado, aparecerá a janela do GraphViewer com um mapa do Porto e o seu grafo, sendo os nós dos
Users amarelos, dos CollectingPoints verdes, e dos nós normais azuis. Também aparecerá um Menu;
- Selecionar opção de "User log in";
- Escrever o User ID "2191" (um do ids dos users existentes);
- Selecionar a opção "Adicionar lixo";
- Escrever um "Garbage Type" por exemplo "plastico";
- Escrever um "Volume" por exemplo "300", dado que os containers têm capacidade de 500;
- Selecionar a opção "Levar lixo";
- Irá aparecer um loading do programa a realizar o Djisktra;
- Finalizado poderá ver-se um cout do ID do contentor com capacidade de receber lixo, o path dos IDs que
passa do grafo, e na janela do GraphViewer poderá observar-se perto do canto superior esquerdo do mapa
uma representação do caminho a percorrer com cor laranja;
- Para testar se o programa consegue encontrar um contentor disponível, assumindo que o anterior não
tenha capacidade de receber o lixo do User, basta repetir a mesma ação desde "Adicionar lixo", 
e irá encontrar um novo contentor mais próximo.
