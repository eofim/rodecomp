# Afinidades no Alt+Q ? client 2026-02-19

Vers?o cumulativa: mant?m seis cartas e nove random options e adiciona seis posi??es de Afinidades abaixo do personagem, na aba de equipamento local do Alt+Q. Usa imagens nativas, sem exigir BMP novo. As posi??es bloqueadas exibem o fundo desabilitado com indica??o de bloqueio.

## Desbloqueio

O servidor Kafraverse-Server controla o registro permanente da conta `#MOREAFFINITIS`:

| Valor | Slots liberados |
| --- | ---: |
| 0 ou negativo | 3 |
| 1 | 4 |
| 2 | 5 |
| 3 ou maior | 6 |

A flag `KAFRAVERSE_AFFINITY_SLOTS6` j? estava habilitada no servidor consultado. As flags de cartas/op??es s?o uma configura??o separada e precisam corresponder ? vers?o cumulativa do client.

O client recebe a quantidade por `0141`, 14 bytes: identificador `AFFS` (`0x41464653`) no offset2, guarda `0xA6060001` no offset6 e quantidade no offset10. Outros pacotes `0141` continuam seguindo o processamento nativo. O estado come?a em tr?s ao trocar de personagem; mudan?as de mapa preservam a quantidade sincronizada.

As seis posi??es usam bits `0x00400000`, `0x00800000`, `0x01000000`, `0x02000000`, `0x04000000`, `0x08000000`. Equipar usa o pacote nativo `0998`; desequipar usa o fluxo nativo por ?ndice. O servidor continua validando posi??o, desbloqueio e duplicatas.

## Comportamento

- Arrastar uma Afinidade para uma posi??o liberada solicita aquela posi??o exata.
- Pedido de equipamento com m?scara de v?rias posi??es escolhe uma posi??o compat?vel, liberada e preferencialmente vazia.
- Posi??es bloqueadas n?o aceitam equipamento pelo painel.
- Duplo clique desequipa; arraste, tooltip e bot?o direito usam o item daquele slot.
- O bot?o de desequipar tudo inclui Afinidades.
- Itens equipados s?o mantidos separadamente do invent?rio e restaurados no invent?rio pelo ACK de desequipar.
- A lista inicial de equipamentos restaura as Afinidades ao entrar no jogo.
- Abas Visual/t?tulos/damage skin e visualiza??o de outro jogador n?o recebem o painel adicional.

## Build e valida??o

```powershell
python scripts/exe/build_exe.py --out build/affinities6
```

Compila??o completa: 982/982 unidades; link sem s?mbolos ausentes nem defini??es duplicadas. Execut?vel cumulativo em `build/affinities6/Ragexe.exe`; hash e resultado em `validation.json` no mesmo diret?rio.

Ainda requer teste no jogo: valores0/1/2/3 de `#MOREAFFINITIS`, atualiza??o com Alt+Q aberto, entrada com itens j? equipados, troca de personagem/mapa, equipar/desequipar cada posi??o, bloqueio ap?s reduzir a vari?vel, descri??o/tooltip/arraste, desequipar tudo, abas e painel de troca de equipamentos. A inspe??o visual e o funcionamento real com servidor n?o foram certificados pela compila??o.
