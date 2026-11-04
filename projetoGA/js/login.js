const loginSection = document.querySelector("#login-section");
const registerSection = document.querySelector("#register-section");
const message = document.querySelector("#auth-message");

document.querySelectorAll("[data-show]").forEach((button) => {
    button.addEventListener("click", () => {
        const showRegister = button.dataset.show === "register";
        loginSection.hidden = showRegister;
        registerSection.hidden = !showRegister;
        message.textContent = "";
    });
});

async function enviarFormulario(form, action) {
    message.textContent = "";

    const formData = new FormData(form);
    const dados = Object.fromEntries(formData.entries());

    try {
        const response = await fetch("../api/auth.php", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ action, ...dados })
        });
        const resultado = await response.json();

        if (!response.ok) {
            throw new Error(resultado.message || "Não foi possível concluir a solicitação.");
        }

        message.textContent = resultado.message;
        if (action === "login") {
            window.location.replace("../include/layout.php?pagina=inicio");
        } else {
            form.reset();
            loginSection.hidden = false;
            registerSection.hidden = true;
        }
    } catch (error) {
        message.textContent = error.message || "Não foi possível conectar ao servidor.";
    }
}

document.querySelector("#login-form").addEventListener("submit", (event) => {
    event.preventDefault();
    enviarFormulario(event.currentTarget, "login");
});

document.querySelector("#register-form").addEventListener("submit", (event) => {
    event.preventDefault();
    enviarFormulario(event.currentTarget, "register");
});
