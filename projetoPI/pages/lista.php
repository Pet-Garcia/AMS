<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Lista de Cadastros</title>
    <link rel="stylesheet" href="../css/style.css">
</head>
<body>
    <header-component></header-component>

    <main class="conteudo">
        <section class="informacoes">
            <h1>Lista de Cursos</h1>
            <p>Aperte em um curso para ver quem está cadastrado</p>
        </section>

        <section class="informacoes">

            <table class="tabela">

                <thead>
                    <tr>
                        <th>Cursos</th>
                        <th>Alunos</th>
                        <th>Editar</th>
                    </tr>
                </thead>

                <tbody>
                    <?php
                    $resultado = $conn->query("SELECT id, nome_curso FROM cursos");
                    while ($linha = $resultado->fetch_assoc()):
                    ?>
                    <tr>
                        <td>
                            <a class="btn btn-editar" href="editar.php?id=<?= $linha['id'] ?>">Editar</a>
                            <a class="btn btn-excluir" href="excluir.php?id=<?= $linha['id'] ?>"
                            onclick="return confirm('Deseja realmente excluir?')">Excluir</a>
                        </td>
                        <td><?= $linha['id'] ?></td>
                        <td><?= htmlspecialchars($linha['nome_curso']) ?></td>
                    </tr>
                    <?php endwhile; ?>
                </tbody>

            </table>
            <!--JS com a lista dos cursos | botão para ver os alunos cadastrados| botão para editar os cadastros e curso-->
        </section>
    </main>

    <footer-component></footer-component>

    <script src="../js/include.js"></script>
</body>
</html>