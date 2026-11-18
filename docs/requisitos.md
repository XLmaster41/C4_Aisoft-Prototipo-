# Requisitos do Sistema

## Atores

| Ator | Responsabilidade |
|---|---|
| Organizador | Liga, seleciona modo, configura tempo, inicia e reinicia. |
| Participante/equipe | Interage com os botões conforme as regras. |
| Dispositivo | Processa entradas, controla estados e tempo, apresenta informações e alertas. |

## Personas (hipotéticas, não validadas)

| Persona | Necessidades | Influência no projeto |
|---|---|---|
| Organizador | Selecionar modo, configurar duração, iniciar e acompanhar o fim. Precisa de comandos simples. | Fluxo guiado, configuração comum, mensagens curtas, início por pressão longa e reinício. |
| Participante/equipe | Interagir com botões e entender o estado exibido. | Botões contextuais, feedback visual/sonoro, regra explícita de Neutro. |

## Jornada do organizador

| Etapa | Ação | Resposta do sistema |
|---|---|---|
| Preparação | Liga o dispositivo | LCD apresenta C4 Airsoft |
| Seleção | Escolhe Sabotagem ou Dominação | Modo apresentado no LCD |
| Configuração | Toques curtos em D3 | +5 min por toque; limite 99:00 |
| Início | Mantém D3 por ~2 s | Inicia se tempo > 0 |
| Execução | Acompanha; participantes interagem | Atualiza tempo, estado e acumuladores |
| Finalização | Aguarda término | LCD e buzzer sinalizam; Dominação mostra resultado |
| Reinício | Aciona D3 | Retorna à tela inicial |

## MVP

**Essenciais**
- Inicializar e apresentar tela inicial.
- Selecionar Sabotagem ou Dominação.
- Configurar tempo comum, em incrementos de 5 min, limite 99:00.
- Iniciar por pressão longa de D3, somente com tempo > 0.
- Sabotagem: contagem regressiva com +7 s (D4) e −9 s (D5).
- Dominação: acumuladores por equipe, só com um botão de equipe pressionado sozinho.
- Exibir modo, tempo, estado e mensagens finais no LCD.
- Sinais sonoros de início e fim em 959 Hz.
- Reiniciar o ciclo.

**Secundárias**
- Mensagem de orientação quando o tempo é zero.
- Repetição de ajustes em Sabotagem a cada 250 ms.
- Resultado final da Dominação: vitória Amarela, Azul ou empate.
- Debounce de 40 ms.

**Fora do MVP**
- Protótipo físico e testes de campo.
- RFID/autenticação, sensores adicionais, aplicativo externo.
- Bluetooth, Wi-Fi ou LoRa.
- Armazenamento EEPROM/SD.
- Medição de autonomia, resistência ambiental e alcance sonoro.
- Avaliação de treinamento ou experiência dos jogadores.

## Requisitos funcionais

| ID | Requisito | Descrição |
|---|---|---|
| RF01 | Inicializar | Inicializar e apresentar interface inicial. |
| RF02 | Selecionar modo | Permitir Sabotagem ou Dominação. |
| RF03 | Configurar tempo | Definir tempo da dinâmica. |
| RF04 | Iniciar | Aguardar confirmação antes da execução. |
| RF05 | Controlar tempo | Realizar controle temporal automático. |
| RF06 | Apresentar informações | Exibir modo, tempo e estado no LCD. |
| RF07 | Alertas sonoros | Sinalizar início e encerramento em 959 Hz. |
| RF08 | Executar Sabotagem | Contagem regressiva com acréscimo/redução. |
| RF09 | Executar Dominação | Controlar Neutro/Azul/Amarelo, acumular tempo e determinar resultado. |
| RF10 | Informar encerramento | Indicar visual e sonoramente a finalização. |
| RF11 | Reiniciar | Retornar ao estado inicial. |

## Requisitos não funcionais

| ID | Requisito | Descrição |
|---|---|---|
| RNF01 | Simplicidade | Poucos comandos; três botões e telas contextualizadas. |
| RNF02 | Modularidade | Separar entrada, interface, tempo e modos por rotinas. |
| RNF03 | Expansibilidade | Separar estrutura comum e regras específicas. |
| RNF04 | Autonomia | Executar ciclo sem comando externo contínuo. |
| RNF05 | Baixa complexidade | Restringir componentes ao MVP. |
| RNF06 | Clareza | Mensagens dentro de duas linhas de 16 caracteres. |

## Regras de negócio

- A configuração de tempo é comum aos dois modos.
- Sabotagem é pré-selecionada; D4 seleciona Sabotagem, D5 seleciona Dominação e D3 confirma.
- Toques curtos em D3 acrescentam 5 min; limite de configuração 99:00.
- D3 pressionado por ~2 s inicia somente se o tempo for maior que zero.
- Em Sabotagem, D4 soma 7 s e D5 subtrai 9 s; os dois simultâneos não produzem ajuste.
- Em Dominação, D4 = Amarelo e D5 = Azul.
- Somente um botão de equipe pressionado sozinho acumula tempo; nenhum ou ambos = Neutro.
- A liberação retorna a Neutro e preserva os tempos acumulados.
- O resultado compara os acumuladores em milissegundos; igualdade exata = empate.

## Histórias de usuário

| ID | História | Critério de aceitação |
|---|---|---|
| HU01 | Como organizador, quero inicializar o dispositivo. | LCD apresenta a identificação C4 Airsoft. |
| HU02 | Quero selecionar um modo. | D4/D5 selecionam e D3 confirma. |
| HU03 | Quero configurar a duração. | Cada toque curto em D3 soma 5 min, respeitando 99:00. |
| HU04 | Quero iniciar a dinâmica. | Pressão longa inicia apenas com tempo > 0. |
| HU05 | Quero ajustar Sabotagem. | D4 soma 7 s e D5 subtrai 9 s. |
| HU06 | Quero representar domínio na Dominação. | Acumula só enquanto o botão da equipe estiver pressionado sozinho. |
| HU07 | Quero identificar o encerramento. | LCD e buzzer indicam fim; Dominação exibe resultado. |
| HU08 | Quero iniciar novo ciclo. | D3 reinicia e retorna à tela inicial. |

## Telas do LCD (16x2)

| Tela | Conteúdo |
|---|---|
| Inicial | `C4` / `AIRSOFT` |
| Seleção | `MODO` / `SABOTAGEM` ou `DOMINACAO` |
| Configuração | `TEMPO` / `MM:SS` |
| Sabotagem | `SABOTAGEM` / tempo restante |
| Dominação (neutro) | `DOMINACAO` / tempo restante |
| Dominação (equipe) | `TIME DOMINANDO` / `AMARELO` ou `AZUL` |
| Final Sabotagem | `BOMBA` / `DETONADA!` |
| Final Dominação | `DOMINACAO` / `CONCLUIDA`; depois `FIM DE JOGO` / resultado |
| Tempo zero ao iniciar | `DEFINA O TEMPO` / `ANTES DE INICIAR` |

## Decisões de usabilidade

- Três botões contextuais reduzem a quantidade de controles.
- O LCD apresenta somente o necessário a cada etapa.
- Configuração compartilhada evita duplicar telas e regras.
- Pressão longa em D3 reduz início acidental.
- Buzzer complementa o feedback visual.
- Neutro evita atribuir domínio quando nenhum ou ambos os botões estão pressionados.

> Não houve teste formal de usabilidade com participantes.
