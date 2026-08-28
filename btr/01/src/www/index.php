<?php
if (!headers_sent()) {
    header('Content-Type: application/json');
} else {
    exit;
}

echo json_encode([
    'service' => 'Byte Key API',
    'status' => 'maintenance',
    'runtime' => 'PHP ' . PHP_VERSION,
    'message' => 'Health endpoint is online.',
], JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES);

echo "\n";
