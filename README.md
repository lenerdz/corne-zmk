# Corne ZMK

Configuração de firmware [ZMK](https://zmk.dev) para um teclado **Corne split** com **RGB por tecla**, **underglow**, **telas OLED verticais** e **ZMK Studio**. O firmware é compilado pelo GitHub Actions a cada push: não é preciso instalar nada no computador para gerar os arquivos de gravação.

> Este README descreve o que está de fato no repositório. Ao mudar qualquer coisa (teclas, luzes, opções, versões), a mudança deve ser refletida aqui. Veja [Manter este README atualizado](#manter-este-readme-atualizado).

## Sumário

- [Visão geral](#visão-geral)
  - [Hardware](#hardware)
  - [Recursos](#recursos)
- [Estrutura do repositório](#estrutura-do-repositório)
- [Teclado: posições, camadas e funções](#teclado-posições-camadas-e-funções)
  - [Posições das teclas](#posições-das-teclas)
  - [Camadas](#camadas)
  - [Funções e recursos](#funções-e-recursos)
  - [ZMK Studio](#zmk-studio)
    - [Ícones nas teclas (fork do app)](#ícones-nas-teclas-fork-do-app)
- [Luzes (RGB por tecla e underglow)](#luzes-rgb-por-tecla-e-underglow)
  - [Como as luzes funcionam](#como-as-luzes-funcionam)
  - [Controles no dia a dia](#controles-no-dia-a-dia)
  - [Efeitos instalados](#efeitos-instalados)
  - [Cores por camada e indicador de Caps Lock](#cores-por-camada-e-indicador-de-caps-lock)
  - [Slots de cor](#slots-de-cor)
  - [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio)
    - [Editar as cores na aba Lights](#editar-as-cores-na-aba-lights)
  - [O que é salvo na memória](#o-que-é-salvo-na-memória)
  - [Guia de configuração](#guia-de-configuração)
    - [Aplicar uma mudança no teclado](#aplicar-uma-mudança-no-teclado)
    - [Mudar a cor ou a velocidade de um efeito](#mudar-a-cor-ou-a-velocidade-de-um-efeito)
    - [Mudar o brilho e o efeito inicial](#mudar-o-brilho-e-o-efeito-inicial)
    - [Manter as luzes acesas quando o teclado fica ocioso](#manter-as-luzes-acesas-quando-o-teclado-fica-ocioso)
    - [Mudar a cor de uma tecla ou de um LED em uma camada](#mudar-a-cor-de-uma-tecla-ou-de-um-led-em-uma-camada)
    - [Tornar as cores editadas na aba Lights os novos padrões](#tornar-as-cores-editadas-na-aba-lights-os-novos-padrões)
    - [Deixar o efeito aparecer por baixo do mapa de uma camada](#deixar-o-efeito-aparecer-por-baixo-do-mapa-de-uma-camada)
    - [Mudar quais LEDs um overlay pinta](#mudar-quais-leds-um-overlay-pinta)
    - [Adicionar um efeito novo](#adicionar-um-efeito-novo)
    - [Adicionar o mapa de cores de uma camada nova](#adicionar-o-mapa-de-cores-de-uma-camada-nova)
    - [Dar um efeito próprio ao underglow](#dar-um-efeito-próprio-ao-underglow)
    - [Escolher quais overlays aparecem em cada efeito](#escolher-quais-overlays-aparecem-em-cada-efeito)
    - [Salvar a cor e a velocidade ajustadas nas teclas](#salvar-a-cor-e-a-velocidade-ajustadas-nas-teclas)
    - [Trocar o mapa dos LEDs](#trocar-o-mapa-dos-leds)
  - [Referência de efeitos, condições e overlays](#referência-de-efeitos-condições-e-overlays)
  - [Mapa dos LEDs](#mapa-dos-leds)
- [Telas OLED](#telas-oled)
  - [O que cada tela mostra](#o-que-cada-tela-mostra)
  - [Opções de configuração das telas](#opções-de-configuração-das-telas)
- [Compilar e gravar o firmware](#compilar-e-gravar-o-firmware)
  - [Compilar](#compilar)
  - [Baixar os arquivos de gravação](#baixar-os-arquivos-de-gravação)
  - [Gravar as metades](#gravar-as-metades)
  - [Limpar as configurações salvas (settings_reset)](#limpar-as-configurações-salvas-settings_reset)
- [Módulos, forks e versões fixadas](#módulos-forks-e-versões-fixadas)
  - [Versões fixadas](#versões-fixadas)
  - [Por que existem os forks](#por-que-existem-os-forks)
  - [Atualizar uma versão ou voltar ao upstream](#atualizar-uma-versão-ou-voltar-ao-upstream)
- [Solução de problemas](#solução-de-problemas)
- [Manter este README atualizado](#manter-este-readme-atualizado)
- [Referências](#referências)

## Visão geral

### Hardware

| Item | Detalhe |
|---|---|
| Teclado | Corne (foostan) split de 42 teclas: 3 linhas de 6 colunas e 3 teclas de polegar por metade |
| Controladores | nice!nano v2, um por metade (placa `nice_nano//zmk`) |
| Telas | OLED SSD1306 em cada metade |
| LEDs | WS2812, 27 por metade: 21 sob as teclas e 6 de underglow |
| Papéis | A metade esquerda é a **central**: fala com o computador (USB ou Bluetooth) e hospeda o ZMK Studio. A metade direita é a **periférica**: conecta-se à esquerda por Bluetooth |

### Recursos

- **6 camadas** no padrão do ZMK Studio: QWERTY, FN1, RAISE, NAV, SYS e MEDIA. Veja [Camadas](#camadas).
- **RGB por tecla**: os 27 LEDs de cada metade são controlados pelo módulo zmk-rgb-matrix, com 9 efeitos, troca direta de efeito por teclas na camada SYS, um **mapa de cores por LED em cada camada** (as teclas acendem pela função e o underglow pela camada) e indicador de Caps Lock. As cores de cada mapa podem ser **editadas e salvas no teclado**, sem recompilar, pela aba **Lights** do fork do app do ZMK Studio (não testado neste teclado). Veja [Luzes](#luzes-rgb-por-tecla-e-underglow) e [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio).
- **Telas OLED verticais** (nice!oled): saída (USB ou Bluetooth), bateria, perfil Bluetooth, velocidade de digitação e camada ativa. A tela nunca apaga. Veja [Telas OLED](#telas-oled).
- **ZMK Studio** na metade esquerda (USB) para editar teclas sem recompilar, com um [fork do app](https://github.com/lenerdz/zmk-studio) que desenha ícones nas teclas de Bluetooth, luzes e camadas e tem a aba **Lights** para editar as cores das luzes. Veja [ZMK Studio](#zmk-studio).
- **Bluetooth com 5 perfis**, **NKRO** e **Caps Word**. Veja [Funções e recursos](#funções-e-recursos).
- **Build automático** pelo GitHub Actions, com versões fixadas do ZMK e dos módulos para que o resultado seja reproduzível. Veja [Compilar e gravar o firmware](#compilar-e-gravar-o-firmware) e [Módulos, forks e versões fixadas](#módulos-forks-e-versões-fixadas).

## Estrutura do repositório

```text
.
├── .github/workflows/build.yml   CI: chama o workflow de build do ZMK (fixado em um commit)
├── boards/shields/.gitkeep       pasta vazia reservada para shields próprios
├── build.yaml                    matriz de builds: placas, shields, snippets e nomes dos artefatos
├── config/
│   ├── corne.keymap              teclas, camadas e toda a configuração das luzes (efeitos, condições, overlays)
│   ├── corne.conf                opções Kconfig das duas metades: telas, Bluetooth, NKRO, energia, luzes
│   ├── corne_left.conf           opções Kconfig só da metade esquerda: buffer de recepção do ZMK Studio
│   ├── corne_left.overlay        mapa dos LEDs da metade esquerda e os slots de cor dela (slot-count, no-key-slots)
│   ├── corne_right.overlay       mapa dos LEDs da metade direita e os slots de cor dela (slot-count, no-key-slots)
│   ├── led_colors.dtsi           cores padrão de cada slot em cada camada (incluído no fim do corne.keymap)
│   ├── rgb.dtsi                  legado, sem uso (veja a nota abaixo)
│   └── west.yml                  versões do ZMK e dos módulos
├── SUGESTOES.md                  ideias de melhoria do layout
└── README.md                     este arquivo
```

- Os shields `corne_left` e `corne_right` vêm do próprio ZMK. Este repositório só acrescenta o keymap, as opções, os mapas de LED e de slots de cor, as cores padrão de cada slot em cada camada e a lista de módulos.
- `config/led_colors.dtsi` é o arquivo a editar para mudar as cores padrão de cada LED em cada camada. O `config/corne.keymap` o inclui no final. As cores são indexadas por slot e valem para as duas metades. Veja [Cores por camada e indicador de Caps Lock](#cores-por-camada-e-indicador-de-caps-lock).
- `config/corne_left.conf` vale só para o build da metade esquerda: o ZMK aplica o `config/<shield>.conf` de cada shield do build, e o `corne.conf` vale para as duas metades. Hoje ele só define o buffer de recepção do ZMK Studio (veja [ZMK Studio](#zmk-studio)).
- `config/rgb.dtsi` é resto da configuração antiga de underglow (macros de cor e anotações do mapa de LEDs da época). Nenhum arquivo o inclui, então ele não afeta o firmware. O mapa de LEDs vigente está nos arquivos `.overlay` e na seção [Mapa dos LEDs](#mapa-dos-leds).
- [`SUGESTOES.md`](SUGESTOES.md) reúne ideias de melhoria do layout (acesso a NAV, home row mods, combos etc.).

## Teclado: posições, camadas e funções

### Posições das teclas

O keymap, os mapas de LED e as receitas deste README usam a numeração de posições do Corne de 6 colunas (`foostan_corne_6col_layout`). As posições 0 a 35 são as três linhas de cada metade e 36 a 41 são os polegares.

```text
Esquerda                      Direita
   0   1   2   3   4   5         6   7   8   9  10  11
  12  13  14  15  16  17        18  19  20  21  22  23
  24  25  26  27  28  29        30  31  32  33  34  35
              36  37  38        39  40  41
```

### Camadas

| ID | Camada | Para que serve | Como ativar | Cor da camada (underglow e tecla que a ativa) |
|---|---|---|---|---|
| 0 | QWERTY | digitação (base) | camada padrão | mostra o efeito ativo (azul só com o efeito `static`) |
| 1 | FN1 | números e teclas F | segurar o polegar do meio da esquerda (posição 37) | laranja |
| 2 | RAISE | símbolos | segurar o polegar do meio da direita (posição 40) | azul-claro |
| 3 | NAV | setas, Home/End, PgUp/PgDn, Insert, Delete | segurar FN1 e, sem soltar, segurar a tecla da posição 24 (canto inferior esquerdo) | verde |
| 4 | SYS | Bluetooth e controle das luzes | segurar FN1 e, sem soltar, segurar a tecla da posição 25 (a do Z) | magenta |
| 5 | MEDIA | volume, mídia, brilho do monitor, Caps Lock, Caps Word | segurar FN1 e, sem soltar, segurar a tecla da posição 26 (a do X) | ciano |

As camadas 3, 4 e 5 só são alcançadas por FN1: a camada FN1 tem `&mo 3`, `&mo 4` e `&mo 5` nas posições 24, 25 e 26.

O **ID** da camada é a ordem em que ela foi declarada em `config/corne.keymap` (QWERTY 0, FN1 1, RAISE 2, NAV 3, SYS 4, MEDIA 5). É o número que as condições de luz (`cond_*`) e o `layer-id` dos mapas de cor usam, e ele não muda quando as camadas são reordenadas no ZMK Studio.

A cor da camada é a do underglow enquanto ela está ativa e a da tecla que a ativa. As cores de todas as teclas de cada camada estão em [Cores por camada e indicador de Caps Lock](#cores-por-camada-e-indicador-de-caps-lock).

Nas grades abaixo, cada camada aparece em duas partes (esquerda e direita), na mesma ordem das linhas do arquivo `config/corne.keymap`. As linhas são: 3 linhas de 6 teclas e, por último, os 3 polegares. Legenda:

- `--` é uma tecla transparente: vale a tecla da camada de baixo.
- Os rótulos seguem os nomes de tecla do ZMK (`LGUI`, `PG_DN`, `C_VOL_DN`...). Pontuação aparece como o próprio caractere (`;`, `[`, `{`...).
- `FN1`, `RAISE`, `NAV`, `SYS` e `MEDIA` são `&mo <camada>` (a camada fica ativa enquanto a tecla é segurada).
- `STUDIO` é `&studio_unlock`, `BT n` é `&bt BT_SEL n` e `CAPS_WORD` é `&caps_word`.
- Na camada SYS, os nomes em minúsculas (`solid` a `static`) são os efeitos diretos `&fx_<nome>` e os `RGB_*` são `&kprgb RGB_*`.

#### Camada 0: QWERTY

```text
Esquerda
TAB       Q         W         E         R         T
LSHIFT    A         S         D         F         G
LCTRL     Z         X         C         V         B
                              LGUI      FN1       SPACE

Direita
Y         U         I         O         P         BSPC
H         J         K         L         ;         '
N         M         ,         .         [         ]
ENTER     RAISE     RALT
```

Com Shift, `[` e `]` viram `{` e `}`.

#### Camada 1: FN1

```text
Esquerda
GRAVE     F1        F2        F3        F4        F5
1         2         3         4         5         6
NAV       SYS       MEDIA     F12       --        --
                              LGUI      --        SPACE

Direita
F6        F7        F8        F9        F10       F11
7         8         9         0         -         =
--        --        --        --        --        --
ENTER     --        RALT
```

#### Camada 2: RAISE

```text
Esquerda
ESC       !         @         #         $         %
LCTRL     STUDIO    /         \         GRAVE     ~
LSHIFT    --        --        --        --        --
                              LGUI      --        SPACE

Direita
^         &         *         (         )         BSPC
-         =         [         ]         {         }
_         +         |         :         "         ?
ENTER     --        RALT
```

#### Camada 3: NAV

```text
Esquerda
ESC       --        --        --        --        --
LCTRL     HOME      PG_DN     PG_UP     END       INS
LSHIFT    --        --        --        --        --
                              LGUI      --        SPACE

Direita
--        --        --        --        --        BSPC
LEFT      DOWN      UP        RIGHT     TAB       DEL
HOME      PG_DN     PG_UP     END       --        --
ENTER     --        RALT
```

#### Camada 4: SYS

```text
Esquerda
BT_CLR    BT 0      BT 1      BT 2      BT 3      BT 4
RGB_TOG   RGB_EFF   RGB_HUI   RGB_HUD   RGB_BRI   RGB_BRD
STUDIO    --        --        --        --        --
                              LGUI      --        SPACE

Direita
solid     breathe   spectrum  rainbow   reactive  ripple
RGB_EFR   RGB_SAI   RGB_SAD   RGB_SPI   RGB_SPD   RGB_RESET
heatmap   starlight static    --        --        --
ENTER     --        RALT
```

O que cada tecla faz está em [Controles no dia a dia](#controles-no-dia-a-dia).

#### Camada 5: MEDIA

```text
Esquerda
C_PWR     C_SLEEP   --        --        --        CAPS_WORD
C_MUTE    C_VOL_DN  C_VOL_UP  C_BRI_DN  C_BRI_UP  CAPS
--        --        --        --        --        --
                              LGUI      --        SPACE

Direita
--        --        --        --        PSCRN     SLCK
C_PREV    C_PP      C_NEXT    C_STOP    --        --
--        --        --        --        --        --
ENTER     --        RALT
```

### Funções e recursos

- **Bluetooth com 5 perfis**: `BT 0` a `BT 4` (camada SYS, posições 1 a 5) escolhem o perfil e `BT_CLR` (posição 0) apaga o pareamento do perfil ativo. Opções em `config/corne.conf`: `CONFIG_BT_MAX_CONN=5` e `CONFIG_BT_MAX_PAIRED=5`. Para parear um dispositivo novo, selecione um perfil livre (ou apague o ativo com `BT_CLR`) e adicione o teclado no computador.
- **Caps Word** (`&caps_word`, camada MEDIA, posição 5): deixa as letras em maiúsculas até você digitar algo que não faça parte da lista de continuação. Letras e números sempre continuam. Neste projeto `continue-list = <UNDERSCORE>`, então só `_` continua além deles; qualquer outra tecla, inclusive Backspace e Delete, encerra o Caps Word. A lista padrão do ZMK é `<UNDERSCORE BACKSPACE DELETE>`: para voltar a ela, ajuste o bloco `&caps_word` no início de `config/corne.keymap`.
- **Caps Lock**: tecla `CAPS` na camada MEDIA (posição 17). Quando o computador reporta o Caps Lock ligado, a coluna externa da metade esquerda acende em branco. O Caps Word não aciona esse indicador, porque ele não liga o Caps Lock do computador.
- **NKRO**: `CONFIG_ZMK_HID_REPORT_TYPE_NKRO=y` permite pressionar qualquer número de teclas ao mesmo tempo.
- **Energia**: `CONFIG_ZMK_SLEEP=n` desliga o deep sleep e `CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=n` mantém as telas sempre acesas (o ZMK não tem uma opção só para USB). Isso aumenta o consumo de bateria no uso sem fio. As luzes são tratadas à parte e apagam após 30 s sem digitar; veja [Manter as luzes acesas quando o teclado fica ocioso](#manter-as-luzes-acesas-quando-o-teclado-fica-ocioso).

### ZMK Studio

O ZMK Studio permite editar teclas pelo navegador, sem recompilar. Ele está habilitado só na metade esquerda: em `build.yaml`, o build `corne_left` usa o snippet `studio-rpc-usb-uart` e `-DCONFIG_ZMK_STUDIO=y`. O `config/corne_left.conf` define `CONFIG_ZMK_STUDIO_RPC_RX_BUF_SIZE=256`, o tamanho do buffer em que o ZMK Studio recebe os pedidos do app: o padrão do ZMK (30 bytes) descarta os bytes que não cabem, e um pedido que edita 16 cores de LED tem 158 bytes (até cerca de 210 com escapes). O módulo zmk-rgb-matrix confere o valor: a compilação da esquerda falha com menos de 256.

1. Conecte a **metade esquerda** ao computador por USB.
2. Abra o app em um navegador baseado em Chromium e conecte ao teclado: [zmk.studio](https://zmk.studio) (o app oficial) ou o [fork não oficial deste projeto](https://lenerdz.github.io/zmk-studio/), que desenha ícones nas teclas (veja [Ícones nas teclas (fork do app)](#ícones-nas-teclas-fork-do-app)) e tem a aba **Lights** para editar as cores das luzes (veja [Editar as cores na aba Lights](#editar-as-cores-na-aba-lights)).
3. Para liberar a edição, pressione a tecla `&studio_unlock`: camada RAISE, posição 13, ou camada SYS, posição 24.

> **Atenção:** depois que você usar o ZMK Studio para gerenciar as teclas, mudanças futuras no arquivo `.keymap` não são aplicadas até você executar a ação "Restore Stock Settings" na interface do Studio (ou gravar o `settings_reset` nas duas metades). É o comportamento documentado pelo ZMK. Em geral, escolha um dos dois caminhos para as teclas: o Studio ou o `.keymap`.
>
> Isso vale para as teclas e camadas. Os efeitos, as condições e os overlays de luz, as cores padrão de `config/led_colors.dtsi`, o `corne.conf` e os `.overlay` são compilados no firmware e continuam valendo normalmente a cada gravação. As cores de mapa que alguém tenha editado e salvo no teclado (veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio)) têm prioridade sobre as padrão nos slots editados, e "Restore Stock Settings" as apaga. A consequência prática: se você já usa o Studio, um efeito novo adicionado ao `.keymap` precisa ser atribuído a uma tecla pelo próprio Studio (é o caso do `&fx_static`, camada SYS, posição 32). As cores de cada camada seguem o ID da camada e a posição física da tecla, não o que o Studio colocou nela.

O firmware usa um fork do protocolo do ZMK Studio, o [`lenerdz/zmk-studio-messages`](https://github.com/lenerdz/zmk-studio-messages) (com [README em português](https://github.com/lenerdz/zmk-studio-messages/blob/main/README.pt-BR.md)), que acrescenta as requisições dos mapas de cor. Os apps (o oficial e o fork) continuam editando teclas normalmente: eles só não conhecem as requisições novas. Veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio) e [Por que existem os forks](#por-que-existem-os-forks).

#### Ícones nas teclas (fork do app)

O app oficial desenha cada tecla como o nome do comportamento e, embaixo, o primeiro parâmetro como se fosse uma tecla do teclado. Isso serve para teclas comuns, mas as teclas de Bluetooth, de luzes e de camadas ficam vazias ou com um rótulo sem sentido. O fork não oficial [`lenerdz/zmk-studio`](https://github.com/lenerdz/zmk-studio) (com [README em português](https://github.com/lenerdz/zmk-studio/blob/main/README.pt-BR.md)), publicado em <https://lenerdz.github.io/zmk-studio/>, desenha um ícone e um rótulo curto nessas teclas. Passar o mouse sobre uma tecla mostra a descrição completa, como `Bluetooth: Select Profile 2`.

| Tecla deste projeto | O que o fork desenha |
|---|---|
| `&mo` (camadas), por exemplo `&mo 1` | ícone de camadas e o nome da camada (`FN1`) |
| `&bt BT_SEL 0` a `&bt BT_SEL 4` | ícone de Bluetooth e o número do perfil |
| `&bt BT_CLR` | ícone de Bluetooth com uma borracha e `clear` |
| `&kprgb RGB_*` | cabeçalho `RGB`, um ícone e uma palavra curta: `on/off`, `hue`, `sat`, `bri`, `time`, `effect`, `reset`, com `+` ou `-` para subir e descer |
| `&fx_*` | cabeçalho `Effect`, um ícone para cada efeito e o nome (`solid`, `breathe`, ...) |
| `&studio_unlock`, `&caps_word`, `&trans` | cadeado aberto, seta do Caps Word e seta dupla esmaecida |
| Teclas de mídia (`C_MUTE`, `C_VOL_UP`, `C_BRI_UP`, ...) | ícones, no lugar dos emojis do app oficial |

Os ícones não alteram o protocolo nem o que é gravado no teclado: a edição das teclas, o salvamento e o "Restore Stock Settings" seguem o mesmo caminho do app oficial. Além do desenho das teclas e da hospedagem do app, o fork acrescenta a aba **Lights**, que usa as requisições novas do firmware (veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio)). Veja [Por que existem os forks](#por-que-existem-os-forks).

**Testado neste teclado.** O fork, na versão que só tinha os ícones (antes da aba Lights), foi usado com este teclado conectado por USB e os ícones e rótulos funcionaram (relato do dono do teclado). Também foi verificado nas stories do Storybook do fork, com as seis camadas deste `corne.keymap`; os nomes dos comportamentos usados nelas vêm do código-fonte do ZMK e do zmk-rgb-matrix. O app só mostra o que o firmware informa: se uma tecla aparecer vazia ou com um rótulo estranho, passe o mouse sobre ela para ver o nome do comportamento.

## Luzes (RGB por tecla e underglow)

### Como as luzes funcionam

As luzes são controladas pelo módulo [zmk-rgb-matrix](https://github.com/gudzpoz/zmk-rgb-matrix), usado a partir de um [fork](https://github.com/lenerdz/zmk-rgb-matrix) com duas correções (veja [Por que existem os forks](#por-que-existem-os-forks)). O underglow nativo do ZMK (`CONFIG_ZMK_RGB_UNDERGLOW`) fica desligado, porque os dois não podem controlar a mesma fita de LEDs ao mesmo tempo.

1. **Fita de LEDs**: cada metade tem 27 LEDs WS2812 em série (`&led_strip { chain-length = <27>; }` em `config/corne.keymap`). Os índices 0 a 5 são o underglow (sem tecla) e 6 a 26 são um LED sob cada tecla.
2. **Mapa dos LEDs**: o nó `keypaw,rgb-matrix` de cada metade (em `config/corne_left.overlay` e `config/corne_right.overlay`) diz onde cada LED fica: pela posição da tecla ou, no underglow, por coordenadas. Os efeitos que dependem de posição (reativo, ondas, mapa de calor) usam essas coordenadas. O mesmo nó define os **slots de cor** (`slot-count` e `no-key-slots`): a posição da lista de cores de onde cada LED tira a sua cor (veja [Slots de cor](#slots-de-cor)).
3. **Efeitos**: são os nós filhos do comportamento `kprgb` no keymap. Um efeito principal de cada vez pinta todos os LEDs, e as teclas da camada SYS trocam o efeito. O efeito `fx_static` é o mapa de cores da camada base.
4. **Overlays**: pintam por cima do efeito principal, só enquanto uma condição for verdadeira (uma camada ativa, o Caps Lock ligado). Aqui há um **mapa de cores por camada** (FN1 a MEDIA), que cobre todos os LEDs da metade, e um indicador de Caps Lock, que pinta só três.
5. **As duas metades precisam ter exatamente os mesmos efeitos, condições e overlays, na mesma ordem**, porque o módulo os identifica pela posição em que foram declarados. Por isso esses blocos ficam no `config/corne.keymap`, que é compartilhado, e não nos `.overlay` de cada metade. As cores também são as mesmas nas duas metades: o `slot-colors` de cada mapa vem de `config/led_colors.dtsi` e é indexado por slot, e cada metade pinta só os slots dos seus LEDs. O que difere entre as metades são os `.overlay` (`mapping`, `slot-count` e `no-key-slots`). Sempre grave as duas metades depois de mexer em qualquer um desses arquivos.

O efeito principal e cada overlay são combinados nesta ordem de pintura (do fundo para o topo): efeito ativo, `ov_fn1`, `ov_raise`, `ov_nav`, `ov_sys`, `ov_media`, `ov_caps`. Quem é declarado depois fica por cima. Um mapa de camada cobre todos os LEDs: enquanto um deles está ativo, o efeito principal e os mapas declarados antes dele nem são desenhados (o efeito principal fica pausado e volta quando a camada é solta).

### Controles no dia a dia

Segure FN1 e, sem soltar, segure a tecla da posição 25 para ativar a camada SYS. Os comandos de luz são `&kprgb RGB_*` (valem para as duas metades) e os efeitos diretos são `&fx_<nome>`.

| Posição | Tecla na base | Comando | O que faz |
|---|---|---|---|
| 0 | TAB | `&bt BT_CLR` | apaga o pareamento do perfil Bluetooth ativo |
| 1 a 5 | Q W E R T | `&bt BT_SEL 0` a `4` | seleciona o perfil Bluetooth 0 a 4 |
| 6 | Y | `&fx_solid` | escolhe o efeito `solid` |
| 7 | U | `&fx_breathe` | escolhe o efeito `breathe` |
| 8 | I | `&fx_spectrum` | escolhe o efeito `spectrum` |
| 9 | O | `&fx_rainbow` | escolhe o efeito `rainbow` |
| 10 | P | `&fx_reactive` | escolhe o efeito `reactive` |
| 11 | BSPC | `&fx_ripple` | escolhe o efeito `ripple` |
| 12 | LSHIFT | `&kprgb RGB_TOG` | liga ou desliga as luzes |
| 13 | A | `&kprgb RGB_EFF` | próximo efeito |
| 14 | S | `&kprgb RGB_HUI` | gira a cor do efeito atual para a frente (matiz +) |
| 15 | D | `&kprgb RGB_HUD` | gira a cor do efeito atual para trás (matiz -) |
| 16 | F | `&kprgb RGB_BRI` | aumenta o brilho (até `max-brightness`) |
| 17 | G | `&kprgb RGB_BRD` | diminui o brilho |
| 18 | H | `&kprgb RGB_EFR` | efeito anterior |
| 19 | J | `&kprgb RGB_SAI` | aumenta a saturação |
| 20 | K | `&kprgb RGB_SAD` | diminui a saturação |
| 21 | L | `&kprgb RGB_SPI` | aumenta a duração do ciclo da animação em 100 ms (`CONFIG_KEYPAW_RGB_MATRIX_DURATION_STEP`): o efeito fica **mais lento**. O nome vem do ZMK, mas aqui o ajuste é no período |
| 22 | ; | `&kprgb RGB_SPD` | diminui a duração do ciclo em 100 ms: o efeito fica **mais rápido** |
| 23 | ' | `&kprgb RGB_RESET` | apaga o estado salvo das luzes e volta aos padrões do keymap |
| 24 | LCTRL | `&studio_unlock` | libera a edição no ZMK Studio |
| 30 | N | `&fx_heatmap` | escolhe o efeito `heatmap` |
| 31 | M | `&fx_starlight` | escolhe o efeito `starlight` |
| 32 | , | `&fx_static` | escolhe o efeito `static`: o mapa de cores da camada base |

### Efeitos instalados

São 9 efeitos, declarados dentro de `kprgb` em `config/corne.keymap`. A ordem da tabela é a ordem de `RGB_EFF` e `RGB_EFR` e o índice usado em `initial-effect` (0 é o primeiro).

| Índice | Nome (`&fx_...`) | Tipo | Resultado | Propriedades no keymap | Atalho na SYS (posição) |
|---|---|---|---|---|---|
| 0 | `fx_solid` | `solid` | cor única | `color = 0xFF0000` | 6 |
| 1 | `fx_breathe` | `breathe` | respiração: o brilho sobe e desce | `color = 0x0000FF`, `duration = 3000` | 7 |
| 2 | `fx_spectrum` | `spectrum` | todos os LEDs ciclam juntos pelo espectro de cores | `duration = 6000` | 8 |
| 3 | `fx_rainbow` | `rainbow` | arco-íris varrendo da esquerda para a direita | `color = 0xFFFFFF`, `duration = 4000`, `basis = "x"`, `direction = "out"`, `palette = "rainbow"` | 9 |
| 4 | `fx_reactive` | `reactive` | acende um disco ao redor da tecla pressionada | `color = 0x00FFFF`, `spread = "disc"`, `spread-radius = 250` | 10 |
| 5 | `fx_ripple` | `ripple` | ondas que se expandem a partir da tecla pressionada | `color = 0x00FFFF` | 11 |
| 6 | `fx_heatmap` | `heatmap` | mapa de calor: as teclas mais usadas esquentam e esfriam com o tempo | padrões do módulo | 30 |
| 7 | `fx_starlight` | `starlight` | brilhos aleatórios suaves | `color = 0xFFFFFF`, `smooth` | 31 |
| 8 | `fx_static` | `static` | cada LED com a cor do mapa da camada base | `slot-colors` em `config/led_colors.dtsi` (bloco `&fx_static`) e `layer-id = 0` | 32 |

O tipo de cada efeito é o `compatible` `keypaw,rgb-matrix-<tipo>`. Os efeitos que dependem de tecla pressionada (`reactive`, `ripple`, `heatmap`) reagem às teclas das duas metades. O `fx_static` não anima: cada LED mostra a cor do seu slot no bloco `&fx_static` de `config/led_colors.dtsi` (ou a cor editada, veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio)). As cores são `0xRRGGBB`: por exemplo vermelho `0xFF0000`, laranja `0xFF8000`, amarelo `0xFFFF00`, verde `0x00FF00`, ciano `0x00FFFF`, azul-claro `0x0080FF`, azul `0x0000FF`, magenta `0xFF00FF` e branco `0xFFFFFF`.

### Cores por camada e indicador de Caps Lock

Cada camada tem o seu mapa de cores: uma cor para cada um dos 54 slots (21 teclas e 6 LEDs de underglow em cada metade, veja [Slots de cor](#slots-de-cor)). As cores padrão ficam em [`config/led_colors.dtsi`](config/led_colors.dtsi), que o `config/corne.keymap` inclui no final, e são definidas na compilação: as teclas de luz não mudam essas cores. O arquivo tem a paleta, a macro que põe as cores na ordem dos slots e um bloco por camada. O firmware também permite editar e salvar a cor de cada slot no teclado, sem recompilar: veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio).

**Não testado neste teclado.** Foi verificado só no computador: as cores por slot reproduzem exatamente as da versão anterior (por LED da fita) em cada LED das duas metades (6 camadas, 2 metades e 27 LEDs, conferência por script que expande o `led_colors.dtsi` antigo e o novo e compara pelo `mapping` dos `.overlay`), e cada um dos 54 slots é pintado por exatamente um LED. O resultado nas teclas ainda não foi visto no teclado.

A camada 0 (QWERTY) usa o efeito `fx_static`: o mapa dela só aparece quando você escolhe esse efeito (camada SYS, posição 32); com os outros efeitos a camada 0 mostra o efeito. As camadas 1 a 5 usam overlays, que aparecem com qualquer efeito. Os overlays são declarados em `rgb_overlays` no `config/corne.keymap`:

| Overlay | Condição | LEDs | Cores |
|---|---|---|---|
| `ov_fn1` | camada 1 (FN1) ativa | `all-leds` | bloco `&map_fn1` |
| `ov_raise` | camada 2 (RAISE) ativa | `all-leds` | bloco `&map_raise` |
| `ov_nav` | camada 3 (NAV) ativa | `all-leds` | bloco `&map_nav` |
| `ov_sys` | camada 4 (SYS) ativa | `all-leds` | bloco `&map_sys` |
| `ov_media` | camada 5 (MEDIA) ativa | `all-leds` | bloco `&map_media` |
| `ov_caps` | Caps Lock do computador ligado | `keys = <0 12 24>` | `0xFFFFFF` (branco) |

Cada mapa de camada é um overlay com `all-leds` e um efeito `static` filho; o `slot-colors` desse filho é preenchido pelo bloco de mesmo nome em `config/led_colors.dtsi`, e o `layer-id` dele é o ID da camada (a ordem em que ela foi declarada no keymap), que identifica o mapa ao editar e salvar.

- **Prioridade entre camadas.** Como NAV, SYS e MEDIA são alcançadas segurando FN1, duas camadas ficam ativas ao mesmo tempo, e vale o mapa da camada declarada depois: FN1 + NAV mostra o mapa de NAV, FN1 + SYS mostra o de SYS e FN1 + MEDIA mostra o de MEDIA.
- **O efeito principal fica pausado.** Cada mapa cobre todos os LEDs da metade. Enquanto uma camada de FN1 a MEDIA está ativa, o efeito principal nem é desenhado: os efeitos que reagem às teclas (`reactive`, `ripple`, `heatmap`) não aparecem nem contam teclas nessas camadas, e voltam quando a camada é solta. Para ver o efeito por baixo do mapa, veja [Deixar o efeito aparecer por baixo do mapa de uma camada](#deixar-o-efeito-aparecer-por-baixo-do-mapa-de-uma-camada).
- **Brilho.** As cores são `0xRRGGBB` com brilho cheio. O brilho real vem do `kprgb` e vale para todas as cores, mapas inclusive: `RGB_BRI` e `RGB_BRD` clareiam e escurecem os mapas, e `max-brightness` é o teto. Matiz, saturação e velocidade não alteram os mapas.
- **As cores seguem a posição, não a tecla.** O mapa guarda uma cor por slot (0 a 41 são as posições físicas das teclas, veja [Posições das teclas](#posições-das-teclas)) e pertence a uma camada pelo ID dela. Se você trocar uma tecla pelo ZMK Studio, a cor não acompanha: edite o `led_colors.dtsi` ou a cor do slot (veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio)). Se você mudar a ordem das camadas no Studio, o mapa e a condição continuam na mesma camada, porque usam o ID, que não muda.
- **Cada metade pinta os seus slots.** Cada bloco tem um grupo de 27 valores para a metade esquerda e outro para a direita, e a macro `LED_SLOTS` os junta na lista de 54 slots, igual para as duas metades. O firmware de cada metade pinta só os slots dos seus LEDs (veja [Slots de cor](#slots-de-cor)).
- O número da camada em cada condição (`cond_fn1` a `cond_media`) e o `layer-id` de cada mapa são o ID da camada: a ordem em que ela foi declarada no keymap, começando em 0 (QWERTY 0, FN1 1, RAISE 2, NAV 3, SYS 4, MEDIA 5). O ID não muda quando as camadas são reordenadas no ZMK Studio.

**Cores padrão.** Cada tecla de camada acende na cor da camada que ela abre (a tecla que você segura continua acesa), e o underglow usa a cor da camada. As demais teclas seguem a função:

| Nome | Cor | Valor | Usada por padrão em |
|---|---|---|---|
| `OFF` | apagado | `0x000000` | teclas transparentes (`&trans`) e teclas sem função na camada |
| `WHT` | branco | `0xFFFFFF` | letras, SPACE, `CAPS`, `CAPS_WORD`, `C_MUTE` e `RGB_TOG` |
| `RED` | vermelho | `0xFF0000` | BSPC, DEL, ESC, `C_PWR`, `BT_CLR` e `RGB_RESET` |
| `ORG` | laranja | `0xFF8000` | teclas F, INS, `C_SLEEP`, `C_STOP`, `RGB_HUI` e `RGB_HUD`; camada FN1 |
| `YEL` | amarelo | `0xFFFF00` | números, `C_BRI_DN`, `C_BRI_UP`, `RGB_BRI` e `RGB_BRD` |
| `LIM` | verde-limão | `0x80FF00` | pontuação e símbolos, HOME, END, PG_UP, PG_DN, PSCRN, SLCK, `RGB_SAI` e `RGB_SAD` |
| `GRN` | verde | `0x00FF00` | setas, `C_PREV` e `C_NEXT`; camada NAV |
| `TEA` | verde-água | `0x00FF80` | ENTER e `C_PP` |
| `CYN` | ciano | `0x00FFFF` | `C_VOL_DN`, `C_VOL_UP`, `RGB_SPI` e `RGB_SPD`; camada MEDIA |
| `SKY` | azul-claro | `0x0080FF` | colchetes, chaves e parênteses; camada RAISE |
| `BLU` | azul | `0x0000FF` | perfis Bluetooth (`BT_SEL`); underglow da camada base |
| `PUR` | roxo | `0x8000FF` | TAB, Shift, Ctrl, GUI e Alt |
| `MAG` | magenta | `0xFF00FF` | `&studio_unlock`; camada SYS |
| `PNK` | rosa | `0xFF0080` | escolha de efeito (`&fx_*`, `RGB_EFF` e `RGB_EFR`) |

Os nomes são macros definidas no começo do `led_colors.dtsi` (veja a receita [Mudar a cor de uma tecla ou de um LED em uma camada](#mudar-a-cor-de-uma-tecla-ou-de-um-led-em-uma-camada)).

**Indicador de Caps Lock.** O overlay `ov_caps` pinta a coluna externa da metade esquerda (`keys = <0 12 24>`: TAB, LSHIFT e LCTRL) de branco enquanto o computador informa Caps Lock ligado (condição `cond_caps`). É o último overlay declarado, então aparece por cima de qualquer mapa de camada.

### Slots de cor

Os mapas de cor de cada camada guardam as cores por **slot**, e não por LED da fita. Um slot é uma posição da lista de cores (`slot-colors`) que significa a mesma coisa nas duas metades:

| Slots | LED que o slot pinta |
|---|---|
| 0 a 41 | o LED sob a tecla de mesma posição (a numeração de [Posições das teclas](#posições-das-teclas)) |
| 42 a 47 | os 6 LEDs de underglow da metade esquerda, na ordem da fita (LEDs 0 a 5) |
| 48 a 53 | os 6 LEDs de underglow da metade direita, na ordem da fita (LEDs 0 a 5) |

São 54 slots: `slot-count = <54>;` nos dois `.overlay`. Cada metade pinta só os seus 27 slots (21 teclas e 6 de underglow); os outros 27 pertencem à outra metade. O `no-key-slots` de cada `.overlay` diz o slot de cada LED sem tecla, na ordem do `mapping`: `<42 43 44 45 46 47>` na esquerda e `<48 49 50 51 52 53>` na direita.

Por que slots:

- A lista é a mesma nas duas metades. Uma cor alterada na metade central pode ser enviada à periférica pelo número do slot (veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio)).
- O `led_colors.dtsi` não depende mais da ordem da fita nem de uma macro por metade: a macro `LED_SLOTS(esquerda, direita)` recebe os dois grupos como são escritos (21 teclas e 6 de underglow cada) e devolve as 54 cores na ordem dos slots.

O limite é 60 slots (`slot-count` até 60): o registro que o firmware grava na memória para cada camada tem no máximo 242 bytes, e o limite de um valor salvo pelas configurações do Zephyr (`SETTINGS_MAX_VAL_LEN`) é 256.

### Mapas de cor editáveis pelo ZMK Studio

O firmware deixa ler, alterar, salvar e descartar as cores de cada mapa de camada pelo protocolo do ZMK Studio, sem recompilar. A tela para isso é a aba **Lights** do [fork do app](https://github.com/lenerdz/zmk-studio) (veja [Editar as cores na aba Lights](#editar-as-cores-na-aba-lights)); o app oficial não tem essa aba.

**Não testado neste teclado.** A aba Lights foi testada em um navegador contra um teclado de demonstração que usa a mesma moldura (framing) e a mesma codificação de mensagens de um teclado real, e tem testes automáticos. O firmware compila no GitHub Actions. Nunca foram experimentados no teclado: a edição ao vivo, o salvamento na memória, o descarte, o "Restore Stock Settings", o `RGB_RESET` e a cópia para a metade direita. O codec do registro salvo na memória e partes da sincronização têm testes de unidade que rodam no computador.

**Como um mapa se comporta.** Cada mapa (um efeito `static` com `layer-id`) guarda três cópias das cores, uma por slot:

| Cópia | O que é | Quando muda |
|---|---|---|
| padrão | as cores de `config/led_colors.dtsi`, gravadas no firmware | só ao gravar um firmware novo |
| ao vivo | o que as luzes mostram agora | a cada edição (`set_led_colors`), na hora |
| salva | o que foi gravado na memória, ou carregado dela ao ligar | ao salvar |

- **Editar** muda a cor ao vivo e repinta na hora. Sem salvar, a edição vale só até desligar o teclado.
- **Salvar** grava, na memória da metade esquerda, um registro por camada alterada (`keypaw/rgb_matrix/map/<ID da camada>`) com só os slots diferentes do padrão. Um mapa que volta a ficar igual ao padrão apaga o registro. Ao ligar, os registros são lidos e valem no lugar do padrão, slot a slot; os slots que nunca foram editados seguem o padrão do firmware.
- **Descartar** devolve as cores ao vivo para as salvas.
- **Restaurar o padrão** de uma camada põe as cores ao vivo dela no padrão (para gravar isso, salve em seguida).
- **`RGB_RESET`** e o **Restore Stock Settings** do ZMK Studio apagam todos os registros e voltam todos os mapas ao padrão.

**Requisições.** Fazem parte do subsistema `keymap` do protocolo e só existem no fork [`lenerdz/zmk-studio-messages`](https://github.com/lenerdz/zmk-studio-messages) (identificadores a partir de 100, longe dos do upstream). Como as de teclas, todas exigem o teclado desbloqueado (`&studio_unlock`).

| Requisição | ID | Resposta | O que faz |
|---|---|---|---|
| `get_led_info` | 100 | `LedInfo`: `slot_count`, `layer_ids` (os IDs das camadas que têm mapa) e `unsaved_changes` | descobre o que há para editar |
| `get_led_map` | 101 | `LedMap`: `layer_id` e `colors` (uma cor `0xRRGGBB` por slot, as ao vivo) | lê o mapa de uma camada |
| `set_led_colors` | 102 | `OK`, `INVALID_LAYER`, `INVALID_SLOT` ou `BUSY` (qualquer outro erro ao aplicar) | altera até 16 slots de uma camada, tudo ou nada |
| `save_led_changes` | 103 | ok, ou erro (`NOT_SUPPORTED`, `NO_SPACE`, `GENERIC`) | grava na memória os mapas alterados |
| `discard_led_changes` | 104 | `true` | volta as cores ao vivo para as salvas |
| `restore_led_defaults` | 105 | `LedMap` já restaurado | volta o mapa de uma camada ao padrão |

O firmware também envia a notificação `unsaved_led_changes_status_changed` (ID 100): `true` quando alguma cor ao vivo fica diferente da salva e `false` quando deixa de ficar. O ZMK Studio já tem a sua própria noção de alterações não salvas (teclas e camadas); um cliente precisa juntar as duas.

**Protocolo.** O ZMK traz o protocolo como o módulo `zmk-studio-messages` (em `app/west.yml`). O `config/west.yml` o substitui, com o mesmo nome e caminho, pelo fork, que parte do mesmo commit do ZMK (`6cb4c28`) e acrescenta um commit (`cfcce43`). Sem o fork o módulo não compila com o ZMK Studio ligado. A opção `CONFIG_KEYPAW_RGB_MAPS_STUDIO` liga as requisições e vem ligada quando o ZMK Studio está no build (só no firmware da esquerda). Os apps que não conhecem as requisições novas continuam editando teclas normalmente: o app oficial não as envia (não testado neste teclado com o app oficial). O fork do app as usa por um cliente TypeScript gerado a partir do mesmo protocolo (`src/vendor/zmk-studio-ts-client`, na revisão `cfcce43`).

**Metade direita.** Quem salva é a central, e a periférica nunca grava os mapas. Cada edição vira um comando interno por slot (`RGB_MAP_SET_CMD`) enviado à periférica, um por vez, com 50 ms entre eles. Quando a periférica conecta (ou reinicia), a central manda primeiro um comando que volta os mapas dela ao padrão (`RGB_MAP_RESET_CMD`) e depois só os slots dela cuja cor difere do padrão. Se a metade direita for desligada, ela volta às cores padrão do firmware dela e recebe as edições de novo ao reconectar. Como a periférica parte do padrão do próprio firmware, grave a metade que você mudou em `led_colors.dtsi`. **Não testado neste teclado**: a sincronização por Bluetooth só pode ser conferida no teclado.

**Limites.** `slot-count` até 60; no protocolo do fork, a lista `colors` de `LedMap` tem 54 posições (com mais slots é preciso aumentar `colors max_count` em `proto/zmk/keymap.options.in` do fork e o firmware avisa na compilação). IDs de camada de 0 a 14. No máximo 8 mapas em `get_led_info` e 16 slots por `set_led_colors`. O buffer de recepção do ZMK Studio precisa ter pelo menos 256 bytes (`CONFIG_ZMK_STUDIO_RPC_RX_BUF_SIZE=256`, em `config/corne_left.conf`): um `set_led_colors` com 16 slots tem 158 bytes depois do enquadramento (até cerca de 210 com escapes) e o padrão do ZMK (30 bytes) descarta o que não cabe. A compilação falha com um valor menor.

#### Editar as cores na aba Lights

1. Grave o firmware nas duas metades, conecte a **metade esquerda** por USB e abra o [fork do app](https://lenerdz.github.io/zmk-studio/) em um navegador baseado em Chromium. Conecte ao teclado e desbloqueie com `&studio_unlock` (veja [ZMK Studio](#zmk-studio)).
2. Depois de desbloquear, o cabeçalho ganha o botão **Lights**, ao lado de **Keys** (o editor de teclas). O app só o oferece quando o firmware tem os mapas editáveis; se ele não aparecer, veja [Solução de problemas](#solução-de-problemas).
3. Escolha uma camada na lista da esquerda. O desenho mostra cada tecla com o seu rótulo e a cor do LED dela. Os LEDs de underglow, que não têm tecla, são as células redondas da faixa sob as teclas (numeradas de 1 a 6 em cada metade).
4. Escolha uma cor (uma das 14 cores da paleta do `led_colors.dtsi`, o seletor de cor do sistema ou um valor hexadecimal) e arraste sobre os LEDs com **Paint**. O app mostra a cor enquanto você pinta e envia o traço quando você solta; o teclado mostra a cor na hora. As células também funcionam pelo teclado do computador (Tab para andar, Enter ou Espaço para pintar).
   - **Pick** pega a cor de um LED.
   - **Fill** preenche todos os LEDs da camada (**All**), só as teclas (**Keys**) ou só o underglow (**Underglow**).
   - **Restore layer defaults** devolve a camada às cores com que o firmware foi compilado.
5. A edição fica só na memória viva do teclado até você clicar em **Save** (canto superior direito), que salva as luzes junto com as teclas. **Discard** descarta as duas coisas, e **Undo** e **Redo** valem para as duas, na ordem em que você fez. O "Restore Stock Settings" do menu do teclado conectado também devolve as cores de fábrica.
6. Para tornar as cores editadas as cores padrão do firmware, use **Export led_colors.dtsi** (veja [Tornar as cores editadas na aba Lights os novos padrões](#tornar-as-cores-editadas-na-aba-lights-os-novos-padrões)).

Para ver a aba sem o teclado, abra o app com `?demo` no endereço (<https://lenerdz.github.io/zmk-studio/?demo>): o diálogo de conexão ganha o "Demo keyboard", um teclado que roda no próprio navegador, e o "Demo keyboard (no light maps)", que responde como um firmware sem os mapas (e então a aba não é oferecida). O código da aba, o protocolo e os testes estão no [`src/lights/README.md`](https://github.com/lenerdz/zmk-studio/blob/main/src/lights/README.md) do fork (em inglês).

### O que é salvo na memória

O módulo guarda o estado das luzes na memória do teclado (`CONFIG_SETTINGS`), mas nem tudo:

| O que | Salvo? | Observação |
|---|---|---|
| ligado ou desligado, brilho e efeito selecionado | sim, sempre | gravados 60 s depois da última alteração (`CONFIG_ZMK_SETTINGS_SAVE_DEBOUNCE`, padrão do ZMK). Se desligar o teclado antes disso, a última alteração se perde |
| matiz, saturação e velocidade ajustados com `RGB_HUI`, `RGB_HUD`, `RGB_SAI`, `RGB_SAD`, `RGB_SPI` e `RGB_SPD` | só nos efeitos que têm `persist-id` | **neste repositório nenhum efeito tem `persist-id`**, então esses ajustes voltam aos valores do keymap ao reiniciar. Veja [Salvar a cor e a velocidade ajustadas nas teclas](#salvar-a-cor-e-a-velocidade-ajustadas-nas-teclas) |
| cores padrão dos mapas por camada (`config/led_colors.dtsi`) | não, fazem parte do firmware | só mudam ao gravar um firmware novo na metade correspondente |
| cores dos mapas por camada editadas pelo ZMK Studio | só quando você salva (botão **Save** do app, que envia `save_led_changes`) | um registro por camada na memória da metade esquerda, só com os slots diferentes do padrão. A metade direita não grava nada: recebe as cores da esquerda ao conectar. Os slots salvos valem no lugar do padrão, e `RGB_RESET` apaga os registros. Veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio) |

O estado salvo tem prioridade sobre os valores iniciais do `kprgb`: depois que você muda o efeito, o brilho ou o liga/desliga pelas teclas, `initial-effect` e `initial-brightness` deixam de valer naquele teclado.

`&kprgb RGB_RESET` apaga o estado salvo das duas metades, inclusive as cores editadas dos mapas por camada, e restaura os padrões do keymap. Use depois de mudar a lista de efeitos, os `persist-id` ou os valores iniciais, porque o estado salvo pode ficar fora de sincronia com a nova definição.

### Guia de configuração

Todas as receitas abaixo editam `config/corne.keymap` (ou `config/led_colors.dtsi`, `config/corne.conf` e os `.overlay`, quando indicado). Os valores de cada propriedade estão em [Referência de efeitos, condições e overlays](#referência-de-efeitos-condições-e-overlays).

> As receitas marcadas como "não testada neste teclado" foram escritas a partir da documentação do módulo (os arquivos `.yaml` de bindings do zmk-rgb-matrix). Se uma propriedade ou valor estiver errado, o build do GitHub Actions falha e mostra o erro no log.

#### Aplicar uma mudança no teclado

1. Edite os arquivos em `config/`.
2. Faça commit e push: o GitHub Actions compila a cada push.
3. Baixe os arquivos de gravação da execução (veja [Baixar os arquivos de gravação](#baixar-os-arquivos-de-gravação)).
4. Grave **as duas metades**: efeitos, condições e overlays precisam ser idênticos nelas.
5. Aperte `RGB_RESET` (camada SYS, posição 23) quando mudar a lista de efeitos, quando adicionar ou remover um `persist-id`, ou quando quiser que novos valores de `initial-effect`, `initial-brightness` ou do `color` e `duration` de um efeito com `persist-id` passem a valer: o estado já salvo tem prioridade sobre eles (veja [O que é salvo na memória](#o-que-é-salvo-na-memória)).
6. Se você já editou teclas pelo ZMK Studio, lembre que mudanças de teclas no `.keymap` só valem após "Restore Stock Settings" (veja [ZMK Studio](#zmk-studio)).

#### Mudar a cor ou a velocidade de um efeito

Edite o nó do efeito dentro de `kprgb`. `color` é `0xRRGGBB` e `duration` é o período da animação em milissegundos (menor é mais rápido):

```dts
fx_breathe: fx_breathe {
    compatible = "keypaw,rgb-matrix-breathe";
    #binding-cells = <0>;
    color = <0xFF00FF>;   // magenta
    duration = <2000>;    // um ciclo a cada 2 s
};
```

- `duration = <0>` (ou ausente) usa o `initial-duration-ms` do `kprgb` (padrão do módulo: 1000).
- O módulo limita a duração entre 100 ms e 10000 ms por padrão (`CONFIG_KEYPAW_RGB_MATRIX_DURATION_MIN_MS` e `CONFIG_KEYPAW_RGB_MATRIX_DURATION_MAX_MS`, que podem ser alterados no `config/corne.conf`).
- As teclas `RGB_HUI`, `RGB_HUD`, `RGB_SAI`, `RGB_SAD`, `RGB_SPI` e `RGB_SPD` mexem nesses valores em tempo de uso, mas sem `persist-id` o ajuste não sobrevive a reiniciar.

#### Mudar o brilho e o efeito inicial

Ficam nas propriedades do próprio `kprgb`:

```dts
kprgb: kprgb {
    compatible = "keypaw,behavior-rgb-matrix";
    #binding-cells = <2>;
    initial-effect = <0>;       // efeito ao ligar (índice da tabela de efeitos)
    initial-brightness = <20>;  // brilho ao ligar, em %
    max-brightness = <50>;      // teto de brilho, em %
    idle-brightness = <10>;     // brilho enquanto ocioso, em %
    // ... efeitos ...
};
```

| Propriedade | Padrão do módulo | Valor aqui | Significado |
|---|---|---|---|
| `initial-effect` | 0 | 0 | índice do efeito ao ligar (0 é `fx_solid`) |
| `initial-brightness` | 30 | 20 | brilho ao ligar, em % (0 a 100) |
| `max-brightness` | 40 | 50 | teto de brilho, em % (0 a 100). `RGB_BRI` nunca passa disso |
| `idle-brightness` | 30 | 10 | brilho durante a inatividade, em %. Só tem efeito com `CONFIG_KEYPAW_RGB_MATRIX_AUTO_OFF_IDLE=n` |
| `initial-duration-ms` | 1000 | não definido | duração aplicada ao ligar aos efeitos que não têm `duration` |

Os valores iniciais só valem enquanto o teclado não tem estado salvo. Se você já mexeu no efeito ou no brilho pelas teclas, aperte `RGB_RESET` depois de gravar para que `initial-effect` e `initial-brightness` voltem a valer.

Os LEDs são o maior consumo de bateria do teclado. Para uso sem fio, mantenha o brilho baixo.

#### Manter as luzes acesas quando o teclado fica ocioso

Por padrão do módulo, as luzes **apagam** quando o ZMK considera o teclado ocioso (30 s sem digitar, `CONFIG_ZMK_IDLE_TIMEOUT`). Para mantê-las acesas:

1. Em `config/corne.conf`, tire o `#` da linha `# CONFIG_KEYPAW_RGB_MATRIX_AUTO_OFF_IDLE=n`.
2. Ajuste `idle-brightness` no `kprgb`: é o brilho usado enquanto o teclado está ocioso.
3. (Opcional) Para mudar o tempo até o teclado ficar ocioso, acrescente ao `config/corne.conf` a linha `CONFIG_ZMK_IDLE_TIMEOUT=60000` (em milissegundos; o padrão é 30000).

Isso não afeta as telas OLED, que nunca apagam (`CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=n`).

#### Mudar a cor de uma tecla ou de um LED em uma camada

As cores ficam em `config/led_colors.dtsi`, um bloco por camada: `&fx_static` (QWERTY), `&map_fn1`, `&map_raise`, `&map_nav`, `&map_sys` e `&map_media`. Cada bloco tem dois grupos de 27 valores, o da metade esquerda e o da direita, nesta ordem: três linhas de 6 teclas, os 3 polegares e os 6 LEDs de underglow. As posições são as de [Posições das teclas](#posições-das-teclas), e o comentário ao lado de cada linha diz que tecla era aquela no keymap. Os dois grupos entram em `LED_SLOTS(esquerda, direita)`, que os põe na ordem dos slots (veja [Slots de cor](#slots-de-cor)). **Não testada neste teclado.**

1. Abra `config/led_colors.dtsi` e ache o bloco da camada.
2. Troque o nome da cor da posição que quiser. Exemplo: a tecla F12 da camada FN1 (terceira linha da metade esquerda, quarta tecla) de laranja (`ORG`) para vermelho (`RED`). No bloco `&map_fn1`, a linha passa a ser:

   ```dts
            GRN, MAG, CYN, RED, OFF, OFF, /* NAV SYS MEDIA F12 -- -- */
   ```

3. Para o underglow, troque os 6 últimos valores do grupo (a linha `/* underglow */`). A posição física de cada um está em [Mapa dos LEDs](#mapa-dos-leds).
4. Para uma cor que não está na paleta, escreva o valor direto no lugar do nome (`0xFF4000`) ou crie um nome novo no começo do arquivo, junto das outras cores (`#define BRN 0x804000 /* marrom */`).
5. Faça commit e push, baixe o firmware e grave a metade que você mudou (as duas, se mexeu nos dois grupos). Mudar só as cores não exige `RGB_RESET`, desde que ninguém tenha salvo edições nos slots que você mudou: uma cor editada e salva pelo ZMK Studio vale no lugar da padrão (veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio)). Nesse caso, aperte `RGB_RESET` para apagar as edições.

Cuidados:

- Cada grupo tem exatamente 27 valores, separados por vírgulas. Com outro número o build falha (veja [Solução de problemas](#solução-de-problemas)).
- Dentro de `LED_SLOTS(...)` use só comentários `/* ... */`. Um comentário `//` apaga o resto da linha depois do pré-processador e as cores seguintes se perdem sem aviso.
- O grupo da esquerda vale só para a metade esquerda, e o da direita só para a direita.

#### Tornar as cores editadas na aba Lights os novos padrões

As cores que você pinta e salva na aba Lights ficam na memória do teclado e valem no lugar das padrão, mas o firmware compilado continua com as cores de `config/led_colors.dtsi`. Para que as cores editadas virem as padrão (por exemplo, para o teclado voltar a elas depois de um `RGB_RESET` ou de um `settings_reset`):

1. Na aba Lights, clique em **Export led_colors.dtsi**. O botão só fica habilitado para este teclado (54 LEDs por camada e as camadas 0 a 5). O arquivo baixado tem a mesma estrutura do `config/led_colors.dtsi` (a paleta, a macro `LED_SLOTS` e um bloco por camada) e as cores de todas as camadas como estão no teclado agora, inclusive as que ainda não foram salvas. Só os comentários de cada linha diferem: os nomes das teclas vêm do teclado e o título de cada camada não tem a cor de destaque.
2. Substitua o `config/led_colors.dtsi` do repositório pelo arquivo baixado.
3. Faça commit e push, baixe o firmware e grave as duas metades.
4. Aperte `RGB_RESET` (camada SYS, posição 23) para apagar os registros salvos, que passaram a ser iguais às cores padrão e não têm mais função. Ele também volta o efeito e o brilho aos valores do keymap.

**Não testada neste teclado.** O arquivo exportado a partir do teclado de demonstração (com as cores padrão deste repositório) foi comparado por script com o `config/led_colors.dtsi`: sem os comentários, os dois têm os mesmos símbolos na mesma ordem (cores, macro e pontuação) e o mesmo número de linhas, então o arquivo exportado sem edições compila nas mesmas cores. A receita inteira (exportar, substituir, gravar) nunca foi feita no teclado.

#### Deixar o efeito aparecer por baixo do mapa de uma camada

Por padrão o mapa de uma camada é opaco: cobre todos os LEDs e o efeito principal fica pausado. Com `opacity` abaixo de 100, o overlay deixa de cobrir tudo: o efeito continua rodando por baixo e o mapa é misturado a ele. **Não testada neste teclado.**

```dts
ov_fn1: ov_fn1 {
    compatible = "keypaw,rgb-overlay";
    condition = <&cond_fn1>;
    all-leds;
    opacity = <70>;             // 70% do mapa e 30% do efeito
    map_fn1: fx_ov_fn1 {
        compatible = "keypaw,rgb-matrix-static";
        #binding-cells = <0>;
        layer-id = <1>;
    };
};
```

- As teclas apagadas (`OFF`) mostram um pouco do efeito, e as demais cores ficam misturadas com a cor do efeito, na proporção de `opacity`.
- Para um efeito aparecer sem nenhum mapa por cima, use `no-overlays` nele (veja [Escolher quais overlays aparecem em cada efeito](#escolher-quais-overlays-aparecem-em-cada-efeito)).

#### Mudar quais LEDs um overlay pinta

Um overlay escolhe seus alvos com estas propriedades (valem para os mapas de camada e para o indicador de Caps Lock):

| Propriedade | Significado |
|---|---|
| `leds = <...>` | índices da fita de LEDs. Serve para LEDs sem tecla, como o underglow (0 a 5) |
| `keys = <...>` | posições de tecla (0 a 41). Vale para as duas metades, porque cada metade resolve a posição pelo seu próprio mapa de LEDs |
| `all-leds;` | pinta todos os LEDs da metade. Não combine com `keys` nem `leds`. Com `opacity` 100, o overlay cobre tudo: o efeito principal e os overlays declarados antes dele nem são desenhados |
| `opacity = <n>` | força da mistura, em %. 100 (padrão) substitui o que estiver embaixo; valores menores misturam |
| `local;` | avalia a condição em cada metade, em vez de na central. Veja a [referência](#referência-de-efeitos-condições-e-overlays) |

`leds` e `keys` podem ser usados juntos. Exemplos:

```dts
// o underglow e as teclas de polegar das duas metades
leds = <0 1 2 3 4 5>;
keys = <36 37 38 39 40 41>;
```

```dts
// Caps Lock em toda a linha do meio das duas metades
keys = <12 13 14 15 16 17 18 19 20 21 22 23>;
```

Para remover o indicador de Caps Lock, apague os nós `ov_caps` (em `rgb_overlays`) e `cond_caps` (em `rgb_conditions`).

#### Adicionar um efeito novo

1. Declare o efeito dentro de `kprgb`, **depois do último**: assim os índices dos efeitos que já existem não mudam.
2. Atribua o efeito a uma tecla. Na camada SYS há teclas transparentes (`&trans`) que podem ser trocadas, por exemplo as três últimas da linha 3 da direita (posições 33 a 35).
3. Faça commit e push, baixe o firmware e grave as duas metades.
4. Aperte `RGB_RESET`.

Exemplo (onda de brilho que atravessa o teclado), **não testado neste teclado**:

```dts
// dentro de kprgb, depois de fx_static
// 9 - onda de brilho da esquerda para a direita
fx_wave: fx_wave {
    compatible = "keypaw,rgb-matrix-breathe";
    #binding-cells = <0>;
    color = <0x00FFFF>;
    duration = <3000>;
    mode = "river";
};
```

```dts
// na camada SYS: troca o primeiro &trans depois de &fx_static
&fx_heatmap     &fx_starlight   &fx_static      &fx_wave        &trans          &trans
```

Mais ideias de efeito, todas só com propriedades (veja os valores em [Referência de efeitos, condições e overlays](#referência-de-efeitos-condições-e-overlays); **não testadas neste teclado**):

| Ideia | Tipo e propriedades |
|---|---|
| Onda de brilho atravessando o teclado | `breathe` com `mode = "river"` |
| Cor oscilando em onda | `breathe` com `mode = "wave"` e `hue-amplitude = <90>` |
| Gradiente fixo de cima para baixo | `solid` com `axis = "vertical"` |
| Arco-íris de cima para baixo | `rainbow` com `basis = "y"` |
| Arco-íris saindo do centro | `rainbow` com `basis = "radial"` |
| Faixa de brilho de uma cor percorrendo as teclas | `rainbow` com `palette = "solid"` |
| Reativo em cruz (linha e coluna da tecla) | `reactive` com `spread = "cross"` |
| Reativo acumulando várias teclas | `reactive` com `multi` |
| Chuva de pixels coloridos | `rain` com `mode = "pixel"` |
| Chuva digital estilo Matrix | `digital-rain` |
| Cada LED com uma cor fixa | `static` com `slot-colors = <...>` (já em uso: `fx_static` e os mapas de camada); `led-colors = <...>`, por LED da fita, só vale quando não há `slot-colors` |

#### Adicionar o mapa de cores de uma camada nova

Depois de criar uma camada no keymap (ela recebe o próximo ID, por exemplo 6), crie a condição, o overlay e o bloco de cores dela. O `layer-id` do mapa é o ID da camada e precisa ser único entre os mapas (de 0 a 14). **Não testada neste teclado.**

```dts
// em config/corne.keymap, dentro de rgb_conditions
cond_game: cond_game {
    compatible = "keypaw,rgb-condition-layer";
    layer = <6>;               // ID da camada no keymap
};
```

```dts
// em config/corne.keymap, dentro de rgb_overlays: depois dos outros mapas de camada
// (para ficar por cima deles) e antes de ov_caps (para o Caps Lock continuar por cima)
ov_game: ov_game {
    compatible = "keypaw,rgb-overlay";
    condition = <&cond_game>;
    all-leds;
    map_game: fx_ov_game {
        compatible = "keypaw,rgb-matrix-static";
        #binding-cells = <0>;
        layer-id = <6>;        // o mesmo ID da camada: identifica o mapa ao editar e salvar
    };
};
```

```dts
// no fim de config/led_colors.dtsi: um grupo de 27 valores para cada metade
&map_game {
    slot-colors = <LED_SLOTS(
        /* esquerda */
        (OFF, OFF, OFF, OFF, OFF, OFF, /* posições 0 a 5 */
         OFF, OFF, OFF, OFF, OFF, OFF, /* posições 12 a 17 */
         OFF, OFF, OFF, OFF, OFF, OFF, /* posições 24 a 29 */
                        OFF, OFF, OFF, /* polegares: posições 36 a 38 */
         RED, RED, RED, RED, RED, RED)/* underglow */,

        /* direita */
        (OFF, OFF, OFF, OFF, OFF, OFF, /* posições 6 a 11 */
         OFF, OFF, OFF, OFF, OFF, OFF, /* posições 18 a 23 */
         OFF, OFF, OFF, OFF, OFF, OFF, /* posições 30 a 35 */
         OFF, OFF, OFF, /* polegares: posições 39 a 41 */
         RED, RED, RED, RED, RED, RED)/* underglow */
    )>;
};
```

Grave as duas metades. A condição `layer` também aceita `only-topmost;`: o mapa só aparece se essa for a camada mais alta ativa (útil para não misturar cores quando duas camadas estão ativas).

#### Dar um efeito próprio ao underglow

Um overlay sem `condition` pinta sempre. Com um efeito filho qualquer, ele dá ao underglow uma animação própria, independente do efeito principal. **Não testada neste teclado.**

```dts
// dentro de rgb_overlays, ANTES de ov_fn1, para que os mapas de camada fiquem por cima
ov_underglow: ov_underglow {
    compatible = "keypaw,rgb-overlay";
    leds = <0 1 2 3 4 5>;
    fx_ov_underglow {
        compatible = "keypaw,rgb-matrix-breathe";
        #binding-cells = <0>;
        color = <0x00FFFF>;
        duration = <4000>;
    };
};
```

Como o efeito de um overlay é privado, as teclas de matiz, saturação e velocidade não mexem nele. Enquanto uma camada de FN1 a MEDIA está ativa, o mapa dela cobre o underglow e esta animação não é desenhada.

#### Escolher quais overlays aparecem em cada efeito

Por padrão, todos os overlays (os mapas de camada e o Caps Lock) são pintados em qualquer efeito. Um efeito pode escolher a própria lista com `overlays`, ou desligá-los com `no-overlays`. É a forma de manter um efeito sempre visível, mesmo nas camadas FN1 a MEDIA:

```dts
fx_rainbow: fx_rainbow {
    // ... propriedades do efeito ...
    no-overlays;                // com este efeito, nenhum overlay é pintado (nem os mapas, nem o Caps Lock)
};

fx_reactive: fx_reactive {
    // ... propriedades do efeito ...
    overlays = <&ov_caps>;      // com este efeito, só o Caps Lock é pintado: os mapas de camada não aparecem
};
```

As entradas de `overlays` não podem se repetir dentro da mesma lista.

#### Salvar a cor e a velocidade ajustadas nas teclas

Acrescente `persist-id` ao efeito. O valor é o nome estável usado para salvar: único entre os efeitos, só com letras, números e `_`, até 31 caracteres.

```dts
fx_solid: fx_solid {
    compatible = "keypaw,rgb-matrix-solid";
    #binding-cells = <0>;
    color = <0xFF0000>;
    persist-id = "solid";
};
```

Com `persist-id`, o matiz, a saturação e a velocidade ajustados nas teclas são salvos (com o atraso de 60 s descrito em [O que é salvo na memória](#o-que-é-salvo-na-memória)) e têm prioridade sobre o `color` e o `duration` do keymap. Para aplicar novos valores do keymap a um efeito que já salvou os seus, aperte `RGB_RESET`.

#### Trocar o mapa dos LEDs

O mapa de cada metade está em `config/corne_left.overlay` e `config/corne_right.overlay`, na propriedade `mapping` do nó `keypaw,rgb-matrix`. Cada entrada, na ordem física da fita, é:

- um número: a posição da tecla sob aquele LED (a numeração de [Posições das teclas](#posições-das-teclas)); ou
- `KP_RGB_NO_KEY(x, y)`: um LED sem tecla (underglow), com coordenadas explícitas.

As coordenadas usam as unidades do layout físico do Corne: 100 é a largura de uma tecla, `x` cresce para a direita e `y` para baixo. A metade esquerda ocupa `x` de 0 a 600 e a direita, de 800 a 1400. Se a fita tiver outro número de LEDs, ajuste também `chain-length` em `config/corne.keymap`. A tabela completa está em [Mapa dos LEDs](#mapa-dos-leds).

Se mudar a ordem da fita, não precisa mexer em `config/led_colors.dtsi`: as cores são por slot, e o slot de um LED sob uma tecla é a posição dela. Se acrescentar ou tirar um LED sem tecla (underglow), atualize o `no-key-slots` do mesmo `.overlay` (um slot para cada entrada `KP_RGB_NO_KEY`, na ordem do `mapping`) e, se o total de slots mudar, o `slot-count` dos dois `.overlay` e a macro `LED_SLOT_ORDER` em `config/led_colors.dtsi` (ela lista os slots em ordem: as posições de tecla de 0 a 41, depois o underglow da esquerda e o da direita).

### Referência de efeitos, condições e overlays

Esta é a lista do que o módulo oferece, não só do que está instalado. Os valores com "(padrão)" são os que valem quando a propriedade é omitida. Imagens e animações de cada efeito estão na [documentação do módulo](https://gudzpoz.github.io/zmk-rgb-matrix/).

**Propriedades comuns de todos os efeitos**

| Propriedade | Tipo | Padrão | Descrição |
|---|---|---|---|
| `color` | cor `0xRRGGBB` | `0xFFFFFF` | cor base do efeito |
| `duration` | inteiro, ms | `0` | período da animação; menor é mais rápido. `0` usa o `initial-duration-ms` do `kprgb` |
| `persist-id` | texto | ausente | liga o salvamento de matiz, saturação e velocidade do efeito |
| `overlays` | lista de overlays | todos | overlays pintados enquanto este efeito está ativo |
| `no-overlays` | booleano | não | não pinta nenhum overlay com este efeito |

**Tipos de efeito** (`compatible = "keypaw,rgb-matrix-<tipo>"`)

| Tipo | Propriedades e valores | O que faz |
|---|---|---|
| `solid` | `axis`: `"none"` (padrão), `"vertical"`, `"horizontal"` | cor única ou gradiente fixo de matiz |
| `breathe` | `mode`: `"brightness"` (padrão), `"river"`, `"hue"`, `"pendulum"`, `"wave"`; `hue-amplitude`: graus (padrão 45) | respiração e variações: onda de brilho ou oscilação de matiz |
| `spectrum` | nenhuma além das comuns | todos os LEDs ciclam juntos pelo espectro |
| `rainbow` | `basis`: `"x"` (padrão), `"y"`, `"radial"`, `"pinwheel"`, `"spiral"`, `"chevron"`, `"flag"`; `direction`: `"out"` (padrão), `"in"`, `"dual"`, `"bloom"`; `palette`: `"rainbow"` (padrão), `"solid"` | gradientes animados em várias formas |
| `band` | `channel`: `"sat"` (padrão), `"val"`; `shape`: `"linear"` (padrão), `"pinwheel"`, `"spiral"` | faixa que percorre o teclado alterando saturação ou brilho |
| `reactive` | `spread`: `"point"` (padrão), `"disc"`, `"cross"`, `"nexus"`; `spread-radius`: unidades do layout (padrão 250); `multi`; `palette`: `"solid"` (padrão), `"gradient"`, `"complement"`; `background-brightness`: % (padrão 10) | reage às teclas pressionadas |
| `ripple` | `background-brightness`: % (padrão 10) | ondas a partir da tecla pressionada |
| `heatmap` | `decrease-delay-ms` (padrão 25), `spread` (padrão 150), `area-limit` (padrão 16), `increase-step` (padrão 32), `slim` | mapa de calor das teclas mais usadas |
| `starlight` | `step-interval-ms` (padrão 32), `smooth`, `dual-hue`, `dual-sat` | brilhos aleatórios |
| `rain` | `mode`: `"pixel"` (padrão), `"flow"`, `"drops"`, `"jellybean"`, `"fractal"`; `step-interval-ms` (padrão 32) | teclas aleatórias com cores aleatórias. O modo `"drops"` precisa de uma `color` saturada para aparecer |
| `digital-rain` | nenhuma além das comuns (`color` para um matiz que não seja verde; `duration` é o tempo de queda) | colunas caindo, estilo Matrix |
| `static` | `slot-colors`: lista de cores `0xRRGGBB`, um valor por slot; `layer-id`: ID da camada (0 a 14), que torna o mapa editável e salvável pelo ZMK Studio; `led-colors`: lista por LED na ordem da fita, usada só sem `slot-colors` | cores fixas por slot (ou por LED, no caso de `led-colors`). Aqui o `slot-colors` vem de `config/led_colors.dtsi` |

**Nó `keypaw,rgb-matrix`** (um por metade, em `config/corne_left.overlay` e `config/corne_right.overlay`)

| Propriedade | Significado |
|---|---|
| `strip` | a fita de LEDs (`&led_strip`) |
| `physical-layout` | o layout físico das teclas (`&foostan_corne_6col_layout`) |
| `mapping` | os LEDs na ordem da fita: a posição da tecla, ou `KP_RGB_NO_KEY(x, y)` para um LED sem tecla |
| `slot-count` | tamanho do espaço de slots de cor, igual nas duas metades (54 aqui; no máximo 60) |
| `no-key-slots` | o slot de cada LED sem tecla, na ordem do `mapping` |

**Condições** (`compatible = "keypaw,rgb-condition-<tipo>"`, declaradas em `rgb_conditions`)

| Tipo | Propriedades | Fica ativa quando |
|---|---|---|
| `always` | nenhuma | sempre |
| `caps-lock` | nenhuma | o computador informa Caps Lock ligado |
| `layer` | `layer` (índice, obrigatório); `only-topmost` | a camada está ativa. Com `only-topmost`, só se for a camada mais alta ativa |
| `ble` | `profile`: índice do perfil, ou `-1` para qualquer (padrão); `state`: `"any"` (padrão), `"connected"`, `"disconnected"`, `"open"` | o perfil Bluetooth ativo atende ao teste. `open` é um perfil sem pareamento |
| `latch` | nenhuma (usa um filho `keypaw,behavior-rgb-overlay-toggle`, cujo nome de nó deve ter no máximo 8 caracteres) | uma tecla a liga e desliga. O estado é volátil e por metade |
| `and`, `or` | `conditions`: lista de condições | todas (`and`) ou pelo menos uma (`or`) das condições da lista está ativa |

**Overlays** (declarados em `rgb_overlays`)

| Tipo | Propriedades | O que faz |
|---|---|---|
| `keypaw,rgb-overlay` | `condition` (opcional; sem ela pinta sempre) e as propriedades comuns; exige exatamente um efeito filho | pinta o efeito filho sobre os LEDs alvo enquanto a condição for verdadeira |
| `keypaw,rgb-overlay-battery` | `condition`, `color` (padrão `0x00FF00`), `background-color` (padrão `0x000000`), `reverse` e as propriedades comuns | desenha uma barra com a carga da bateria da própria metade nos LEDs alvo. Costuma ser combinado com uma condição `latch` para ligar e desligar por tecla. **Não instalado neste repositório** |

Propriedades comuns dos overlays: `keys`, `leds`, `all-leds`, `opacity` (padrão 100) e `local`. Sem `local`, a condição é avaliada na metade central e o resultado é enviado à periférica; com `local`, cada metade avalia a sua própria condição. Um overlay com `all-leds` e `opacity` 100 cobre todos os LEDs: o efeito principal e os overlays declarados antes dele nem são desenhados.

### Mapa dos LEDs

A fita de cada metade tem 27 LEDs. Os LEDs de 0 a 5 são o underglow e os de 6 a 26 ficam sob as teclas. Os números abaixo são o **índice do LED** sob cada tecla (gerados a partir dos arquivos `.overlay`):

```text
Esquerda                      Direita
  24  23  18  17  10   9         9  10  17  18  23  24
  25  22  19  16  11   8         8  11  16  19  22  25
  26  21  20  15  12   7         7  12  15  20  21  26
              14  13   6         6  13  14
```

A ordem da fita, de dentro para fora, é a mesma nas duas metades (a direita é o espelho da esquerda):

| LEDs | Esquerda | Direita |
|---|---|---|
| 6 | polegar interno (SPACE) | polegar interno (ENTER) |
| 7 a 9 | coluna interna, de baixo para cima (B G T) | coluna interna, de baixo para cima (N H Y) |
| 10 a 12 | coluna seguinte, de cima para baixo (R F V) | coluna seguinte, de cima para baixo (U J M) |
| 13 | polegar do meio (FN1) | polegar do meio (RAISE) |
| 14 | polegar externo (LGUI) | polegar externo (RALT) |
| 15 a 17 | C D E | `,` K I |
| 18 a 20 | W S X | O L `.` |
| 21 a 23 | Z A Q | `[` `;` P |
| 24 a 26 | coluna externa, de cima para baixo (TAB LSHIFT LCTRL) | coluna externa, de cima para baixo (BSPC `'` `]`) |

Underglow (LEDs 0 a 5), com coordenadas em unidades do layout (100 é a largura de uma tecla):

| LED | Esquerda (x, y) | Direita (x, y) |
|---|---|---|
| 0 | 550, 144 | 850, 144 |
| 1 | 344, 126 | 1056, 126 |
| 2 | 144, 168 | 1256, 168 |
| 3 | 144, 273 | 1256, 273 |
| 4 | 344, 332 | 1056, 332 |
| 5 | 550, 356 | 850, 356 |

Os mapas de cores por camada ([Cores por camada e indicador de Caps Lock](#cores-por-camada-e-indicador-de-caps-lock)) guardam as cores por slot, não por LED: o slot de cada LED está em [Slots de cor](#slots-de-cor). O LED sob uma tecla usa a posição da tecla como slot, e os de underglow usam os slots 42 a 47 na esquerda e 48 a 53 na direita.

## Telas OLED

As telas usam o módulo [zmk-nice-oled](https://github.com/lenerdz/zmk-nice-oled) (widgets na vertical), a partir de um fork que o adapta ao ZMK `main` (veja [Por que existem os forks](#por-que-existem-os-forks)). A opção `CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM=y` ativa essa tela, e os widgets nativos do ZMK ficam desligados porque conflitam com ela.

### O que cada tela mostra

- **Metade esquerda (central)**: saída ativa (USB ou Bluetooth, com ícone próprio para perfil sem pareamento e sem conexão), porcentagem de bateria (com indicação de carregamento por USB), perfil Bluetooth ativo, velocidade de digitação (velocímetro, número e gráfico) e o nome da camada ativa (o `display-name` de cada camada no keymap: QWERTY, FN1, RAISE, NAV, SYS e MEDIA).
- **Metade direita (periférica)**: animação do gato, porcentagem de bateria e o estado da conexão Bluetooth com a metade esquerda.

As telas **nunca apagam** (`CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=n`), nem no USB nem na bateria.

### Opções de configuração das telas

As opções ficam em `config/corne.conf`:

| Opção | Valor | O que faz |
|---|---|---|
| `CONFIG_ZMK_DISPLAY` | `y` | liga o suporte a telas |
| `CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM` | `y` | usa a tela do zmk-nice-oled |
| `CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE` | `n` | a tela nunca apaga por inatividade |
| `CONFIG_ZMK_WIDGET_LAYER_STATUS`, `CONFIG_ZMK_WIDGET_BATTERY_STATUS`, `CONFIG_ZMK_WIDGET_OUTPUT_STATUS`, `CONFIG_ZMK_WIDGET_WPM_STATUS`, `CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS` | `n` | desligam os widgets nativos do ZMK, que conflitam com o zmk-nice-oled |
| `CONFIG_ZMK_DISPLAY_DEDICATED_THREAD_STACK_SIZE` | `4096` | pilha da thread da tela. O LVGL 9 precisa de mais que o valor antigo (2560): com ele a metade periférica travava (hard fault) |
| `CONFIG_NICE_OLED_WIDGET_WPM_BONGO_CAT` | `n` | desliga o gato da tela esquerda para dar lugar ao velocímetro e ao gráfico |
| `CONFIG_NICE_OLED_WIDGET_WPM_GRAPH` | `y` | gráfico de WPM |
| `CONFIG_NICE_OLED_WIDGET_WPM_SPEEDOMETER` | `y` | velocímetro de WPM |
| `CONFIG_NICE_OLED_WIDGET_WPM_NUMBER` | `y` | número de WPM |
| `CONFIG_NICE_OLED_WIDGET_ANIMATION_PERIPHERAL_WPM` | `n` | o WPM na metade periférica exige um módulo extra (zmk-wpm-peripheral) |
| `CONFIG_NICE_OLED_WIDGET_MODIFIERS_INDICATORS` | `n` | sem indicadores de modificadores |

O `corne.conf` tem ainda `CONFIG_ZMK_BLE=y`, `CONFIG_BT_MAX_CONN=5`, `CONFIG_BT_MAX_PAIRED=5`, `CONFIG_ZMK_SLEEP=n` e `CONFIG_ZMK_HID_REPORT_TYPE_NKRO=y`, descritos em [Funções e recursos](#funções-e-recursos).

Todas as opções `CONFIG_NICE_OLED_*`, com padrões e descrições, estão no [README do fork em português](https://github.com/lenerdz/zmk-nice-oled/blob/zmk-main/README.pt-BR.md). Por exemplo, `CONFIG_NICE_OLED_WIDGET_CENTRAL_SHOW_BATTERY_PERIPHERAL_AND_CENTRAL=y` mostra a bateria das duas metades na tela esquerda (**não testada neste teclado**).

Ao compilar a metade direita aparecem avisos do Kconfig sobre os widgets de WPM do `nice_oled`: são esperados, porque esses widgets só existem na metade central.

## Compilar e gravar o firmware

### Compilar

O workflow `.github/workflows/build.yml` roda a cada push, a cada pull request e manualmente (aba **Actions**, workflow **Build ZMK firmware**, botão **Run workflow**). Ele chama o workflow de build do próprio ZMK, fixado no mesmo commit do ZMK de `config/west.yml`, e compila três firmwares definidos em `build.yaml`:

| Artefato | Shield | Observações |
|---|---|---|
| `corne_left` | `corne_left nice_oled` | snippet `studio-rpc-usb-uart` e `-DCONFIG_ZMK_STUDIO=y` (ZMK Studio), mais as opções de `config/corne_left.conf` (buffer de recepção do ZMK Studio) |
| `corne_right` | `corne_right nice_oled` | metade periférica |
| `settings_reset` | `settings_reset` | limpa as configurações salvas |

Todos usam a placa `nice_nano//zmk`.

### Baixar os arquivos de gravação

Na página da execução no GitHub, baixe o artefato **firmware** (um zip). Ele contém `corne_left.uf2`, `corne_right.uf2` e `settings_reset.uf2`.

Pela linha de comando, com a GitHub CLI (`gh`) autenticada, dentro do repositório:

```powershell
gh run list --limit 5
gh run download <ID-da-execução> -D firmware-novo
```

Os arquivos ficam em `firmware-novo/firmware/`.

### Gravar as metades

1. Conecte a metade ao computador por USB.
2. Dê dois toques rápidos no botão de reset do nice!nano. Um drive chamado **NICENANO** aparece.
3. Copie o arquivo `.uf2` correspondente para o drive: `corne_left.uf2` na esquerda e `corne_right.uf2` na direita. A metade reinicia sozinha e o drive some.
4. Repita na outra metade.

Grave **as duas metades** sempre que mudar efeitos, condições, overlays ou o keymap: o módulo de luzes exige que as duas tenham as mesmas definições.

### Limpar as configurações salvas (settings_reset)

O `settings_reset.uf2` apaga tudo o que o teclado guardou: pareamentos Bluetooth, o estado das luzes (inclusive as cores editadas e salvas pela aba Lights) e as alterações salvas pelo ZMK Studio. Use quando houver comportamento estranho depois de uma atualização grande, problema de pareamento entre as metades ou entre o teclado e o computador, ou para descartar as edições do Studio.

1. Grave o `settings_reset.uf2` nas **duas** metades.
2. Grave `corne_left.uf2` e `corne_right.uf2` nas respectivas metades.
3. Remova o teclado da lista de dispositivos Bluetooth do computador e pareie de novo.

## Módulos, forks e versões fixadas

### Versões fixadas

`config/west.yml` fixa tudo em commits exatos para que o build seja reproduzível:

| Componente | Origem | Revisão fixada | Observação |
|---|---|---|---|
| ZMK | `zmkfirmware/zmk`, branch `main` | `4dd95d7840eb3d5a3f59bb29fbf1ab054715ef85` (2026-10-09) | Zephyr 4.1. O mesmo commit é usado no `ref` de `.github/workflows/build.yml` |
| zmk-rgb-matrix | `lenerdz/zmk-rgb-matrix`, branch `corne-fixes` | `c4bf112fe47bc5c93da310acfd6c2c92dbbe6874` | upstream `gudzpoz/zmk-rgb-matrix` em `a9add03` (2026-10-08) mais duas correções e os mapas de cor editáveis |
| zmk-nice-oled | `lenerdz/zmk-nice-oled`, branch `zmk-main` | `479a516e01c942df79567475e424de4d1560e28c` | PR #37 do upstream (`de5b2af`) mais a correção do transporte `NONE` |
| zmk-studio-messages | `lenerdz/zmk-studio-messages`, branch `main` | `cfcce43b2156151fcd09902de1f4887be387b905` | `zmkfirmware/zmk-studio-messages` em `6cb4c28` (o commit que o ZMK fixa) mais as requisições dos mapas de cor. Substitui o módulo de mesmo nome que o ZMK importa |

A ponta da branch `zmk-main` (`ae83011`) tem um commit a mais, só de documentação (`README.pt-BR.md`); o pin não foi movido para ele para que o firmware compilado continue idêntico. A ponta da `corne-fixes` (`c4bf112`) e a da `main` do fork do protocolo (`cfcce43`) são os próprios pins.

O app web ZMK Studio do fork `lenerdz/zmk-studio` não aparece no `west.yml`: ele não faz parte do firmware. Veja [Por que existem os forks](#por-que-existem-os-forks).

### Por que existem os forks

**zmk-rgb-matrix** (fork `lenerdz/zmk-rgb-matrix`, branch `corne-fixes`): o fork tem duas correções de problemas do upstream, cada uma com a própria branch para poder ser enviada ao autor, e um recurso novo:

1. `fix/behavior-metadata-sets-type` (`98070e1`): o tipo do vetor `sets[]` em `behavior_rgb_matrix.c` causava erro de compilação quando o ZMK Studio está ligado (o build da metade esquerda).
2. `fix/physical-layout-lookup` (`2c1ecbe`): `kp_rgb_matrix_layout_init()` usava o primeiro layout físico da lista (o do Corne de 5 colunas, com 36 teclas) em vez do layout indicado em `physical-layout` (6 colunas, 42 teclas). Com isso, as teclas de polegar (posições 36 a 41) eram ignoradas pelos efeitos que dependem de posição e as outras teclas recebiam coordenadas erradas.
3. Mapas de cor editáveis (`6ebecb4`, mais `cfc69e4`, que faz a compilação falhar se o buffer de recepção do ZMK Studio for menor que 256 bytes; só na `corne-fixes`, não foi proposto ao upstream): slots de cor iguais nas duas metades, mapas que podem ser editados e salvos na memória da central, sincronização da metade direita e as requisições do ZMK Studio. O commit seguinte (`c4bf112`) só acrescenta a documentação (`README.md` e `README.pt-BR.md`). Veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio).

A branch `corne-fixes` reúne as duas correções e o recurso novo. O módulo ainda ignora a rotação das teclas de polegar (diferença pequena nas coordenadas).

**zmk-nice-oled** (fork `lenerdz/zmk-nice-oled`, branch `zmk-main`): a `main` do upstream (`mctechnology17/zmk-nice-oled`) mira o ZMK 0.3 e o LVGL 8. O [PR #37](https://github.com/mctechnology17/zmk-nice-oled/pull/37), de tokyo2006, migra o módulo para o ZMK `main` (Zephyr 4.1 e LVGL 9). A branch `zmk-main` do fork é esse PR mais uma correção: no ZMK `main`, a função que escolhe a saída devolve `ZMK_TRANSPORT_NONE` enquanto o USB não está pronto e o perfil Bluetooth ativo não está conectado, e o widget deixava o ícone de saída em branco nesse estado. Agora ele desenha o ícone de perfil sem pareamento ou sem sinal.

**zmk-studio-messages** (fork `lenerdz/zmk-studio-messages`, branch `main`): o ZMK traz o protocolo do ZMK Studio como o módulo `zmk-studio-messages`, importado de `app/west.yml`, e o `config/west.yml` o substitui, com o mesmo nome e caminho, pelo fork. O fork parte do commit `6cb4c28`, o mesmo que o ZMK fixa, e acrescenta ao subsistema `keymap` as requisições e a notificação dos mapas de cor, com identificadores a partir de 100 para não colidir com os do upstream. O ZMK compila o protocolo junto com o firmware, então o módulo zmk-rgb-matrix usa as mensagens novas direto; o fork do app web traz um cliente TypeScript gerado a partir do mesmo protocolo (`src/vendor/zmk-studio-ts-client`) e é por ele que usa as mensagens novas. Veja o [README](https://github.com/lenerdz/zmk-studio-messages/blob/main/README.md) e o [README em português](https://github.com/lenerdz/zmk-studio-messages/blob/main/README.pt-BR.md) do fork.

**zmk-studio** (fork `lenerdz/zmk-studio`, branch `main`): é o app web do ZMK Studio, e não faz parte do firmware nem do `west.yml`. O fork parte de `zmkfirmware/zmk-studio` no commit `1bb6bb8` e acrescenta: o desenho das teclas (ícones e rótulos para Bluetooth, luzes, camadas e teclas de mídia); a aba **Lights**, que edita as cores dos mapas de cor (veja [Editar as cores na aba Lights](#editar-as-cores-na-aba-lights)), com um cliente TypeScript do protocolo estendido copiado para dentro do repositório (`src/vendor/zmk-studio-ts-client`, gerado a partir do `lenerdz/zmk-studio-messages` na revisão `cfcce43`), um teclado de demonstração e testes automáticos (`npm test`); os avisos de "fork não oficial"; e a hospedagem no GitHub Pages (workflow `pages.yml`, que roda os testes antes de publicar), em <https://lenerdz.github.io/zmk-studio/>. A ponta da `main` do fork é `d914e25`. Os workflows `release-please` e `tauri-build` do upstream estão desativados nas configurações do fork. Veja o [README](https://github.com/lenerdz/zmk-studio/blob/main/README.md) e o [README em português](https://github.com/lenerdz/zmk-studio/blob/main/README.pt-BR.md) do fork.

### Atualizar uma versão ou voltar ao upstream

Para atualizar um módulo:

1. Descubra o commit desejado (o hash completo). Para a ponta de uma branch de um fork:

   ```powershell
   git ls-remote https://github.com/lenerdz/zmk-rgb-matrix corne-fixes
   ```

2. Troque o `revision:` correspondente em `config/west.yml`. Para o ZMK, troque também o ref de `uses:` em `.github/workflows/build.yml`: os dois precisam apontar para o mesmo commit.
3. Faça push e confirme que o build passa.

Para voltar ao upstream quando o autor aceitar as correções, acrescente o remote dele em `config/west.yml` (por exemplo `gudzpoz` com `url-base: https://github.com/gudzpoz`, ou `mctechnology17` com `url-base: https://github.com/mctechnology17`) e aponte o projeto para ele.

## Solução de problemas

| Sintoma | Causa e solução |
|---|---|
| Mudei o `.keymap` e as teclas não mudaram | Se você já editou teclas pelo ZMK Studio, o Studio tem prioridade. Use "Restore Stock Settings" no Studio ou grave o `settings_reset` nas duas metades e depois o firmware |
| A tecla do efeito `static` (camada SYS, posição 32) não aparece no teclado | O mesmo caso da linha anterior: se você já editou teclas pelo Studio, atribua `fx_static` a uma tecla pelo próprio Studio ou use "Restore Stock Settings" |
| A cor ou a velocidade que ajustei nas teclas voltou depois de reiniciar | Sem `persist-id`, matiz, saturação e velocidade não são salvos. Veja [Salvar a cor e a velocidade ajustadas nas teclas](#salvar-a-cor-e-a-velocidade-ajustadas-nas-teclas) |
| O efeito ou o brilho voltou ao anterior depois de desligar o teclado | O estado é gravado 60 s depois da última alteração. Espere um minuto antes de desligar |
| Mudei `initial-effect` ou `initial-brightness` e nada mudou | O estado salvo tem prioridade sobre os valores iniciais. Aperte `RGB_RESET` (camada SYS, posição 23) depois de gravar |
| Troquei efeitos ou overlays e o comportamento ficou estranho (efeito errado, luzes que não ligam) | Grave as duas metades e aperte `RGB_RESET` (camada SYS, posição 23). Confira se as duas metades receberam o mesmo firmware |
| As luzes apagam sozinhas | É o padrão do módulo (apagam após 30 s sem digitar). Veja [Manter as luzes acesas quando o teclado fica ocioso](#manter-as-luzes-acesas-quando-o-teclado-fica-ocioso) |
| As teclas de polegar não reagem aos efeitos reativos | Corrigido no fork `corne-fixes`. Se voltar a acontecer, confira se `config/west.yml` aponta para o fork e não para o upstream |
| O ícone de saída da tela esquerda fica em branco com o teclado desconectado | Corrigido na branch `zmk-main` do fork do zmk-nice-oled (commit `479a516` ou posterior). Confira o pin em `config/west.yml` |
| Erros de link como `multiple definition` ou `undefined reference` depois de mexer em widgets | Mantenha os widgets nativos desligados (`CONFIG_ZMK_WIDGET_*_STATUS=n`) e use apenas o fork `zmk-main` do zmk-nice-oled: a `main` do upstream não é compatível com o ZMK `main` |
| A metade periférica trava ao ligar a tela | Não reduza `CONFIG_ZMK_DISPLAY_DEDICATED_THREAD_STACK_SIZE` abaixo de `4096` |
| A metade direita não conecta à esquerda ou há pareamento estranho | Grave o `settings_reset` nas duas metades, depois o firmware em cada uma, e pareie o teclado de novo no computador |
| O build falha ao baixar um módulo | O commit fixado em `config/west.yml` não existe mais (branch reescrita) ou o hash está errado. Confira com `git ls-remote` |
| O build falha com erro de macro em `config/led_colors.dtsi` (algo como `macro "LED_SLOT_ORDER" requires 54 arguments, but only 53 given` ou `passed 55 arguments, but takes just 54`) | Um grupo de `LED_SLOTS` não tem exatamente 27 valores (21 teclas e 6 de underglow). Confira as vírgulas e os parênteses |
| Faltam cores em uma camada depois de editar `config/led_colors.dtsi` | Dentro de `LED_SLOTS(...)` só valem comentários `/* ... */`. Um comentário `//` apaga o resto da linha e as cores seguintes se perdem sem aviso |
| Mudei uma cor em `config/led_colors.dtsi` e a tecla continua com a cor antiga | Se a cor desse slot foi editada e salva pelo ZMK Studio, ela vale no lugar da padrão. Aperte `RGB_RESET` (camada SYS, posição 23) para apagar as edições. **Não testado neste teclado** |
| O build falha com `slot-colors has more entries than the matrix has slots` | O nó `keypaw,rgb-matrix` do `.overlay` da metade não tem `slot-count` (ou ele é menor que a lista). Os dois `.overlay` precisam de `slot-count = <54>;` |
| O build falha com `zmk_keymap_Request_get_led_info_tag` (ou outro nome `zmk_keymap_..._led_...`) não declarado | O módulo usa as requisições do fork do protocolo: o `config/west.yml` precisa substituir o `zmk-studio-messages` do ZMK pelo fork `lenerdz/zmk-studio-messages` (veja [Módulos, forks e versões fixadas](#módulos-forks-e-versões-fixadas)) |
| Aviso `no-key-slots lists N slots for M LEDs that are not under a key` no log do teclado | O `no-key-slots` do `.overlay` precisa de um slot para cada LED sem tecla (cada entrada `KP_RGB_NO_KEY` do `mapping`). Confira o `.overlay` da metade |
| A aba Lights não aparece no app | Ela só aparece depois de desbloquear o teclado (`&studio_unlock`) e com um firmware que tem os mapas editáveis, e só no [fork do app](https://lenerdz.github.io/zmk-studio/): o app oficial não tem a aba. Com outro firmware (sem o fork do protocolo ou sem o módulo zmk-rgb-matrix do fork) o teclado responde "RPC not found" à primeira requisição e o app não oferece a aba. Confira o `config/west.yml` e grave a metade esquerda. **Não testado neste teclado** |
| Pintei LEDs na aba Lights e o teclado não mudou, ou o app avisou que as cores não puderam ser definidas | Confira se a metade esquerda foi compilada com `CONFIG_ZMK_STUDIO_RPC_RX_BUF_SIZE=256` (`config/corne_left.conf`): com o padrão do ZMK (30 bytes) os pedidos de edição chegam cortados e o log do teclado mostra `Dropping incoming RPC byte, insufficient room in the RX buffer`. **Não testado neste teclado**: baseado no código do ZMK |
| O build da metade esquerda falha com `ZMK Studio would drop the bytes of a set_led_colors request` | O `config/corne_left.conf` foi apagado ou não está sendo aplicado: ele precisa ter `CONFIG_ZMK_STUDIO_RPC_RX_BUF_SIZE=256` (ou mais). O módulo zmk-rgb-matrix confere esse valor de propósito |
| As cores que pintei na aba Lights sumiram depois de reiniciar o teclado | A edição vale só até desligar, a não ser que você clique em **Save** (canto superior direito do app). Elas também são apagadas por "Restore Stock Settings", por `RGB_RESET` e pelo `settings_reset` |
| Pinto na aba Lights e só a metade esquerda muda | A metade direita recebe as edições da esquerda por Bluetooth, um slot a cada 50 ms, e só depois de conectar. Confira se as duas metades estão ligadas, conectadas e com o firmware da mesma compilação. **Não testado neste teclado** |
| Avisos do Kconfig sobre widgets de WPM no build da metade direita | Esperados: esses widgets só existem na metade central |

## Manter este README atualizado

Este README é a documentação do projeto e deve acompanhar o repositório: **sempre que algo for adicionado, alterado, atualizado ou removido, atualize a seção correspondente na mesma mudança.** Existe uma regra do Cursor (`.cursor/rules/readme-sync.mdc`) que faz o assistente fazer isso a cada mudança.

| O que mudou | Seção a revisar |
|---|---|
| Teclas, camadas ou nomes de camada em `config/corne.keymap` | [Teclado: posições, camadas e funções](#teclado-posições-camadas-e-funções) e as cores da camada em `config/led_colors.dtsi` ([Cores por camada e indicador de Caps Lock](#cores-por-camada-e-indicador-de-caps-lock)) |
| Efeitos (`kprgb`, `fx_*`), brilhos, condições ou overlays em `config/corne.keymap` | [Luzes](#luzes-rgb-por-tecla-e-underglow) |
| `config/corne_left.overlay` ou `config/corne_right.overlay` | [Mapa dos LEDs](#mapa-dos-leds), [Slots de cor](#slots-de-cor) e, se o `mapping`, o `slot-count` ou o `no-key-slots` mudarem, a macro `LED_SLOT_ORDER` em `config/led_colors.dtsi` |
| `config/led_colors.dtsi` (cores, paleta, ordem dos slots) | [Cores por camada e indicador de Caps Lock](#cores-por-camada-e-indicador-de-caps-lock), [Slots de cor](#slots-de-cor) e as receitas do [Guia de configuração](#guia-de-configuração) que mostram trechos do arquivo |
| Fork do protocolo (`lenerdz/zmk-studio-messages`), `src/studio_rpc.c`, `src/rgb_maps.c` ou `src/rgb_split_sync.c` do zmk-rgb-matrix | [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio) (requisições, IDs e limites) e [Módulos, forks e versões fixadas](#módulos-forks-e-versões-fixadas) |
| `config/corne.conf` ou `config/corne_left.conf` | [Telas OLED](#telas-oled), [Funções e recursos](#funções-e-recursos), [ZMK Studio](#zmk-studio) (buffer de recepção) e [O que é salvo na memória](#o-que-é-salvo-na-memória) |
| `config/west.yml` ou `.github/workflows/build.yml` | [Módulos, forks e versões fixadas](#módulos-forks-e-versões-fixadas) |
| `build.yaml` | [Compilar e gravar o firmware](#compilar-e-gravar-o-firmware) |
| Arquivo criado, movido ou removido | [Estrutura do repositório](#estrutura-do-repositório) |
| Fork do app ZMK Studio (`lenerdz/zmk-studio`): ícones, aba Lights, hospedagem ou commit | [ZMK Studio](#zmk-studio), [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio) e [Módulos, forks e versões fixadas](#módulos-forks-e-versões-fixadas) |
| Problema encontrado ou resolvido | [Solução de problemas](#solução-de-problemas) |

## Referências

- ZMK: [documentação](https://zmk.dev/docs), [ZMK Studio](https://zmk.dev/docs/features/studio) e [Caps Word](https://zmk.dev/docs/keymaps/behaviors/caps-word).
- zmk-rgb-matrix: [upstream](https://github.com/gudzpoz/zmk-rgb-matrix) e [documentação](https://gudzpoz.github.io/zmk-rgb-matrix/); [fork](https://github.com/lenerdz/zmk-rgb-matrix) e seu [README em português](https://github.com/lenerdz/zmk-rgb-matrix/blob/corne-fixes/README.pt-BR.md), com a seção [Slots de cor e mapas de cores editáveis](https://github.com/lenerdz/zmk-rgb-matrix/blob/corne-fixes/README.pt-BR.md#slots-de-cor-e-mapas-de-cores-editáveis).
- zmk-nice-oled: [upstream](https://github.com/mctechnology17/zmk-nice-oled), [PR #37](https://github.com/mctechnology17/zmk-nice-oled/pull/37); [fork](https://github.com/lenerdz/zmk-nice-oled) e seu [README em português](https://github.com/lenerdz/zmk-nice-oled/blob/zmk-main/README.pt-BR.md).
- zmk-studio-messages: [upstream](https://github.com/zmkfirmware/zmk-studio-messages); [fork](https://github.com/lenerdz/zmk-studio-messages) e seu [README em português](https://github.com/lenerdz/zmk-studio-messages/blob/main/README.pt-BR.md).
- zmk-studio: [upstream](https://github.com/zmkfirmware/zmk-studio); [fork](https://github.com/lenerdz/zmk-studio), seu [README em português](https://github.com/lenerdz/zmk-studio/blob/main/README.pt-BR.md), a [documentação da aba Lights](https://github.com/lenerdz/zmk-studio/blob/main/src/lights/README.md) (em inglês) e o [app publicado](https://lenerdz.github.io/zmk-studio/).
- Este repositório: [lenerdz/corne-zmk](https://github.com/lenerdz/corne-zmk).
