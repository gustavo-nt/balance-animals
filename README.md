<h4 align="center">
  <img src="https://github.com/gustavo-nt/dev-finances/blob/master/public/assets/github/logo.svg" alt="logo" width="400px"/>
</h4>

<h1 align="center">
    Trabalho de Conclusão de Curso(TCC)
</h1>

<p align="center">Projeto balance.animals</p>

<p align="center">
  <img src="https://img.shields.io/static/v1?label=node&message=12.13.1&color=339933&logo=node.js" />
  <img src="https://img.shields.io/static/v1?label=html&message=5.0&color=61DAFB&logo=html" />
  <img src="https://img.shields.io/static/v1?label=css&message=3.0&color=0088CC&logo=css" />
  <img src="https://img.shields.io/static/v1?label=js&message=ecma2018&color=yellow&logo=javascript" />
  <img src="https://img.shields.io/badge/last%21commit-february-important" />
  <img src="https://img.shields.io/badge/license-MIT-success"/>
</p>

<p align="center">
  <a href="#-features">Features</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#-pré-requisitos">Pré-Requisitos</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#-tecnologias">Tecnologias</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
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
<img src="https://github.com/gustavo-nt/dev-finances/blob/master/public/assets/github/dev.finances-github.PNG" />

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

<img src="https://github.com/gustavo-nt/dev-finances/blob/master/public/assets/github/dev.finances-github.PNG" />

### 🔌 Principais Componentes

- Microcontrolador PIC16F877A
- Ponte H Dupla L298N
- Micromotores G12-N20-100
- Display LCD 20x4
- Célula de Carga Single Point SP4MC3 10Kg
- Módulo Conversor HX711
- Teclado Matricial

### 💡 Futuras Funcionalidade

- Botão de Emergência: Responsável pela paralisação do sistema.
- Botão Deletar/Corrigir Senha: Responsável pela correção da senha caso o usuário erre algum algoritmo.
- Sensor Infravermelho: Responsável por inibir o funcionamento dos portões enquanto o feixe estiver cortado.

### 📝 Licença

Esse projeto está sob a licença MIT.

<hr/>

Feito por Gustavo Teixeira
