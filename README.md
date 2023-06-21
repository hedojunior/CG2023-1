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
		<CameraSpeed>0.15</CameraSpeed>
		<Specular>10.0</Specular>
    </Scene>
    <Objects>
        <Object>
            <ObjFile>C:\Users\eccke\CG202301\Trabalhos\3D_Models\Cube\Cube.obj</ObjFile>
            <InitialRotation x="45.0" y="45.0" z="0.0" />
            <InitialTranslation x="0.0" y="0.0" z="0.0" />
            <InitialScale x="1.0" y="1.0" z="1.0" />
        </Object>
        <Object>
            <ObjFile>C:\Users\eccke\CG202301\Trabalhos\3D_Models\Pokemon\Pikachu.obj</ObjFile>
            <InitialRotation x="90.0" y="45.0" z="0.0" />
            <InitialTranslation x="5.0" y="0.0" z="0.0" />
            <InitialScale x="1.0" y="1.0" z="1.0" />
        </Object>
    </Objects>
</SceneConfig>
```

Teclas de utilização:
- TAB: alterna a seleção entre os objetos carregados (indicado pelo aumento/diminuição da escala do objeto);
- W, A, S, D: Controlam a câmera, junto ao movimento do mouse;
- X, Y, Z: Rocationam o objeto selecionado no eixo correspondente;
- 1: Diminui a escala do objeto selecionado;
- 2: Aumenta a escala do objeto selecionado;
- Setas direcionais: Movimentam o objeto selecionado nos eixos X e Y.

OBS: Não foi implementada a animação em curva.
