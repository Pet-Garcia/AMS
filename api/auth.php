<?php
require_once __DIR__ . '/../include/conexao.php';

header('Content-Type: application/json; charset=utf-8');

function responder(int $status, string $message): void
{
    http_response_code($status);
    echo json_encode(['message' => $message], JSON_UNESCAPED_UNICODE);
    exit;
}

function campoTexto(array $dados, string $campo): string
{
    $valor = $dados[$campo] ?? '';

    return is_string($valor) ? trim($valor) : '';
}

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    header('Allow: POST');
    responder(405, 'Método não permitido.');
}

$dados = json_decode(file_get_contents('php://input'), true);
if (!is_array($dados)) {
    responder(400, 'Requisição inválida.');
}

$action = campoTexto($dados, 'action');
if (!in_array($action, ['login', 'register'], true)) {
    responder(400, 'Ação inválida.');
}

$email = campoTexto($dados, 'email');
$senha = is_string($dados['senha'] ?? null) ? $dados['senha'] : '';

if (!filter_var($email, FILTER_VALIDATE_EMAIL) || strlen($email) > 255 || $senha === '') {
    responder(422, 'Informe um e-mail válido e uma senha.');
}

try {
    $conn = conectarBanco();

    if ($action === 'login') {
        $stmt = $conn->prepare(
            'SELECT id_usuario, nome_usuario, senha FROM usuarios WHERE email = ? LIMIT 1'
        );
        $stmt->bind_param('s', $email);
        $stmt->execute();
        $stmt->bind_result($idUsuario, $nomeUsuario, $senhaHash);

        if (!$stmt->fetch() || !password_verify($senha, $senhaHash)) {
            $stmt->close();
            responder(401, 'E-mail ou senha incorretos.');
        }
        $stmt->close();

        $secureCookie = !empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off';
        session_set_cookie_params([
            'httponly' => true,
            'samesite' => 'Lax',
            'secure' => $secureCookie
        ]);
        session_start();
        session_regenerate_id(true);
        $_SESSION['usuario'] = [
            'id' => $idUsuario,
            'nome' => $nomeUsuario,
            'email' => $email
        ];

        responder(200, 'Login realizado com sucesso.');
    }

    $nome = campoTexto($dados, 'nome');
    $cpfInformado = campoTexto($dados, 'cpf');
    $telefoneInformado = campoTexto($dados, 'telefone');
    $cpf = preg_replace('/\D/', '', $cpfInformado);
    $telefone = preg_replace('/\D/', '', $telefoneInformado);

    if (
        $nome === '' || strlen($nome) > 500 ||
        strlen($senha) < 8 || strlen($senha) > 72 ||
        !is_string($cpf) || strlen($cpf) !== 11 ||
        !is_string($telefone) || !in_array(strlen($telefone), [10, 11], true)
    ) {
        responder(422, 'Confira nome, senha (8 a 72 caracteres), CPF (11 dígitos) e telefone com DDD.');
    }

    $cpf = substr($cpf, 0, 3) . '.' . substr($cpf, 3, 3) . '.' .
        substr($cpf, 6, 3) . '-' . substr($cpf, 9, 2);

    $stmt = $conn->prepare('SELECT id_usuario FROM usuarios WHERE email = ? OR cpf = ? LIMIT 1');
    $stmt->bind_param('ss', $email, $cpf);
    $stmt->execute();
    $stmt->store_result();

    if ($stmt->num_rows > 0) {
        $stmt->close();
        responder(409, 'Já existe um usuário com esse e-mail ou CPF.');
    }
    $stmt->close();

    $senhaHash = password_hash($senha, PASSWORD_DEFAULT);

    $stmt = $conn->prepare(
        'INSERT INTO usuarios (nome_usuario, email, senha, cpf, telefone) VALUES (?, ?, ?, ?, ?)'
    );
    $stmt->bind_param('sssss', $nome, $email, $senhaHash, $cpf, $telefone);
    $stmt->execute();
    $stmt->close();

    responder(201, 'Usuário criado com sucesso. Faça login para continuar.');
} catch (mysqli_sql_exception $erro) {
    error_log('Erro na autenticação: ' . $erro->getMessage());
    responder(500, 'Não foi possível concluir a solicitação agora.');
}
