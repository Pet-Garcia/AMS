<?php
session_start();

$_SESSION = []; // Apaga dados


// Apaga a sessão dos cookies
if (ini_get('session.use_cookies')) {
    $p = session_get_cookie_params();
    setcookie(session_name(), '', time() - 42000, $p['path'], $p['domain'], $p['secure'], $p['httponly']);
}

// Apaga o restante da sessão
session_destroy();

header('Location: ../pages/login.php');
exit;