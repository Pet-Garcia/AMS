
const currentScript = document.currentScript;
const includeDirectory = new URL("../include/", currentScript.src);

const includeTargets = [
    ["head.html", document.querySelector("#head-content")],
    ["header.html", document.querySelector("#header-content")],
    ["footer.html", document.querySelector("#footer-content")]
];

async function carregarIncludes() {
    try {
        const fragments = await Promise.all(
            includeTargets.map(async ([file, target]) => {
                if (!target) {
                    throw new Error(`O elemento para carregar ${file} não foi encontrado.`);
                }

                const response = await fetch(new URL(file, includeDirectory));
                if (!response.ok) {
                    throw new Error(`Não foi possível carregar ${file} (HTTP ${response.status}).`);
                }

                return [target, await response.text()];
            })
        );

        fragments.forEach(([target, html]) => {
            target.innerHTML = html;
        });

        const pageTitle = document.querySelector("#main-content")?.dataset.pageTitle;
        if (pageTitle) {
            document.title = pageTitle;
        }
    } catch (error) {
        console.error("Erro ao montar o layout:", error);

        const notice = document.createElement("p");
        notice.setAttribute("role", "alert");
        notice.textContent = "Não foi possível carregar todos os elementos do layout. Verifique os arquivos de include.";
        document.querySelector("#main-content")?.prepend(notice);
    }
}

carregarIncludes();
