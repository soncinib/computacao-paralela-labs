# Questões para Reflexão

**1. O speedup que você obteve foi “perfeito” (ou seja, próximo de N, o número de processos)?
Se não, quais fatores podem ter impedido um speedup ideal? (pense no custo de criar processos, por exemplo).**

Não foi perfeito. Isso acontece porque:

- Existe overhead para criar e gerenciar processos com `fork()`.
- A comunicação e sincronização (ex.: `wait()`) também consomem tempo.
- A memória RAM/cache é um gargalo: vários processos acessando o mesmo vetor ao mesmo tempo competem por largura de banda.
- O sistema operacional precisa fazer agendamento (scheduling) entre os processos, e isso adiciona custo.
- Se a máquina tiver menos núcleos físicos que o número de processos criados, o sistema operacional vai alternar os processos no mesmo núcleo, aumentando o tempo.

---

**2. Se você precisasse que o processo pai tivesse o vetor final completamente calculado, que estratégias poderia imaginar para que os filhos enviassem suas fatias processadas de volta para o pai?**

Com `fork()`, a memória é cópia isolada, ou seja, o pai não vê as mudanças feitas pelos filhos. Para juntar os resultados, é preciso algum mecanismo de comunicação entre processos (IPC), por exemplo:

- Pipes: cada filho escreve sua soma parcial em um pipe, o pai lê e acumula.
- Memória compartilhada (`mmap`, `shmget`): todos acessam a mesma área de memória. O pai depois vê o vetor atualizado.
- Arquivos temporários: cada filho escreve em arquivo, e o pai lê no final (menos eficiente).