# Simulação (Tinkercad Circuits)

**Link do circuito:** [INSERIR LINK REAL DO TINKERCAD]

## Montagem do circuito

| Componente | Ligação |
|---|---|
| Arduino UNO | Placa principal |
| LCD 16x2 I2C (0x27) | GND→GND · VCC→5V · SDA→A4 · SCL→A5 |
| Botão D3 | Um terminal em `D3`, o outro em `GND` |
| Botão D4 | Um terminal em `D4`, o outro em `GND` |
| Botão D5 | Um terminal em `D5`, o outro em `GND` |
| Buzzer piezo | Positivo em `D6`, negativo em `GND` |

Os botões usam resistores *pull-up* internos (`INPUT_PULLUP`); não são necessários resistores externos.

## Como executar

1. Abra o link do circuito no Tinkercad (ou crie um circuito novo com os componentes acima).
2. Clique em **Código → Texto** e cole o conteúdo de [`../src/C4_Airsoft/C4_Airsoft.ino`](../src/C4_Airsoft/C4_Airsoft.ino).
3. Clique em **Iniciar simulação**.
4. Siga o roteiro de demonstração:
   1. Pressione `D3` para sair da tela inicial.
   2. Escolha o modo (`D4` = Sabotagem, `D5` = Dominação) e confirme com `D3`.
   3. Dê toques curtos em `D3` para somar 5 min cada.
   4. Mantenha `D3` pressionado por ~2 s para iniciar.
   5. **Sabotagem:** use `D4` (+7 s) e `D5` (−9 s).
   6. **Dominação:** mantenha `D4` (Amarelo) ou `D5` (Azul); solte ou pressione ambos para Neutro.
   7. Ao final, observe as mensagens e use `D3` para reiniciar.

> Dica: use 5 min como tempo mínimo de teste. Se quiser testes mais rápidos, reduza temporariamente o incremento de `5 * 60` em `loop()` — e volte ao valor original antes de entregar.

## Arquivos

Se desejar, salve aqui o arquivo do circuito exportado (`.brd`/`.png`) como complemento ao link.
