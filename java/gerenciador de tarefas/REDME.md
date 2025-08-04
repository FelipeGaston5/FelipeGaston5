# 📋 Gerenciador de Tarefas - Java Console

Este é um sistema de linha de comando feito em **Java** para gerenciamento simples de tarefas, com persistência em arquivo `.json`.

## 🚀 Funcionalidades

- ✅ Cadastrar tarefa com:
  - Nome
  - Descrição
  - Data
  - Hora
  - Prioridade
- 📃 Listar todas as tarefas salvas
- 🗑️ Excluir tarefas por índice
- ✅ Marcar tarefas como feitas
- 💾 Salvamento persistente em arquivo JSON

## 🛠️ Tecnologias

- Java 17+ (compatível com JDK 24)
- Biblioteca [Gson](https://github.com/google/gson) para manipulação de JSON

## 📂 Estrutura de Pastas

```plaintext
gerenciador-de-tarefas/
├── src/
│   └── main/
│       ├── java/
│       │   └── br/
│       │       └── com/
│       │           └── gaston/
│       │               ├── Main.java
│       │               └── functions/
│       │                   ├── Cadastrar.java
│       │                   ├── Listar.java
│       │                   ├── Excluir.java
│       │                   ├── MarcarComoFeita.java
│       │                   └── Escolha.java
│       └── resources/
│           └── Tarefas.json
