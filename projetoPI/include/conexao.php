<?php
$conn = mysqli_connect("localhost", "root", "", "pi_cursos");

if (!$conn) {
    die("Erro de conexão: " . mysqli_connect_error());
}
?>