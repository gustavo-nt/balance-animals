<h4 align="center">
  <img src="https://github.com/gustavo-nt/balance-animals/blob/main/assets/logo.png" alt="logo" width="400px"/>
</h4>

<h1 align="center">
    Trabalho de Conclusão de Curso(TCC)
</h1>

<p align="center">
  <img src="https://img.shields.io/static/v1?message=C18&color=0088CC&logo=c" />
  <img src="https://img.shields.io/badge/last%21commit-february-important" />
  <img src="https://img.shields.io/badge/license-MIT-success"/>
</p>

<p align="center">
  <a href="#-funcionalidade">Funcionalidades</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#-pré-requisitos">Pré-Requisitos</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#-tecnologias">Tecnologias</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#-tecnologias">Diagramas de Blocos</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#-licença">Lincença</a>
</p>

<h3 align="center"> 
🚧  Finalizado  🚧
</h3>

### 📎 Funcionalidades

- [x] Sistema automatizado para manejo das portas
- [x] Sistema de pesagem com alta precisão
- [x] Comunicação com o usuário via display lcd
- [x] Ajuste de dados, tais como senha e peso máximo
- [x] Bloqueio total do sistema após sobrepeso

### 💻 Projeto

---

### ✅ Demonstração
<h4>
  <img src="https://github.com/gustavo-nt/dev-finances/blob/master/public/assets/github/dev.finances-github.PNG" width="50%"/>
  <img src="https://github.com/gustavo-nt/dev-finances/blob/master/public/assets/github/dev.finances-github.PNG" width="50%"/>
</h4>

### ⚙ Pré-requisitos

Para testes virtuais, antes de começar, você vai precisar ter instalado em sua máquina as seguintes ferramentas:
[CCS](http://www.ccsinfo.com/compilerupdates.php) e [Proteus](https://www.labcenter.com/). Lembrando que, o módulo
HX711 não possui no software Proteus, dessa forma, deve ser instalado um plugin ou utilizar outro tipo de sensor 
para fins de testes.

### 🚀 Tecnologias

Esse projeto foi desenvolvido com a linguagem C, utilizando os principais conceitos durante o curso técnico, como, por exemplo, 
o uso de funções externas no mesmo arquivo, para fins de organização.

### 📊 Diagrama de Blocos 

Confira o diagrama do funcionamento do projeto:

<img src="https://github.com/gustavo-nt/balance-animals/blob/main/assets/Diagrama%20de%20Blocos.PNG" />

### 🔌 Principais Componentes

- Microcontrolador PIC16F877A
- Ponte H Dupla L298N
- Micromotores G12-N20-100
- Display LCD 20x4
- Célula de Carga Single Point SP4MC3 10Kg
- Módulo Conversor HX711
- Teclado Matricial

### 💡 Futuras Funcionalidades

- Botão de Emergência: Responsável pela paralisação do sistema.
- Botão Deletar/Corrigir Senha: Responsável pela correção da senha caso o usuário erre algum algoritmo.
- Sensor Infravermelho: Responsável por inibir o funcionamento dos portões enquanto o feixe estiver cortado.

### 📝 Licença

Esse projeto está sob a licença MIT.

<hr/>

Feito por Gustavo Teixeira
