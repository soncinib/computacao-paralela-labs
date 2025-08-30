# Questões para Reflexão

**1. Qual a principal diferença entre o valor da variável pid no processo pai e no processo filho, logo após a chamada fork()? Por que essa diferença é tão importante?**

No pai, a variável pid recebe o PID do filho (um número positivo > 0). No filho, a variável pid recebe o valor 0. Se a chamada falhar, retorna -1.

Essa diferença é importante porque é assim que o programa sabe quem é o pai e quem é o filho. Sem isso, não daria para separar a lógica do pai e a lógica do filho.

---

**2. O que aconteceria no exemplo fork_example.c se você removesse a linha wait(NULL); do código do processo pai? Compile e execute para testar sua hipótese. (Pesquise sobre processos zumbis e processos órfãos).**

Se tirar o `wait(NULL)`, o pai não espera o filho terminar.
Quando o filho termina, ele fica no estado zumbi: já finalizou, mas o sistema ainda mantém sua entrada na tabela de processos até que o pai colete o status.

Se o pai terminar antes do filho, o filho vira órfão: o kernel reatribui o filho ao processo `init` (ou `systemd`), que cuida dele.