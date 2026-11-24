# Visual das Afinidades pelo Lua

A vers?o cumulativa mant?m seis cartas, nove op??es e o desbloqueio de Afinidades por `#MOREAFFINITIS`. A tabela Lua altera somente a apresenta??o do painel local de equipamentos.

## Instalar

Copie `client-data/LuaFiles514/Lua Files/DataInfo/AffinityVisual.lua` para o mesmo caminho virtual dentro dos dados/GRF do client: `LuaFiles514\Lua Files\DataInfo\AffinityVisual.lua` (normalmente sob `data`). O carregador procura `.lub` antes de `.lua`: remova ou atualize um `.lub` antigo quando editar o `.lua`.

O arquivo define `AffinityHUD`. Ele ? carregado depois de `HatEffect_F`; tamb?m ? poss?vel definir a tabela no `HatEffect_F` existente e omitir o novo arquivo. Se ambos definirem a tabela, o novo arquivo prevalece. O arquivo ? opcional. As configura??es s?o lidas ao criar a janela; reinicie o client para aplicar altera??es nos arquivos.

## Campos

| Campo | Padr?o | Uso |
| --- | --- | --- |
| `panel_height` | 36 | Altura adicional do Alt+Q e deslocamento do rodap? |
| `center` | true | Centraliza o conjunto de slots |
| `x`, `y` | 0, 149 | Origem; x ? deslocamento se centralizado, y ? relativo ao conte?do |
| `step_x`, `step_y` | 28, 0 | Deslocamento entre slots |
| `width`, `height` | 24, 24 | ?rea de clique por slot; n?o redimensiona imagens |
| `icon_x`, `icon_y` | 0, 0 | Recuo do ?cone do item dentro da posi??o |
| `draw_background` | true | Pinta a ?rea de fundo do painel |
| `background_x`, `background_y` | 1, 147 | Origem do fundo |
| `background_width` | 0 | 0 usa a largura interna da janela |
| `background_height` | 34 | Altura do fundo |
| `background_color` | 0xFFFFFF | Cor RGB |
| `panel_image` | vazio | Imagem opcional no fundo do painel |
| `slot_image` | imagem nativa | Fundo da posi??o liberada |
| `locked_image` | imagem nativa | Fundo da posi??o bloqueada |
| `lock_overlay` | ban.bmp nativo | Imagem sobreposta ao slot bloqueado |
| `highlight_image` | item_invert.bmp nativo | Destaque de destino compat?vel durante arraste |
| `slots` | tabela vazia | Overrides individuais de posi??o, ?ndices Lua1?6 |

Os caminhos das imagens s?o relativos ? raiz de texturas, como os caminhos nativos. String vazia desativa a imagem correspondente. Bitmaps s?o desenhados em tamanho natural: forne?a imagens do tamanho desejado. O exemplo usa escapes de bytes CP949 para os caminhos coreanos nativos, evitando depender da codifica??o do editor.

Desenho, clique, arraste, tooltip e descri??o compartilham as posi??es calculadas. Os espa?os entre as ?reas de clique n?o aceitam drop. A altura do painel deve comportar a configura??o; o client aplica limites e corrige a altura m?nima conforme as posi??es.

Exemplo com fundo pr?prio:

```lua
AffinityHUD.slot_image = "basic_interface\\affinity_slot.bmp"
AffinityHUD.locked_image = "basic_interface\\affinity_locked.bmp"
AffinityHUD.lock_overlay = ""
AffinityHUD.x = 0
AffinityHUD.step_x = 30
```

Posi??es individuais usam x absoluto na janela e y relativo ao topo do conte?do:

```lua
AffinityHUD.slots = {
    [1] = { x = 52, y = 149 },
    [2] = { x = 80, y = 149 },
    [3] = { x = 108, y = 149 },
    [4] = { x = 136, y = 149 },
    [5] = { x = 164, y = 149 },
    [6] = { x = 192, y = 149 },
}
```

Teste no jogo as imagens da sua distribui??o, clique/drop ap?s mover os slots, estados bloqueado/liberado e altern?ncia de abas. A compila??o n?o confirma a apar?ncia real do painel nem a disponibilidade dos seus BMPs.

## Instala??o e atualiza??o

Copie `client-data/LuaFiles514/Lua Files/DataInfo/AffinityVisual.lua` para `data/LuaFiles514/Lua Files/DataInfo/AffinityVisual.lua` na distribui??o do jogo, ou para esse caminho virtual dentro do GRF. O loader procura `.lub` antes de `.lua`; remova/atualize uma vers?o `.lub` antiga ao editar o `.lua`.

O arquivo define a tabela `AffinityHUD`. Como alternativa, a mesma tabela pode ser definida no `HatEffect_F.lua/.lub` j? carregado pelo client; o arquivo `AffinityVisual`, quando presente, ? carregado depois e prevalece. Aus?ncia do arquivo/tabela ou campos omitidos mant?m valores padr?o. Tipos incorretos s?o ignorados; n?meros finitos s?o limitados a intervalos v?lidos.

A configura??o ? lida ao criar a janela. Reinicie o client ap?s editar o Lua para garantir o recarregamento. Ela n?o altera os seis slots dispon?veis nem o desbloqueio de `#MOREAFFINITIS`.

A altura informada funciona como m?nimo: o client amplia o painel quando necess?rio para acomodar posi??es, ?cones e bitmaps. As posi??es individuais `slots[1]` a `slots[6]` substituem o c?lculo de linha; cada entrada aceita `x` e `y`.

Exemplo de duas linhas com tr?s slots:

```lua
AffinityHUD.panel_height = 66
AffinityHUD.slots = {
    {x = 100, y = 149}, {x = 128, y = 149}, {x = 156, y = 149},
    {x = 100, y = 177}, {x = 128, y = 177}, {x = 156, y = 177},
}
```

## Resultado local

Build cumulativo: `build/affinities6-visual/Ragexe.exe`, com seis cartas, nove op??es e seis Afinidades. Compila??o completa 982/982 e link sem erros. O exemplo foi executado com o Lua 5.1 do pr?prio projeto para verificar sintaxe e caminhos em CP949. N?o houve teste visual ou de integra??o dentro do jogo.
