<?php
if (!defined('APP_LAYOUT')) {
    header('Location: login.php');
    exit;
}

require_once __DIR__ . '/../include/conexao.php';
$conn = conectarBanco();
$usuarioId = (int) $_SESSION['usuario']['id'];
$idMatricula = filter_input(INPUT_GET, 'id', FILTER_VALIDATE_INT);

$sql = 'SELECT m.id_lista, m.data_matricula, c.nome_cursos, c.num_aulas, c.periodo,
               u.nome_usuario, u.email, u.cpf, u.telefone
        FROM matriculas m
        INNER JOIN cursos c ON c.id_cursos = m.id_curso
        INNER JOIN usuarios u ON u.id_usuario = m.id_usuario
        WHERE m.id_usuario = ?';

if ($idMatricula && $idMatricula > 0) {
    $sql .= ' AND m.id_lista = ?';
    $stmt = $conn->prepare($sql . ' ORDER BY m.data_matricula DESC');
    $stmt->bind_param('ii', $usuarioId, $idMatricula);
} else {
    $stmt = $conn->prepare($sql . ' ORDER BY m.data_matricula DESC');
    $idMatricula = null;
    $stmt->bind_param('i', $usuarioId);
}

$stmt->execute();
$extratos = $stmt->get_result();
?>
<section class="informacoes">
    <h1>Meu extrato de matrícula</h1>
    <p>Este extrato mostra somente as matrículas da sua conta.</p>
</section>

<?php if ($extratos->num_rows === 0): ?>
    <section class="informacoes">
        <p>Você ainda não possui matrícula<?= $idMatricula ? ' com esse número' : '' ?>.</p>
        <a href="../include/layout.php?pagina=cursos">Ver cursos disponíveis</a>
    </section>
<?php else: ?>
    <?php while ($extrato = $extratos->fetch_assoc()): ?>
        <section class="informacoes receipt">
            <h2>Comprovante de matrícula #<?= (int) $extrato['id_lista'] ?></h2>
            <p><strong>Data:</strong> <?= htmlspecialchars(date('d/m/Y H:i', strtotime($extrato['data_matricula'])), ENT_QUOTES, 'UTF-8') ?></p>
            <h3>Dados do aluno</h3>
            <p><strong>Nome:</strong> <?= htmlspecialchars($extrato['nome_usuario'], ENT_QUOTES, 'UTF-8') ?></p>
            <p><strong>E-mail:</strong> <?= htmlspecialchars($extrato['email'], ENT_QUOTES, 'UTF-8') ?></p>
            <p><strong>CPF:</strong> <?= htmlspecialchars($extrato['cpf'], ENT_QUOTES, 'UTF-8') ?></p>
            <p><strong>Telefone:</strong> <?= htmlspecialchars($extrato['telefone'], ENT_QUOTES, 'UTF-8') ?></p>
            <h3>Dados do curso</h3>
            <p><strong>Curso:</strong> <?= htmlspecialchars($extrato['nome_cursos'], ENT_QUOTES, 'UTF-8') ?></p>
            <p><strong>Número de aulas:</strong> <?= htmlspecialchars($extrato['num_aulas'], ENT_QUOTES, 'UTF-8') ?></p>
            <p><strong>Período:</strong> <?= htmlspecialchars($extrato['periodo'], ENT_QUOTES, 'UTF-8') ?></p>
            <button type="button" class="no-print" onclick="window.print()">Imprimir extrato</button>
        </section>
    <?php endwhile; ?>
<?php endif; ?>
