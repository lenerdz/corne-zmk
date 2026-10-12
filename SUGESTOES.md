# Sugestões de melhorias — Corne ZMK

Prioridade alta — o que mais “dói” no dia a dia:

## 1. Acesso a NAV / SYS / MEDIA

Hoje exige FN1 + outra tecla (`&mo`). Para setas isso é ruim.

Melhor:

- `&mo 3` (NAV) num polegar, ou
- **tri-layer** (segurar os dois polegares → SYS)

NAV merece um atalho direto.

## 2. Home row mods

Ctrl/Shift só nas bordas desperdiça espaço. Vale testar tap-hold em `A`/`S`/`D`/`F` e `J`/`K`/`L`/`;` (Gui/Alt/Ctrl/Shift).

É a mudança que mais acelera Corne, mas precisa calibrar `tapping-term-ms`.

## 3. `/` e `?` na base

Sairam da QWERTY; `/` ficou no RAISE. Se digita muito path/URL, traga `&kp FSLH` de volta (ex.: no lugar de `RBKT`, ou num polegar com layer-tap).

## 4. Esc mais fácil

Só no RAISE. Opções comuns:

- `Tab` como `&lt 2 ESC` / `&mt LCTRL ESC`, ou
- Esc no canto superior esquerdo da base

## 5. Delete

Só na NAV. Muitos usam `&mt LCTRL BSPC` ou Delete no FN1 ao lado do Backspace.

---

## Melhorias boas, mas secundárias

- **Combos**: `JK` → Esc, `DF` → Tab, etc., sem gastar tecla.
- **`&sk` (sticky shift)**: Shift “gruda” um toque — ótimo em teclado pequeno.
- **Soft off / deep sleep**: `CONFIG_ZMK_SLEEP=n` está desligado; com bateria, vale ligar sleep + tecla Soft Off na SYS.
- **RGB na SYS ok**, mas volume/mute na MEDIA somem no fundo; mute no FN1 ou num combo é mais útil.
- **`studio_unlock`**: manter só na SYS e tirar do RAISE para não apertar sem querer.
- **Layout ABNT2**: se o SO está em BR, vários símbolos do RAISE (especialmente com Shift “embutido”) podem sair errados — aí o caminho é keymap pensado no host ou US intl.

---

## Ordem sugerida para aplicar

1. NAV no polegar
2. Esc/Delete mais acessíveis
3. Home row mods (depois de usar 1–2 semanas)
