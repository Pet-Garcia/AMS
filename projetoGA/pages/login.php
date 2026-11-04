<?php
session_start();

if (isset($_SESSION['usuario']['id'])) {
    header('Location: ../include/layout.php?pagina=inicio');
    exit;
}
?>
<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Entrar ou criar conta</title>
    <link rel="stylesheet" href="../css/style.css">
</head>
<body class="pagina-auth">
    <main class="conteudo">
        <section class="informacoes auth">
            <section id="login-section" aria-labelledby="login-title">
                <h1 id="login-title">Entrar</h1>
                <form id="login-form" class="auth-form">
                    <label for="login-email">E-mail</label>
                    <input id="login-email" name="email" type="email" autocomplete="email" maxlength="255" required>

                    <label for="login-password">Senha</label>
                    <input id="login-password" name="senha" type="password" autocomplete="current-password" required>

                    <button type="submit">Entrar</button>
                </form>
                <p>Não tem uma conta?
                    <button class="auth-link" type="button" data-show="register">Criar usuário</button>
                </p>
            </section>

            <section id="register-section" aria-labelledby="register-title" hidden>
                <h1 id="register-title">Criar usuário</h1>
                <form id="register-form" class="auth-form">
                    <label for="register-name">Nome completo</label>
                    <input id="register-name" name="nome" type="text" autocomplete="name" maxlength="500" required>

                    <label for="register-email">E-mail</label>
                    <input id="register-email" name="email" type="email" autocomplete="email" maxlength="255" required>

                    <label for="register-password">Senha (mínimo 8 caracteres)</label>
                    <input id="register-password" name="senha" type="password" autocomplete="new-password" minlength="8" maxlength="72" required>

                    <label for="register-cpf">CPF (somente números)</label>
                    <input id="register-cpf" name="cpf" type="text" inputmode="numeric" autocomplete="off" pattern="[0-9]{11}" minlength="11" maxlength="11" title="Digite os 11 números do CPF." required>

                    <label for="register-phone">Telefone (DDD + número)</label>
                    <input id="register-phone" name="telefone" type="tel" inputmode="numeric" autocomplete="tel" pattern="[0-9]{10,11}" minlength="10" maxlength="11" title="Digite o DDD e o número, somente com dígitos." required>

                    <button type="submit">Criar conta</button>
                </form>
                <p>Já tem uma conta?
                    <button class="auth-link" type="button" data-show="login">Voltar para o login</button>
                </p>
            </section>

            <p id="auth-message" class="auth-message" role="status" aria-live="polite"></p>
        </section>
    </main>
    <script src="../js/login.js" defer></script>
</body>
</html>
