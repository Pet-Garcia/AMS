-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Tempo de geração: 31/10/2026 às 01:18
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
-- Banco de dados: `pi_cursos`
--
CREATE DATABASE IF NOT EXISTS `pi_cursos` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `pi_cursos`;

-- --------------------------------------------------------

--
-- Estrutura para tabela `cursos`
--

CREATE TABLE `cursos` (
  `id_cursos` int(5) NOT NULL,
  `nome_cursos` varchar(255) NOT NULL,
  `num_aulas` varchar(30) NOT NULL,
  `periodo` varchar(50) NOT NULL,
  `vagas` int(5) NOT NULL,
  `vagas_ocupadas` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `cursos`
--

INSERT INTO `cursos` (`id_cursos`, `nome_cursos`, `num_aulas`, `periodo`, `vagas`, `vagas_ocupadas`) VALUES
(1, 'Análise e Desenvolvimento de Sistemas', '80', 'Noturno', 120, 0),
(2, 'Gestão da Tecnologia da Informação', '72', 'Noturno', 80, 0),
(3, 'Banco de Dados', '60', 'Matutino', 60, 0),
(4, 'Desenvolvimento Web', '64', 'Vespertino', 40, 0),
(5, 'Desenvolvimento Mobile', '64', 'Noturno', 60, 0),
(6, 'Segurança da Informação', '56', 'Noturno', 80, 0),
(7, 'Redes de Computadores', '60', 'Matutino', 40, 0),
(8, 'Ciência de Dados', '72', 'Vespertino', 60, 0),
(9, 'Inteligência Artificial', '68', 'Noturno', 80, 0),
(10, 'Engenharia de Software', '80', 'Matutino', 120, 0),
(11, 'Arquitetura de Software', '48', 'Noturno', 40, 0),
(12, 'Computação em Nuvem', '52', 'Vespertino', 60, 0),
(13, 'DevOps', '44', 'Noturno', 36, 0),
(14, 'Lógica de Programação', '40', 'Matutino', 85, 0),
(15, 'Algoritmos e Estruturas de Dados', '72', 'Matutino', 120, 0),
(16, 'Programação Orientada a Objetos', '64', 'Vespertino', 80, 0),
(17, 'Interface e Experiência do Usuário', '48', 'Vespertino', 40, 0),
(18, 'Sistemas Operacionais', '56', 'Matutino', 60, 0),
(19, 'Gestão de Projetos', '40', 'Noturno', 36, 0),
(20, 'Empreendedorismo Digital', '36', 'Noturno', 24, 0),
(21, 'Marketing Digital', '40', 'Vespertino', 60, 0),
(22, 'Estatística Aplicada', '48', 'Matutino', 40, 0),
(23, 'Análise de Negócios', '52', 'Vespertino', 36, 0),
(24, 'Testes de Software', '44', 'Noturno', 60, 0),
(25, 'Internet das Coisas', '56', 'Integral', 40, 0);

-- --------------------------------------------------------

--
-- Estrutura para tabela `matriculas`
--

CREATE TABLE `matriculas` (
  `id_lista` int(11) NOT NULL,
  `id_curso` int(11) NOT NULL,
  `id_usuario` int(11) NOT NULL,
  `data_matricula` datetime NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estrutura para tabela `usuarios`
--

CREATE TABLE `usuarios` (
  `id_usuario` int(5) NOT NULL,
  `nome_usuario` varchar(500) NOT NULL,
  `email` varchar(255) NOT NULL,
  `senha` varchar(1500) NOT NULL,
  `cpf` char(14) NOT NULL,
  `telefone` char(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `usuarios`
--

INSERT INTO `usuarios` (`id_usuario`, `nome_usuario`, `email`, `senha`, `cpf`, `telefone`) VALUES
(1, 'Admin', 'admin@projeto.com', '$2y$10$Ciarn2D1HBSBLwXVYTtCEONiKh8QPOZ5EjPtcgBlBwA3gmhH07HW2', '111.111.111-11', '11111111111');

--
-- Índices para tabelas despejadas
--

--
-- Índices de tabela `cursos`
--
ALTER TABLE `cursos`
  ADD PRIMARY KEY (`id_cursos`);

--
-- Índices de tabela `matriculas`
--
ALTER TABLE `matriculas`
  ADD PRIMARY KEY (`id_lista`),
  ADD UNIQUE KEY `uq_matricula_curso_usuario` (`id_curso`,`id_usuario`),
  ADD KEY `idx_matriculas_usuario` (`id_usuario`);

--
-- Índices de tabela `usuarios`
--
ALTER TABLE `usuarios`
  ADD PRIMARY KEY (`id_usuario`);

--
-- AUTO_INCREMENT para tabelas despejadas
--

--
-- AUTO_INCREMENT de tabela `cursos`
--
ALTER TABLE `cursos`
  MODIFY `id_cursos` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=26;

--
-- AUTO_INCREMENT de tabela `matriculas`
--
ALTER TABLE `matriculas`
  MODIFY `id_lista` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de tabela `usuarios`
--
ALTER TABLE `usuarios`
  MODIFY `id_usuario` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- Restrições para tabelas despejadas
--

--
-- Restrições para tabelas `matriculas`
--
ALTER TABLE `matriculas`
  ADD CONSTRAINT `fk_matriculas_curso` FOREIGN KEY (`id_curso`) REFERENCES `cursos` (`id_cursos`),
  ADD CONSTRAINT `fk_matriculas_usuario` FOREIGN KEY (`id_usuario`) REFERENCES `usuarios` (`id_usuario`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
