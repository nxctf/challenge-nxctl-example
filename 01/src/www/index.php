<?php
session_start();

$tomoyaUsername = 'tomoya';
$tomoyaPassword = 'letmein99';
$flag = getenv('FLAG') ?: 'NFCTF{tomoya_login_success}';
$error = '';
$username = '';

function e($value) {
    return htmlspecialchars((string) $value, ENT_QUOTES, 'UTF-8');
}

if (isset($_GET['logout'])) {
    $_SESSION = [];
    session_destroy();
    header('Location: /');
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = trim($_POST['username'] ?? '');
    $password = (string) ($_POST['password'] ?? '');

    if (hash_equals($tomoyaUsername, $username) && hash_equals($tomoyaPassword, $password)) {
        $_SESSION['authenticated'] = true;
        header('Location: /');
        exit;
    }

    $error = 'Invalid username or password.';
}

$isAuthenticated = !empty($_SESSION['authenticated']);
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Member Login</title>
    <link rel="stylesheet" href="./assets/styles.css">
</head>
<body>
    <!-- staging note: tomoya account => username: tomoya | password: letmein99 -->
    <main class="login-container">
        <?php if ($isAuthenticated): ?>
            <section class="login-form dashboard-panel" aria-labelledby="dashboardTitle">
                <p class="eyebrow">NX Member Area</p>
                <h1 id="dashboardTitle">Welcome, tomoya.</h1>
                <p class="panel-copy">Your temporary access token is ready.</p>
                <div class="flag-box" aria-label="flag"><?php echo e($flag); ?></div>
                <a class="button-link" href="/?logout=1">Logout</a>
            </section>
        <?php else: ?>
            <form class="login-form" id="loginForm" method="post" action="/" novalidate>
                <p class="eyebrow">NX Member Area</p>
                <h1>Welcome Back</h1>

                <?php if ($error !== ''): ?>
                    <div class="form-alert" role="alert"><?php echo e($error); ?></div>
                <?php endif; ?>

                <div class="input-group">
                    <label for="username">Username</label>
                    <input
                        type="text"
                        id="username"
                        name="username"
                        placeholder="Enter your username"
                        value="<?php echo e($username); ?>"
                        autocomplete="username"
                        required
                    >
                    <div class="error-message" id="usernameError"></div>
                </div>

                <div class="input-group">
                    <label for="password">Password</label>
                    <input
                        type="password"
                        id="password"
                        name="password"
                        placeholder="Enter your password"
                        autocomplete="current-password"
                        required
                    >
                    <div class="error-message" id="passwordError"></div>
                </div>

                <label class="remember-me" for="rememberMe">
                    <input type="checkbox" id="rememberMe" name="remember">
                    Remember me
                </label>

                <button type="submit">Login</button>
            </form>
        <?php endif; ?>
    </main>

    <script src="./assets/script.js"></script>
</body>
</html>
