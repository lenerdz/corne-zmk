# Corne ZMK

Configuração de firmware [ZMK](https://zmk.dev) para um teclado **Corne split** com **RGB por tecla**, **underglow**, **telas OLED verticais**, **ZMK Studio** e **estenotipia** para o Plover (por teclas comuns ou por acordes enviados por uma porta serial USB). O firmware é compilado pelo GitHub Actions a cada push: não é preciso instalar nada no computador para gerar os arquivos de gravação.

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
  - [Modo de estenotipia (Plover)](#modo-de-estenotipia-plover)
    - [Como ligar e desligar](#como-ligar-e-desligar)
    - [Teclas da camada STENO](#teclas-da-camada-steno)
    - [Outras formas de ter estenotipia no teclado](#outras-formas-de-ter-estenotipia-no-teclado)
  - [Estenotipia por acordes (Gemini PR)](#estenotipia-por-acordes-gemini-pr)
    - [Configurar o Plover](#configurar-o-plover)
    - [Teclas da camada GEMINI](#teclas-da-camada-gemini)
    - [Como funciona por dentro](#como-funciona-por-dentro)
  - [ZMK Studio](#zmk-studio)
    - [Ícones nas teclas (fork do app)](#ícones-nas-teclas-fork-do-app)
    - [Arrastar teclas (fork do app)](#arrastar-teclas-fork-do-app)
- [Luzes (RGB por tecla e underglow)](#luzes-rgb-por-tecla-e-underglow)
  - [Como as luzes funcionam](#como-as-luzes-funcionam)
  - [Controles no dia a dia](#controles-no-dia-a-dia)
  - [Efeitos instalados](#efeitos-instalados)
  - [Cores por camada e indicador de Caps Lock](#cores-por-camada-e-indicador-de-caps-lock)
  - [Animações do underglow](#animações-do-underglow)
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
  - [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display)
    - [Usar a aba Display](#usar-a-aba-display)
    - [As seis configurações](#as-seis-configurações)
    - [Apagar a tela](#apagar-a-tela)
    - [Memória e metade direita](#memória-e-metade-direita)
    - [O que continua só na compilação](#o-que-continua-só-na-compilação)
  - [Opções de configuração das telas](#opções-de-configuração-das-telas)
    - [Opções das duas telas](#opções-das-duas-telas)
    - [Tela esquerda (central)](#tela-esquerda-central)
    - [Tela direita (periférica)](#tela-direita-periférica)
    - [Aviso das luzes (toast)](#aviso-das-luzes-toast)
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

- **8 camadas** no padrão do ZMK Studio: QWERTY, FN1, RAISE, NAV, SYS, MEDIA, STENO e GEMINI. Veja [Camadas](#camadas).
- **Modo de estenotipia**: a camada STENO troca o QWERTY pelas teclas que o [Plover](https://github.com/openstenoproject/plover) lê como uma máquina de estenotipia, e dois macros (`&steno_on` e `&steno_off`) trocam de camada e ligam ou suspendem o Plover (não testado neste teclado). Veja [Modo de estenotipia (Plover)](#modo-de-estenotipia-plover).
- **Estenotipia por acordes (Gemini PR)**: a camada GEMINI não digita letras: o teclado junta as teclas de cada acorde e manda o acorde inteiro ao Plover por uma segunda porta serial USB, no protocolo Gemini PR. Com o Plover fechado nada é escrito, e só funciona por USB (não testado neste teclado). Veja [Estenotipia por acordes (Gemini PR)](#estenotipia-por-acordes-gemini-pr).
- **RGB por tecla**: os 27 LEDs de cada metade são controlados pelo módulo zmk-rgb-matrix, com 9 efeitos, troca direta de efeito por teclas na camada SYS, um **mapa de cores por LED em cada camada** (as teclas acendem pela função e o underglow pela camada), indicador de Caps Lock e **animações do underglow** que cinco teclas da camada SYS ligam e desligam sem mexer no efeito das teclas (não testado neste teclado). As cores de cada mapa podem ser **editadas e salvas no teclado**, sem recompilar, pela aba **Lights** do fork do app do ZMK Studio (funcionou no teclado, segundo o dono). Veja [Luzes](#luzes-rgb-por-tecla-e-underglow) e [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio).
- **Telas OLED verticais** (nice!oled), com uma configuração para cada metade: a esquerda mostra a saída (USB ou Bluetooth), a bateria das duas metades (não testado neste teclado), o perfil Bluetooth, a velocidade de digitação e a camada ativa; a direita mostra a animação do gato, a bateria e a conexão e, por um instante a cada mudança nas luzes (efeito, brilho, cor), um aviso com o que mudou (não testado neste teclado). Por padrão as telas ficam sempre ligadas; o contraste de cada tela, quando elas apagam e o aviso das luzes podem ser mudados sem recompilar na aba **Display** do ZMK Studio (não testado neste teclado). Veja [Telas OLED](#telas-oled) e [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display).
- **ZMK Studio** na metade esquerda (USB) para editar teclas sem recompilar, com um [fork do app](https://github.com/lenerdz/zmk-studio) que desenha ícones nas teclas de Bluetooth, luzes, camadas e do modo de estenotipia, deixa **arrastar uma tecla sobre outra** para trocá-las e tem as abas **Lights**, para editar as cores das luzes, e **Display**, para configurar as telas (não testado neste teclado). Veja [ZMK Studio](#zmk-studio).
- **Bluetooth com 5 perfis**, **NKRO** e **Caps Word**. Veja [Funções e recursos](#funções-e-recursos).
- **Build automático** pelo GitHub Actions, com versões fixadas do ZMK e dos módulos para que o resultado seja reproduzível. Veja [Compilar e gravar o firmware](#compilar-e-gravar-o-firmware) e [Módulos, forks e versões fixadas](#módulos-forks-e-versões-fixadas).

## Estrutura do repositório

```text
.
├── .github/workflows/build.yml   CI: chama o workflow de build do ZMK (fixado em um commit)
├── boards/shields/.gitkeep       pasta vazia reservada para shields próprios
├── build.yaml                    matriz de builds: placas, shields, snippets e nomes dos artefatos
├── config/
│   ├── corne.keymap              teclas (inclusive as `&stn` da camada GEMINI), camadas, macros do modo de estenotipia e toda a configuração das luzes (efeitos, condições, overlays)
│   ├── corne.conf                opções Kconfig das duas metades: parte comum das telas (inclusive as configurações das telas pelo ZMK Studio), Bluetooth, NKRO, energia, luzes
│   ├── corne_left.conf           opções Kconfig só da metade esquerda: buffer de recepção do ZMK Studio, a tela esquerda e as transferências USB das duas portas seriais
│   ├── corne_right.conf          opções Kconfig só da metade direita: a tela direita (animação e aviso das luzes)
│   ├── corne_left.overlay        mapa dos LEDs da metade esquerda, os slots de cor dela (slot-count, no-key-slots) e a segunda porta serial USB (gemini_uart)
│   ├── corne_right.overlay       mapa dos LEDs da metade direita e os slots de cor dela (slot-count, no-key-slots)
│   ├── led_colors.dtsi           cores padrão de cada slot em cada camada (incluído no fim do corne.keymap)
│   ├── rgb.dtsi                  legado, sem uso (veja a nota abaixo)
│   └── west.yml                  versões do ZMK e dos módulos
├── dts/bindings/behaviors/       zmk,behavior-steno-gemini.yaml: o binding do comportamento &stn
├── include/dt-bindings/steno/    gemini.h: os números das teclas de estenotipia (STN_*), lidos pelo keymap e pelo C
├── src/                          behavior_steno_gemini.c: o comportamento &stn (acordes Gemini PR pela porta serial USB)
├── zephyr/module.yml             registra este repositório como módulo do Zephyr
├── CMakeLists.txt                compila o código do módulo (só o &stn)
├── Kconfig                       a opção CONFIG_ZMK_STENO_GEMINI do módulo
├── SUGESTOES.md                  ideias de melhoria do layout
└── README.md                     este arquivo
```

- Os shields `corne_left` e `corne_right` vêm do próprio ZMK. Este repositório só acrescenta o keymap, as opções, os mapas de LED e de slots de cor, as cores padrão de cada slot em cada camada e a lista de módulos.
- `config/led_colors.dtsi` é o arquivo a editar para mudar as cores padrão de cada LED em cada camada. O `config/corne.keymap` o inclui no final. As cores são indexadas por slot e valem para as duas metades. Veja [Cores por camada e indicador de Caps Lock](#cores-por-camada-e-indicador-de-caps-lock).
- `config/corne_left.conf` e `config/corne_right.conf` valem só para o build da metade correspondente: o ZMK aplica o `config/<shield>.conf` de cada shield do build, e o `corne.conf` vale para as duas metades. O da esquerda define o buffer de recepção do ZMK Studio (veja [ZMK Studio](#zmk-studio)), os widgets da tela esquerda e as transferências USB das duas portas seriais (veja [Estenotipia por acordes (Gemini PR)](#estenotipia-por-acordes-gemini-pr)); o da direita define a animação da tela direita e o aviso das luzes (veja [Telas OLED](#telas-oled)).
- A raiz do repositório é também um **módulo do Zephyr** (`zephyr/module.yml`): `CMakeLists.txt`, `Kconfig`, `src/`, `include/` e `dts/` guardam o código que o ZMK não tem, hoje só o comportamento `&stn` da camada GEMINI (veja [Estenotipia por acordes (Gemini PR)](#estenotipia-por-acordes-gemini-pr)). O workflow de build do ZMK o encontra pelo `zephyr/module.yml` (veja [Compilar](#compilar)).
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
| 4 | SYS | Bluetooth, controle das luzes e animações do underglow | segurar FN1 e, sem soltar, segurar a tecla da posição 25 (a do Z) | magenta |
| 5 | MEDIA | volume, mídia, brilho do monitor, Caps Lock, Caps Word | segurar FN1 e, sem soltar, segurar a tecla da posição 26 (a do X) | ciano |
| 6 | STENO | digitação de estenotipia no Plover (veja [Modo de estenotipia (Plover)](#modo-de-estenotipia-plover)) | na camada SYS, tocar `&steno_on` (posição 33, que também liga o Plover) ou `&to 6` (posição 34, que só troca de camada); sair com `&steno_off` (posição 0 da STENO) ou `&to 0` (posição 12) | roxo |
| 7 | GEMINI | estenotipia por acordes, enviados ao Plover por uma porta serial USB (veja [Estenotipia por acordes (Gemini PR)](#estenotipia-por-acordes-gemini-pr)) | na camada SYS, tocar `&to 7` (posição 40); sair com `&to 0` (posição 0 da GEMINI) | amarelo |

As camadas 3, 4 e 5 só são alcançadas por FN1: a camada FN1 tem `&mo 3`, `&mo 4` e `&mo 5` nas posições 24, 25 e 26. As camadas 6 (STENO) e 7 (GEMINI) só são alcançadas pela SYS e não são de segurar: `&to` as deixa ativas e desativa as outras, e elas só terminam com `&to 0` (a STENO também com `&steno_off`).

O **ID** da camada é a ordem em que ela foi declarada em `config/corne.keymap` (QWERTY 0, FN1 1, RAISE 2, NAV 3, SYS 4, MEDIA 5, STENO 6, GEMINI 7). É o número que as condições de luz (`cond_*`) e o `layer-id` dos mapas de cor usam, e ele não muda quando as camadas são reordenadas no ZMK Studio.

A cor da camada é a do underglow enquanto ela está ativa e a da tecla que a ativa. As cores de todas as teclas de cada camada estão em [Cores por camada e indicador de Caps Lock](#cores-por-camada-e-indicador-de-caps-lock).

Nas grades abaixo, cada camada aparece em duas partes (esquerda e direita), na mesma ordem das linhas do arquivo `config/corne.keymap`. As linhas são: 3 linhas de 6 teclas e, por último, os 3 polegares. Legenda:

- `--` é uma tecla transparente: vale a tecla da camada de baixo.
- Os rótulos seguem os nomes de tecla do ZMK (`LGUI`, `PG_DN`, `C_VOL_DN`...). Pontuação aparece como o próprio caractere (`;`, `[`, `{`...).
- `FN1`, `RAISE`, `NAV`, `SYS` e `MEDIA` são `&mo <camada>` (a camada fica ativa enquanto a tecla é segurada).
- `STUDIO` é `&studio_unlock`, `BT n` é `&bt BT_SEL n` e `CAPS_WORD` é `&caps_word`.
- `NONE` é `&none`: a tecla não faz nada e, ao contrário de `--`, **não** deixa passar a tecla da camada de baixo. `TO n` é `&to n`: vai para a camada n e desativa as outras. `STENO_ON` e `STENO_OFF` são os macros do [modo de estenotipia](#modo-de-estenotipia-plover). Na camada GEMINI, `S1-`, `T-`, `*1`, `-E`, `#` e os demais nomes de tecla de estenotipia são `&stn STN_<tecla>` ([Estenotipia por acordes (Gemini PR)](#estenotipia-por-acordes-gemini-pr)).
- Na camada SYS, os nomes em minúsculas (`solid` a `static`) são os efeitos diretos `&fx_<nome>`, os `RGB_*` são `&kprgb RGB_*` e `ug_rain`, `ug_brth`, `ug_spec`, `ug_star` e `ug_off` são os interruptores das [animações do underglow](#animações-do-underglow).

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
STUDIO    --        ug_rain   ug_brth   ug_spec   ug_star
                              LGUI      --        SPACE

Direita
solid     breathe   spectrum  rainbow   reactive  ripple
RGB_EFR   RGB_SAI   RGB_SAD   RGB_SPI   RGB_SPD   RGB_RESET
heatmap   starlight static    STENO_ON  TO 6      ug_off
ENTER     TO 7      RALT
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

#### Camada 6: STENO

```text
Esquerda
STENO_OFF Q         W         E         R         T
TO 0      A         S         D         F         G
NONE      NONE      NONE      NONE      NONE      NONE
                              1         C         V

Direita
Y         U         I         O         P         [
H         J         K         L         ;         '
NONE      NONE      NONE      NONE      NONE      NONE
N         M         0
```

As letras são as do mapa padrão da máquina Keyboard do Plover: veja [Teclas da camada STENO](#teclas-da-camada-steno). A terceira linha é `NONE` para que as teclas sem uso não escrevam nada.

#### Camada 7: GEMINI

```text
Esquerda
TO 0      S1-       T-        P-        H-        *1
NONE      S2-       K-        W-        R-        *2
NONE      NONE      NONE      NONE      NONE      NONE
                              #         A-        O-

Direita
*3        -F        -P        -L        -T        -D
*4        -R        -B        -G        -S        -Z
NONE      NONE      NONE      NONE      NONE      NONE
-E        -U        #
```

Cada tecla de estenotipia é `&stn STN_<tecla>` (veja [Teclas da camada GEMINI](#teclas-da-camada-gemini)); `TO 0` é a saída e `#` é a barra de números. A terceira linha é `NONE` para que as teclas sem uso não façam nada.

### Funções e recursos

- **Bluetooth com 5 perfis**: `BT 0` a `BT 4` (camada SYS, posições 1 a 5) escolhem o perfil e `BT_CLR` (posição 0) apaga o pareamento do perfil ativo. Opções em `config/corne.conf`: `CONFIG_BT_MAX_CONN=5` e `CONFIG_BT_MAX_PAIRED=5`. Para parear um dispositivo novo, selecione um perfil livre (ou apague o ativo com `BT_CLR`) e adicione o teclado no computador.
- **Caps Word** (`&caps_word`, camada MEDIA, posição 5): deixa as letras em maiúsculas até você digitar algo que não faça parte da lista de continuação. Letras e números sempre continuam. Neste projeto `continue-list = <UNDERSCORE>`, então só `_` continua além deles; qualquer outra tecla, inclusive Backspace e Delete, encerra o Caps Word. A lista padrão do ZMK é `<UNDERSCORE BACKSPACE DELETE>`: para voltar a ela, ajuste o bloco `&caps_word` no início de `config/corne.keymap`.
- **Caps Lock**: tecla `CAPS` na camada MEDIA (posição 17). Quando o computador reporta o Caps Lock ligado, a coluna externa da metade esquerda acende em branco. O Caps Word não aciona esse indicador, porque ele não liga o Caps Lock do computador.
- **Animações do underglow** (`&ug_rain`, `&ug_brth`, `&ug_spec`, `&ug_star` e `&ug_off`, camada SYS, posições 26 a 29 e 35): o underglow de cada metade ganha uma animação própria, independente do efeito das teclas. Veja [Animações do underglow](#animações-do-underglow).
- **NKRO**: `CONFIG_ZMK_HID_REPORT_TYPE_NKRO=y` permite pressionar qualquer número de teclas ao mesmo tempo. A camada STENO depende dele: o acorde que liga o Plover tem 7 teclas (veja [Modo de estenotipia (Plover)](#modo-de-estenotipia-plover)).
- **Estenotipia por acordes** (`&stn`, camada GEMINI): o teclado manda cada acorde inteiro ao Plover por uma segunda porta serial USB, sem digitar letras. Só por USB. Veja [Estenotipia por acordes (Gemini PR)](#estenotipia-por-acordes-gemini-pr).
- **Energia**: `CONFIG_ZMK_SLEEP=n` desliga o deep sleep e `CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=n` desliga o apagar de tela do ZMK (que não distingue USB de bateria), então as telas ficam sempre acesas por padrão. Isso aumenta o consumo de bateria no uso sem fio: para gastar menos, escolha **Only on battery** ou **Always** na aba Display (veja [Apagar a tela](#apagar-a-tela)). As luzes são tratadas à parte e apagam após 30 s sem digitar; veja [Manter as luzes acesas quando o teclado fica ocioso](#manter-as-luzes-acesas-quando-o-teclado-fica-ocioso).
- **Configurações das telas** (aba **Display** do ZMK Studio): o contraste de cada tela, quando as telas apagam (nunca, só na bateria ou sempre) e o aviso das luzes mudam sem recompilar, e cada metade guarda os valores na própria memória. Liga com `CONFIG_KEYPAW_DISPLAY_SETTINGS=y` em `config/corne.conf`. Veja [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display).

### Modo de estenotipia (Plover)

A camada **STENO** (ID 6) troca o QWERTY por um teclado de estenotipia para o [Plover](https://github.com/openstenoproject/plover) ([documentação](https://plover.readthedocs.io/en/latest/)), o programa que transforma acordes em texto. O teclado continua sendo um teclado USB ou Bluetooth comum: ele envia as **letras do mapa padrão da máquina "Keyboard" do Plover**, e o Plover trata várias teclas apertadas juntas como um acorde e o traduz pelo dicionário. Sem o Plover rodando, a camada só digita letras. Para mandar o acorde inteiro por uma porta serial, sem letras, veja [Estenotipia por acordes (Gemini PR)](#estenotipia-por-acordes-gemini-pr).

Requisitos: no computador, o Plover aberto, com a máquina **Keyboard** e as teclas e os comandos padrão (`commands.json`); no teclado, o NKRO (`CONFIG_ZMK_HID_REPORT_TYPE_NKRO=y`, já ligado em `config/corne.conf`), porque o acorde que liga o Plover tem 7 teclas apertadas ao mesmo tempo.

**Não testado neste teclado nem com o Plover.** O que foi conferido: o keymap, os macros e as cores passam no pré-processador e na leitura da estrutura do devicetree (por script) e o build do GitHub Actions compila as duas metades. Os acordes foram tirados do código-fonte do Plover (o mapa padrão da máquina Keyboard e o `commands.json` padrão, e o código do `engine.py` que executa os comandos), sem rodar o Plover.

#### Como ligar e desligar

| Tecla | Onde | O que faz |
|---|---|---|
| `&steno_on` | camada SYS, posição 33 | vai para a camada STENO (`&to 6`) e envia o acorde que liga o Plover |
| `&to 6` | camada SYS, posição 34 | só vai para a camada STENO, sem falar com o Plover |
| `&steno_off` | camada STENO, posição 0 | volta ao QWERTY (`&to 0`) e envia o acorde que suspende o Plover |
| `&to 0` | camada STENO, posição 12 | só volta ao QWERTY, sem falar com o Plover |

Para chegar à camada SYS, segure FN1 (posição 37) e, sem soltar, a tecla da posição 25; depois toque na posição 33 ou 34. Como `&to` desativa as outras camadas, soltar FN1 e SYS não tira o teclado da STENO.

Os dois macros estão em `config/corne.keymap` (bloco `macros`). Cada um troca de camada, aperta todas as teclas do acorde, espera e solta todas (`&macro_press` e `&macro_release`, com `wait-ms` e `tap-ms` em 20 ms). Os acordes são os comandos do `commands.json` padrão do Plover, escritos nas teclas que o mapa padrão dá a cada tecla de estenotipia:

| Comando do Plover | Acorde | Teclas enviadas | Usado em |
|---|---|---|---|
| `{PLOVER:RESUME}` (liga a saída) | `PHRO*PB` | E R F V T I K | `&steno_on` |
| `{PLOVER:SUSPEND}` (suspende a saída) | `PHRO*F` | E R F V T U | `&steno_off` |
| `{PLOVER:TOGGLE}` (alterna a saída) | `PHROLG` | E R F V O L | nenhum macro (use, se quiser um) |

Cuidados:

- **Letras que vazam.** No `engine.py` do Plover, `resume` e `toggle` funcionam mesmo com a saída desligada, e o Plover apaga com Backspace as letras do acorde que chegaram à janela. `suspend`, ao contrário, só vale com a saída ligada: se o Plover já estiver suspenso (ou fechado), `&steno_off` digita `erfvtu` na janela ativa e nada o apaga. Para sair sem acorde, use `&to 0`.
- **Fora de sincronia.** O teclado não sabe se o Plover está ligado. Se você ligar ou suspender a saída por outro meio (o ícone do Plover, a linha de comando, um acorde do dicionário), a camada e o Plover ficam fora de sincronia: toque `&steno_on` ou `&steno_off` de novo, ou troque só a camada com `&to`.
- **Mapa do Plover alterado.** Se você mudou o mapa de teclas da máquina Keyboard ou o `commands.json`, ajuste as teclas dos macros e as da camada STENO.
- **Teclas de uso comum.** A camada STENO não tem Esc, Enter, setas nem modificadores: para digitar normalmente, saia dela.
- **ZMK Studio.** Quem já salvou alterações pelo Studio talvez só veja a camada STENO e as teclas novas da SYS depois de "Restore Stock Settings" (veja [ZMK Studio](#zmk-studio)).

#### Teclas da camada STENO

A primeira linha de cada metade é a de cima do teclado de estenotipia, a segunda é a de baixo, e os polegares são as vogais e a barra de números. A terceira linha são teclas `&none`, que não escrevem nada.

| Tecla de estenotipia | Tecla do teclado | Posição |
|---|---|---|
| `S-` | `Q` e `A` | 1 e 13 |
| `T-` | `W` | 2 |
| `K-` | `S` | 14 |
| `P-` | `E` | 3 |
| `W-` | `D` | 15 |
| `H-` | `R` | 4 |
| `R-` | `F` | 16 |
| `*` (esquerda) | `T` e `G` | 5 e 17 |
| `A-` | `C` (polegar do meio da esquerda) | 37 |
| `O-` | `V` (polegar interno da esquerda) | 38 |
| `*` (direita) | `Y` e `H` | 6 e 18 |
| `-E` | `N` (polegar interno da direita) | 39 |
| `-U` | `M` (polegar do meio da direita) | 40 |
| `-F` | `U` | 7 |
| `-R` | `J` | 19 |
| `-P` | `I` | 8 |
| `-B` | `K` | 20 |
| `-L` | `O` | 9 |
| `-G` | `L` | 21 |
| `-T` | `P` | 10 |
| `-S` | `;` | 22 |
| `-D` | `[` | 11 |
| `-Z` | `'` | 23 |
| `#` (barra de números) | `1` (polegar externo da esquerda) e `0` (polegar externo da direita) | 36 e 41 |

#### Outras formas de ter estenotipia no teclado

As formas 1 e 5 são as que este repositório implementa (a 5, só para o Gemini PR, na camada GEMINI: veja [Estenotipia por acordes (Gemini PR)](#estenotipia-por-acordes-gemini-pr)). As outras são alternativas, **nenhuma delas feita aqui**:

| # | Forma | Como funciona | A favor | Contra |
|---|---|---|---|---|
| 1 | Mapa padrão do Plover por NKRO (**implementada**) | camada STENO com as letras do mapa padrão da máquina Keyboard e macros com os acordes de comando | só precisa do Plover; vale em USB e em Bluetooth; nada para configurar no Plover | as letras vazam com o Plover desligado; os acordes de comando também são letras; depende do mapa padrão |
| 2 | Mapa próprio no Plover, com teclas que não escrevem | trocar as teclas da camada por F13 a F24 (teclas de função extras, que quase nenhum teclado físico tem e que por isso não escrevem nada), teclado numérico ou outras que não geram texto, e configurar o mapa da máquina Keyboard do Plover para elas | nada vaza com o Plover desligado | configurar o Plover em cada computador; F13 a F24 podem colidir com atalhos e são só 12, enquanto a estenotipia tem 23 teclas, então seria preciso completar com outras; os macros mudam junto |
| 3 | Modo arpejo (arpeggiate) do Plover | o Plover aceita uma tecla de cada vez, e uma tecla de separação (o espaço, por padrão) fecha o golpe | funciona com 6KRO, sem NKRO | bem mais lento; a camada e os comandos mudam |
| 4 | Plover HID | o teclado se apresenta como um dispositivo HID de estenotipia, que o Plover lê direto: sem letras que vazem e sem mapa de teclas | a forma mais limpa | pede suporte no firmware: o [PR 962 do ZMK](https://github.com/zmkfirmware/zmk/pull/962) (WIP) ainda está aberto e não faz parte do ZMK fixado aqui |
| 5 | Gemini PR ou TX Bolt por porta serial (**Gemini PR implementado**) | o Plover tem as máquinas Gemini PR e TX Bolt, que leem pacotes por uma porta serial; o teclado ganha uma segunda porta serial USB (CDC ACM) e manda um pacote por acorde | protocolo clássico de máquinas de estenotipia; nada vaza com o Plover fechado; o acorde sai inteiro, sem depender do mapa de teclas nem do NKRO | só por USB; o computador vê uma segunda porta serial; pede código próprio no firmware (o módulo deste repositório); só o Gemini PR foi feito, não o TX Bolt |
| 6 | Atalho do sistema operacional chamando o Plover | uma tecla que não escreve nada (por exemplo F24), ligada por um atalho global do sistema a `plover -s plover_send_command toggle` (ou `resume`, `suspend`) | liga e desliga o Plover sem acorde e sem letras que vazem | configurar o atalho em cada computador |
| 7 | Só trocar de camada | `&to 6` e `&to 0`, que já existem | simples | o Plover precisa ser ligado e desligado por outro meio |

### Estenotipia por acordes (Gemini PR)

A camada **GEMINI** (ID 7) é a estenotipia por acordes de verdade. A camada STENO digita letras e deixa o Plover reconhecer que elas formam um acorde; a GEMINI não digita nada: o teclado junta as teclas apertadas e, quando o acorde termina, manda **um pacote por acorde** ao Plover por uma **segunda porta serial USB** (CDC ACM), no protocolo **Gemini PR**, o das máquinas de estenotipia profissionais, que o Plover lê na máquina "Gemini PR". É a forma 5 de [Outras formas de ter estenotipia no teclado](#outras-formas-de-ter-estenotipia-no-teclado), feita só para o Gemini PR.

Na prática:

- Com o Plover fechado, apertar acordes **não escreve nada** em lugar nenhum: o teclado não envia teclas, então nenhuma letra vaza e não há macro para ligar ou desligar o Plover.
- O acorde é o conjunto das teclas apertadas, não a ordem: ele é enviado quando a **última tecla é solta**, e teclas apertadas e soltas em ordens diferentes, ou de metades diferentes, entram no mesmo acorde. Não precisa de NKRO.
- **Só funciona por USB**, com a metade esquerda ligada ao computador: a porta serial é da metade esquerda (a central) e não existe por Bluetooth. Por Bluetooth, use a camada STENO.

**Não testado neste teclado nem com o Plover.** O que foi conferido no computador: o código do comportamento (`src/behavior_steno_gemini.c`) foi compilado fora do firmware, com peças de teste no lugar do Zephyr e do ZMK, e executado contra casos de acorde (uma tecla, `STKPWHR`, vogais soltas em ordem diferente, vários acordes seguidos, a mesma chave em duas posições, porta fechada no computador, buffer cheio, soltura sem aperto correspondente), e os pacotes saíram como o esperado; os números das 42 teclas conferem com a tabela `STENO_KEY_CHART` do Plover (`plover/machine/gemini_pr.py`); e o keymap e as cores passam no pré-processador e na leitura da estrutura do devicetree (por script), com os mesmos acordes da camada STENO em todas as posições. O formato do pacote e o comportamento do Plover vêm do código-fonte do Plover, e o da porta serial USB, do código-fonte do Zephyr. Não foi visto: o computador mostrando duas portas, o Plover abrindo a porta e o acorde chegando.

#### Configurar o Plover

1. Grave o firmware nas duas metades e conecte a metade esquerda ao computador por USB. O computador passa a ver **duas portas seriais** do teclado: uma é a do ZMK Studio e a outra é a do Plover. No Windows aparecem como dois "Dispositivo Serial USB" com números de COM diferentes (Gerenciador de Dispositivos, "Portas (COM e LPT)"); no Linux, dois `/dev/ttyACM*`; no macOS, dois `/dev/cu.usbmodem*`.
2. No Plover, abra **Configure**, aba **Machine**, escolha **Gemini PR** e, nas opções da máquina, escolha a porta. Os outros valores podem ficar como estão (`9600`, 8 bits, sem paridade, 1 bit de parada): numa porta serial USB virtual a velocidade não faz diferença.
3. Se você não sabe qual das duas é a do Plover, entre na camada GEMINI (passo 4), abra uma janela do Plover que mostre os golpes (o **Paper Tape**) e aperte um acorde: se nada aparecer, escolha a outra porta. A porta do Studio é a que o app do Studio abre ao conectar, e a que sobra é a do Plover.
4. Entre na camada GEMINI: na camada SYS (segure FN1 e, sem soltar, a tecla da posição 25), toque `&to 7` (posição 40). Saia com `&to 0` (posição 0, a primeira tecla da esquerda na GEMINI).

Cuidados:

- **Uma máquina de cada vez.** O Plover usa uma só máquina: com a **Gemini PR** escolhida, ele não lê as letras da camada STENO, que são da máquina **Keyboard**, e o contrário também. Troque a máquina em Configure ao trocar de camada. Na camada GEMINI os macros `&steno_on` e `&steno_off` não servem: os acordes de comando do Plover (`PHRO*PB`, `PHRO*F` e `PHROLG`, que o `commands.json` padrão liga a `{PLOVER:RESUME}`, `{PLOVER:SUSPEND}` e `{PLOVER:TOGGLE}`) são acordes comuns e saem das próprias teclas.
- **Cada porta é de um programa só.** Se o Plover abrir a porta do Studio, o app do Studio não conecta, e o contrário também. O teclado só envia acordes enquanto o computador está com a porta do Plover aberta (ele lê o sinal DTR da porta): acordes apertados antes de o Plover abrir a porta são descartados, e não ficam guardados para depois.
- **Teclas de uso comum.** A camada GEMINI não tem Esc, Enter, setas nem modificadores: para digitar normalmente, saia dela com `&to 0`.
- **ZMK Studio.** O app do Studio e o navegador pedem para escolher uma porta serial ao conectar: escolha a do Studio. Se o app não conectar, é a outra. Quem já salvou alterações pelo Studio talvez só veja a camada GEMINI e o `&to 7` da SYS depois de "Restore Stock Settings" (veja [ZMK Studio](#zmk-studio)).

#### Teclas da camada GEMINI

A disposição é a da camada STENO: a primeira linha de cada metade é a de cima do teclado de estenotipia, a segunda é a de baixo, e os polegares são as vogais e a barra de números; a terceira linha são teclas `&none`. Cada tecla é `&stn STN_<tecla>`, com o nome da tecla no `include/dt-bindings/steno/gemini.h` (os nomes do QMK: `STN_TL` é `T-` e `STN_TR` é `-T`). O Plover trata as duas `S1-` e `S2-` como `S-`, os quatro asteriscos como `*` e as teclas de número como `#`.

| Tecla de estenotipia | Tecla do keymap | Posição |
|---|---|---|
| `S-` | `STN_S1` e `STN_S2` | 1 e 13 |
| `T-` | `STN_TL` | 2 |
| `K-` | `STN_KL` | 14 |
| `P-` | `STN_PL` | 3 |
| `W-` | `STN_WL` | 15 |
| `H-` | `STN_HL` | 4 |
| `R-` | `STN_RL` | 16 |
| `*` (esquerda) | `STN_ST1` e `STN_ST2` | 5 e 17 |
| `A-` | `STN_A` (polegar do meio da esquerda) | 37 |
| `O-` | `STN_O` (polegar interno da esquerda) | 38 |
| `*` (direita) | `STN_ST3` e `STN_ST4` | 6 e 18 |
| `-E` | `STN_E` (polegar interno da direita) | 39 |
| `-U` | `STN_U` (polegar do meio da direita) | 40 |
| `-F` | `STN_FR` | 7 |
| `-R` | `STN_RR` | 19 |
| `-P` | `STN_PR` | 8 |
| `-B` | `STN_BR` | 20 |
| `-L` | `STN_LR` | 9 |
| `-G` | `STN_GR` | 21 |
| `-T` | `STN_TR` | 10 |
| `-S` | `STN_SR` | 22 |
| `-D` | `STN_DR` | 11 |
| `-Z` | `STN_ZR` | 23 |
| `#` (barra de números) | `STN_N1` (polegar externo da esquerda e polegar externo da direita) | 36 e 41 |

O protocolo Gemini PR tem 42 teclas e o keymap usa 27 delas. As que ficaram de fora (`STN_FN`, `STN_PWR`, `STN_RES1`, `STN_RES2` e as teclas de número `STN_N2` a `STN_NC`) existem em `include/dt-bindings/steno/gemini.h` e valem em qualquer `&stn`, mas no mapa padrão da máquina Gemini PR do Plover as primeiras não têm função (`no-op`) e todas as de número são a mesma tecla `#`.

#### Como funciona por dentro

O ZMK não tem esse comportamento, então o repositório é também um **módulo do Zephyr**: o `zephyr/module.yml` da raiz o registra e o workflow de build do ZMK o compila junto com o firmware (veja [Compilar](#compilar)).

- **`&stn`** (`src/behavior_steno_gemini.c`, `dts/bindings/behaviors/zmk,behavior-steno-gemini.yaml`, `Kconfig` e `CMakeLists.txt`): o parâmetro é o número da tecla de estenotipia (os `STN_*` de `include/dt-bindings/steno/gemini.h`), que é também a posição dela no pacote. Apertar uma tecla soma a chave ao acorde; soltar a última tecla envia o acorde. Duas teclas do keymap com a mesma chave (as duas `S-`, os quatro `*`) contam juntas. Uma soltura sem o aperto correspondente é ignorada (o ZMK manda a soltura ao mesmo comportamento do aperto, então não deveria acontecer): ela não vira um acorde vazio.
- **O pacote** tem 6 bytes de 7 teclas cada (`Fn #1 #2 #3 #4 #5 #6`, `S1- S2- T- K- P- W- H-`, `R- A- O- *1 *2 res1 res2`, `pwr *3 *4 -E -U -F -R`, `-P -B -L -G -T -S -D`, `#7 #8 #9 #A #B #C -Z`), com o bit mais alto do primeiro byte ligado para marcar o início do pacote: é o `STENO_KEY_CHART` de `plover/machine/gemini_pr.py`. O Plover descarta o pacote cujo primeiro byte não tem esse bit ou cujos outros bytes têm.
- **A porta** é o nó `gemini_uart` de `config/corne_left.overlay` (um `zephyr,cdc-acm-uart` dentro de `&zephyr_udc0`), a segunda porta serial USB, além da do ZMK Studio (snippet `studio-rpc-usb-uart`). O pacote entra no buffer de saída da porta (`uart_fifo_fill`) sem esperar o computador, e só se o computador abriu a porta (sinal DTR; é a opção `CONFIG_ZMK_STENO_GEMINI_REQUIRE_DTR`, ligada por padrão).
- **Só a metade central o executa.** O comportamento tem `locality` central, então o keymap o roda na metade esquerda, que tem a porta, mesmo para as teclas da direita, que chegam por Bluetooth. A metade direita compila o mesmo código, sem o nó da porta, e nunca o executa.
- **Opções.** A primeira está em `config/corne_left.conf`; a segunda é do `Kconfig` do repositório e vale `y` sem aparecer em nenhum `.conf` (para mudá-la, acrescente a linha em `config/corne_left.conf`):

| Opção | Valor | O que faz |
|---|---|---|
| `CONFIG_USB_MAX_NUM_TRANSFERS` | `8` | quantas transferências USB podem estar em andamento ao mesmo tempo. Cada porta serial usa até duas (uma de leitura, uma de escrita), então as duas portas usam exatamente o padrão do Zephyr (4), sem folga; com 8 sobra margem |
| `CONFIG_ZMK_STENO_GEMINI_REQUIRE_DTR` | `y` (padrão do `Kconfig`; só existe na metade esquerda, a única com a porta serial) | só envia o acorde enquanto o computador está com a porta aberta (sinal DTR alto), e descarta o acorde com a porta fechada. Com `n` o acorde sai sempre e, com a porta fechada, fica no buffer da porta e chega ao Plover quando ele a abrir, como um golpe que ninguém digitou naquele momento. Use `n` só para descobrir se um computador que nunca levanta o DTR é o motivo de nenhum acorde chegar |

Para desligar o módulo sem apagar nada, troque as teclas `&stn` da camada GEMINI por `&none` (ou apague a camada) e remova o nó `stn` de `config/corne.keymap`: a opção `CONFIG_ZMK_STENO_GEMINI` do `Kconfig` depende da existência do nó e o código deixa de ser compilado (com o nó removido e as teclas `&stn` ainda no keymap, a compilação falha). Isso não tira a segunda porta serial do computador, porque ela existe por causa do nó `gemini_uart`: para voltar a ter só a porta do ZMK Studio, apague também o bloco `&zephyr_udc0 { gemini_uart: ... }` de `config/corne_left.overlay` e a linha `CONFIG_USB_MAX_NUM_TRANSFERS=8` de `config/corne_left.conf`.

### ZMK Studio

O ZMK Studio permite editar teclas pelo navegador, sem recompilar. Ele está habilitado só na metade esquerda: em `build.yaml`, o build `corne_left` usa o snippet `studio-rpc-usb-uart` e `-DCONFIG_ZMK_STUDIO=y`. O `config/corne_left.conf` define `CONFIG_ZMK_STUDIO_RPC_RX_BUF_SIZE=256`, o tamanho do buffer em que o ZMK Studio recebe os pedidos do app: o padrão do ZMK (30 bytes) descarta os bytes que não cabem, e um pedido que edita 16 cores de LED tem 158 bytes (até cerca de 210 com escapes). O módulo zmk-rgb-matrix confere o valor: a compilação da esquerda falha com menos de 256.

1. Conecte a **metade esquerda** ao computador por USB.
2. Abra o app em um navegador baseado em Chromium e conecte ao teclado: [zmk.studio](https://zmk.studio) (o app oficial) ou o [fork não oficial deste projeto](https://lenerdz.github.io/zmk-studio/), que desenha ícones nas teclas (veja [Ícones nas teclas (fork do app)](#ícones-nas-teclas-fork-do-app)), deixa arrastar uma tecla sobre outra (veja [Arrastar teclas (fork do app)](#arrastar-teclas-fork-do-app)) e tem a aba **Lights** para editar as cores das luzes (veja [Editar as cores na aba Lights](#editar-as-cores-na-aba-lights)) e a aba **Display** para configurar as telas (veja [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display)).
3. Para liberar a edição, pressione a tecla `&studio_unlock`: camada RAISE, posição 13, ou camada SYS, posição 24.

O teclado mostra ao computador **duas portas seriais** USB (a do Studio e a do Plover, veja [Estenotipia por acordes (Gemini PR)](#estenotipia-por-acordes-gemini-pr)): ao conectar, o navegador pede para escolher uma, e a do Studio é a que responde. Se o app não conectar, tente a outra. Não testado neste teclado.

> **Atenção:** depois que você usar o ZMK Studio para gerenciar as teclas, mudanças futuras no arquivo `.keymap` não são aplicadas até você executar a ação "Restore Stock Settings" na interface do Studio (ou gravar o `settings_reset` nas duas metades). É o comportamento documentado pelo ZMK. Em geral, escolha um dos dois caminhos para as teclas: o Studio ou o `.keymap`.
>
> Isso vale para as teclas e camadas. Os efeitos, as condições e os overlays de luz, as cores padrão de `config/led_colors.dtsi`, o `corne.conf` e os `.overlay` são compilados no firmware e continuam valendo normalmente a cada gravação. As cores de mapa que alguém tenha editado e salvo no teclado (veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio)) têm prioridade sobre as padrão nos slots editados, e "Restore Stock Settings" as apaga. As configurações das telas (aba Display) também voltam ao padrão com "Restore Stock Settings". A consequência prática: se você já usa o Studio, um efeito novo adicionado ao `.keymap` precisa ser atribuído a uma tecla pelo próprio Studio (foi o caso do `&fx_static`, camada SYS, posição 32; o mesmo vale para as camadas STENO e GEMINI e para `&steno_on`, `&to 6` e `&to 7`, camada SYS, posições 33, 34 e 40). As cores de cada camada seguem o ID da camada e a posição física da tecla, não o que o Studio colocou nela.

O firmware usa um fork do protocolo do ZMK Studio, o [`lenerdz/zmk-studio-messages`](https://github.com/lenerdz/zmk-studio-messages) (com [README em português](https://github.com/lenerdz/zmk-studio-messages/blob/main/README.pt-BR.md)), que acrescenta as requisições dos mapas de cor e as das configurações das telas. Os apps (o oficial e o fork) continuam editando teclas normalmente: eles só não conhecem as requisições novas. Veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio), [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display) e [Por que existem os forks](#por-que-existem-os-forks).

#### Ícones nas teclas (fork do app)

O app oficial desenha cada tecla como o nome do comportamento e, embaixo, o primeiro parâmetro como se fosse uma tecla do teclado. Isso serve para teclas comuns, mas as teclas de Bluetooth, de luzes e de camadas ficam vazias ou com um rótulo sem sentido. O fork não oficial [`lenerdz/zmk-studio`](https://github.com/lenerdz/zmk-studio) (com [README em português](https://github.com/lenerdz/zmk-studio/blob/main/README.pt-BR.md)), publicado em <https://lenerdz.github.io/zmk-studio/>, desenha um ícone e um rótulo curto nessas teclas. Passar o mouse sobre uma tecla mostra a descrição completa, como `Bluetooth: Select Profile 2`.

| Tecla deste projeto | O que o fork desenha |
|---|---|
| `&mo` (camadas), por exemplo `&mo 1` | ícone de camadas e o nome da camada (`FN1`) |
| `&to`, por exemplo `&to 6` | seta para a camada e o nome da camada |
| `&bt BT_SEL 0` a `&bt BT_SEL 4` | ícone de Bluetooth e o número do perfil |
| `&bt BT_CLR` | ícone de Bluetooth com uma borracha e `clear` |
| `&kprgb RGB_*` | cabeçalho `RGB`, um ícone e uma palavra curta: `on/off`, `hue`, `sat`, `bri`, `time`, `effect`, `reset`, com `+` ou `-` para subir e descer |
| `&fx_*` | cabeçalho `Effect`, um ícone para cada efeito e o nome (`solid`, `breathe`, ...) |
| `&ug_*`, por exemplo `&ug_rain` (as animações do underglow da SYS) | cabeçalho `Underglow`, um ícone para cada animação e o nome (`rainbow`, `breathe`, `spectrum`, `starlight`, `off`) |
| `&studio_unlock`, `&caps_word`, `&trans`, `&none` | cadeado aberto, seta do Caps Word, seta dupla esmaecida e símbolo de proibido esmaecido |
| `&steno_on`, `&steno_off` | ícone de teclado (riscado no desligar) e o texto `steno on` ou `steno off` |
| `&stn`, por exemplo `&stn STN_TL` (as teclas da camada GEMINI) | só o nome da tecla de estenotipia (`T-`, `*1`, `A-`, `-E`, `#`, ...), tirado dos nomes de parâmetro que o firmware informa (a lista `STN_VALUE` de `src/behavior_steno_gemini.c`) |
| Teclas de mídia (`C_MUTE`, `C_VOL_UP`, `C_BRI_UP`, ...) | ícones, no lugar dos emojis do app oficial |

Os ícones não alteram o protocolo nem o que é gravado no teclado: a edição das teclas, o salvamento e o "Restore Stock Settings" seguem o mesmo caminho do app oficial. Além do desenho das teclas e da hospedagem do app, o fork acrescenta a aba **Lights**, que usa as requisições novas do firmware (veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio)). Veja [Por que existem os forks](#por-que-existem-os-forks).

**Testado neste teclado.** O fork, na versão que só tinha os ícones (antes da aba Lights), foi usado com este teclado conectado por USB e os ícones e rótulos funcionaram (relato do dono do teclado). Também foi verificado nas stories do Storybook do fork, com as oito camadas deste `corne.keymap`; os nomes dos comportamentos usados nelas vêm do código-fonte do ZMK e do zmk-rgb-matrix (e, nos dois macros do modo de estenotipia, no `&stn` e nas teclas `&ug_*`, do `display-name` e dos nomes de nó do `corne.keymap`). Os ícones de `&to`, `&none`, `&ug_*`, `&stn` e dos macros do modo de estenotipia, a camada GEMINI e o mapa de cores dela na aba Lights foram vistos só em um navegador, com o teclado de demonstração e nas stories, não neste teclado. O app só mostra o que o firmware informa: se uma tecla aparecer vazia ou com um rótulo estranho, passe o mouse sobre ela para ver o nome do comportamento.

#### Arrastar teclas (fork do app)

Na visão **Keys** do [fork do app](https://lenerdz.github.io/zmk-studio/), arraste uma tecla sobre outra da mesma camada para **trocar** as duas (comportamento e parâmetros). Com **Ctrl** ou **Alt** pressionado, soltar **copia**: a tecla de destino recebe o binding da arrastada, que fica como estava. **Esc** cancela. O arraste começa depois de 6 pixels de movimento, então um clique simples continua selecionando a tecla. Cada soltar é **um passo** do Undo e do Redo, mesmo na troca, que muda duas teclas, e grava com a mesma requisição que o seletor de teclas usa (`setLayerBinding`): **Save** e **Discard** funcionam como antes. Se o teclado recusar uma gravação, as teclas já gravadas voltam ao que eram e o app mostra um alerta. As teclas giradas (os polegares) e as da metade direita funcionam como as outras.

O fork também corrigiu uma corrida do seletor de bindings do upstream: quando o binding mudava por fora do seletor (um soltar sobre a tecla selecionada, Undo ou Redo), o seletor podia gravar o valor antigo de volta, e os valores antigo e novo podiam se substituir sem parar. Agora o seletor só avisa o teclado quando o usuário muda algo nos próprios controles. Os detalhes estão no [README do fork em português](https://github.com/lenerdz/zmk-studio/blob/main/README.pt-BR.md).

**Não testado neste teclado.** O arraste foi testado em um navegador com o teclado de demonstração (troca, cópia com Ctrl e com Alt, Esc, soltar fora das teclas, as teclas giradas, Undo e Redo), e as regras têm testes automáticos. Em um teclado real e com toque não foi experimentado.

## Luzes (RGB por tecla e underglow)

### Como as luzes funcionam

As luzes são controladas pelo módulo [zmk-rgb-matrix](https://github.com/gudzpoz/zmk-rgb-matrix), usado a partir de um [fork](https://github.com/lenerdz/zmk-rgb-matrix) com duas correções (veja [Por que existem os forks](#por-que-existem-os-forks)). O underglow nativo do ZMK (`CONFIG_ZMK_RGB_UNDERGLOW`) fica desligado, porque os dois não podem controlar a mesma fita de LEDs ao mesmo tempo.

1. **Fita de LEDs**: cada metade tem 27 LEDs WS2812 em série (`&led_strip { chain-length = <27>; }` em `config/corne.keymap`). Os índices 0 a 5 são o underglow (sem tecla) e 6 a 26 são um LED sob cada tecla.
2. **Mapa dos LEDs**: o nó `keypaw,rgb-matrix` de cada metade (em `config/corne_left.overlay` e `config/corne_right.overlay`) diz onde cada LED fica: pela posição da tecla ou, no underglow, por coordenadas. Os efeitos que dependem de posição (reativo, ondas, mapa de calor) usam essas coordenadas. O mesmo nó define os **slots de cor** (`slot-count` e `no-key-slots`): a posição da lista de cores de onde cada LED tira a sua cor (veja [Slots de cor](#slots-de-cor)).
3. **Efeitos**: são os nós filhos do comportamento `kprgb` no keymap. Um efeito principal de cada vez pinta todos os LEDs, e as teclas da camada SYS trocam o efeito. O efeito `fx_static` é o mapa de cores da camada base.
4. **Overlays**: pintam por cima do efeito principal, só enquanto uma condição for verdadeira (uma camada ativa, o Caps Lock ligado, um interruptor ligado por tecla). Aqui há cinco **animações do underglow** (`ov_ugrain` a `ov_ugoff`), que pintam só os 6 LEDs de underglow, um **mapa de cores por camada** (FN1 a GEMINI), que cobre todos os LEDs da metade, e um indicador de Caps Lock, que pinta só três.
5. **As duas metades precisam ter exatamente os mesmos efeitos, condições e overlays, na mesma ordem**, porque o módulo os identifica pela posição em que foram declarados. Por isso esses blocos ficam no `config/corne.keymap`, que é compartilhado, e não nos `.overlay` de cada metade. As cores também são as mesmas nas duas metades: o `slot-colors` de cada mapa vem de `config/led_colors.dtsi` e é indexado por slot, e cada metade pinta só os slots dos seus LEDs. O que difere entre as metades são os `.overlay` (`mapping`, `slot-count` e `no-key-slots`). Sempre grave as duas metades depois de mexer em qualquer um desses arquivos.

O efeito principal e cada overlay são combinados nesta ordem de pintura (do fundo para o topo): efeito ativo, `ov_ugrain`, `ov_ugbrth`, `ov_ugspec`, `ov_ugstar`, `ov_ugoff`, `ov_fn1`, `ov_raise`, `ov_nav`, `ov_sys`, `ov_media`, `ov_steno`, `ov_gemini`, `ov_caps`. Quem é declarado depois fica por cima. Um mapa de camada cobre todos os LEDs: enquanto um deles está ativo, o efeito principal, as animações do underglow e os mapas declarados antes dele nem são desenhados (o efeito principal fica pausado e volta quando a camada é solta).

### Controles no dia a dia

Segure FN1 e, sem soltar, segure a tecla da posição 25 para ativar a camada SYS. Os comandos de luz são `&kprgb RGB_*` (valem para as duas metades), os efeitos diretos são `&fx_<nome>` e as animações do underglow são `&ug_<nome>` (veja [Animações do underglow](#animações-do-underglow)).

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
| 16 | F | `&kprgb RGB_BRI` | aumenta o brilho em 10 pontos (`CONFIG_KEYPAW_RGB_MATRIX_BRT_STEP`) numa escala de 0 a 100, em que 100 equivale a `max-brightness` |
| 17 | G | `&kprgb RGB_BRD` | diminui o brilho em 10 pontos |
| 18 | H | `&kprgb RGB_EFR` | efeito anterior |
| 19 | J | `&kprgb RGB_SAI` | aumenta a saturação |
| 20 | K | `&kprgb RGB_SAD` | diminui a saturação |
| 21 | L | `&kprgb RGB_SPI` | aumenta a duração do ciclo da animação em 100 ms (`CONFIG_KEYPAW_RGB_MATRIX_DURATION_STEP`): o efeito fica **mais lento**. O nome vem do ZMK, mas aqui o ajuste é no período |
| 22 | ; | `&kprgb RGB_SPD` | diminui a duração do ciclo em 100 ms: o efeito fica **mais rápido** |
| 23 | ' | `&kprgb RGB_RESET` | apaga o estado salvo das luzes e volta aos padrões do keymap |
| 24 | LCTRL | `&studio_unlock` | libera a edição no ZMK Studio |
| 26 | X | `&ug_rain` | liga ou desliga a animação arco-íris do underglow |
| 27 | C | `&ug_brth` | liga ou desliga a animação de respiração em ciano do underglow |
| 28 | V | `&ug_spec` | liga ou desliga a animação de espectro do underglow (os 6 LEDs ciclam juntos pelas cores) |
| 29 | B | `&ug_star` | liga ou desliga a animação de brilhos aleatórios brancos do underglow |
| 30 | N | `&fx_heatmap` | escolhe o efeito `heatmap` |
| 31 | M | `&fx_starlight` | escolhe o efeito `starlight` |
| 32 | , | `&fx_static` | escolhe o efeito `static`: o mapa de cores da camada base |
| 33 | . | `&steno_on` | vai para a camada STENO e liga o Plover (veja [Modo de estenotipia (Plover)](#modo-de-estenotipia-plover)) |
| 34 | [ | `&to 6` | vai para a camada STENO, sem falar com o Plover |
| 35 | ] | `&ug_off` | liga ou desliga o underglow apagado: apaga os 6 LEDs de underglow de cada metade e vale mais que as outras animações |
| 40 | RAISE | `&to 7` | vai para a camada GEMINI, a estenotipia por acordes (veja [Estenotipia por acordes (Gemini PR)](#estenotipia-por-acordes-gemini-pr)) |

**Aviso na tela direita (não testado neste teclado).** Cada tecla acima que muda algo que se vê (efeito, ligar e desligar, brilho, matiz, saturação, ciclo da animação ou o reset) faz a tela direita mostrar, por 1,5 s (o padrão: a aba Display muda o tempo e pode desligar o aviso, veja [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display)), duas linhas embaixo do gato: por exemplo `EFEITO 4` e `RAINBOW`, `BRILHO` e `70%`, `LUZES` e `APAGADAS`. O aviso vem do evento `zmk_rgb_matrix_changed` do módulo de luzes, que é disparado nas duas metades, e vale para as teclas das duas metades. Comando que não muda nada (o mesmo efeito de novo, o brilho já no limite) não avisa nada, e o aviso não aparece ao ligar o teclado, ao conectar a metade direita nem quando as cores são editadas pelo ZMK Studio. As teclas `&ug_*` também não avisam nada: elas não passam pelo evento das luzes. Os textos e as opções estão em [Aviso das luzes (toast)](#aviso-das-luzes-toast).

**O número do brilho.** O brilho que as teclas `RGB_BRI` e `RGB_BRD` mudam e o aviso mostra é o do controlador, de 0 a 100, em passos de 10 (`CONFIG_KEYPAW_RGB_MATRIX_BRT_STEP`). O valor 100 corresponde a `max-brightness` (50 aqui) e o brilho real dos LEDs é `max-brightness` vezes esse valor. Pela leitura do código do módulo, antes do commit `123f7ac` do fork essas duas teclas não mudavam nada (veja [Solução de problemas](#solução-de-problemas)); a correção não foi testada neste teclado.

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

**Funcionou no teclado**, segundo o dono, depois de gravar o firmware com as cores por slot. No computador, um script conferiu que as cores por slot reproduzem exatamente as da versão anterior (por LED da fita) em cada LED das duas metades (as 6 camadas daquela versão, 2 metades e 27 LEDs: o script expande o `led_colors.dtsi` antigo e o novo e compara pelo `mapping` dos `.overlay`) e que cada um dos 54 slots é pintado por exatamente um LED. As camadas STENO e GEMINI (a sétima e a oitava) vieram depois dessa conferência, e as cores delas foram escritas direto por slot: **não testado neste teclado**.

A camada 0 (QWERTY) usa o efeito `fx_static`: o mapa dela só aparece quando você escolhe esse efeito (camada SYS, posição 32); com os outros efeitos a camada 0 mostra o efeito. As camadas 1 a 7 usam overlays, que aparecem com qualquer efeito. Os overlays são declarados em `rgb_overlays` no `config/corne.keymap`, na ordem desta tabela, que é a ordem de pintura (o último fica por cima):

| Overlay | Condição | LEDs | Cores |
|---|---|---|---|
| `ov_ugrain` | interruptor `&ug_rain` ligado (`cond_ugrain`) | `leds = <0 1 2 3 4 5>` (o underglow) | efeito `rainbow` próprio |
| `ov_ugbrth` | interruptor `&ug_brth` ligado (`cond_ugbrth`) | `leds = <0 1 2 3 4 5>` | efeito `breathe` próprio, em `0x00FFFF` |
| `ov_ugspec` | interruptor `&ug_spec` ligado (`cond_ugspec`) | `leds = <0 1 2 3 4 5>` | efeito `spectrum` próprio |
| `ov_ugstar` | interruptor `&ug_star` ligado (`cond_ugstar`) | `leds = <0 1 2 3 4 5>` | efeito `starlight` próprio, em `0xFFFFFF` |
| `ov_ugoff` | interruptor `&ug_off` ligado (`cond_ugoff`) | `leds = <0 1 2 3 4 5>` | efeito `solid` em `0x000000` (apagado) |
| `ov_fn1` | camada 1 (FN1) ativa | `all-leds` | bloco `&map_fn1` |
| `ov_raise` | camada 2 (RAISE) ativa | `all-leds` | bloco `&map_raise` |
| `ov_nav` | camada 3 (NAV) ativa | `all-leds` | bloco `&map_nav` |
| `ov_sys` | camada 4 (SYS) ativa | `all-leds` | bloco `&map_sys` |
| `ov_media` | camada 5 (MEDIA) ativa | `all-leds` | bloco `&map_media` |
| `ov_steno` | camada 6 (STENO) ativa | `all-leds` | bloco `&map_steno` |
| `ov_gemini` | camada 7 (GEMINI) ativa | `all-leds` | bloco `&map_gemini` |
| `ov_caps` | Caps Lock do computador ligado | `keys = <0 12 24>` | `0xFFFFFF` (branco) |

Cada mapa de camada é um overlay com `all-leds` e um efeito `static` filho; o `slot-colors` desse filho é preenchido pelo bloco de mesmo nome em `config/led_colors.dtsi`, e o `layer-id` dele é o ID da camada (a ordem em que ela foi declarada no keymap), que identifica o mapa ao editar e salvar.

- **Prioridade entre camadas.** Como NAV, SYS e MEDIA são alcançadas segurando FN1, duas camadas ficam ativas ao mesmo tempo, e vale o mapa da camada declarada depois: FN1 + NAV mostra o mapa de NAV, FN1 + SYS mostra o de SYS e FN1 + MEDIA mostra o de MEDIA.
- **O efeito principal fica pausado.** Cada mapa cobre todos os LEDs da metade. Enquanto uma camada de FN1 a GEMINI está ativa, o efeito principal nem é desenhado: os efeitos que reagem às teclas (`reactive`, `ripple`, `heatmap`) não aparecem nem contam teclas nessas camadas, e voltam quando a camada é solta. Para ver o efeito por baixo do mapa, veja [Deixar o efeito aparecer por baixo do mapa de uma camada](#deixar-o-efeito-aparecer-por-baixo-do-mapa-de-uma-camada).
- **Brilho.** As cores são `0xRRGGBB` com brilho cheio. O brilho real vem do `kprgb` e vale para todas as cores, mapas inclusive: `RGB_BRI` e `RGB_BRD` clareiam e escurecem os mapas, e `max-brightness` é o teto. Matiz, saturação e velocidade não alteram os mapas.
- **As cores seguem a posição, não a tecla.** O mapa guarda uma cor por slot (0 a 41 são as posições físicas das teclas, veja [Posições das teclas](#posições-das-teclas)) e pertence a uma camada pelo ID dela. Se você trocar uma tecla pelo ZMK Studio, a cor não acompanha: edite o `led_colors.dtsi` ou a cor do slot (veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio)). Se você mudar a ordem das camadas no Studio, o mapa e a condição continuam na mesma camada, porque usam o ID, que não muda.
- **Cada metade pinta os seus slots.** Cada bloco tem um grupo de 27 valores para a metade esquerda e outro para a direita, e a macro `LED_SLOTS` os junta na lista de 54 slots, igual para as duas metades. O firmware de cada metade pinta só os slots dos seus LEDs (veja [Slots de cor](#slots-de-cor)).
- O número da camada em cada condição (`cond_fn1` a `cond_gemini`) e o `layer-id` de cada mapa são o ID da camada: a ordem em que ela foi declarada no keymap, começando em 0 (QWERTY 0, FN1 1, RAISE 2, NAV 3, SYS 4, MEDIA 5, STENO 6, GEMINI 7). O ID não muda quando as camadas são reordenadas no ZMK Studio.

**Cores padrão.** Cada tecla de camada acende na cor da camada que ela abre (a tecla que você segura continua acesa), e o underglow usa a cor da camada. As demais teclas seguem a função:

| Nome | Cor | Valor | Usada por padrão em |
|---|---|---|---|
| `OFF` | apagado | `0x000000` | teclas transparentes (`&trans`) e teclas sem função na camada (inclusive as `&none` da STENO e da GEMINI) |
| `WHT` | branco | `0xFFFFFF` | letras, SPACE, `CAPS`, `CAPS_WORD`, `C_MUTE` e `RGB_TOG`; as teclas `&to` (`TO 6` na SYS e `TO 0` na STENO) e `&ug_off` |
| `RED` | vermelho | `0xFF0000` | BSPC, DEL, ESC, `C_PWR`, `BT_CLR`, `RGB_RESET` e `&steno_off`; o `&to 0` da GEMINI |
| `ORG` | laranja | `0xFF8000` | teclas F, INS, `C_SLEEP`, `C_STOP`, `RGB_HUI` e `RGB_HUD`; camada FN1; consoantes da mão direita (`-F` a `-Z`) da STENO e da GEMINI |
| `YEL` | amarelo | `0xFFFF00` | números, `C_BRI_DN`, `C_BRI_UP`, `RGB_BRI` e `RGB_BRD`; as teclas `1` e `0` (barra de números) da STENO; as teclas `#` (barra de números), o underglow e a tecla `&to 7` da camada GEMINI |
| `LIM` | verde-limão | `0x80FF00` | pontuação e símbolos, HOME, END, PG_UP, PG_DN, PSCRN, SLCK, `RGB_SAI` e `RGB_SAD` |
| `GRN` | verde | `0x00FF00` | setas, `C_PREV` e `C_NEXT`; camada NAV; as vogais (`A-`, `O-`, `-E` e `-U`) da STENO e da GEMINI |
| `TEA` | verde-água | `0x00FF80` | ENTER e `C_PP`; as teclas das animações do underglow (`&ug_rain`, `&ug_brth`, `&ug_spec` e `&ug_star`) |
| `CYN` | ciano | `0x00FFFF` | `C_VOL_DN`, `C_VOL_UP`, `RGB_SPI` e `RGB_SPD`; camada MEDIA; consoantes da mão esquerda (`S-` a `R-`) da STENO e da GEMINI |
| `SKY` | azul-claro | `0x0080FF` | colchetes, chaves e parênteses; camada RAISE |
| `BLU` | azul | `0x0000FF` | perfis Bluetooth (`BT_SEL`); underglow da camada base |
| `PUR` | roxo | `0x8000FF` | TAB, Shift, Ctrl, GUI e Alt; `&steno_on`; camada STENO |
| `MAG` | magenta | `0xFF00FF` | `&studio_unlock`; camada SYS; os asteriscos (`*`) da STENO e da GEMINI |
| `PNK` | rosa | `0xFF0080` | escolha de efeito (`&fx_*`, `RGB_EFF` e `RGB_EFR`) |

Os nomes são macros definidas no começo do `led_colors.dtsi` (veja a receita [Mudar a cor de uma tecla ou de um LED em uma camada](#mudar-a-cor-de-uma-tecla-ou-de-um-led-em-uma-camada)).

**Indicador de Caps Lock.** O overlay `ov_caps` pinta a coluna externa da metade esquerda (`keys = <0 12 24>`: TAB, LSHIFT e LCTRL) de branco enquanto o computador informa Caps Lock ligado (condição `cond_caps`). É o último overlay declarado, então aparece por cima de qualquer mapa de camada.

### Animações do underglow

Além do efeito principal, que pinta as teclas e o underglow juntos, o underglow pode ter uma **animação própria**, independente do efeito das teclas: as teclas continuam com o efeito escolhido (ou com o mapa da camada) e só os 6 LEDs de underglow de cada metade mudam. Cinco teclas da camada SYS (segure FN1 e, sem soltar, a posição 25) ligam e desligam as animações.

**Não testado neste teclado.** O que foi conferido: o keymap passa no pré-processador e na leitura da estrutura do devicetree (por script), e o comportamento descrito vem da leitura do código e dos arquivos de binding do módulo zmk-rgb-matrix. Ninguém viu as animações nos LEDs.

| Posição | Tecla na base | Comando | Animação | Overlay | Efeito e propriedades |
|---|---|---|---|---|---|
| 26 | X | `&ug_rain` | arco-íris varrendo o underglow | `ov_ugrain` | `rainbow`: `color = 0xFFFFFF`, `duration = 4000`, `basis = "x"`, `direction = "out"`, `palette = "rainbow"` |
| 27 | C | `&ug_brth` | respiração em ciano | `ov_ugbrth` | `breathe`: `color = 0x00FFFF`, `duration = 4000` |
| 28 | V | `&ug_spec` | os 6 LEDs ciclam juntos pelo espectro | `ov_ugspec` | `spectrum`: `duration = 6000` |
| 29 | B | `&ug_star` | brilhos aleatórios brancos | `ov_ugstar` | `starlight`: `color = 0xFFFFFF`, `smooth` |
| 35 | ] | `&ug_off` | underglow apagado | `ov_ugoff` | `solid`: `color = 0x000000` |

Como usar e o que esperar:

- Cada tecla é um **interruptor**: um toque liga a animação e outro toque a desliga. O comando vale para as duas metades: uma tecla de qualquer metade liga ou desliga a animação nas duas.
- Com mais de uma animação ligada, vale a de baixo da tabela (a última declarada fica por cima), e `&ug_off` vence todas.
- O estado **não é salvo**: ao desligar o teclado, todas voltam a desligadas e o underglow volta a mostrar o efeito principal (ou o mapa de cores da camada base).
- As animações só aparecem na camada QWERTY. Elas vêm antes dos mapas de camada na ordem de pintura, então, enquanto uma camada de FN1 a GEMINI está ativa, o mapa da camada cobre o underglow (que mostra a cor da camada) e a animação nem é desenhada. Por isso, ao tocar uma tecla destas na camada SYS, a animação só aparece quando você solta as teclas e volta ao QWERTY. Para ela aparecer por cima dos mapas (e o underglow deixar de mostrar a cor da camada), mova os cinco overlays `ov_ug*` para depois de `ov_gemini` e antes de `ov_caps` em `rgb_overlays`.
- `RGB_TOG` apaga tudo, as animações inclusive, e o brilho (`RGB_BRI` e `RGB_BRD`) vale para elas. Matiz, saturação e velocidade (`RGB_HUI` a `RGB_SPD`) e a troca de efeito (`RGB_EFF` e `RGB_EFR`) não mexem nas animações, porque o efeito de um overlay é privado.
- Se você já salvou edições na camada SYS pelo ZMK Studio, as cinco teclas só aparecem depois de "Restore Stock Settings" ou de você atribuí-las pelo próprio Studio (veja [Solução de problemas](#solução-de-problemas)).
- Para mudar as cores e os efeitos, ou criar uma animação nova, veja [Dar um efeito próprio ao underglow](#dar-um-efeito-próprio-ao-underglow).

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

**Funcionou no teclado**, segundo o dono: depois de gravar o firmware com o buffer de recepção de 256 bytes, ele informou que funcionou, sem detalhar cada operação. A aba Lights também foi testada em um navegador contra um teclado de demonstração que usa a mesma moldura (framing) e a mesma codificação de mensagens de um teclado real, e tem testes automáticos; o firmware compila no GitHub Actions. **Sem confirmação individual neste teclado**: o descarte, o "Restore Stock Settings", o `RGB_RESET` e a cópia para a metade direita. O codec do registro salvo na memória e partes da sincronização têm testes de unidade que rodam no computador.

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

**Protocolo.** O ZMK traz o protocolo como o módulo `zmk-studio-messages` (em `app/west.yml`). O `config/west.yml` o substitui, com o mesmo nome e caminho, pelo fork, que parte do mesmo commit do ZMK (`6cb4c28`) e acrescenta dois commits: o `cfcce43` (os mapas de cor) e o `caee958` (as configurações das telas e o limite de 15 mapas em `get_led_info`). Sem o fork o módulo não compila com o ZMK Studio ligado. A opção `CONFIG_KEYPAW_RGB_MAPS_STUDIO` liga as requisições e vem ligada quando o ZMK Studio está no build (só no firmware da esquerda). Os apps que não conhecem as requisições novas continuam editando teclas normalmente: o app oficial não as envia (não testado neste teclado com o app oficial). O fork do app as usa por um cliente TypeScript gerado a partir do mesmo protocolo (`src/vendor/zmk-studio-ts-client`, na revisão `caee958`).

**Metade direita.** Quem salva é a central, e a periférica nunca grava os mapas. Cada edição vira um comando interno por slot (`RGB_MAP_SET_CMD`) enviado à periférica, um por vez, com 50 ms entre eles. Quando a periférica conecta (ou reinicia), a central manda primeiro um comando que volta os mapas dela ao padrão (`RGB_MAP_RESET_CMD`) e depois só os slots dela cuja cor difere do padrão. Se a metade direita for desligada, ela volta às cores padrão do firmware dela e recebe as edições de novo ao reconectar. Como a periférica parte do padrão do próprio firmware, grave a metade que você mudou em `led_colors.dtsi`. A sincronização por Bluetooth só pode ser conferida no teclado e não tem confirmação individual (veja a situação acima).

**Limites.** `slot-count` até 60; no protocolo do fork, a lista `colors` de `LedMap` tem 54 posições (com mais slots é preciso aumentar `colors max_count` em `proto/zmk/keymap.options.in` do fork e o firmware avisa na compilação). IDs de camada de 0 a 14. No máximo 15 mapas em `get_led_info` (`layer_ids max_count:15` no fork do protocolo; são 8 aqui, então sobram 7; a compilação falha com mais de 15, com a mensagem `more colour maps than the LedInfo of the protocol can list`) e 16 slots por `set_led_colors`. O buffer de recepção do ZMK Studio precisa ter pelo menos 256 bytes (`CONFIG_ZMK_STUDIO_RPC_RX_BUF_SIZE=256`, em `config/corne_left.conf`): um `set_led_colors` com 16 slots tem 158 bytes depois do enquadramento (até cerca de 210 com escapes) e o padrão do ZMK (30 bytes) descarta o que não cabe. A compilação falha com um valor menor.

#### Editar as cores na aba Lights

1. Grave o firmware nas duas metades, conecte a **metade esquerda** por USB e abra o [fork do app](https://lenerdz.github.io/zmk-studio/) em um navegador baseado em Chromium. Conecte ao teclado e desbloqueie com `&studio_unlock` (veja [ZMK Studio](#zmk-studio)).
2. Depois de desbloquear, o cabeçalho ganha o botão **Lights**, ao lado de **Keys** (o editor de teclas) e de **Display** (as telas, veja [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display)). O app só oferece a aba Lights quando o firmware tem os mapas editáveis; se ele não aparecer, veja [Solução de problemas](#solução-de-problemas).
3. Escolha uma camada na lista da esquerda. O desenho mostra cada tecla com o seu rótulo e a cor do LED dela. Os LEDs de underglow, que não têm tecla, são as células redondas da faixa sob as teclas (numeradas de 1 a 6 em cada metade).
4. Escolha uma cor (uma das 14 cores da paleta do `led_colors.dtsi`, o seletor de cor do sistema ou um valor hexadecimal) e arraste sobre os LEDs com **Paint**. O app mostra a cor enquanto você pinta e envia o traço quando você solta; o teclado mostra a cor na hora. As células também funcionam pelo teclado do computador (Tab para andar, Enter ou Espaço para pintar).
   - **Pick** pega a cor de um LED.
   - **Fill** preenche todos os LEDs da camada (**All**), só as teclas (**Keys**) ou só o underglow (**Underglow**).
   - **Restore layer defaults** devolve a camada às cores com que o firmware foi compilado.
5. A edição fica só na memória viva do teclado até você clicar em **Save** (canto superior direito), que salva as luzes junto com as teclas. **Discard** descarta as duas coisas, e **Undo** e **Redo** valem para as duas, na ordem em que você fez. O "Restore Stock Settings" do menu do teclado conectado também devolve as cores de fábrica.
6. Para tornar as cores editadas as cores padrão do firmware, use **Export led_colors.dtsi** (veja [Tornar as cores editadas na aba Lights os novos padrões](#tornar-as-cores-editadas-na-aba-lights-os-novos-padrões)).

Para ver a aba sem o teclado, abra o app com `?demo` no endereço (<https://lenerdz.github.io/zmk-studio/?demo>): o diálogo de conexão ganha o "Demo keyboard", um teclado que roda no próprio navegador, o "Demo keyboard (no light maps)", que responde como um firmware sem os mapas (e então a aba não é oferecida), e o "Demo keyboard (no display settings)", que responde como um firmware sem as configurações das telas (e então a aba Display não é oferecida). O código da aba, o protocolo e os testes estão no [`src/lights/README.md`](https://github.com/lenerdz/zmk-studio/blob/main/src/lights/README.md) do fork (em inglês).

### O que é salvo na memória

O módulo guarda o estado das luzes na memória do teclado (`CONFIG_SETTINGS`), mas nem tudo:

| O que | Salvo? | Observação |
|---|---|---|
| ligado ou desligado, brilho e efeito selecionado | sim, sempre | gravados 60 s depois da última alteração (`CONFIG_ZMK_SETTINGS_SAVE_DEBOUNCE`, padrão do ZMK). Se desligar o teclado antes disso, a última alteração se perde |
| matiz, saturação e velocidade ajustados com `RGB_HUI`, `RGB_HUD`, `RGB_SAI`, `RGB_SAD`, `RGB_SPI` e `RGB_SPD` | só nos efeitos que têm `persist-id` | **neste repositório nenhum efeito tem `persist-id`**, então esses ajustes voltam aos valores do keymap ao reiniciar. Veja [Salvar a cor e a velocidade ajustadas nas teclas](#salvar-a-cor-e-a-velocidade-ajustadas-nas-teclas) |
| cores padrão dos mapas por camada (`config/led_colors.dtsi`) | não, fazem parte do firmware | só mudam ao gravar um firmware novo na metade correspondente |
| cores dos mapas por camada editadas pelo ZMK Studio | só quando você salva (botão **Save** do app, que envia `save_led_changes`) | um registro por camada na memória da metade esquerda, só com os slots diferentes do padrão. A metade direita não grava nada: recebe as cores da esquerda ao conectar. Os slots salvos valem no lugar do padrão, e `RGB_RESET` apaga os registros. Veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio) |
| animações do underglow ligadas pelas teclas `&ug_*` | não | o estado fica só na RAM de cada metade: ao desligar o teclado, todas voltam a desligadas |
| configurações das telas (aba Display do ZMK Studio) | sim, pelo próprio firmware (não há botão Save) | cada metade guarda na própria memória um registro por configuração diferente do padrão (`keypaw/display/<id>`), `CONFIG_KEYPAW_DISPLAY_SAVE_DEBOUNCE_MS` (3 s) depois da última mudança. A direita recebe os valores da esquerda ao conectar e também os guarda. `RGB_RESET` não os apaga; "Restore Stock Settings" e o `settings_reset` apagam. Veja [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display) |

O estado salvo tem prioridade sobre os valores iniciais do `kprgb`: depois que você muda o efeito, o brilho ou o liga/desliga pelas teclas, `initial-effect` e `initial-brightness` deixam de valer naquele teclado.

`&kprgb RGB_RESET` apaga o estado salvo das duas metades, inclusive as cores editadas dos mapas por camada, e restaura os padrões do keymap (as configurações das telas não são tocadas). Use depois de mudar a lista de efeitos, os `persist-id` ou os valores iniciais, porque o estado salvo pode ficar fora de sincronia com a nova definição.

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

Isso não afeta as telas OLED, que por padrão ficam sempre ligadas (veja [Apagar a tela](#apagar-a-tela)).

#### Mudar a cor de uma tecla ou de um LED em uma camada

As cores ficam em `config/led_colors.dtsi`, um bloco por camada: `&fx_static` (QWERTY), `&map_fn1`, `&map_raise`, `&map_nav`, `&map_sys`, `&map_media`, `&map_steno` e `&map_gemini`. Cada bloco tem dois grupos de 27 valores, o da metade esquerda e o da direita, nesta ordem: três linhas de 6 teclas, os 3 polegares e os 6 LEDs de underglow. As posições são as de [Posições das teclas](#posições-das-teclas), e o comentário ao lado de cada linha diz que tecla era aquela no keymap. Os dois grupos entram em `LED_SLOTS(esquerda, direita)`, que os põe na ordem dos slots (veja [Slots de cor](#slots-de-cor)). **Não testada neste teclado.**

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

1. Na aba Lights, clique em **Export led_colors.dtsi**. O botão só fica habilitado para este teclado (54 LEDs por camada e as camadas 0 a 7). O arquivo baixado tem a mesma estrutura do `config/led_colors.dtsi` (a paleta, a macro `LED_SLOTS` e um bloco por camada) e as cores de todas as camadas como estão no teclado agora, inclusive as que ainda não foram salvas. Só os comentários de cada linha diferem: os nomes das teclas vêm do teclado e o título de cada camada não tem a cor de destaque.
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

Um overlay escolhe seus alvos com estas propriedades (valem para os mapas de camada, para as animações do underglow e para o indicador de Caps Lock):

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

Para remover as animações do underglow, apague os cinco overlays `ov_ug*` (em `rgb_overlays`), as cinco condições `cond_ug*` (em `rgb_conditions`) e troque as cinco teclas `&ug_*` da camada SYS por `&trans`.

#### Adicionar um efeito novo

1. Declare o efeito dentro de `kprgb`, **depois do último**: assim os índices dos efeitos que já existem não mudam.
2. Atribua o efeito a uma tecla livre. A camada SYS não tem mais posições livres (os `&ug_*` ocupam as posições 26 a 29 e 35): troque uma tecla que você não usa ou use outra camada com teclas transparentes (`&trans`), como a MEDIA (por exemplo a posição 2).
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
// na camada MEDIA: troca o &trans da posição 2 (a terceira tecla da linha 1 da esquerda)
&kp C_PWR  &kp C_SLEEP &fx_wave  &trans    &trans    &caps_word
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

Depois de criar uma camada no keymap (ela recebe o próximo ID, por exemplo 8), crie a condição, o overlay e o bloco de cores dela. O `layer-id` do mapa é o ID da camada e precisa ser único entre os mapas (de 0 a 14). **Não testada neste teclado.**

```dts
// em config/corne.keymap, dentro de rgb_conditions
cond_game: cond_game {
    compatible = "keypaw,rgb-condition-layer";
    layer = <8>;               // ID da camada no keymap
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
        layer-id = <8>;        // o mesmo ID da camada: identifica o mapa ao editar e salvar
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

Dois limites: o protocolo lista no máximo 8 mapas (`layer_ids max_count` no fork do protocolo), e a compilação da esquerda falha com mais de 8: **hoje são 8 de 8** (com a GEMINI), então um mapa novo, o nono, exige antes aumentar `layer_ids max_count` em `proto/zmk/keymap.options.in` do fork `lenerdz/zmk-studio-messages`, atualizar o pin em `config/west.yml` e gerar de novo o cliente do app (veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio)); e o botão **Export led_colors.dtsi** do app só vale para as camadas 0 a 7, então, para uma camada nova, acrescente o mapa em `MAP_LABELS` (`src/lights/exportDtsi.ts`) e em `LAYER_IDS` (`scripts/generate-led-data.mjs`) do [fork do app](https://github.com/lenerdz/zmk-studio).

#### Dar um efeito próprio ao underglow

O repositório já traz cinco animações do underglow, ligadas por teclas da camada SYS (veja [Animações do underglow](#animações-do-underglow)). Esta receita mostra como mudar uma delas e como acrescentar outra. **Não testada neste teclado.**

**Mudar uma animação que já existe.** Cada uma é um overlay de `rgb_overlays` (`ov_ugrain`, `ov_ugbrth`, `ov_ugspec`, `ov_ugstar` ou `ov_ugoff`) com um efeito filho (`fx_ov_ugrain` e os demais). Edite as propriedades do filho (`color`, `duration` e as outras do tipo, que estão em [Referência de efeitos, condições e overlays](#referência-de-efeitos-condições-e-overlays)) ou troque o `compatible` por outro tipo de efeito. Para o underglow ter a animação o tempo todo, sem tecla, apague a linha `condition` do overlay: um overlay sem `condition` pinta sempre.

**Acrescentar uma animação nova ligada por uma tecla.** São três peças, todas em `config/corne.keymap`:

```dts
// 1. em rgb_conditions: o interruptor. O nome do nó dele (ug_nova) tem no máximo 8 caracteres
cond_ugnova: cond_ugnova {
    compatible = "keypaw,rgb-condition-latch";
    ug_nova: ug_nova {
        compatible = "keypaw,behavior-rgb-overlay-toggle";
        #binding-cells = <0>;
    };
};

// 2. em rgb_overlays, ANTES de ov_ugoff (para o underglow apagado continuar valendo mais)
//    e antes de ov_fn1 (para os mapas de camada ficarem por cima)
ov_ugnova: ov_ugnova {
    compatible = "keypaw,rgb-overlay";
    condition = <&cond_ugnova>;
    leds = <0 1 2 3 4 5>;
    fx_ov_ugnova {
        compatible = "keypaw,rgb-matrix-breathe";
        #binding-cells = <0>;
        color = <0xFF00FF>;
        duration = <3000>;
    };
};
```

```dts
// 3. em uma camada, o comando &ug_nova (a SYS está cheia: aqui, o &trans da posição 2 da MEDIA)
&kp C_PWR  &kp C_SLEEP &ug_nova  &trans    &trans    &caps_word
```

Como o efeito de um overlay é privado, as teclas de matiz, saturação e velocidade não mexem nele. Enquanto uma camada de FN1 a GEMINI está ativa, o mapa dela cobre o underglow e a animação não é desenhada. O interruptor não é salvo: ao reiniciar, todas as animações voltam a desligadas. As duas metades precisam receber o mesmo firmware, porque o keymap é compartilhado.

#### Escolher quais overlays aparecem em cada efeito

Por padrão, todos os overlays (as animações do underglow, os mapas de camada e o Caps Lock) são pintados em qualquer efeito. Um efeito pode escolher a própria lista com `overlays`, ou desligá-los com `no-overlays`. É a forma de manter um efeito sempre visível, mesmo nas camadas FN1 a GEMINI:

```dts
fx_rainbow: fx_rainbow {
    // ... propriedades do efeito ...
    no-overlays;                // com este efeito, nenhum overlay é pintado (nem as animações do underglow, nem os mapas, nem o Caps Lock)
};

fx_reactive: fx_reactive {
    // ... propriedades do efeito ...
    overlays = <&ov_caps>;      // com este efeito, só o Caps Lock é pintado: as animações do underglow e os mapas de camada não aparecem
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
| `latch` | nenhuma (usa um filho `keypaw,behavior-rgb-overlay-toggle`, cujo nome de nó deve ter no máximo 8 caracteres) | uma tecla a liga e desliga. O estado é volátil e por metade. Usada pelas animações do underglow (`cond_ugrain` a `cond_ugoff`) |
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

- **Metade esquerda (central)**: saída ativa (USB ou Bluetooth, com ícone próprio para perfil sem pareamento e sem conexão), a bateria das duas metades (como dois números no lugar do ícone, sem o indicador de carga por USB; não testado neste teclado, veja [Tela esquerda (central)](#tela-esquerda-central)), perfil Bluetooth ativo, velocidade de digitação (velocímetro, número e gráfico) e o nome da camada ativa (o `display-name` de cada camada no keymap: QWERTY, FN1, RAISE, NAV, SYS, MEDIA, STENO e GEMINI).
- **Metade direita (periférica)**: animação do gato, porcentagem de bateria e o estado da conexão Bluetooth com a metade esquerda. Por 1,5 s (o padrão: a aba Display muda o tempo e pode desligar o aviso) depois de cada mudança nas luzes, duas linhas embaixo do gato dizem o que mudou (veja [Aviso das luzes (toast)](#aviso-das-luzes-toast); não testado neste teclado).

Por padrão as telas **ficam sempre ligadas**, no USB e na bateria: `CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=n` desliga o apagar de tela do próprio ZMK, e o modo **Never** das configurações das telas (o padrão) não apaga nunca. Quem quiser que elas apaguem (sempre, ou só na bateria) escolhe na aba **Display**: veja [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display).

O zmk-nice-oled não tem "layouts" para escolher: cada tela é montada pelas opções `CONFIG_NICE_OLED_*` do build da metade. As duas telas são diferentes porque a central e a periférica têm widgets diferentes (o WPM, o perfil, a camada e a bateria da outra metade só existem na central; a animação, na periférica). Por isso cada metade tem o próprio arquivo de opções.

### Configurar as telas pelo ZMK Studio (aba Display)

Com `CONFIG_KEYPAW_DISPLAY_SETTINGS=y` (em `config/corne.conf`, que vale para as duas metades), seis configurações das telas mudam **sem recompilar**, pela aba **Display** do [fork do app](https://lenerdz.github.io/zmk-studio/): o contraste de cada tela, quando as telas apagam e o aviso das luzes. O módulo zmk-rgb-matrix aplica as configurações, guarda cada uma na memória da metade e copia todas para a metade direita; o fork do zmk-nice-oled lê as duas do aviso das luzes; e o fork do protocolo (`lenerdz/zmk-studio-messages`) leva os pedidos do app ao teclado (requisições 106 a 108). Sem a opção, as telas ficam sempre ligadas, o aviso usa o tempo de `CONFIG_NICE_OLED_WIDGET_LED_TOAST_MS` e a aba não aparece no app.

**Não testado neste teclado.** O firmware compila no GitHub Actions, nas duas metades. A lógica das configurações (faixas, registros na memória, o contraste de cada metade, quando a tela apaga e o comando enviado à metade direita) passa em testes no computador com um relógio falso (`tests/unit/test_display_settings.py` do módulo zmk-rgb-matrix; ali o driver da tela, as filas de trabalho e a memória são substitutos), e a aba foi usada em um navegador contra o teclado de demonstração. Nenhuma configuração foi vista em uma tela de verdade: o contraste, a tela apagando em cada modo, a cópia para a metade direita e o que sobra depois de reiniciar dependem do teste no teclado.

#### Usar a aba Display

1. Conecte a **metade esquerda** por USB, abra o fork do app, conecte ao teclado e desbloqueie com `&studio_unlock` (veja [ZMK Studio](#zmk-studio)).
2. No cabeçalho, ao lado de **Keys** e **Lights**, escolha **Display**. O app só oferece a aba quando o firmware tem as configurações das telas; se ela não aparecer, veja [Solução de problemas](#solução-de-problemas).
3. Mude o que quiser: os dois contrastes (controles deslizantes), **Turn the screen off** (**Never**, **Only on battery** ou **Always**) com o tempo sem atividade, a chave do aviso das luzes e a duração dele. O tempo só vale com o apagar diferente de **Never**, e a duração só vale com o aviso ligado: o app desabilita o controle e diz por quê.
4. Não há o que salvar. O teclado aplica cada mudança na hora e a guarda na memória uns 3 segundos depois da última. **Save**, **Discard**, **Undo** e **Redo** do cabeçalho não agem sobre essas configurações. **Restore defaults** (na própria aba) e **Restore Stock Settings** (menu do teclado conectado) devolvem tudo ao padrão do firmware.

Uma mudança acende as telas por pelo menos 10 s, para que dê para vê-la. A tela da direita recebe as configurações da esquerda, o que pode levar alguns segundos depois de ela conectar. Para ver a aba sem o teclado, abra o app com `?demo` e escolha o "Demo keyboard" (<https://lenerdz.github.io/zmk-studio/?demo>); o "Demo keyboard (no display settings)" responde como um firmware sem as configurações, e então a aba não é oferecida. A documentação da aba, em inglês, está no [`src/display/README.md`](https://github.com/lenerdz/zmk-studio/blob/main/src/display/README.md) do fork.

#### As seis configurações

| Id | Nome no app | Faixa | Padrão | O que faz |
|---|---|---|---|---|
| 1 | Left screen contrast | 0 a 255 | 128 | contraste da tela esquerda (`display_set_contrast()`); 128 é o padrão do driver (`CONFIG_SSD1306_DEFAULT_CONTRAST`) |
| 2 | Right screen contrast | 0 a 255 | 128 | o mesmo, na tela direita |
| 3 | Turn the screen off | 0 (Never), 1 (Only on battery) ou 2 (Always) | 0 (Never) | quando a tela apaga com o teclado parado |
| 4 | Time without activity before it goes off | 30 s a 1 h (de 10 em 10 s no app) | 1 min | segundos sem atividade até a tela apagar; o mínimo é o tempo ocioso do ZMK (`CONFIG_ZMK_IDLE_TIMEOUT`, 30 s); só vale quando a 3 não é Never |
| 5 | Light toast on the right screen | ligado ou desligado | ligado | o [aviso das luzes](#aviso-das-luzes-toast) da tela direita |
| 6 | Toast duration | 0,5 s a 5 s (de 0,1 em 0,1 s no app) | 1,5 s (`CONFIG_KEYPAW_DISPLAY_TOAST_MS_DEFAULT`) | por quanto tempo o aviso fica na tela; só vale com a 5 ligada |

As faixas e os padrões vêm do firmware: o app lê os limites do teclado (o mínimo da configuração 4, por exemplo, depende do tempo ocioso com que o firmware foi compilado). Tudo parte do padrão, então o teclado se comporta como antes (telas sempre ligadas) até você mudar alguma coisa.

#### Apagar a tela

O apagar de tela do próprio ZMK (`CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE`) não distingue USB de bateria, então fica desligado (`n`), e quem apaga a tela, só se você mandar, é o módulo zmk-rgb-matrix, com a mesma chamada do driver (`display_blanking_on()`). Os modos da configuração 3:

| Modo | O que faz |
|---|---|
| Never (o padrão) | a tela nunca apaga, no USB ou na bateria (como antes) |
| Only on battery | apaga depois do tempo sem atividade se aquela metade **não** está com USB ligado; com USB ligado, não apaga |
| Always | apaga depois do tempo sem atividade, com ou sem USB |

O tempo é contado a partir da última atividade: o ZMK fica ocioso depois de `CONFIG_ZMK_IDLE_TIMEOUT` e o módulo espera o resto do tempo da configuração 4. Apertar uma tecla acende a tela de novo. Duas coisas valem **por metade**, porque o ZMK enxerga cada metade sozinha:

- **O USB.** A metade direita costuma estar sem cabo (ela fala com a esquerda por Bluetooth), então **Only on battery** apaga a tela direita mesmo com o teclado no USB, e a esquerda continua acesa. Para manter as duas telas acesas no USB, deixe **Never**.
- **A atividade.** A metade esquerda (central) conta também as teclas da direita, mas a direita conta só as suas: a tela direita pode apagar enquanto você digita apenas na esquerda.

Não testado neste teclado: baseado no código do ZMK (`activity.c` e `zmk_usb_is_powered()`) e nos testes no computador.

#### Memória e metade direita

Cada metade guarda, na própria memória, um registro por configuração que difere do padrão (`keypaw/display/<id>`), gravado `CONFIG_KEYPAW_DISPLAY_SAVE_DEBOUNCE_MS` (3000 ms) depois da última mudança, para que arrastar um controle deslizante grave uma vez só. Ao ligar, os registros valem no lugar dos padrões; um registro desconhecido ou fora da faixa é ignorado. As duas metades guardam as seis configurações e cada uma aplica o próprio contraste.

A metade esquerda (central) copia as configurações para a direita pela mesma sincronização por Bluetooth dos mapas de cor (um comando por configuração, com 50 ms entre eles), quando a direita conecta ou reinicia e sempre que uma configuração muda. A direita as aplica e as guarda, então já liga com os últimos valores recebidos, antes de conectar à esquerda. `&kprgb RGB_RESET` não mexe nelas; "Restore Stock Settings" do ZMK Studio e o `settings_reset` as apagam e voltam ao padrão (veja [O que é salvo na memória](#o-que-é-salvo-na-memória)).

#### O que continua só na compilação

A aba não muda o que as telas desenham: quais widgets aparecem e onde, a animação do gato (ou outra), o estilo do WPM, o idioma do aviso (`CONFIG_NICE_OLED_WIDGET_LED_TOAST_LANGUAGE_PT_BR`) e a posição do aviso continuam sendo opções `CONFIG_NICE_OLED_*` dos arquivos `.conf` (tabelas abaixo) e exigem gravar o firmware. Também são de compilação o tempo ocioso do ZMK (o mínimo da configuração 4) e, com `CONFIG_KEYPAW_DISPLAY_SETTINGS=y`, o tempo padrão do aviso (`CONFIG_KEYPAW_DISPLAY_TOAST_MS_DEFAULT`, 1500) e a espera para gravar na memória (`CONFIG_KEYPAW_DISPLAY_SAVE_DEBOUNCE_MS`, 3000), que aqui ficam nos valores padrão.

### Opções de configuração das telas

As opções ficam em três arquivos: `config/corne.conf` (as duas metades), `config/corne_left.conf` (só a esquerda) e `config/corne_right.conf` (só a direita). O ZMK aplica o `config/<shield>.conf` de cada shield do build (veja [Estrutura do repositório](#estrutura-do-repositório)).

#### Opções das duas telas

Em `config/corne.conf`:

| Opção | Valor | O que faz |
|---|---|---|
| `CONFIG_ZMK_DISPLAY` | `y` | liga o suporte a telas |
| `CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM` | `y` | usa a tela do zmk-nice-oled |
| `CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE` | `n` | desliga o apagar de tela do próprio ZMK, que não distingue USB de bateria. Quem apaga a tela, se você mandar, é o zmk-rgb-matrix (linha abaixo) |
| `CONFIG_KEYPAW_DISPLAY_SETTINGS` | `y` | liga as configurações das telas (aba Display do ZMK Studio, veja [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display)). Precisa estar ligada nas duas metades e exige `CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=n` |
| `CONFIG_ZMK_WIDGET_LAYER_STATUS`, `CONFIG_ZMK_WIDGET_BATTERY_STATUS`, `CONFIG_ZMK_WIDGET_OUTPUT_STATUS`, `CONFIG_ZMK_WIDGET_WPM_STATUS`, `CONFIG_ZMK_WIDGET_PERIPHERAL_STATUS` | `n` | desligam os widgets nativos do ZMK, que conflitam com o zmk-nice-oled |
| `CONFIG_ZMK_DISPLAY_DEDICATED_THREAD_STACK_SIZE` | `4096` | pilha da thread da tela. O LVGL 9 precisa de mais que o valor antigo (2560): com ele a metade periférica travava (hard fault) |

O `corne.conf` tem ainda `CONFIG_ZMK_BLE=y`, `CONFIG_BT_MAX_CONN=5`, `CONFIG_BT_MAX_PAIRED=5`, `CONFIG_ZMK_SLEEP=n` e `CONFIG_ZMK_HID_REPORT_TYPE_NKRO=y`, descritos em [Funções e recursos](#funções-e-recursos).

#### Tela esquerda (central)

Em `config/corne_left.conf`. As opções dos widgets da central (WPM, camada, perfil, modificadores e a bateria da outra metade) só existem no build da esquerda; por isso ficam neste arquivo, e não no `corne.conf`.

| Opção | Valor | O que faz |
|---|---|---|
| `CONFIG_NICE_OLED_WIDGET_WPM_BONGO_CAT` | `n` | desliga o gato da tela esquerda para dar lugar ao velocímetro e ao gráfico |
| `CONFIG_NICE_OLED_WIDGET_WPM_GRAPH` | `y` | gráfico de WPM |
| `CONFIG_NICE_OLED_WIDGET_WPM_SPEEDOMETER` | `y` | velocímetro de WPM |
| `CONFIG_NICE_OLED_WIDGET_WPM_NUMBER` | `y` | número de WPM |
| `CONFIG_NICE_OLED_WIDGET_MODIFIERS_INDICATORS` | `n` | sem indicadores de modificadores |
| `CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_FETCHING` | `y` | a central busca o nível de bateria da periférica por Bluetooth |
| `CONFIG_NICE_OLED_WIDGET_CENTRAL_SHOW_BATTERY_PERIPHERAL_AND_CENTRAL` | `y` | mostra a bateria da esquerda e a da direita como dois números |

**Bateria das duas metades (não testado neste teclado).** Com essa opção, o texto "esquerda  direita" (por exemplo `85  90`: o nível da esquerda, dois espaços e o da direita, de 0 a 100) aparece no lugar do ícone de bateria, e o indicador de carga por USB deixa de aparecer. É o modo `AND_CENTRAL` do widget `screen.c` do fork, escrito a partir da leitura do código do módulo e do ZMK; nunca foi visto neste teclado. As outras opções do mesmo grupo são `CONFIG_NICE_OLED_WIDGET_CENTRAL_SHOW_BATTERY_PERIPHERAL_ALL` (todas as baterias numa linha) e `CONFIG_NICE_OLED_WIDGET_CENTRAL_SHOW_BATTERY_PERIPHERAL_ONLY` (só a da periférica). Para voltar ao ícone da bateria só da esquerda, apague as duas últimas opções do `config/corne_left.conf` (`CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_FETCHING` e `CONFIG_NICE_OLED_WIDGET_CENTRAL_SHOW_BATTERY_PERIPHERAL_AND_CENTRAL`).

#### Tela direita (periférica)

Em `config/corne_right.conf`:

| Opção | Valor | O que faz |
|---|---|---|
| `CONFIG_NICE_OLED_WIDGET_ANIMATION_PERIPHERAL` | `y` | liga a animação da tela direita |
| `CONFIG_NICE_OLED_WIDGET_ANIMATION_PERIPHERAL_CAT` | `y` | a animação é o gato (o padrão do módulo) |
| `CONFIG_NICE_OLED_WIDGET_ANIMATION_PERIPHERAL_WPM` | `n` | o WPM na metade periférica exige um módulo extra (zmk-wpm-peripheral) |
| `CONFIG_NICE_OLED_WIDGET_LED_TOAST` | `y` | liga o aviso das luzes (veja [Aviso das luzes (toast)](#aviso-das-luzes-toast)) |
| `CONFIG_NICE_OLED_WIDGET_LED_TOAST_LANGUAGE_PT_BR` | `y` | os textos do aviso em português (o padrão do widget é o inglês, `..._LANGUAGE_EN`) |
| `CONFIG_NICE_OLED_WIDGET_LED_TOAST_MS` | `1500` | por quanto tempo o aviso fica na tela, em milissegundos (200 a 10000). Com `CONFIG_KEYPAW_DISPLAY_SETTINGS=y` esta opção não vale: o aviso (ligado ou desligado) e o tempo dele são configurações do ZMK Studio, e o tempo padrão passa a ser `CONFIG_KEYPAW_DISPLAY_TOAST_MS_DEFAULT` (1500) |

As alternativas estão comentadas no próprio `corne_right.conf`: outra animação (`CONFIG_NICE_OLED_WIDGET_ANIMATION_PERIPHERAL_GEM`, `_HEAD`, `_POKEMON` ou `_SPACEMAN`: desligue o gato e ligue uma delas) ou uma imagem parada, que gasta menos bateria (`CONFIG_NICE_OLED_WIDGET_ANIMATION_PERIPHERAL=n` e `CONFIG_NICE_OLED_WIDGET_STATIC_IMAGE_PERIPHERAL=y`, com `CONFIG_NICE_OLED_WIDGET_STATIC_IMAGE_PERIPHERAL_VIM` ou `CONFIG_NICE_OLED_WIDGET_STATIC_IMAGE_PERIPHERAL_VIP_MARCOS`). Não testado neste teclado.

**Posição dos widgets.** Cada widget tem opções `..._CUSTOM_X` e `..._CUSTOM_Y` que mudam onde ele é desenhado (por exemplo `CONFIG_NICE_OLED_WIDGET_BATTERY_CUSTOM_X` e `_Y` na esquerda, `CONFIG_NICE_OLED_WIDGET_ANIMATION_PERIPHERAL_CUSTOM_X` e `_Y` na direita). Não testado neste teclado.

Todas as opções `CONFIG_NICE_OLED_*`, com padrões e descrições, estão no [README do fork em português](https://github.com/lenerdz/zmk-nice-oled/blob/zmk-main/README.pt-BR.md).

Antes de as opções da central irem para o `corne_left.conf`, elas ficavam no `corne.conf`, valiam para as duas metades e o build da direita mostrava avisos do Kconfig sobre os widgets de WPM do `nice_oled`. Agora o build da direita não as define: o log do GitHub Actions desta mudança não tem mais esses avisos (o `.config` das duas metades também confirma as opções de cada arquivo).

#### Aviso das luzes (toast)

**Não testado neste teclado.** O código compila no GitHub Actions e a formatação dos textos foi conferida no computador, mas o aviso nunca foi visto numa tela de verdade. A posição foi calculada a partir da geometria da tela (veja abaixo) e pode precisar de ajuste.

Com `CONFIG_NICE_OLED_WIDGET_LED_TOAST=y` (só existe no build da metade periférica, a direita), a tela mostra, por `CONFIG_NICE_OLED_WIDGET_LED_TOAST_MS` (ou pelo tempo da aba Display, veja [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display)) depois de uma mudança nas luzes, duas linhas de até 8 caracteres na faixa livre embaixo da animação do gato. Uma mudança nova substitui a que está na tela e reinicia a contagem. Com `CONFIG_NICE_OLED_WIDGET_LED_TOAST_LANGUAGE_PT_BR=y` os textos são:

| O que mudou | Primeira linha | Segunda linha |
|---|---|---|
| Efeito | `EFEITO 4` (ou `EFX 12` a partir do décimo) | o nome do efeito em maiúsculas, cortado em 8 letras: `RAINBOW`, `STARLIGH` |
| Ligar ou apagar | `LUZES` | `LIGADAS` ou `APAGADAS` |
| Brilho | `BRILHO` | `70%` (a escala de 0 a 100 de [Controles no dia a dia](#controles-no-dia-a-dia)) |
| Matiz | `MATIZ` | `210 deg` |
| Saturação | `SATUR.` | `100%` |
| Ciclo da animação | `CICLO` | `3000 ms` |
| Reset | `LUZES` | `RESET` |

O número do efeito é a posição na tabela de [Efeitos instalados](#efeitos-instalados) mais um (`fx_solid` é o `EFEITO 1`). O aviso vem do evento `zmk_rgb_matrix_changed` do módulo zmk-rgb-matrix (opção `CONFIG_KEYPAW_RGB_MATRIX_CHANGE_EVENT`, ligada por padrão), disparado nas duas metades: por isso uma tecla de luz apertada em qualquer uma das metades faz o aviso aparecer na tela direita. Ele não aparece ao ligar o teclado, ao conectar a metade direita nem quando as cores são editadas pelo ZMK Studio.

**Geometria.** O canvas do widget tem 68 de largura por 160 de altura; no OLED de 128x32 só aparece a parte de x de 0 a 31 e y de 32 a 159 (a tela é girada). A animação do gato ocupa de y 73 a 141, e o aviso fica na faixa de y 142 a 159: a primeira linha em `CONFIG_NICE_OLED_WIDGET_LED_TOAST_CUSTOM_X`/`_Y` (padrão 0 e 143) e a segunda 8 pixels abaixo. Se você trocar a animação, ajuste essas duas opções. Texto, opções e posição estão no [README do fork em português](https://github.com/lenerdz/zmk-nice-oled/blob/zmk-main/README.pt-BR.md#toast-de-rgb-periférico).

## Compilar e gravar o firmware

### Compilar

O workflow `.github/workflows/build.yml` roda a cada push, a cada pull request e manualmente (aba **Actions**, workflow **Build ZMK firmware**, botão **Run workflow**). Ele chama o workflow de build do próprio ZMK, fixado no mesmo commit do ZMK de `config/west.yml`, e compila três firmwares definidos em `build.yaml`:

| Artefato | Shield | Observações |
|---|---|---|
| `corne_left` | `corne_left nice_oled` | snippet `studio-rpc-usb-uart` e `-DCONFIG_ZMK_STUDIO=y` (ZMK Studio), mais as opções de `config/corne_left.conf` (buffer de recepção do ZMK Studio, a tela esquerda e as transferências USB) e a segunda porta serial USB da camada GEMINI (nó `gemini_uart` em `config/corne_left.overlay`) |
| `corne_right` | `corne_right nice_oled` | metade periférica, com as opções de `config/corne_right.conf` (a tela direita) |
| `settings_reset` | `settings_reset` | limpa as configurações salvas |

Todos usam a placa `nice_nano//zmk`.

Como a raiz do repositório tem um `zephyr/module.yml`, o workflow de build do ZMK a compila como **módulo extra** (`-DZMK_EXTRA_MODULES` com a raiz do repositório) e trabalha numa cópia da pasta `config` em um diretório temporário, em vez de na pasta do repositório. Na prática, a primeira execução depois de o módulo entrar baixa os módulos do `west.yml` de novo, porque o cache dos módulos usa outro caminho; as seguintes voltam a usar o cache. O que o módulo contém está em [Como funciona por dentro](#como-funciona-por-dentro).

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

O `settings_reset.uf2` apaga tudo o que o teclado guardou: pareamentos Bluetooth, o estado das luzes (inclusive as cores editadas e salvas pela aba Lights), as configurações das telas (aba Display) e as alterações salvas pelo ZMK Studio. Use quando houver comportamento estranho depois de uma atualização grande, problema de pareamento entre as metades ou entre o teclado e o computador, ou para descartar as edições do Studio.

1. Grave o `settings_reset.uf2` nas **duas** metades.
2. Grave `corne_left.uf2` e `corne_right.uf2` nas respectivas metades.
3. Remova o teclado da lista de dispositivos Bluetooth do computador e pareie de novo.

## Módulos, forks e versões fixadas

### Versões fixadas

`config/west.yml` fixa tudo em commits exatos para que o build seja reproduzível:

| Componente | Origem | Revisão fixada | Observação |
|---|---|---|---|
| ZMK | `zmkfirmware/zmk`, branch `main` | `4dd95d7840eb3d5a3f59bb29fbf1ab054715ef85` (2026-10-09) | Zephyr 4.1. O mesmo commit é usado no `ref` de `.github/workflows/build.yml` |
| zmk-rgb-matrix | `lenerdz/zmk-rgb-matrix`, branch `corne-fixes` | `f0617b0dc2365e8bf3bfc7d083be14618fced718` | upstream `gudzpoz/zmk-rgb-matrix` em `a9add03` (2026-10-08) mais duas correções, os mapas de cor editáveis, o evento de mudança, a correção das teclas de brilho e as configurações das telas |
| zmk-nice-oled | `lenerdz/zmk-nice-oled`, branch `zmk-main` | `70f757f7766c3c4b1004a42acebbeb4fcb4d5013` | PR #37 do upstream (`de5b2af`) mais a correção do transporte `NONE` e o aviso das luzes na tela da periférica, que lê as configurações da aba Display |
| zmk-studio-messages | `lenerdz/zmk-studio-messages`, branch `main` | `caee958c434f40143eda7195c1ca0939bf905e8b` | `zmkfirmware/zmk-studio-messages` em `6cb4c28` (o commit que o ZMK fixa) mais as requisições dos mapas de cor e as das configurações das telas (e o limite de 15 mapas em `get_led_info`). Substitui o módulo de mesmo nome que o ZMK importa |

A ponta da `corne-fixes` (`f0617b0`), a da `zmk-main` (`70f757f`) e a da `main` do fork do protocolo (`caee958`) são os próprios pins. O módulo local deste repositório (o comportamento `&stn`, veja [Como funciona por dentro](#como-funciona-por-dentro)) não tem revisão fixada: ele é o próprio repositório, compilado junto com o firmware.

O app web ZMK Studio do fork `lenerdz/zmk-studio` não aparece no `west.yml`: ele não faz parte do firmware. Veja [Por que existem os forks](#por-que-existem-os-forks).

### Por que existem os forks

**zmk-rgb-matrix** (fork `lenerdz/zmk-rgb-matrix`, branch `corne-fixes`): o fork tem duas correções de problemas do upstream, cada uma com a própria branch para poder ser enviada ao autor, e três recursos novos (os mapas de cor editáveis, o evento de mudança e as configurações das telas), com uma correção que só existe na `corne-fixes`:

1. `fix/behavior-metadata-sets-type` (`98070e1`): o tipo do vetor `sets[]` em `behavior_rgb_matrix.c` causava erro de compilação quando o ZMK Studio está ligado (o build da metade esquerda).
2. `fix/physical-layout-lookup` (`2c1ecbe`): `kp_rgb_matrix_layout_init()` usava o primeiro layout físico da lista (o do Corne de 5 colunas, com 36 teclas) em vez do layout indicado em `physical-layout` (6 colunas, 42 teclas). Com isso, as teclas de polegar (posições 36 a 41) eram ignoradas pelos efeitos que dependem de posição e as outras teclas recebiam coordenadas erradas.
3. Mapas de cor editáveis (`6ebecb4`, mais `cfc69e4`, que faz a compilação falhar se o buffer de recepção do ZMK Studio for menor que 256 bytes; só na `corne-fixes`, não foi proposto ao upstream): slots de cor iguais nas duas metades, mapas que podem ser editados e salvos na memória da central, sincronização da metade direita e as requisições do ZMK Studio. O commit seguinte (`c4bf112`) só acrescenta a documentação (`README.md` e `README.pt-BR.md`). Veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio).
4. Evento de mudança e correção do brilho (`123f7ac`, só na `corne-fixes`): o evento `zmk_rgb_matrix_changed` (opção `CONFIG_KEYPAW_RGB_MATRIX_CHANGE_EVENT`) avisa, nas duas metades, o que um comando de luz do usuário mudou; a tela direita o usa para o [aviso das luzes](#aviso-das-luzes-toast). O mesmo commit corrige as teclas de brilho: a central converte `RGB_BRI` e `RGB_BRD` em `RGB_COLOR_HSB_CMD`, mas o tratamento desse comando só aplicava matiz e saturação, então o brilho do controlador nunca mudava, e a sincronização com a metade direita sempre enviava 100. Agora o comando aplica o brilho que carrega e a sincronização envia o brilho do controlador. O texto da seção "Change event" está no [README do fork](https://github.com/lenerdz/zmk-rgb-matrix/blob/corne-fixes/README.md#change-event) e no [em português](https://github.com/lenerdz/zmk-rgb-matrix/blob/corne-fixes/README.pt-BR.md#evento-de-mudança).
5. Configurações das telas (`2efbd69`, só na `corne-fixes`; o `3103ee2` e o `f0617b0` só acrescentam a documentação e os testes no computador): `CONFIG_KEYPAW_DISPLAY_SETTINGS`, seis configurações numeradas (o contraste de cada tela, quando apagar e o aviso das luzes), aplicadas na hora, guardadas na memória de cada metade, copiadas para a direita pela mesma sincronização dos mapas de cor e editadas pelo ZMK Studio por três requisições novas. O apagar de tela do módulo substitui o do ZMK (`CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=n` é obrigatório). Veja [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display), o [README do fork](https://github.com/lenerdz/zmk-rgb-matrix/blob/corne-fixes/README.md#display-oled-settings) e o [em português](https://github.com/lenerdz/zmk-rgb-matrix/blob/corne-fixes/README.pt-BR.md#configurações-da-tela-oled).

A branch `corne-fixes` reúne as duas correções e os recursos novos. O módulo ainda ignora a rotação das teclas de polegar (diferença pequena nas coordenadas).

**zmk-nice-oled** (fork `lenerdz/zmk-nice-oled`, branch `zmk-main`): a `main` do upstream (`mctechnology17/zmk-nice-oled`) mira o ZMK 0.3 e o LVGL 8. O [PR #37](https://github.com/mctechnology17/zmk-nice-oled/pull/37), de tokyo2006, migra o módulo para o ZMK `main` (Zephyr 4.1 e LVGL 9). A branch `zmk-main` do fork é esse PR mais uma correção: no ZMK `main`, a função que escolhe a saída devolve `ZMK_TRANSPORT_NONE` enquanto o USB não está pronto e o perfil Bluetooth ativo não está conectado, e o widget deixava o ícone de saída em branco nesse estado. Agora ele desenha o ícone de perfil sem pareamento ou sem sinal. A branch tem ainda um recurso novo, o **aviso das luzes** (`CONFIG_NICE_OLED_WIDGET_LED_TOAST`, commit `c13dbdd`, e o `7c93edd`, que só tira um aviso do compilador): na tela da periférica, mostra por um instante o que um comando de luz mudou, escutando o evento do zmk-rgb-matrix (veja [Aviso das luzes (toast)](#aviso-das-luzes-toast)). Com `CONFIG_KEYPAW_DISPLAY_SETTINGS=y`, o aviso ligado ou desligado e o tempo dele vêm das configurações 5 e 6 do zmk-rgb-matrix, editáveis pela aba Display (commit `70f757f`; veja [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display)).

**zmk-studio-messages** (fork `lenerdz/zmk-studio-messages`, branch `main`): o ZMK traz o protocolo do ZMK Studio como o módulo `zmk-studio-messages`, importado de `app/west.yml`, e o `config/west.yml` o substitui, com o mesmo nome e caminho, pelo fork. O fork parte do commit `6cb4c28`, o mesmo que o ZMK fixa, e acrescenta ao subsistema `keymap` as requisições e a notificação dos mapas de cor (`cfcce43`) e as requisições das configurações das telas (`caee958`, que também sobe de 8 para 15 o limite de mapas em `get_led_info`), com identificadores a partir de 100 para não colidir com os do upstream. O ZMK compila o protocolo junto com o firmware, então o módulo zmk-rgb-matrix usa as mensagens novas direto; o fork do app web traz um cliente TypeScript gerado a partir do mesmo protocolo (`src/vendor/zmk-studio-ts-client`) e é por ele que usa as mensagens novas. Veja o [README](https://github.com/lenerdz/zmk-studio-messages/blob/main/README.md) e o [README em português](https://github.com/lenerdz/zmk-studio-messages/blob/main/README.pt-BR.md) do fork.

**zmk-studio** (fork `lenerdz/zmk-studio`, branch `main`): é o app web do ZMK Studio, e não faz parte do firmware nem do `west.yml`. O fork parte de `zmkfirmware/zmk-studio` no commit `1bb6bb8` e acrescenta: o desenho das teclas (ícones e rótulos para Bluetooth, luzes, as animações do underglow, camadas, teclas de mídia, os macros do modo de estenotipia e as teclas `&stn` da estenotipia por acordes); a troca de teclas por arraste na visão Keys; a aba **Lights**, que edita as cores dos mapas de cor (veja [Editar as cores na aba Lights](#editar-as-cores-na-aba-lights)), e a aba **Display**, que configura as telas (veja [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display)), com um cliente TypeScript do protocolo estendido copiado para dentro do repositório (`src/vendor/zmk-studio-ts-client`, gerado a partir do `lenerdz/zmk-studio-messages` na revisão `caee958`), um teclado de demonstração (completo, sem mapas de luz e sem configurações das telas) e testes automáticos (`npm test`); os avisos de "fork não oficial"; e a hospedagem no GitHub Pages (workflow `pages.yml`, que roda os testes antes de publicar), em <https://lenerdz.github.io/zmk-studio/>. A ponta da `main` do fork é `13d0d44`. Os workflows `release-please` e `tauri-build` do upstream estão desativados nas configurações do fork. Veja o [README](https://github.com/lenerdz/zmk-studio/blob/main/README.md) e o [README em português](https://github.com/lenerdz/zmk-studio/blob/main/README.pt-BR.md) do fork.

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
| A tecla do efeito `static` (camada SYS, posição 32), as teclas do modo de estenotipia (SYS, posições 33 e 34), a tecla `&to 7` da camada GEMINI (SYS, posição 40), as teclas das animações do underglow (SYS, posições 26 a 29 e 35) ou as camadas STENO e GEMINI não aparecem no teclado | O mesmo caso da linha anterior: se você já editou teclas pelo Studio, o que foi salvo tem prioridade. Use "Restore Stock Settings" ou, para uma tecla avulsa, atribua o comportamento pelo próprio Studio |
| A cor ou a velocidade que ajustei nas teclas voltou depois de reiniciar | Sem `persist-id`, matiz, saturação e velocidade não são salvos. Veja [Salvar a cor e a velocidade ajustadas nas teclas](#salvar-a-cor-e-a-velocidade-ajustadas-nas-teclas) |
| O efeito ou o brilho voltou ao anterior depois de desligar o teclado | O estado é gravado 60 s depois da última alteração. Espere um minuto antes de desligar |
| Mudei `initial-effect` ou `initial-brightness` e nada mudou | O estado salvo tem prioridade sobre os valores iniciais. Aperte `RGB_RESET` (camada SYS, posição 23) depois de gravar |
| Troquei efeitos ou overlays e o comportamento ficou estranho (efeito errado, luzes que não ligam) | Grave as duas metades e aperte `RGB_RESET` (camada SYS, posição 23). Confira se as duas metades receberam o mesmo firmware |
| As luzes apagam sozinhas | É o padrão do módulo (apagam após 30 s sem digitar). Veja [Manter as luzes acesas quando o teclado fica ocioso](#manter-as-luzes-acesas-quando-o-teclado-fica-ocioso) |
| As teclas de polegar não reagem aos efeitos reativos | Corrigido no fork `corne-fixes`. Se voltar a acontecer, confira se `config/west.yml` aponta para o fork e não para o upstream |
| As teclas de brilho (camada SYS, posições 16 e 17) não mudam o brilho | Pela leitura do código, era um defeito do módulo: `RGB_COLOR_HSB_CMD`, em que a central converte `RGB_BRI` e `RGB_BRD`, só aplicava matiz e saturação. Corrigido no fork `corne-fixes` a partir do commit `123f7ac`: confira o pin em `config/west.yml` e grave as duas metades. **Não testado neste teclado** |
| O aviso das luzes não aparece na tela direita | O aviso só existe no build da metade direita: grave o firmware novo nela e confira se `config/corne_right.conf` tem `CONFIG_NICE_OLED_WIDGET_LED_TOAST=y` e se o aviso não está desligado na aba Display (**Light toast on the right screen**). Ele só aparece quando o comando muda algo (o mesmo efeito de novo, ou o brilho já no limite, não avisa). Se o texto aparecer cortado ou sobre o gato, ajuste `CONFIG_NICE_OLED_WIDGET_LED_TOAST_CUSTOM_Y` (padrão 143). **Não testado neste teclado** |
| A aba Display não aparece no app | Ela só aparece depois de desbloquear o teclado (`&studio_unlock`), no [fork do app](https://lenerdz.github.io/zmk-studio/) (o app oficial não tem a aba) e com um firmware que tem as configurações das telas: `config/corne.conf` com `CONFIG_KEYPAW_DISPLAY_SETTINGS=y` e, em `config/west.yml`, o `zmk-rgb-matrix` na `f0617b0` ou mais nova e o `zmk-studio-messages` na `caee958` ou mais nova. Com outro firmware o teclado responde "RPC not found" e o app não oferece a aba. Se `CONFIG_ZMK_DISPLAY_BLANK_ON_IDLE=y` for ligada, o build **termina sem erro**, mas o Kconfig desliga as configurações das telas e deixa só um aviso no log (`KEYPAW_DISPLAY_SETTINGS ... was assigned the value 'y' but got the value 'n'`, com a dependência `(!ZMK_DISPLAY_BLANK_ON_IDLE) (=n)`; visto em um build de teste no GitHub Actions): volte a opção para `n`. Grave a metade esquerda. **Não testado neste teclado** (a aba em si; o aviso do Kconfig foi visto no log do CI) |
| A tela direita apaga com o teclado no USB, ou apaga enquanto só digito na esquerda | O USB e a atividade são vistos por metade. A metade direita costuma estar sem cabo, então **Only on battery** apaga a tela dela mesmo com o teclado no USB, e ela só conta as teclas que você aperta nela mesma. Para as duas telas ficarem sempre acesas, deixe **Never** (o padrão). Veja [Apagar a tela](#apagar-a-tela). **Não testado neste teclado**: baseado no código do ZMK |
| Mudei uma configuração da tela e ela voltou ao que era depois de reiniciar | O teclado grava a mudança `CONFIG_KEYPAW_DISPLAY_SAVE_DEBOUNCE_MS` (3 s) depois da última: espere alguns segundos antes de desligar. "Restore Stock Settings" e o `settings_reset` também devolvem as configurações ao padrão. **Não testado neste teclado** |
| O contraste ou o aviso da tela direita não mudou | A direita recebe as configurações da esquerda por Bluetooth, um comando a cada 50 ms, e só depois de conectar (ela guarda o último valor e já liga com ele). Confira se as duas metades estão ligadas, conectadas e gravadas com este firmware (`CONFIG_KEYPAW_DISPLAY_SETTINGS=y` vale para as duas). **Não testado neste teclado** |
| As animações do underglow (teclas `&ug_*` da SYS) não aparecem | Elas só aparecem na camada QWERTY, com as luzes ligadas (`RGB_TOG`): nas camadas FN1 a GEMINI o mapa da camada cobre o underglow, inclusive enquanto você está na SYS tocando a tecla. Ao reiniciar o teclado todas voltam a desligadas. Com duas ligadas, vale a de baixo da tabela, e `&ug_off` apaga o underglow. **Não testado neste teclado** |
| O build falha com `node name must fit the 9-byte split behavior_dev field (<= 8 characters)` | O nome do nó de um interruptor de animação (o filho `ug_*` de uma condição `latch`) tem mais de 8 caracteres. Encurte o nome: o do overlay e o da condição não têm esse limite |
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
| A aba Lights não aparece no app | Ela só aparece depois de desbloquear o teclado (`&studio_unlock`) e com um firmware que tem os mapas editáveis, e só no [fork do app](https://lenerdz.github.io/zmk-studio/): o app oficial não tem a aba. Com outro firmware (sem o fork do protocolo ou sem o módulo zmk-rgb-matrix do fork) o teclado responde "RPC not found" à primeira requisição e o app não oferece a aba. Confira o `config/west.yml` e grave a metade esquerda |
| Pintei LEDs na aba Lights e o teclado não mudou, ou o app avisou que as cores não puderam ser definidas | Confira se a metade esquerda foi compilada com `CONFIG_ZMK_STUDIO_RPC_RX_BUF_SIZE=256` (`config/corne_left.conf`): com o padrão do ZMK (30 bytes) os pedidos de edição chegam cortados e o log do teclado mostra `Dropping incoming RPC byte, insufficient room in the RX buffer`. **Não testado neste teclado**: baseado no código do ZMK |
| O build da metade esquerda falha com `ZMK Studio would drop the bytes of a set_led_colors request` | O `config/corne_left.conf` foi apagado ou não está sendo aplicado: ele precisa ter `CONFIG_ZMK_STUDIO_RPC_RX_BUF_SIZE=256` (ou mais). O módulo zmk-rgb-matrix confere esse valor de propósito |
| As cores que pintei na aba Lights sumiram depois de reiniciar o teclado | A edição vale só até desligar, a não ser que você clique em **Save** (canto superior direito do app). Elas também são apagadas por "Restore Stock Settings", por `RGB_RESET` e pelo `settings_reset` |
| Pinto na aba Lights e só a metade esquerda muda | A metade direita recebe as edições da esquerda por Bluetooth, um slot a cada 50 ms, e só depois de conectar. Confira se as duas metades estão ligadas, conectadas e com o firmware da mesma compilação. **Não testado neste teclado** |
| Apertei `&steno_on` e apareceram as letras `erfvtik` (ou o Plover não ligou) | O acorde só vira comando com o Plover aberto, com a máquina Keyboard e os mapas padrão (`commands.json`); sem isso as sete teclas são digitadas. Confira o Plover e veja [Modo de estenotipia (Plover)](#modo-de-estenotipia-plover). **Não testado neste teclado**: baseado no código do Plover |
| `&steno_off` digitou `erfvtu` na janela | O Plover estava suspenso ou fechado: o comando de suspender só vale com a saída do Plover ligada. Use `&to 0` para voltar ao QWERTY sem acorde. **Não testado neste teclado**: baseado no código do Plover |
| A camada STENO só digita letras e o Plover não traduz | O Plover pode estar suspenso ou fora de sincronia com o teclado. Toque `&steno_on` outra vez ou ligue a saída pelo próprio Plover |
| Apertei acordes na camada GEMINI e o Plover não recebe nada | Confira, nesta ordem: o teclado está por USB na metade esquerda (a porta não existe por Bluetooth); o Plover está com a máquina **Gemini PR** (e não **Keyboard**) e conectada; a porta escolhida no Plover é a do Plover e não a do ZMK Studio (o computador mostra duas portas do teclado: tente a outra); nenhum outro programa, como o app do Studio, está com a porta aberta; o Plover abriu a porta antes de você apertar o acorde (o teclado descarta os acordes enquanto a porta está fechada); se nada disso resolver, teste `CONFIG_ZMK_STENO_GEMINI_REQUIRE_DTR=n` em `config/corne_left.conf` (o acorde passa a sair mesmo com a porta fechada: se assim chegar, o computador não está levantando o sinal DTR ao abrir a porta). Veja [Configurar o Plover](#configurar-o-plover). **Não testado neste teclado**: baseado no código do Plover e do Zephyr |
| O computador mostra duas portas seriais do teclado, ou o app do ZMK Studio não conecta | É esperado desde a camada GEMINI: a segunda porta serial USB é a do Plover. Ao conectar o Studio, escolha a outra porta. Se o app continuar sem conectar, feche o Plover (ele pode estar com a porta do Studio aberta) e tente de novo. **Não testado neste teclado** |
| O build da esquerda falha com `more colour maps than the LedInfo of the protocol can list` | Há mais de 15 mapas de cor (`layer-id`). Aumente `layer_ids max_count` em `proto/zmk/keymap.options.in` do fork `lenerdz/zmk-studio-messages` e atualize o pin em `config/west.yml` (veja [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio)) |
| Avisos do Kconfig sobre widgets de WPM, modificadores ou bateria no build da metade direita | As opções dos widgets da central ficam em `config/corne_left.conf`. Se os avisos voltarem, alguma delas foi parar no `corne.conf` ou no `corne_right.conf`. O aviso sobre `ZMK_USB` (a periférica não tem a dependência de USB do ZMK) é esperado e continua aparecendo |

## Manter este README atualizado

Este README é a documentação do projeto e deve acompanhar o repositório: **sempre que algo for adicionado, alterado, atualizado ou removido, atualize a seção correspondente na mesma mudança.** Existe uma regra do Cursor (`.cursor/rules/readme-sync.mdc`) que faz o assistente fazer isso a cada mudança.

| O que mudou | Seção a revisar |
|---|---|
| Teclas, camadas, macros ou nomes de camada em `config/corne.keymap` | [Teclado: posições, camadas e funções](#teclado-posições-camadas-e-funções) (inclusive [Modo de estenotipia (Plover)](#modo-de-estenotipia-plover)) e as cores da camada em `config/led_colors.dtsi` ([Cores por camada e indicador de Caps Lock](#cores-por-camada-e-indicador-de-caps-lock)) |
| Efeitos (`kprgb`, `fx_*`), brilhos, condições ou overlays em `config/corne.keymap` | [Luzes](#luzes-rgb-por-tecla-e-underglow) |
| `config/corne_left.overlay` ou `config/corne_right.overlay` | [Mapa dos LEDs](#mapa-dos-leds), [Slots de cor](#slots-de-cor) e, se o `mapping`, o `slot-count` ou o `no-key-slots` mudarem, a macro `LED_SLOT_ORDER` em `config/led_colors.dtsi` |
| `config/led_colors.dtsi` (cores, paleta, ordem dos slots) | [Cores por camada e indicador de Caps Lock](#cores-por-camada-e-indicador-de-caps-lock), [Slots de cor](#slots-de-cor) e as receitas do [Guia de configuração](#guia-de-configuração) que mostram trechos do arquivo |
| Fork do protocolo (`lenerdz/zmk-studio-messages`), `src/studio_rpc.c`, `src/rgb_maps.c` ou `src/rgb_split_sync.c` do zmk-rgb-matrix | [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio) (requisições, IDs e limites) e [Módulos, forks e versões fixadas](#módulos-forks-e-versões-fixadas) |
| Configurações das telas: `src/display_settings.c`, `src/studio_rpc_display.c`, `Kconfig` ou `include/zmk/display_settings.h` do zmk-rgb-matrix, `widgets/screen_peripheral.c` do zmk-nice-oled, ou as requisições 106 a 108 do fork do protocolo | [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display) (ids, faixas, padrões, modos de apagar, memória e metade direita), [O que é salvo na memória](#o-que-é-salvo-na-memória), [Telas OLED](#telas-oled) e [Módulos, forks e versões fixadas](#módulos-forks-e-versões-fixadas) |
| `config/corne.conf`, `config/corne_left.conf` ou `config/corne_right.conf` | [Telas OLED](#telas-oled) (as três tabelas de opções), [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display) (`CONFIG_KEYPAW_DISPLAY_SETTINGS`), [Funções e recursos](#funções-e-recursos), [Modo de estenotipia (Plover)](#modo-de-estenotipia-plover) (NKRO), [ZMK Studio](#zmk-studio) (buffer de recepção) e [O que é salvo na memória](#o-que-é-salvo-na-memória) |
| `config/west.yml` ou `.github/workflows/build.yml` | [Módulos, forks e versões fixadas](#módulos-forks-e-versões-fixadas) |
| `build.yaml` | [Compilar e gravar o firmware](#compilar-e-gravar-o-firmware) |
| Código do módulo local (`src/`, `include/`, `dts/`, `Kconfig`, `CMakeLists.txt` e `zephyr/module.yml`) | [Estenotipia por acordes (Gemini PR)](#estenotipia-por-acordes-gemini-pr), [Estrutura do repositório](#estrutura-do-repositório) e [Compilar](#compilar) |
| Arquivo criado, movido ou removido | [Estrutura do repositório](#estrutura-do-repositório) |
| Fork do app ZMK Studio (`lenerdz/zmk-studio`): ícones, arraste de teclas, aba Lights, aba Display, hospedagem ou commit | [ZMK Studio](#zmk-studio), [Mapas de cor editáveis pelo ZMK Studio](#mapas-de-cor-editáveis-pelo-zmk-studio), [Configurar as telas pelo ZMK Studio (aba Display)](#configurar-as-telas-pelo-zmk-studio-aba-display) e [Módulos, forks e versões fixadas](#módulos-forks-e-versões-fixadas) |
| Problema encontrado ou resolvido | [Solução de problemas](#solução-de-problemas) |

## Referências

- ZMK: [documentação](https://zmk.dev/docs), [ZMK Studio](https://zmk.dev/docs/features/studio) e [Caps Word](https://zmk.dev/docs/keymaps/behaviors/caps-word).
- Plover (estenotipia): [código](https://github.com/openstenoproject/plover), [documentação](https://plover.readthedocs.io/en/latest/) e o [PR 962 do ZMK](https://github.com/zmkfirmware/zmk/pull/962) (suporte ao Plover HID, ainda aberto).
- Gemini PR (camada GEMINI): a [máquina Gemini PR do Plover](https://github.com/openstenoproject/plover/blob/main/plover/machine/gemini_pr.py) (o formato do pacote) e os [mapas de teclas padrão do Plover](https://github.com/openstenoproject/plover/blob/main/plover/system/english_stenotype.py).
- zmk-rgb-matrix: [upstream](https://github.com/gudzpoz/zmk-rgb-matrix) e [documentação](https://gudzpoz.github.io/zmk-rgb-matrix/); [fork](https://github.com/lenerdz/zmk-rgb-matrix) e seu [README em português](https://github.com/lenerdz/zmk-rgb-matrix/blob/corne-fixes/README.pt-BR.md), com as seções [Slots de cor e mapas de cores editáveis](https://github.com/lenerdz/zmk-rgb-matrix/blob/corne-fixes/README.pt-BR.md#slots-de-cor-e-mapas-de-cores-editáveis) e [Configurações da tela (OLED)](https://github.com/lenerdz/zmk-rgb-matrix/blob/corne-fixes/README.pt-BR.md#configurações-da-tela-oled).
- zmk-nice-oled: [upstream](https://github.com/mctechnology17/zmk-nice-oled), [PR #37](https://github.com/mctechnology17/zmk-nice-oled/pull/37); [fork](https://github.com/lenerdz/zmk-nice-oled) e seu [README em português](https://github.com/lenerdz/zmk-nice-oled/blob/zmk-main/README.pt-BR.md).
- zmk-studio-messages: [upstream](https://github.com/zmkfirmware/zmk-studio-messages); [fork](https://github.com/lenerdz/zmk-studio-messages) e seu [README em português](https://github.com/lenerdz/zmk-studio-messages/blob/main/README.pt-BR.md).
- zmk-studio: [upstream](https://github.com/zmkfirmware/zmk-studio); [fork](https://github.com/lenerdz/zmk-studio), seu [README em português](https://github.com/lenerdz/zmk-studio/blob/main/README.pt-BR.md), a documentação das abas [Lights](https://github.com/lenerdz/zmk-studio/blob/main/src/lights/README.md) e [Display](https://github.com/lenerdz/zmk-studio/blob/main/src/display/README.md) (em inglês) e o [app publicado](https://lenerdz.github.io/zmk-studio/).
- Este repositório: [lenerdz/corne-zmk](https://github.com/lenerdz/corne-zmk).
