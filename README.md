# C4 Airsoft

Dispositivo eletrônico embarcado, baseado em **Arduino UNO**, para gerenciar tempo, estados e regras de dinâmicas de airsoft. Dois modos de jogo — **Sabotagem** e **Dominação** — compartilham o mesmo hardware e a mesma etapa de configuração.

> Trabalho Final — Laboratório de Engenharia de Software
> "Da ideia ao MVP: análise, projeto, desenvolvimento, testes e reflexão"

## Integrantes e instituição

| Integrante | Papel |
|---|---|
| Gabriel Oliveira Neves | Discente |
| Victor Jesus Gama da Silva | Discente |

- **Docente:** Maricy Caregnato
- **Instituição:** Universidade do Estado de Mato Grosso (UNEMAT), Campus “Jane Vanini” — Cáceres/MT
- **Simulação (Tinkercad):** https://www.tinkercad.com/things/f96OpHrRg1R-projeto-c410

## Objetivo

Em dinâmicas de airsoft, o controle do tempo, do estado do objetivo, do domínio das equipes e do encerramento costuma depender de intervenção manual. O C4 Airsoft propõe automatizar isso em um dispositivo simples, operado por três botões, com LCD 16x2 e buzzer.

> O problema é tratado como necessidade de projeto, não como prevalência comprovada por pesquisa de campo.

## Funcionalidades

### Fluxo comum
1. **Tela inicial** `C4 AIRSOFT`; `D3` avança.
2. **Seleção de modo:** `D4` = Sabotagem, `D5` = Dominação, `D3` confirma (Sabotagem vem pré-selecionada).
3. **Configuração de tempo (comum aos dois modos):** cada toque curto em `D3` soma 5 min, limite de **99:00**.
4. **Início:** manter `D3` pressionado por ~2 s (somente se o tempo for maior que zero). Dois bipes de 959 Hz.

### Modo Sabotagem
- Contagem regressiva exibida no LCD.
- `D4` soma **7 s**; `D5` subtrai **9 s** (repete a cada 250 ms enquanto mantido pressionado).
- Os dois botões ao mesmo tempo não produzem ajuste.
- Ao chegar a zero: `BOMBA DETONADA!` + sinal sonoro.

### Modo Dominação
- `D4` = equipe **Amarela**, `D5` = equipe **Azul**.
- Só acumula tempo quando **exatamente um** botão de equipe está pressionado; nenhum ou ambos = **Neutro**.
- Acumuladores independentes em milissegundos (`yellowMilliseconds`, `blueMilliseconds`).
- Ao final: `DOMINACAO CONCLUIDA`, e em seguida `FIM DE JOGO` com `VENCEU: AMARELO`, `VENCEU: AZUL` ou `EMPATE`.

### Reinício
Ao término, `D3` retorna à tela inicial.

## Componentes e pinos

| Componente | Pino / valor | Função |
|---|---|---|
| Arduino UNO | — | Processamento central |
| LCD 16x2 I2C | `0x27` (SDA/SCL: A4/A5) | Interface visual |
| Botão D3 | `D3` (`INPUT_PULLUP`) | Confirmar / +5 min / iniciar (2 s) / reiniciar |
| Botão D4 | `D4` (`INPUT_PULLUP`) | Sabotagem: +7 s · Dominação: Amarelo |
| Botão D5 | `D5` (`INPUT_PULLUP`) | Sabotagem: −9 s · Dominação: Azul |
| Buzzer | `D6` | Alertas de início e fim (959 Hz) |

Os botões usam `INPUT_PULLUP`: ligue um terminal de cada botão ao pino e o outro ao **GND** (pressionado = `LOW`).

### Parâmetros do código

| Constante | Valor | Descrição |
|---|---|---|
| `HOLD_MS` | 2000 ms | Pressão longa para iniciar |
| `DEBOUNCE_MS` | 40 ms | Tratamento de repique |
| `MAX_SETUP_SECONDS` | 5940 s | Limite de 99:00 |
| `ADJUST_REPEAT_MS` | 250 ms | Repetição do ajuste em Sabotagem |
| Tom do buzzer | 959 Hz | Frequência (não é decibéis) |

## Tecnologias

- C/C++ para Arduino (Arduino IDE)
- Bibliotecas: `Wire.h` (nativa) e `LiquidCrystal_I2C.h`
- Tinkercad Circuits (simulação)
- Draw.io (fluxos e diagramas)

Não há backend, frontend web, banco de dados, API ou serviço externo: tudo executa localmente no microcontrolador.

## Como compilar e executar

1. Instale a [Arduino IDE](https://www.arduino.cc/en/software).
2. Em **Sketch → Incluir Biblioteca → Gerenciar Bibliotecas**, instale **LiquidCrystal I2C** (ex.: a de Frank de Brabander).
3. Abra `src/C4_Airsoft/C4_Airsoft.ino`.
   > O Arduino IDE exige que o `.ino` esteja numa pasta de mesmo nome, por isso o sketch fica em `src/C4_Airsoft/`.
4. Selecione **Placa: Arduino Uno** e a porta correta.
5. Clique em **Verificar** e depois em **Carregar**.

Se o LCD não exibir nada, confirme o endereço I2C (`0x27`; alguns módulos usam `0x3F`) e ajuste a linha `LiquidCrystal_I2C lcd(0x27, 16, 2);`.

## Como reproduzir a simulação

Veja [`simulation/README.md`](simulation/README.md).

## Estrutura do repositório

```
C4-Airsoft/
├── README.md
├── .gitignore
├── src/
│   └── C4_Airsoft/
│       └── C4_Airsoft.ino
├── docs/
│   ├── arquitetura.md
│   ├── requisitos.md
│   ├── testes.md
│   ├── metodologia.md
│   ├── decisoes-tecnicas.md
│   ├── uso-de-ia.md
│   └── imagens/
└── simulation/
    └── README.md
```

## Limitações

- Validação **somente em simulação virtual** (Tinkercad) e por inspeção de código.
- **Não houve protótipo físico validado**, testes de campo ou avaliação com jogadores.
- Sem medição de autonomia, resistência ambiental ou alcance sonoro.
- Persona e requisitos não foram validados com usuários reais.

## Trabalhos futuros

- Protótipo físico e testes de bancada.
- Avaliar alimentação, autonomia e proteção do circuito.
- Modelagem explícita de estados (máquina de estados).
- Novos modos, RFID, armazenamento (EEPROM/SD) ou comunicação sem fio, se houver necessidade.

## Diagramas e evidências

Veja [`docs/imagens/`](docs/imagens/) (arquitetura, circuito, wireframes, diagrama de estados e capturas da simulação).

## Documentação

- [Requisitos](docs/requisitos.md)
- [Arquitetura](docs/arquitetura.md)
- [Testes](docs/testes.md)
- [Metodologia e backlog](docs/metodologia.md)
- [Matriz de decisões técnicas](docs/decisoes-tecnicas.md)
- [Uso de IA](docs/uso-de-ia.md)
# C4_Aisoft-
