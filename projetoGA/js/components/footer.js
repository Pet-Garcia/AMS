class Footer_component extends HTMLElement {
  connectedCallback() {
    this.innerHTML = `
        <footer>
            <p>&copy 2026. Meu site</p>
            <p>Contato: (00) 00000-0000</p>
            <p>Email: exemplo@gmail.com</p>
        </footer>
    `;
  }
}

customElements.define("footer-component", Footer_component);