# Trabalho GA - 3D Viewer.
### Aluno: Hedo Eccker da Silva Júnior

Utilizei como base o projeto Hello3D - Phong, portanto o nome do projeto ficou o mesmo (pra evitar erros que não teria tempo de consertar).

Ao iniciar o programa, é solicitado que se insira o caminho de arquivos .obj para leitura. Podem ser inseridos quantos forem necessários. Ao fim da inserção, é necessário apertar Enter. Considerando o caminho relativo do projeto, o caminho que normalmente utilizei nos testes era algo desse tipo:
`../../3D_Models/Pokemon/Pikachu.obj`

Teclas de utilização:
- TAB: alterna a seleção entre os objetos carregados;
- W, A, S, D: Controlam a câmera, junto ao movimento do mouse;
- X, Y, Z: Iniciam a rotação do objeto selecionado no eixo correspondente;
- 1: Diminui a escala do objeto selecionado;
- 2: Aumenta a escala do objeto selecionado;
- Setas direcionais: Movimentam o objeto selecionado nos eixos X e Y.

# Trabalho GB - 3D Viewer Incrementado.
### Aluno: Hedo Eccker da Silva Júnior

Utilizei como base o projeto Hello3D - Texturas, portanto o nome do projeto ficou o mesmo (pra evitar erros que não teria tempo de consertar).

Ao iniciar o programa, é solicitado que se insira o caminho de um arquivo .xml para leitura. Exemplo:
```
<SceneConfig>
    <Scene>
        <LightPos x="-2.0" y="10.0" z="3.0" />
        <LightColor r="1.0" g="1.0" b="1.0" />
        <CameraPos x="0.0" y="0.0" z="3.0" />
        <CameraFront x="0.0" y="0.0" z="-1.0" />
        <CameraUp x="0.0" y="1.0" z="0.0" />
    </Scene>
    <Objects>
        <Object>
            <ObjFile>../../3D_models/Pokemon/Pikachu.obj</ObjFile>
            <TextureFiles>
                <TextureFile>../../3D_models/Pokemon/textures/PikachuMouthDh.png</TextureFile>
                <TextureFile>../../3D_models/Pokemon/textures/PikachuDh.png</TextureFile>
                <TextureFile>../../3D_models/Pokemon/textures/PikachuHohoDh.png</TextureFile>
                <TextureFile>../../3D_models/Pokemon/textures/PikachuEyeDh.png</TextureFile>
                <TextureFile>../../3D_models/Pokemon/textures/PikachuDh.png</TextureFile>
            </TextureFiles>
            <InitialRotation x="45.0" y="90.0" z="0.0" />
            <InitialTranslation x="6.0" y="0.0" z="0.0" />
            <InitialScale x="1.0" y="1.0" z="1.0" />
            <Reflection ka="0.3" kd="0.5" ks="0.6" q="10.0" />
        </Object>
		<Object>
            <ObjFile>../../3D_models/Pokemon/Pikachu.obj</ObjFile>
            <TextureFiles>
                <TextureFile>../../3D_models/Pokemon/textures/PikachuMouthDh.png</TextureFile>
                <TextureFile>../../3D_models/Pokemon/textures/PikachuDh.png</TextureFile>
                <TextureFile>../../3D_models/Pokemon/textures/PikachuHohoDh.png</TextureFile>
                <TextureFile>../../3D_models/Pokemon/textures/PikachuEyeDh.png</TextureFile>
                <TextureFile>../../3D_models/Pokemon/textures/PikachuDh.png</TextureFile>
            </TextureFiles>
            <InitialRotation x="45.0" y="90.0" z="0.0" />
            <InitialTranslation x="0.0" y="0.0" z="0.0" />
            <InitialScale x="1.4" y="1.4" z="1.4" />
            <Reflection ka="0.7" kd="0.6" ks="0.5" q="10.0" />
        </Object>
    </Objects>
</SceneConfig>

```

Teclas de utilização:
- TAB: alterna a seleção entre os objetos carregados (indicado pelo aumento da luminosidade no objeto);
- W, A, S, D: Controlam a câmera, junto ao movimento do mouse;
- X, Y, Z: Iniciam a rotação do objeto selecionado no eixo correspondente;
- 1: Diminui a escala do objeto selecionado;
- 2: Aumenta a escala do objeto selecionado;
- Setas direcionais: Movimentam o objeto selecionado nos eixos X e Y.

OBS: Não consegui implementar a leitura de arquivo .mtl, por isso botei propriedades de material no XML e a possibilidade de passar arquivos de textura, similar ao exemplo dado pela própria professora.
