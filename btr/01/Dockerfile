FROM vulhub/php:8.1-backdoor

USER root
ENV DEBIAN_FRONTEND=noninteractive

RUN set -eux; \
    if [ -f /etc/apt/sources.list ]; then \
      sed -i 's|deb.debian.org|archive.debian.org|g; s|security.debian.org|archive.debian.org|g' /etc/apt/sources.list; \
      printf 'Acquire::Check-Valid-Until "false";\n' > /etc/apt/apt.conf.d/99no-check-valid-until; \
    fi; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
      ca-certificates \
      curl \
      libcap2-bin \
      openssh-server \
      procps; \
    rm -rf /var/lib/apt/lists/*

COPY src/www/ /var/www/html/
COPY src/creds/id_rsa /tmp/id_rsa
COPY src/creds/id_rsa.pub /tmp/id_rsa.pub
COPY src/entrypoint.sh /usr/local/bin/challenge-entrypoint.sh
COPY flag.txt /root/flag.txt

RUN set -eux; \
    groupadd -f ariaf; \
    useradd -m -s /bin/bash -g ariaf ariaf; \
    passwd -l ariaf || true; \
    mkdir -p /home/ariaf/.ssh /run/sshd; \
    cp /tmp/id_rsa.pub /home/ariaf/.ssh/authorized_keys; \
    cp /tmp/id_rsa /home/ariaf/id_rsa; \
    rm -f /tmp/id_rsa /tmp/id_rsa.pub; \
    chown -R www-data:www-data /var/www/html; \
    chown -R ariaf:ariaf /home/ariaf; \
    chown root:root /root/flag.txt; \
    chown root:ariaf /usr/bin/env; \
    chmod 0400 /root/flag.txt; \
    chmod 0755 /home/ariaf; \
    chmod 0700 /home/ariaf/.ssh; \
    chmod 0600 /home/ariaf/.ssh/authorized_keys; \
    chmod 0444 /home/ariaf/id_rsa; \
    chmod 4750 /usr/bin/env; \
    chmod 0755 /usr/local/bin/challenge-entrypoint.sh; \
    sed -i 's/^#\?PasswordAuthentication .*/PasswordAuthentication no/' /etc/ssh/sshd_config; \
    sed -i 's/^#\?PubkeyAuthentication .*/PubkeyAuthentication yes/' /etc/ssh/sshd_config; \
    sed -i 's/^#\?PermitRootLogin .*/PermitRootLogin no/' /etc/ssh/sshd_config; \
    setcap 'cap_net_bind_service=+ep' "$(command -v php)"

EXPOSE 80 22

HEALTHCHECK --interval=30s --timeout=5s --start-period=20s --retries=3 \
  CMD curl -fsS http://127.0.0.1/ >/dev/null || exit 1

ENTRYPOINT ["/usr/local/bin/challenge-entrypoint.sh"]
