document.addEventListener("DOMContentLoaded", function () {
  const loginForm = document.getElementById("loginForm");

  if (!loginForm) {
    return;
  }

  const usernameInput = document.getElementById("username");
  const passwordInput = document.getElementById("password");
  const usernameError = document.getElementById("usernameError");
  const passwordError = document.getElementById("passwordError");

  loginForm.addEventListener("submit", function (event) {
    let isValid = true;

    usernameError.textContent = "";
    usernameError.classList.remove("show");
    passwordError.textContent = "";
    passwordError.classList.remove("show");

    if (usernameInput.value.trim() === "") {
      usernameError.textContent = "Username is required.";
      usernameError.classList.add("show");
      isValid = false;
    }

    if (passwordInput.value.trim() === "") {
      passwordError.textContent = "Password is required.";
      passwordError.classList.add("show");
      isValid = false;
    }

    if (!isValid) {
      event.preventDefault();
    }
  });

  usernameInput.addEventListener("input", function () {
    if (usernameInput.value.trim() !== "") {
      usernameError.textContent = "";
      usernameError.classList.remove("show");
    }
  });

  passwordInput.addEventListener("input", function () {
    if (passwordInput.value.trim() !== "") {
      passwordError.textContent = "";
      passwordError.classList.remove("show");
    }
  });
});
