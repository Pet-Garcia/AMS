<?php
if (!defined('APP_LAYOUT')) {
    header('Location: login.php');
    exit;
}

require_once __DIR__ . '/../include/conexao.php';
$conn = conectarBanco();

/* Paginação - Inicio */
$por_pagina = 25;

$pag_atual = isset($_GET['p']) ? (int) $_GET['p'] : 1;
if ($pag_atual < 1) $pag_atual = 1;

$total = (int) $conn->query('SELECT COUNT(*) AS total FROM cursos')->fetch_assoc()['total'];
$total_paginas = max(1, (int) ceil($total / $por_pagina));

if ($pag_atual > $total_paginas) $pag_atual = $total_paginas;

$offset = ($pag_atual - 1) * $por_pagina;
/* Paginação - Fim */

$stmt = $conn->prepare(
    'SELECT c.id_cursos, c.nome_cursos, c.num_aulas, c.periodo, c.vagas,
            (SELECT COUNT(*) FROM matriculas mt WHERE mt.id_curso = c.id_cursos) AS vagas_ocupadas,
            m.id_lista
     FROM cursos c
     LEFT JOIN matriculas m ON m.id_curso = c.id_cursos AND m.id_usuario = ?
     ORDER BY c.nome_cursos
     LIMIT ? OFFSET ?'
);
$stmt->bind_param('iii', $usuarioId, $por_pagina, $offset);
$stmt->execute();
$resultado = $stmt->get_result();
$csrfToken = $_SESSION['csrf_token'];
?>
<section class="informacoes">
    <h1>Cursos</h1>
    <p>Escolha um curso para realizar sua matrícula.</p>
</section>

<section class="informacoes">
    <h2>Cursos disponíveis</h2>
    <?php if ($resultado->num_rows === 0): ?>
        <p>Nenhum curso disponível no momento.</p>
    <?php else: ?>
        <table class="tabela">
            <thead>
                <tr>
                    <th>Curso</th>
                    <th>Número de aulas</th>
                    <th>Vagas</th>
                    <th>Período</th>
                    <th>Matrícula</th>
                </tr>
            </thead>
            <tbody>
                <?php while ($curso = $resultado->fetch_assoc()): ?>
                    <tr>
                        <td><?= htmlspecialchars($curso['nome_cursos'], ENT_QUOTES, 'UTF-8') ?></td>
                        <td><?= htmlspecialchars($curso['num_aulas'], ENT_QUOTES, 'UTF-8') ?></td>
                        <?php $disponiveis = max(0, (int) $curso['vagas'] - (int) $curso['vagas_ocupadas']); ?>
                        <td><?= $disponiveis ?> / <?= (int) $curso['vagas'] ?></td>
                        <td><?= htmlspecialchars($curso['periodo'], ENT_QUOTES, 'UTF-8') ?></td>
                        <td>
                            <?php if ($curso['id_lista'] !== null): ?>
                                <a href="../include/layout.php?pagina=extrato&id=<?= (int) $curso['id_lista'] ?>">
                                    Ver extrato
                                </a>
                            <?php else: ?>
                                <form method="post" action="../include/layout.php?pagina=cursos">
                                    <input type="hidden" name="acao" value="matricular">
                                    <input type="hidden" name="id_curso" value="<?= (int) $curso['id_cursos'] ?>">
                                    <input type="hidden" name="csrf_token" value="<?= htmlspecialchars($csrfToken, ENT_QUOTES, 'UTF-8') ?>">
                                    <?php if ($disponiveis > 0): ?>
                                        <button type="submit">Matricular-se</button>
                                    <?php else: ?>
                                        <button type="button" disabled>Vagas esgotadas</button>
                                    <?php endif; ?>
                                </form>
                            <?php endif; ?>
                        </td>
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