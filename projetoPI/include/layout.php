<?php
session_start();

if (!isset($_SESSION['usuario']['id'])) {
    header('Location: ../pages/login.php');
    exit;
}

if (empty($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}

$usuarioId = (int) $_SESSION['usuario']['id'];

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $csrfToken = $_POST['csrf_token'] ?? '';
    $idCurso = filter_input(INPUT_POST, 'id_curso', FILTER_VALIDATE_INT);

    if (
        !is_string($csrfToken) ||
        !hash_equals($_SESSION['csrf_token'], $csrfToken) ||
        ($_POST['acao'] ?? '') !== 'matricular' ||
        !$idCurso ||
        $idCurso < 1
    ) {
        $_SESSION['flash_message'] = 'Solicitação inválida. Tente novamente.';
        header('Location: layout.php?pagina=cursos');
        exit;
    }

    require_once __DIR__ . '/conexao.php';

    try {
        $conn = conectarBanco();
        $stmt = $conn->prepare('SELECT id_cursos FROM cursos WHERE id_cursos = ?');
        $stmt->bind_param('i', $idCurso);
        $stmt->execute();
        $stmt->store_result();
        $cursoExiste = $stmt->num_rows === 1;
        $stmt->close();

        if (!$cursoExiste) {
            $_SESSION['flash_message'] = 'O curso selecionado não existe.';
            header('Location: layout.php?pagina=cursos');
            exit;
        }

        $stmt = $conn->prepare(
            'SELECT id_lista FROM matriculas WHERE id_curso = ? AND id_usuario = ? LIMIT 1'
        );
        $stmt->bind_param('ii', $idCurso, $usuarioId);
        $stmt->execute();
        $stmt->bind_result($idMatricula);

        if ($stmt->fetch()) {
            $stmt->close();
            $_SESSION['flash_message'] = 'Você já está matriculado neste curso.';
            header('Location: layout.php?pagina=extrato&id=' . (int) $idMatricula);
            exit;
        }
        $stmt->close();

        $stmt = $conn->prepare(
            'INSERT INTO matriculas (id_curso, id_usuario) VALUES (?, ?)'
        );
        $stmt->bind_param('ii', $idCurso, $usuarioId);
        $stmt->execute();
        $idMatricula = $conn->insert_id;
        $stmt->close();

        $_SESSION['flash_message'] = 'Matrícula realizada com sucesso.';
        header('Location: layout.php?pagina=extrato&id=' . $idMatricula);
        exit;
    } catch (mysqli_sql_exception $erro) {
        error_log('Erro ao realizar matrícula: ' . $erro->getMessage());

        if ($erro->getCode() === 1062) {
            $stmt = $conn->prepare(
                'SELECT id_lista FROM matriculas WHERE id_curso = ? AND id_usuario = ? LIMIT 1'
            );
            $stmt->bind_param('ii', $idCurso, $usuarioId);
            $stmt->execute();
            $stmt->bind_result($idMatricula);

            if ($stmt->fetch()) {
                $stmt->close();
                header('Location: layout.php?pagina=extrato&id=' . (int) $idMatricula);
                exit;
            }
            $stmt->close();
        }

        $_SESSION['flash_message'] = 'Não foi possível realizar a matrícula. Tente novamente.';
        header('Location: layout.php?pagina=cursos');
        exit;
    }
}

$paginas = [
    'inicio' => [
        'titulo' => 'Início',
        'arquivo' => __DIR__ . '/../pages/inicio.php'
    ],
    'cursos' => [
        'titulo' => 'Cursos',
        'arquivo' => __DIR__ . '/../pages/cursos.php'
    ],
    'lista' => [
        'titulo' => 'Alunos matriculados',
        'arquivo' => __DIR__ . '/../pages/lista.php'
    ],
    'extrato' => [
        'titulo' => 'Meu extrato',
        'arquivo' => __DIR__ . '/../pages/extrato.php'
    ]
];

$pagina = $_GET['pagina'] ?? 'inicio';
$paginaValida = is_string($pagina) && isset($paginas[$pagina]);

if (!$paginaValida) {
    http_response_code(404);
    $tituloPagina = 'Página não encontrada';
} else {
    $tituloPagina = $paginas[$pagina]['titulo'];
}

define('APP_LAYOUT', true);
$mensagem = $_SESSION['flash_message'] ?? '';
unset($_SESSION['flash_message']);
?>
<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <?php require __DIR__ . '/head.html'; ?>
    <title><?= htmlspecialchars($tituloPagina, ENT_QUOTES, 'UTF-8') ?></title>
</head>
<body>
    <header>
        <?php require __DIR__ . '/header.html'; ?>
    </header>

    <main id="main-content" class="conteudo">
        <?php if ($mensagem !== ''): ?>
            <p class="flash-message" role="status"><?= htmlspecialchars($mensagem, ENT_QUOTES, 'UTF-8') ?></p>
        <?php endif; ?>
        <?php if ($paginaValida): ?>
            <?php require $paginas[$pagina]['arquivo']; ?>
        <?php else: ?>
            <section class="informacoes">
                <h1>Página não encontrada</h1>
                <p>Escolha uma página usando a navegação.</p>
            </section>
        <?php endif; ?>
    </main>

    <?php require __DIR__ . '/footer.html'; ?>
</body>
</html>
