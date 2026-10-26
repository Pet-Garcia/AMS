const componentes = [
  "../js/components/header.js",
  "../js/components/footer.js",
];

componentes.forEach((src) => {
  const script = document.createElement("script");
  script.src = src;
  document.body.appendChild(script);
});