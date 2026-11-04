class Header_component extends HTMLElement {
  connectedCallback() {
    this.innerHTML = `
        <header>
            <nav>
                <a href="inicio.php" class="logo">Inicio</a>
                <a href="cursos.php" class="logo">Cursos</a>
                <a href="lista.php" class="logo">Lista</a>
                <a href="perfil.php" class="logo perfil">Pefil</a>
            </nav>
        </header>
    `;
  }
}

customElements.define("header-component", Header_component);