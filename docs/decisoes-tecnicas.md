# Matriz de Decisões Técnicas

| Decisão | Alternativas | Escolha e justificativa | Consequência |
|---|---|---|---|
| Microcontrolador | UNO / ESP32 | UNO: suficiente, documentado e compatível com a simulação | Sem conectividade nativa utilizada |
| Display | LCD 16x2 / gráfico | LCD 16x2 I2C: informação essencial e menor complexidade | Mensagens curtas |
| Entrada | Botões / touchscreen | Três botões: interação direta e simples | Funções contextuais |
| Comunicação LCD | Paralelo / I2C | I2C reduz conexões | Libera pinos |
| Feedback | Buzzer / alto-falante | Buzzer suficiente para validar alertas | Sem afirmação de alcance real |
| Temporização | Externa / Arduino | Temporizador no Arduino | Execução local |
| Software | Linear / estados | Estados e rotinas modulares | Manutenção e testes facilitados |
| Conectividade | Bluetooth / Wi-Fi / nenhuma | Nenhuma no MVP; não necessária para validar a lógica | Fica como evolução |
| Aplicativo | Controle por celular / local | Controles locais | Sem interface web/mobile |
| Sensores | Sensores / nenhum | Nenhum adicional no MVP | Eventos apenas por botões |
| Persistência | EEPROM / SD / nenhuma | Sem armazenamento persistente | Dados não são gravados |

Em caso de divergência entre documentos, prevalece a versão consolidada do TCC: desenvolvimento e validação virtuais, sem afirmar montagem física.
