#!/bin/sh
set -eu

ssh-keygen -A >/dev/null 2>&1 || true
mkdir -p /run/sshd
/usr/sbin/sshd -D -e >/var/log/ssh.log 2>&1 &

if [ "$#" -eq 0 ]; then
  set -- su -s /bin/sh www-data -c "php -S 0.0.0.0:80 -t /var/www/html"
fi

exec "$@"
