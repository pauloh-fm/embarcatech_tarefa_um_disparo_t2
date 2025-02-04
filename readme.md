# Tarefa 2 - Aula Síncrona 29/01 - Um Disparo

**Autor:** Paulo Henrique de Farias Martins

## Funcionalidades

1. **Sequência de LEDs com controle por botão:**  
   Caso o usuário clique no botão (pushbutton), os três LEDs serão ligados (todos em nível alto). A partir da primeira rotina de atraso, ocorrerá uma mudança de estado para dois LEDs ligados e, em seguida, apenas um.
2. **Temporização com callback:**  
   O temporizador do alarme é ajustado para um atraso de 3 segundos (3.000 ms) entre os estados de acionamento dos LEDs.

3. **Implementação em função de callback:**  
   A mudança de estado dos LEDs é implementada por meio de funções de callback do temporizador, seguindo o exemplo da rotina trabalhada na aula síncrona (*turn_off_callback()*).

4. **Controle de evento do botão:**  
   O botão só pode alterar o estado dos LEDs quando o último LED for desligado. Durante a execução das rotinas de temporização, o botão não pode iniciar uma nova chamada da função callback.

5. **Rotina opcional de debounce:**  
   Implementado uma rotina em software para atenuação do efeito *bouncing* no botão (software debounce), caso necessário.

---


## Instruções

Siga estes 3 passos simples para executar o projeto:

1. **Clonar o projeto:**  
   Clone este repositório para sua máquina local.

2. **Importar o projeto:**  
   Importe o projeto utilizando a extensão *Raspberry Pico Pi* no seu ambiente de desenvolvimento.

3. **Executar o projeto:**  
   Execute o projeto utilizando a extensão *Raspberry Pico Pi* , para gerar o arquivo de build.

4. **Executar o Simulador**  
   Execute o projeto, com a extenção da wokwi instalada, clicando no arquivo *diagram.json*.





