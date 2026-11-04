<?php
if (!defined('APP_LAYOUT')) {
    header('Location: login.php');
    exit;
}

require_once __DIR__ . '/../include/conexao.php';
$conn = conectarBanco();
$cursos = $conn->query('SELECT id_cursos, nome_cursos FROM cursos ORDER BY nome_cursos');

/* Paginação - Inicio */
$por_pagina = 25;

$pag_atual = isset($_GET['p']) ? (int) $_GET['p'] : 1;
if ($pag_atual < 1) $pag_atual = 1;

$total = (int) $conn->query('SELECT COUNT(*) AS total FROM cursos')->fetch_assoc()['total'];
$total_paginas = max(1, (int) ceil($total / $por_pagina));

if ($pag_atual > $total_paginas) $pag_atual = $total_paginas;

$offset = ($pag_atual - 1) * $por_pagina;
/* Paginação - Fim */

$idCurso = filter_input(INPUT_GET, 'curso', FILTER_VALIDATE_INT);
$idCurso = $idCurso && $idCurso > 0 ? $idCurso : 0;

if ($idCurso > 0) {
    $stmt = $conn->prepare(
        'SELECT c.nome_cursos, u.nome_usuario
         FROM matriculas m
         INNER JOIN cursos c ON c.id_cursos = m.id_curso
         INNER JOIN usuarios u ON u.id_usuario = m.id_usuario
         WHERE c.id_cursos = ?
         ORDER BY u.nome_usuario'
    );
    $stmt->bind_param('i', $idCurso);
} else {
    $stmt = $conn->prepare(
        'SELECT c.nome_cursos, u.nome_usuario
         FROM matriculas m
         INNER JOIN cursos c ON c.id_cursos = m.id_curso
         INNER JOIN usuarios u ON u.id_usuario = m.id_usuario
         ORDER BY c.nome_cursos, u.nome_usuario'
    );
}

$stmt->execute();
$matriculas = $stmt->get_result();
?>
<section class="informacoes">
    <h1>Alunos matriculados</h1>
    <p>Consulte os alunos inscritos em cada curso.</p>

    <form method="get" action="../include/layout.php" class="course-filter">
        <input type="hidden" name="pagina" value="lista">
        <label for="curso">Filtrar por curso</label>
        <select id="curso" name="curso">
            <option value="0">Todos os cursos</option>
            <?php while ($curso = $cursos->fetch_assoc()): ?>
                <option value="<?= (int) $curso['id_cursos'] ?>"
                    <?= $idCurso === (int) $curso['id_cursos'] ? 'selected' : '' ?>>
                    <?= htmlspecialchars($curso['nome_cursos'], ENT_QUOTES, 'UTF-8') ?>
                </option>
            <?php endwhile; ?>
        </select>
        <button type="submit">Filtrar</button>
    </form>
</section>

<section class="informacoes">
    <?php if ($matriculas->num_rows === 0): ?>
        <p>Nenhum aluno matriculado<?= $idCurso > 0 ? ' neste curso' : '' ?>.</p>
    <?php else: ?>
        <table class="tabela">
            <thead>
                <tr>
                    <th>Curso</th>
                    <th>Aluno</th>
                </tr>
            </thead>
            <tbody>
                <?php while ($matricula = $matriculas->fetch_assoc()): ?>
                    <tr>
                        <td><?= htmlspecialchars($matricula['nome_cursos'], ENT_QUOTES, 'UTF-8') ?></td>
                        <td><?= htmlspecialchars($matricula['nome_usuario'], ENT_QUOTES, 'UTF-8') ?></td>
                    </tr>
                <?php endwhile; ?>
            </tbody>
        </table>
        <?php if ($total_paginas > 1): ?>
            <div class="paginacao">
                <?php if ($pag_atual > 1): ?>
                    <a href="?pagina=cursos&p=<?= $pag_atual - 1 ?>">&laquo; Anterior</a>
                <?php endif; ?>

                <?php for ($i = 1; $i <= $total_paginas; $i++): ?>
                    <?php if ($i === $pag_atual): ?>
                        <span class="atual"><?= $i ?></span>
                    <?php else: ?>
                        <a href="?pagina=cursos&p=<?= $i ?>"><?= $i ?></a>
                    <?php endif; ?>
                <?php endfor; ?>

                <?php if ($pag_atual < $total_paginas): ?>
                    <a href="?pagina=cursos&p=<?= $pag_atual + 1 ?>">Próxima &raquo;</a>
                <?php endif; ?>
            </div>
        <?php endif; ?>
    <?php endif; ?>
</section>
