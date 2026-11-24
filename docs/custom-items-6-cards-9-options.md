# Seis cartas e nove random options (client 2026-02-19)

Customiza??o local do fonte, incompat?vel com o protocolo padr?o de quatro cartas/cinco op??es. N?o enviar como reconstru??o equivalente do execut?vel original ao Clank.

## Contrato

Refer?ncia: `../Kafraverse-Server/src/common/mmo.hpp` e `src/map/packets_struct.hpp`, com `KAFRAVERSE_CARD_SLOTS6` e `KAFRAVERSE_RANDOM_OPTIONS9` habilitadas juntas. Essas flags estavam comentadas na configura??o do servidor durante a implementa??o; este trabalho n?o as ativa no servidor.

- Seis IDs de carta de 32 bits: 24 bytes.
- Nove op??es empacotadas (`int16 id`, `int16 value`, `uint8 parameter`): 45 bytes.
- Cada registro com cartas e op??es cresce 28 bytes no protocolo. O tamanho de objetos C++ depende tamb?m do alinhamento.
- IDs das op??es de dura??o de cartas tempor?rias permanecem os do servidor: 1101?1108 para slots 1?4 e 1121?1124 para slots 5?6. N?o h? um array adicional de vencimentos no pacote; o servidor transmite essas informa??es como op??es de apresenta??o.

| Pacote | Bytes |
| --- | ---: |
| 0B3F RODEX | 92 |
| 0B41 pegar item | 98 |
| 0B42 troca | 90 |
| 0B43 atualiza??o de op??es/cartas | 76 |
| 0B44 dep?sito | 86 |
| 0B45 carrinho | 86 |
| 0B40 venda | 8 + 86 ? itens |
| Lista de equipamentos atual | 5 + 96 ? itens |

A expans?o cobre os dados dos itens, c?pias, arraste, pacotes, nomes, painel e compara??o, links de chat, replay e backup da loja. Metadados de forja nos primeiros quatro campos mant?m o significado original. Replays/links gerados com a expans?o n?o s?o destinados ao client padr?o.

Os slots adicionais usam as imagens nativas existentes; n?o ? necess?rio fornecer `disable_card_slot2.bmp`. Os textos Lua das op??es, inclusive dura??o de cartas, precisam estar dispon?veis na distribui??o de dados do client. A quantidade de slots liberados do item continua sendo lida da tabela de itens.

## Valida??o no jogo

Com servidor recompilado com ambas as flags e migra??es SQL correspondentes, conferir: entrada no mapa com equipamento j? equipado; nove op??es e contagem no nome; cartas apenas nos slots 5/6; descri??o e compara??o; arraste/equipar; dep?sito e carrinho; troca; loja remota e refino; RODEX; link de chat; carta tempor?ria nos slots 5/6 antes e depois do vencimento; reconex?o. A compila??o n?o substitui esses testes nem certifica compatibilidade com prote??o de terceiros.

## Compilar

```powershell
python scripts/exe/build_exe.py --out build/options9-cards6
```

O diret?rio de sa?da ? separado de `build/exe`. Depend?ncias de execu??o e dados do jogo n?o acompanham o build.

## Resultado local

Compila??o MSVC v142: 982/982 unidades aprovadas; link sem s?mbolos ausentes e sem defini??es duplicadas. Execut?vel: `build/options9-cards6/Ragexe.exe` (11.068.928 bytes). Hash e resultado em `validation.json` no mesmo diret?rio. N?o foi testado em jogo.
