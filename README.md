# Processamento Gráfico 

###Configurações on Visual Studio:
	#C/C++ -> Geral -> Diretórios de inclusão adicionais -> incluir:
		#../../dependencies/glm
		#../../dependencies/GLAD/include
		#../../dependencies/glfw-3.3.4.bin.WIN64/glfw-3.3.4.bin.WIN64/include
	#Vinculador -> Geral -> Diretórios de biblioteca adicionais -> incluir:
		#../../dependencies/glfw-3.3.4.bin.WIN64/glfw-3.3.4.bin.WIN64/lib-vc2019
	#Vinculador -> Entrada -> Dependências adicionais -> incluir:
		#opengl32.lib;
		#glfw3.lib;
		
###Lista 5:
	#9 imagens, ocupando exatamente toda a tela, com os filtros pedidos (o da vinheta tá ruim)
	
###Trabalho GB:
	#Digitar entre 1 e 4 para escolher uma das texturas de opção
	#Aberta a textura, ter-se-á as seguintes ações (AQUI É A PARTE IMPORTANTE)
		##Se aproximar com o mouse de um sticker e clicar ENTER, irá selecioná-lo;
		##Selecionado o sticker, ele seguirá o ponteiro do mouse;
		##Apertando ENTER novamente com um sticker selecionado, irá desselecioná-lo;
		##Clicar '1' irá dar toggle no filtro de habilitar somente o canal vermelho;
		##Clicar '2' irá dar toggle no filtro de habilitar somente o canal verde;
		##Clicar '3' irá dar toggle no filtro de habilitar somente o canal azul;
		##Clicar '4' irá dar toggle no filtro de grayScale;
		##Clicar '6' irá dar toggle no filtro de inversão;
		##Clicar '5' irá dar toggle no filtro de somar cor (tá somando um rosinha bubble gun);
		##Clicar '7' irá dar toggle no filtro de binarização;
		##Clicar '8' irá dar toggle no meu filtro, q transforma pixels bem escuros em brancos;
	##OBS.: Usei máscara de bits para somar os filtros, irei explicar no vídeo da apresentação.
