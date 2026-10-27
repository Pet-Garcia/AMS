<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Lista de Cadastros</title>
    <link rel="stylesheet" href="../css/style.css">
    <link href="https://cdn.jsdelivr.net/npm/simple-datatables@latest/dist/style.css" rel="stylesheet"> <!--Páginação-->
</head>
<body>
    <?php include("../include/conexao.php"); ?>
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
                        <th>Excluir</th>
                    </tr>
                </thead>

                <tbody>
                    <?php
                    $resultado = $conn->query("SELECT id_cursos, nome_cursos FROM cursos");
                    while ($linha = $resultado->fetch_assoc()):
                    ?>
                    <tr>
                        <td><?= htmlspecialchars($linha['nome_cursos']) ?></td>
                        <td class='acoes'>
                            <a class="btn btn-editar" href="editar.php?id=<?= $linha['id_cursos'] ?>">Ver Matriculas</a>
                        </td>
                        <td class='acoes'>
                            <a class="btn btn-editar" href="editar.php?id=<?= $linha['id_cursos'] ?>">Editar</a>
                        </td>
                        <td class='acoes'>
                            <a class="btn btn-excluir" href="excluir.php?id=<?= $linha['id_cursos'] ?>"
                            onclick="return confirm('Deseja realmente excluir?')">Excluir</a>
                        </td>
                        
                    </tr>
                    <?php endwhile; ?>
                </tbody>

            </table>
        </section>
    </main>

    <footer-component></footer-component>

    <script src="../js/include.js"></script>
    <!--Páginação-->
    <script src="https://cdn.jsdelivr.net/npm/simple-datatables@latest"></script>
    <script>
        new simpleDatatables.DataTable(".tabela", {
            perPage: 25,
            perPageSelect: [10, 25, 50],
            columns: [
                { select: 4, sortable: false }
            ],
            labels: {
                placeholder: "Pesquisar...",
                perPage: "registros por página",
                noRows: "Nenhum registro encontrado",
                info: "{start} a {end} de {rows} dados"
            }
        });
    </script>
</body>
</html>