<?php
function conectarBanco(): mysqli
{
    $conn = new mysqli("localhost", "root", "", "pi_cursos");
    $conn->set_charset("utf8mb4");

    return $conn;
}


?>