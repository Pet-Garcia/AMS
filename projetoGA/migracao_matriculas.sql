USE `pi_cursos`;

ALTER TABLE `matriculas`
  ADD COLUMN `data_matricula` datetime NOT NULL DEFAULT current_timestamp(),
  MODIFY `id_lista` int(11) NOT NULL AUTO_INCREMENT,
  ADD PRIMARY KEY (`id_lista`),
  ADD UNIQUE KEY `uq_matricula_curso_usuario` (`id_curso`, `id_usuario`),
  ADD KEY `idx_matriculas_usuario` (`id_usuario`),
  ADD CONSTRAINT `fk_matriculas_curso`
    FOREIGN KEY (`id_curso`) REFERENCES `cursos` (`id_cursos`),
  ADD CONSTRAINT `fk_matriculas_usuario`
    FOREIGN KEY (`id_usuario`) REFERENCES `usuarios` (`id_usuario`);
