-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Tempo de geração: 24/03/2026 às 20:16
-- Versão do servidor: 10.4.32-MariaDB
-- Versão do PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Banco de dados: `academico`
--
CREATE DATABASE IF NOT EXISTS `academico` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `academico`;

-- --------------------------------------------------------

--
-- Estrutura para tabela `alunos`
--

CREATE TABLE `alunos` (
  `ra` int(16) NOT NULL,
  `nome` varchar(50) NOT NULL,
  `cpf` char(16) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `alunos`
--

INSERT INTO `alunos` (`ra`, `nome`, `cpf`) VALUES
(1001, 'João Pedro', '123.456.789-00'),
(1002, 'Maria Clara', '234.567.890-11'),
(1003, 'Lucas Santos', '345.678.901-22'),
(1004, 'Beatriz Oliveira', '456.789.012-33'),
(1005, 'Gabriel Rocha', '567.890.123-44');

-- --------------------------------------------------------

--
-- Estrutura para tabela `cursos`
--

CREATE TABLE `cursos` (
  `idcurso` int(5) NOT NULL,
  `nomecurso` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `cursos`
--

INSERT INTO `cursos` (`idcurso`, `nomecurso`) VALUES
(1, 'Sistemas de Informação'),
(2, 'Engenharia de Software'),
(3, 'Ciência da Computação'),
(4, 'Análise e Desenvolvimento de Sistemas'),
(5, 'Banco de Dados');

-- --------------------------------------------------------

--
-- Estrutura para tabela `disciplina`
--

CREATE TABLE `disciplina` (
  `iddisciplina` int(5) NOT NULL,
  `nomedisciplina` varchar(50) NOT NULL,
  `idcurso` int(5) NOT NULL,
  `idprofessor` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `disciplina`
--

INSERT INTO `disciplina` (`iddisciplina`, `nomedisciplina`, `idcurso`, `idprofessor`) VALUES
(1, 'Banco de Dados I', 5, 1),
(2, 'Programação I', 1, 2),
(3, 'Estruturas de Dados', 3, 3),
(4, 'Engenharia de Software I', 2, 4),
(5, 'Análise de Sistemas', 4, 5);

-- --------------------------------------------------------

--
-- Estrutura para tabela `itemturma`
--

CREATE TABLE `itemturma` (
  `iditem` int(11) NOT NULL,
  `ra` int(16) NOT NULL,
  `idturma` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `itemturma`
--

INSERT INTO `itemturma` (`iditem`, `ra`, `idturma`) VALUES
(1, 1001, 1),
(2, 1002, 2),
(3, 1003, 3),
(4, 1004, 4),
(5, 1005, 5);

-- --------------------------------------------------------

--
-- Estrutura para tabela `professor`
--

CREATE TABLE `professor` (
  `idprofessor` int(5) NOT NULL,
  `nomeprofessor` varchar(50) NOT NULL,
  `cpf` char(16) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `professor`
--

INSERT INTO `professor` (`idprofessor`, `nomeprofessor`, `cpf`) VALUES
(1, 'Carlos Silva', '111.111.111-11'),
(2, 'Ana Souza', '222.222.222-22'),
(3, 'Marcos Lima', '333.333.333-33'),
(4, 'Fernanda Costa', '444.444.444-44'),
(5, 'Juliana Alves', '555.555.555-55');

-- --------------------------------------------------------

--
-- Estrutura para tabela `turma`
--

CREATE TABLE `turma` (
  `idturma` int(5) NOT NULL,
  `nometurma` varchar(50) NOT NULL,
  `iddisciplina` int(5) NOT NULL,
  `semestre` int(3) NOT NULL,
  `ano` int(3) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `turma`
--

INSERT INTO `turma` (`idturma`, `nometurma`, `iddisciplina`, `semestre`, `ano`) VALUES
(1, 'Turma A - BD', 1, 1, 2026),
(2, 'Turma B - Prog', 2, 2, 2026),
(3, 'Turma C - ED', 3, 1, 2025),
(4, 'Turma D - ES', 4, 2, 2025),
(5, 'Turma E - AS', 5, 1, 2026);

--
-- Índices para tabelas despejadas
--

--
-- Índices de tabela `alunos`
--
ALTER TABLE `alunos`
  ADD PRIMARY KEY (`ra`);

--
-- Índices de tabela `cursos`
--
ALTER TABLE `cursos`
  ADD PRIMARY KEY (`idcurso`);

--
-- Índices de tabela `disciplina`
--
ALTER TABLE `disciplina`
  ADD PRIMARY KEY (`iddisciplina`),
  ADD KEY `idcurso` (`idcurso`),
  ADD KEY `idprofessor` (`idprofessor`);

--
-- Índices de tabela `itemturma`
--
ALTER TABLE `itemturma`
  ADD PRIMARY KEY (`iditem`),
  ADD KEY `ra` (`ra`),
  ADD KEY `idturma` (`idturma`);

--
-- Índices de tabela `professor`
--
ALTER TABLE `professor`
  ADD PRIMARY KEY (`idprofessor`);

--
-- Índices de tabela `turma`
--
ALTER TABLE `turma`
  ADD PRIMARY KEY (`idturma`),
  ADD KEY `iddisciplina` (`iddisciplina`);

--
-- AUTO_INCREMENT para tabelas despejadas
--

--
-- AUTO_INCREMENT de tabela `disciplina`
--
ALTER TABLE `disciplina`
  MODIFY `iddisciplina` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT de tabela `itemturma`
--
ALTER TABLE `itemturma`
  MODIFY `iditem` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT de tabela `professor`
--
ALTER TABLE `professor`
  MODIFY `idprofessor` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- Restrições para tabelas despejadas
--

--
-- Restrições para tabelas `disciplina`
--
ALTER TABLE `disciplina`
  ADD CONSTRAINT `disciplina_ibfk_1` FOREIGN KEY (`idcurso`) REFERENCES `cursos` (`idcurso`),
  ADD CONSTRAINT `disciplina_ibfk_2` FOREIGN KEY (`idprofessor`) REFERENCES `professor` (`idprofessor`);

--
-- Restrições para tabelas `itemturma`
--
ALTER TABLE `itemturma`
  ADD CONSTRAINT `itemturma_ibfk_1` FOREIGN KEY (`ra`) REFERENCES `alunos` (`ra`),
  ADD CONSTRAINT `itemturma_ibfk_2` FOREIGN KEY (`idturma`) REFERENCES `turma` (`idturma`);

--
-- Restrições para tabelas `turma`
--
ALTER TABLE `turma`
  ADD CONSTRAINT `turma_ibfk_1` FOREIGN KEY (`iddisciplina`) REFERENCES `disciplina` (`iddisciplina`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
