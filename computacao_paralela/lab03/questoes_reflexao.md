# Questões para Reflexão

**1. Por que é crucial que o pai e o filho fechem as pontas do pipe que não estão utilizando? O
que poderia acontecer se eles não o fizessem? (Dica: pense no que acontece com a chamada
read() se ainda houver um processo com a ponta de escrita aberta).**

Pipes têm duas pontas: leitura `(pipefd[0])` e escrita `(pipefd[1])`. Cada processo deve fechar a ponta que não usa para que o kernel saiba quando pode sinalizar EOF (fim de dados) para o leitor. Se algum processo mantiver a ponta de escrita aberta, o `read()` do pai pode bloquear para sempre, gerando deadlock. Fechar as pontas também evita vazamento de descritores e comportamentos confusos na sincronização.

---

**2. Pipes são canais unidirecionais. Como você poderia usar dois pipes para estabelecer uma
comunicação bidirecional entre um pai e um filho?**

Criar os 2 pipes antes do `fork()`:
- `p2c[2]` para pai -> filho (pai escreve, filho lê)
- `c2p[2]` para filho -> pai (filho escreve, pai lê)

Sendo assim:
- Pai: fecha `p2c[0]` e `c2p[1]`.
- Filho: fecha `p2c[1]` e `c2p[0]`.