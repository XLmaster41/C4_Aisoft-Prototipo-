# Metodologia, Backlog e Incrementos

## Metodologia

Desenvolvimento tecnológico aplicado, orientado por requisitos (pesquisa aplicada, exploratória e descritiva, abordagem qualitativa e técnico-descritiva).

Etapas: levantamento bibliográfico narrativo e observação documental → identificação do problema → modelagem de regras → requisitos → arquitetura → prototipação virtual → programação → simulação → testes de conformidade → registro de evidências → análise.

> Não há documentação suficiente para afirmar aplicação integral do Scrum (papéis, cerimônias, duração fixa, métricas). A divisão individual de tarefas e reuniões não foi registrada. **Completar com o histórico real da equipe.**

## Backlog

| Prioridade | Item | Status |
| P1 | Inicialização e tela inicial | Implementado/simulado |
| P1 | Seleção dos modos | Implementado/simulado |
| P1 | Configuração temporal | Implementado/simulado |
| P1 | Início controlado | Implementado/simulado |
| P1 | Sabotagem +7/−9 s | Implementado/simulado; repetição por inspeção do código |
| P1 | Dominação e acumuladores | Implementado/simulado; simultaneidade/Neutro por código |
| P1 | Finalização e reinício | Implementado/simulado |
| P2 | Clareza e modularidade | Rotinas e mensagens documentadas |
| P3 | RFID, sensores, conectividade | Fora do MVP; futuro |
| P3 | Armazenamento | Fora do MVP; futuro |
| P3 | Protótipo físico | Não realizado |

Não há estimativas, datas ou cronograma de sprint verificáveis.

## Incrementos técnicos (retrospectivos)

> Não são sprints formais com datas e cerimônias. Associe a sprints reais somente se houver registros.

| # | Incremento | Realizado | Decisão | Lição aprendida |
|---|---|---|---|---|
| 1 | Concepção e delimitação | Proposta com dois modos e Arduino UNO | Manter duas dinâmicas e plataforma comum | Delimitar escopo antes de implementar |
| 2 | Requisitos, arquitetura e interface | RF01–RF11, RNF01–RNF06, blueprint, wireframes e fluxo | Interface contextual e configuração compartilhada | Regras claras reduzem ambiguidades |
| 3 | Implementação | Código C/C++ com seleção, configuração, Sabotagem, Dominação, finalização e reinício | Sabotagem ajustável; Dominação momentânea | Separar regras comuns e específicas |
| 4 | Simulação e testes | CT01–CT16 documentados | Distinguir simulação, inspeção de código e validação física | Rastreabilidade exige evidências adequadas |

## Decisões extras e mudanças

| Problema | Decisão e impacto |
|---|---|
| Dois modos distintos | Mesmo Arduino UNO; evita duplicação e demonstra flexibilidade do software |
| Configuração duplicada | Tempo compartilhado; simplifica o fluxo |
| Regra da Sabotagem | Contagem regressiva com +7/−9 s (em vez de ativar/desativar); requisitos atualizados |
| Regra da Dominação | Domínio momentâneo e acumuladores; exige tratamento de Neutro |
| Conectividade | Sem comunicação no MVP; menor complexidade |
| Validação | Tinkercad; conclusão limitada à verificação virtual |
